/** CS515 Lab 13
File: wordcheck.cpp
Name: Biao Zhang
Section: 01
Date: 12/12/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <cctype>
#include <algorithm>
using namespace std;

bool isAlphabetic (string str){
    int i = 0;
    while(str[i]){
        if(!isalpha(str[i]))
            return false;
        i++;
    }
    return true;
}

int main(int argc, char * argv[]){
    //Open file and read data
    ifstream f("words");
    if(f.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }

    map< string, list<string> > fr_words;
    map< string, list<string> > sc_words;
    map< string, list<string> > th_words;
    map< string, list<string> > fo_words;
    vector< map< string, list<string> > > words;
    words.push_back(fr_words);
    words.push_back(sc_words);
    words.push_back(th_words);
    words.push_back(fo_words);
    string str, tmp;
    if(f.is_open()) {
        while (getline(f, str)) {
            if (str.size() == 4 && isAlphabetic(str)) {
                for (int k = 0; k < 4; k++) {
                    tmp = str;
                    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
                    tmp[k] = '#';
                    words[k][tmp].push_back(str);
                }
            }
        }
        f.close();
    }

    cout << "Please input a 4 letter word:";
    set<string> print_res;
    string _word;
    bool is_first;
    while(cin >> _word) {
        if(_word.size() != 4)
            cout << "wrong length!";
        else {
            if (isAlphabetic(_word)) {
                transform(_word.begin(), _word.end(), _word.begin(), ::tolower);
                for (int k = 0; k < 4; k++) {
                    tmp = _word;
                    tmp[k] = '#';
                    for (string s : words[k][tmp]) {
                        transform(s.begin(), s.end(), s.begin(), ::tolower);
                        if (s.compare(_word) != 0)
                            print_res.insert(s);
                    }
                }
                is_first = true;
                for (string s : print_res) {
                    if (!is_first)
                        cout << ' ';
                    else
                        is_first = false;

                    cout << s;
                }
                cout << endl;
                cout << "Total: " << print_res.size() << " words." << endl;
                cout << "Please input a 4 letter word:";
                print_res.clear();
            }
        }
    }
    cout << endl;
}

