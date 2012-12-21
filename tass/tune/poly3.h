#ifndef POLY3
#define POLY3

#include <iostream>

class Poly3 {
  double coeff[4];
 public:

  Poly3(double c3, double c2, double c1, double c0);
  void solve(double* g1, double* g2, double * g3)const;

  friend std::ostream& operator<<(std::ostream&, const Poly3&);
};

std::ostream& operator<<(std::ostream&, const Poly3&);

#endif
