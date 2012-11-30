#include <iostream>

#include "vector3.h"

using namespace std;

Vector3::Vector3(){
}

std::ostream& operator<<(std::ostream& os, const Vector3& v3)
{
  for(int p = 0; p < 3; ++p){
      os << v3(p) << " ";
  }
  // os << endl;
  return os;
}
