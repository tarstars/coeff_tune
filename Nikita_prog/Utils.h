#ifndef UTILS_H
#define UTILS_H

class Ntensor4;
class Ntensor3;
class Nmatrix;
class Nvector;

Ntensor4 makeElasticTensor36(double mat []);
Ntensor4 makeElasticTensor8(double c11,double c12,double c13,double c14,double c22,double c23,double c33,double c44);

Ntensor3 makePiezoTensor18(double mat []);
Ntensor3 makePiezoTensor5(double e15,double e22,double e31,double e32,double e33);

Nmatrix makePermitTensor6(double mat []);
Nmatrix makePermitTensor2(double eo,double ee);

Nvector makeDirection3D(double n1,double n2,double n3);
Nvector makeDirection3S(double rho,double phi, double theta);

Nvector solve3(double a,double b,double c);
Nvector eigval3(Nmatrix mat);




#endif