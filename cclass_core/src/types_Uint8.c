#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
METHOD_IMPL_NO_ARGS(UInt8, uint8_t, ToNumber) {
    return self->_data;
}
METHOD_IMPL(UInt8, void, FromNumber, uint8_t num) {
    self->_data = num;
}
typedef uint8_t (*UInt8Op)(UInt8*, UInt8*);
static uint8_t add_op(UInt8* a, UInt8* b) { return a->_data + b->_data; }
static uint8_t sub_op(UInt8* a, UInt8* b) { return a->_data - b->_data; }
static uint8_t mul_op(UInt8* a, UInt8* b) { return a->_data * b->_data; }
static uint8_t div_op(UInt8* a, UInt8* b) { if (b->_data == 0) PANIC_RUNTIME("Division by zero"); return a->_data / b->_data; }
static uint8_t mod_op(UInt8* a, UInt8* b) { if (b->_data == 0) PANIC_RUNTIME("Modulo by zero"); return a->_data % b->_data; }
static uint8_t and_op(UInt8* a, UInt8* b) { return a->_data & b->_data; }
static uint8_t or_op(UInt8* a, UInt8* b) { return a->_data | b->_data; }
static uint8_t xor_op(UInt8* a, UInt8* b) { return a->_data ^ b->_data; }
static uint8_t UInt8_vararg_reduce(UInt8* first, va_list args, UInt8Op op) {
    if (!first) return 0;
    uint8_t acc = first->_data;
    UInt8* n = va_arg(args, UInt8*);
    while (n) {
        UInt8 tmp = { ._data = acc };
        acc = op(&tmp, n);
        n = va_arg(args, UInt8*);
    }
    return acc;
}
#define VAR_METHOD(name, op) \
METHOD_IMPL(UInt8, void, name, UInt8* first, ...) { \
va_list args; va_start(args, first); \
self->_data = UInt8_vararg_reduce(first, args, op); \
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
METHOD_IMPL_NO_ARGS(UInt8, void, Not) {
    self->_data = ~self->_data;
}
METHOD_IMPL(UInt8, void, Shl, uint8_t bits) {
    if(bits > 7) PANIC_RUNTIME("Shift left out of bounds");
    self->_data <<= bits;
}
METHOD_IMPL(UInt8, void, Shr, uint8_t bits) {
    if(bits > 7) PANIC_RUNTIME("Shift right out of bounds");
    self->_data >>= bits;
}
CONSTRUCTOR_OF(UInt8) {
    UInt8* u8 = (UInt8*)malloc(sizeof(UInt8));
    if(!u8) PANIC_RUNTIME("Failed to allocate UInt8");
    return u8;
}
DESTRUCTOR_OF(UInt8) { free(self); }
DEFAULT_COPY_IMPL(UInt8)