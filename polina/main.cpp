#include <iostream>
#include <fstream>

#include "piezo_tensor.h"
#include "material_tensor.h"
#include "vector.h"
#include "matrix.h"
#include "polynom.h"
#include "util.h"

#include <conio.h>
#include <cmath>
#include <iostream>

using namespace std;

void test_read_file() {
  ifstream sour("..\\linbo3_data\\linbo3_sqs_0c_sw.txt");

  if (!sour){
    cout << "problem!" << endl;
  }

  cout << "ok!" << endl;
}

void coeff_tune() {

  PiezoTensor pt = make_piezo_tensor(3.655, 2.407, 0.328, 1.894);

  MaterialTensor mt = make_material_tensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);

  Matrix3 eps = make_permit(44.9, 26.7);

  double rho = 4642.8;

  Vector3 n(1,0,0);

  Matrix3 christ = make_christ(n,pt,mt,eps);

  //cout << "pt = " << endl << pt << endl;
  //cout << "mt = " << endl << mt << endl;
  //cout << "eps = " << endl << eps << endl;

  Poly3 charact = christ.getCharPoly();

  //Poly3 charact(1,-14,59,-70);

  cout << charact << endl;

  double r1, r2, r3;

  charact.solve(&r1, &r2, &r3);

  double V1 = sqrt(r1/rho);
  double V2 = sqrt(r2/rho);
  double V3 = sqrt(r3/rho);

  cout << r1 << " " << r2 << " " << r3 << endl;

  cout << V1 << " " << V2 << " " << V3 << endl;
}

int main() {
  
  //test_read_file();

  coeff_tune();
  
  getch();

  return 0;
}
