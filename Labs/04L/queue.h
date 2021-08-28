/** CS515 Lab 4
File: queue.cpp
Name: Biao Zhang
Section: 01
Date: 10/03/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/

#include <iostream>
#include <cstdlib>

#define TYPE int

using namespace std;

class EmptyQueueException{};

struct node{
	node(TYPE x, node * n=0):data(x), next(n){}

	TYPE data;
	node * next;
	
};

class queue{
public:
    // default constructor
    queue();
    
    // copy constructor
    queue(const queue &v);
    
    // assignment operator
    queue& operator=(const queue &rhs);
    
    // destructor
    ~queue();
    
    // add an element to the end of queue
    void enqueue(const TYPE);
    
    // remove an element from the front of queue
    // throws EmptyQueueException if queue is empty
    TYPE dequeue();
    
    // output queue elements to ostream
    // output from queue front to queue end; output nothing if queue is empty
    void dump(ostream &os);
    
    // return the number of elements currently in the queue
    int size();
    
    // return true if the queue is empty, false otherwise
    bool empty();  
    
private:
    // ***feel free to add more methods here, such as common***
    // ***methods for copy and destruction operations       ***

    node * _front;//front of the queue where dequeueing happens
    node * _rear; //rear of the queue where enqueueing happen
    int _size; 
};
