#include "sa-acop.h"

double * TuneConstants(double * constants, param parameters, gsl_rng * generator){
	
	ofstream out ("out.dat");
	
	double discrepancy;
	double tempDiscrepancy;
	double bestDiscrepancy;
	double deltaDisc;
	double initDiscrepancy;

	double T;
	double p, prob;
	
	double tempConstants[4];
	double bestConstants[4];
		
	T=parameters.initTemperature;
	
	for (int i=0; i<4; i++) bestConstants[i]=constants[i];
	
	initDiscrepancy=Discrepancy(constants);
	bestDiscrepancy=initDiscrepancy;
	
	int exit=0;	
	for (int k=1; k<parameters.iterations; k++){
			
		cout<<" in progress... "<<100*k/parameters.iterations <<"%"<<"\r";
		do{
			for(int i=0; i<4; i++) tempConstants[i]=constants[i];
			tempDiscrepancy=Discrepancy(tempConstants);
			
			Randomize(constants, T, generator);
			discrepancy=Discrepancy(constants);
		
			deltaDisc=discrepancy-tempDiscrepancy;
			
			p=exp(-deltaDisc/T);
			prob=gsl_ran_flat(generator, 0.0,1.0);
			
				if (p>prob){
					exit=1;
					//E+=DE;
					//E=newE;
					
					if (discrepancy<bestDiscrepancy){ 
						bestDiscrepancy=discrepancy;
						for (int i =0; i<4; i++) bestConstants[i]=constants[i];
							
						//out<<k<<"\t"<<constants[0]<<"\t"<<constants[1]<<"\t"<<constants[2]<<"\t"<<constants[3]<<"\t"<<discrepancy<<"\n";
						
					}
				}
				else {
					exit=0;
					for (int i =0; i<4; i++) constants[i]=tempConstants[i];
				}
			}while (!exit); 
		
			
			if (parameters.cool) T=parameters.initTemperature/log(k+1);
						
		}
		
		cout<<endl;
		cout<<"initial discrepancy: "<<initDiscrepancy<<"\t"<<"final discrepancy: "<<bestDiscrepancy<<"\n"<<"To: "<<parameters.initTemperature<<"\t\t"<<"T fin: "<< T<<endl<<endl;
		cout<<bestConstants[0]<<"\t"<<bestConstants[1]<<"\t"<<bestConstants[2]<<"\t"<<bestConstants[3]<<endl;
		
	
	return constants;
}


void Randomize(double * constants, double T, gsl_rng * generator){
	int i=gsl_rng_uniform_int(generator, 4);
	//for (int i=0; i<4; i++)
	constants[i]+= gsl_ran_gaussian (generator, T);  	
}


double Cubic(double * constants, int x){
	return constants[0]*x*x*x+constants[1]*x*x+constants[2]*x+constants[3];
}

double Discrepancy(double * constants){
	double trueConstants[4]={401, 7, 16, 179};
	double discrepancy=0;
	
	for (int x=0; x<100; x++){
		discrepancy+= (Cubic(constants, x)-Cubic(trueConstants,x))*(Cubic(constants, x)-Cubic(trueConstants,x));
	}
	return discrepancy;
	
}	


