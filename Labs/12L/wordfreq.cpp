/** CS515 Lab 12
File: wordfreq.cpp
Name: Biao Zhang
Section: 01
Date: 12/05/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;
int main(int argc, char * argv[]){
    //The number of arguments are incorrect.
    if(argc != 2) {
        cerr << "Wrong number of arguments" << endl;
        exit(1);
    }

    //Open file and read data
    ifstream f(argv[1]);
    if(f.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }

    map< string, map<string, string> > freq_table;
    string _word, _year, _freq, str;
    if(f.is_open()) {
        while (getline(f, str)) {
            stringstream row(str);
            row >> _word >> _year >> _freq;
            freq_table[_word][_year] = _freq;
        }
        f.close();
    }

    cout << "Which word starting which year?" << ' ';
    while(cin >> _word >> _year) {
        map<string, map<string, string> >::iterator itr;
        map<string, string>::iterator ptr;
        itr = freq_table.find(_word);
        ptr = itr->second.find(_year);
        while (ptr != itr->second.end()) {
            cout << ptr->first << " " << ptr->second << endl;
            ptr++;
        }
        cout << "Which word starting which year?" << ' ';
    }
    cout << endl;
}
