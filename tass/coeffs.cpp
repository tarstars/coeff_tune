#include <cmath>
#include <cstdlib>

#include "coeffs.h"
#include "piezo_tensor.h"
#include "material_tensor.h"
#include "mat3.h"
#include "poly3.h"
#include "util.h"
#include "vec3.h"

using namespace std;

/*
999777 1.64349
2.03685e+011 5.75795e+010 7.51035e+010 
8.52658e+009 2.42839e+011 5.97913e+010
7.3132e+010 3.87359 2.51145 0.289444
1.40349 47.0199 30.3427 
 */

Coeffs::Coeffs() : c11(19.886e10), c12(5.467e10),  c13(6.799e10),
		   c14(0.783e10),  c33(23.418e10), c44(5.985e10),
		   c66(7.209e10), e15(3.655), e22(2.407), e31(0.328), 
		   e33(1.894), exxc(44.9), ezzc(26.7) {
  
}

int
Coeffs::coeffNum() const{return 13;}

double&
Coeffs::at(int ind) {
  double *pEl[] = {&c11, &c12, &c13, &c14, &c33, &c44, &c66,
		   &e15, &e22, &e31, &e33, &exxc, &ezzc};
  return *(pEl[ind]);
}

const double&
Coeffs::at(int ind) const {
  const double *pEl[] = {&c11, &c12, &c13, &c14, &c33, &c44, &c66,
			 &e15, &e22, &e31, &e33, &exxc, &ezzc};
  return *(pEl[ind]);
}

void
Coeffs::vary(double kt) {
  double partToVary = 0.0001;// * pow(10, -kt);

  for(int t = 0; t < coeffNum(); ++t) {
    double rv = double(rand()) / RAND_MAX;
    rv = 2 * (rv - 0.5);
    at(t) *= (1 + partToVary * rv);
  }
}

double
Coeffs::residual(const VNVels& vnv) {
  double ret = 0; 

  // for(int t = 0; t < coeffNum(); ++t) {
  //   double x = 10 + 2 * t;
  //   double dx = x - at(t);
  //   ret += dx * dx;
  // }

  PiezoTensor pt = makePiezoTensor(e15, e22, e31, e33);
  MaterialTensor mt = makeMaterialTensor(c11, c12, c13, c14, c33, c44, c66);

  double rho = 4642.8;
  double eps0 = 8.8542e-12;
  double exx = eps0 * exxc;
  double ezz = eps0 * ezzc;
  
  for(VNVels::const_iterator it = vnv.begin(); it != vnv.end(); ++it) {
    Vec3 n(it -> first);

    Mat3 christ = makePiezoChristoffel(pt, mt, n, exx, ezz);
    Poly3 christPoly = christ.getPoly();
  
    double g1, g2, g3;
    christPoly.solve(&g1, &g2, &g3);
    double v1 = sqrt(g1 / rho);
    double v2 = sqrt(g2 / rho);
    double v3 = sqrt(g3 / rho);

    double maxv = max(max(v1, v2), v3);
    double minv = min(min(v1, v2), v3);
    double medv = v1 + v2 + v3 - maxv - minv;

    Vec3 tv(minv, medv, maxv);
    Vec3 ex = it -> second;

    double curResidual = (ex - tv).norm();
    ret += curResidual;
  }

  return ret/vnv.size();
}

std::ostream& 
operator<<(std::ostream& os, const Coeffs& r) {

  for(int t = 0; t < r.coeffNum(); ++t) {
    os << r.at(t) << " ";
  }

  return os;
}