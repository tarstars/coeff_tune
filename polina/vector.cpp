#include <iostream>

#include "vector.h"

using namespace std;

Vector3::Vector3(){
}

Vector3::Vector3(double a, double b, double c){
    r[0] = a;
    r[1] = b;
    r[2] = c;
}

ostream& operator<<(ostream& os, const Vector3& r) {
    for(int i=0; i < 3; i++)
        os << r(i) << " ";

    return os;
}
