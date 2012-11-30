#include <cmath>

#include "poly3.h"

using namespace std;

Poly3::Poly3(double c3, double c2, double c1, double c0){
  coeff[3] = c3;
  coeff[2] = c2;
  coeff[1] = c1;
  coeff[0] = c0;
}

void 
Poly3::solve(double *pg1, double *pg2, double *pg3)const{
  double a = coeff[2] / coeff[3];
  double b = coeff[1] / coeff[3];
  double c = coeff[0] / coeff[3];

  double p = b - a * a / 3;
  double q = 2 * a * a * a / 27 - a * b / 3 + c;

  if (p > 0)
    throw(string("no real roots"));

  double A = sqrt(- 4 * p / 3); 

  //cout << "\t\tA = " << A << endl;

  double c3phi = - 4 * q / (A * A * A);

  if (abs(c3phi) > 1)
    throw(string("no real roots"));

  double phi = acos(c3phi) / 3;
  
  *pg1 = A * cos(phi) - a / 3;
  *pg2 = A * cos(phi + 2 * M_PI / 3) - a / 3;
  *pg3 = A * cos(phi - 2 * M_PI / 3) - a / 3;

  if (*pg1 < 0 || *pg2 < 0 || *pg3 < 0)
    throw(string("bad root"));
}

std::ostream& 
operator<<(std::ostream& os, const Poly3& r){
  for(int t = 3; t >= 0; --t)
    os << r.coeff[t] << " ";
  return os;
}

