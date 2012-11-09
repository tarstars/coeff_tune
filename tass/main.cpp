#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "mat3.h"
#include "material_tensor.h"
#include "piezo_tensor.h"
#include "poly3.h"
#include "tests.h"
#include "util.h"
#include "vec3.h"

using namespace std;

//D:\\arseniy\\2012\\c\\coeff_tune
//..\\linbo3_data\\linbo3_sqs_0c_sw.txt


int main() {
  //testPolynome();
  //work();
  //testReadFile();
  try {
    //testResidual();
    testAnneal();
  } catch (string msg) {
    cout << "error: " << msg << endl;
  }
}
