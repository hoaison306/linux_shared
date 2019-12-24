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

#include "processData.h"
//#include "dbLib.h"
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
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
	~L1List() { clean(); };

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

    void    reverse();

	int idx_cityName(bool(*func)(T&,string&), string & a);
	int count_cityID(bool(*func)(T&, int&), int &a);
	int count_station_cityID(bool(*func)(T&, int&), int&a);
	int* get_idxStation_cityID_equal(bool(*func)(T&, int&), int&a);
	int count_line_cityID(bool(*func)(T&, int&), int&a);
	int* get_idxLine_cityID_equal(bool(*func)(T&, int&), int&a);
	int count_stationLine_line_id(bool(*func)(T&, int&), int&a);
	int* get_idxStationLine_lineID_equal(bool(*func)(T&, int&), int&a);
	bool isFound_city_cityName(bool(*func)(T&, string&), string &a);
	bool isFound_station_name(bool(*func)(T&, string&), string &a);
	int getIndex_station_name(bool(*func)(T&, string&), string &a);
	int getIndex_station_id_equal(bool(*func)(T&, int&), int &a);
	int getIndex_track_id_equal(bool(*func)(T&, int&), int &a);
	T get_station_id_max(bool(*func)(T&, T&), T& a);
	int getIndex_stationLine_Stationid_equal(bool(*func)(T&, int&), int &a);
	int* getindex_stationline_lineid_equal(bool(*func)(T&, int&), int &a);
	int count_stationline_lineid_equal(bool(*func)(T&, int&), int &a);
	bool isFound_station_station_id(bool(*func)(T&, int&), int &a);
	int index_lineid_equal_pi_th(bool(*func)(T&, int&), int &a, int & pos);
	int getindex_track_cityid_equal(bool(*func)(T&, int&), int &a);
    void    traverse(void (*op)(T&)) {
        // TODO: Your code goes here
		L1Item<T> *new_item = _pHead;
		
		do {
			op(new_item->data);
			new_item = new_item->pNext;
		} while (new_item != NULL);

    }

    void    traverse(void (*op)(T&, void*), void* pParam) {
        // TODO: Your code goes here
		
    }
     L1Item<T>* rePo(int i) {
		L1Item<T> *new_item = _pHead;
		if (i == 0) return _pHead->pNext;
		for (int j = 0; j < i; j++) {
			new_item = new_item->pNext;
		}
		return new_item->pNext;
	}
};

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
	L1Item<T> *new_item = new L1Item<T>(a);
	if (new_item == NULL) return -1;

	if (_pHead == NULL) {
		_pHead = new_item;
		new_item->pNext = NULL;
	}
	else {
		L1Item<T> *exp = _pHead;
		while(	exp->pNext != NULL){
			exp = exp->pNext;
		}
		new_item->pNext = NULL;
		exp->pNext = new_item;

	}
	_size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
	L1Item<T> *new_item = new L1Item<T>(a);
	new_item->pNext = _pHead;
	_pHead = new_item;
	_size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
	if (_size==0) 
    return -1;
	else  {
		L1Item<T>*temp = _pHead;
		_pHead= _pHead->pNext;
		delete temp;
		

		_size--;
		return 0;
	}
	
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
	if (_size == 0)
    return -1;
	if (_size == 1) {
		_pHead = NULL;
		_size--;
		return 0;
	}
	L1Item<T> *new_item = new L1Item<T>;
	new_item = _pHead;
	while (new_item->pNext->pNext != NULL) {
		new_item = new_item->pNext;
	}
	L1Item<T> *delete_item = new L1Item<T>;
	delete_item = new_item->pNext;
	new_item->pNext = NULL;
	delete delete_item;

	_size--;
	return 0;
}



template<class T>
T& L1List<T>::at(int i) {
	L1Item<T>* temp = this->_pHead;
	for (int index = 1; index <= i; index++) temp = temp->pNext;
	return temp->data;
}


template<class T>
T& L1List<T>::operator[](int i) {
	L1Item<T> *new_item = _pHead;
	if (i == 0) return _pHead->data;
	for (int j = 0; j < i; j++) {
		new_item = new_item->pNext;
	}
	return new_item->data;
}


