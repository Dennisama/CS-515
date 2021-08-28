/** CS515 Lab 4
File: queue.cpp
Name: Biao Zhang
Section: 01
Date: 10/03/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/

#include "queue.h"

// singly linked list implementation of queue
// empty queue is represented by null front and rear pointers

queue::queue(){
    // creates an empty queue
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

queue::~queue(){
    node * curr = _front;
    while (curr) {
        curr = curr->next;
        delete _front;
        _size--;
        _front = curr;
    }
}

// copy constructor
queue::queue(const queue &v){
    if (v._front == nullptr)
        return;

    // Deep copy
    _size = 0;
    node * temp = v._front;
    _front = new node(temp->data);
    _rear = _front;
    _size++;
    temp = temp->next;
    while (temp != nullptr) {
        enqueue(temp->data);
        temp = temp->next;
    }
}

// assignment operator
queue& queue::operator=(const queue &rhs){
    if (this == &rhs)
        return *this;

    // ~queue()
    node * curr = _front;
    while (curr) {
        curr = curr->next;
        delete _front;
        _size--;
        _front = curr;
    }

    if (rhs._size > 0) {
        // Deep copy
        node * temp = rhs._front;
        _front = new node(temp->data);
        _rear = _front;
        _size++;
        temp = temp->next;
        while (temp != nullptr) {
            enqueue(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

void queue::enqueue(const TYPE data){
    node * n = new node(data);
    if (_rear) {
        n->next = _rear->next;
        _rear->next = n;
        if (n->next == nullptr)
            _rear = n;
    } else {
        _front = n;
        _rear = n;
    }

    _size++;
}

TYPE queue::dequeue(){
	TYPE val;
	if (_front) {
        node * n = _front;
        _front = n->next;
        val = n->data;
        delete n;
        _size--;
	} else
	    throw EmptyQueueException();

	// In the case after we dequeue
	// one last element, there should
	// be no item in the queue
	if (!_front)
	    _rear = nullptr;

	return val;
}

void queue::dump(ostream &os){
    node * n = _front;
    while (n) {
        os << n->data << " ";
        n = n->next;
    }
    os << endl;
}

int queue::size(){
    return _size;
}

bool queue::empty(){
    return (_size == 0) ? true : false;
}

