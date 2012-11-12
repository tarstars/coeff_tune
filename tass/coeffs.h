#ifndef COEFFS
#define COEFFS

#include <iostream>
#include "types.h"

class Coeffs {
  double c11, c12, c13, c14, c33, c44, c66;
  double e15, e22, e31, e33;
  double exxc, ezzc;

  const double& at(int)const;
  double& at(int);
  int coeffNum()const;

 public:
  Coeffs();
  void vary(double);
  double residual(const VNVels&);
  void pprint(std::ostream&)const;
  void truncate();

  friend std::ostream& operator<<(std::ostream&, const Coeffs&);
};

std::ostream& operator<<(std::ostream&, const Coeffs& r);

#endif
