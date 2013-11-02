/**
 *  @file      sequence-list.h
 *  @brief     Data structure: sequence list
 *  @brief     *Still some unsolved bugs exists.*
 *  @author    Darren Liu (MSR.B, msr-b)
 *  @date      2013/10/11
 *  @copyright Copyright (c) 2013 Darren Liu. All rights reserved.
 */

#ifndef _SEQUENCE_LIST_H_
#define _SEQUENCE_LIST_H_
/// @brief enabling va_list
#include <cstdarg>
#include <cstdlib>
#include <cstring>
/// @brief test type, avoid type improvment error
#include <typeinfo>
#include "range.h"

/// @brief Data structure: sequence list
template <typename _Ty>
class SequenceList {
public:
	/// @brief default
	SequenceList() : _n (0) {
		this -> _list = (_Ty *) malloc (sizeof (_Ty));
	}
	/**
	 *  @brief sequence list can be initialized with any amount of values
	 *  @param arg1   (_Ty) arg1
	 *  @param arg2   (_Ty) arg2
	 *  @param arg3   (_Ty) arg3
	 *  ...
	 *  @param argEnd (_Ty) ended with logical null of your type
	 */
	SequenceList (_Ty arg, ...) : _n (0) {
		va_list vl;
		const char *typeName = typeid (_Ty).name();
		this -> _list = (_Ty *) malloc (sizeof (_Ty));
		va_start (vl, arg);
		while (1) {
			/// @brief WARNING! this will cause error in many occasions
			if (!arg) {
				break;
			}
			this -> push (arg);
			if (!strcmp (typeName, typeid (char).name())) {
				arg = va_arg (vl, int);
			} else if (!strcmp (typeName, typeid (float).name())) {
				arg = va_arg (vl, double);
			} else {
				arg = va_arg (vl, _Ty);
			}
		}
		va_end (vl);
	}

	/**
	 *  @brief copy constructor
	 *
	 *  @param list (const SequenceList&) list you want to copy
	 */
	SequenceList (const SequenceList &list) : _n (list._n) {
		_Ty *newList = (_Ty *) malloc ( (list._n + 1) * sizeof (_Ty));
		for (int i = 0; i < _n; i++) {
			newList[i] = list[i];
		}
		_list = newList;
	}
	/**
	 *  @brief  push element into the sequence list
	 *
	 *  @param  x     (const _Ty&) element pushed
	 *
	 *  @return succeeded or not
	 *  @retval true  push succeded
	 *  @retval false push failed
	 */
	bool push (const _Ty &x) {
		_Ty *newList = (_Ty *) realloc (_list, (_n + 2) * sizeof (_Ty));
		if (!newList) {
			return false;
		}
		newList[_n++] = x;
		_list = newList;
		return true;
	}
	/**
	 *  @brief  merge a Range<_Ty> object
	 *
	 *  @param  range (const _Ty&) your range
	 *
	 *  @return succeeded or not
	 *  @retval true  merge succeded
	 *  @retval false merge failed
	 *  @see    bool push(const _Ty& x)
	 */
	bool merge (const Range<_Ty> &range) {
		_Ty lower = range.getLower();
		_Ty upper = range.getUpper();
		for (_Ty i = lower; i <= upper; i++) {
			if (!push (i)) {
				return false;
			}
		}
		return true;
	}
	/**
	 *  @brief  merge a SequenceList<_Ty> object
	 *
	 *  @param  list  (const _Ty&) your list
	 *
	 *  @return succeeded or not
	 *  @retval true  merge succeded
	 *  @retval false merge failed
	 *  @see    bool push(const _Ty& x)
	 */
	bool merge (const SequenceList<_Ty> &list) {
		for (int i = 0; i < list.count(); i++) {
			if (!push (list[i])) {
				return false;
			}
		}
		return true;
	}
	/**
	 *  @brief  return element at index, exit when violence access
	 *
	 *  @param  pos   (const int&) index
	 *
	 *  @return element at index
	 */
	_Ty &at (const int &pos) const {
		if (pos < _n) {
			return (_list) [pos];
		}
		exit (EXIT_FAILURE);
	}
	/**
	 *  @brief  same as at()
	 *
	 *  @param  pos   (const int&) index
	 *
	 *  @return element at index
	 *  @see    _Ty& at(const int& pos) const
	 */
	_Ty &operator[] (const int &pos) const {
		return at (pos);
	}
	/**
	 *  @brief  find whether a element in list
	 *  @param  x     element
	 *  @return in or not
	 *  @retval true  in
	 *  @retval false not in
	 */
	bool in (const _Ty &x) const {
		for (int i = 0; i < _n; i++) {
			if (_list[i] == x) {
				return true;
			}
		}
		return false;
	}
	/**
	 *  @brief  get amount of elements in list
	 *  @return element amount
	 */
	int count() const {
		return _n;
	}
	/// @brief destructor of sequence list
	~SequenceList() {
		delete _list;
	}
private:
	/// @brief list pointer
	_Ty *_list;
	/// @brief element amount
	int _n;
};

#endif