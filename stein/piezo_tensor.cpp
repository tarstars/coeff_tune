#include "piezo_tensor.h"

PiezoTensor::PiezoTensor(){

}

ostream& 
operator<<(ostream& os, const PiezoTensor& ptens){
  for(int p = 0; p < 3; ++p){
    for(int q = 0; q < 3; ++q){
      for(int r = 0; r < 3; ++r)
	os << ptens(p, q, r) << " ";
      os << endl;
    }
    os << endl;
  }

  return os;
}

