#ifndef C_CLASS_CORE_TYPES_HCLASS
#define C_CLASS_CORE_TYPES_HCLASS
#include "cclass.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// -------------------
// Int8
// -------------------
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
DEFAULT_COPY_DEF(Int8);

// -------------------
// Int16
// -------------------
CLASS(Int16) {
int16_t _data;

METHOD_PTR(Int16, int16_t, ToNumber);
METHOD_PTR(Int16, void, FromNumber, int16_t num);

METHOD_PTR(Int16, void, Add, Int16* numbers, ...);
METHOD_PTR(Int16, void, Sub, Int16* numbers, ...);
METHOD_PTR(Int16, void, Mul, Int16* numbers, ...);
METHOD_PTR(Int16, void, Div, Int16* numbers, ...);
METHOD_PTR(Int16, void, Mod, Int16* numbers, ...);

METHOD_PTR(Int16, void, And, Int16* numbers, ...);
METHOD_PTR(Int16, void, Or, Int16* numbers, ...);
METHOD_PTR(Int16, void, Xor, Int16* numbers, ...);
METHOD_PTR(Int16, void, Not);
METHOD_PTR(Int16, void, Shl, int16_t bits);
METHOD_PTR(Int16, void, Shr, int16_t bits);

};
CONSTRUCTOR_OF(Int16);
DESTRUCTOR_OF(Int16);
DEFAULT_COPY_DEF(Int16);

// -------------------
// Int32
// -------------------
CLASS(Int32) {
int32_t _data;

METHOD_PTR(Int32, int32_t, ToNumber);
METHOD_PTR(Int32, void, FromNumber, int32_t num);

METHOD_PTR(Int32, void, Add, Int32* numbers, ...);
METHOD_PTR(Int32, void, Sub, Int32* numbers, ...);
METHOD_PTR(Int32, void, Mul, Int32* numbers, ...);
METHOD_PTR(Int32, void, Div, Int32* numbers, ...);
METHOD_PTR(Int32, void, Mod, Int32* numbers, ...);

METHOD_PTR(Int32, void, And, Int32* numbers, ...);
METHOD_PTR(Int32, void, Or, Int32* numbers, ...);
METHOD_PTR(Int32, void, Xor, Int32* numbers, ...);
METHOD_PTR(Int32, void, Not);
METHOD_PTR(Int32, void, Shl, int32_t bits);
METHOD_PTR(Int32, void, Shr, int32_t bits);

};
CONSTRUCTOR_OF(Int32);
DESTRUCTOR_OF(Int32);
DEFAULT_COPY_DEF(Int32);

// -------------------
// Int64
// -------------------
CLASS(Int64) {
int64_t _data;

METHOD_PTR(Int64, int64_t, ToNumber);
METHOD_PTR(Int64, void, FromNumber, int64_t num);

METHOD_PTR(Int64, void, Add, Int64* numbers, ...);
METHOD_PTR(Int64, void, Sub, Int64* numbers, ...);
METHOD_PTR(Int64, void, Mul, Int64* numbers, ...);
METHOD_PTR(Int64, void, Div, Int64* numbers, ...);
METHOD_PTR(Int64, void, Mod, Int64* numbers, ...);

METHOD_PTR(Int64, void, And, Int64* numbers, ...);
METHOD_PTR(Int64, void, Or, Int64* numbers, ...);
METHOD_PTR(Int64, void, Xor, Int64* numbers, ...);
METHOD_PTR(Int64, void, Not);
METHOD_PTR(Int64, void, Shl, int64_t bits);
METHOD_PTR(Int64, void, Shr, int64_t bits);

};
CONSTRUCTOR_OF(Int64);
DESTRUCTOR_OF(Int64);
DEFAULT_COPY_DEF(Int64);

// -------------------
// UInt8
// -------------------
CLASS(UInt8) {
uint8_t _data;

METHOD_PTR(UInt8, uint8_t, ToNumber);
METHOD_PTR(UInt8, void, FromNumber, uint8_t num);

METHOD_PTR(UInt8, void, Add, UInt8* numbers, ...);
METHOD_PTR(UInt8, void, Sub, UInt8* numbers, ...);
METHOD_PTR(UInt8, void, Mul, UInt8* numbers, ...);
METHOD_PTR(UInt8, void, Div, UInt8* numbers, ...);
METHOD_PTR(UInt8, void, Mod, UInt8* numbers, ...);

METHOD_PTR(UInt8, void, And, UInt8* numbers, ...);
METHOD_PTR(UInt8, void, Or, UInt8* numbers, ...);
METHOD_PTR(UInt8, void, Xor, UInt8* numbers, ...);
METHOD_PTR(UInt8, void, Not);
METHOD_PTR(UInt8, void, Shl, uint8_t bits);
METHOD_PTR(UInt8, void, Shr, uint8_t bits);

};
CONSTRUCTOR_OF(UInt8);
DESTRUCTOR_OF(UInt8);
DEFAULT_COPY_DEF(UInt8);

// -------------------
// UInt16
// -------------------
CLASS(UInt16) {
uint16_t _data;

METHOD_PTR(UInt16, uint16_t, ToNumber);
METHOD_PTR(UInt16, void, FromNumber, uint16_t num);

METHOD_PTR(UInt16, void, Add, UInt16* numbers, ...);
METHOD_PTR(UInt16, void, Sub, UInt16* numbers, ...);
METHOD_PTR(UInt16, void, Mul, UInt16* numbers, ...);
METHOD_PTR(UInt16, void, Div, UInt16* numbers, ...);
METHOD_PTR(UInt16, void, Mod, UInt16* numbers, ...);

METHOD_PTR(UInt16, void, And, UInt16* numbers, ...);
METHOD_PTR(UInt16, void, Or, UInt16* numbers, ...);
METHOD_PTR(UInt16, void, Xor, UInt16* numbers, ...);
METHOD_PTR(UInt16, void, Not);
METHOD_PTR(UInt16, void, Shl, uint16_t bits);
METHOD_PTR(UInt16, void, Shr, uint16_t bits);

};
CONSTRUCTOR_OF(UInt16);
DESTRUCTOR_OF(UInt16);
DEFAULT_COPY_DEF(UInt16);

