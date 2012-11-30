#include <iostream>

#include "material_tensor.h"

using namespace std;

MaterialTensor::MaterialTensor(){}

std::ostream& operator<<(std::ostream& os, const MaterialTensor& mtens)
{
    for(int p = 0; p < 3; ++p){
        os << "----------------------------------" << endl;
        for(int q = 0; q < 3; ++q){
            for(int r = 0; r < 3; ++r){
                for(int s = 0; s < 3; ++s){
                    os << mtens(p, q, r, s) << "\t";
                }
                os << endl;
            }
            os << endl;
        }
    }
    return os;
}
