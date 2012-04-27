#ifndef PIEZO_TENSOR
#define PIEZO_TENSOR

#include <iostream>

class PiezoTensor{
  double dat[3][3][3];
 public:
  PiezoTensor();

  double& operator()(int p, int q, int r){return dat[p][q][r];}
  const double& operator()(int p, int q, int r)const {return dat[p][q][r];}

  friend std::ostream& operator<<(std::ostream&, const PiezoTensor&);
};

std::ostream& operator<<(std::ostream&, const PiezoTensor&);


#endif
