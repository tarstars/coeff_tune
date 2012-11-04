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

typedef pair<Vector3, Vector3> NVels;
typedef vector<NVels> VNVels;

//Global variables declaration.
int np, nq;
vector<double> phi, theta;

/*
void testReadFile(){
  ifstream sour("..\\linbo3_data\\linbo3_fqs_25c_sw.txt");
  int np = 0, nq = 0;
  cout << "np = " << np << " nq = " << nq << endl;

  if (!sour){
    cout << "Problems with file open." << endl;
    return;
  }
  else if (sour){
    cout << "File one is ready." << endl;
  }
  sour >> np >> nq;

  cout << "np = " << np << " nq = " << nq << endl;
  
  double val;
  vector<int>  phi;
  vector<int>  theta;
  double vel[19][13];
  vector<NVels> ret;

  for(int p = 0; p < np+1; ++p){
    for(int q = 0; q < nq+1; ++q){
      sour >> val;
      if (p == 0){
	phi.push_back(val);
	if (q == nq){
	  p = 1;
	  q = 0;
	  cout << "!" << endl;
	}
      }
      if (q == 0 && p !=0){
	theta.push_back(val);
      }
      else{
	vel[p-1][q-1] = val;
      }
      
      //Vector3 n = makeWaveVector(cos(3), sin(15), cos(18));
      //Vector3 vel = makeWaveVector(1, 2, 3);
      
      
      //ret.push_back(make_pair(n, vel));
      //cout << val  << " ";
      
    }
    // cout << endl << "return" << endl;
  }
  cout << "Phi array: ";
  for(int q = 0; q < nq; ++q){
    cout << phi[q] << " ";
  }
  cout << endl;
  cout << "Theta array: ";
  for(int p = 0; p < np; ++p){
    cout << theta[p] << " ";
  }
  cout << endl;
  for(int p = 0; p < np; ++p){
    for(int q = 0; q < nq; ++q){
      cout << vel[p][q] << " ";
    }
    cout << endl;
  }
 }
*/

//Textbook data extraction
VNVels extract_data(){
  ifstream sour1("..\\linbo3_data\\linbo3_ql_0c_sw.txt");
  ifstream sour2("..\\linbo3_data\\linbo3_sqs_0c_sw.txt");
  ifstream sour3("..\\linbo3_data\\linbo3_fqs_0c_sw.txt");
    
  if (!sour1){cout << "Problems with data sheet one open." << endl;}
  else if (sour1){cout << "Data sheet one is ready." << endl;}
  if (!sour2){cout << "Problems with data sheet two open." << endl;}
  else if (sour2){cout << "Data sheet two is ready." << endl;}
  if (!sour3){cout << "Problems with data sheet three open." << endl;}
  else if (sour3){cout << "Data sheet three is ready." << endl;}
  
  int np1, nq1;
  int np2, nq2;
  int np3, nq3;

  sour1 >> np1 >> nq1;
  sour2 >> np2 >> nq2;
  sour3 >> np3 >> nq3;
  
  if(np1 != np2 || np1 != np3 || np2 != np3 || nq1 != nq2 || nq1 != nq3 || nq2 != nq3){
    cout << "Different data sheets formats." << endl;}
  np = np1; 
  nq = nq1;
  
  double val1, val2, val3;
  double minvel, medvel, maxvel;

  VNVels ret;

  for(int q = 0; q < nq; ++q){
    sour1 >> val1;
    sour2 >> val2;
    sour3 >> val3;
     
    if (val1 == val2 && val1 == val3){
      phi.push_back(val1*M_PI/180);
    }
    else{
      cout << "Different phi angles in data sheets." << endl; 
    }
  }
  
  for(int p = 0; p < np; ++p){
    sour1 >> val1;
    sour2 >> val2;
    sour3 >> val3;
    
    if (val1 == val2 && val1 == val3){
      theta.push_back(val1*M_PI/180);
    }
    else{
      cout << "Different theta angles in data sheets." << endl; 
    }
  
    for(int q = 0; q < nq; ++q){
        sour1 >> val1;
	sour2 >> val2;
	sour3 >> val3;
	
	maxvel = max(max(val1, val2), val3);
	minvel = min(min(val1, val2), val3);
	medvel = val1 + val2 + val3 - maxvel - minvel;
	
	Vector3 n = makeWaveVector(sin(theta[p])*cos(phi[q]), sin(theta[p])*sin(phi[q]), cos(theta[p]));
	Vector3 vels = makeWaveVector(minvel, medvel, maxvel);
	
	ret.push_back(make_pair(n, vels));
	// cout << ret.back().first << "\t" << ret.back().second << endl;
    }
  }

  cout <<  "Phi (size  " << phi.size() <<"):" << endl;
  for(int q = 0; q < nq; ++q){
    cout << phi[q]*180/M_PI << " ";
  }
  cout << endl;
  cout <<  "Theta (size  " << theta.size() <<"):" << endl;
  for(int p = 0; p < np; ++p){
    cout << theta[p]*180/M_PI << " ";
  }
  cout << endl;

  return ret;
}

