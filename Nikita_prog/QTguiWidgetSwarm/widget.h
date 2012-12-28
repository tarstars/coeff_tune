#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include "..\Swarm.h"

class QTimer;

namespace Ui {
class Widget;
}

class Widget : public QWidget, swarm
{
    Q_OBJECT
    
public:
    static const int cent=100;


    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void show(){QWidget::show();}
    void showSwarm(char*c=""){swarm::show(c);}

protected:
 void paintEvent(QPaintEvent*);
 void saveBeePosition(unsigned int beeN,unsigned int coordN);

private:
    Ui::Widget *ui;
    QTimer *ourTimer;
    QVector<QVector<QPointF> > trace;
    int stepCount;



public slots:
    void flySwarm();
    void start_timer();
    void stop_timer();
    void clearAxes();
};

#endif // WIDGET_H
