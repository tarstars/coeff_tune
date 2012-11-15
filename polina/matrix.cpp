#include <iostream>

#include "matrix.h"
#include "polynom.h"

using namespace std;

Matrix3::Matrix3(){}

Poly3 Matrix3::getCharPoly()const{
  const Matrix3& m = *this;
  Poly3 ret(-1,  
	    + m(0,0) + m(1,1) + m(2,2), 
	    - m(0,0)*m(1,1) - m(0,0)*m(2,2) - m(1,1)*m(2,2) + m(0,1)*m(1,0) + m(0,2)*m(2,0) + m(1,2)*m(2,1), 
        - m(0,0)*m(1,2)*m(2,1) - m(1,1)*m(0,2)*m(2,0) - m(2,2)*m(0,1)*m(1,0)
	    + m(0,1)*m(1,2)*m(2,0) + m(0,2)*m(2,1)*m(1,0) + m(0,0)*m(1,1)*m(2,2));
  
  return ret;
}


std::ostream& operator<<(std::ostream& os, const Matrix3& mrx3)
{
  for(int p = 0; p < 3; ++p){
    for(int q = 0; q < 3; ++q){
      os << mrx3(p, q) << "\t";
    }
    os << endl;
  }
  return os;
}
