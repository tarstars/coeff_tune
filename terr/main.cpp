#include <iostream>

#include "piezo_tensor.h"
#include "util.h"

using namespace std;

int main(){
  PiezoTensor pt=makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  cout << pt << endl;
}
