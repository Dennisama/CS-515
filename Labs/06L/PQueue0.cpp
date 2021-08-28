/** CS515 Lab 6
File: PQueue0.cpp
Name: Biao Zhang
Section: 01
Date: 10/17/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/
#include "PQueue0.h"

PQueue::PQueue()
{
    _size = 0;
}

PQueue::PQueue(int* items, int size)
{
    _size = size;
    for (int i = 0; i < size; i++)
        _array[i+1] = items[i];

    buildHeap();
}

void PQueue::insert(T item)
{
    if (_size < MAX_SIZE) {
        _size++;
        _array[_size] = item;
        moveUp();
    }
}

T PQueue::findMin()
{
    return _array[1];
}

void PQueue::deleteMin()
{
    _array[1] = _array[_size];
    _size--;

    moveDown(1);
}

bool PQueue::isEmpty()
{
    return (_size == 0) ? true : false;
}

int PQueue::size()
{
    return _size;
}

void PQueue::buildHeap()
{
    for (int i = _size / 2 + 1; i >= 1; i--)
        moveDown(i);
}

void PQueue::moveDown(int index)
{
    int tmp;
    bool leftOrRight;
    while ((2 * index <= _size)) {

        if (2 * index + 1 > _size)
            leftOrRight = true; // no right child
        else
            leftOrRight = (_array[2 * index] < _array[2 * index + 1]) ? true : false;

        if (leftOrRight) {
            if (_array[index] >= _array[2 * index]) {
                tmp = _array[index];
                _array[index] = _array[2 * index];
                _array[2 * index] = tmp;
                index = 2 * index;
            } else
                break;
        } else {
            if (_array[index] >= _array[2 * index + 1]) {
                tmp = _array[index];
                _array[index] = _array[2 * index + 1];
                _array[2 * index + 1] = tmp;
                index = 2 * index + 1;
            } else
                break;
        }
    }
}

void PQueue::moveUp()
{
    int index = _size;
    int tmp;
    while (!(index == 1)) {
        if (_array[index / 2] >= _array[index]) {
            tmp = _array[index / 2];
            _array[index / 2] = _array[index];
            _array[index] = tmp;
            index = index / 2;
        } else
            break;
    }
}

