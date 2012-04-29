#include <iostream>

#include "mat3.h"
#include "material_tensor.h"
#include "piezo_tensor.h"
#include "util.h"
#include "vec3.h"

using namespace std;

int main(){
  PiezoTensor pt = makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  MaterialTensor mt = makeMaterialTensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);

  //double rho = 4642.8;
  double eps0 = 8.8542e-12;
  double exx = eps0 * 44.9;
  double ezz = eps0 * 26.7;


  Vec3 n(0, 0, 1);

  Mat3 christ = makePiezoChristoffel(pt, mt, n, exx, ezz);

  cout << "piezo tensor: " << pt << endl;
  cout << "materian tensor: " << mt << endl;
  cout << "christoffel matrix: " << christ << endl;
}
