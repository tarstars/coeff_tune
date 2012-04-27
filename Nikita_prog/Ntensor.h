#ifndef NTENSOR_H
#define NTENSOR_H


#include<cmath>
#include"stdio.h"
#include"Nvalue.h"

class Ntensor: public Nvalue
{
public:
	int ndim,nels;
	int *dims;
	double *data;

	Ntensor();
	Ntensor(const Ntensor &);
	Ntensor &operator =(const Ntensor &);
	Ntensor(int i_ndim);
	Ntensor(int i_ndim,int *i_dims, int type=-1);
	Ntensor(int i_ndim,int *i_dims,double* vals);
	virtual ~Ntensor();
	
	int ind(int* i_inds);
	int *ind(int i_ind);
	double val(int * inds);

//		virtual Ntensor con();
//		virtual double abs();
	virtual void show(char *c1,char *c2);
	virtual void show(char *c0){Nvalue::show(c0);};
	virtual void show(){Nvalue::show();};
	virtual void show(int n){Nvalue::show(n);};
	virtual void show(int n, int m){Nvalue::show(n,m);};
	virtual void show(int n, int m,int k,int l);

	friend std::ostream & operator <<(std::ostream &os,Ntensor t);

	Ntensor operator +(Ntensor & ten);
	Ntensor operator -(Ntensor & ten);
	Ntensor operator *(Ntensor & ten);
	Ntensor operator /(Ntensor & ten);
	Ntensor mult(Ntensor & ten,int ind1=-1,int ind2=0);
	Ntensor extm(Ntensor & ten);
	double & el(int ind);
	double & el(int *ind);


};

class Nmatrix;
class Ntensor3;
class Ntensor4;



class Nvector: public Ntensor
{
public:
	Nvector();
	Nvector(const Nvector &);
	Nvector(const Ntensor &);
	Nvector(int dim,double *i_inp);
	Nvector(int dim,int type);
	~Nvector();
	friend std::ostream & operator <<(std::ostream &os,Ntensor t);

	double & operator ()(int);

	Nmatrix toMatrix3();

};


class Nmatrix: public Ntensor
{
public:
	Nmatrix();
	Nmatrix(const Nmatrix &);
	Nmatrix &operator =(const Nmatrix &ten);
	Nmatrix(const Ntensor &);
	Nmatrix(int dim,double *i_inp);
	Nmatrix(int dim,int type);
	~Nmatrix();
	friend std::ostream & operator <<(std::ostream &os,Ntensor t);

	double & operator ()(int,int);
	double tr();
	double det();
	Nvector toVector6();
	Ntensor4 toTensor4x3();
	Ntensor3 toTensor3x3();

	virtual void show(char *c1,char *c2);
	virtual void show(char *c0){Nvalue::show(c0);};
	virtual void show(){Nvalue::show();};
	virtual void show(int n){Nvalue::show(n);};
	virtual void show(int n, int m){Nvalue::show(n,m);};
	virtual void show(int n, int m,int k,int l);


};

class Ntensor3: public Ntensor
{
public:
	Ntensor3();
	Ntensor3(const Ntensor3 &);
	Ntensor3 &operator =(const Ntensor3 &ten);
	Ntensor3(const Ntensor &);
	Ntensor3(int dim,double *i_inp);
	~Ntensor3();
	friend std::ostream & operator <<(std::ostream &os,Ntensor t);

	double & operator ()(int,int,int);
	Nmatrix toMatrix3x6();

	virtual void show6(char *c1,char *c2);
	virtual void show6(char *c0){show6(c0,c0);};
	virtual void show6(){show6(3,1,3,1);};
	virtual void show6(int n){show6(n,n,n,n);};
	virtual void show6(int n, int m){show6(n,m,n,m);};
	virtual void show6(int n, int m,int k,int l);


};

class Ntensor4: public Ntensor
{
public:
	Ntensor4();
	Ntensor4(const Ntensor4 &);
	Ntensor4 &operator =(const Ntensor4 &ten);
	Ntensor4(const Ntensor &);
	Ntensor4(int dim,double *i_inp);
	~Ntensor4();
	friend std::ostream & operator <<(std::ostream &os,Ntensor t);

	double & operator ()(int,int,int,int);
	Nmatrix toMatrix6();

	virtual void show6(char *c1,char *c2);
	virtual void show6(char *c0){show6(c0,c0);};
	virtual void show6(){show6(3,1,3,1);};
	virtual void show6(int n){show6(n,n,n,n);};
	virtual void show6(int n, int m){show6(n,m,n,m);};
	virtual void show6(int n, int m,int k,int l);


};

#endif