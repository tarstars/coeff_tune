#include <iostream>

using namespace std;

class ExperimentalData;

class Coeffs {
public:
  double c11, c12;

  Coeffs() {
    c11 = 271;
    c12 = 100510;
  }

  double residual(const ExperimentalData& ed);
};


class ExperimentalData {
public:
  double a, b;
  ExperimentalData(double aa, double bb): a(aa), b(bb) {
  }
};

double 
Coeffs::residual(const ExperimentalData& ed) {
  double dx = ed.a - c11;
  double dy = ed.b - c12;
  
  return dx*dx + dy*dy;
}

Coeffs optimize(Coeffs start, ExperimentalData dat) {
  Coeffs ret;
  cout << "optimize" << endl;

  int iterCount;
  for(iterCount = 0; iterCount < 10000; ++iterCount) {
    double d1 = 0.001;
    double d2 = 0.001;

    Coeffs c1(ret);
    Coeffs c2(ret);

    c1.c11 += d1;
    c2.c12 += d2;

    double r1 = ret.residual(dat);
    double r2 = c1.residual(dat);
    double r3 = c2.residual(dat);

    double grad1 = (r2 - r1) / d1;
    double grad2 = (r3 - r1) / d2;

    cout << "grad1 = " << grad1 << endl;
    cout << "grad2 = " << grad2 << endl;

    ret.c11 -= grad1 * 0.001;
    ret.c12 -= grad2 * 0.001;

    cout << "res = " << r1 << endl;
  }

  return ret;
}

int main() {
  Coeffs x;
  ExperimentalData ed(513, 100500);

  cout << "x=" << x.c11 << " " << x.c12 << endl;
  cout << "r=" << x.residual(ed) << endl;

  Coeffs x1 = optimize(x, ed);
  cout << "optimum=" << x1.c11 << " " << x1.c12 << endl;
}
