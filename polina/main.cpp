#include <iostream>

#include "piezo_tensor.h"
#include "material_tensor.h"
#include "matrix.h"
#include "util.h"

#include <conio.h>
#include <cmath>
#include <iostream>

using namespace std;

void coeff_tune() {

  PiezoTensor pt = make_piezo_tensor(3.655, 2.407, 0.328, 1.894);

  MaterialTensor mt = make_material_tensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);

  Matrix3 eps = make_permit(44.9, 26.7);

  double rho = 4642.8;

  Vector3 n = (0,0,1);

  // Matrix3 christ = make_christ(n,pt,mt,eps);

  // Pol3 charact = make_character(christ);

  // double r1, r2, r3;

  // charact.all_roots(r1,r2,r3);

  // double V1 = sqrt(r1/rho); 
}

int main() {
  
  coeff_tune();
  
  getch();

  return 0;
}
