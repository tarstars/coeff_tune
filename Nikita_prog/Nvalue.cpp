#include"Nvalue.h"



void Nvalue::show(char *c1,char *c2){char * c=new char[40];sprintf(c,"%s+ i%s\n",c1,c2);}
void Nvalue::show(char *c0){this->show(c0,c0);}
void Nvalue::show(int n,int m,int k, int l){char * c=new char[40];sprintf(c,"%%%d.%dlf+ i%%%d.%dlf\n",n,m,k,l);}
void Nvalue::show(){this->show(3,1,3,1);}
void Nvalue::show(int n){this->show(n,1,n,1);}
void Nvalue::show(int n, int m){this->show(n,m,n,m);}
//void Nvalue::show(int n, int m,int k){this->show(n,m,n,k);}

//Nvalue & Nvalue::operator -(Nvalue &v){return *this+(-v);}