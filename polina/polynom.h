#ifndef POLYNOM
#define POLYNOM

#include <iostream>

class Poly3{
  double dat[3];
 public:
  Poly3();

  double& operator()(int p){return dat[p];}
  const double& operator()(int p)const {return dat[p];}

  friend std::ostream& operator<<(std::ostream&, const Poly3&);
};

std::ostream& operator<<(std::ostream&, const Poly3&);

#endif
