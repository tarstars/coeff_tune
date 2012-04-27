#include"Nvalue.h"
#include "Ntensor.h"

//double PI=3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093845;

Ntensor::Ntensor()
{
	ndim=0;
	dims=0;
	data=0;
	nels=0;
}

Ntensor::Ntensor(const Ntensor & cpy)
{
	ndim=cpy.ndim;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
	nels=cpy.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=cpy.data[j];
}

Ntensor &Ntensor::operator =(const Ntensor & ten)
{
	ndim=ten.ndim;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=ten.dims[j];
	nels=ten.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=ten.data[j];

	return *this;
}
Ntensor::~Ntensor()
{
	if(dims) delete [] dims;
	if(data) delete [] data;
}

Ntensor::Ntensor(int i_ndim)
{
	ndim=i_ndim;
	dims=new int[ndim];
	data=0;
	nels=0;
}

Ntensor::Ntensor(int i_ndim, int *i_dims, int type)
{
		ndim=i_ndim;
		dims=i_dims;
		nels=1;
		for(int j=0;j<ndim;j++)nels*=dims[j];
		data=new double[nels];
	switch(type)
	{
	case -1:break;
	case 0: for(int j=0;j<nels;j++)
				data[j]=0; break;
	}

}

int Ntensor::ind(int* i_inds)
{
	int base=1, ret=i_inds[0];
	for(int j=1;j<ndim;j++)
	{
//		printf("ret=%d\n",ret);
		base*=dims[j-1];
		ret+=i_inds[j]*base;
	}
	return ret;
}
int *Ntensor::ind(int i_ind)
{
	int *ret=new int[ndim];
	for(int j=0;j<ndim;j++)
	{
		ret[j]=i_ind%dims[j];
		i_ind/=dims[j];
	}
	return ret;
}

Ntensor::Ntensor(int i_ndim, int *i_dims, double *i_vals)
{
	ndim=i_ndim;
	dims=i_dims;
	data=i_vals;
	nels=1;
	for(int j=0;j<ndim;j++)nels*=dims[j];
//	for(int j=0;j<ndim;j++)data=new double[nels];
//	for(int j=0;j<nels;j++)

}

void Ntensor::show(char *c1,char *c2)
{
	char * c=new char[40];sprintf(c,"%s\t",c1);
	for(int j=0;j<nels;j++)printf("%3.1lf\t",data[j]);
	printf("\n");
}

void Ntensor::show(int n,int m,int k, int l)
{
	char * c=new char[40];sprintf(c,"%%%d.%dlf\t",n,m);
	for(int j=0;j<nels;j++)printf("%3.1lf\t",data[j]);
	printf("\n");
}

std::ostream & operator <<(std::ostream &os, Ntensor t)
{
	for(int j=0;j<t.nels;j++)os<<t.data[j]<<"\t";
	os<<std::endl;
	return os;

}

