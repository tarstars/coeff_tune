#include <iostream>

#include "mat3.h"

using namespace std;

ostream&
operator<<(ostream& os, const Mat3& r){
  for(int p = 0; p < 3; ++p){
    for(int q = 0; q < 3; ++q){
      os << r(p,q) << " ";
    }
    os << endl;
  }

  return os;
}
