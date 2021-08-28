/* CS515 Assignment 6
File: set.cpp
Name: Biao Zhang
Section: 1
Date: 10/21/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
#include "set.h"
#include <iostream>

Set::Set()
{
    //initialSentinelNodes();
    _head = new Elem;
    _tail = new Elem;
    _head->info = ""; // The value does not matter
    _head->next = _tail;
    _head->prev = nullptr;
    _tail->info = ""; // The value does not matter
    _tail->next = nullptr;
    _tail->prev = _head;
    _size = 0;
}

// The copy constructor
Set::Set(const Set &rhs)
{
    //initialSentinelNodes();
    _head = new Elem;
    _tail = new Elem;
    _head->info = ""; // The value does not matter
    _head->next = _tail;
    _head->prev = nullptr;
    _tail->info = ""; // The value does not matter
    _tail->next = nullptr;
    _tail->prev = _head;
    _size = 0;

    if (rhs._size > 0) {
        copyCode(rhs);
    }
}

// The destructor
Set::~Set() {
    destructCode();
}

// The assignment operator
Set& Set::operator=(const Set &rhs) {
    if (this == &rhs)
        return *this;

    destructCode();

    //initialSentinelNodes();
    _head = new Elem;
    _tail = new Elem;
    _head->info = ""; // The value does not matter
    _head->next = _tail;
    _head->prev = nullptr;
    _tail->info = ""; // The value does not matter
    _tail->next = nullptr;
    _tail->prev = _head;
    _size = 0;

    if (rhs._size > 0) {
        copyCode(rhs);
    }

    return *this;
}

// Insert a string in to the set
// No duplicate, and sorted
void Set::insert(ELEMENT_TYPE val) {
    Elem *curr = _head->next;

    if (_size == 0) {
        Elem *temp = new Elem;
        temp->info = val;

        temp->next = _tail;
        temp->prev = _head;
        _head->next = temp;
        _tail->prev = temp;
        _size++;
        return;
    }

    while(curr != _tail) {
        if (curr->info > val) {
            //insert the data before curr
            Elem *temp = new Elem;
            temp->info = val;

            temp->next = curr;
            temp->prev = curr->prev;
            curr->prev->next = temp;
            curr->prev = temp;
            _size++;
            break;
        } else if (curr->info == val) {
            break; // do not take any operations
        } else {
            // The input val is the maximum
            if (curr->next == _tail) {
                // insert the data after curr
                Elem *temp = new Elem;
                temp->info = val;

                temp->prev = curr;
                temp->next = curr->next;
                curr->next->prev = temp;
                curr->next = temp;
                _size++;
                break;
            } else {
                curr = curr->next;
            }
        }
    }
}

// Remove a string from the set
void Set::erase(ELEMENT_TYPE val) {
    Elem *curr = _head->next;

    while(curr != _tail) {
        if (curr->info == val) {
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            delete curr;
            _size--;
            break;
        }

        curr = curr->next;
    }
}

// Clear all items in the set
void Set::clear() {
    Elem *temp, *curr = _head->next;

    while(curr != _tail) {
        temp = curr;
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        curr = curr->next;
        delete temp;
    }

    _size = 0;
}

// Return the size of the set
int Set::size() const {
    return _size;
}

// return an iterator to the element if val is found, or set::end() otherwise.
Set::Iterator Set::find(ELEMENT_TYPE val) const
{
    // The following operations should be overloaded
    Iterator it = begin();
    while(it != end()) {
        if(*it == val)
            return it;
        it++;
    }

    return it;
}

// return an iterator pointing at the begining of the list
Set::Iterator Set::begin() const
{
    Iterator it(_head->next);
    return it;
}

// return an iterator pointing at one element beyond the end of list
Set::Iterator Set::end() const
{
    Iterator it(_tail);
    return it;
}

// return an reverse iterator pointing at the reverse beginning of the list
Set::Reverse_Iterator Set::rbegin() const
{
    Reverse_Iterator rit(_tail->prev);
    return rit;
}

// return an reverse iterator pointing at one element beyond the beginning of list
Set::Reverse_Iterator Set::rend() const
{
    Reverse_Iterator rit(_head);
    return rit;
}

// friend top level function for output all list elements
// elements are output as a single white space delimited
ostream& operator<< (ostream& out, Set& s)
{
    //Refer to the definition of dump function
    return s.dump(out, s);
}


//**********Iterator and its methods*************//
// construct a null iterator
Set::Iterator::Iterator()
{
    _cur = nullptr;
}

