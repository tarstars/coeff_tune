#ifndef NVALUE_H
#define NVALUE_H

#include<cmath>
#include"stdio.h"
#include<iostream>


class Nvalue
{
public:
	double type;
//	static int valCount;
	Nvalue(){type=0;};

//		virtual Nvalue conj();
		virtual double abs(double n=1){return pow(type,n);};
	virtual void show(char *c1,char *c2);
	virtual void show(char *c0);
	virtual void show();
	virtual void show(int n);
	virtual void show(int n, int m);
//	virtual void show(int n, int m,int k);
	virtual void show(int n, int m,int k,int l);


//	virtual Nvalue &operator + (Nvalue &);
//	virtual Nvalue &operator - ();
//	virtual Nvalue &operator - (Nvalue &);
};

#endif