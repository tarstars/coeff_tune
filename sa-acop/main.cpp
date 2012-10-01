#include "sa-acop.h"

using namespace std;

int main(){

	srand((unsigned)time(0));
	int seed=rand();

	gsl_rng * generator = gsl_rng_alloc(gsl_rng_default);
	gsl_rng_set(generator, seed);
	
	double constants[4]={50, 50, 50, 50};
	param P;
	
	P.initTemperature=0.002;
	P.iterations=10000000;
	P.cool=0;
	
	TuneConstants(constants, P, generator);

	gsl_rng_free(generator);

	return 0;
}
