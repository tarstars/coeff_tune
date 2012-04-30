#include "poly3.h"

Poly3::Poly3(double c3, double c2, double c1, double c0){
  coeff[3] = c3;
  coeff[2] = c2;
  coeff[1] = c1;
  coeff[0] = c0;
}

std::ostream& 
operator<<(std::ostream& os, const Poly3& r){
  for(int t = 3; t >= 0; --t)
    os << r.coeff[t] << " ";
  return os;
}

