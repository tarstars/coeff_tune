#include "Ncomplex.h"
//#include "Nvalue.h"
#include "Ntensor.h"
#include "Utils.h"
#include "PovrayMaker.h"
#include"Swarm.h"
#include"Read.h"
#include <time.h>

double* convD(double data0[])
{
	int length=(sizeof data0)/(sizeof(double));
double * data1=new double[length];
for(int j=0;j<length;j++)data1[j]=data0[j];
return data1;
}


class coeffTune: public functional
{
    Direction dir;
//    Nmatrix Christofel;
    RawData table;
public:
    coeffTune(const std::vector<double> &bv,const std::vector<double> &ev)
        :functional(bv,ev),dir(0,0){setDirS(0,0);loadTable();}
    coeffTune(double p,double t,const std::vector<double> &bv,const std::vector<double> &ev)
        :functional(bv,ev),dir(t,p){setDirS(p,t);loadTable();}

    void loadTable(char *path1=0, char *path2=0, char *path3=0)
    {
        if (!table.data.empty())table.clear();
        if(path3)table.read(path1, path2, path3);
        else if (path1) table.read(path1);
        else
        {
            table.phi.push_back(0);
            table.theta.push_back(0);
            table.data[Direction(0,0)]=vec3(7328.6,3590.4,3590.4);
        }
    }

    void setDirS(double phi, double theta)
    {
        dir.phi=phi;
        dir.theta=theta;
//        printf("++++++++++++ Direction %lf, %lf ++++++++++++\n",phi,theta);
    }



    double check(bees *p)
    {
        double dist=0;

            Ntensor4 Elastic=makeElasticTensor8(p->coord[0], p->coord[1], p->coord[2], p->coord[3],p->coord[4],p->coord[5], p->coord[6], p->coord[7]);
//            printf("Elastic\n");
//            Elastic.show6();

            Ntensor3 Piezo=makePiezoTensor5(p->coord[8], p->coord[9], p->coord[10], p->coord[11], p->coord[12]);
//            printf("Piezo\n");
//            Piezo.show6();
//            Piezo.show();

            Nmatrix Permit=makePermitTensor2(p->coord[13],p->coord[14]);
//            printf("Permittivity\n");
//            Permit.show();

            double epsilon0=8.8542e-12;

            Nvector Direction=makeDirection3S(1,dir.phi,dir.theta);
//            printf("Direction\n");
//            Direction.show();

            Ntensor ji=Piezo.mult(Direction,2).mult(Direction,0);
//            printf("ij\n");
//            ji.show();

            Nmatrix Christofel=Elastic.mult(Direction,2).mult(Direction,1)+ji.extm(ji)/(Permit.mult(Direction,1).mult(Direction,0))/epsilon0;
//            printf("Christofel\n");
//            Christofel.show();

        Nvector velocities=eigval3(Christofel);
		if ((velocities(1)!=velocities(1))||(velocities(2)!=velocities(2))||(velocities(3)!=velocities(3))) 
		{
			//printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!!!!!!!!!!!!!! %lf\n",velocities(1));
			return INFINITY;
		}
//        printf("velocities: %lf, %lf, %lf\n",sqrt(velocities(1)/4642.8),sqrt(velocities(2)/4642.8),sqrt(velocities(3)/4642.8));
//        printf("table");table.data[dir].show();
        vec3 vel(table.data[dir][0]-sqrt(velocities(1)/4642.8),table.data[dir][1]-sqrt(velocities(2)/4642.8),table.data[dir][2]-sqrt(velocities(3)/4642.8));
        dist=vel.abs2();

        return dist;
    }

};


