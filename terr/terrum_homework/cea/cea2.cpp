#include <iostream>
using namespace std;

int main(){

  int a, b;
  
  cout << "Please, input first number..." << endl;
  cin >> a;
  cout << "Please, input second number..." << endl;
  cin >> b;
  
  int p, q, d = 1;
  
  for(p = a, q = b ; p > 0 && q > 0 ; ){
    if(p%2 == 0 && q%2 == 0){
      d *= 2;
      p = p / 2;
      q = q / 2;
    }
    else if (p%2 == 0 && q%2 == 1){
      p = p / 2;
    }
    else if (p%2 == 1 && q%2 == 0){
      q = q / 2;
    }
    else if(p >= q && p%2 == 1 && q%2 == 1){
      p = p - q;
    }
    else if(q >= p && p%2 == 1 && q%2 == 1){
      q = q - p;
    }
  }
  
  if(p == 0)
    cout << "gcd(" << a << ", " << b << ") = " << d*q << endl;
  else
    cout << "gcd(" << a << ", " << b << ") = " << d*p << endl;
}
