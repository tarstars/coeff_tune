#ifndef UTIL
#define UTIL

class PiezoTensor;
class MaterialTensor;
class Matrix3;
class Vector3;

PiezoTensor 
makePiezoTensor(const double*);

MaterialTensor 
makeMaterialTensor(const double*);

Matrix3
makeEpsilonTensor(const double*);

Vector3
makeWaveVector(double x, double y, double z);

Matrix3
makePiezoChristoffel(const MaterialTensor&, const PiezoTensor&, const Matrix3&, const Vector3&);

#endif
