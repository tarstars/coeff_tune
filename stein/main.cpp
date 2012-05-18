#include <iostream>

#include "piezo_tensor.h"
#include "utility.h"

using namespace std;



int main(){
  PiezoTensor a=makePiezoTensor(3.655, 2.407, 0.328, 1.894, 2.783);
  cout << a << endl;
  //a.show();
}
