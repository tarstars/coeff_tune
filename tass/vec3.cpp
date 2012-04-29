#include <iostream>

#include "vec3.h"

using namespace std;

ostream& 
operator<<(ostream& os, const Vec3& r){
  for(int p = 0; p < 3; ++p)
    os << r[p] << " ";

  return os;
}
