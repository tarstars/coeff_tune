#pragma once
#ifndef UT
#define UT

#include "piezo_tensor.h"

//e32 added, e22 replaced by e21
PiezoTensor makePiezoTensor(double e15, double e21, double e31, double e33, double e32);




#endif
