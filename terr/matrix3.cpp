#include <iostream>

#include "matrix3.h"

using namespace std;

Matrix3::Matrix3(){
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
