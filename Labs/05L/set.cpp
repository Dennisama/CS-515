/** CS515 Lab 5
File: set.cpp
Name: Biao Zhang
Section: 01
Date: 10/08/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include "set.h"

// The default constructor
Set::Set()
{
    initialSentinelNodes();
}

// The copy constructor
Set::Set(const Set &rhs)
{
    initialSentinelNodes();
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
    initialSentinelNodes();
    if (rhs._size > 0) {
        copyCode(rhs);
    }

    return *this;
}

// Insert an int in to the set
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

// Remove an int from the set
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

// Return true if the element is found
bool Set::find(ELEMENT_TYPE val) const {
    Elem *curr = _head->next;

    while(curr != _tail) {
        if (curr->info == val)
            return true;
        curr = curr->next;
    }

    return false;
}

// The common code for copy and assignment operator
void Set::copyCode(const Set &v) {
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

void Set::destructCode() {
    Elem *n = _head;
    while (n) {
        n = n->next;
        delete _head;
        _head = n;
    }
    _size = 0;
}

// common code for building _head and _tail
void Set::initialSentinelNodes() {
    _head = new Elem;
    _tail = new Elem;
    _head->info = 0; // The value does not matter
    _head->next = _tail;
    _head->prev = nullptr;
    _tail->info = 0; // The value does not matter
    _tail->next = nullptr;
    _tail->prev = _head;
    _size = 0;
}

// private method for output set elements
ostream& Set::dump(ostream& out, const Set &v) const {
    if (v._head != 0) {
        Elem *curr = v._head->next;
        while(curr != v._tail) {
            out << curr->info << " ";
            curr = curr->next;
        }
    }
    out << endl;
    return out;
}

// Overloaded logic equality
bool operator==(const Set& s1, const Set& s2)
{
    if (s1._size != s2._size)
        return false;

    Set::Elem *cur1 = s1._head->next;
    Set::Elem *cur2 = s2._head->next;
    while (cur1 != s1._tail) {
        if (cur1->info != cur2->info)
            return false;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return true;
}

//Overloaded output operator
ostream& operator<< (ostream& out, const Set& s)
{
    // dump is a method, not the function, it should
    // be called by the object.
    return s.dump(out,s);
}

