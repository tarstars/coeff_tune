#include"Ncomplex.h"

const double PI=3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093845;

Ncomplex::Ncomplex(double x1, double y1){x=x1;y=y1;};
Ncomplex::Ncomplex(double x1){x=x1;y=0;};
Ncomplex::Ncomplex(int x1){x=x1;y=0;};
Ncomplex::Ncomplex(){x=0;y=0;};
double Ncomplex::arg(double N){//in -PI;PI
					double P;
					if(y>0)P=PI/2; else if(y<0) P=-PI/2; else P=0;
					if(x==0) return P/N;
					if (x>0) return atan(y/x)/N;
					else return (2*P+atan(y/x))/N;
		};
double Ncomplex::arg2(double N){//in 0;2PI
				if(x==0)if(y>0)return PI/2/N; else if(y<0)return 3*PI/2/N; else return 0;
					if (x>0)
			if (y>0)return atan(y/x)/N;else return 2*PI/N+atan(y/x)/N;
					else
			if (y>0)return PI/N+atan(y/x)/N;else return PI/N+atan(y/x)/N;
		};
Ncomplex Ncomplex::con(){return Ncomplex (x,-y);};
double Ncomplex::abs(double n){return pow(sqrt(x*x+y*y), n);};
Ncomplex Ncomplex::operator &=(double z){return *this=Ncomplex(z,0);}
void Ncomplex::show(char *c1,char *c2){char * c=new char[40];sprintf(c,"%s+ i%s\n",c1,c2);
								printf(c,x,y);}
void Ncomplex::show(char *c0){this->show(c0,c0);}
void Ncomplex::show(int n,int m,int k, int l){char * c=new char[40];sprintf(c,"%%%d.%dlf+ i%%%d.%dlf\n",n,m,k,l);
							printf(c,x,y);}
void Ncomplex::show(){this->show(3,1,3,1);}
void Ncomplex::show(int n){this->show(n,1,n,1);}
void Ncomplex::show(int n, int m){this->show(n,m,n,m);}
void Ncomplex::show(int n, int m,int k){this->show(n,m,n,k);}

Ncomplex operator +(Ncomplex z,Ncomplex z1){return Ncomplex(z.x+z1.x,z.y+z1.y);}
Ncomplex operator +(Ncomplex z1,double z){return Ncomplex(z1.x+z,z1.y);}
Ncomplex operator +(double z,Ncomplex z1){return Ncomplex(z1.x+z,z1.y);}

Ncomplex operator -(Ncomplex z){return Ncomplex(-z.x,-z.y);}
Ncomplex operator -(Ncomplex z,Ncomplex z1){return Ncomplex(z.x-z1.x,z.y-z1.y);}
Ncomplex operator -(Ncomplex z1,double z){return Ncomplex( z1.x-z, z1.y);}
Ncomplex operator -(double z,Ncomplex z1){return Ncomplex(-z1.x+z,-z1.y);}

Ncomplex operator *(Ncomplex z1,Ncomplex z){return Ncomplex(z1.x*z.x-z1.y*z.y,z1.x*z.y+z1.y*z.x);}
Ncomplex operator *(double z,Ncomplex z1){return Ncomplex(z1.x*z,z1.y*z);}
Ncomplex operator *(Ncomplex z1,double z){return Ncomplex(z1.x*z,z1.y*z);}

Ncomplex operator /(Ncomplex z1,double z){return Ncomplex(z1.x/z,z1.y/z);}
Ncomplex operator /(double z,Ncomplex z1){return z*z1.con()/z1.abs(2);}
Ncomplex operator /(Ncomplex z1,Ncomplex z){return z1*z.con()/z.abs(2);}

Ncomplex sin(Ncomplex z){return Ncomplex(sin(z.x)*ch(z.y), cos(z.x)*sh(z.y));}
Ncomplex cos(Ncomplex z){return Ncomplex(cos(z.x)*ch(z.y), -sin(z.x)*sh(z.y));}
Ncomplex ei(double fi){return Ncomplex(cos(fi),sin(fi));};
Ncomplex ei(Ncomplex z){return exp(-z.y)*ei(z.x);};

Ncomplex pow(Ncomplex z1,double x){return Ncomplex (z1.abs(x)*cos(x*z1.arg()),z1.abs(x)*sin(x*z1.arg()));}
Ncomplex pow(double x,Ncomplex z1){return exp(pow(x,z1.x))*ei(log(x)*z1.y);};
Ncomplex pow(Ncomplex z1,Ncomplex z2){return pow(z1.abs(), z2)*ei(z1.arg()*z2);};
Ncomplex sqr(Ncomplex z){return z*z;};
double abs(Ncomplex z){return z.abs();};

