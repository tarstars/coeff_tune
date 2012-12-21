#include"Read.h"
#include"Swarm.h"
#include <time.h>


int main()
{

printf("Hello World!\n");
printf("%d\n",'\n');

/*
//char *path=new char;
//path="../../../linbo3_data/linbo3_fqs.txt";

RawData *FirstFile=new RawData;

FirstFile->read("../../../linbo3_data/linbo3_sqs_room_woc.txt","../../../linbo3_data/linbo3_sqs_0c_sw.txt","../../../linbo3_data/linbo3_ql_0c_sw.txt");
FirstFile->show(1);
*/


	srand ( time(NULL) );
double b[]={-1,-2,-3,-4};
std::vector <double> bv(b,b+4);
double e[]={1,2,3,4};
std::vector <double> ev(e,e+4);

bees init(bv,ev);
init.show("init ");

functional problem(bv,ev);
problem.show("problem ");


swarm hive(10,&problem);
hive.show("Hive");
hive.communicate();
hive.move();
hive.show("moved Hive");
hive.fly();


return 0;
}