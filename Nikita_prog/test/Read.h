#ifndef Read
#define Read


#include<map>
#include<vector>
#include<fstream>
#include"stdio.h"

class Direction{
public:
	double theta,phi;
	
	Direction(double i_t,double i_p):theta(i_t),phi(i_p){};
	bool operator <(const Direction &d) const
	{
		if (theta<d.theta)
			return true;
		else if (theta>d.theta)
			return false;
		else if (phi<d.phi)
			return true;
		else
			return false;
	}
};


struct DirInfo{
	std::vector <double> v;
	Direction dir;
	
	DirInfo()
		:dir(0,0)
		{
			v.push_back(0);
			v.push_back(0);
			v.push_back(0);
		}
	DirInfo(double i_theta, double i_phi, double i_v1, double i_v2, double i_v3)
		:dir(i_theta,i_phi)
		{
			v.push_back(i_v1);
			v.push_back(i_v2);
			v.push_back(i_v3);
		}
	void set(double i_theta, double i_phi,double i_v, int n)
		{	
			dir.phi=i_phi;dir.theta=i_theta;
			v[n]=i_v;
		}
};

class vec3
{
	public: std::vector<double> components;
	vec3(){components.push_back(0);components.push_back(0);components.push_back(0);}
	vec3(double a,double b,double c){components.push_back(a);components.push_back(b);components.push_back(c);}
	vec3(double a,int i){components.push_back(0);components.push_back(0);components.push_back(0);components[i]=a;}
	double &operator [](int i){return components[i];}
	void show(){printf("\t\t%lf, %lf, %lf\n",components[0],components[1],components[2]);}
	bool operator <(const vec3 &d) const
	{
		return components<d.components;
	}
};


class RawData{

private:
	double *m;
	int I,J;
	void addData(double,double,double,int);
//	std::map < Direction, vec3 >::iterator pdata;

public:
	std::map < Direction, vec3 > data;
	std::vector<double> v;
	std::vector<double> phi;
	std::vector<double> theta;
	
	RawData()
	{
//		pdata = data.begin();
		I=0;
		J=0;
		m=NULL;
	}
	~RawData(){if (m) delete [] m;};

	void read(char *path,int NV=0);
	void read(char *path1, char *path2, char *path3);
	void show(int param=0);
	void Hello();
	
};

#endif