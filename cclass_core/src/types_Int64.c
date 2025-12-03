#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
METHOD_IMPL_NO_ARGS(Int64, int64_t, ToNumber) {
    return self->_data;
}
METHOD_IMPL(Int64, void, FromNumber, int64_t num) {
    self->_data = num;
}
typedef int64_t (*Int64Op)(Int64*, Int64*);
static int64_t add_op(Int64* a, Int64* b) { return a->_data + b->_data; }
static int64_t sub_op(Int64* a, Int64* b) { return a->_data - b->_data; }
static int64_t mul_op(Int64* a, Int64* b) { return a->_data * b->_data; }
static int64_t div_op(Int64* a, Int64* b) {
    if (b->_data == 0) PANIC_RUNTIME("Division by zero");
    return a->_data / b->_data;
}
static int64_t mod_op(Int64* a, Int64* b) {
    if (b->_data == 0) PANIC_RUNTIME("Modulo by zero");
    return a->_data % b->_data;
}
static int64_t and_op(Int64* a, Int64* b) { return a->_data & b->_data; }
static int64_t or_op(Int64* a, Int64* b)  { return a->_data | b->_data; }
static int64_t xor_op(Int64* a, Int64* b) { return a->_data ^ b->_data; }
static int64_t Int64_vararg_reduce(Int64* first, va_list args, Int64Op op) {
    if (!first) return 0;
    int64_t acc = first->_data;
    Int64* n = va_arg(args, Int64*);
    while (n) {
        Int64 tmp = { ._data = acc };
        acc = op(&tmp, n);
        n = va_arg(args, Int64*);
    }
return acc;
}
#define VAR_METHOD(name, op) \
METHOD_IMPL(Int64, void, name, Int64* first, ...) { \
va_list args; va_start(args, first); \
self->_data = Int64_vararg_reduce(first, args, op); \
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
METHOD_IMPL_NO_ARGS(Int64, void, Not) {
    self->_data = ~self->_data;
}
METHOD_IMPL(Int64, void, Shl, int64_t bits) {
    if (bits < 0 || bits > 63) PANIC_RUNTIME("Shift left out of bounds (0-63)");
    self->_data = (int64_t)((uint64_t)self->_data << bits);
}
METHOD_IMPL(Int64, void, Shr, int64_t bits) {
    if (bits < 0 || bits > 63) PANIC_RUNTIME("Shift right out of bounds (0-63)");
    self->_data = (int64_t)((uint64_t)self->_data >> bits);
}
CONSTRUCTOR_OF(Int64) {
    Int64* i64 = (Int64*)malloc(sizeof(Int64));
    if (!i64) PANIC_RUNTIME("Failed to allocate Int64");
    return i64;
}
DESTRUCTOR_OF(Int64) { free(self);}
DEFAULT_COPY_IMPL(Int64)