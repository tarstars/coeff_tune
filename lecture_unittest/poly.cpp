#include <cmath>

#include "poly.h"

using namespace std;

vector<double> 
Poly::solve() const {
  vector<double> ret;

  switch(deg) {
  case 1: 
    if (abs(dat[1]) > 1e-10)
      ret.push_back(-dat[0] / dat[1]);
    break;
  case 2:
    double a = dat[2];
    double b = dat[1];
    double c = dat[0];

    double D = (b * b - 4 * a * c);
    double x1 = (-b + sqrt(D)) / (2 * a);
    double x2 = (-b - sqrt(D)) / (2 * a);

    ret.push_back(x1);
    ret.push_back(x2);
    break;
  }
  return ret;
}
