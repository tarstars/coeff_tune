#ifndef POLY3
#define POLY3

#include <iostream>

class Poly3{
  double coef[4];
 public:
  Poly3();
  Poly3(double, double, double, double);

  double& operator()(int p){return coef[p];}
  const double& operator()(int p)const {return coef[p];}

  void solve(double*, double*, double*);

  friend std::ostream& operator<<(std::ostream&, const Poly3&);
};

std::ostream& operator<<(std::ostream&, const Poly3&);


#endif
