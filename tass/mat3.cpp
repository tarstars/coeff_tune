#include <iostream>

#include "mat3.h"
#include "poly3.h"

using namespace std;

Poly3
Mat3::getPoly()const{
  const Mat3& a = *this;
  return Poly3(1,
	       -a(0,0) - a(1,1) - a(2,2),
	       a(1,1) * a(2,2) - a(1,2) * a(2,1) + a(0,0) * a(2,2) - a(0,2) * a(2,0) + a(0,0)*a(1,1) - a(0,1) * a(1,0), 
	       -(a(0,0) * (a(1,1) * a(2,2) - a(2,1) * a(1,2)) - a(0,1) * (a(1,0) * a(2,2) - a(1,2) * a(2,0)) + a(0,2) * (a(1,0) * a(2,1) - a(1,1) * a(2,0)))
	       );
}

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
