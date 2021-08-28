/* CS515 Assignment 10
File: unorderedmap.cpp
Name: Biao Zhang
Section: 1
Date: 11/19/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
// Below are the stubs for SOME methods
// Make sure all methods in unorderedmap.h are implemented

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::UnorderedMap(){
    tablesize = 101;
    entrysize = 0;
    array = new Entry *[tablesize] {};
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::UnorderedMap(const UnorderedMap& rhs){
    tablesize = rhs.tablesize;
    entrysize = rhs.entrysize;
    array = new Entry *[tablesize] {};
    if (rhs.entrysize) {
        Entry *old_tmp, *prev_tmp, *copy_entry;
        for (int i = 0; i < tablesize; i++) {
            old_tmp = rhs.array[i];
            prev_tmp = 0;
            copy_entry = 0;
            while (old_tmp) {
                copy_entry = new Entry(old_tmp->key, old_tmp->data);
                copy_entry->next = 0;
                if (prev_tmp) {
                    prev_tmp->next = copy_entry;
                    prev_tmp = prev_tmp->next;
                } else {
                    array[i] = copy_entry;
                    prev_tmp = array[i];
                }
                old_tmp = old_tmp->next;
            }
        }
    }
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>& UnorderedMap<KEY, T, H>::operator=(const UnorderedMap& rhs){
    if (this == &rhs)
        return *this;
    if (entrysize) {
        Entry* tmp;
        for (int i = 0; i < tablesize; i++) {
            if (array[i]) {
                while (array[i]->next) {
                    tmp = array[i]->next;
                    array[i]->next = array[i]->next->next;
                    delete tmp;
                }
                tmp = array[i];
                delete tmp;
            }
        }
    }
    delete []array;
    tablesize = rhs.tablesize;
    entrysize = rhs.entrysize;
    array = new Entry *[tablesize] {};
    if (entrysize) {
        Entry *old_tmp, *prev_tmp, *copy_entry;
        for (int i = 0; i < tablesize; i++) {
            old_tmp = rhs.array[i];
            prev_tmp = 0;
            copy_entry = 0;
            while (old_tmp) {
                copy_entry = new Entry(old_tmp->key, old_tmp->data);
                copy_entry->next = 0;
                if (prev_tmp) {
                    prev_tmp->next = copy_entry;
                    prev_tmp = prev_tmp->next;
                } else {
                    array[i] = copy_entry;
                    prev_tmp = array[i];
                }
                old_tmp = old_tmp->next;
            }
        }
    }
    return *this;
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::~UnorderedMap(){
    if (entrysize) {
        Entry* tmp;
        for (int i = 0; i < tablesize; i++) {
            if (array[i]) {
                while (array[i]->next) {
                    tmp = array[i]->next;
                    array[i]->next = array[i]->next->next;
                    delete tmp;
                }
                tmp = array[i];
                delete tmp;
            }
        }
    }
    delete []array;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::insert(const KEY & newkey, const T & data){
	std::size_t key = H()(newkey);
	int k = key % tablesize;
	Entry* tmp = array[k];

	while (tmp) {
	    if (tmp->key == newkey)
	        return false;
	    tmp = tmp->next;
	}


	Entry* new_entry = new Entry(newkey, data);
	new_entry->next = array[k];
	array[k] = new_entry;
	entrysize++;

    double lambda = (double)entrysize / (double)tablesize;
	if (lambda >= 2)
	    rehash();
	return true;
}

template <typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::rehash( ){
    Entry **tmp_array = new Entry *[tablesize] {};

    if (entrysize) {
        Entry *old_tmp, *prev_tmp, *copy_entry;
        for (int i = 0; i < tablesize; i++) {
                old_tmp = array[i];
                prev_tmp = 0;
                copy_entry = 0;
                while (old_tmp) {
                    copy_entry = new Entry(old_tmp->key, old_tmp->data);
                    copy_entry->next = 0;
                    if (prev_tmp) {
                        prev_tmp->next = copy_entry;
                        prev_tmp = prev_tmp->next;
                    } else {
                        tmp_array[i] = copy_entry;
                        prev_tmp = tmp_array[i];
                    }
                    old_tmp = old_tmp->next;
                }
        }
    }

    Entry* tmp;
    for (int i = 0; i < tablesize; i++) {
        if (array[i]) {
            while (array[i]->next) {
                tmp = array[i]->next;
                array[i]->next = array[i]->next->next;
                delete tmp;
            }
            tmp = array[i];
            delete tmp;
        }
    }
    delete []array;

    array = new Entry *[nextPrime(2*tablesize)] {};
    Entry *tmp_entry, *new_entry;
    std::size_t new_key;
    int k;

    for (int i = 0; i < tablesize; i++) {
        tmp_entry = tmp_array[i];
        while (tmp_entry) {
            new_key = H()(tmp_entry->key);
            k = new_key % nextPrime(2 * tablesize);

            new_entry = new Entry(tmp_entry->key, tmp_entry->data);
            new_entry->next = array[k];
            array[k] = new_entry;

            tmp_entry = tmp_entry->next;
        }
    }

    //Entry* tmp;
    for (int i = 0; i < tablesize; i++) {
        if (tmp_array[i]) {
            while (tmp_array[i]->next) {
                tmp = tmp_array[i]->next;
                tmp_array[i]->next = tmp_array[i]->next->next;
                delete tmp;
            }
            tmp = tmp_array[i];
            delete tmp;
        }
    }
    delete []tmp_array;

    tablesize = nextPrime(2*tablesize);
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::erase (const KEY& key) {
    std::size_t e_key = H()(key);
    int k = e_key % tablesize;
    Entry* tmp = array[k];
    Entry* prev_tmp = 0;

    while (tmp) {
        if (tmp->key == key) {
            if (prev_tmp) {
                prev_tmp->next = tmp->next;
                delete tmp;
            } else {
                array[k] = tmp->next;
                delete tmp;
            }
            entrysize--;
            return true;
        }
        prev_tmp = tmp;
        tmp = tmp->next;
    }

    return false;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::find( const KEY & x ) const{
    std::size_t key = H()(x);
    int k = key % tablesize;
    Entry* tmp = array[k];

    while (tmp) {
        if (tmp->key == x) {
            Iterator it(tmp, this);
            return it;
        }

        tmp = tmp->next;
    }
	return end(); 
}


template<typename KEY, typename T, typename H>
T& UnorderedMap<KEY, T, H>::operator[](const KEY & k){
    std::size_t key = H()(k);
    int new_k = key % tablesize;
    Entry* tmp = array[new_k];

    while (tmp) {
        if (tmp->key == k)
            return tmp->data;
        tmp = tmp->next;
    }

    Entry* new_entry = new Entry;
    new_entry->key = k;
    new_entry->next = array[new_k];
    array[new_k] = new_entry;
    entrysize++;

    tmp = array[new_k];

    double lambda = (double)entrysize / (double)tablesize;
    if (lambda >= 2) {
        rehash();
        new_k = key % tablesize;
        tmp = array[new_k];

        while (tmp) {
            if (tmp->key == k)
                return tmp->data;
            tmp = tmp->next;
        }
    }

    return tmp->data;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::Iterator::operator++(int){
	if (_cur) {
	    if (_cur->next)
	        _cur = _cur->next;
	    else {
            std::size_t key = H()(_cur->key);
            int k = key % (_map->tablesize);
            bool is_out_of_bound = true;

            for (int i = k + 1; i < _map->tablesize; i++){
                if(_map->array[i]) {
                    _cur = _map->array[i];
                    is_out_of_bound = false;
                    break;
                }
            }

            if (is_out_of_bound)
                _cur = 0;
	    }
	}
	return *this;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::begin() const{
    Entry* tmp = 0;
    for (int i = 0; i < tablesize; i++) {
        if (array[i]) {
            tmp = array[i];
            break;
        }
    }
    Iterator it(tmp,this);
    return it;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::end() const{
    Iterator it(NULL,this);
    return it;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry* UnorderedMap<KEY, T, H>::Iterator::operator->(){
	return _cur;
}

template <typename KEY, typename T, typename H>
typename UnorderedMap<KEY, T, H>::Entry& UnorderedMap<KEY, T, H>::Iterator::operator*(){
	return *_cur;
}


template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator!=(Iterator it){
	return _cur != it._cur;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator==(Iterator it){
	return _cur == it._cur;
}

// Internal method to test if a positive number is prime (not efficient)
bool isPrime( int n ){
	if( n == 2 || n == 3 )
		return true;
	if( n == 1 || n % 2 == 0 )
		return false;
	for( int i = 3; i * i <= n; i += 2 )
		if( n % i == 0 )
			return false;
	return true;
}

// Internal method to return a prime number at least as large as n.
// Assumes n > 0.
int nextPrime( int n ){
	if( n % 2 == 0 )
		n++;
	for( ; !isPrime( n ); n += 2 )
		;
	return n;
}