Ntensor Ntensor::operator +(Ntensor & ten)
{
	if(ndim==ten.ndim && nels==ten.nels)
	{
		double *nData=new double[nels];
		int *nDims=new int[ndim];
		for(int j=0;j<ndim;j++)nDims[j]=dims[j];
		for(int j=0;j<nels;j++)nData[j]=data[j]+ten.data[j];

		return Ntensor(ndim,nDims,nData);
	}
	else
		return Ntensor();
}
Ntensor Ntensor::operator -(Ntensor & ten)
{
	double *nData=new double[nels];
	int *nDims=new int[ndim];
	for(int j=0;j<ndim;j++)nDims[j]=dims[j];
	for(int j=0;j<nels;j++)nData[j]=data[j]-ten.data[j];

	return Ntensor(ndim,nDims,nData);
}
Ntensor Ntensor::operator *(Ntensor & ten)
{
	if(ndim==ten.ndim && nels==ten.nels)
	{
		double *nData=new double[nels];
		int *nDims=new int[ndim];
		for(int j=0;j<ndim;j++)nDims[j]=dims[j];
		for(int j=0;j<nels;j++)nData[j]=data[j]*ten.data[j];
		return Ntensor(ndim,nDims,nData);
	}
	else if (ten.nels==1)
	{
		double *nData=new double[nels];
		int *nDims=new int[ndim];
		for(int j=0;j<ndim;j++)nDims[j]=dims[j];
		for(int j=0;j<nels;j++)nData[j]=data[j]*ten.data[0];
		return Ntensor(ndim,nDims,nData);
	}
	else
		return Ntensor();
}
Ntensor Ntensor::operator /(Ntensor & ten)
{
	if(ndim==ten.ndim && nels==ten.nels)
	{
		double *nData=new double[nels];
		int *nDims=new int[ndim];
		for(int j=0;j<ndim;j++)nDims[j]=dims[j];
		for(int j=0;j<nels;j++)nData[j]=data[j]/ten.data[j];
		return Ntensor(ndim,nDims,nData);
	}
	else if (ten.nels==1)
	{
		double *nData=new double[nels];
		int *nDims=new int[ndim];
		for(int j=0;j<ndim;j++)nDims[j]=dims[j];
		for(int j=0;j<nels;j++)nData[j]=data[j]/ten.data[0];
		return Ntensor(ndim,nDims,nData);
	}
	else
		return Ntensor();
}
double & Ntensor::el(int i_ind)
{
return data[i_ind];
}

double & Ntensor::el(int *i_ind)
{
return data[ind(i_ind)];
}

Ntensor Ntensor::extm(Ntensor & ten)
{

		int nNdims=ndim+ten.ndim;
		int *nDims=new int[nNdims];

		for(int j=0;j<ndim;    j++)nDims[j]=dims[j];
		for(int j=0;j<ten.ndim;j++)nDims[j+ndim]=ten.dims[j];
		Ntensor ret(nNdims,nDims,0);

		int * nInds;
		int * thInds=new int[ndim];
		int * teInds=new int[ten.ndim];
		for(int j=0;j<ret.nels;j++)
		{
				nInds=ret.ind(j);
				for(int p=0;p<ndim;	   p++)thInds[p]=nInds[p];
				for(int p=0;p<ten.ndim;p++)teInds[p]=nInds[p+ndim];
				ret.data[j]=el(thInds)*ten.el(teInds);
		}
		delete [] nInds;
		delete [] thInds;
		delete [] teInds;

		return ret;
}

Ntensor Ntensor::mult(Ntensor & ten,int ind1,int ind2)
{
	if(ind1==-1)ind1=ndim-1;
	if(ind1>ndim-1)
		throw Ntensor();
	int N=dims[ind1];
	if(N==ten.dims[0])
	{
		int nNdims=ndim+ten.ndim-2;
		int *nDims=new int[nNdims];

		for(int j=0;     j<ind1;j++)nDims[j]=dims[j];
		for(int j=ind1+1;j<ndim;j++)nDims[j-1]=dims[j];
		for(int j=0;     j<ind2;j++)nDims[j+ndim-1]=ten.dims[j];
		for(int j=ind2+1;j<ten.ndim;j++)nDims[j+ndim-2]=ten.dims[j];
		Ntensor ret(nNdims,nDims,0);

		int * nInds;
		int * thInds=new int[ndim];
		int * teInds=new int[ten.ndim];
		for(int j=0;j<ret.nels;j++)
			for(int k=0;k<N;k++)
			{
				nInds=ret.ind(j);
				for(int p=0;     p<ind1;p++)thInds[p]=nInds[p];				thInds[ind1]=k;
				for(int p=ind1+1;p<ndim;p++)thInds[p]=nInds[p-1];
				for(int p=0;     p<ind2;p++)teInds[p]=nInds[p+ndim-1];	teInds[ind2]=k;
				for(int p=ind2+1;p<ten.ndim;p++)teInds[p]=nInds[p+ndim-2];
//				for(int p=0;p<ndim;p++)thInds[p]=nInds[p];thInds[ind1]=k;
//				for(int p=0;p<ten.ndim;p++)	teInds[p]=nInds[p+ndim-1];teInds[ind2]=k;
//				printf("i=%d\tret=%lf=%lf*%lf\n",j,ret.data[j],el(thInds),ten.el(teInds));
				ret.data[j]+=el(thInds)*ten.el(teInds);
			}
		delete [] nInds;
		delete [] thInds;
		delete [] teInds;

		return ret;
	}
	else
		return Ntensor();
}

