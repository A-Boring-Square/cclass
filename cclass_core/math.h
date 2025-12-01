#ifndef C_CLASS_CORE_MATH_HCLASS
#define C_CLASS_CORE_MATH_HCLASS
#include "cclass.h"
#include <stdint.h>
#include <stdbool.h>

/*
 Checks if a number is a power of two
 NOTE(A-Boring-Square): Mostly used by SIMD code
*/
#define IsPowerOf2(X) ((X) != 0 && (((X) & ((X) - 1)) == 0))



#endif // C_CLASS_CORE_MATH_HCLASS