#ifndef C_CLASS_CORE_TYPES_HCLASS
#define C_CLASS_CORE_TYPES_HCLASS
#include "cclass.h"
#include <stdint.h>


CLASS(Int8) {
    int8_t _data;

    METHOD_PTR(Int8, int8_t, ToNumber);
    METHOD_PTR(Int8, void, FromNumber, int8_t num);

    METHOD_PTR(Int8, void, Add, Int8* numbers, ...);
    METHOD_PTR(Int8, void, Sub, Int8* numbers, ...);
    METHOD_PTR(Int8, void, Mul, Int8* numbers, ...);
    METHOD_PTR(Int8, void, Div, Int8* numbers, ...);
    METHOD_PTR(Int8, void, Mod, Int8* numbers, ...);

    METHOD_PTR(Int8, void, And, Int8* numbers, ...);
    METHOD_PTR(Int8, void, Or, Int8* numbers, ...);
    METHOD_PTR(Int8, void, Xor, Int8* numbers, ...);
    METHOD_PTR(Int8, void, Not);
    METHOD_PTR(Int8, void, Shl, int8_t bits);
    METHOD_PTR(Int8, void, Shr, int8_t bits);
};


CONSTRUCTOR_OF(Int8);
DESTRUCTOR_OF(Int8);

#endif C_CLASS_CORE_TYPES_HCLASS