int *mm(int v1,int v2)
{
	int * ret=new int[2];
	ret[0]=v1;ret[1]=v2;
return ret;
}

int *mN(int v1,int col)
{
	int * ret=new int[col];
	for(int j=0;j<col;j++)ret[j]=v1;
return ret;
}

double *ReadM()
{
	double * ret=new double[10];

	//ret[0]=v1;ret[1]=v2;
return ret;
}

//++++++++++++++++++++++++++++ Nvector ++++++++++++++++++++++++++++++++++++++
Nvector::Nvector()
{
}

Nvector::Nvector(const Nvector & cpy)
{
	ndim=1;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
	nels=cpy.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=cpy.data[j];
}
Nvector::Nvector(const Ntensor & cpy)
{
	if(cpy.ndim==1)
	{
		ndim=1;
		dims=new int[ndim];
		for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
		nels=cpy.nels;
		data=new double[nels];
		for(int j=0;j<nels;j++)data[j]=cpy.data[j];
	}
}

Nvector::~Nvector()
{
}

Nvector::Nvector(int dim,double *i_inp)
:Ntensor(1,mN(dim,1),i_inp)
{
}
Nvector::Nvector(int dim,int type)
:Ntensor(1,mN(dim,1),type)
{
}
std::ostream & operator <<(std::ostream &os, Nvector t)
{
	for(int j=0;j<t.nels;j++)os<<t.data[j]<<"\t";
	os<<std::endl;
	return os;

}

double & Nvector::operator ()(int ind)
{
	return el(ind-1);
}
Nmatrix Nvector::toMatrix3()
{
	Nmatrix ret(3,0);
	if(dims[0]==6)
	{
		ret.data=new double [9];
		ret.data[0]=data[0];
		ret.data[4]=data[1];
		ret.data[8]=data[2];
		ret.data[5]=ret.data[7]=data[3];
		ret.data[2]=ret.data[6]=data[4];
		ret.data[1]=ret.data[3]=data[5];
	}
	return ret;
}

//++++++++++++++++++++++++++++ Nmatrix ++++++++++++++++++++++++++++++++++++++
Nmatrix::Nmatrix()
{
}

Nmatrix::Nmatrix(const Nmatrix & cpy)
{
	ndim=2;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
	nels=cpy.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=cpy.data[j];
}

Nmatrix &Nmatrix::operator =(const Nmatrix & ten)
{
	ndim=ten.ndim;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=ten.dims[j];
	nels=ten.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=ten.data[j];

	return *this;
}

Nmatrix::Nmatrix(const Ntensor & cpy)
{
	ndim=2;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
	nels=cpy.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=cpy.data[j];
}

Nmatrix::~Nmatrix()
{
}

Nmatrix::Nmatrix(int dim,int type)
:Ntensor(2,mm(dim,dim),type)
{
}
Nmatrix::Nmatrix(int dim,double *i_inp)
:Ntensor(2,mm(dim,dim),i_inp)
{
}
void Nmatrix::show(char *c1,char *c2)
{
	for(int j=0;j<dims[1];j++)printf("--------");
	printf("\n");
	int Nu=0;

	char * c=new char[40];sprintf(c,"%s\t",c1);
	for(int j=0;j<dims[0];j++)
	{
		for(int k=0;k<dims[1];k++)Nu=printf(c,el(mm(j,k)));
		printf("\n");
	}

	for(int j=0;j<(dims[1]-1)*8+Nu;j++)printf("-");
	printf("\n");
}

