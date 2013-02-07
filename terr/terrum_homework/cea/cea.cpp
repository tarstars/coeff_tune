#include <iostream>

using namespace std;

int main(){

  int a, b;

  cout << "Please, input first number..." << endl;
  cin >> a;
  cout << "Please, input second number..." << endl;
  cin >> b;

  int p, q;
  
  for(p = a, q = b ; p > 0 && q > 0 ; ){
    if(p >= q){
      p = p - q;
    }
    else{
      q = q - p;
    }
  }
  
  if(p == 0)
    cout << "gcd(" << a << ", " << b << ") = " << q << endl;
  else
    cout << "gcd(" << a << ", " << b << ") = " << p << endl;
}
