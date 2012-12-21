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

class bees
{
private:
	
	bees(){printf("hello bee\n");};
	
public:
	double inert, conf, trust;
	std::vector<double> coord;
	std::vector<double> speed;
	std::vector<double> memory_place;
	double value,memory_value;
	

	bees(unsigned int N,double x):inert(1), conf(1), trust(1),coord(N,x),speed(N,0),memory_place(N,x),value(0),memory_value(0){};
	bees(const std::vector<double> & in):inert(1), conf(1), trust(1),coord(in),speed(coord.size(),0),memory_place(in),value(0),memory_value(0){};
	bees(const std::vector<double> &,const std::vector<double> &);
	bees(const bees &,const bees &);
	virtual void random(const std::vector<double> &,const std::vector<double> &);
	
	virtual unsigned int size() const{return coord.size();};
	virtual void move(std::vector<double>);
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
	
	virtual double check(bees *p);
	
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
	
	
	swarm(unsigned int, functional *);
	~swarm(){file->close();}
	void communicate();
	void move();
	bees* fly(int N=15);
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