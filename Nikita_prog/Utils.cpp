#include"Utils.h"
#include"Ntensor.h"
#include"Ncomplex.h"

Ntensor4 makeElasticTensor36(double mat [])
{
	Nmatrix nret(6,mat);
	return nret.toTensor4x3();
}

Ntensor4 makeElasticTensor8(double c11,double c12,double c13,double c14,double c22,double c23,double c33,double c44)
{
	Nmatrix nret(6,0);
	nret(1,1)=c11;
	nret(2,2)=c22;
	nret(3,3)=c33;
	nret(2,3)=nret(3,2)=c23;
	nret(1,3)=nret(3,1)=c13;
	nret(1,2)=nret(2,1)=c12;
	nret(4,4)=c44;
	nret(1,4)=nret(4,1)=c14;
	nret(2,4)=nret(4,2)=-c14;
	nret(5,5)=c44;
	nret(5,6)=nret(6,5)=c14;
	nret(6,6)=(c11-c12)/2;
	return nret.toTensor4x3();
}


Ntensor3 makePiezoTensor18(double mat [])
{
	Nmatrix nret(6,mat);
	return nret.toTensor3x3();
}

Ntensor3 makePiezoTensor5(double e15,double e22,double e31,double e32,double e33)
{
	Nmatrix nret(6,0);
	nret(2,1)=nret(1,6)=-e22;
	nret(2,2)=e22;
	nret(3,1)=e31;
	nret(3,2)=e32;
	nret(3,3)=e33;
	nret(2,4)=nret(1,5)=e15;
	return nret.toTensor3x3();
}





Nmatrix makePermitTensor6(double mat [])
{
	Nvector nret(6,mat);
	return nret.toMatrix3();
}

Nmatrix makePermitTensor2(double eo,double ee)
{
	Nmatrix nret(3,0);
	nret(1,1)=eo;
	nret(2,2)=eo;
	nret(3,3)=ee;
	return nret;
}




Nvector makeDirection3D(double n1,double n2,double n3)
{
	Nvector nret(3,0);
	nret(1)=n1;
	nret(2)=n2;
	nret(3)=n3;
	return nret;
}

Nvector makeDirection3S(double rho,double phi, double theta)
{
	Nvector nret(3,0);
	nret(1)=rho*cos(phi)*sin(theta);
	nret(2)=rho*sin(phi)*sin(theta);
	nret(3)=rho*cos(theta);
	return nret;
}


Nvector solve3(double a,double b,double c)
{
	Nvector ret(3,0);
	double Q=(a*a-3*b)/9;
	double R=(2*a*a*a-9*a*b+27*c)/54;
	double S=Q*Q*Q-R*R;
	double sqrtQ=sqrt(abs(Q));
	double x=abs(R)/(sqrtQ*sqrtQ*sqrtQ);
	if(S>0)
	{
		double phi=acos(x)/3;
		ret(1)=-2*sqrtQ*cos(phi)-a/3;
		ret(2)=-2*sqrtQ*cos(phi+2.094395103)-a/3;
		ret(3)=-2*sqrtQ*cos(phi-2.094395103)-a/3;
	}
	else if(S==0)
	{
		ret(1)=-2*sqrtQ*sign(R)-a/3;
		ret(2)=sqrtQ*sign(R)-a/3;
		ret(3)=sqrtQ*sign(R)-a/3;
	}
	else
		throw(("error"));
	/*
	{
		if(Q>0)
		{
			double phi=ach(abs(x))/3;
			ret(1)=-2*sqrt(Q)*ch(phi)*sign(R)-a/3;
			ret(2)=0;//Ncomplex(2*sqrt(Q)*ch(phi)*sign(R)-a/3, sqrt(3)*sqrt(Q)*sh(phi));
			ret(3)=0;//Ncomplex(2*sqrt(Q)*ch(phi)*sign(R)-a/3,-sqrt(3)*sqrt(Q)*sh(phi));
		}
		else if(Q<0)
		{
			double phi=ash(x)/3;
			ret(1)=-2*sqrtQ*sh(phi)-a/3;
			ret(2)=0;//Ncomplex(2*sqrtQ*sh(phi)-a/3, sqrt(3)*sqrtQ*ch(phi));
			ret(3)=0;//Ncomplex(2*sqrtQ*sh(phi)-a/3,-sqrt(3)*sqrtQ*ch(phi));
		}
		else
		{
			double phi=pow(2*R,1.0/3.0)/2;
			ret(1)=-2*phi-a/3;
			ret(2)=0;//Ncomplex(-phi-a/3, sqrt(3)*phi);
			ret(3)=0;//Ncomplex(-phi-a/3,-sqrt(3)*phi);
		}

	}
	*/
	return ret;
}

Nvector eigval3(Nmatrix mat)
{
	double a=-mat.tr();
	double b=mat(1,2)*mat(2,1)+mat(1,3)*mat(3,1)+mat(3,2)*mat(2,3)-mat(1,1)*(mat(2,2)+mat(3,3))-mat(2,2)*mat(3,3);
	double c=mat.det();

	return solve3(a,b,c);
}