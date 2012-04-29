#ifndef VEC3
#define VEC3

#include <iostream>

class Vec3{
  double x, y, z;
 public:

 Vec3():x(0), y(0), z(0){}
 Vec3(double xx, double yy, double zz):x(xx), y(yy), z(zz){}

  double& operator[](int ind){double* ret[]={&x, &y, &z}; return *ret[ind];}
  const double& operator[](int ind)const{const double* ret[]={&x, &y, &z}; return *ret[ind];}

  friend std::ostream& operator<<(std::ostream&, const Vec3&);
};

std::ostream& operator<<(std::ostream&, const Vec3&);

#endif
