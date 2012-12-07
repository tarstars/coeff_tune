#ifndef POLY
#define POLY

#include <vector>

class Poly {
  int deg;
  std::vector<double> dat;
 public:
 Poly(double a0, double a1) : deg(1), dat(2) {
    dat[0] = a0;
    dat[1] = a1;
  }
 Poly(double a0, double a1, double a2) : deg(2), dat(3) {
    dat[0] = a0;
    dat[1] = a1;
    dat[2] = a2;
  }

  int degree() const {return deg;}

  std::vector<double> solve() const;
};

#endif
