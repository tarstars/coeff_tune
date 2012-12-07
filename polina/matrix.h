#ifndef MATRIX3
#define MATRIX3

#include <iostream>

class Poly3;

class Matrix3{
  double dat[3][3];
 public:
  Matrix3();

  Poly3 getCharPoly()const;

  double& operator()(int p, int q){return dat[p][q];}
  const double& operator()(int p, int q)const {return dat[p][q];}

  friend std::ostream& operator<<(std::ostream&, const Matrix3&);
};

std::ostream& operator<<(std::ostream&, const Matrix3&);

#endif
