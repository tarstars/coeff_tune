#pragma once
#ifndef PT
#define PT

#include <iostream>

using namespace std;

class PiezoTensor{
  double dat[3][3][3];
 public:
  PiezoTensor();

  double& operator()(int p, int q, int r){return dat[p][q][r];}
  const double& operator()(int p, int q, int r)const {return dat[p][q][r];}

  friend ostream& operator<<(ostream& os, const PiezoTensor&);
	
 
 void show(){
	cout<<"e15 is"<<dat[0][0][2];}


};

ostream& operator<<(ostream& os, const PiezoTensor&);

#endif
