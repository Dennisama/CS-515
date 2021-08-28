/* CS515 Assignment 0
File: hello.cpp
Name: Biao Zhang
Section: 1
Date: 09/02/2020
Collaboration Declaration: 
          assistance received from TA, PAC and online resources etc. 
*/  

#include <iostream> // for cin and cout
#include <string> // for string type
using namespace std;
string trim(string str);

int main(int argc, char ** argv) {
    string name = " ";
    while (trim(name).length() == 0) {
        cout << "What is your name?" << endl;
        getline (cin,name);
    }
    cout << "Hello World!" << endl;
    cout << "Welcome to CS515, " << name << "!" << endl;
	
    return 0; 
}

/*==========================================*
 * fact--returns a string without head and tail
 *       whitespace.
 * Input: str - a string
 * Output: Returns a string without head and
 *         tail whitespace
 * =========================================*/
string trim(string str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

