/* CS515 Assignment 9
File: map.cpp
Name: Biao Zhang
Section: 1
Date: 11/24/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
// A generic Map implemented with right-threaded AVL Tree
// AVL Tree is balanced

#include <map> // helper container for thread copying

template <typename KEY, typename T>
Map<KEY, T>::Map(){
    // create a dummy root node
    _root = new Elem;
    _root->left = _root; // empty tree
    _root->right = 0;
    _root->rightThread = false;
    _root->height = 0; // For this dummy node, it should never change
    _size = 0;

}

// copy constructor
template <typename KEY, typename T>
Map<KEY, T>::Map(const Map<KEY,T> &v){
    // if empty tree
    if (v._root == v._root->left){
        _root = new Elem;
        _root->left = _root;  // empty tree
        _root->right = 0;
        _root->height = 0;
        _size = 0;
    } else {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
        _root->height = 0;
        copyCode(_root->left, v._root->left); // to deep copy the tree without dummy nodes (*height*)
        copyThread(_root, v._root); // to copy the threading; must pass dummy nodes to complete the threads
        _size = v._size;
    }
}

// destructor
template <typename KEY, typename T>
Map<KEY, T>::~Map(){
    if (_root != _root->left)  // not an empty tree
        destructCode(_root->left);
    delete _root;
}

// assignment operator
template <typename KEY, typename T>
Map<KEY, T>& Map<KEY, T>::operator=(const Map<KEY, T> &rhs){
    if (this == &rhs)
        return *this;
    if (_root != _root->left)  // not an empty tree
        destructCode(_root->left);
    delete _root;
    // if empty tree
    if (rhs._root == rhs._root->left){
        _root = new Elem;
        _root->left = _root;  // empty tree
        _root->right = 0;
        _root->height = 0;
        _size = 0;
    } else {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
        _root->height = 0;
        copyCode(_root->left, rhs._root->left); // to deep copy the tree without dummy nodes
        copyThread(_root, rhs._root); // to copy the threading; must pass dummy nodes to complete the threads
        _size = rhs._size;
    }
    return *this;
}

// insert an element into the Map; return true if successful
template <typename KEY, typename T>
bool Map<KEY, T>::insert(KEY key, T data){
    if (_root == _root->left) {
        Elem* item = new Elem;
        item->key = key;
        item->data = data;
        item->left = 0;
        //_root is the unique dummy node
        //whose right child is empty.
        item->right = _root;
        item->rightThread = true;
        item->height = 0;
        _root->left = item;
        _size = 1;
        return true;
    } else
        return insert(_root->left, key, data, _root);
}

// helper method for inserting record into tree.
template <typename KEY, typename T>
bool Map<KEY, T>::insert(Elem *& root, const KEY &key, const T &data, Elem *lastLeft){
    // if root exists
    bool result;

    if (root){
        if (key < root->key)
            result = insert(root->left, key, data, root);
        else if (key > root->key) {
            // If the added item is the right child
            // of root
            if (root->rightThread) {
                Elem* item = new Elem;
                item->key = key;
                item->data = data;
                item->left = 0;
                item->right = lastLeft;
                item->rightThread = true;
                item->height = 0;
                root->rightThread = false;
                root->right = item;
                _size++;
                result = true;
            } else
                result = insert(root->right, key, data, lastLeft);
        } else
            result = false;
    } else {
        // If the added item is the left child
        // of root
        Elem* item = new Elem;
        item->key = key;
        item->data = data;
        item->left = 0;
        item->right = lastLeft;
        item->height = 0;
        item->rightThread = true;
        root = item;

        _size++;
        result = true;
    }

    if (result) {
        int right_height = (root->rightThread) ? -1 : height(root->right);

        // It may not have right child
        if (height(root->left) - right_height == 2) { // calculate load factor
            if(key < root->left->key) // outside case
                rotateRight(root);
            else  // inside case
                doubleRotateRight(root);
        }

        // It must have right child
        if (height(root->left) - right_height == -2) { // calculate load factor
            if (key > root->right->key) // outside case
                rotateLeft(root);
            else  // inside case
                doubleRotateLeft(root);
        }
        //After the rotation, it is updated
        right_height = (root->rightThread) ? -1 : height(root->right);
        root->height = max(height(root->left), right_height) + 1; // update height
    }

    return result;
}

// return the height of a node
template <typename KEY, typename T>
int Map<KEY, T>::height(Elem *node){
    return node == 0 ? -1 : node->height;
}

template <typename KEY, typename T>
void Map<KEY, T>::rotateRight(Elem *& node) {
    // Updates are necessary
    Elem* beta = node->left;
    node->left = (beta->rightThread) ? 0 : beta->right;
    //Update the height
    int right_height = (node->rightThread) ? -1 : height(node->right);
    node->height = max(height(node->left), right_height) + 1;

    beta->right = node;
    if (beta->rightThread)
        beta->rightThread = false;
    node = beta;
}

template <typename KEY, typename T>
void Map<KEY, T>::rotateLeft(Elem *& node){
    // Updates are necessary
    Elem* gamma = node->right;
    node->right = (!gamma->left) ? gamma : gamma->left;
    node->rightThread = (!gamma->left) ? true : false;
    // Update the height
    int right_height = (node->rightThread) ? -1 : height(node->right);
    node->height = max(height(node->left), right_height) + 1;

    gamma->left = node;
    node = gamma;
}

template <typename KEY, typename T>
void Map<KEY, T>::doubleRotateRight(Elem *& node) {
    // No updates
    rotateLeft(node->left);
    rotateRight(node);
}

template <typename KEY, typename T>
void Map<KEY, T>::doubleRotateLeft(Elem *& node) {
    // No updates
    rotateRight(node->right);
    rotateLeft(node);
}

// common code for deallocation
template <typename KEY, typename T>
void Map<KEY, T>::destructCode(Elem *& p){
    if (!p)
        return;

    if (p->left)
        destructCode(p->left);
    if (!p->rightThread)
        destructCode(p->right);
    delete p;
}

// construct a key-element map to rethread the new tree
// the map contains all nodes key values and their corresonding elem node address
// for furture lookup in setting up threads
template <typename KEY, typename T>
void Map<KEY, T>::addToMap(Elem* root, map<KEY, Elem*> &keyElemMap){
    if (root) {
        keyElemMap[root->key] = root;
        addToMap(root->left, keyElemMap);
        if (!root->rightThread)
            addToMap(root->right, keyElemMap);
    }
}

// common copy code for thread copying
template <typename KEY, typename T>
void Map<KEY, T>::copyThread(Elem* &newRoot, Elem* origRoot){
    // construct the key-element map for new and orig tree
    map<KEY, Elem*> newKeyElemMap;
    map<KEY, Elem*> origKeyElemMap;
    addToMap(newRoot->left, newKeyElemMap);
    addToMap(origRoot->left, origKeyElemMap);

    // start at the last element in the tree, which threads to root
    typename std::map<KEY, Elem*>::reverse_iterator it = origKeyElemMap.rbegin();
    newKeyElemMap[it->first] -> rightThread = true;
    newKeyElemMap[it->first] -> right = newRoot;

    // then thread the rest of the tree backwardly
    it++;
    while(it != origKeyElemMap.rend()){
        if (it->second->rightThread){
            newKeyElemMap[it->first] -> rightThread = true;
            newKeyElemMap[it->first] -> right = newKeyElemMap[ origKeyElemMap[it->first]->right->key ];
        }
        it++;
    }
}

// common copy code for deep copy a tree without copying threads
template <typename KEY, typename T>
void  Map<KEY,T>::copyCode(Elem* &newRoot, Elem* origRoot){
    if (origRoot == 0)
        newRoot = 0;
    else{
        newRoot = new Elem;
        newRoot->key = origRoot->key;
        newRoot->data = origRoot->data;
        newRoot->rightThread = origRoot->rightThread;
        newRoot->height = origRoot->height;
        copyCode(newRoot->left, origRoot->left);
        if (!origRoot->rightThread)
            copyCode(newRoot->right, origRoot->right);
    }
}



template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::begin() const {  // return the left most (smallest) tree node
    // fill in here
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

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::end() const {  // return the dummy root node
    // fill in here
    Iterator it(_root);
    return it;
}


template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::Iterator::operator++(int){
    // fill in here
    if (_cur) {
        if (!_cur->right) {
            _cur = _cur->right;
        } else {
            if (!_cur->rightThread) {
                if (_cur->right->left) {
                    _cur = _cur->right->left;
                    while (_cur->left)
                        _cur = _cur->left;
                } else
                    _cur = _cur->right;
            } else
                _cur = _cur->right;
        }
    }
    return *this;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator==(Iterator it) {
    return _cur == it._cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator!=(Iterator it) {
    return _cur != it._cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem& Map<KEY, T>::Iterator::operator*(){
    // fill in here
    return *_cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::Iterator::operator->(){
    // fill in here
    return _cur;
}

template <typename KEY, typename T>
int Map<KEY, T>::size() const{
    return _size;
}

// return an iterator pointing to the end if an element is not found,
// otherwise, return an iterator to the element
template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::find(KEY k) const {

    if (_root != _root->left) {
        Elem* localRoot = _root->left;
        while (localRoot) {
            if (k < localRoot->key)
                localRoot = localRoot->left;
            else if (k > localRoot->key) {
                if (localRoot->rightThread)
                    localRoot = 0;
                else
                    localRoot = localRoot->right;
            } else
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

// overloaded subscript operator
template <typename KEY, typename T>
T& Map<KEY, T>::operator[](KEY k) {
    Iterator it = find(k);
    if (it == end()) {
        T data{};
        insert(k, data);
        it = find(k);
    }
    return it->data;
}


// output the structure of tree. The tree is output as "lying down"
// output each node's key, value and its tree height 
template <typename KEY, typename T>
void Map<KEY, T>::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		if (p->right && !p->rightThread)
			printTree(out, level+1,p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << "(" << p->height << ")" << '\n';
		printTree(out, level+1,p->left);
	}
}

// outputs information in tree in inorder traversal order
template <typename KEY, typename T>
ostream& Map<KEY, T>::dump(ostream& out) const{
	if ( _root == _root->left) {// tree empty
		return out;
	}
	printTree(out, 0, _root->left);   // print tree structure
	return out;
}


// outputs using overloaded << operator
template<typename KEY, typename T>
ostream& operator<< (ostream& out, const Map<KEY, T>& v){
	v.dump(out);
	return out;
}
