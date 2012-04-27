#include<cmath>
#include"stdio.h"

class MATRIX{public:int id; complex **M;int I,J;
	void swap(MATRIX &m2){
		printf("swaping %d %d\n",this->id,m2.id);
		int RI=m2.I,RJ=m2.J,Rid=m2.id;
		complex **RM=m2.M;
		m2.I=I;I=RI;
		m2.J=J;J=RJ;
		m2.id=id;id=Rid;
		m2.M=M;M=RM;
	}
	MATRIX(const MATRIX &m){I=m.I;J=m.J;id=m.id*10;printf("%d constructed\n",id);
							M=new complex*[I];
							for(int i=0;i<I;i++){
								*(M+i)=new complex[J];
								for(int j=0;j<J;j++)
									*(*(M+i)+j)=m.M[i][j];}
	}

	MATRIX &operator =(const MATRIX &m){printf("%d becomes %d:\n",this->id,m.id);
		MATRIX R(m);
		swap(R);
		printf("returning %d\n",this->id);
	return *this;}
	~MATRIX(){	for(int i=0;i<I;i++)
						delete [] *(M+i);
				delete [] M;
				printf("%d deleted\n",id);};
				
	MATRIX(int I0,int J0,int ID=0){id=ID;I=I0;J=J0;M=new complex*[I];for(int i=0;i<I;i++)*(M+i)=new complex[J];printf("%d constructed pure\n",id);}
	MATRIX(int I0,int J0,char *c,int ID=0){id=ID;I=I0;J=J0;M=new complex*[I];	
		for(int i=0;i<I;i++){*(M+i)=new complex[J];
		switch(*c){
			case 105:{for(int j=0;j<J;j++)*(*(M+i)+j)=i*J+j;break;}
			default:{break;}
			}}printf("%d constructed %c\n",id,*c);
	};
	MATRIX(int I0,int J0,complex x,int ID=0){id=ID;I=I0;J=J0;M=new complex*[I];	
	for(int i=0;i<I;i++){*(M+i)=new complex[J];
		for(int j=0;j<J;j++)*(*(M+i)+j)=x;}printf("%d constructed %d's\n",id,x);
	};
	void view(char *c1,char *c2){char * c=new char[40];sprintf(c,"%s+ i%s, ",c1,c2);
				printf("--------%d viewing---------\n",id);
				for(int i=0;i<I;i++){for(int j=0;j<J;j++)printf(c,*(*(M+i)+j));
									printf("\n");}
				printf("--------------------------\n");
	delete [] c;}
	void view(char *c0){this->view(c0,c0);}
	void view(int n,int m,int k, int l){char * c=new char[40];sprintf(c,"%%%d.%dlf+ i%%%d.%dlf, ",n,m,k,l);
				printf("--------%d viewing---------\n",id);
				for(int i=0;i<I;i++){for(int j=0;j<J;j++)printf(c,*(*(M+i)+j));
									printf("\n");}
				printf("--------------------------\n");
	delete [] c;}
	void view(){this->view(3,1,3,1);}
	void view(int n){this->view(n,1,n,1);}
	void view(int n, int m){this->view(n,m,n,m);}
	void view(int n, int m,int k){this->view(n,m,n,k);}

	void viewR(char *c1,double n=1){
				printf("--------Re %d viewing---------\n",id);
				for(int i=0;i<I;i++){for(int j=0;j<J;j++)printf(c1,(*(M+i)+j)->mod(n));
									printf("\n");}
				printf("--------------------------\n");
	}


	MATRIX T(){printf("transpose %d:\n",this->id);
											MATRIX R(J,I,id*10); 
											for(int i=0;i<J;i++)
												for(int j=0;j<I;j++)R.M[i][j]=M[j][i];
	printf("returning %d\n",R.id);
	return R;}

};
//END OF CLASS
void swap(MATRIX &m1,MATRIX &m2){m1.swap(m2);}
	MATRIX operator +(MATRIX &m1,MATRIX &m2){printf("summing %d %d:\n",m1.id,m2.id);
											MATRIX R(min(m1.I,m2.I),min(m1.J,m2.J),m1.id+m2.id); 
											for(int i=0;i<min(m1.I,m2.I);i++)
												for(int j=0;j<min(m1.J,m2.J);j++)R.M[i][j]=m1.M[i][j]+m2.M[i][j];
	printf("returning %d\n",R.id);
	return R;}

	MATRIX operator -(MATRIX &m1,MATRIX &m2){printf("subtracting %d %d:\n",m1.id,m2.id);
											MATRIX R(min(m1.I,m2.I),min(m1.J,m2.J),m1.id-m2.id); 
											for(int i=0;i<min(m1.I,m2.I);i++)
												for(int j=0;j<min(m1.J,m2.J);j++)R.M[i][j]=m1.M[i][j]-m2.M[i][j];
	printf("returning %d\n",R.id);
	return R;}
	MATRIX operator -(MATRIX &m){printf("negating %d:\n",m.id);			
											MATRIX R(m); 
											for(int i=0;i<m.I;i++)
												for(int j=0;j<m.J;j++)R.M[i][j]=-m.M[i][j];
	printf("returning %d\n",R.id);
	return R;}
	
	MATRIX operator *(MATRIX &m1,MATRIX &m2){printf("producting %d %d:\n",m1.id,m2.id);
											MATRIX R(m1.I,m2.J,0.0,m1.id*m2.id); 
								if(m1.J==m2.I)for(int i=0;i<R.I;i++)
												for(int j=0;j<R.J;j++)
													for(int k=0;k<m1.J;k++)R.M[i][j]=R.M[i][j]+m1.M[i][k]*m2.M[k][j];
								else printf("ERROR PROD: %d->%d >< %d->%d, 0 returned\n",m1.id,m1.J,m2.id,m2.I);
	printf("returning %d\n",R.id);
	return R;}
	MATRIX operator *(complex &c,MATRIX &m2){printf("producting %lf+i%lf %d:\n",c.x,c.y,m2.id);
											MATRIX R(m2); 
											for(int i=0;i<R.I;i++)
												for(int j=0;j<R.J;j++)R.M[i][j]=R.M[i][j]*c;
	printf("returning %d\n",R.id);
	return R;}



void main(){
	int *p;
	{
		int d[10];p=d;
complex z1(1,3);
complex z2=ei(3);
complex z3=0*z1/z2;



printf("%lf %lfi\n",z1);
printf("%lf %lfi\n",z2);
printf("%lf %lfi\n",z3);
z1.view("%5.2lf");

MATRIX m1(2,4,"i",1);
MATRIX m2(2,4,"i",2);
MATRIX m3(2,4,complex (7,2),3);

printf("%d\n",*"i");

m1.view();
m2.view();
m3.view();
m1=m2*m2.T();
m1.view();

printf("end of line\n");
}
char s;
scanf("%c",&s);

}