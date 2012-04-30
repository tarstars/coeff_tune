#include "util.h"
#include "piezo_tensor.h"
#include "material_tensor.h"
#include "mat3.h"
#include "vec3.h"

PiezoTensor 
makePiezoTensor(double e15, double e21, double e31, double e33){
  double mat[][6]={
    {   0,   0,   0,   0,  e15,  -e21},
    {-e21, e21,   0, e15,    0,     0},
    { e31, e31, e33,   0,    0,     0}};
  
  int dict[3][3] = {
    {1, 6, 5},
    {6, 2, 4},
    {5, 4, 3}};

  PiezoTensor ret;

  for(int p = 0; p < 3; ++p)
    for(int q = 0; q < 3; ++q)
      for(int r = 0; r < 3; ++r)
	ret(p,q,r) = mat[p][dict[q][r] - 1]; 

  return ret;
}

MaterialTensor makeMaterialTensor(double c11,
				  double c12,
				  double c13,
				  double c14,
				  double c33,
				  double c44,
				  double c66) {
  MaterialTensor r;

  double arr[6][6] = {
    {c11,  c12, c13,  c14,   0,   0},
    {c12,  c11, c13, -c14,   0,   0}, 
    {c13,  c13, c33,    0,   0,   0},
    {c14, -c14,   0,  c44,   0,   0},
    {  0,    0,   0,    0, c44, c14},
    {  0,    0,   0,    0, c14, c66}};
  
  int dict[3][3] = {
    {1, 6, 5},
    {6, 2, 4},
    {5, 4, 3}};

  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      for(int k = 0; k < 3; ++k)
	for(int l = 0; l < 3; ++l){
	  int p = dict[i][j]; 
	  int q = dict[k][l];
		
	  r(i,j,k,l) = arr[p - 1][q - 1];
	}

  return r;
}

Mat3 
makePiezoChristoffel(const PiezoTensor& pt, 
		     const MaterialTensor& mt, 
		     const Vec3& n,
		     double exx, 
		     double ezz){
  Mat3 ret;

  for(int p = 0; p < 3; ++p)
    for(int q = 0; q < 3; ++q){
      ret(p,q) = 0;
      for(int r = 0; r < 3; ++r)
	for(int s = 0; s < 3; ++s)
	  ret(p, q) += mt(p, r, q, s) * n[r] * n[s];
    }

  return ret;
}
