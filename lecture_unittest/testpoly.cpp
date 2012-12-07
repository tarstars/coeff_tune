#include <algorithm>
#include <vector>
#include <cmath>

#include <QtTest/QtTest>

#include "poly.h"

using namespace std;


class TestPoly : public QObject {
  Q_OBJECT

  private slots:

  void testDegree();
  void testSolve();
};

void
TestPoly::testDegree() {
  Poly a(1, -1);
  Poly b(1, 2, 1);
  QCOMPARE(a.degree(), 1);
  QCOMPARE(b.degree(), 2);
}

bool comp_vects(vector<double> l, vector<double> r) {
  if (l.size() != r.size())
    return false;

  sort(l.begin(), l.end());
  sort(r.begin(), r.end());

  for(int t = 0; t < (int) l.size(); ++t) {
    if (abs(l[t] - r[t]) > 1e-10)
      return false;
  }

  return true;
}

vector<double> mkvect(double x0) {
  vector<double> dat;
  dat.push_back(x0);
  
  return dat;
}

vector<double> mkvect(double x0, double x1) {
  vector<double> dat;
  dat.push_back(x0);
  dat.push_back(x1);
  
  return dat;
}

void
TestPoly::testSolve() {
  Poly a(1, -1);
  Poly b(1, -8, 15);
 
  
  QVERIFY(comp_vects(a.solve(), mkvect(1)) );
}

QTEST_MAIN(TestPoly)
#include "testpoly.moc"
