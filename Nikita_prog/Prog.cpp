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
	Nmatrix((ij*2)).show();

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//============================================================
	printf("++++++++++++ The Programm ++++++++++++\n");

//	Ntensor4 Elastic=makeElasticTensor8(1,2,3,4,5,6,7,8);
	Ntensor4 Elastic=makeElasticTensor8(19.886e10, 5.467e10, 6.799e10, 0.783e10,19.886e10,6.799e10, 23.418e10, 5.985e10);
	printf("Elastic\n");
	Elastic.show6();

//	Ntensor3 Piezo=makePiezoTensor5(1,2,3,4,5);
	Ntensor3 Piezo=makePiezoTensor5(3.655, 2.407, 0.328, 0.328, 1.894);
	printf("Piezo\n");
	Piezo.show6();
	Piezo.show();

//	Nmatrix Permit=makePermitTensor2(1,2);
	Nmatrix Permit=makePermitTensor2(44.9,26.7);
	printf("Permittivity\n");
	Permit.show();

	double epsilon0=8.8542e-12;

	Nvector Direction=makeDirection3D(0,0,1);
	printf("Direction\n");
	Direction.show();

	Ntensor ji=Piezo.mult(Direction,2).mult(Direction,0);
	printf("ij\n");
	ji.show();

	Nmatrix Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0))/epsilon0;
	printf("Christofel\n");
	Christofel.show();


	Nvector velocities=eigval3(Christofel);
	printf("velocities\n");
	velocities.show();
	printf("velocities: %lf, %lf, %lf\n",sqrt(velocities(1)/4642.8),sqrt(velocities(2)/4642.8),sqrt(velocities(3)/4642.8));
	Nvector velocities2=sqrt(eigval3(Christofel)/4642.8);
	velocities2.show();
//	solve3(2,1.1,0).show();


	PovrayMaker pm1(QString("Velocity1"));
	PovrayMaker pm2(QString("Velocity2"));
	PovrayMaker pm3(QString("Velocity3"));
	//nsamp>3!!!!!!
	int nsamp=100;
	//nsamp>3!!!!!!
	int turns=7;
	int npoints=nsamp*(nsamp-2)/2+2;
	double Pi=3.1415926535897932384626433832795;
	double step=2*Pi/nsamp;
	double min1,min2,min3;
	Nvector *massive=new Nvector[npoints];

	{
		Direction=makeDirection3S(1,0,0);
		ji=Piezo.mult(Direction,2).mult(Direction,0);
		Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0));
		velocities=sqrt(eigval3(Christofel)/4642.8)/1000;///10000000000;
			velocities.show();printf("in km/s in direction ");
			Direction.show(6,4);
//		pm.addSphere(Direction.data,1);
		pm1.addRadial(100/velocities(1),0,0,1);
		pm2.addRadial(100/velocities(2),0,0,2);
		pm3.addRadial(100/velocities(3),0,0,3);
			min1=velocities(1);
			min2=velocities(2);
			min3=velocities(3);
			massive[0]=velocities;
	}
	for(int k=1;k<nsamp/2;k++)
		for(int j=0;j<nsamp;j++)
		{
			Direction=makeDirection3S(1,step*j,step*k);
			ji=Piezo.mult(Direction,2).mult(Direction,0);
			Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0));
			velocities=sqrt(eigval3(Christofel)/4642.8)/1000;///10000000000;
	//		pm.addSphere(Direction.data,1);
			velocities.show();printf("in km/s in direction ");
			Direction.show(6,4);
//			if((velocities(1)<0)||(velocities(2)<0)||(velocities(3)<0))velocities.show();
			pm1.addRadial(100/velocities(1),step*j,step*k,1);
			pm2.addRadial(100/velocities(2),step*j,step*k,2);
			pm3.addRadial(100/velocities(3),step*j,step*k,3);
			min1=(velocities(1)<min1)?velocities(1):min1;
			min2=(velocities(2)<min2)?velocities(2):min2;
			min3=(velocities(3)<min3)?velocities(3):min3;
			massive[j+1+nsamp*(k-1)]=velocities;
		}
	{
		Direction=makeDirection3S(1,0,Pi);
		ji=Piezo.mult(Direction,2).mult(Direction,0);
		Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0));
		velocities=sqrt(eigval3(Christofel)/4642.8)/1000;///10000000000;
			velocities.show();printf("in km/s in direction ");
			Direction.show(6,4);
//		pm.addSphere(Direction.data,1);
		pm1.addRadial(100/velocities(1),0,Pi,1);
		pm2.addRadial(100/velocities(2),0,Pi,2);
		pm3.addRadial(100/velocities(3),0,Pi,3);
			min1=(velocities(1)<min1)?velocities(1):min1;
			min2=(velocities(2)<min2)?velocities(2):min2;
			min3=(velocities(3)<min3)?velocities(3):min3;
			massive[npoints-1]=velocities;
	}
/**/
	pm1.codeLine(QString("//aaaaaaaaa!"));

	pm1.filmINI(turns);
	pm1.render();

	pm2.filmINI(turns);
	pm2.render();

	pm3.filmINI(turns);
	pm3.render();
	printf("minimum speed is %lf\n",min1);
	printf("Make contrast?(1,0)\n");
	int mc=2;
//	while(mc*mc-mc)scanf("%d",&mc);
	if (1)
	{
		pm1.init();
		pm2.init();
		pm3.init();
			pm1.addRadial(1000*(massive[0](1)-min1),0,0,1);
			pm2.addRadial(1000*(massive[0](2)-min2),0,0,2);
			pm3.addRadial(1000*(massive[0](3)-min3),0,0,3);
		for(int k=1;k<nsamp/2;k++)
			for(int j=0;j<nsamp;j++)
			{
				pm1.addRadial(1000*(massive[j+1+nsamp*(k-1)](1)-min1),step*j,step*k,1);
				pm2.addRadial(1000*(massive[j+1+nsamp*(k-1)](2)-min2),step*j,step*k,2);
				pm3.addRadial(1000*(massive[j+1+nsamp*(k-1)](3)-min3),step*j,step*k,3);
			}	
			pm1.addRadial(1000*(massive[npoints-1](1)-min1),0,Pi,1);
			pm2.addRadial(1000*(massive[npoints-1](2)-min2),0,Pi,2);
			pm3.addRadial(1000*(massive[npoints-1](3)-min3),0,Pi,3);

	pm1.filmINI(turns);
	pm1.render();

	pm2.filmINI(turns);
	pm2.render();

	pm3.filmINI(turns);
	pm3.render();
			
	}		
			
		printf("end of line\n");
		scanf("%d",mc);
		}

	//char s;
	//scanf("%c",&s);

	return 0;
}