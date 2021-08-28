/** CS515 Lab 3
File: stack.cpp
Name: Biao Zhang
Section: 01
Date: 9/22/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/

#include "stack.h"

// constructor with default capacity
stack::stack(int cap)
: _tos(-1), _capacity(cap)
{
    _arr = new int[cap];
}

// copy constructor
stack::stack(const stack& s)
: _tos(s._tos), _capacity(s._capacity)
{
    _arr = new int[_capacity];
    if (_tos >= 0) {
        for (int i = 0; i <= _tos; ++i)
            _arr[i] = s._arr[i];
    }
}

// assignment operator
stack& stack::operator=(const stack& s)
{
    if (this == &s)
        return *this;
    delete []_arr;
    _tos = s._tos;
    _capacity = s._capacity;
    if (_tos >= 0) {
        _arr = new int[_capacity];
        for (int i = 0; i <= _tos; ++i)
            _arr[i] = s._arr[i];
    }

    return *this;
}

//move constructor
stack::stack(stack&& s)
{
    _tos = s._tos;
    _capacity = s._capacity;
    _arr = s._arr;
    s._arr = nullptr;
    s._capacity = 0;
    s._tos = -1; //set it to an "empty" state.
}

//move assignment operator
stack& stack::operator=(stack&& s)
{
    if (this == &s)
        return *this;
    delete []_arr;
    _tos = s._tos;
    _capacity = s._capacity;
    _arr = s._arr;
    s._arr = nullptr;
    s._capacity = 0;
    s._tos = -1; //set it to an "empty" state.

    return *this;
}

// destructor
stack::~stack()
{
    delete []_arr;
}

void stack::push(const TYPE x)
{
    if(size() >= _capacity)
        throw FullStackException();

    _arr[++_tos] = x;
}

void stack::pop()
{
    if(empty())
        throw EmptyStackException();

    _tos--;
}

TYPE& stack::top()
{
    if(empty())
        throw EmptyStackException();

    return _arr[_tos];//Why does here return the reference ?
}

bool stack::empty()
{
    return (_tos < 0) ? true : false;
}

int stack::size()
{
    return (_tos + 1);
}

int stack::capacity()
{
    return _capacity;
}