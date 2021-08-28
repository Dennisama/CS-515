/* CS515 Assignment 4
File: queue.cpp
Name: Biao Zhang
Section: 1
Date: 10/05/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/

#include "queue.h"

// circular array implementation of queue
queue::queue(int cap)
: _front(0), _size(0), _capacity(cap)
{
    //rear = -1;  // rear used as the count of queue items
    //front = 0;  // front points to queue front
	/*for(int i=0; i<MAX_CAP; i++)
		item[i]=0;*/
	_arr = new int[cap];
}

// copy constructor
queue::queue(const queue& q)
: _front(q._front), _size(q._size), _capacity(q._capacity)
{
    _arr = new int[_capacity];

    if (_size > 0) {
        int _rear = _front + _size - 1;
        for (int i = _front; i <= _rear; i++)
            _arr[i % _capacity] = q._arr[i % _capacity];
    }
}

// assignment operator
queue& queue::operator=(const queue& q) {
    if (this == &q)
        return *this;
    delete [] _arr;
    _front = q._front;
    _size = q._size;
    _capacity = q._capacity;
    if (_size > 0) {
        int _rear = _front + _size - 1;
        _arr = new int[_capacity];
        for (int i = _front; i <= _rear; i++)
            _arr[i % _capacity] = q._arr[i % _capacity];
    }

    return *this;
}

// destructor
queue::~queue()
{
    delete [] _arr;
}

void queue::enqueue(int data){
    //item[++rear % MAX_CAP] = data;
    int _rear = _front + _size - 1;

    // The queue only expands when its capacity reaches
    // the limit.
    if (_size == _capacity) {
        int * tmp = new int[2 * _capacity];

        for (int i = _front; i <= _rear; i++) {
            if (i <= (_capacity - 1)) {
                // when it is below the capacity, the index does not change.
                tmp[i % _capacity] = _arr[i % _capacity];
            } else {
                // when it is above, it should not return to 0.
                tmp[i % (2 * _capacity)] = _arr[i % _capacity];
            }
        }

        delete [] _arr;
        _capacity = 2 * _capacity;
        _arr = tmp;
    }

    ++_size;
    _arr[++_rear % _capacity] = data;
}

int queue::dequeue() {
    if(empty())
        throw EmptyQueueException();

    --_size;
    return _arr[_front++ % _capacity];
}

int& queue::front() {
    if(empty())
        throw EmptyQueueException();

    return _arr[_front];
}

bool queue::empty() {
    return (_size == 0) ? true : false;
}

int queue::size() {
    return _size;
}

int queue::capacity() {
    return _capacity;
}

void queue::dump(ostream &os) {
    int _rear = _front + _size - 1;
    for(int i=_front; i<=_rear; i++)
        os << _arr[i % _capacity] << " ";
    os << endl;
}