void Nmatrix::show(int n,int m,int k, int l)
{
	for(int j=0;j<dims[1];j++)printf("--------");
	printf("\n");
	int Nu=0;

	char * c=new char[40];sprintf(c,"%%%d.%dlf\t",n,m);
	for(int j=0;j<dims[0];j++)
	{
//		Nu=0;
		for(int k=0;k<dims[1];k++)Nu=printf(c,el(mm(j,k)));
		printf("\n");
	}

	for(int j=0;j<(dims[1]-1)*8+Nu;j++)printf("-");
	printf("\n");
}
std::ostream & operator <<(std::ostream &os, Nmatrix t)
{
	for(int j=0;j<t.dims[1];j++)os<<"--------";
	os<<std::endl;
	int Nu=0;

	for(int j=0;j<t.dims[0];j++)
	{
//		Nu=0;
		for(int k=0;k<t.dims[1];k++)os<<t.el(mm(j,k))<<"\t";
		os<<std::endl;
	}
	Nu=8;

	for(int j=0;j<(t.dims[1]-1)*8+Nu;j++)os<<"-";
	os<<std::endl;

	return os;

}
double & Nmatrix::operator ()(int ind1,int ind2)
{
	int*pind=new int[2];
	pind[0]=ind1-1;pind[1]=ind2-1;
	double &ret=el(pind);
	delete [] pind;
	return ret;
}
double Nmatrix::tr()
{
	double ret=0;
	for(int j=0;j<dims[0];j++)
		ret+=el(mm(j,j));
	return ret;
}
double Nmatrix::det()
{
	if(dims[0]==2)
		return (*this)(1,1)*(*this)(2,2)-(*this)(1,2)*(*this)(2,1);
	else if(dims[0]==3)
		return (*this)(1,1)*((*this)(2,2)*(*this)(3,3)-(*this)(2,3)*(*this)(3,2))
			  -(*this)(1,2)*((*this)(2,1)*(*this)(3,3)-(*this)(2,3)*(*this)(3,1))
			  +(*this)(1,3)*((*this)(2,1)*(*this)(3,2)-(*this)(3,1)*(*this)(2,2));
	else
		return -1;
}
Nvector Nmatrix::toVector6()
{
	Nvector ret(6,0);
	if(dims[0]==3 && dims[1]==3)
	{
		ret.data=new double [6];
		ret.data[0]=data[0];
		ret.data[1]=data[4];
		ret.data[2]=data[8];
		ret.data[3]=data[5];
		ret.data[4]=data[2];
		ret.data[5]=data[1];
	}
	return ret;
}

Ntensor4 Nmatrix::toTensor4x3()
{
	int test;
	Ntensor4 ret(3,0);
	if(dims[0]==6 && dims[1]==6)
	{
		int *inds;
		int l,m;
		ret.data=new double [81];
		for(int j=0;j<81;j++)
		{
			inds=ret.ind(j);
			if(inds[0]==inds[1])l=inds[0]+1;
			else				l=7-inds[0]-inds[1];
			if(inds[2]==inds[3])m=inds[2]+1;
			else				m=7-inds[2]-inds[3];
			test=ret.el(inds)=(*this)(l,m);
		}
		delete [] inds;
	}
	return ret;
}

Ntensor3 Nmatrix::toTensor3x3()
{
	int test;
	Ntensor3 ret(3,0);
	if(dims[0]==6 && dims[1]==6)
	{
		int *inds;
		int l,m;
		ret.data=new double [27];
		for(int j=0;j<27;j++)
		{
			inds=ret.ind(j);
			l=inds[0]+1;
			if(inds[1]==inds[2])m=inds[1]+1;
			else				m=7-inds[1]-inds[2];
//			if(l<4)
				test=ret.el(inds)=(*this)(l,m);
		}
		delete [] inds;
	}
	return ret;
}

//++++++++++++++++++++++++++++ Ntensor3 ++++++++++++++++++++++++++++++++++++++
Ntensor3::Ntensor3()
{
}

Ntensor3::Ntensor3(const Ntensor3 & cpy)
{
	ndim=3;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
	nels=cpy.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=cpy.data[j];
}
Ntensor3 &Ntensor3::operator =(const Ntensor3 & ten)
{
	ndim=ten.ndim;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=ten.dims[j];
	nels=ten.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=ten.data[j];

	return *this;
}

