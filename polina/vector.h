#ifndef VECTOR
#define VECTOR

#include <iostream>

class Vector3{
  double r [3];
 public:
  Vector3();
  Vector3(double, double, double);

  double& operator()(int p){return r[p];}
  const double& operator()(int p)const {return r[p];}

  friend std::ostream& operator<<(std::ostream&, const Vector3&);
};

std::ostream& operator<<(std::ostream&, const Vector3&);

#endif
