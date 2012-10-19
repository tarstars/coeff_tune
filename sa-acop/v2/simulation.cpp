#define __GSL

#include "simulation.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using ::std::cout;
using ::std::ostream;
using ::std::endl;

//  Pretty printing
ostream&  operator<<(ostream& os, const Constants& constants){
  
  os  <<  "<CONSTANTS>: a=" << constants.a << ", b=" << constants.b;
  os  <<  ", c=" << constants.c << ", d=" << constants.d << endl;
  
  return  os;
} //  Constants::operator<<

double  Simulation::cubicPolynomial(double x, Constants coeff){
  return  coeff.a * x * x * x
            + coeff.b * x * x
              + coeff.c * x
                + coeff.d;
} //  Simulation::cubicPolynomial

double  Simulation::calculateResidual(Constants constants){
  double  residual  = 0;
  double  difference  = 0;
  
  for (int x = 0; x < 100; ++x){
    difference  = this->cubicPolynomial(x, constants) - this->cubicPolynomial(x, this->true_constants);
    residual  +=  difference * difference;
  }
  
  return  residual;
} //  Simulation::calculateResidual

inline  double  Simulation::randomUniform(double min, double max){
  return  gsl_ran_flat(this->generator, min, max);
} //  Simulation::randomUniform

inline  double  Simulation::randomGaussian(double dispersion){
  return  gsl_ran_gaussian(this->generator, dispersion);
} //  Simulation::randomGaussian

Constants Simulation::randomizeConstants(Constants constants, double dispersion){
  int const_num = (int)ceil(this->randomUniform(0, 4));
  double  delta = this->randomGaussian(dispersion);
  
  switch (const_num){
    case  1:
      constants.a +=  delta;
      break;
      
    case  2:
      constants.b +=  delta;
      break;
      
    case  3:
      constants.c +=  delta;
      break;
      
    case  4:
      constants.d +=  delta;
      break;
  } //  switch
  
  return  constants;
} //  Simulation::randomizeConstants

void  Simulation::setTrueConstants(Constants true_constants){
  this->true_constants  = true_constants;
} //  Simulation::setTrueConstants

void  Simulation::initializeRandomGenerator(){
  srand((unsigned)time(0));
  int seed  = rand();
  
  this->generator = gsl_rng_alloc(gsl_rng_default);
  gsl_rng_set(this->generator, seed);
} //  Simulation::initializeRandomGenerator

void  Simulation::freeRandomGenerator(){
  gsl_rng_free(this->generator);
} //  Simulation::freeRandomGenerator

Simulation::~Simulation(){
  this->freeRandomGenerator();
} //  Simulation::~Simulation()

Constants Simulation::tuneConstants(Constants constants, AnnealingParams params){
  Constants tuned_constants = constants;
  Constants previous_constants;
  
  double  residual  = this->calculateResidual(constants);
  double  best_residual = residual;
  double  previous_residual = residual;
  
  double  Temperature = params.initialTemperature;
  double  probability;
  double  energy_difference;
  
  //  Annealing
  for (int i = 0; i < params.iterationsNumber; ++i){
    
    cout <<  "annealing in progress... ";
    cout <<  100 * ((double)i / params.iterationsNumber);
    cout << "%" << "\r";
    
    //  Changing constants till energy becomes lower
    while(true) {
      previous_constants = constants;
      previous_residual  = this->calculateResidual(previous_constants);
      
      constants = this->randomizeConstants(constants, Temperature);
      residual  = this->calculateResidual(constants);
      
      energy_difference = exp(-(residual - previous_residual)/Temperature);
      probability = this->randomUniform(0.0, 1.0);
      
      if (energy_difference > probability){
        //  "Energy" (residual) changed sufficiently
        if (residual < best_residual){
          best_residual = residual;
          tuned_constants = constants;
        }
        
        //  To the next iteration...
        break;
      }
      else{
        //  Modification's too weak - let's try again
        constants = previous_constants;
      }
      
    } //  while
    
    if (params.doCooling){
      Temperature = params.initialTemperature/log(i + 1);
    }
  } //  for
  
  //  To erase "in progress"  message
  cout << "\r";
  
  return  tuned_constants;
} //  Simulation::tuneConstants
