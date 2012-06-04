#include "Ncomplex.h"
//#include "Nvalue.h"
#include "Ntensor.h"
#include "Utils.h"
#include "PovrayMaker.h"

double* convD(double data0[])
{
	int length=(sizeof data0)/(sizeof(double));
double * data1=new double[length];
for(int j=0;j<length;j++)data1[j]=data0[j];
return data1;
}


int main()
{
		int *p;

		{
			int d[10];p=d;
	Ncomplex z1(1,3);
	Ncomplex z2=ei(3);
	Ncomplex z3=z1/z2;


	double * data1=new double[16];
	double * data16=new double[16];
	double data4 []={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	double data6 []={1,2,3,4,5,6};
	double data2 []={1,2,3,4};

	int s=(sizeof data4)/(sizeof(double));
	for(int j=0;j<s;j++)
	{
		data1[j]=data4[j];
	}

	s=(sizeof data6)/(sizeof(double));
	for(int j=0;j<s;j++)
	{
		data16[j]=data6[j];
	}

	printf("%lf %lfi\n",z1.x,z1.y);
	z1.show("%5.2lf");
	z2.show(5,2);
	(z2+z3).show();

	Nmatrix mat(sqrt(double(s)),data1);
	Nmatrix mat2(sqrt(double(s)),data1);
	mat.show();
	printf("tr=%lf det=%lf \n",mat.tr(),mat.det());


	Nmatrix mat3=mat*mat2;
	mat3.show();
	Nmatrix mat4=mat.mult(mat2);
	mat4.show();
	mat4=mat.mult(mat2,0);
	mat4.show();

	Nvector lambda(6,data16);
	lambda.show();
	Nmatrix ij=lambda.toMatrix3();
	ij.show();
	printf("tr=%lf det=%lf \n",ij.tr(),ij.det());

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//============================================================

	Ntensor4 Elastic=makeElasticTensor8(1,2,3,4,5,6,7,8);
	Elastic.show6();

	Ntensor3 Piezo=makePiezoTensor5(1,2,3,4,5);
	Piezo.show6();
	Piezo.show();

	Nmatrix Permit=makePermitTensor2(1,2);
	Permit.show();

	Nvector Direction=makeDirection3D(1,2,3);
	Direction.show();

	Ntensor ji=Piezo.mult(Direction,2).mult(Direction,0);
	ji.show();

	Nmatrix Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0));
	Christofel.show();


	Nvector velocities=eigval3(Christofel);
	velocities.show();
	solve3(2,1.1,0).show();


	PovrayMaker pm1(QString("Velocity1"));
	PovrayMaker pm2(QString("Velocity2"));
	PovrayMaker pm3(QString("Velocity3"));
	int nsamp=4;
	double Pi=3.1415926535897932384626433832795;
	double step=2*Pi/nsamp;
	for(int k=1;k<nsamp/2;k++)
		for(int j=0;j<nsamp;j++)
		{
			Direction=makeDirection3S(1,step*j,step*k);
			ji=Piezo.mult(Direction,2).mult(Direction,0);
			Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0));
			velocities=eigval3(Christofel);
	//		pm.addSphere(Direction.data,1);
			pm1.addRadial(velocities(1),step*j,step*k,1);
			pm2.addRadial(velocities(2),step*j,step*k,2);
			pm3.addRadial(velocities(3),step*j,step*k,3);
		}
	{
		Direction=makeDirection3S(1,0,0);
		ji=Piezo.mult(Direction,2).mult(Direction,0);
		Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0));
		velocities=eigval3(Christofel);
//		pm.addSphere(Direction.data,1);
		pm1.addRadial(velocities(1),0,0,1);
		pm2.addRadial(velocities(2),0,0,2);
		pm3.addRadial(velocities(3),0,0,3);
	}
	{
		Direction=makeDirection3S(1,0,Pi);
		ji=Piezo.mult(Direction,2).mult(Direction,0);
		Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0));
		velocities=eigval3(Christofel);
//		pm.addSphere(Direction.data,1);
		pm1.addRadial(velocities(1),0,Pi,1);
		pm2.addRadial(velocities(2),0,Pi,2);
		pm3.addRadial(velocities(3),0,Pi,3);
	}

	pm1.codeLine(QString("//aaaaaaaaa!"));
	pm1.filmINI(4);
	pm1.render();
//	pm2.render();
//	pm3.render();
	printf("end of line\n");
		}

	//char s;
	//scanf("%c",&s);

	return 0;
}