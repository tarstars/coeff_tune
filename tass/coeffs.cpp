#include <cstdlib>

#include "coeffs.h"

using namespace std;

Coeffs::Coeffs() : c11(10), c12(10), c13(10), c14(10), c33(10),
		   c44(10), c66(10), e15(10), e22(10), e31(10), 
		   e33(10) {
  
}

int
Coeffs::coeffNum() {return 11;}

double&
Coeffs::at(int ind) {
  double *pEl[] = {&c11, &c12, &c13, &c14, &c33, &c44, &c66,
		   &e15, &e22, &e31, &e33};
  return *(pEl[ind]);
}

void
Coeffs::vary(double kt) {
  double partToVary = 0.01;

  for(int t = 0; t < coeffNum(); ++t) {
    double rv = double(rand()) / RAND_MAX;
    rv = 2 * (rv - 0.5);
    at(t) *= (1 + partToVary * rv);
  }
}

double
Coeffs::residual(const VNVels&) {
  double ret = 0; 

  for(int t = 0; t < coeffNum(); ++t) {
    double x = 10 + 2 * t;
    double dx = x - at[t];
    ret += dx * dx;
  }

  return ret;
}

std::ostream& 
operator<<(std::ostream& os, const Coeffs& r) {

  return os;
}
