#include "material_tensor.h"

#include <iostream>

using namespace std;

MaterialTensor::MaterialTensor(){

}

std::ostream& operator<<(std::ostream& os, const MaterialTensor& ptens){
  for(int p = 0; p < 3; ++p){
    for(int q = 0; q < 3; ++q){
      for(int r = 0; r < 3; ++r){
	for(int s = 0; s < 3; ++s){
	  os << ptens(p, q, r, s) << " ";
	}
	os << "\t";
      }
      os << endl;
    }
    os << endl;
  }
  return os;
}
