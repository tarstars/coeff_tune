#include "Swarm.h"

//-------------------------------------------------------
//-----------------BEES----------------------------------
//-------------------------------------------------------

bees::bees(const std::vector<double> & b,const std::vector<double> & e):speed(b.size(),0),inert(1), conf(1), trust(1)
{
	if (b.size()!=e.size()) throw "b!=e in bee init";
 	for(unsigned int j=0;j<b.size();j++)
		coord.push_back(b[j]+rand()*(e[j]-b[j])/RAND_MAX);
	memory=coord;
}
bees::bees(const bees & b,const bees & e):speed(b.size(),0),inert(1), conf(1), trust(1)
{
	if (b.size()!=e.size()) throw "b!=e in bee init";
 	for(unsigned int j=0;j<b.size();j++)
		coord.push_back(b.coord[j]+rand()*(e.coord[j]-b.coord[j])/RAND_MAX);
	memory=coord;
}
void bees::random(const std::vector<double> & b,const std::vector<double> & e)
{
	if (b.size()!=e.size()) throw "b!=e in bee rand";
 	for(unsigned int j=0;j<coord.size();j++)
		coord[j]=b[j];
	memory=coord;
}
void bees::move(std::vector<double> rumor)
{
 	for(unsigned int j=0;j<coord.size();j++)
	{
		speed[j]=inert*speed[j]+conf*(memory[j]-coord[j])*rand()/RAND_MAX+trust*(rumor[j]-coord[j])*rand()/RAND_MAX;
		coord[j]+=speed[j];
	}
	printf("Tweak!\n");
}
void bees::show(char*c)
{
	printf(c);
	for(unsigned int i=0;i<coord.size();i++)
		printf("%lf, ",coord[i]);
	printf("\n");
	for(unsigned int j=0;j<speed.size();j++)
		printf("%lf, ",speed[j]);
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
int functional::check(bees *p)
{
	
	return 0;
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
swarm::swarm(int pop,functional* prob):best(problem->begin,problem->end)
{
	problem=prob;
	bees *pointer;
	for(int i=0;i<pop;i++)
	{
		pointer=new bees(problem->begin,problem->end);
		Bee.push_back(pointer);
	}
}


void swarm::show(char*c)
{
	printf(c);
	for(unsigned int i=0;i<Bee.size();i++)
		{printf("bee %d:",i);Bee[i]->show("");}
	printf("\n");
}

bees* swarm::calculate()
{
	for(unsigned int i=0;i<Bee.size();i++)
	{
	//	Bee[i]->move();
	}
return Bee[0];
}
