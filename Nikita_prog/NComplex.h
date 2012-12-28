
#ifndef Ncomplex_H
#define Ncomplex_H

#include<cmath>
#include"stdio.h"
//#include"Nvalue.h"

	inline double sh(double x){return (exp(x)-exp(-x))/2;}
	inline double ch(double x){return (exp(x)+exp(-x))/2;}
	inline double th(double x){return (exp(x)-exp(-x))/(exp(x)+exp(-x));}
	inline double ash(double x){return log(x+sqrt(x*x+1));}
	inline double ach(double x){return log(x+sqrt(x*x-1));}
	inline double ath(double x){return log((x+1)/(x-1))/2;}
	inline double sqr(double a){return a*a;}
	inline double max(double x,double y){if(x>y)return x;else return y;}
	inline double min(double x,double y){if(x>y)return y;else return x;}
	inline double sign(double x){if(x>0)return 1;if(x<0)return -1;return 0;}

//class test{public: test(){};virtual double abs(double n){return 0;};};

class Ncomplex//: public Nvalue
{
public: double x,y;
		Ncomplex(double x1, double y1);
		Ncomplex(double x1);
		Ncomplex(int x1);
		Ncomplex();
		double	arg(double N=1.0);
		double	arg2(double N=1.0);
		inline Ncomplex con();
		double abs(double n=1);
		Ncomplex operator &=(double z);
	void show(char *c1,char *c2);
	void show(char *c0);
	void show(int n,int m,int k, int l);
	void show();
	void show(int n);
	void show(int n, int m);
	void show(int n, int m,int k);
friend Ncomplex operator +(Ncomplex z,Ncomplex z1);
friend Ncomplex operator +(Ncomplex z1,double z);
friend Ncomplex operator +(double z,Ncomplex z1);

friend Ncomplex operator -(Ncomplex z);
friend Ncomplex operator -(Ncomplex z,Ncomplex z1);
friend Ncomplex operator -(Ncomplex z1,double z);
friend Ncomplex operator -(double z,Ncomplex z1);

friend Ncomplex operator *(Ncomplex z1,Ncomplex z);
friend Ncomplex operator *(double z,Ncomplex z1);
friend Ncomplex operator *(Ncomplex z1,double z);

friend Ncomplex operator /(Ncomplex z1,double z);
friend Ncomplex operator /(double z,Ncomplex z1);
friend Ncomplex operator /(Ncomplex z1,Ncomplex z);

friend Ncomplex sin(Ncomplex z);
friend Ncomplex cos(Ncomplex z);
friend Ncomplex ei(Ncomplex z);

friend Ncomplex pow(Ncomplex z1,double x);
friend Ncomplex pow(double x,Ncomplex z1);
friend Ncomplex pow(Ncomplex z1,Ncomplex z2);
friend Ncomplex sqr(Ncomplex z);
friend double abs(Ncomplex z);
};

Ncomplex ei(double fi);

#endif