/** CS515 Lab 2
File: debug2.cpp
Name: Biao Zhang
Section: 01
Date: 9/18/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: Instructor Matthew Plumlee
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int* initArray(int);
void fillArray(int *, int);
int* doubleArray(int *, int);
void displayArray(int *, int);

/* 
 * The program will create an array of given size
 * populate the array with random number from (0-99)
 * and display the array. Next, the program will double
 * the size of the array, repopulate the array and 
 * display it again.
 */


int main(int argc, char ** argv){
    if (argc != 2){
        cout << "wrong number of arguments" << endl;
        exit(1);
    }
    
    int n = atoi(argv[1]); // get size
    srand(time(0));
    
    // create initial array and display it
    int* ptr = initArray(n);
    fillArray(ptr, n);
    displayArray(ptr, n);

    // create the double sized array and display it
    ptr = doubleArray(ptr, n);
    fillArray(ptr, 2*n);
    displayArray(ptr, 2*n);

    delete [] ptr;
}

// Create an array of size n and return its address
int* initArray(int n){
    // arr[n]; variable length array is legal in g++, but illegal in proper c++.
    int *ptr = new int[n];
    return ptr;
}

// Fill array ptr with n random numbers
void fillArray(int *ptr, int n){
    for(int i=0; i<n; i++){
        ptr[i] = rand() % 100;
    }
}

// Double the size of the array, make sure no memory leak
int* doubleArray(int *ptr, int n){
    delete [] ptr;
    int size = 2*n;
    int * tmp = new int[size];
    ptr = tmp;
    //delete [] tmp; // Dangling pointer
    return ptr;
}

// Display n array elements
void displayArray(int *ptr, int n){
    for(int i=0; i<n; i++){
        cout << ptr[i] << " ";
    }
    cout << endl;
}