#include <iostream>
#include <cmath>

#include "poly3.h"

using namespace std;

Poly3::Poly3(){
}

Poly3::Poly3(double c3, double c2, double c1, double c0){
  coef[3] = c3;
  coef[2] = c2;
  coef[1] = c1;
  coef[0] = c0;
}

void Poly3::solve(double *rp1, double *rp2, double *rp3){
  double a = coef[2] / coef[3];
  double b = coef[1] / coef[3];
  double c = coef[0] / coef[3];

  // x*x*x + a * x * x + b * x  + c == 0
  double p = b - a * a / 3;
  double q = 2 * a * a * a / 27 - a * b / 3 + c;
  double A = sqrt(- 4 * p / 3); 
 
  double c3phi = - 4 * q / (A * A * A);
 
  double phi = acos(c3phi) / 3;  
 
  double root1 = A * cos(phi) - a / 3;
  double root2 = A * cos(phi + 2 * M_PI / 3) - a / 3;
  double root3 = A * cos(phi - 2 * M_PI / 3) - a / 3;

  *rp1 = root1;
  *rp2 = root2;
  *rp3 = root3;
}

std::ostream& operator<<(std::ostream& os, const Poly3& poly3)
{
  for(int p = 3; p >= 0; --p){
      os << poly3(p) << "\t";
    }
  return os;
}
