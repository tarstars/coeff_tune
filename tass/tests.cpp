#include <iostream>

#include "poly3.h"
#include "types.h"
#include "util.h"

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


void
testResidual() {
  VNVels vecs = readFiles("../linbo3_data/linbo3_sqs_0c_sw.txt",
			  "../linbo3_data/linbo3_ql_0c_sw.txt",
			  "../linbo3_data/linbo3_fqs_0c_sw.txt"
			  );
  cout << residual(vecs) << endl;
}
