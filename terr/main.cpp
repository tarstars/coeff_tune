#include <iostream>

#include "piezo_tensor.h"
#include "material_tensor.h"
#include "matrix3.h"
#include "vector3.h"
#include "util.h"

using namespace std;

int main()
{
  PiezoTensor pt=makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  cout << "Piezo tensor:" << endl << pt << endl;

  MaterialTensor mt = makeMaterialTensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);
  cout << "Material tensor:" << endl << mt << endl;

  Matrix3 et = makeEpsilonTensor(44.9, 26.7);
  cout << "Epsilon tensor:" << endl << et <<endl;

  Vector3 n = makeWaveVector(0,0,1);
  cout << "Wave vector:" << endl << n <<endl;

  Matrix3 chr = makePiezoChristoffel(mt, pt, et, n);
  cout << "Christoffel matrix:" << endl << chr << endl;
}
