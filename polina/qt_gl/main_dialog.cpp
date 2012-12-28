#include <iostream>
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include "our_gl_widget.h"

#include "main_dialog.h"

using namespace std;

OurDialog::OurDialog(QWidget *parent, Qt::WindowFlags flags) :
  QDialog(parent, flags) {
  

  /*ourTimer = new QTimer(this);
  connect(ourTimer, SIGNAL(timeout()), this, SLOT(update()));
  ourTimer -> start(100);
  ourTimer -> stop();

  QVBoxLayout *pvbl = new QVBoxLayout(this);

  ourStopButton = new QPushButton("Stop!", this);
  ourStartButton = new QPushButton("Start!", this);

  pvbl -> addWidget(ourStopButton);
  pvbl -> addWidget(ourStartButton);

  resize(450,450);
  */
  setupUi(this);

  ourTimer = new QTimer(this);
  connect(ourTimer, SIGNAL(timeout()), this, SLOT(update()));
  
  ourTimer -> start(100);
  ourTimer -> stop();

  connect(pushButtonStart, SIGNAL(pressed()), this, SLOT(start_timer()));
  connect(pushButtonStop, SIGNAL(pressed()), this, SLOT(stop_timer()));

  OurGlWidget *pOurGL;
  vlGL -> addWidget(pOurGL = new OurGlWidget(this));


  connect(dial_rot_x, SIGNAL(valueChanged(int)), pOurGL, SLOT(rotxChange(int)));
  connect(dial_rot_y, SIGNAL(valueChanged(int)), pOurGL, SLOT(rotyChange(int)));
  connect(dial_rot_z, SIGNAL(valueChanged(int)), pOurGL, SLOT(rotzChange(int)));
}

void
OurDialog::paintEvent(QPaintEvent*) {
  QPainter dc(this);

  static int x = 0;
  ++x;
  dc.drawEllipse(35 + x, 35, 50, 50);
}

void
OurDialog::start_timer() {
  cout << "start_timer" << endl;
  ourTimer -> start();
}

void
OurDialog::stop_timer() {
  cout << "stop_timer" << endl;
  ourTimer -> stop();
}
