#ifndef _NIL_H_
#define _NIL_H_
#include <typeinfo>
#include <iostream>
typedef struct NIL {
} NIL;
static NIL nil;

template <typename _Ty>
bool operator==(const NIL& a, const _Ty& b) {
	return typeid(a).name() == typeid(b).name();
}

template <typename _Ty>
bool operator==(const _Ty& a, const NIL& b) {
	return typeid(a).name() == typeid(b).name();
}

// nonsence...
#endif