#include "Swarm.h"


double rndnum(int rg=1)
{
    if (rg<1) return -rg;
	double x=(double(rand())/RAND_MAX);
    for(;rg>1;rg--)x*=x;
    return x;
}
//-------------------------------------------------------
//-----------------BEES----------------------------------
//-------------------------------------------------------

bees::bees(functional *probl,double in,double co,double tr, double inte,int rndp)
    :inert(in), conf(co), trust(tr), intent(inte),rndPower(rndp),value(0),memory_value(0)
{
    if (probl->begin.size()!=probl->end.size()) throw "b!=e in bee init";
    for(unsigned int j=0;j<probl->begin.size();j++)
    {
        coord.push_back(probl->begin.coord[j]+(probl->end.coord[j]-probl->begin.coord[j])*rndnum());
        speed.push_back((probl->end.coord[j]-probl->begin.coord[j])*rndnum()/100);
    }
    memory_place=coord;
    value=probl->check(this);
    memory_value=value;
}

void bees::setChar(double i, double c, double t, double in)
{
    inert=i;
    conf=c;
    trust=t;
    intent=in;
}

void bees::move(std::vector<double> rumor,std::vector<double> begin,std::vector<double> end)
{
    double velocity=0;
    for(unsigned int j=0;j<coord.size();j++)
    {
        speed[j]=inert*speed[j]+conf*(memory_place[j]-coord[j])*rndnum(rndPower)+trust*(rumor[j]-coord[j])*rndnum(rndPower)+intent*(end[j]-begin[j])*rndnum()/100;
        coord[j]+=speed[j];
        if (coord[j]<begin[j]) { coord[j]=begin[j]; speed[j]=0;}
        if (coord[j]>end[j])   { coord[j]=end[j];   speed[j]=0;}
        velocity+=speed[j]*speed[j];
    }
    printf("%lf Bzzzzzz!\n",(velocity));
}
void bees::show(char*c)
{
	printf(c);
	for(unsigned int i=0;i<coord.size();i++)
		printf("%lf, ",coord[i]);
	printf("\n");
	for(unsigned int j=0;j<speed.size();j++)
		printf("\t%lf, ",speed[j]);
	printf("\n");
    printf("\tinert: %lf, conf: %lf, trust: %lf\n",inert,conf,trust);
}


//-------------------------------------------------------
//-----------------functional----------------------------
//-------------------------------------------------------
functional::functional(const std::vector<double> & b,const std::vector<double> & e)
:begin(b),end(e)
{
	if (begin.size()!=end.size()) throw "b!=e in functional init";
}
double functional::check(bees *p)// const
{
	double dist=0;
	for(unsigned int j=0;j<p->coord.size();j++)
		dist+=p->coord[j]*p->coord[j];
	return dist;
}
void functional::show(char*c)
{
	printf(c);
	printf("\n begin ");
	for(unsigned int i=0;i<begin.size();i++)
		printf("%lf, ",begin.coord[i]);
	printf("\n end ");
	for(unsigned int i=0;i<begin.size();i++)
		printf("%lf, ",end.coord[i]);
	printf("\n");
}



//-------------------------------------------------------
//-----------------SWARM---------------------------------
//-------------------------------------------------------
swarm::swarm(unsigned int pop,functional* prob,double in,double co,double tr,double inte,int rndp)
:bestBee(prob->begin.coord.size(),0),center(prob->begin.coord.size(),0),population(pop)
{
	problem=prob;
	bees *pointer;
    printf("----------------------\nConstructing Swarm\n");
	for(unsigned int i=0;i<pop;i++)
	{
        pointer=new bees(problem,in,co,tr,inte,rndp);
		Bee.push_back(pointer);
		for(unsigned int j=0;j<Bee[i]->coord.size();j++)
		{
			center.coord[j]+=Bee[i]->coord[j]/pop;
        }
        Bee[i]->show();
    }
    bestBee=*(Bee[0]);
    center.value=problem->check(&center);
    center.memory_value=center.value;
    center.show();
    communicate();
	
	
	file=new QFile(QString("HiveTrace.txt"));
	if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
	{
        printf("Файл не открыт\n");
		throw QString("Файл не открыт");
	}
	textOut.setDevice(file);

}


void swarm::show(char*c)
{
	printf("---------------------------\n");
	printf(c);
	printf("\n");
	problem->show("problem");
	printf("\n");
	for(unsigned int i=0;i<Bee.size();i++)
        {printf("bee %d: ",i);Bee[i]->show("");printf("value %lf (%lf)\n",Bee[i]->value,Bee[i]->memory_value);}
	printf("population %d\n",population);
	printf("\n");
    printf("Hive is in : ");center.show("");printf("value %lf (%lf)\n\n",center.value,center.memory_value);
    printf("bestBee : ");bestBee.show("");printf("value %lf=%lf\n",bestBee.value,bestBee.memory_value);
    printf("---------------------------\n");
}

void swarm::communicate()
{
	printf("----------------------\nCommunication\n");
    center=bees(bestBee.coord.size(),0);
    for(unsigned int i=0;i<Bee.size();i++)
		{
            for(unsigned int j=0;j<Bee[i]->coord.size();j++)
            {
                saveBeePosition(i,j);//textOut<<Bee[i]->coord[j]<<"\t";
                center.coord[j]+=Bee[i]->coord[j]/Bee.size();
            }
            textOut<<"\n";
            if (Bee[i]->memory_value>Bee[i]->value)
            {
                Bee[i]->memory_value=Bee[i]->value;
                Bee[i]->memory_place=Bee[i]->coord;
                printf("Bee %d: I'm improoving!\n",i);
            }
            if (bestBee.memory_value>Bee[i]->memory_value)
            {
                bestBee=*(Bee[i]);
                printf("Bee %d: I'm the best!\n",i);
            }
        }
    textOut<<"\n";
    //	printf("Hive is in\n");
    //	center.show();
        center.value=problem->check(&center);
//		if (center.memory_value>center.value) {center.memory_value=center.value; printf("Center: I'm improoving!\n");}
//		if (bestBee.memory_value>center.memory_value) {bestBee=center; printf("Center: I'm the best!\n");}
}

void swarm::saveBeePosition(unsigned int beeN,unsigned int coordN)
{
    textOut<<Bee[beeN]->coord[coordN]<<"\t";
}

void swarm::move()
{
	printf("----------------------\nMovement\n");
	for(unsigned int i=0;i<Bee.size();i++)
	{
        Bee[i]->move(bestBee.coord,problem->begin.coord,problem->end.coord);
        Bee[i]->value=problem->check(Bee[i]);
    }
}

bees* swarm::fly(double threshold, int Nsteps)
{
	int step=0;
    if ((threshold<0)&&(Nsteps<0)) throw "Infinite loop in fly";
    while (((threshold<0)||(bestBee.value>threshold))&&((Nsteps<0)||(step<Nsteps)))
	{
		step++;
		move();
		communicate();
        printf("----------Step %d: current best %lf----------\n",step,bestBee.value);
	}
    bees *ret=new bees(bestBee);
return ret;
}
bees* swarm::fly(int Nsteps)
{
    return fly(-1, Nsteps);
}