int main(int argc, char* argv[])
{
    std::vector <double> bv(15,0);
    std::vector <double> ev(8,30e10);
    ev.insert(ev.end(),5,5);
    ev.insert(ev.end(),2,50);
    coeffTune tune(bv,ev);

    double l[]={19.886e10, 5.467e10, 6.799e10, 0.783e10,19.886e10,6.799e10, 23.418e10, 5.985e10,3.655, 2.407, 0.328, 0.328, 1.894,44.9,26.7};
    std::vector <double> lv(l,l+15);
    bees LiNbO3(lv);
    LiNbO3.show("LiNbO3 ");
    printf("check: %lf\n",tune.check(&LiNbO3));


    double pr[]={136258430738.242740, 140220954008.606230, 129080477309.488200, 148334604937.894840, 138848536637.470610, 125173802911.465810, 134538102359.080760, 165589159825.434110, 2.041917, 2.817240, 1.249886, 2.805277, 1.690588, 30.450911, 24.563433};
    std::vector <double> prv(pr,pr+15);
    bees kosiak(prv);
    kosiak.show("kosiak ");
    printf("check: %lf\n",tune.check(&kosiak));




printf("\n+++++++++++++++++++++++++++++++\n");
	printf("Hello World!\n");
	printf("%d\n",'\n');
	srand ( time(NULL) );
	

coeffTune problem(bv,ev);
problem.show("problem ");


swarm hive(30,&problem,0.1,0.1,0.1,0.0);
hive.show("Hive");
hive.move();
hive.communicate();
hive.show("Moved Hive");

bees *result=hive.fly(0.001,-1);
result->show("RESULT: ");
printf("Value: %lf\n",result->value);
if(result->value>2000)printf("ERROR!!!ERROR!!!ERROR!!!ERROR!!!\nERROR!!!ERROR!!!ERROR!!!ERROR!!!\nERROR!!!ERROR!!!ERROR!!!ERROR!!!");

printf("Error : ");
for(unsigned int k=0;k<LiNbO3.size();k++)
    printf("%3.1lf, ",100*(result->coord[k]-LiNbO3.coord[k])/LiNbO3.coord[k]);
printf("\n");


//RESULT: 115046433405.099240, 250460521369.044590, 125030864744.834820, 270201824643.679870, 198694741670.008970, 72536885293.658554, 87099932900.768311, 59850205556.540550, 2.959473, 2.423008, 2.103074, 1.623456, 1.059869, 11.956804, 17.458574,
//RESULT: 223031322864.615510, 143490815334.895600, 111316836619.472000, 225423682365.720180, 152242212945.748170, 75975373444.960602, 125941338771.734450, 59850205585.755585, 1.758021, 3.555711, 1.068858, 3.387644, 3.715350, 6.472005, 30.087337,
double res1[]={115046433405.099240, 250460521369.044590, 125030864744.834820, 270201824643.679870, 198694741670.008970, 72536885293.658554, 87099932900.768311, 59850205556.540550, 2.959473, 2.423008, 2.103074, 1.623456, 1.059869, 11.956804, 17.458574};
std::vector <double> res1v(res1,res1+15);
bees result1(res1v);
//LiNbO3.show("LiNbO3 ");
printf("check: %lf\n",tune.check(&result1));

double res2[]={223031322864.615510, 143490815334.895600, 111316836619.472000, 225423682365.720180, 152242212945.748170, 75975373444.960602, 125941338771.734450, 59850205585.755585, 1.758021, 3.555711, 1.068858, 3.387644, 3.715350, 6.472005, 30.087337};
std::vector <double> res2v(res2,res2+15);
bees result2(res2v);
//LiNbO3.show("LiNbO3 ");
printf("check: %lf\n",tune.check(&result2));

double res3[]={213196348743.295040, 155047087332.067900, 184414815022.437960, 67162336216.048935, 141161093223.842860, 138992054503.078700, 93920856409.207596, 59850205573.099617, 0.837712, 1.929626, 3.384956, 1.227865, 3.304281, 19.574077, 25.845072};
std::vector <double> res3v(res3,res3+15);
bees result3(res3v);
//LiNbO3.show("LiNbO3 ");
printf("check: %lf\n",tune.check(&result3));


/*



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
*/
    return 0;
}
