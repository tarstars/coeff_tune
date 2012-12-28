#ifndef Swarm
#define Swarm


#include<map>
#include<vector>
#include<fstream>
#include"stdio.h"
#include <stdlib.h>
#include <time.h>
#include <QFile>
#include <QString>
#include <QTextStream>

class functional;

class bees
{
private:
	
	bees(){printf("hello bee\n");};
	
public:
    double inert, conf, trust,intent,rndPower;
	std::vector<double> coord;
	std::vector<double> speed;
	std::vector<double> memory_place;
	double value,memory_value;
	

    bees(const bees & Bee):inert(Bee.inert), conf(Bee.conf), trust(Bee.trust),intent(Bee.intent),rndPower(Bee.rndPower),coord(Bee.coord),speed(Bee.speed),memory_place(Bee.memory_place),value(Bee.value),memory_value(Bee.memory_value){}
    bees(const std::vector<double> & in,double ine=1,double co=1,double tr=1,double inte=5,int rndp=2):inert(ine), conf(co), trust(tr), intent(inte),rndPower(rndp),coord(in),speed(in),memory_place(in),value(0),memory_value(0){}
    bees(unsigned int N,double x,double in=1,double co=1,double tr=1,double inte=5,int rndp=2):inert(in), conf(co), trust(tr), intent(inte),rndPower(rndp),coord(N,x),speed(N,x),memory_place(N,x),value(0),memory_value(0){}

    bees(functional *probl,double in=1,double co=1,double tr=1,double inte=5,int rndp=2);
	
    virtual unsigned int size() const{return coord.size();}
    virtual void setChar(double i,double c,double t,double in);
    virtual void move(std::vector<double>,std::vector<double>,std::vector<double>);
    virtual void show(char* c="");
	
};


class functional
{
private:
	functional();
	functional(const functional &);
	functional &operator = (const functional &);
public:
	bees begin;
	bees end;
	
	functional(const std::vector<double> &,const std::vector<double> &);
	
    virtual double check(bees *p);// const;
	
	virtual void show(char* c="");
};

class swarm
{
private:
	swarm();
	swarm(const swarm &);
	swarm &operator = (const swarm &);
	
	
	
	//std::map<double,unsigned int> distance;
public:
	bees bestBee,center;
	unsigned int population;
	functional *problem;
	std::vector<bees*> Bee;
//	std::vector<double> value;
	QFile *file;
	QTextStream textOut;
	
	
    swarm(unsigned int pop, functional *prob,double in=1,double co=1,double tr=1,double inte=5,int rndp=2);
	~swarm(){file->close();}
	void communicate();
	void move();
    bees* fly(double threshold=0.1,int Nsteps=100);
    bees* fly(int Nsteps);
    virtual void saveBeePosition(unsigned int beeN,unsigned int coordN);
	virtual void show(char* c="");
	
};

/*
class TestPar: public params
{

public:
	int x,y,z;
	TestPar(int i1,int i2, int i3)x(i1),y(i2),z(i3){};
	params &operator = (const &params){};
	virtual void tweak()=0;
	virtual params operator+(const &params p)=0;
	virtual params operator*(double n)=0;
}
	
class TestFun: public functional
{
private:
	int n;
public:
		TesrFun(int i_n)n(i_n){};
		int check
}
*/
	
#endif
