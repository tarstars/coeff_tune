#ifndef UTIL
#define UTIL

class PiezoTensor;
class MaterialTensor;

PiezoTensor 
makePiezoTensor(double e15, double e22, double e31, double e33);

MaterialTensor 
makeTrigonalMaterialTensor(double c11, double c12, double c13, double c14, double c33, double c44, double c66);

double 
makeEpsilonTensor(double eps11, double eps33);

#endif
