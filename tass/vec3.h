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
  Vec3 operator-(const Vec3& r)const{return Vec3(x - r.x, y - r.y, z - r.z);}
  double norm()const {return x * x + y * y + z * z;}
  std::pair<double, double> thetaPhi()const;

  friend std::ostream& operator<<(std::ostream&, const Vec3&);
};

std::ostream& operator<<(std::ostream&, const Vec3&);

#endif
