/* CS515 Assignment 12
File: PQueue.cpp
Name: Biao Zhang
Section: 1
Date: 12/08/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
template< class T, int MAX_SIZE >
PQueue<T,MAX_SIZE>::PQueue()
{
    _size = 0;
}

template< class T, int MAX_SIZE >
PQueue<T,MAX_SIZE>::PQueue(T* items, int size)
{
    _size = size;
    for (int i = 0; i < size; i++)
        _array[i+1] = items[i];

    buildHeap();
}

template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::insert(T item)
{
    if (_size < MAX_SIZE) {
        _size++;
        _array[_size] = item;
        moveUp();
    }
}

template< class T, int MAX_SIZE >
T PQueue<T,MAX_SIZE>::findMin()
{
    return _array[1];
}

template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::deleteMin()
{
    _array[1] = _array[_size];
    _size--;

    moveDown(1);
}

template< class T, int MAX_SIZE >
bool PQueue<T,MAX_SIZE>::isEmpty()
{
    return (_size == 0) ? true : false;
}

template< class T, int MAX_SIZE >
int PQueue<T,MAX_SIZE>::size()
{
    return _size;
}

template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::buildHeap()
{
    for (int i = _size / 2 + 1; i >= 1; i--)
        moveDown(i);
}

template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::moveDown(int index)
{
    T tmp;
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

template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::moveUp()
{
    int index = _size;
    T tmp;
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

