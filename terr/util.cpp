#include "util.h"
#include "piezo_tensor.h"
#include "material_tensor.h"
#include "matrix3.h"
#include "vector3.h"

int magic[3][3] = {{0, 5, 4},
		   {5, 1, 3},
		   {4, 3, 2}};

PiezoTensor 
makePiezoTensor(double e15, double e22, double e31, double e33){
  PiezoTensor ret;
  double ptc[3][6] = {{0, 0, 0, 0, e15, -e22}, 
		      {-e22, e22, 0, e15, 0, 0}, 
		      {e31, e31, e33, 0, 0, 0}};
  
  for(int p=0; p<3; ++p)
    for(int q=0; q<3; ++q)
      for(int r=0; r<3; ++r)
	ret(p, q, r) = ptc[p][magic[q][r]];
  
  return ret;
}

MaterialTensor 
makeMaterialTensor(double c11, double c12, double c13, double c14, double c33, double c44, double c66){
  MaterialTensor ret;
  double mtc[6][6] = {{c11, c12, c13, c14, 0, 0}, 
		      {c12, c11, c13, -c14, 0, 0}, 
		      {c13, c13, c33, 0, 0, 0},
		      {c14, -c14, 0, c44, 0, 0}, 
		      {0, 0, 0, 0, c44, c14}, 
		      {0, 0, 0, 0, c14, c66}};

  for(int p=0; p<3; ++p)
    for(int q=0; q<3; ++q)
      for(int r=0; r<3; ++r)
	for(int s=0; s<3; ++s)
	  ret(p, q, r, s) = mtc[magic[p][q]][magic[r][s]];
  
  return ret;
}

Matrix3 
makeEpsilonTensor(double eps11, double eps33){
  Matrix3 ret;
  double epstc[3][3] = {{eps11, 0, 0}, 
			{0, eps11, 0}, 
			{0, 0, eps33}};

  for(int p=0; p<3; ++p)
    for(int q=0; q<3; ++q)
      ret(p, q) = epstc[p][q];
  
  return ret;
}

Vector3 
makeWaveVector(double x, double y, double z){
  Vector3 ret;
  double wv[3] ={x, y, z};

  for(int p=0; p<3; ++p)
    ret(p) = wv[p];
  
  return ret;
}

Matrix3
makePiezoChristoffel(const MaterialTensor& mtens, const PiezoTensor& ptens, const Matrix3& etens, const Vector3& n){
  Matrix3 ret;
  return ret;
}

