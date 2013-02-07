#include <QtTest/QtTest>
#include <algorithm>
#include <vector>
#include <cmath>

#include "poly.h"

using namespace std;

class TestSubject : public QObject {
  Q_OBJECT

  private slots:

  void testDegree();
  void testSolve();
};

void TestSubject::testDegree() {
  Poly a(1, -1);
  Poly b(1, 2, 1);
  QCOMPARE(a.degree(), 1);
  QCOMPARE(b.degree(), 2);
}

bool comp_vectors(vector<double> p, vector<double> q){
  if (p.size() != q.size())
	 return false;

  sort(p.begin(), p.end());
  sort(q.begin(), q.end());

  for(int t = 0; t < (int)p.size(); ++t){
    if (abs(p[t] - q[t] > 1e-10))
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

vector<double> mkvect(double x0, double x1, double x2) {
  vector<double> dat;
  dat.push_back(x0);
  dat.push_back(x1);
  dat.push_back(x2);
  return dat;
}


void TestSubject::testSolve() {
  Poly a(1, -1);
  Poly b(1, -8, 15);

  
  QVERIFY(comp_vectors(a.solve(), mkvect(1)));
}

QTEST_MAIN(TestSubject)
#include "testsubject.moc"
