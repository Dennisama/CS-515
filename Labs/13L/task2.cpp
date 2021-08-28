/** CS515 Lab 13
File: task2.cpp
Name: Biao Zhang
Section: 01
Date: 12/13/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include <iostream>
#include <sstream>
using namespace std;

double doit(istream &in)
{
    // YOUR CODE GOES HERE
    int a = 0;
    int sum = 0;
    int count = 0;
    while (in >> a) {
        if (a == -99)
            break;

        if (a >= 0) {
            sum += a;
            count++;
        }
    }

    return (double)sum / (double)count;
}

// Testing framework for doit function
int main(int argc, char *argv[])
{
    cout << "------Basic test------" << endl;
    string data[] = {"1 2 3 -99",
                     "1 2 3 0 -6 -99",
                     "-99"
                    };

    for (string &in : data)
    {
       stringstream input(in);
       try
       {
          cout << "Your result: " << doit(input) << endl;
       } catch (int e)
       {
          cout << "Call threw an exception!" << endl;
       }
    }

    cout << "------Test using input data------" << endl;
    double result = doit(cin);
    cout << "Your result: " << result << endl;
}
