#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>

#include "coeffs.h"
#include "util.h"
#include "piezo_tensor.h"
#include "material_tensor.h"
#include "mat3.h"
#include "poly3.h"
#include "vec3.h"

using namespace std;

PiezoTensor 
makePiezoTensor(double e15, double e21, double e31, double e33){
  double mat[][6]={
    {   0,   0,   0,   0,  e15,  -e21},
    {-e21, e21,   0, e15,    0,     0},
    { e31, e31, e33,   0,    0,     0}};
  
  int dict[3][3] = {
    {1, 6, 5},
    {6, 2, 4},
    {5, 4, 3}};

  PiezoTensor ret;

  for(int p = 0; p < 3; ++p)
    for(int q = 0; q < 3; ++q)
      for(int r = 0; r < 3; ++r)
	ret(p,q,r) = mat[p][dict[q][r] - 1]; 

  return ret;
}

MaterialTensor makeMaterialTensor(double c11,
				  double c12,
				  double c13,
				  double c14,
				  double c33,
				  double c44,
				  double c66) {
  MaterialTensor r;

  double arr[6][6] = {
    {c11,  c12, c13,  c14,   0,   0},
    {c12,  c11, c13, -c14,   0,   0}, 
    {c13,  c13, c33,    0,   0,   0},
    {c14, -c14,   0,  c44,   0,   0},
    {  0,    0,   0,    0, c44, c14},
    {  0,    0,   0,    0, c14, c66}};
  
  int dict[3][3] = {
    {1, 6, 5},
    {6, 2, 4},
    {5, 4, 3}};

  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      for(int k = 0; k < 3; ++k)
	for(int l = 0; l < 3; ++l){
	  int p = dict[i][j]; 
	  int q = dict[k][l];
		
	  r(i,j,k,l) = arr[p - 1][q - 1];
	}

  return r;
}

Mat3 
makePiezoChristoffel(const PiezoTensor& pt, 
		     const MaterialTensor& mt, 
		     const Vec3& n,
		     double exx, 
		     double ezz){
  Mat3 ret;

  double eps = exx * (n[0] * n[0] + n[1] * n[1]) + ezz * (n[2] * n[2]); 

  for(int p = 0; p < 3; ++p){
    for(int q = 0; q < 3; ++q){
      double val = 0;
      double gamma_p = 0;
      double gamma_q = 0;

      for(int r = 0; r < 3; ++r){
	for(int s = 0; s < 3; ++s){
	  val += mt(p, r, q, s) * n[r] * n[s];
	  gamma_p += pt(r, p, s) * n[r] * n[s];
	  gamma_q += pt(r, q, s) * n[r] * n[s];
	}
      }

      ret(p, q) = val + gamma_p * gamma_q / eps;
    }
  }

  return ret;
}

VNVels readFiles(string flnm1, string flnm2, string flnm3) {
  ifstream sour1(flnm1.c_str());
  ifstream sour2(flnm2.c_str());
  ifstream sour3(flnm3.c_str());

  int np1, nq1;
  int np2, nq2;
  int np3, nq3;

  sour1 >> np1 >> nq1;
  sour2 >> np2 >> nq2;
  sour3 >> np3 >> nq3;

  if (np1 != np2) {
    throw(string("readFile: mismatch dimensions in 1 and 2 files"));
  }

  if (np2 != np3) {
    throw(string("readFile: mismatch dimensions in 2 and 3 files"));
  }

  int np = np1, nq = nq1;

  if (!sour1) {
    throw(string("problem opening file 1"));
  }

  if (!sour2) {
    throw(string("problem opening file 2"));
  }

  if (!sour3) {
    throw(string("problem opening file 3"));
  }

  vector<double> phis(nq);
  for(int i = 0; i < nq; ++i) {
    sour1 >> phis[i];
    phis[i] *= M_PI / 180;

    double trash;
    sour2 >> trash;
    sour3 >> trash;
  }

  VNVels ret;

  //cout << "first" << endl;

  for(int p = 0; p < np; ++p){
    double theta;
    sour1 >> theta;
    theta *= M_PI / 180;

    double trash;
    sour2 >> trash;
    sour3 >> trash;
    
    for(int q = 0; q < nq; ++q){
      double val1, val2, val3;
      sour1 >> val1;
      sour2 >> val2;
      sour3 >> val3;

      double minval = min(min(val1, val2), val3);
      double maxval = max(max(val1, val2), val3);
      double medval = val1 + val2 + val3 - minval - maxval;

      Vec3 n(sin(theta) * cos(phis[q]), sin(theta) * sin(phis[q]), cos(theta));
      Vec3 vel(minval, medval, maxval);

      ret.push_back(make_pair(n, vel));
    }
  }

  //cout << "second" << endl;

  return ret;
}

double residual(const VNVels& vnv) {
  PiezoTensor pt = makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  MaterialTensor mt = makeMaterialTensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);

  double rho = 4642.8;
  double eps0 = 8.8542e-12;
  double exx = eps0 * 44.9;
  double ezz = eps0 * 26.7;
  
  double ret = 0;
  for(VNVels::const_iterator it = vnv.begin(); it != vnv.end(); ++it) {
    Vec3 n(it -> first);

    Mat3 christ = makePiezoChristoffel(pt, mt, n, exx, ezz);
    Poly3 christPoly = christ.getPoly();
  
    double g1, g2, g3;
    christPoly.solve(&g1, &g2, &g3);
    double v1 = sqrt(g1 / rho);
    double v2 = sqrt(g2 / rho);
    double v3 = sqrt(g3 / rho);

    double maxv = max(max(v1, v2), v3);
    double minv = min(min(v1, v2), v3);
    double medv = v1 + v2 + v3 - maxv - minv;

    Vec3 tv(minv, medv, maxv);
    Vec3 ex = it -> second;

    double curResidual = (ex - tv).norm();
    ret += curResidual;

    if (curResidual > 30000) {
      cout << "curResidual = " << curResidual << " n = " << it -> first 
	   << " experimental = " << it -> second << " theory = " << tv << endl; 
    }
  }

  return ret;
}


Coeffs anneal() {
  Coeffs ret;

  //cout << "initial value " << ret << endl;

  VNVels vecs = readFiles("../linbo3_data/linbo3_sqs_0c_sw.txt",
			  "../linbo3_data/linbo3_ql_0c_sw.txt",
			  "../linbo3_data/linbo3_fqs_0c_sw.txt"
			  );

  const int maxIter = 10000;
  int iterMeter = 0;
  double kt = 1;

  for(; iterMeter < maxIter; ++iterMeter) {
    Coeffs nextPos(ret);
    nextPos.vary(kt);
    
    double resOld = ret.residual(vecs);
    double resNew = nextPos.residual(vecs);
    
    double delta = resNew - resOld;

    double thresh = exp(-delta / kt);

    double rv = double(rand()) / RAND_MAX;

    if (rv < thresh) {
      ret = nextPos;
      cout << "accepted: " << resNew << endl; // " " << ret << endl;
    } else {
      cout << "declined: " << resNew << endl; // " " << ret << nextPos << endl;
    }
  }

  return ret;
}