//Velocities calculation function
VNVels calculate_nvels(const vector<double>& phi, const vector<double>& theta)
{
  VNVels ret;
  double rho =4642.8;
  double r1, r2, r3;
  double vel1, vel2, vel3;
  double minvel, medvel, maxvel;

  PiezoTensor pt=makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  //PiezoTensor pt=makePiezoTensor(0, 0, 0, 0);
  //cout << "Piezo tensor:" << endl << pt << endl;

  MaterialTensor mt = makeMaterialTensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);
  //cout << "Material tensor:" << endl << mt << endl;

  Matrix3 et = makeEpsilonTensor(44.9, 26.7);
  //cout << "Epsilon tensor:" << endl << et <<endl;

  for(int p = 0; p < np; ++p){
    for(int q = 0; q < nq; ++q){
      Vector3 n = makeWaveVector(sin(theta[p])*cos(phi[q]), sin(theta[p])*sin(phi[q]), cos(theta[p]));
      // cout << "Wave vector:" << endl << n <<endl;

      Matrix3 chr = makePiezoChristoffel(mt, pt, et, n);
      //cout << "Christoffel matrix:" << endl << chr << endl;

      Poly3 chrpoly = chr.getCharPoly();
      //cout << "Characteristic polynomial of Christoffel matrix:" << endl << chrpoly << endl << endl;
      chrpoly.solve(&r1, &r2, &r3);
  
      vel1 = sqrt(r1 / rho);
      vel2 = sqrt(r2 / rho);
      vel3 = sqrt(r3 / rho);

      maxvel = max(max(vel1, vel2), vel3);
      minvel = min(min(vel1, vel2), vel3);
      medvel = vel1 + vel2 + vel3 - maxvel - minvel;
	
      Vector3 vels = makeWaveVector(minvel, medvel, maxvel);
	
      ret.push_back(make_pair(n, vels));
      // cout << ret.back().first << "\t" << ret.back().second << endl;

      // cout << "Velocity 1 = " << vel1 << " [m/sec];" << endl;
      // cout << "Velocity 2 = " << vel2 << " [m/sec];" << endl; 
      // cout << "Velocity 3 = " << vel3 << " [m/sec];" << endl;
    }
  }
  // cout << endl << "Cake is waiting for you!" << endl;
  return ret;
}

int main()
{
  cout << "Hello and welcome to Aperture Science Enrichment Center's" << endl << "Cute Piezocrystal's Acoustic Waves Speed Finder!" << endl << endl;
  //work();
  // testReadFile();
  VNVels nvels_exp = extract_data();
  VNVels nvels_num = calculate_nvels(phi, theta);
  for(int r = 0; r < nvels_exp.size(); ++r){
    cout << "Exp: " << nvels_exp[r].first << "\t" << nvels_exp[r].second << endl;
    cout << "Num: " << nvels_num[r].first << "\t" << nvels_num[r].second << endl;
  }
}