// construct an iterator given pointer to Elem
Set::Iterator::Iterator(Elem* cur)
{
    _cur = cur;
}

//dereference
ELEMENT_TYPE& Set::Iterator::operator*()
{
    return _cur->info;
}

//post-increment operator
Set::Iterator Set::Iterator::operator++(int)
{
    Iterator tmp(this->_cur);
    this->_cur = this->_cur->next;
    return tmp;
}

//post-decrement operator
Set::Iterator Set::Iterator::operator--(int)
{
    Iterator tmp(this->_cur);
    this->_cur = this->_cur->prev;
    return tmp;
}

// equality operator
bool Set::Iterator::operator==(Iterator it) const
{
    return this->_cur == it._cur;
}

// inequality operator
bool Set::Iterator::operator!=(Iterator it) const
{
    return this->_cur != it._cur;
}

//*****************************************//

//**********Reverse Iterator and its methods*************//
// construct a null iterator
Set::Reverse_Iterator::Reverse_Iterator()
{
    _cur = nullptr;
}

// construct an iterator given pointer to Elem
Set::Reverse_Iterator::Reverse_Iterator(Elem* cur)
{
    _cur = cur;
}

//dereference
ELEMENT_TYPE& Set::Reverse_Iterator::operator*()
{
    return _cur->info;
}

//post-increment operator
Set::Reverse_Iterator Set::Reverse_Iterator::operator++(int)
{
    Reverse_Iterator tmp(this->_cur);
    this->_cur = this->_cur->prev;
    return tmp;
}

//post-decrement operator
Set::Reverse_Iterator Set::Reverse_Iterator::operator--(int)
{
    Reverse_Iterator tmp(this->_cur);
    this->_cur = this->_cur->next;
    return tmp;
}

// equality operator
bool Set::Reverse_Iterator::operator==(Reverse_Iterator it) const
{
    return this->_cur == it._cur;
}

// inequality operator
bool Set::Reverse_Iterator::operator!=(Reverse_Iterator it) const
{
    return this->_cur != it._cur;
}

//*****************************************//

// common code for copy constructor and assignment
void Set::copyCode(const Set & v)
{
    // Not null
    if (v._head != 0) {
        Elem *curr = v._head->next;
        // Not empty list
        while (curr != v._tail) {
            // The following codes are mainly done by insert()
            insert(curr->info);
            curr = curr->next;
        }
    }
}

// common code for deallocation
void Set::destructCode()
{
    Elem *n = _head;
    while (n) {
        n = n->next;
        delete _head;
        _head = n;
    }
    _size = 0;
}

// output set elements
ostream& Set::dump(ostream& out, const Set &v) {
    if (v._head != 0) {
        Elem *curr = v._head->next;
        while (curr != v._tail) {
            out << curr->info << " ";
            curr = curr->next;
        }
    }
    out << endl;
    return out;
}

// set intersect
Set operator&(const Set& s1, const Set& s2)
{
    Set s;
    Set::Iterator it = s1.begin();
    while(it != s1.end()) {
        if (s2.find(*it) != s2.end())
            s.insert(*it);
        it++;
    }
    return s;
}

// set union
Set operator|(const Set& s1, const Set& s2)
{
    Set s;
    Set::Iterator it = s1.begin();
    while (it != s1.end()) {
        s.insert(*it);
        it++;
    }
    it = s2.begin();
    while (it != s2.end()) {
        s.insert(*it);
        it++;
    }
    return s;
}

// set difference
Set operator-(const Set& s1, const Set& s2)
{
    Set s;
    Set::Iterator it = s1.begin();
    while (it != s1.end()) {
        if (s2.find(*it) == s2.end())
            s.insert(*it);
        it++;
    }
    return s;
}

// set equality
bool operator==(const Set& s1, const Set& s2)
{
    if (s1.size() != s2.size())
        return false;

    Set::Iterator it1 = s1.begin();
    Set::Iterator it2 = s2.begin();
    while (it1 != s1.end()) {
        if (*it1 != *it2)
            return false;
        it1++;
        it2++;
    }
    return true;
}