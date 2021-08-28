/* CS515 Assignment 7
File: map.cpp
Name: Biao Zhang
Section: 1
Date: 10/29/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
// A non-generic Map ADT implemented with a BST data structure
// The BST is not-balanced and non-threaded
#include "map.h"

Map::Map(){
	// create a dummy root node and set up an empty tree
	_root = new Elem;
	_root->left = _root;  
	_root->right = 0;
	_size = 0;

}

// copy constructor
Map::Map(const Map &v){
	// if empty tree
	if (v._root == v._root->left){
		_root = new Elem;
		_root->left = _root;  // empty tree
		_root->right = 0;
		_size = 0;
	} else {
		_root = new Elem;
		_root->left = _root;
		_root->right = 0;
		copyCode(_root->left, v._root->left);
		_size = v._size;
	}
}

// destructor
Map::~Map(){
    if (_root != _root->left)  // not an empty tree
        destructCode(_root->left);
    delete _root;
}

// assignment operator
Map& Map::operator=(const Map &rhs){
    if (this == &rhs)
        return *this;
    if (_root != _root->left)  // not an empty tree
        destructCode(_root->left);
    delete _root;
    if (rhs._root == rhs._root->left){
        _root = new Elem;
        _root->left = _root;  // empty tree
        _root->right = 0;
        _size = 0;
    } else {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
        copyCode(_root->left, rhs._root->left);
        _size = rhs._size;
    }
    return *this;
}

// insert an element; return true if successful
bool Map::insert(KEY_TYPE k, VALUE_TYPE v){
    if (_root == _root->left) {
        Elem* item = new Elem;
        item->key = k;
        item->data = v;
        item->left = 0;
        item->right = 0;
        _root->left = item;
        _size = 1;
        return true;
    } else
        return insert(_root->left, k, v);
}

// remove an element; return true if successful
bool Map::erase(KEY_TYPE k){
    if (_root != _root->left) {
        Elem* parent = _root;
        Elem* localRoot = _root->left;
        while (localRoot) {
            if (k < localRoot->key) {
                parent = localRoot;
                localRoot = localRoot->left;
            } else if (k > localRoot->key) {
                parent = localRoot;
                localRoot = localRoot->right;
            } else
                break;
        }

        // The searching key does not exist
        if (!localRoot)
            return false;

        bool isDone = false;
        while (!isDone) {
            if (!(localRoot->left || localRoot->right)) {
                if (parent->right == localRoot)
                    parent->right = 0;
                else {
                    if (parent == _root)
                        parent->left = _root;
                    else
                        parent->left = 0;
                }

                delete localRoot;
                _size--;
                isDone = true;
            } else if (localRoot->left && localRoot->right) {
                Elem* successor;
                // Find successor
                Elem* minElem = localRoot->right;
                parent = localRoot;
                while (minElem->left) {
                    parent = minElem;
                    minElem = minElem->left;
                }

                successor = minElem;

                localRoot->key = successor->key;
                localRoot->data = successor->data;
                localRoot = successor;
            } else {
                if (localRoot->right) {
                    if (parent->right == localRoot)
                        parent->right = localRoot->right;
                    else
                        parent->left = localRoot->right;
                } else {
                    if (parent->right == localRoot)
                        parent->right = localRoot->left;
                    else
                        parent->left = localRoot->left;
                }
                delete localRoot;
                _size--;
                isDone = true;
            }
        }
        return isDone;
    }
    return false;
}

// return size of the Map
int Map::size() const {
    return _size;
}

// return an iterator pointing to the end if an element is not found,
// otherwise, return an iterator to the element
Map::Iterator Map::find(KEY_TYPE k) const {

    if (_root != _root->left) {
        Elem* localRoot = _root->left;
        while (localRoot) {
            if (k < localRoot->key)
                localRoot = localRoot->left;
            else if (k > localRoot->key)
                localRoot = localRoot->right;
            else
                break;
        }

        if (localRoot) {
            Iterator it(localRoot);
            return it;
        }
    }
    Iterator no_it = end();
    return no_it;
}

// Iterators for accessing beginning of collection
Map::Iterator Map::begin() const {
    if (_root != _root->left) {
        Elem* localRoot = _root->left;
        while (localRoot->left)
            localRoot = localRoot->left;
        Iterator it(localRoot);
        return it;
    }
    Iterator no_it(_root);
    return no_it;
}

// Iterators for accessing end of collection
Map::Iterator Map::end() const {
    /*if (_root != _root->left) {
        Elem* localRoot = _root->left;
        while (localRoot->right)
            localRoot = localRoot->right;
        Iterator it(localRoot);
        return it;
    }*/
    Iterator it(_root);
    return it;
}

// overloaded subscript operator
VALUE_TYPE& Map::operator[](KEY_TYPE k) {
    if (_root != _root->left) {
        Elem* parent = _root;
        Elem* localRoot = _root->left;
        bool is_left = true;
        while (localRoot) {
            if (k < localRoot->key) {
                parent = localRoot;
                localRoot = localRoot->left;
                is_left = true;
            } else if (k > localRoot->key) {
                parent = localRoot;
                localRoot = localRoot->right;
                is_left = false;
            } else
                break;
        }

        if (!localRoot) {
            Elem* item = new Elem;
            item->right = 0;
            item->left = 0;
            item->key = k;
            item->data = "";
            if (is_left)
                parent->left = item;
            else
                parent->right = item;
            _size++;
            return item->data;
        }

        return localRoot->data;
    }

    Elem* item = new Elem;
    item->right = 0;
    item->left = 0;
    item->key = k;
    item->data = "";
    _root->left = item;
    _size++;
    return item->data;
}

Map::Elem& Map::Iterator::operator*() {
    return *_cur;
}

Map::Elem* Map::Iterator::operator->() {
    return _cur;
}

bool Map::Iterator::operator==(Iterator it) const {
    return _cur == it._cur;
}

bool Map::Iterator::operator!=(Iterator it) const {
    return _cur != it._cur;
}

// helper method for inserting record into tree.
bool Map::insert(Elem *& root, const KEY_TYPE& key, const VALUE_TYPE& data) {
    // if root exists
    if (root){
        if (key < root->key)
            return insert(root->left, key, data);
        else if (key > root->key)
            return insert(root->right, key, data);
        else
            return false;
    }

    Elem* item = new Elem;
    item->key = key;
    item->data = data;
    item->left = 0;
    item->right = 0;
    root = item;
    _size++;
    return true;
}

void Map::destructCode(Elem *& p){
    if (!p)
        return;

    if (p->left)
        destructCode(p->left);
    if (p->right)
        destructCode(p->right);
    delete p;
}

// common copy code for deep copy a tree
void  Map::copyCode(Elem* &newRoot, Elem* origRoot){
	if (origRoot == 0)
		newRoot = 0;
	else{
		newRoot = new Elem;
		newRoot->key = origRoot->key;
		newRoot->data = origRoot->data;
		copyCode(newRoot->left, origRoot->left);
		copyCode(newRoot->right, origRoot->right);
	}
}

// 
//  Do Not Modify Below Here
//
//
// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Map::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		printTree(out, level+1, p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << '\n';
		printTree(out, level+1, p->left);
	}
}

// outputs information in tree
ostream& Map::dump(ostream& out) const{
	if ( _root == _root->left) { // tree empty
		return out;
	}
	printTree(out, 0, _root->left);   // print tree structure
	return out;
}

// outputs using overloaded << operator
ostream& operator<< (ostream& out, const Map& v){
	v.dump(out);
	return out;
}
