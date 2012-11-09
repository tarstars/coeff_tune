#ifndef UTIL
#define UTIL
#include <vector>

class PiezoTensor;
class MaterialTensor;
class Matrix3;
class Vector3;

PiezoTensor makePiezoTensor(const std::vector<double>&);
MaterialTensor makeMaterialTensor(const std::vector<double>&);
Matrix3 makeEpsilonTensor(const std::vector<double>&);
Vector3 makeWaveVector(double x, double y, double z);
Matrix3 makePiezoChristoffel(const MaterialTensor&, const PiezoTensor&, const Matrix3&, const Vector3&);

std::pair<int, int> pickCoeff();

#endif
