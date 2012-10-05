#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "piezo_tensor.h"
#include "material_tensor.h"
#include "matrix3.h"
#include "vector3.h"
#include "poly3.h"
#include "util.h"

using namespace std;

//typedef pair<Vector3, Vector3> NVels;


void testReadFile(){
  ifstream sour("..\\..\\linbo3_data\\linbo3_fqs_0c_sw.txt");
  int np = 0, nq = 0;
  cout << "np = " << np << " nq = " << nq << endl;

  if (!sour){
    cout << "problems with file open" << endl;
    return;
  }

  cout << "file is ready" << endl;


  sour >> np >> nq;

  cout << "np = " << np << " nq = " << nq << endl;
  /*
  double val;

  vector<NVels> ret;

  for(int p = 0; p < np; ++p){
    for(int q = 0; q < nq; ++q){
      sour >> val;

      Vector3 n = makeWaveVector(cos(3), sin(15), cos(18));
      Vector3 vel = makeWaveVector(1, 2, 3);

      ret.push_back(make_pair(n, vel));
    }
  }
  */
}



void work()
{
  cout << "Hello and welcome to Aperture Science Enrichment Center's" << endl << "Cute Piezocrystal's Acoustic Waves Speed Finder!" << endl << endl;
  
  PiezoTensor pt=makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  //cout << "Piezo tensor:" << endl << pt << endl;

  MaterialTensor mt = makeMaterialTensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);
  //cout << "Material tensor:" << endl << mt << endl;

  Matrix3 et = makeEpsilonTensor(44.9, 26.7);
  //cout << "Epsilon tensor:" << endl << et <<endl;

  /*
  double phi = 0;
  double theta = 0;
  
  cout << "Please, input phi angle [degrees]:" << endl;
  cin >> phi;
  phi = phi * M_PI / 180;

  cout << "Please, input theta angle [degrees]:" << endl;
  cin >> theta;
  theta = theta * M_PI / 180;
  
  Vector3 n = makeWaveVector(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
  cout << "Wave vector:" << endl << n <<endl;
  */

  Vector3 n = makeWaveVector(0, 0, 1);
  cout << "Wave vector:" << endl << n <<endl;

  Matrix3 chr = makePiezoChristoffel(mt, pt, et, n);
  cout << "Christoffel matrix:" << endl << chr << endl;

  Poly3 chrpoly = chr.getCharPoly();
  cout << "Characteristic polynomial of Christoffel matrix:" << endl << chrpoly << endl << endl;

  double rho =4642.8;
  double r1, r2, r3;
  double v1, v2, v3;

  chrpoly.solve(&r1, &r2, &r3);
  
  v1 = sqrt(r1 / rho);
  v2 = sqrt(r2 / rho);
  v3 = sqrt(r3 / rho);

  cout << "Velocity 1 = " << v1 << " [m/sec];" << endl;
  cout << "Velocity 2 = " << v2 << " [m/sec];" << endl; 
  cout << "Velocity 3 = " << v3 << " [m/sec];" << endl;

  cout << endl << "Cake is waiting for you!" << endl;
}

int main()
{
  //  work();
  testReadFile();
}
