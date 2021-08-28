/* CS515 Assignment 9
File: map.cpp
Name: Biao Zhang
Section: 1
Date: 11/12/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
// A generic Map implemented with right-threaded BST
// BST is not balanced

#include <map> // helper container for thread copying

template <typename KEY, typename T>
Map<KEY, T>::Map(){
	// create a dummy root node
	_root = new Elem;
	_root->left = _root;  // empty tree
	_root->right = 0;
	_root->rightThread = false;
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
		_size = 0;
	} else {
		_root = new Elem;
		_root->left = _root;
		_root->right = 0;
		copyCode(_root->left, v._root->left); // to deep copy the tree without dummy nodes
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
        _size = 0;
    } else {
        _root = new Elem;
        _root->left = _root;
        _root->right = 0;
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
    if (root){
        if (key < root->key)
            return insert(root->left, key, data, root);
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
                root->rightThread = false;
                root->right = item;
                _size++;
                return true;
            } else
                return insert(root->right, key, data, lastLeft);
        } else
            return false;
    }

    // If the added item is the left child
    // of root
    Elem* item = new Elem;
    item->key = key;
    item->data = data;
    item->left = 0;
    item->right = lastLeft;
    item->rightThread = true;
    root = item;

    _size++;
    return true;
}

// remove an element from the Map; return true if successful
template <typename KEY, typename T>
bool Map<KEY, T>::erase(KEY k){
    if (_root != _root->left) {
        Elem* parent = _root;
        Elem* localRoot = _root->left;
        while (localRoot) {
            if (k < localRoot->key) {
                parent = localRoot;
                localRoot = localRoot->left;
            } else if (k > localRoot->key) {
                parent = localRoot;
                if (parent->rightThread)
                    localRoot = 0;
                else
                    localRoot = localRoot->right;
            } else
                break;
        }

        // The searching key does not exist
        if (!localRoot)
            return false;

        bool isDone = false;
        while (!isDone) {
            if (!localRoot->left && localRoot->rightThread) {
                if (parent->right == localRoot) {
                    parent->right = localRoot->right;
                    parent->rightThread = true;
                } else {
                    if (parent == _root)
                        parent->left = _root;
                    else
                        parent->left = 0;
                }

                delete localRoot;
                _size--;
                isDone = true;
            } else if (localRoot->left && !localRoot->rightThread) {
                Elem* successor;
                // Find successor
                Elem* minElem = localRoot->right;
                parent = localRoot;
                while (minElem->left) {
                    parent = minElem;
                    minElem = minElem->left;
                }

                successor = minElem;

                //Here we just copy the data and key
                //The rightThread should remain unchanged.
                localRoot->key = successor->key;
                localRoot->data = successor->data;
                localRoot = successor;
            } else {
                if (!localRoot->rightThread) {
                    if (parent->right == localRoot)
                        parent->right = localRoot->right;
                    else
                        parent->left = localRoot->right;
                } else {
                    if (parent->right == localRoot) {
                        parent->right = localRoot->left;

                        if (localRoot->left->rightThread)
                            localRoot->left->right = localRoot->right;
                        else {
                            Elem* right_most = localRoot->left->right;
                            while(!right_most->rightThread)
                                right_most = right_most->right;
                            right_most->right = localRoot->right;
                        }
                    } else {
                        parent->left = localRoot->left;

                        if (localRoot->left->rightThread)
                            localRoot->left->right = localRoot->right;
                    }
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
    if (_root != _root->left) {
        Elem* parent = _root;
        Elem* lastLeft = _root;
        Elem* localRoot = _root->left;
        bool is_left = true;
        while (localRoot) {
            if (k < localRoot->key) {
                parent = localRoot;
                lastLeft = localRoot;
                localRoot = localRoot->left;
                is_left = true;
            } else if (k > localRoot->key) {
                parent = localRoot;
                if (parent->rightThread)
                    localRoot = 0;
                else
                    localRoot = localRoot->right;
                is_left = false;
            } else
                break;
        }

        if (!localRoot) {
            Elem* item = new Elem;
            item->right = lastLeft;
            item->rightThread = true;
            item->left = 0;
            item->key = k;
            //item->data = "";
            if (is_left)
                parent->left = item;
            else {
                parent->rightThread = false;
                parent->right = item;
            }

            _size++;
            return item->data;
        }

        return localRoot->data;
    }

    Elem* item = new Elem;
    item->right = _root;
    item->rightThread = true;
    item->left = 0;
    item->key = k;
    //item->data = "";
    _root->left = item;
    _size++;
    return item->data;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
template <typename KEY, typename T>
void Map<KEY, T>::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		if (p->right && !p->rightThread)
			printTree(out, level+1,p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << '\n';
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
