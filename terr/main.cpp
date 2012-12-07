#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "piezo_tensor.h"
#include "material_tensor.h"
#include "matrix3.h"
#include "vector3.h"
#include "poly3.h"
#include "util.h"

using namespace std;

typedef pair<Vector3, Vector3> NVels;
typedef vector<NVels> VNVels;
typedef vector<vector<double> > Coeffs;

//Global variables declaration and initialization.
int np, nq;
vector<double> phi, theta;
vector<double> cfmat(7); //Initial material tenzor parameters [1e10]
vector<double> cfpiezo(4);//Initial piezo tenzor parameters
vector<double> cfeps(2);//Initial relative permittivity

//Textbook data extraction
VNVels extractData(){
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
VNVels calculateNVels(const vector<double>& phi, const vector<double>& theta, const Coeffs& coeffs)
{
  VNVels ret;
  double rho =4642.8;
  double r1, r2, r3;
  double vel1, vel2, vel3;
  double minvel, medvel, maxvel;

  MaterialTensor mt = makeMaterialTensor(coeffs[0]);
  //cout << "Material tensor:" << endl << mt << endl;

  PiezoTensor pt=makePiezoTensor(coeffs[1]);
  //PiezoTensor pt=makePiezoTensor(0, 0, 0, 0);
  //cout << "Piezo tensor:" << endl << pt << endl;

  Matrix3 et = makeEpsilonTensor(coeffs[2]);
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

double getDiscrepancy(const VNVels& nvels_exp, const VNVels& nvels_num)
{
  double ret = 0;
  
  for(unsigned int r = 0; r < nvels_exp.size(); ++r){
    double a = (nvels_num[r].second(0) - nvels_exp[r].second(0));
    double b = (nvels_num[r].second(1) - nvels_exp[r].second(1));
    double c = (nvels_num[r].second(2) - nvels_exp[r].second(2));
    ret += a*a + b*b + c*c;
    //   cout << "a = " << a << " b = " << b << " c = " << c << " dscr = " << ret << endl;
  }
  ret = ret/nvels_exp.size();
  return ret;
}

Coeffs shiftCoeffs(const Coeffs& coeffs){

  Coeffs ret;
  pair<int, int> randy;
  double partToVary = 0.0001;
  double rv = double(rand()) / RAND_MAX;
  rv = 2 * (rv - 0.5);

  ret = coeffs;
  randy = pickCoeff();
  ret[randy.first][randy.second] *= (1 + partToVary * rv);
  
  return ret;
}

VNVels nvels_exp;
VNVels nvels_num;
Coeffs coeffs;

double temperature = 0.0000001;
int iter = 10;

Coeffs anneal(int iter, double temperature){
  nvels_exp = extractData();  

  Coeffs curr_coeffs = coeffs;
  Coeffs best_coeffs = coeffs;
  VNVels curr_nvels = calculateNVels(phi, theta, curr_coeffs);
  double curr_discrepancy = getDiscrepancy(nvels_exp, curr_nvels);
  double best_discrepancy = curr_discrepancy;
  double energy;
  double chance;
  int counter = 0;

  best_discrepancy = curr_discrepancy;
  cout << "Initial discrepancy: " << best_discrepancy << endl;

  for(int p = 0; p < iter; ++p){
    curr_coeffs = shiftCoeffs(best_coeffs);
    curr_nvels = calculateNVels(phi, theta, curr_coeffs);
    curr_discrepancy = getDiscrepancy(nvels_exp, curr_nvels);
    
    chance = double(rand())/RAND_MAX;
    energy = exp(-(curr_discrepancy - best_discrepancy)/temperature);
    cout  << "Best: " << best_discrepancy << "\tCurrent: " << curr_discrepancy  << "\tDelta: " << energy << "\tChance: " << chance;

    if(energy > chance){
      cout << "\tGG" << endl;
      best_discrepancy = curr_discrepancy;
      best_coeffs = curr_coeffs;
      counter++;
    }
    else{
      cout << endl;
    }
  }
  cout << "Counter: " << counter << endl;
  for(int p = 0; p < 3; ++p){
    for(unsigned int q = 0; q < best_coeffs[p].size(); ++q){
      if(p == 0){cout << "cfmat[" << q << "] = " << best_coeffs[p][q] << ";" << endl;}
      if(p == 1){cout << "cfpiezo[" << q << "] = " << best_coeffs[p][q] << ";" << endl;}
      if(p == 2){cout << "cfeps[" << q << "] = " << best_coeffs[p][q] << ";" << endl;}
    }
  }
  return best_coeffs;
}

int main()
{
  srand(time(NULL));
  /*
  //Kushibiki coeffs
  cfmat[0] = 19.886;
  cfmat[1] = 5.467;
  cfmat[2] = 6.799;
  cfmat[3] = 0.783;
  cfmat[4] = 23.418;
  cfmat[5] = 5.985;
  cfmat[6] = 7.209;

  cfpiezo[0] = 3.655;
  cfpiezo[1] = 2.407;
  cfpiezo[2] = 0.328;
  cfpiezo[3] = 1.894;

  cfeps[0] = 44.9;
  cfeps[1] = 26.7;
  */
  cfmat[0] = 20.3811;
  cfmat[1] = 5.76408;
  cfmat[2] = 7.54739;
  cfmat[3] = 0.85425;
  cfmat[4] = 24.3244;
  cfmat[5] = 5.97822;
  cfmat[6] = 7.30852;
  cfpiezo[0] = 4.1312;
  cfpiezo[1] = 2.67444;
  cfpiezo[2] = 0.252067;
  cfpiezo[3] = 1.43387;
  cfeps[0] = 53.4247;
  cfeps[1] = 33.4012; 
 /*
  cfmat[0] = 20.3814;
  cfmat[1] = 5.76431;
  cfmat[2] = 7.54762;
  cfmat[3] = 0.854336;
  cfmat[4] = 24.3247;
  cfmat[5] = 5.9782;
  cfmat[6] = 7.30838;
  cfpiezo[0] = 4.1312;
  cfpiezo[1] = 2.67444;
  cfpiezo[2] = 0.251738;
  cfpiezo[3] = 1.43349;
  cfeps[0] = 53.4246;
  cfeps[1] = 33.3947;
  */
/* Terrum best
  cfmat[0] = 20.3733;
  cfmat[1] = 5.76002;
  cfmat[2] = 7.52272;
  cfmat[3] = 0.853238;
  cfmat[4] = 24.2971;
  cfmat[5] = 5.97872;
  cfmat[6] = 7.31158;
  cfpiezo[0] = 4.11959;
  cfpiezo[1] = 2.6693;
  cfpiezo[2] = 0.288409;
  cfpiezo[3] = 1.47162;
  cfeps[0] = 53.155;
  cfeps[1] = 33.9506;*/
  /*  //Terrum' second to best
  cfmat[0] = 20.4111;
  cfmat[1] = 5.777339;
  cfmat[2] = 7.36441;
  cfmat[3] = 0.84533;
  cfmat[4] = 23.9542;
  cfmat[5] = 5.99331;
  cfmat[6] = 7.30143;

  cfpiezo[0] = 3.63674;
  cfpiezo[1] = 2.34767;
  cfpiezo[2] = 0.338447;
  cfpiezo[3] = 1.65699;

  cfeps[0] = 41.6584;
  cfeps[1] = 30.0418;*/

  /*
    //Tarstars' best
  cfmat[0] = 20.3777;
  cfmat[1] = 5.76219;
  cfmat[2] = 7.53698;
  cfmat[3] = 0.853752;
  cfmat[4] = 24.313;
  cfmat[5] = 5.97846;
  cfmat[6] = 7.30987;

  cfpiezo[0] = 3.92559;
  cfpiezo[1] = 2.54236;
  cfpiezo[2] = 0.254881;
  cfpiezo[3] = 1.37947;

  cfeps[0] = 48.2537;
  cfeps[1] = 30.4489;
*/  
  
  coeffs.push_back(cfmat);
  coeffs.push_back(cfpiezo);
  coeffs.push_back(cfeps);

  
  cout << "Hello and welcome to Aperture Science Enrichment Center's" << endl << "Cute Piezocrystal's Parameters Finder!" << endl << endl;

  // Coeffs best_coeffs = anneal(iter, temperature);
  nvels_exp = extractData();
  nvels_num = calculateNVels(phi, theta, coeffs);
  
  //Print nvels comparison
  for(unsigned int r = 0; r < nvels_exp.size(); ++r){
    cout << "Exp: " << nvels_exp[r].first << "\t" << nvels_exp[r].second << endl;
    cout << "Num: " << nvels_num[r].first << "\t" << nvels_num[r].second << endl;
  }
   //  double init_discrepancy = getDiscrepancy(nvels_exp, nvels_num);
  //  cout << "Discrepancy = " << init_discrepancy << endl;
 

}
