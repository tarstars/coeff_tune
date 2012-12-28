#include "widget.h"
#include "ui_widget.h"

#include <QTimer>


class illus2dProb: public functional
{
public:
    illus2dProb(const std::vector<double> &bv,const std::vector<double> &ev)
        :functional(bv,ev){}
    double check(bees *p)
    {
        double dist=0;
        for(unsigned int j=0;j<p->coord.size();j++)
            dist+=(p->coord[j]-100)*(p->coord[j]-100);
        return dist;
    }

};


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    swarm(17,new illus2dProb(std::vector <double>(2,-cent),std::vector <double>(2,cent)),0.125,0.125,0.15,0.5),
    ui(new Ui::Widget),
    trace(this->population),
    stepCount(0)
{
    ui->setupUi(this);
    ourTimer = new QTimer(this);
    connect(ourTimer, SIGNAL(timeout()), this, SLOT(flySwarm()));
    ourTimer -> start(100);
    ourTimer -> stop();
    for(unsigned int k=0;k<Bee.size();k++)
    {
        trace[k].push_back(QPointF(2*(Bee[k]->coord[0]+2*cent),2*(Bee[k]->coord[1]+2*cent)));
        trace[k].push_back(QPointF(2*(Bee[k]->coord[0]+2*cent),2*(Bee[k]->coord[1]+2*cent)));
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent*) {

  QPainter dc(this);


  dc.setPen(QColor(255,0,0));
  dc.drawEllipse(4*cent, 4*cent, 5, 5);
  dc.drawLine(2*cent,4*cent,6*cent,4*cent);
  dc.drawLine(4*cent,2*cent,4*cent,6*cent);
 /*
  dc.setPen(QColor(255,0,0));
  dc.drawEllipse(Bee[2]->coord[0]+100, Bee[2]->coord[1]+100, 10, 10);
  dc.drawLines(trace[2]);

  dc.setPen(QColor(0,255,0));
  dc.drawEllipse(Bee[3]->coord[0]+100, Bee[3]->coord[1]+100, 10, 10);
  dc.drawLines(trace[3]);
*/
  int step=(256*256*256-1)/Bee.size();
  for(unsigned int k=0;k<Bee.size();k++)
  {
      dc.setPen(QColor((step*k)%256,(step*k/256)%256,(step*k/256/256)%256));
      dc.drawEllipse(2*(Bee[k]->coord[0]+2*cent), 2*(Bee[k]->coord[1]+2*cent), 10, 10);
      dc.drawLines(trace[k]);
  }

}

void Widget::saveBeePosition(unsigned int beeN,unsigned int coordN)
{
    textOut<<Bee[beeN]->speed[coordN]<<"\t";
}

void Widget::flySwarm()
{
    //bees *result=fly(1);
    stepCount++;
    ui->bestVal->setText(QString("Step %1: current best %2").arg(stepCount).arg(fly(1)->value));
//    ui->bestVal->setText(QString("%1").arg(fly(1)->value));
    for(unsigned int k=0;k<Bee.size();k++)
    {
        trace[k].push_back(trace[k].last());
        trace[k].push_back(QPointF(2*(Bee[k]->coord[0]+2*cent),2*(Bee[k]->coord[1]+2*cent)));
    }

    update();
}

void Widget::clearAxes()
{
    //bees *result=fly(1);
    trace.clear();
    trace.resize(this->population);
    for(unsigned int k=0;k<Bee.size();k++)
    {
        trace[k].push_back(QPointF(2*(Bee[k]->coord[0]+2*cent),2*(Bee[k]->coord[1]+2*cent)));
        trace[k].push_back(QPointF(2*(Bee[k]->coord[0]+2*cent),2*(Bee[k]->coord[1]+2*cent)));
    }

    update();
}

void Widget::start_timer() {
  ourTimer -> start();
}

void Widget::stop_timer() {
  ourTimer -> stop();
}
