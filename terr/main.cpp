#include <iostream>

#include "piezo_tensor.h"
#include "material_tensor.h"
#include "util.h"

using namespace std;

int main()
{
  PiezoTensor pt=makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  MaterialTensor mt = makeTrigonalMaterialTensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);
  cout << pt << endl;
  cout << mt << endl;
}