template<class T>
bool L1List<T>::find(T& a, int& idx) {
	L1Item<T> *new_item = _pHead;
	for (int i = 0; i < _size; i++) {
		if (new_item->data == a) {
			idx = i;
			return 1;
		}
	}
	idx = -1;
	return 0;
}


template<class T>
int L1List<T>::insert(int i, T& a) {

	if (i > this->_size || i < 0) return -1;
	L1Item<T>* pNew = new L1Item<T>(a);
	if (pNew == NULL) return -1;
	if (i == 0) {
		pNew->pNext = this->_pHead;
		this->_pHead = pNew;
		this->_size++;
		return 0;
	}
	L1Item<T>* temp = this->_pHead;
	for (int index = 0; index < i-1; index++)
		temp = temp->pNext;
	pNew->pNext = temp->pNext;
	temp->pNext = pNew;
	this->_size++;
	return 0;
	
}


template<class T>
int L1List<T>::remove(int i) {
	if (_size == 0 || i < 0 || i > _size) return -1;
	if (i == 0) removeHead();
	else {
		L1Item<T> *exp = _pHead;
		for (int j = 0; j < i -1; j++) {
			exp = exp->pNext;
		}
		L1Item<T> *temp;
		temp = exp->pNext;
		exp->pNext = exp->pNext->pNext;
		delete temp;
		_size--;
	}
}


template<class T>
void L1List<T>::reverse() {
	L1Item<T> *temp ;
	L1Item<T> *next ;
	L1Item<T> *pre;
	next = NULL;
	pre = NULL;
	temp = _pHead;
	while (temp->pNext != NULL) {
		next = temp->pNext;
		temp->pNext = pre;
		pre = temp;
		temp = next;

	}
	next = temp->pNext;
	temp->pNext = pre;
	pre = temp;
	temp = next;
	_pHead = pre;	
}


template <class T>
void L1List<T>::clean() {
	L1Item<T> *temp = new L1Item<T>;
	L1Item<T> *next = new L1Item<T>;
	temp = _pHead;
	while (temp != NULL) {
		next = temp->pNext;
		delete temp;
		temp = next;

	}
	_pHead = NULL;
}


