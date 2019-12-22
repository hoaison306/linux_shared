/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
	L1Item<T>	*_pTail;
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0), _pTail(NULL) {}
    ~L1List();

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list
	L1Item<T> *getHead() {
		return _pHead;
	}
    void    reverse();

	int findIndex(bool (*pFunc)(const T&, const T&), const T& value) {
		if (!isEmpty()) {
			L1Item<T> *p = _pHead;
			int index = 0;
			do {
				if ((*pFunc)(p->data,value)) {
					return index;
				}
				index++;
				p = p->pNext;
			} while (p != NULL);
		}
		return -1;
	}
	L1List<int> *findListOfIndexes(bool(*pFunc)(const T&, const T&), const T& value) {
		L1List<int> *listOfIndexes = new L1List<int>;
		if (!isEmpty()) {
			L1Item<T> *p = _pHead;
			int index = 0;
			do {
				if ((*pFunc)(p->data, value)) {
					listOfIndexes->push_back(index);
				}
				index++;
				p = p->pNext;
			} while (p != NULL);
		}
		return listOfIndexes;
	}
	L1List<int> *findListOfValues(bool(*pFunc)(const T&, const T&),void(*pGetValue)(L1List<int> *&, T&), const T& value) {
		/*
		* Function (*pFunc) is used to compare 2 values
		* Function (*pGetValue) is used to push the wanted value (int type) to a list
		* I use list here instead of array because I don't know the size of output until it's done
		so I'll move from list to output array later.
		*/
		L1List<int> *listOfValues = new L1List<int>;
		int i = 0;
		if (!isEmpty()) {
			L1Item<T> *p = _pHead;
			do {
				i++;
				if (i == 487) {
					std::cout << "";
				}
				if ((*pFunc)(p->data, value)) {
					(*pGetValue)(listOfValues, p->data);
				}
				p = p->pNext;
			} while (p != NULL);
		}
		return listOfValues;
	}
	void compareAndOperate(bool(*compareFunc)(const T &,const T &), void(*operateFunc)(T &, T &), T &value) {
		if (!isEmpty()) {
			L1Item<T> *p = _pHead;
			do {
				if ((*compareFunc)(p->data, value)) {
					(*operateFunc)(p->data, value);
				}
				p = p->pNext;
			} while (p != NULL);
		}
	}
    void traverseAndOperate(void (*op)(T&, T*&), T*& pParam) {
        // TODO: Your code goes here
		if (!isEmpty()) {
			L1Item<T> *p = _pHead;
			do {
				(*op)(p->data, pParam);
				p = p->pNext;
			} while (p != NULL);
		}
    }
	// For testing
	void printList() {
		if (isEmpty())
			return;
		else {
			L1Item<T> *p = _pHead;
			do {
				std::cout << p->data << '\n';
				p = p->pNext;
			} while (p != NULL);
		}
	}
};

template <class T>
L1List<T>::~L1List() {
	clean();
}

// Not tested
template <class T>
void L1List<T>::clean() {
	if (_pHead == NULL)
		return;
	else {
		L1Item<T> *p = _pHead;
		while (_pHead != NULL) {
			p = _pHead->pNext;
			delete _pHead;
			_pHead = p;
		}
		_size = 0;
		_pTail = _pHead;
	}
}
// Can't handle when i >= _size
template <class T>
T& L1List<T>::at(int i) {
	int currPos = 0;
	L1Item<T> *p = _pHead;
	while (currPos++ < i)
		p = p->pNext;
	return p->data;
}

template <class T>
T& L1List<T>::operator[](int i) {
	return at(i);
}

template <class T>
bool L1List<T>::find(T &a, int& idx) {
	if (isEmpty()) {
		idx = -1;
		return false;
	}
	else {
		L1Item<T> *p = _pHead;
		int currPos = 0;
		do {
			if (p->data == a) {
				idx = currPos;
				return true;
			}
			p = p->pNext;
			currPos++;
		} while (p != NULL);
	}
	idx = -1;
	return false;
}

template <class T>
int L1List<T>::insert(int i, T& a) {
	if (i > _size || i < 0)
		return -1;
	else if (i == 0)
		insertHead(a);
	else if (i == _size) {
		push_back(a);
	}
	else {
		L1Item<T> *newNode = new L1Item<T>(a);
		int currPos = 0;
		L1Item<T> *p = _pHead;
		while (currPos++ < i - 1) {
			p = p->pNext;
		}
		newNode->pNext = p->pNext;
		p->pNext = newNode;
		_size++;
	}
	return 0;
}

template <class T>
int L1List<T>::remove(int i) {
	if (i >= _size || i < 0)
		return -1;
	else if (i == 0)
		removeHead();
	else if (i == _size - 1)
		removeLast();
	else {
		int currPos = 0;
		L1Item<T> *p = _pHead;
		while (currPos++ < i - 1) {
			p = p->pNext;
		}
		L1Item<T> *temp = p->pNext->pNext;
		delete p->pNext;
		p->pNext = temp;
		_size--;
	}
	return 0;
}
/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
	L1Item<T> *newNode = new L1Item<T>(a);
	if (_pHead == NULL){
		_pHead = newNode;
		_pTail = newNode;
	}
	else {
		_pTail->pNext = newNode;
		_pTail = newNode;
	}
	_size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
	L1Item<T> *newNode = new L1Item<T>(a);
	newNode->pNext = _pHead;
	_pHead = newNode;
	_size++;
	if (_size == 1) _pTail = _pHead;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
	if (_pHead == NULL)
		return -1;
	else {
		L1Item<T> *p = _pHead->pNext;
		delete _pHead;
		_pHead = p;
		_size--;
		if (_size == 0) _pTail = NULL;
		return 0;
	}
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
	if (_pHead == NULL)
		return -1;
	else if (_size == 1) {
		delete _pHead;
		_pHead = NULL;
		_pTail = NULL;
	} 
	else {
		L1Item<T> *p = _pHead;
		while (p->pNext->pNext != NULL)
			p = p->pNext;
		delete p->pNext;
		p->pNext = NULL;
		_pTail = p;
	}
	_size--;
	return 0;
}

template <class T>
void L1List<T>::reverse() {
	if (_size <= 1)
		return;
	else {
		L1Item<T> *current = _pHead, *prev = NULL, *following = _pHead;
		while (current != NULL) {
			following = current->pNext;
			current->pNext = prev;
			prev = current;
			current = following;
		}
		_pHead = prev;
	}
}

#endif //DSA191_A1_DSALIB_H
