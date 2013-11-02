#ifndef _TYPE_H_
#define _TYPE_H_
#include <typeinfo>
template <typename _Ty>
const char *typeName (const _Ty &x) {
	return typeid (x).name();
}

// object function
// objects which are following types will be changed when no-type parameter transport
// ——char、signed char、unsigned char
// ——short、unsigned short
// ——signed short、short int、signed short int、unsigned short int
// ——float
// nonsence now...
#endif