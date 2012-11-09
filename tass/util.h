#ifndef UTIL
#define UTIL

#include "types.h"

class PiezoTensor;
class MaterialTensor;
class Mat3;
class Vec3;

PiezoTensor makePiezoTensor(double e15, double e22, double e31, double e33);
MaterialTensor makeMaterialTensor(double c11,
				  double c12,
				  double c13,
				  double c14,
				  double c33,
				  double c44,
				  double c66);

Mat3 makePiezoChristoffel(const PiezoTensor&, 
			  const MaterialTensor&, 
			  const Vec3&,
			  double, 
			  double);


VNVels readFiles(std::string flnm1, std::string flnm2, std::string flnm3);
double residual(const VNVels& vnv);

#endif
