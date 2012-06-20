#include "util.h"
#include "piezo_tensor.h"
#include "material_tensor.h"
#include "matrix.h"
#include "vector.h"

int jum(int p, int q) {
  int ind [3][3]={
    {0,5,4},
    {5,1,3},
    {4,3,2}
  };

  return ind [p][q];
}

PiezoTensor 
make_piezo_tensor(double e15,
		  double e22,
		  double e31,
		  double e33) {
  PiezoTensor ret;
  double el_p_c [3][6]={
    {   0,   0,   0,   0, e15, -e22},
    {-e22, e22,   0, e15,   0,    0},
    { e31, e31, e33,   0,   0,    0}};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
	ret(i,j,k) = el_p_c [i][jum(j,k)];
      }
    }
  }

  return ret;
}

MaterialTensor
make_material_tensor(double c11,
		     double c12,
		     double c13,
		     double c33,
		     double c14,
		     double c44,
		     double c66) {
  MaterialTensor ret;
  double el_c [6][6]={
    {c11, c12, c13, c14,   0,   0},
    {c12, c11, c13,-c14,   0,   0},
    {c13, c13, c33,   0,   0,   0},
    {c14,-c14,   0, c44,   0,   0},
    {  0,   0,   0,   0, c44, c14},
    {  0,   0,   0,   0, c14, c66}};
    
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
	for (int l = 0; l < 3; l++) {
	  ret(i,j,k,l) = el_c [jum(i,j)][jum(k,l)];
	}
      }
    }
  }
    
  return ret;
}


Matrix3 make_permit (double e_xx, double e_zz) {
  Matrix3 ret;
	
  ret(0,0)=e_xx; ret(0,1)=0;	   ret(0,2)=0;
  ret(1,0)=0;    ret(1,1)= e_xx;   ret(1,2)=0;
  ret(2,0)=0;	   ret(2,1)=0;	   ret(2,2)=e_zz;
	
  return ret;
}

Matrix3 make_christ (const Vector3& n,
		     const PiezoTensor& pt,
		     const MaterialTensor& mt,
		     const Matrix3& eps) {
  Matrix3 ret;

  
  return ret;
}
