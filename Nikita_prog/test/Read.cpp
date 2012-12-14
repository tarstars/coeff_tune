#include "Read.h"
#include<sstream>
#include<set>
#include<vector>

void RawData::Hello(){printf("Hellow RawData\n");}
void RawData::read(char *path,int NV)
{
//		std::ifstream ist(path);
		FILE * file;
		file=fopen(path,"r");

		if (!file)
			printf("Bad stream\n");

		int sc=0,lind=0,off=1;
		char ival=' ',pval=' ';
		
		std::stringstream text(std::stringstream::in | std::stringstream::out);
	std::string perms ("0123456789. \r\t\n");
	std::set<char> permset(perms.begin(), perms.end());
	//std::vector<double> *row0=new std::vector<double>, *row1=new std::vector<double>;

		double val=0;
		int flag=3,columns=0;
		if (phi.size()!=0)
			{phi.clear();theta.clear();v.clear();}
			
		while(!feof(file))
		{
			lind++;
			pval=ival;
			sc=fscanf(file,"%c",&ival);
			if (permset.find(pval)!=permset.end())
				if ((ival=='0')||((ival<='9')&&(ival>='1'))||(ival=='.'))
					if (text.eof()) {text.clear();
						text<<ival;}
					else
						text<<ival;
				else if ((ival==' ')||(ival=='\t'))    //||(ival=='\r'))
					if (text.eof())
						{}
					else if (flag==0)
						{text>>val;                            printf("%lf, ",val);
						v.push_back(val);
//							printf("%d, %d, %d\n",(v.size()-1),(phi.size()-1),(v.size()-1)%(phi.size()-1)+1);
						addData(theta.back(),phi[(v.size()-1)%(phi.size()-off)+off],val,NV);
						flag=0;}
					else if(flag==1)
						{text>>val;                            printf("|%lf|, ",val);
						theta.push_back(val);
						flag=0;}
					else if(flag==3)
						{text>>val;                            printf("**%lf, ",val);
						phi.push_back(val);columns++;		
						flag=3;}
					else printf("Whatthefuc????");
				else if (ival=='\n')
				{
//					printf("\n!n, flag=%d\n",flag);
					if (flag==3)
					{
						if (phi.size()>5)
						{
							if (!text.eof())
								{
									flag=1;
									text>>val;                  printf("**%lf!!\n",val);
									phi.push_back(val);columns++;
								}
							else
								{
									flag=1;
																printf("!!!\n");
								}
						}
						else
						{
							//	text>>val;                 		printf("**%lf!!\n",val);
								phi.clear();//printf("\nclear, %d\n",phi.size());
						}
					}
					else
					{
						if (!text.eof())
						{
							flag=1;
							text>>val;                          printf("%lf!\n",val);
							v.push_back(val);
//							printf("%d, %d, %d   %lf\n",(v.size()-1),(phi.size()-1),(v.size()-1)%(phi.size()-1)+1,phi[13]);
							addData(theta.back(),phi[(v.size()-1)%(phi.size()-off)+off],val,NV);
						}
						else
						{
							flag=1;
														printf("!!!\n");
						}
					}
				}
				else
					{printf("\nFuuu=%c(%d)! %d\n",ival,ival,lind);if(ival=='\r')printf("!r");}
			else
				{printf("fuu! %c -- %c(%d) %d\n",pval,ival,ival,lind);if (text.eof())printf("EOFu!");}
			
		}





//		while(ist>>ival)
/*
		while(!feof(file))
		{
			lind++;
			pval=ival;
			sc=fscanf(file,"%c",&ival);
//			printf("%c,%c",ival,pval);
//			printf("=%d ",int(ival));
			if (permset.find(ival)!=permset.end())
				if (permset.find(pval)!=permset.end())
					if (pval!='\n')
						text<<ival;
					else
						while(text>>val)
						{
							printf("%lf, ",val);
							row.push_back(val);
						}
				else
					printf("fuu! %c -- %d\n",pval,lind);
			else
				printf("Fuuu=%c! %d\n",ival,lind);
			
//			printf("%lf",inum);
//			printf("\n%d\n",sc);
//			printf("%lf",inum);
//			printf("\n%d\n",sc);
		}
*/



		printf("----------------\nstring left\n%s\n---------------\n\n",text.str().c_str());
		
/*
		double val;
		while(text>>val)
		{
			printf("%lf\n",val);
		}
*/
		fclose(file);
}

void RawData::addData(double theta,double phi,double val,int nv)
{
		vec3 vs;
		Direction di(theta,phi);
		
//		printf("[%lf, %lf]: %lf (%d)\n",theta,phi,val,nv);
//		printf("[%lf, %lf]: %lf (%d)  -> %lf\n",di.theta,di.phi,val,nv,vs[nv]);
			vs=data[di];
//			vs.show();
			vs[nv]=val;
		data[di]=vs;
//			vs.show();
		
		/*
		printf("[%lf, %lf]: %lf, %lf, %lf\n",di.theta,
											 di.phi,
											 data[di][0],
											 data[di][1],
											 data[di][2]);
		*/

}

void RawData::show(int param)
{
printf("______________________________\n");
std::map < Direction, vec3 >::iterator pdata;
pdata=data.begin();
unsigned int i=0;
while(i<data.size())
	{
		printf("[%lf, %lf]: %lf, %lf, %lf\n",pdata->first.theta,pdata->first.phi,(*pdata).second[0],(*pdata).second[1],(*pdata).second[2]);
		++pdata;printf("aga\n");++i;
	}
}

void RawData::read(char *path1, char *path2, char *path3)
{
	read(path1,0);
	read(path2,1);
	read(path3,2);
}
