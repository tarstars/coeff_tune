#ifndef MAIN_DIALOG
#define MAIN_DIALOG

#include <QDialog>

class QPushButton;
class QPaintEvent;
class QTimer;

#include "ui_md.h"

class OurDialog : public QDialog, public Ui::mainDialog {
  Q_OBJECT

public:

  QTimer *ourTimer;
  OurDialog(QWidget * parent = 0, Qt::WindowFlags = 0);
  
 protected:
  void paintEvent(QPaintEvent*);

 public slots:
  void start_timer();
  void stop_timer();
};

#endif
