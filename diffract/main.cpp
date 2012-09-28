#include <algorithm>
#include <complex>
#include <fstream>
#include <iostream>
#include <vector>

#include "fftw3.h"

using namespace std;

class Matrix {
  int h, w;
  fftw_complex *pDat;

  Matrix(const Matrix&);
  Matrix& operator=(const Matrix&);
public:
  Matrix() : h(0), w(0), pDat(0) {}
  Matrix(int hh, int ww) : h(hh), w(ww) {
    pDat = (fftw_complex*) fftw_malloc(hh * ww * sizeof(fftw_complex));
  }
  ~Matrix() {fftw_free(pDat);}

  complex<double>& operator()(int p, int q) {
    return (complex<double>&)pDat[p * w + q];
  }

  void shift_dz(double dz, double A, double lambda);
  void saveAsPic(string);

  friend class Plan;
};

void 
Matrix::saveAsPic(string flnm) {
  vector<double> modules(h * w);

  for(int p = 0; p < h; ++p)
    for(int q = 0; q < h; ++q)
      modules[p * w + q] = abs((*this)(p,q));

  double minval = *min_element(modules.begin(), modules.end());
  double maxval = *max_element(modules.begin(), modules.end());
  
  for(int t = 0; t < (int)modules.size(); ++t)
    modules[t] = 255 * sqrt((modules[t] - minval) / (maxval - minval));

  ofstream dest(flnm.c_str());
  dest << "P2" << endl;
  dest << "# " << flnm << endl;
  dest << w << " " << h << endl;
  dest << 256 << endl;
  for(int p = 0; p < h; ++p) {
    for(int q = 0; q < w; ++q) {
      dest << int(modules[p * w + q]) << " ";
    }
    dest << endl;
  }
}

int i2ik(int ind, int n) {
  if (2 * ind < n)
    return ind;
  return ind - n;
}

void
Matrix::shift_dz(double dz, double A, double lambda) {
  double dk = 2 * M_PI / A;
  double k = 2 * M_PI / lambda;

  for(int p = 0; p < h; ++p) {
    for(int q = 0; q < w; ++q) {
      double kx = dk * i2ik(q, w);
      double ky = dk * i2ik(p, h);
      double kz = sqrt(k * k - (kx * kx + ky * ky));

      (*this)(p, q) *= exp(complex<double>(0, dz * kz));
    }
  }
}

class Plan {
  fftw_plan plan;

  Plan(const Plan&);
  Plan& operator=(const Plan&);
public:
  Plan(Matrix& in, Matrix& out, int dir, int flag) {
      plan = fftw_plan_dft_2d(in.h, in.w, in.pDat, out.pDat, dir, flag);
  }
  ~Plan(){
    fftw_destroy_plan(plan);
  }
  void execute()const {
    fftw_execute(plan);
  }
};

void rect(Matrix& dat, int x1, int y1, int x2, int y2, double val) {
  for(int p = y1; p <= y2; ++p)
    for(int q = x1; q <= x2; ++q)
      dat(p, q) = val;
}

int main() {
  int mx = 400, my = 400;

  Matrix zeroz(my, mx), zerozf(my, mx), shifted(my, mx);
  Plan forw(zeroz, zerozf, FFTW_FORWARD, FFTW_ESTIMATE);
  Plan bakw(zerozf, shifted, FFTW_BACKWARD, FFTW_ESTIMATE);

  rect(zeroz, 198, 100, 202, 300, 1);
  rect(zeroz, 210, 100, 214, 300, 1);
  zeroz.saveAsPic("a.pgm");

  forw.execute();
  zerozf.shift_dz(20.1, 1, 0.5e-4); 
  bakw.execute();

  shifted.saveAsPic("b.pgm");
}