template <class T>
int L1List<T>::idx_cityName(bool(*func)(T&, string&), string & a) {
	int idx = 0;
	L1Item<T> *temp = _pHead;

	while (temp->pNext != NULL) {
		if (p_idx_name(temp->data, a)) return idx;
		idx++;
		temp = temp->pNext;
	}
	if (p_idx_name(temp->data, a)) return idx;
	return -1;
}
 template<class T>
 int L1List<T>::count_cityID(bool(*func)(T&, int&), int &a) {
	 L1Item<T> *temp = _pHead;
	 int count = 0;
	 while (temp->pNext != NULL) {
		 if (p_idx_id(temp->data, a)) count++;
		 temp = temp->pNext;
	 }
	 if (p_idx_id(temp->data, a)) count++;
	 return count;
 }


 template<class T>
 int L1List<T> ::count_station_cityID(bool(*func)(T&, int&), int&a) {
	 L1Item<T> *temp = _pHead;
	 int count = 0;
	 while (temp->pNext != NULL) {
		 if (station_cityID(temp->data, a)) count++;
		 temp = temp->pNext;
	 }
	 if (station_cityID(temp->data, a)) count++;
	 return count;
 }
 
 template<class T>
 int* L1List<T>::get_idxStation_cityID_equal(bool(*func)(T&, int&), int&a) {
	 int count = 0;
	 L1Item<T> *temp = _pHead;
	 while (temp->pNext != NULL) {
		 if (station_cityID(temp->data, a)) count++;
		 temp = temp->pNext;
	 }
	 if (station_cityID(temp->data, a)) count++;
	 int* res;
	 int* qq = new int[count];
	 L1Item<T> *item = _pHead;
	 int i = 0;
	 int idx = 0;
	 while (item->pNext != NULL) {
		 if (station_cityID(item->data, a)) {
			 qq[i] = idx;
			 i++;
		 }
		 idx++;
		 item = item->pNext;
	 }
	 if (station_cityID(item->data, a)) {
		 qq[i] = idx;
		 i++;
	 }
	 return qq;
 }

 template<class T>
 int L1List<T> ::count_line_cityID(bool(*func)(T&, int&), int&a) {
	 L1Item<T> *temp = _pHead;
	 int count = 0;
	 while (temp->pNext != NULL) {
		 if (line_city_id(temp->data, a)) count++;
		 temp = temp->pNext;
	 }
	 if (line_city_id(temp->data, a)) count++;
	 return count;
 }

 template<class T>
 int* L1List<T>::get_idxLine_cityID_equal(bool(*func)(T&, int&), int&a) {
	 int count = 0;
	 L1Item<T> *temp = _pHead;
	 while (temp->pNext != NULL) {
		 if (line_city_id(temp->data, a)) count++;
		 temp = temp->pNext;
	 }
	 if (line_city_id(temp->data, a)) count++;
	 int* qq = new int[count];
	 L1Item<T> *item = _pHead;
	 int i = 0;
	 int idx = 0;
	 while (item->pNext != NULL) {
		 if (line_city_id(item->data, a)) {
			 qq[i] = idx;
			 i++;
		 }
		 idx++;
		 item = item->pNext;
	 }
	 if (line_city_id(item->data, a)) {
		 qq[i] = idx;
		 i++;
	 }
	 return qq;
 }

 template<class T>
 int L1List<T>:: count_stationLine_line_id(bool(*func)(T&, int&), int&a) {
	 int count = 0;
	 L1Item<T> *temp = _pHead;
	 while (temp->pNext != NULL) {
		 if (stationLine_line_id(temp->data, a)) count++;
		 temp = temp->pNext;
	 }
	 if (stationLine_line_id(temp->data, a)) count++;
	 return count;
 }

 template<class T>
 int* L1List<T>::get_idxStationLine_lineID_equal(bool(*func)(T&, int&), int&a) {
	 int count = 0;
	 L1Item<T> *temp = _pHead;
	 while (temp->pNext != NULL) {
		 if (stationLine_line_id(temp->data, a)) count++;
		 temp = temp->pNext;
	 }
	 if (stationLine_line_id(temp->data, a)) count++;
	 int* res;
	 int* qq = new int[count];
	 L1Item<T> *item = _pHead;
	 int i = 0;
	 int idx = 0;
	 while (item->pNext != NULL) {
		 if (stationLine_line_id(item->data, a)) {
			 qq[i] = idx;
			 i++;
		 }
		 idx++;
		 item = item->pNext;
	 }
	 if (stationLine_line_id(item->data, a)) {
		 qq[i] = idx;
		 
	 }
	 return qq;
 }
  template<class T>
  bool L1List<T>::isFound_city_cityName(bool(*func)(T&, string&), string &a) {
	  
	  L1Item<T>*temp = _pHead;
	  while (temp->pNext != NULL) {
		  if (p_idx_name(temp->data, a)) {
			  return 1;
			  
		  }
		  temp = temp->pNext;
	  }
	  if (p_idx_name(temp->data, a)) {
		  return 1;

	  }
	  return 0;
  }

  template<class T>
  bool L1List<T>::isFound_station_name(bool(*func)(T&, string&), string &a) {
	  L1Item<T> *temp = _pHead;
	  while (temp->pNext != NULL) {
		  if (station_name(temp->data, a))
		  {
			  return 1;
		  }
		  temp = temp->pNext;
	  }
	  if (station_name(temp->data, a))
	  {
		  return 1;
	  }
	  return 0;
  }

  template<class T>
  int L1List<T>::getIndex_station_name(bool(*func)(T&, string&), string &a) {
	  int i = 0;
	  L1Item<T>*temp = _pHead;
	  while (temp->pNext != NULL) {
		  if (station_name(temp->data, a)) return i;
		  i++;
		  temp = temp->pNext;
	  }
	  if (station_name(temp->data, a)) return i;
	  return -1;
  }

  template<class T>
  int L1List<T>:: getIndex_station_id_equal(bool(*func)(T&, int&), int &a) {
	  int i = 0;
	  L1Item<T> *temp = _pHead;
	  while (temp->pNext != NULL) {
		  if (station_id(temp->data, a)) return i;
		  i++;
		  temp = temp->pNext;
	  } 
	  if (station_id(temp->data, a)) return i;
	  

	  return -1;
  }

  template<class T>
  int L1List<T>::getIndex_track_id_equal(bool(*func)(T&, int&), int &a) {
	  int i = 0;
	  L1Item<T> *temp = _pHead;
	  while (temp->pNext != NULL) {
		  if (track_id(temp->data, a)) return i;
		  i++;
		  temp = temp->pNext;
	  }
	  if (track_id(temp->data, a)) return i;
	  return -1;
  }

  template<class T>
  T L1List<T>:: get_station_id_max(bool(*func)(T&, T&), T& a) {
	  L1Item<T> *temp = _pHead;
	  a = temp->data;
	  while (temp->pNext != NULL) {
		  if (station_id_bt(temp->data, a)) {
			  a = temp->data;
		  }
		  temp = temp->pNext;
	  }
	  if (station_id_bt(temp->data, a)) {
		  a = temp->data;
	  }
	  return a;
  }

  template<class T>
	  int L1List<T>::getIndex_stationLine_Stationid_equal(bool(*func)(T&, int&), int &a) {
	  int i = 0;
	  L1Item<T> *temp = _pHead;
	  while (temp->pNext != NULL) {
		  if (stationLine_station_id(temp->data, a)) return i;
		  i++;
		  temp = temp->pNext;
	  }
	  if (stationLine_station_id(temp->data, a)) return i;
	  i++;
	  return -1;
  }



	  template<class T>
	  int* L1List<T>::getindex_stationline_lineid_equal(bool(*func)(T&, int&), int &a) {
		  L1Item<T>*temp = _pHead;
		  int i = 0;
		  int index = 0;
		  while (temp->pNext != NULL) {
			  if (stationLine_line_id(temp->data, a)) {
				  index++;
			  }
			  temp = temp->pNext;
		  }
		  if (stationLine_line_id(temp->data, a)) index++;;
		  int*qq = new int[index];

		  L1Item<T>*temp1 = _pHead;
		  int pos = 0;
		  while (temp1->pNext != NULL) {
			  if (stationLine_line_id(temp1->data, a)) {
				  qq[i] = pos;
				  i++;
			  }
			  pos++;
			  temp1 = temp1->pNext;
		  }
		  if (stationLine_line_id(temp1->data, a)) qq[i] = pos;
		  return qq;
	  }
	

	  template<class T>
	  int L1List<T>::count_stationline_lineid_equal(bool(*func)(T&, int&), int &a) {
		  L1Item<T>*temp = _pHead;
		  int index = 0;
		  while (temp->pNext != NULL) {
			  if (stationLine_line_id(temp->data, a)) {
				  index++;
			  }
			  temp = temp->pNext;
		  }
		  if (stationLine_line_id(temp->data, a)) index++;
		  return index;
	  }

	  template<class T>
	  bool L1List<T>::isFound_station_station_id(bool(*func)(T&, int&), int &a) {
		  L1Item<T> *temp = _pHead;
		  bool res = 0;
		  while (temp->pNext != NULL) {
			  if (station_id(temp->data, a)) return 1;
			  temp = temp->pNext;
		  }
		  if (station_id(temp->data, a)) return 1;
		  return 0;
	  }

	  template<class T>
	  int L1List<T>::index_lineid_equal_pi_th(bool(*func)(T&, int&), int &a, int & pos) {
		  int index = 0;
		  int count = -1;
		  L1Item<T>*temp = _pHead;
		  while (temp->pNext != NULL) {
			  if (stationLine_line_id(temp->data, a)) {
				  count++;
			  }
			  if (count == pos) return index;
			  index++;
			  temp = temp->pNext;
		  }
		  if (stationLine_line_id(temp->data, a)) {
			  count++;
		  }
		  if (count == pos) return index;
		  if (count == pos - 1) return index++;
		  return -1;
	  }

	  template <class T>
		 int L1List<T>::getindex_track_cityid_equal(bool(*func)(T&, int&), int &a){
			 int i = 0;
			 L1Item<T> *temp = _pHead;
			 while (temp->pNext != NULL) {
				 if (track_cityid(temp->data, a)) return i;
				 i++;
				 temp = temp->pNext;
			 }
			 if (track_cityid(temp->data, a)) return i;
			 return -1;
		 }
#endif //DSA191_A1_DSALIB_H
