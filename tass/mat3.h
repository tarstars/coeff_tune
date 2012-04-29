#ifndef MAT3
#define MAT3

class Mat3{
  double dat[3][3];
 public:

  double& operator()(int p, int q){return dat[p][q];}
  const double& operator()(int p, int q)const{return dat[p][q];}
  
  friend std::ostream& operator<<(std::ostream& os, const Mat3&);
};

std::ostream& operator<<(std::ostream& os, const Mat3&);

#endif
