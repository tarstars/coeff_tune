// Оператор switch, служебные слова case, default, break.
// Ввести из входного потока целое число num.
// При num == 1 напечатать "один", num == 2 "два" при num == 3 или num==4 напечатать "три или четыре".
// Во всех остальных случаях напечатать "много"

#include <limits.h>
#include <cmath>
#include <iostream>
#include <string>

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

int main(void){

    int N   = 0;
    
    //  User input
    cout << "Enter a positive integer number:";
    N = getNonzeroIntFromSTDIN("");
    
    switch (N){
        case    1:
            cout << "one" << endl;
            break;
        
        case    2:
            cout << "two" << endl;
            break;
            
        case    3:
        case    4:
            cout << "three or four" << endl;
            break;
            
        default  :
            cout << "too much" << endl;
            break;
    }
    
    
    return  0;
}   //  main