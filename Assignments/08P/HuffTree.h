/* CS515 Assignment 8
File: HuffTree.h
Name: Biao Zhang
Section: 1
Date: 11/04/2020
Collaboration Declaration:
          assistance received from online resources and Dr.Matthew.
*/
#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <string>
using namespace std;

struct HuffNode{
    // default constructor
    HuffNode(HuffNode* l = 0, HuffNode* r = 0, int f = 0, char d = '\0')
        : left(l), right(r), freq(f), data(d){}
    HuffNode * left, * right;  // two child node
    unsigned int freq; // freqency of the node
    char data;  // char value for leaf nodes; '\0' for internal nodes
    string code;  // Huffman code for leaf nodes; not assigned for internal nodes
    
    // do not change above code
    // you may add below here
    void setFreq(int);
    void setData(char);
    // Since my PQueue only involves those
    // two comparisons, we only overload
    // those two operators.
    bool operator >(const HuffNode&);
    bool operator <(const HuffNode&);
};

class HuffTree{
public:
    // get Huffman code and return it as a string
    string getCode(char);
    
    // build Huffman tree from an array of characters
    // and and an array of their corresponding freqencys;
    // the size of both arrays is given
    void buildTree(char * chs, int * freqs, int size);

    ~HuffTree();

private:
    HuffNode * _root; // root of the Huffman tree
   
    // do not change above code
    // you may add below here
    bool getCodeHelper(HuffNode *& n, char c, string& s);
    void destructTree(HuffNode *& n);
};

#endif