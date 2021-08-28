/** CS515 Lab 2
File: debug1.cpp
Name: Biao Zhang
Section: 01
Date: 9/18/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/

#include<iostream>
using namespace std;
 
/******************************************************************
 *   Calculate the factorial of a number input from keyboard.  
 ******************************************************************/ 
 
long factorial(int n); // function declaration
 
int main(){
    int n = 0;
    cin >> n;
    cout << "The factorial of " << n << " is " << factorial(n);
    cout << endl;
    return 0;
}
 
long factorial(int n){
    long result = 1;
    while(n > 0){
        result *= n;
        n--;
    }
    return result;
}

