#include <iostream>

#include "material_tensor.h"

using namespace std;

MaterialTensor::MaterialTensor(){}

std::ostream& operator<<(std::ostream& os, const MaterialTensor& mtens)
{
  for(int s = 0; s < 3; ++s){
    os << "----------------------------------" << endl;
    for(int r = 0; r < 3; ++r){
      for(int p = 0; p < 3; ++p){
	for(int q = 0; q < 3; ++q){
        os << mtens(p, q, r, s) << "\t";
	}
	os << endl;
      }
      os << endl;
    }
  }
  return os;
}
