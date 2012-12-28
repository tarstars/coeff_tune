#ifndef MAIN_DIALOG
#define MAIN_DIALOG

#include <QDialog>

class QPaintEvent;
class QTimer;
class QPushButton;

#include "ui_md.h"

class OurDialog: public QDialog, public Ui::main_Dialog {
  Q_OBJECT

    QTimer *ourTimer;
  QPushButton *ourStopButton;
  QPushButton *ourStartButton;
  
    public:
  OurDialog(QWidget * parent = 0, Qt::WindowFlags = 0);

 protected:
  void paintEvent(QPaintEvent*);

  public slots:
  void start_timer();
  void stop_timer();
};

#endif
