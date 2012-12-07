#include "util.h"
#include "piezo_tensor.h"
#include "material_tensor.h"
#include "matrix3.h"
#include "vector3.h"
#include <cstdlib>

using namespace std;

int magic[3][3] = {{0, 5, 4},
		   {5, 1, 3},
		   {4, 3, 2}};

PiezoTensor
makePiezoTensor(const vector<double>& cfpiezo){
  double e15 = cfpiezo[0];
  double e22 = cfpiezo[1];
  double e31 = cfpiezo[2];
  double e33 = cfpiezo[3];
  PiezoTensor ret;
  double ptc[3][6] = {{0, 0, 0, 0, e15, -e22}, 
		      {-e22, e22, 0, e15, 0, 0}, 
		      {e31, e31, e33, 0, 0, 0}};
  
  for(int p=0; p<3; ++p)
    for(int q=0; q<3; ++q)
      for(int r=0; r<3; ++r)
	ret(p, q, r) = ptc[p][magic[q][r]];
  
  return ret;
}

MaterialTensor 
makeMaterialTensor(const vector<double>& cfmat){
  double c11 = cfmat[0]*1e10; 
  double c12 = cfmat[1]*1e10;
  double c13 = cfmat[2]*1e10;
  double c14 = cfmat[3]*1e10;
  double c33 = cfmat[4]*1e10;
  double c44 = cfmat[5]*1e10;
  double c66 = cfmat[6]*1e10;
  MaterialTensor ret;
  double mtc[6][6] = {{c11, c12, c13, c14, 0, 0}, 
		      {c12, c11, c13, -c14, 0, 0}, 
		      {c13, c13, c33, 0, 0, 0},
		      {c14, -c14, 0, c44, 0, 0}, 
		      {0, 0, 0, 0, c44, c14}, 
		      {0, 0, 0, 0, c14, c66}};

  for(int p=0; p<3; ++p)
    for(int q=0; q<3; ++q)
      for(int r=0; r<3; ++r)
	for(int s=0; s<3; ++s)
	  ret(p, q, r, s) = mtc[magic[p][q]][magic[r][s]];
  
  return ret;
}

Matrix3 
makeEpsilonTensor(const vector<double>& cfeps){
  double eps11 = cfeps[0];
  double eps33 = cfeps[1];
  Matrix3 ret;
  double eps0 = 8.8542e-12;
  double epstc[3][3] = {{eps0*eps11, 0, 0}, 
			{0, eps0*eps11, 0}, 
			{0, 0, eps0*eps33}};

  for(int p=0; p<3; ++p)
    for(int q=0; q<3; ++q)
      ret(p, q) = epstc[p][q];
  
  return ret;
}

Vector3 
makeWaveVector(double x, double y, double z){
  Vector3 ret;
  if (x < 1e-12)
    x = 0;
  if (y < 1e-12)
    y = 0;
  if (z < 1e-12)
    z = 0;
  double wv[3] ={x, y, z};

  for(int p=0; p<3; ++p)
    ret(p) = wv[p];
  
  return ret;
}

Matrix3
makePiezoChristoffel(const MaterialTensor& mtens, 
		     const PiezoTensor& ptens, 
		     const Matrix3& etens, 
		     const Vector3& n){
  Matrix3 ret;
  
  //GG_ps = G_ps + g_p*g_s/eps

  double eps = 0;
  for(int p = 0; p < 3; ++p)
    eps += etens(p, p) * n(p) * n(p);

  for (int p = 0; p < 3; ++p){
    for(int s = 0; s < 3; ++s){
  
      double gamma_ps = 0; //Main christoffel
      double gamma_p = 0;  //Piezo part 1
      double gamma_s = 0;  //Piezo part 2
      
      for(int q = 0; q < 3; ++q){
	for(int r = 0; r < 3; ++r){
	  gamma_ps += mtens(p, q, r, s) * n(q) * n(r);
	  gamma_p += ptens(q, p, r) * n(q) * n(r);
	  gamma_s += ptens(q, s, r) * n(q) * n(r);
	}
      }
      ret(p, s) = gamma_ps + gamma_p * gamma_s / eps; 
    }
  }
  
  return ret;
}

pair<int, int> pickCoeff(){

  pair<int, int> ret;

  ret.first = rand()%3;
  if(ret.first == 0)
    ret.second = rand()%7;
  else if(ret.first == 1)
    ret.second = rand()%4;
  else if(ret.first == 2)
    ret.second = rand()%2;
  
  return ret;
}
