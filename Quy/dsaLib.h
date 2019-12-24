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
	L1Item<T>	*_pEnd;
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _pEnd(NULL), _size(0) {}
    ~L1List();

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

	L1Item<T>* getHead(){
		return _pHead;
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

    void    reverse();

    void    traverse(void (*op)(T&)) {
        // TODO: Your code goes here
		L1Item<T>* temp = this->_pHead;
		int i = 0;
		while (temp->pNext != NULL && i < this->_size) {
			op(temp->data);
			temp = temp->pNext;
			i++;
		}
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        // TODO: Your code goes here
    }
	
	int findFirst(bool (*compare)(const T&, const T&), const T& data1, T& p) {
		L1Item<T>* temp = this->_pHead;
		while (temp->pNext != NULL) {
			if (!compare(temp->data, data1)) temp = temp->pNext;
			else {
				p = temp->data;
				return 0;
			}
		}
		if (compare(temp->data, data1)) {
			p = temp->data;
			return 0;
		}
		return -1;
	}
	int findSize(bool (*compare)(const T&, const T&), const T& data1, int& len) {
		L1Item<T>* temp = this->_pHead;
		len = 0;
		while (temp->pNext != NULL) {
			if (compare(temp->data, data1)) len++; 
			temp = temp->pNext;
		}
		if (compare(temp->data, data1)) len++;
		return (len == 0) ? -1 : 0;
	}
	T* findArr(bool (*compare)(const T&, const T&), const T& data1, const int& len) {
		L1Item<T>* temp = this->_pHead;
		if (len == 0) return NULL;
		T* arr = new T[len];
		int idx = 0;
		while (temp->pNext != NULL) {
			if (compare(temp->data, data1)) { 
				arr[idx] = temp->data;
				idx++;
			}
			temp = temp->pNext;
		}
		if (compare(temp->data, data1)) arr[idx] = temp->data;
		return arr;
	}
	T findMax(bool (*compare)(const T&, const T&)) {
		L1Item<T>* temp = this->_pHead;
		T max = temp->data;
		temp = temp->pNext;
		while (temp->pNext != NULL) {
			if (compare(max, temp->data)) max = temp->data;
			temp = temp->pNext;
		}
		if (compare(max, temp->data)) max = temp->data;
		return max;
	}
	template <class V>
	int remove_lineStr(bool (*compare)(T&, const T&), const V& data1) {
		if (isEmpty()) return -1;
		L1Item<T>* temp = this->head;
		while (temp != nullptr) {
			compare(temp->data, data1);
			temp = temp->pNext;
		}
	}
	int remove(bool (*compare)(const T&, const T&), const T& data1, T& data2) {
		if (isEmpty()) return -1;
		L1Item<T>* temp = this->_pHead;
		L1Item<T>* tempDel = this->_pHead;
		L1Item<T>* pre = this->_pHead;
		bool isFound = false;
		while (temp->pNext != NULL) {
			if (temp == _pHead && compare(temp->data, data1)) {
				isFound = true;
				_pHead = temp->pNext;
				temp = _pHead;
				data2 = tempDel->data;
				delete tempDel;
				_size--;
				tempDel = temp;
			}
			else if (temp != _pHead && compare(temp->data, data1)){
				isFound = true;
				temp = temp->pNext;
				pre->pNext = temp;
				data2 = tempDel->data;
				delete tempDel;
				_size--;
				tempDel = temp;
			}
			else {
				pre = temp;
				temp = temp->pNext;
				tempDel = temp;
			}
		}
		if (temp == _pHead && compare(temp->data, data1)) {
			isFound = true;
			_pHead = temp->pNext;
			temp = _pHead;
			data2 = tempDel->data;
			delete tempDel;
			_size--;
			tempDel = temp;
		}
		else if (temp != _pHead && compare(temp->data, data1)) {
			isFound = true;
			temp = temp->pNext;
			pre->pNext = temp;
			data2 = tempDel->data;
			delete tempDel;
			_size--;
			tempDel = temp;
		}
		return (isFound) ? 0 : -1;
	}
	int findUpdate(bool (*compare)(const T&, const T&), const T& data1, const T& data2, T& save) {
		L1Item<T>* temp = this->_pHead;
		while (temp->pNext != NULL) {
			if (!compare(temp->data, data1)) temp = temp->pNext;
			else {
				save = temp->data;
				temp->data = data2;
				return 0;
			}
		}
		if (compare(temp->data, data1)) {
			save = temp->data;
			temp->data = data2;
			return 0;
		}
		return -1;
	}
	int insertAtIdx(bool (*compare)(const T&, const T&), const T& data1, T& data2, const int idx, const bool b) {
		L1Item<T>* temp = this->_pHead;
		L1Item<T>* pre = this->_pHead;
		int i = 0;
		while (temp->pNext != NULL) {
			if (compare(temp->data, data1)) { 
				if (i < idx) { 
					i++; 
					pre = temp;
					temp = temp->pNext;
				}
				else break;
			}
			else { 
				if (i < idx) {
					pre = temp;
					temp = temp->pNext;
				}
				else break;
			}
		}
		L1Item<T>* pNew = new L1Item<T>(data2);
		if (!b) {
			if (temp == _pHead && pre == _pHead) {
				pNew->pNext = _pHead;
				_pHead = pNew;
			}
			else {
				pNew->pNext = pre->pNext;
				pre->pNext = pNew;
			}
		}
		else {
			pNew->pNext = temp->pNext;
			temp->pNext = pNew;
		}
		_size++;
		return 0;
	}
	int removeWithData(bool (*compare)(const T&, const T&), const T& data1) {
		L1Item<T>* temp = _pHead;
		L1Item<T>* pre = _pHead;
		while (temp->pNext != NULL) {
			if (!compare(temp->data, data1)) {
				pre = temp;
				temp = temp->pNext;
			}
			else break;
		}
		if (!compare(temp->data, data1)) return -1;
		if (temp == _pHead) {
			_pHead = temp->pNext;
			delete temp;
			_size--;
		}
		else {
			pre->pNext = temp->pNext;
			delete temp;
			_size--;
		}
		return 0;
	}

};

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
	L1Item<T>* pNew = new L1Item<T>(a);
	if (pNew == NULL) return -1;
	if (_pHead == NULL) {
		pNew->pNext = _pHead;
		_pHead = pNew;
		_pEnd = pNew;
	}
	else {
		/*L1Item<T>* temp = this->_pHead;
		while (temp->pNext != NULL) temp = temp->pNext;*/
		L1Item<T>* temp = this->_pEnd;
		pNew->pNext = NULL;
		temp->pNext = pNew;
		_pEnd = pNew;
	}
	this->_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
	L1Item<T>* pNew = new L1Item<T>(a);
	if (pNew == NULL) return -1;
	pNew->pNext = this->head;
	this->head = pNew;
	this->_size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
	if (isEmpty()) return -1;
	else {
		L1Item<T>* pLoc = _pHead;
		this->_pHead = pLoc->pNext;
		this->_size--;
		delete pLoc;
		return 0;
	}
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
	if (isEmpty()) return -1;
	else {
		L1Item<T>* pLoc = this->_pHead;
		L1Item<T>* pPre = this->_pHead;
		while (pLoc->pNext != NULL) {
			pPre = pLoc;
			pLoc = pLoc->pNext;
		}
		pPre->pNext = NULL;
		_pEnd = pPre;
		delete pLoc;
		this->_size--;
		return 0;
	}
}
template <class T>
T& L1List<T>::at(int i) {
	L1Item<T>* temp = this->_pHead;
	for (int index = 1; index <= i; index++) temp = temp->pNext;
	return temp->data;
}

