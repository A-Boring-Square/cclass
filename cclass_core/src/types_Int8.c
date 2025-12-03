#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
METHOD_IMPL_NO_ARGS(Int8, int8_t, ToNumber) {
    return self->_data;
}
METHOD_IMPL(Int8, void, FromNumber, int8_t num) {
    self->_data = num;
}
typedef int32_t (*Int8Op)(Int8*, Int8*);
static int32_t Int8_vararg_reduce(Int8* first, va_list args, Int8Op op) {
    if (first == PTR_SENTINEL) return 0;
    int32_t acc = first->_data;
    Int8* n = va_arg(args, Int8*);
    while (n != PTR_SENTINEL) {
        acc = op((Int8*)&acc, n);
        n = va_arg(args, Int8*);
    }
    if (acc > INT8_MAX) acc = INT8_MAX;
    else if (acc < INT8_MIN) acc = INT8_MIN;
    return acc;
}
static int32_t add_op(Int8* a, Int8* b) { return a->_data + b->_data; }
static int32_t sub_op(Int8* a, Int8* b) { return a->_data - b->_data; }
static int32_t mul_op(Int8* a, Int8* b) { return a->_data * b->_data; }
static int32_t div_op(Int8* a, Int8* b) {
    if (b->_data == 0) PANIC_RUNTIME("Division by zero");
    return a->_data / b->_data;
}
static int32_t mod_op(Int8* a, Int8* b) {
    if (b->_data == 0) PANIC_RUNTIME("Modulo by zero");
    return a->_data % b->_data;
}
static int32_t and_op(Int8* a, Int8* b) { return a->_data & b->_data; }
static int32_t or_op(Int8* a, Int8* b)  { return a->_data | b->_data; }
static int32_t xor_op(Int8* a, Int8* b) { return a->_data ^ b->_data; }
#define VAR_METHOD(name, op) \
METHOD_IMPL(Int8, void, name, Int8* first, ...) { \
    va_list args; va_start(args, first); \
    self->_data = (int8_t)Int8_vararg_reduce(first, args, op); \
    va_end(args); \
}
VAR_METHOD(Add, add_op)
VAR_METHOD(Sub, sub_op)
VAR_METHOD(Mul, mul_op)
VAR_METHOD(Div, div_op)
VAR_METHOD(Mod, mod_op)
VAR_METHOD(And, and_op)
VAR_METHOD(Or, or_op)
VAR_METHOD(Xor, xor_op)
METHOD_IMPL_NO_ARGS(Int8, void, Not) {
    self->_data = ~self->_data;
}
METHOD_IMPL(Int8, void, Shl, int8_t bits) {
    if (bits < 0 || bits > 7) PANIC_RUNTIME("Shift left out of bounds (0-7)");
    self->_data = (int8_t)((uint8_t)self->_data << bits);
}
METHOD_IMPL(Int8, void, Shr, int8_t bits) {
    if (bits < 0 || bits > 7) PANIC_RUNTIME("Shift right out of bounds (0-7)");
    self->_data = (int8_t)((uint8_t)self->_data >> bits);
}
CONSTRUCTOR_OF(Int8) {
    Int8* i8 = (Int8*)malloc(sizeof(Int8));
    if (i8 == NULL) {
        PANIC_RUNTIME("Failed to allocate Int8");
    }
    return i8;
}
DESTRUCTOR_OF(Int8) {
    free(self);
    
}
DEFAULT_COPY_IMPL(Int8)