// Оператор for: ввести из входного потока целое число n.
// Вывести на печать первые n чисел последовательности Фиббоначи 1,1,2,3,5,8...

#include <limits.h>
#include <cmath>
#include <iostream>
#include <string>

#define MAX_N 100

using   std::cin;
using   std::cout;
using   std::endl;
using   std::string;

double  getNonzeroIntFromSTDIN(string invitation){
    int result  =   0;
    
    while (true){
        cout << invitation;
        
        if (cin >> result   &&  result > 0){
            return  result;
        }
        else{
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }   //  while
}   //  getNonzeroIntFromSTDIN

typedef unsigned long long  longint;

int fibN(int n){
    static  longint storage[MAX_N];
    static  bool    initialized =   false;
    
    if (!initialized){
        storage[0]  =   1;
        storage[1]  =   1;
        
        for (int i = 2; i < MAX_N; ++i){
            storage[i]  =   0;
        }
        
        initialized =   true;
    }
    
    if (0 == storage[n]){
        storage[n] = fibN(n - 1) + fibN(n - 2);
    }
    
    return  storage[n];
}   //  fibN

int main(void){

    int N   = 0;
    
    //  User input
    cout << "Enter the number of the elements of the Fibbonaci sequence you want to calculate\n";
    N = getNonzeroIntFromSTDIN("N: ");
    
    longint  current =   0;
    
    for (int i = 0; i < N; ++i){
        current = (long long)fibN(i);
        cout << current << " ";
        
        if (current > INT_MAX){
            cout << endl;
            cout << "This was the " << i << "-th member of the Fibonacci sequence." << endl;
            cout << "Following members are greater then INT_MAX. Sad but true :-(" << endl;
            break;
        }
    }
    
    cout << endl;
    
    return  0;
}   //  main