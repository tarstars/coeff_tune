#include <limits.h>
#include <cmath>
#include <iostream>
#include <string>

using   std::cin;
using   std::cout;
using   std::endl;
using   std::string;

double  getDoubleFromSTDIN(string invitation){
    double  result  =   0;
    
    while (true){
        cout << invitation;
        
        if (cin >> result){
            return  result;
        }
        else{
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }   //  while
}   //  getDoubleFromSTDIN

int main(void){

    double  a, b, c;
    bool    input_finished  =   false;
    
    //  User input
    cout << "Enter square equation (a * x^2 + b * x + c = 0) coefficients a, b, c\n";
    a = getDoubleFromSTDIN("a: ");
    b = getDoubleFromSTDIN("b: ");
    c = getDoubleFromSTDIN("c: ");
    
    //  Solving the equation
    double  D   =   b*b - 4*a*c;
    
    if (D < 0.0){
        cout << "Your equation has no roots" << endl;
    }
    else if (0 == D){
        cout << "Your equation has one root: " << (-b / 2 * a) << endl;
    }
    else{
        cout << "Your equation has two roots: " << ((-b + sqrt(D))/ 2 * a) << ", " << ((-b - sqrt(D))/ 2 * a)<< endl;
    }
    
    return  0;
}   //  main