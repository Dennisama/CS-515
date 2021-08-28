/* CS515 Assignment 8
File: HuffTree.cpp
Name: Biao Zhang
Section: 1
Date: 11/04/2020
Collaboration Declaration:
          assistance received from online resources and Dr.Matthew.
*/
#include "HuffTree.h"
#include "PQueue.h"

void HuffNode::setFreq(int f) {
    freq = f;
}

void HuffNode::setData(char c) {
    data = c;
}

bool HuffNode::operator >(const HuffNode& n) {
    return freq > n.freq;
}
bool HuffNode::operator <(const HuffNode& n) {
    return freq < n.freq;
}

HuffTree::~HuffTree() {
    if (_root)
        destructTree(_root);
}

// build Huffman tree from an array of characters
// and and an array of their corresponding freqencys;
// the size of both arrays is given
void HuffTree::buildTree(char * chs, int * freqs, int size) {
    PQueue<HuffNode, 128> p_q;
    HuffNode* nodes = new HuffNode[size];
    for (int i = 0; i < size; i++) {
        nodes[i].setData(chs[i]);
        nodes[i].setFreq(freqs[i]);
        p_q.insert(nodes[i]);
    }

    HuffNode tmp;
    HuffNode* tmp_1;
    HuffNode* tmp_2;
    while (p_q.size() >= 2) {
        tmp_1 = new HuffNode(p_q.findMin());
        p_q.deleteMin();
        tmp_2 = new HuffNode(p_q.findMin());
        p_q.deleteMin();
        tmp.left = tmp_1;
        tmp.right = tmp_2;
        tmp.freq = tmp_1->freq + tmp_2->freq;
        p_q.insert(tmp);
    }

    if (p_q.size() == 1) {
        _root = new HuffNode(p_q.findMin());
        p_q.deleteMin();
    }

    delete [] nodes;
}

// get Huffman code and return it as a string
string HuffTree::getCode(char c) {
    string res = "";
    getCodeHelper(_root, c, res);
    return res;
}

void HuffTree::destructTree(HuffNode *& n){
    if (!n)
        return;

    if (n->left)
        destructTree(n->left);
    if (n->right)
        destructTree(n->right);
    delete n;
}

bool HuffTree::getCodeHelper(HuffNode *& n, char c, string& s) {
    if (!n)
        return false;

    if (n->data == c) {
        n->code = s;
        return true;
    }

    s = s + "0";
    if (getCodeHelper(n->left, c, s))
        return true;
    else
        s.pop_back();

    s = s + "1";
    if (getCodeHelper(n->right, c, s))
        return true;
    else
        s.pop_back();

    return false;
}