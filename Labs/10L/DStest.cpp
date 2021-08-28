/** CS515 Lab 10
File: DStest.cpp
Name: Biao Zhang
Section: 01
Date: 11/22/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include "DisjointSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(){
    DisjointSet<int> s;
   
    /*
     *   you fill in here to set up the disjoint set 
     */
    for (int i = 1; i < 10; ++i) {
        s.createSet(i);
    }
    s.unionSets(3,5);
    s.unionSets(4,2);
    s.unionSets(1,6);
    s.unionSets(5,7);
    s.unionSets(4,8);
    s.unionSets(3,7);
    s.unionSets(8,1);

    assert(s.findSet(1) == s.findSet(6)); // 1 and 6 are connected.
    assert(s.findSet(3) != s.findSet(6)); // 3 and 6 are not connected.
    assert(s.findSet(1) == s.findSet(1)); // 1 and 1 are connected.
    assert(s.findSet(3) == s.findSet(5)); // 3 and 5 are connected.
    assert(s.findSet(3) != s.findSet(9)); // 3 and 9 are not connected.
    
}
