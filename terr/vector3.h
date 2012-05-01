#ifndef VECTOR3
#define VECTOR3

#include <iostream>

class Vector3{
  double dat[3];
 public:
  Vector3();

  double& operator()(int p){return dat[p];}
  const double& operator()(int p)const {return dat[p];}

  friend std::ostream& operator<<(std::ostream&, const Vector3&);
};

std::ostream& operator<<(std::ostream&, const Vector3&);


#endif
