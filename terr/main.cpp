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

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using namespace std;

typedef pair<Vector3, Vector3> NVels;
typedef vector<NVels> VNVels;

//Global variables declaration and initialization.
int np, nq;
vector<double> phi, theta;

VNVels nvels_exp;
VNVels nvels_num;

double init_discrepancy;
double curr_discrepancy;
double best_discrepancy;

double temperature = 33;
int iter = 1000000;

vector<double> cfmat(7); //Initial material tenzor parameters [1e10]
vector<double> cfpiezo(4);//Initial piezo tenzor parameters
vector<double> cfeps(2);//Initial relative permittivity

vector<vector<double> > coeffs;


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
VNVels calculateNVels(const vector<double>& phi, const vector<double>& theta, const vector<vector<double> >& coeffs)
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
    ret += 
      pow((nvels_num[r].second(0) - nvels_exp[r].second(0)), 2) + 
      pow((nvels_num[r].second(1) - nvels_exp[r].second(1)), 2) +
      pow((nvels_num[r].second(2) - nvels_exp[r].second(2)), 2);
  }
  return ret;
}

vector<vector<double> > shiftCoeffs(vector<vector<double> >& coeffs, gsl_rng* generator, double temperature){

  vector<vector<double> > ret;
  pair<int, int> randy;
  
  ret = coeffs;
  randy = pickCoeff();
  ret[randy.first][randy.second] += ret[randy.first][randy.second]*gsl_ran_gaussian (generator, temperature);
  
  return ret;
}

vector<vector<double> > anneal(int iter, gsl_rng* generator, double temperature){

  VNVels curr_nvels_num;
  vector<vector<double> > curr_coeffs;
  vector<vector<double> > best_coeffs;
  double delta_exp;
  double accept_prop;
  
  nvels_exp = extractData();
  nvels_num = calculateNVels(phi, theta, coeffs);

  init_discrepancy = getDiscrepancy(nvels_exp, nvels_num);
  best_discrepancy = init_discrepancy;
  best_coeffs = coeffs;
  
  for (int p = 0; p < iter; ++p){
    curr_coeffs = shiftCoeffs(coeffs, generator, temperature);
    curr_nvels_num = calculateNVels(phi, theta, curr_coeffs);
    
    curr_discrepancy = getDiscrepancy(nvels_exp, curr_nvels_num);
    
    delta_exp = exp(-(curr_discrepancy - best_discrepancy) / temperature);
    accept_prop = gsl_ran_flat(generator, 0.0,1.0);
    
    if (delta_exp > accept_prop || best_discrepancy > curr_discrepancy){
      best_coeffs = curr_coeffs;
      best_discrepancy = curr_discrepancy;
      temperature *= 1/log(p+1);
    }
    //  cout << "Best Discrepancy = " << best_discrepancy << "\t Current Discrepancy = " << curr_discrepancy << endl;
  }
  return best_coeffs;
}


int main()
{
  srand(time(NULL));
  int seed=rand();

  gsl_rng *generator = gsl_rng_alloc(gsl_rng_default);
  gsl_rng_set(generator, seed);
  
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

  coeffs.push_back(cfmat);
  coeffs.push_back(cfpiezo);
  coeffs.push_back(cfeps);

  
  cout << "Hello and welcome to Aperture Science Enrichment Center's" << endl << "Cute Piezocrystal's Parameters Finder!" << endl << endl;

  // nvels_exp = extractData();
  // nvels_num = calculateNVels(phi, theta, coeffs);
  
  //Print nvels comparison
 /* for(unsigned int r = 0; r < nvels_exp.size(); ++r){
    cout << "Exp: " << nvels_exp[r].first << "\t" << nvels_exp[r].second << endl;
    cout << "Num: " << nvels_num[r].first << "\t" << nvels_num[r].second << endl;
    }*/
 // init_discrepancy = getDiscrepancy(nvels_exp, nvels_num);
  //cout << "Discrepancy = " << init_discrepancy << endl;
  
  vector<vector<double> > best_coeffs = anneal(iter, generator, temperature);
  VNVels best_nvels_num = calculateNVels(phi, theta, best_coeffs);
  best_discrepancy = getDiscrepancy(nvels_exp, best_nvels_num);
  cout << "Discrepancy = " << best_discrepancy << endl;
  
  gsl_rng_free(generator);
}
