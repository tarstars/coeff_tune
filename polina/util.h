#ifndef UTIL
#define UTIL

#include "type.h"

class PiezoTensor;
class MaterialTensor;
class Matrix3;
class Vector3;

PiezoTensor make_piezo_tensor(double e15, double e22, double e31, double e33);

MaterialTensor make_material_tensor(double c11, double c12, double c13, double c14, double c33, double c44, double c66);

Matrix3 make_permit(double e_xx, double e_zz);

Matrix3 make_christ(const Vector3& n, const PiezoTensor& pt, const MaterialTensor& mt, const Matrix3& eps);

Vector3 make_vector();

VNVels readFiles(std::string flnm1, std::string flnm2, std::string flnm3);

#endif
