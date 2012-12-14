#ifndef MAIN_DIALOG
#define MAIN_DIALOG

#include <QDialog>

class QPushButton;
class QPaintEvent;
class QTimer;

class OurDialog : public QDialog {
  Q_OBJECT

    public:

  QTimer *ourTimer;
  QPushButton *pButtonStart;
  QPushButton *pButtonStop;

  OurDialog(QWidget * parent = 0, Qt::WindowFlags = 0);
  
 protected:
  void paintEvent(QPaintEvent*);

 public slots:
  void start_timer();
  void stop_timer();
};

#endif
