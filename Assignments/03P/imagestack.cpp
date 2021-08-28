/* CS515 Assignment 3
File: imagestack.cpp
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
// Function to sort an array using insertion sort
void insertionSort(int arr[], int n);

int main(int argc, char * argv[]){

    //Unnecessary to test errors
    /*if(argc != 4) {
        cerr << "Usage: image <input image> <neg image> <rotate image>" << endl;
        exit(1);
    }

    ifstream f(argv[1]);
    if(f.fail()) {
        cerr << "Can not open " << argv[1] << " for input." << endl;
        exit(1);
    }*/

    // Declare variables
    int m, row, col, nummatrix, numrows, numcols, maxgrayval; // The size of images should be the same
    ifstream infile;
    stringstream ss;
    string inputLine;

    nummatrix = argc - 2;// Exclude the compile file and the output file
    int*** datum = new int**[nummatrix];

    for(m = 0; m < nummatrix; m++){
        row = 0, col = 0, numrows = 0, numcols = 0, maxgrayval = 255;
        infile.open(argv[m + 1]);// The input file starts with index 1
        inputLine = "";

        // First line : version
        getline(infile,inputLine);

        // Optional line : comment
        /*getline(infile,inputLine);
        cout << "Comment : " << inputLine << endl;*/

        // Continue with a stringstream
        ss << infile.rdbuf();
        // Second & Third line : size
        ss >> numcols >> numrows >> maxgrayval;

        datum[m] = new int *[numrows];

        // Following lines : data
        for (row = 0; row < numrows; row++) {
            datum[m][row] = new int[numcols];
            for (col = 0; col < numcols; col++)
                ss >> datum[m][row][col];
        }

        infile.close();
    }

    FILE *filter_pgmimg;
    int output_index = argc - 1; // The index starts at 0.
    filter_pgmimg = fopen(argv[output_index], "wb");

    // Writing Magic Number to the file
    fprintf(filter_pgmimg, "%s\n", inputLine.c_str());

    // Writing width and height
    fprintf(filter_pgmimg, "%d %d\n", numcols, numrows);

    // Writing the maximum gray value
    fprintf(filter_pgmimg, "%d\n", maxgrayval);

    int temp_list[nummatrix] = {0};
    int temp = 0;

    // Write to .pgm file
    for (row = 0; row < numrows; row++) {
        for (col = 0; col < numcols; col++) {
            for (m = 0; m < nummatrix; m++) {
                temp_list[m] = datum[m][row][col];
            }
            insertionSort(temp_list, nummatrix);
            if (nummatrix % 2 == 0)
                temp = (temp_list[nummatrix / 2] + temp_list[nummatrix / 2 - 1]) / 2;
            else
                temp = temp_list[(nummatrix - 1) / 2];


            fprintf(filter_pgmimg, "%d ", temp);
        }
        fprintf(filter_pgmimg, "\n");
    }

    fclose(filter_pgmimg);

    // Dealloacte the dynamic 3D array
    for (m = 0; m < nummatrix; m++) {
        for (row = 0; row < numrows; row++)
            delete [] datum[m][row];
        delete [] datum[m];
    }
    delete [] datum;

    return 0;
}

/*===============================*
 * fact--Insertion Sort
 * Input: arr[] - the input array
 *        n - it determines items
 *        from 1st to nth to be
 *        sorted
 * Output: void - array is sorted
 *         by reference, no return
 *         val.
 *================================*/
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}