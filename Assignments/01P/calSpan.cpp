/* CS515 Assignment 1
File: calSpan.cpp
Name: Biao Zhang
Section: 1
Date: 09/13/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
bool is_number(const string& s);
bool is_integer(const string& s);

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

    string str;

    if(f.is_open()) {
        getline(f,str);
        f.close();
    }

    stringstream ss(str);

    vector<double> numbers;

    //Invalid data have all been stored as
    //the number 101.
    for (string num; ss >> num;) {
        if (is_number(num)){
            double number;
            number = stod(num);
            if (number > 100 || number < -100)
                numbers.push_back(-101);
            else
                numbers.push_back(number);
        } else
            numbers.push_back(-101);

    }

    //Testing whether the input data is stored properly.
    /*for (int i = 0; i < numbers.size(); ++i) {
        cout << numbers.at(i) << ' ';
    }
        cout << endl;*/

    string answer = "start";
    while(answer.compare("exit") != 0){
        cout << "Which minute to query?" << ' ';
        cin >> answer;
        if(is_integer(answer)) {
            int minute;
            minute = stoi(answer);
            if((minute + 1) > numbers.size() || minute < 0)
                cerr << "Query minute out of range" << endl;
            else {
                if (numbers.at(minute) == -101) {
                    cout << "Data at minute " << minute
                         << " is corrupted." << endl;
                } else {
                    int span = 0;
                    double target = numbers.at(minute);
                    for(int i = minute; i >= 0; --i){
                        if (numbers.at(i) <= target)
                            span++;
                        else
                            break;
                    }
                    cout << "Data at minute " << minute
                         << " is a " << span << "-minute(s) high."
                         << endl;
                }

            }
        } else {
            transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
            if(answer.compare("exit") != 0)
                cerr << "Wrong query input." << endl;
            else
                cout << endl;
        }

    }
}

/*==========================================*
 * fact--test whether the string is a valid
 *       real number, real number is allowed
 *       to have '+' or '-' in front of it.
 * Input: str - a string
 * Output: Returns the result about whether
 *         it is a valid real number.
 * =========================================*/
bool is_number(const string& s){
    string::const_iterator itr = s.begin();

    if (isdigit(*itr) || *itr == '-' || *itr == '+')
        itr++;

    while(itr != s.end() && (isdigit(*itr)
    || *itr == '.' ))
        itr++;

    return !s.empty() && (itr == s.end());
}

/*==========================================*
 * fact--test whether the string is a valid
 *       integer.
 * Input: str - a string
 * Output: Returns the result about whether
 *         it is a valid integer.
 * =========================================*/
bool is_integer(const string& s){
    string::const_iterator itr = s.begin();

    if (isdigit(*itr) || *itr == '-' )
        itr++;

    while(itr != s.end() && isdigit(*itr))
        itr++;

    return !s.empty() && (itr == s.end());
}