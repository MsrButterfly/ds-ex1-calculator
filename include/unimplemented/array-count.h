#ifndef _ARRAY_COUNT_H_
#define _ARRAY_COUNT_H_
// Referenced from http://stackoverflow.com/questions/2236197/c-easiest-way-to-initialize-an-stl-vector-with-hardcoded-elements
// Answered by: David Rodríguez - dribeas
// ===START===
#include <iostream>
template <typename _Ty, std::size_t _N>
inline std::size_t ArrayCount(_Ty (&)[_N]) {
   return _N;
}
// ====END====
#endif