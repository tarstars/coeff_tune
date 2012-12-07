#include <cmath>
#include <iostream>

#include "coeffs.h"
#include "poly3.h"
#include "types.h"
#include "util.h"

#include "mat3.h"
#include "material_tensor.h"
#include "piezo_tensor.h"
#include "poly3.h"
#include "tests.h"
#include "util.h"
#include "vec3.h"


using namespace std;

void testReadFile() {
  VNVels vecs = readFiles("../linbo3_data/linbo3_sqs_0c_sw.txt",
			  "../linbo3_data/linbo3_ql_0c_sw.txt",
			  "../linbo3_data/linbo3_fqs_0c_sw.txt"
			  );
  
  for(VNVels::iterator it = vecs.begin(); it != vecs.end(); ++it) {
    cout << "vect = " << it->first << " " << it->second << endl;
  }
}

void testPolynome() {
  double g1, g2, g3;
  Poly3(1, -11, 31, -21).solve(&g1, &g2, &g3);
  cout << "g1 g2 g3 = " << g1 << " " << g2 << " " << g3 << endl;
}

void work() {
  PiezoTensor pt = makePiezoTensor(3.655, 2.407, 0.328, 1.894);
  MaterialTensor mt = makeMaterialTensor(19.886e10, 5.467e10, 6.799e10, 0.783e10, 23.418e10, 5.985e10, 7.209e10);

  double rho = 4642.8;
  double eps0 = 8.8542e-12;
  double exx = eps0 * 44.9;
  double ezz = eps0 * 26.7;

  Vec3 n(0, 0, 1);

  Mat3 christ = makePiezoChristoffel(pt, mt, n, exx, ezz);
  Poly3 christPoly = christ.getPoly();
  
  double g1, g2, g3;
  christPoly.solve(&g1, &g2, &g3);
  double v1 = sqrt(g1 / rho);
  double v2 = sqrt(g2 / rho);
  double v3 = sqrt(g3 / rho);

  cout << "piezo tensor: " << endl << pt << endl;
  cout << "material tensor: " << endl << mt << endl;
  cout << "christoffel matrix: " << endl << christ << endl;
  cout << "polynome " << christPoly << endl;
  cout << "velocities = " << v1 << " " << v2 << " " << v3 << endl;
}

void
testResidual() {
  VNVels vecs = readFiles("../linbo3_data/linbo3_sqs_0c_sw.txt",
			  "../linbo3_data/linbo3_ql_0c_sw.txt",
			  "../linbo3_data/linbo3_fqs_0c_sw.txt"
			  );

  Coeffs dat;
  cout << "coeffs: " << dat << endl;
  dat.pprint(cout);
  cout << endl;
  

  cout << dat.residual(vecs) << endl;
}

void
testAnneal() {
  //anneal();
  anneal().pprint(cout);
  cout << endl;
}

void
testCoeffs() {
  Coeffs dat;
  dat.vary(0);

  cout << "line: " << dat << endl;
  dat.pprint(cout);
  cout << endl;
}
