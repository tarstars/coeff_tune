#include <cmath>
#include <iostream>

#include "vec3.h"

using namespace std;

ostream& 
operator<<(ostream& os, const Vec3& r){
  for(int p = 0; p < 3; ++p)
    os << r[p] << " ";

  return os;
}

pair<double, double>
Vec3::thetaPhi() const {
  pair<double, double> ret;

  ret.first = acos(z) / M_PI * 180;
  ret.second = atan2(y, x) / M_PI * 180;

  return ret;
}
