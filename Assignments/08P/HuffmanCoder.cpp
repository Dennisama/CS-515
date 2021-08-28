/* CS515 Assignment 8
File: HuffmanCoder.cpp
Name: Biao Zhang
Section: 1
Date: 11/04/2020
Collaboration Declaration:
          assistance received from online resources and Dr.Matthew.
*/
#include "HuffTree.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string.h>
#include <iomanip>

int main(int argc, char * argv[]) {

    int freqs[26] = {0};
    char alphabet [26];
    for (char c = 'a'; c <= 'z'; c++)
        alphabet[c - 'a'] = c;
    int originalAlphaBits = 0;
    int compressAlphaBits = 0;
    int originalTotalBits = 0;

    char c;
    fstream f(argv[1], fstream::in);
    if (f.is_open()) {
        while (f >> noskipws >> c) {
            if (isalpha(c)) {
                c = tolower(c, locale());
                freqs[c - 'a']++;
                //cout << c - 'a' << ": " << freqs[c - 'a'] << " ";
                originalAlphaBits += 8;
            }

            originalTotalBits += 8;
        }

        f.close();
    }

    HuffTree h;
    h.buildTree(alphabet, freqs, 26);
    string res;

    for (int i = 0; i < 26; i++) {
        if (freqs[i] > 0) {
            res = h.getCode(alphabet[i]);
            //Calculate the difference
            compressAlphaBits = compressAlphaBits + res.length() * freqs[i];
        }
    }

    double rate = (originalAlphaBits - compressAlphaBits) * 100.0 / originalTotalBits;

    cout << "original bits: " << originalTotalBits << endl;
    cout << "bits after compression: "
         << originalTotalBits - (originalAlphaBits - compressAlphaBits)
         << endl;
    cout << "compression rate: " << setprecision(4) << rate << "%" << endl;
}

