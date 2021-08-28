/* CS515 Assignment 3
File: image.cpp
Name: Biao Zhang
Section: 1
Date: 09/29/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;

int main(int argc, char * argv[]){

    if(argc != 4) {
        cout << "Usage: ./image <input image> <neg image> <rotate image>" << endl;
        exit(1);
    }

    ifstream f(argv[1]);
    if(f.fail()) {
        cout << "Can not open " << argv[1] << " for input." << endl;
        exit(1);
    }

    int row = 0, col = 0, numrows = 0, numcols = 0, maxgrayval = 255;
    ifstream infile(argv[1]);
    stringstream ss;
    string inputLine = "";

    // First line : version
    getline(infile,inputLine);

    // Check the version
    /*if(inputLine.compare("P2") != 0) cerr << "Version error" << endl;
    else cout << "Version : " << inputLine << endl;*/

    // Optional line : comment
    /*getline(infile,inputLine);
    cout << "Comment : " << inputLine << endl;*/

    // Continue with a stringstream
    ss << infile.rdbuf();
    // Second & Third line : size
    ss >> numcols >> numrows >> maxgrayval;

    int **datum = new int *[numrows];

    // Following lines : data
    for (row = 0; row < numrows; row++) {
        datum[row] = new int[numcols];
        for (col = 0; col < numcols; col++)
            ss >> datum[row][col];
    }

    infile.close();

    FILE *negative_pgmimg, *clockwise_pgmimg;
    negative_pgmimg = fopen(argv[2], "wb");
    clockwise_pgmimg = fopen(argv[3], "wb");

    // Writing Magic Number to the file
    fprintf(negative_pgmimg, "%s\n", inputLine.c_str());
    fprintf(clockwise_pgmimg, "%s\n", inputLine.c_str());

    // Writing width and height
    fprintf(negative_pgmimg, "%d %d\n", numcols, numrows);
    fprintf(clockwise_pgmimg, "%d %d\n", numrows, numcols);

    // Writing the maximum gray value
    fprintf(negative_pgmimg, "%d\n", maxgrayval);
    fprintf(clockwise_pgmimg, "%d\n", maxgrayval);

    int temp = 0;

    // Write to .pgm file
    for (row = 0; row < numrows; row++) {
        for (col = 0; col < numcols; col++) {
            temp = datum[row][col];

            fprintf(negative_pgmimg, "%d ", (255 - temp));
        }
        fprintf(negative_pgmimg, "\n");
    }

    for (col = 0; col < numcols; col++) {
        for (row = numrows - 1; row >= 0; row--) {
            temp = datum[row][col];

            fprintf(clockwise_pgmimg, "%d ", temp);
        }
        fprintf(clockwise_pgmimg, "\n");
    }

    fclose(negative_pgmimg);
    fclose(clockwise_pgmimg);

    // Dealloacte the dynamic 2D array
    for (row = 0; row < numrows; row++)
        delete [] datum[row];
    delete [] datum;

    return 0;
}

