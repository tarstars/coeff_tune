#ifndef __SA_ACOP__SIMULATION__
#define __SA_ACOP__SIMULATION__

#include <iostream>

#include <gsl/gsl_rng.h>

using ::std::ostream;

struct  Constants{
  double  a, b, c, d;
  
  friend  ostream&  operator<<(ostream& os, const Constants& constants);
};

struct  AnnealingParams{
  int iterationsNumber;
  double  initialTemperature;
  bool  doCooling;
};

class Simulation{
  private:
    AnnealingParams params;
    Constants true_constants;
    gsl_rng *generator;
    
    double  cubicPolynomial(double x, Constants coeff);
    double  calculateResidual(Constants constants);
    
    inline  double  randomUniform(double min, double max);
    inline  double  randomGaussian(double dispersion);
    
    Constants randomizeConstants(Constants, double dispersion);
  
  public:
    ~Simulation();
    
    void  initializeRandomGenerator();
    void  freeRandomGenerator();
    void  setTrueConstants(Constants true_constants);
//    void  setParams(SimAnnealingParams params);
    
    Constants tuneConstants(Constants constants, AnnealingParams params);
};

#endif  //  __SA_ACOP__SIMULATION__
