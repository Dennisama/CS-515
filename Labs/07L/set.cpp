/** CS515 Lab 7
File: set.cpp
Name: Biao Zhang
Section: 01
Date: 10/21/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include "set.h"

Set::Set():_size(0){
    // create a dummy root node
    _root = new Elem;
    _root->info = numeric_limits<int>::max();
    _root->left = _root;  // empty tree
    _root->right = 0;
    _root->rightThread = false;
}

Set::~Set(){
    if (_root->left != _root)  // not an empty tree
        destructCode(_root->left);
    delete _root;
}

void Set::destructCode(Elem *& p){
   // fill in here
   if (!p)
       return;

   if (p->left)
       destructCode(p->left);
   if (!(p->rightThread))
       destructCode(p->right);
   delete p;
}


// returns true if the new node is inserted, otherwise false
bool Set::insert(ELEMENT_TYPE v){
    if (insert(_root->left, v, _root)){
        _size++;
        return true;
    }
    return false;
}

// insert helper method
// returns true if the new node is inserted, otherwise false
bool Set::insert(Elem *&cur, const ELEMENT_TYPE &value, Elem *lastLeft){
    if (cur == _root || cur == 0) {
        cur = new Elem;
        cur->info = value;
        cur->left = 0;
        cur->right = lastLeft;
        cur->rightThread = true;
        return true;
    }
    
    if (value == cur->info){
        return false;
    }
    // insert at left
    if (value < cur->info)
        return insert( cur->left, value, cur);
    
    // insert at right
    if (!cur->rightThread){
        return insert(cur->right, value, lastLeft);
    } else {  // current's right is a thread; add a new node
        cur->rightThread = false;
        cur->right = new Elem;
        cur->right->info = value;
        cur->right->left = 0;
        cur->right->right = lastLeft;
        cur->right->rightThread = true;
        return true;
    }
}

// print out tree elements in depth first in order
void Set::depthFirstInOrder(){
   // fill in here
   Elem* cur = _root;

    while (cur){
        while (cur->left) {
            cur = cur->left;
        }
        cout << cur->info << " ";
        while (cur->rightThread) {
            if (cur->right != _root)
                cout << cur->right->info << " ";
            cur = cur->right;
        }
        cur = cur->right;
    }
}

void Set::breadthFirst(){
   // fill in here
   queue<Elem *> q;
   Elem* cur;
   q.push(_root);
   while (q.size() > 0) {
       cur = q.front();
       q.pop();

       if(cur->left)
           q.push(cur->left);

       if(!(cur->rightThread)) {
           if(cur->right)
               q.push(cur->right);
       }


       if(cur->right)
           cout << cur->info << " ";
   }
}

int Set::size() const{
    return _size;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Set::printTree(ostream& out, int level, Elem *p){
    int i;
    if (p) {
        if (p->right && !p->rightThread)
            printTree(out, level+1,p->right);
        for(i=0;i<level;i++)
            out << "\t";
        out << p->info << '\n';
        printTree(out, level+1,p->left);
    }
}

// outputs information in tree in inorder traversal order
ostream& Set::dump(ostream &out){
    if ( _root == _root->left) // tree empty
        return out;
    printTree(out, 0, _root->left);   // print tree structure
    return out; 
}


// outputs using overloaded << operator
ostream& operator << (ostream &s, Set &v){
    v.dump(s);
    return s;
}

