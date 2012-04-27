#include <iostream>

#include "piezo_tensor.h"
#include "util.h"

#include <cmath>
#include <iostream>

using namespace std;

void coeff_tune() {

  PiezoTensor pt = make_piezo_tensor();

  MaterialTensor mt = make_material_tensor();

  Matrix3 eps = make_permit();

  double rho = ;

  Vector3 n = (0,0,1);

  Matrix3 christ = make_christ(n,pt,mt,eps);

  Pol3 charact = make_character(christ);

  double r1, r2, r3;

  charact.all_roots(r1,r2,r3);

  double V1 = sqrt(r1/rho); 
}

int main() {
  
  coeff_tune();
  
  getch();

  return 0;
}
 
