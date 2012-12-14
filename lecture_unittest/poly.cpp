#include "poly.h"

using namespace std;

vector<double> 
Poly::solve() const {
  vector<double> ret;
  if (deg == 1) {
    ret.push_back(- dat[0] / dat[1]);
  }
  return ret;
}