// -------------------
// UInt32
// -------------------
CLASS(UInt32) {
uint32_t _data;

METHOD_PTR(UInt32, uint32_t, ToNumber);
METHOD_PTR(UInt32, void, FromNumber, uint32_t num);

METHOD_PTR(UInt32, void, Add, UInt32* numbers, ...);
METHOD_PTR(UInt32, void, Sub, UInt32* numbers, ...);
METHOD_PTR(UInt32, void, Mul, UInt32* numbers, ...);
METHOD_PTR(UInt32, void, Div, UInt32* numbers, ...);
METHOD_PTR(UInt32, void, Mod, UInt32* numbers, ...);

METHOD_PTR(UInt32, void, And, UInt32* numbers, ...);
METHOD_PTR(UInt32, void, Or, UInt32* numbers, ...);
METHOD_PTR(UInt32, void, Xor, UInt32* numbers, ...);
METHOD_PTR(UInt32, void, Not);
METHOD_PTR(UInt32, void, Shl, uint32_t bits);
METHOD_PTR(UInt32, void, Shr, uint32_t bits);

};
CONSTRUCTOR_OF(UInt32);
DESTRUCTOR_OF(UInt32);
DEFAULT_COPY_DEF(UInt32);

// -------------------
// UInt64
// -------------------
CLASS(UInt64) {
uint64_t _data;

METHOD_PTR(UInt64, uint64_t, ToNumber);
METHOD_PTR(UInt64, void, FromNumber, uint64_t num);

METHOD_PTR(UInt64, void, Add, UInt64* numbers, ...);
METHOD_PTR(UInt64, void, Sub, UInt64* numbers, ...);
METHOD_PTR(UInt64, void, Mul, UInt64* numbers, ...);
METHOD_PTR(UInt64, void, Div, UInt64* numbers, ...);
METHOD_PTR(UInt64, void, Mod, UInt64* numbers, ...);

METHOD_PTR(UInt64, void, And, UInt64* numbers, ...);
METHOD_PTR(UInt64, void, Or, UInt64* numbers, ...);
METHOD_PTR(UInt64, void, Xor, UInt64* numbers, ...);
METHOD_PTR(UInt64, void, Not);
METHOD_PTR(UInt64, void, Shl, uint64_t bits);
METHOD_PTR(UInt64, void, Shr, uint64_t bits);

};
CONSTRUCTOR_OF(UInt64);
DESTRUCTOR_OF(UInt64);
DEFAULT_COPY_DEF(UInt64);

// -------------------
// Float32
// -------------------
CLASS(Float32) {
float _data;

METHOD_PTR(Float32, float, ToNumber);
METHOD_PTR(Float32, void, FromNumber, float num);

METHOD_PTR(Float32, void, Add, Float32* numbers, ...);
METHOD_PTR(Float32, void, Sub, Float32* numbers, ...);
METHOD_PTR(Float32, void, Mul, Float32* numbers, ...);
METHOD_PTR(Float32, void, Div, Float32* numbers, ...);

};
CONSTRUCTOR_OF(Float32);
DESTRUCTOR_OF(Float32);
DEFAULT_COPY_DEF(Float32);

// -------------------
// Float64
// -------------------
CLASS(Float64) {
double _data;

METHOD_PTR(Float64, double, ToNumber);
METHOD_PTR(Float64, void, FromNumber, double num);

METHOD_PTR(Float64, void, Add, Float64* numbers, ...);
METHOD_PTR(Float64, void, Sub, Float64* numbers, ...);
METHOD_PTR(Float64, void, Mul, Float64* numbers, ...);
METHOD_PTR(Float64, void, Div, Float64* numbers, ...);

};
CONSTRUCTOR_OF(Float64);
DESTRUCTOR_OF(Float64);
DEFAULT_COPY_DEF(Float64);


// Dynamically resizing string class
CLASS(String) {
    // Data buffer
    char* _data;

    // Allocated bytes
    size_t _capacity;

    // Number of bytes used
    size_t _length;

    METHOD_PTR(String, size_t, Len);
    METHOD_PTR(String, const char*, AsString);
    METHOD_PTR(String, void, FromString, const char* str);
    METHOD_PTR(String, void, Reserve, size_t size);
    METHOD_PTR(String, size_t, CurrentCapacity);
    METHOD_PTR(String, void, Append, const char* seperator, const char* str, ...);
    METHOD_PTR(String, char*, _GetRaw); // NOTE: **INTERNAL RUNTIME USE ONLY**
};

CONSTRUCTOR_OF(String);
DESTRUCTOR_OF(String);
COPY_OF(String);

CLASS(Array) {
    size_t _length;
    size_t _capacity;
    void* _data;
    size_t _element_size;

    // Methods
    METHOD_PTR(Array, void, Push, void* elem, size_t element_size);
    METHOD_PTR(Array, void*, At, size_t index);
    METHOD_PTR(Array, size_t, Len);
    METHOD_PTR(Array, void, Swizzle, const size_t* indices, size_t count);
    METHOD_PTR(Array, bool, Compare, Array* array);
};

CONSTRUCTOR_OF(Array);
DESTRUCTOR_OF(Array);
COPY_OF(Array);


#endif // C_CLASS_CORE_TYPES_HCLASS