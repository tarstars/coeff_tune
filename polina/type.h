#ifndef TYPE_H
#define TYPE_H

#include <vector>

#include "vector.h"

typedef std::pair<Vector3, Vector3> NVels; //first = n, second = v1, v2, v3
typedef std::vector<NVels> VNVels;

#endif // TYPE_H
