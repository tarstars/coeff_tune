#include "piezo_tensor.h"

//e32 added, e22 replaced by e21
PiezoTensor makePiezoTensor(double e15, double e21, double e31, double e33, double e32){
  PiezoTensor ret;
	
  int i, j,k;

 
  double pmat[3][6] = {{0,    0,    0,    0,   e15,   -e21},
		       {-e21,  e21,    0,  e15,     0,      0},
		       {e31,  e32,  e33,    0,     0,      0}};

  int m[3][3] = {{0, 5, 4},
		 {5, 1, 3},
		 {4, 3, 2}};

 for (i=0; i<3;i++){
	for(j=0; j<3; j++){
		for(k=0; k<3; k++){
		  ret(i, j, k)=pmat[i][ m[j][k] ];
		}
	}
  }

  return ret;
}
