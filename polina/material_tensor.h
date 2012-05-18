#ifndef MATERIAL_TENSOR
#define MATERIAL_TENSOR

#include <iostream>

class MaterialTensor{
  double dat[3][3][3][3];
 public:
  MaterialTensor();

  double& operator()(int p, int q, int r, int s){return dat[p][q][r][s];}
  const double& operator()(int p, int q, int r, int s)const{return dat[p][q][r][s];}

  friend std::ostream& operator<<(std::ostream&, const MaterialTensor&);
};

std::ostream& operator<<(std::ostream&, const MaterialTensor&);

#endif
