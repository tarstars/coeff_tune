#ifndef sa
#define sa
#include<fstream>
#include<iostream>
#include<cmath>
#include <cstdlib>
#include <ctime>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#define pi 3.141592654

using namespace std;

struct param{
double initTemperature;
int iterations;
bool cool;
};

double * TuneConstants(double * constants, param parameters, gsl_rng * generator);
void Randomize(double * constants, double T, gsl_rng * generator);
double Discrepancy(double * constants);
double Cubic(double * constants, int x);


#endif
