#include "simulation.h"

#include <iostream>

using ::std::cout;
using ::std::endl;

int main(void){
  
  Simulation  simulation;
  AnnealingParams params;
  
  Constants true_constants  = {50, 50, 50, 50};
  Constants to_tune_constants  = {48, 49, 51, 52};
  Constants tuned_constants;
  
  simulation.initializeRandomGenerator();
  simulation.setTrueConstants(Constants{50, 50, 50, 50});
  
  params.initialTemperature = 0.0002;  /* in arbitrary units, not a real temperature */
  params.iterationsNumber = 2E6;  /* maximum number of iterations for annealing */
  params.doCooling  = false;  /* reduce the temperature as the number of iterations grows larger */
  
  tuned_constants = simulation.tuneConstants(Constants{48, 49, 51, 52}, params);
  
  cout << endl << endl;
  
  cout << "PASSED: " << to_tune_constants;
  cout << "TUNED: " << tuned_constants;
  cout << "TRUE: " << true_constants;
  
  cout << endl;
  
  return  0;
} //  main
