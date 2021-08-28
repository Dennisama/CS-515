/** CS515 Lab 8
File: set.cpp
Name: Biao Zhang
Section: 01
Date: 11/01/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include "set.h"

Set::Set() {
    _size = 0;
    _root = new TrieNode;
}

// insert a key into the set
// return false if key already exists; otherwise insert new key and return true
bool Set::insert(string s){
    TrieNode* curr = _root;
    bool is_exist = true;

    for (int i = 0; i < s.length(); i++) {
        int index = s[i] - 'a';
        if (!curr->child[index]) {
            curr->child[index] = new TrieNode;
            is_exist = false;
        }
        curr = curr->child[index];
    }

    // The string does not exist.
    if (!is_exist) {
        curr->isWord = true;
        _size++;
    }

    // The string is a substring of the current string.
    if (!curr->isWord) {
        is_exist = false;
        curr->isWord = true;
        _size++;
    }

    return !is_exist;
}

// remove a key from the set
// return false if the key doesn't exist; otherwise remove key and return true
bool Set::erase(string s) {
    TrieNode* curr = _root;
    for (int i = 0; i < s.length(); i++) {
        int index = s[i] - 'a';

        if (!curr->child[index])
            return false;

        curr = curr->child[index];
    }

    if (!curr->isWord)
        return false;

    curr->isWord = false;
    _size--;
    return true;
}

// search for a key
// return true if an element is found; false otherwise
bool Set::find(string s) {
    TrieNode* curr = _root;
    for (int i = 0; i < s.length(); i++) {
        int index = s[i] - 'a';

        if (!curr->child[index])
            return false;

        curr = curr->child[index];
    }

    if (!curr->isWord)
        return false;

    return true;
}

// return size of the set
int Set::size() {
    return _size;
}