#include <QtTest/QtTest>

class TestPoly : public QObject {
  Q_OBJECT

  private slots:

  void testTest();
};

void
TestPoly::testTest() {
  QCOMPARE(1,0);
}

QTEST_MAIN(TestPoly)
#include "testpoly.moc"
