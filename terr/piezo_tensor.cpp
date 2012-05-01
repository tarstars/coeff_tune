#include <iostream>

#include "piezo_tensor.h"

using namespace std;

PiezoTensor::PiezoTensor(){

}

std::ostream& operator<<(std::ostream& os, const PiezoTensor& ptens){
  for(int r = 0; r < 3; ++r){
    for(int p = 0; p < 3; ++p){
      for(int q = 0; q < 3; ++q){
	os << ptens(p, q, r) << "\t";
      }
      os << endl;
    }
    os << endl;
  }
  return os;
}