template <class T>
T& L1List<T>::operator[](int i) {
	return at(i);
}

template <class T>
bool L1List<T>::find(T& a, int& idx) {
	L1Item<T>* temp = this->_pHead;
	for (int i = 0; i < this->_size; i++) {
		if (temp->data != a) temp = temp->pNext;
		else { 
			idx = i; 
			break;
		}
	}
	if (temp == NULL) return 0;
	else return 1;
}

template <class T>
int L1List<T>::insert(int i, T& a) {
	if (i >= this->_size || i < 0) return -1;
	L1Item<T>* pNew = new L1Item<T>(a);
	if (pNew == NULL) return -1;
	if (i == 0) {
		pNew->pNext = this->_pHead;
		this->_pHead = pNew;
		this->_size++;
		return 0;
	}
	L1Item<T>* temp = this->_pHead;
	for (int index = 0; index < i; index++)	temp = temp->pNext;
	pNew->pNext = temp->pNext;
	temp->pNext = pNew;
	this->_size++;
	return 0;
}

template <class T>
int L1List<T>::remove(int i) {
	if (i >= this->_size || i < 0) return -1;
	if (this->_pHead == NULL) return -1;
	else {
		if (i == 0) return removeHead();
		else if (i == _size - 1) return removeLast();
		else {
			L1Item<T>* temp = this->_pHead;
			L1Item<T>* pre = this->_pHead;
			for (int index = 0; index < i; index++) {
				pre = temp;
				temp = temp->pNext;
			}
			pre->pNext = temp->pNext;
			delete temp;
			this->_size--;
			return 0;
		}
	}
}

template <class T>
void L1List<T>::clean() {
	L1Item<T>* temp;
	this->_pEnd = NULL;
	while (this->_pHead != NULL) {
		temp = this->_pHead;
		this->_pHead = this->_pHead->pNext;
		delete temp;
	}
	this->_size = 0;
}

template <class T>
L1List<T>::~L1List() {
	this->clean();
}

template <class T>
void L1List<T>::reverse() {
	L1Item<T>* current = _pHead;
	L1Item<T>* prev = NULL, * next = NULL;

	while (current != NULL) {
		next = current->pNext;
		current->pNext = prev;
		prev = current;
		current = next;
	}
	_pHead = prev;
}

#endif //DSA191_A1_DSALIB_H
