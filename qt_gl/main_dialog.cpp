#include <iostream>

#include "main_dialog.h"

#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QVBoxLayout>

using namespace std;

OurDialog::OurDialog(QWidget *parent, Qt::WindowFlags flags) :
  QDialog(parent, flags) {
  ourTimer = new QTimer(this);
  connect(ourTimer, SIGNAL(timeout()), this, SLOT(update()));

  ourTimer -> start(100);
  ourTimer -> stop();

  QVBoxLayout *pvbl = new QVBoxLayout(this);

  pButtonStart = new QPushButton("Start!",this);
  pButtonStop = new QPushButton("Stop!",this);

  pvbl -> addWidget(pButtonStart);
  pvbl -> addWidget(pButtonStop);

  resize(300, 300);

  connect(pButtonStart, SIGNAL(pressed()), this, SLOT(start_timer()));
  connect(pButtonStop, SIGNAL(pressed()), this, SLOT(stop_timer()));
}

void
OurDialog::paintEvent(QPaintEvent*) {
  QPainter dc(this);

  static int x = 0;
  ++ x;
  dc.drawEllipse(50 + (x%150), 50, 100, 100);
}

void
OurDialog::start_timer() {
  ourTimer -> start();
}

void
OurDialog::stop_timer() {
  ourTimer -> stop();
}
