#ifndef UTIL
#define UTIL

class PiezoTensor;
class MaterialTensor;
class Matrix3;
class Vector3;

PiezoTensor 
makePiezoTensor(double e15, double e22, double e31, double e33);

MaterialTensor 
makeMaterialTensor(double c11, double c12, double c13, double c14, double c33, double c44, double c66);

Matrix3
makeEpsilonTensor(double eps11, double eps33);

Vector3
makeWaveVector(double x, double y, double z);

Matrix3
makePiezoChristoffel(const MaterialTensor&, const PiezoTensor&, const Matrix3&, const Vector3&);

#endif