Ntensor3::Ntensor3(const Ntensor & cpy)
{
	if(cpy.ndim==3)
	{
		ndim=3;
		dims=new int[ndim];
		for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
		nels=cpy.nels;
		data=new double[nels];
		for(int j=0;j<nels;j++)data[j]=cpy.data[j];
	}
}

Ntensor3::~Ntensor3()
{
}

Ntensor3::Ntensor3(int dim,double *i_inp)
:Ntensor(3,mN(dim,4),i_inp)
{
}
double & Ntensor3::operator ()(int ind1,int ind2,int ind3)
{
	int*pind=new int[3];
	pind[0]=ind1-1;pind[1]=ind2-1;pind[2]=ind3-1;
	double &ret=el(pind);
	delete pind;
	return ret;
}
Nmatrix Ntensor3::toMatrix3x6()
{
	Nmatrix ret(6,0);
	if(dims[0]==3 && dims[1]==3 && dims[2]==3)
	{
		int *inds;
		int l,m;
		ret.data=new double [36];
		for(int j=0;j<81;j++)
		{
			inds=ind(j);
			l=inds[0]+1;
			if(inds[1]==inds[2])m=inds[1]+1;
			else				m=7-inds[1]-inds[2];
//			if(l<4)
				ret(l,m)=el(inds);
//			else
//				ret(l,m)=0;
		}
		delete [] inds;
	}
	return ret;
}

void Ntensor3::show6(char *c1,char *c2)
{
	Nmatrix view=toMatrix3x6();
	view.show(c1,c2);
}

void Ntensor3::show6(int n,int m,int k, int l)
{
	Nmatrix view=toMatrix3x6();
	view.show(n,m,k,l);
}



//++++++++++++++++++++++++++++ Ntensor4 ++++++++++++++++++++++++++++++++++++++
Ntensor4::Ntensor4()
{
}

Ntensor4::Ntensor4(const Ntensor4 & cpy)
{
	ndim=4;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
	nels=cpy.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=cpy.data[j];
}
Ntensor4 &Ntensor4::operator =(const Ntensor4 & ten)
{
	ndim=ten.ndim;
	dims=new int[ndim];
	for(int j=0;j<ndim;j++)dims[j]=ten.dims[j];
	nels=ten.nels;
	data=new double[nels];
	for(int j=0;j<nels;j++)data[j]=ten.data[j];

	return *this;
}

Ntensor4::Ntensor4(const Ntensor & cpy)
{
	if(cpy.ndim==4)
	{
		ndim=4;
		dims=new int[ndim];
		for(int j=0;j<ndim;j++)dims[j]=cpy.dims[j];
		nels=cpy.nels;
		data=new double[nels];
		for(int j=0;j<nels;j++)data[j]=cpy.data[j];
	}
}

Ntensor4::~Ntensor4()
{
}

Ntensor4::Ntensor4(int dim,double *i_inp)
:Ntensor(4,mN(dim,4),i_inp)
{
}
double & Ntensor4::operator ()(int ind1,int ind2,int ind3,int ind4)
{
	int*pind=new int[4];
	pind[0]=ind1-1;pind[1]=ind2-1;pind[2]=ind3-1;pind[3]=ind4-1;
	double &ret=el(pind);
	delete pind;
	return ret;
}
Nmatrix Ntensor4::toMatrix6()
{
	Nmatrix ret(6,0);
	if(dims[0]==3 && dims[1]==3 && dims[2]==3 && dims[3]==3)
	{
		int *inds;
		int l,m;
		ret.data=new double [36];
		for(int j=0;j<81;j++)
		{
			inds=ind(j);
			if(inds[0]==inds[1])l=inds[0]+1;
			else				l=7-inds[0]-inds[1];
			if(inds[2]==inds[3])m=inds[2]+1;
			else				m=7-inds[2]-inds[3];
			ret(l,m)=el(inds);
		}
		delete [] inds;
	}
	return ret;
}

void Ntensor4::show6(char *c1,char *c2)
{
	Nmatrix view=toMatrix6();
	view.show(c1,c2);
}

void Ntensor4::show6(int n,int m,int k, int l)
{
	Nmatrix view=toMatrix6();
	view.show(n,m,k,l);
}

