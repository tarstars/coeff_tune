#include "Swarm.h"


double rndnum(int rg=0)
{
	if (rg) return rg;
	double x=(double(rand())/RAND_MAX);
	return x;
}
//-------------------------------------------------------
//-----------------BEES----------------------------------
//-------------------------------------------------------

bees::bees(const std::vector<double> & b,const std::vector<double> & e):inert(1), conf(1), trust(1),speed(b.size(),0),value(0),memory_value(0)
{
	if (b.size()!=e.size()) throw "b!=e in bee init";
 	for(unsigned int j=0;j<b.size();j++)
		coord.push_back(b[j]+(e[j]-b[j])*rndnum());
	memory_place=coord;
}
bees::bees(const bees & b,const bees & e):inert(1), conf(1), trust(1),speed(b.size(),0),value(0),memory_value(0)
{
	if (b.size()!=e.size()) throw "b!=e in bee init";
 	for(unsigned int j=0;j<b.size();j++)
		coord.push_back(b.coord[j]+(e.coord[j]-b.coord[j])*rndnum());
	memory_place=coord;
}
void bees::random(const std::vector<double> & b,const std::vector<double> & e)
{
	if (b.size()!=e.size()) throw "b!=e in bee rand";
 	for(unsigned int j=0;j<coord.size();j++)
		coord[j]=b[j];
	memory_place=coord;
}
void bees::move(std::vector<double> rumor)
{
	double velocity=0;
 	for(unsigned int j=0;j<coord.size();j++)
	{
		speed[j]=inert*speed[j]+conf*(memory_place[j]-coord[j])*rndnum()+trust*(rumor[j]-coord[j])*rndnum();
		coord[j]+=speed[j];
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
}


//-------------------------------------------------------
//-----------------functional----------------------------
//-------------------------------------------------------
functional::functional(const std::vector<double> & b,const std::vector<double> & e)
:begin(b),end(e)
{
	if (begin.size()!=end.size()) throw "b!=e in functional init";
};
double functional::check(bees *p)
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
swarm::swarm(unsigned int pop,functional* prob)
:bestBee(prob->begin.coord.size(),0),center(prob->begin.coord.size(),0),population(pop)
{
	problem=prob;
	bees *pointer;
	for(unsigned int i=0;i<pop;i++)
	{
		pointer=new bees(problem->begin,problem->end);
		pointer->value=problem->check(pointer);
		pointer->memory_value=pointer->value;
		Bee.push_back(pointer);
		for(unsigned int j=0;j<Bee[i]->coord.size();j++)
		{
			center.coord[j]+=Bee[i]->coord[j]/pop;
		}
		Bee[i]->value=problem->check(Bee[i]);
//		Bee[i]();
//		Bee[i]->memory_value
	}
	bestBee=*(Bee[1]);
	communicate();
	
	
	file=new QFile(QString("HiveTrace.txt"));
	if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		printf("%s\n",QString("Файл не открыт"));
		throw QString("Файл не открыт");
	}
	textOut.setDevice(file);

//	textOut<<"Hive trace"<<"\n";
}


void swarm::show(char*c)
{
	printf("---------------------------\n");
	printf(c);
	printf("\n");
	problem->show("problem");
	printf("\n");
	for(unsigned int i=0;i<Bee.size();i++)
		{printf("bee %d:",i);Bee[i]->show("");printf("value %lf\n",Bee[i]->value);}
	printf("population %d\n",population);
	printf("\n");
	printf("bestBee :");bestBee.show("");printf("value %lf\n",bestBee.memory_value);
	printf("---------------------------\n");
}

void swarm::communicate()
{
	printf("----------------------\nCommunication\n");
	for(unsigned int i=0;i<Bee.size();i++)
		{
//			Bee[i]->value=problem->check(Bee[i]);
			if (Bee[i]->memory_value>Bee[i]->value) {Bee[i]->memory_value=Bee[i]->value; printf("Bee %d: I'm improoving!\n",i);}
			if (bestBee.memory_value>Bee[i]->memory_value) {bestBee=*(Bee[i]); printf("Bee %d: I'm the best!\n",i);}
		}
//		center.value=problem->check(&center);
//		if (center.memory_value>center.value) {center.memory_value=center.value; printf("Center: I'm improoving!\n");}
//		if (bestBee.memory_value>center.memory_value) {bestBee=center; printf("Center: I'm the best!\n");}
}

void swarm::move()
{
	printf("----------------------\nMovement\n");
	center=bees(bestBee.coord.size(),0);
	for(unsigned int i=0;i<Bee.size();i++)
	{
		Bee[i]->move(bestBee.coord);
		for(unsigned int j=0;j<Bee[i]->coord.size();j++)
		{
			textOut<<Bee[i]->coord[j]<<"\t";
			center.coord[j]+=Bee[i]->coord[j]/Bee.size();
		}
		textOut<<"\n";
		Bee[i]->value=problem->check(Bee[i]);
	}
	printf("Hive is in\n");
	center.show();
}

bees* swarm::fly(int Nsteps)
{
	int step=0;
	while ((bestBee.value>0.1)&&(step<Nsteps))
	{
		step++;
		move();
		communicate();
		printf("Step %d: current best %lf\n",step,bestBee.value);
	}
return Bee[0];
}
