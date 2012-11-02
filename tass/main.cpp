#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "mat3.h"
#include "material_tensor.h"
#include "piezo_tensor.h"
#include "poly3.h"
#include "util.h"
#include "vec3.h"

using namespace std;

typedef pair<Vec3, Vec3> NVels; //first = n, second = v1, v2, v3
typedef vector<pair<Vec3, Vec3> > VNVels;

//D:\\arseniy\\2012\\c\\coeff_tune
//..\\linbo3_data\\linbo3_sqs_0c_sw.txt

VNVels readFile(string flnm1, string flnm2, string flnm3) {
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

  cout << "first" << endl;

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

      Vec3 n(sin(theta) * cos(phis[q]), sin(theta) * sin(phis[q]), cos(theta));
      Vec3 vel(val1, val2, val3);

      ret.push_back(make_pair(n, vel));
    }
  }

  cout << "second" << endl;

  return ret;
}

void testReadFile() {
  VNVels vecs = readFile("../linbo3_data/linbo3_sqs_0c_sw.txt",
			 "../linbo3_data/linbo3_ql_0c_sw.txt",
			 "../linbo3_data/linbo3_fqs_0c_sw.txt"
			 );
  
  for(auto it = vecs.begin(); it != vecs.end(); ++it) {
    cout << "vect = " << it->first << " " << it->second << endl;
  }
}

void work() {
  PiezoTensor pt = makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  MaterialTensor mt = makeMaterialTensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);

  double rho = 4642.8;
  double eps0 = 8.8542e-12;
  double exx = eps0 * 44.9;
  double ezz = eps0 * 26.7;


  Vec3 n(0, 0, 1);

  Mat3 christ = makePiezoChristoffel(pt, mt, n, exx, ezz);
  Poly3 christPoly = christ.getPoly();
  
  double g1, g2, g3;
  christPoly.solve(&g1, &g2, &g3);
  double v1 = sqrt(g1 / rho);
  double v2 = sqrt(g2 / rho);
  double v3 = sqrt(g3 / rho);

  cout << "piezo tensor: " << endl << pt << endl;
  cout << "material tensor: " << endl << mt << endl;
  cout << "christoffel matrix: " << endl << christ << endl;
  cout << "polynome " << christPoly << endl;
  cout << "velocities = " << v1 << " " << v2 << " " << v3 << endl;
}

void testPolynome() {
  double g1, g2, g3;
  Poly3(1, -11, 31, -21).solve(&g1, &g2, &g3);
  cout << "g1 g2 g3 = " << g1 << " " << g2 << " " << g3 << endl;
}

int main() {
  //testPolynome();
  //work();
  try { 
    testReadFile();
  } catch (string msg) {
    cout << "error: " << msg << endl;
  }
}
