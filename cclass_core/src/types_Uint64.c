#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

METHOD_IMPL_NO_ARGS(UInt64, uint64_t, ToNumber) {
return self->_data;
}

METHOD_IMPL(UInt64, void, FromNumber, uint64_t num) {
self->_data = num;
}

typedef uint64_t (*UInt64Op)(UInt64*, UInt64*);

static uint64_t add_op(UInt64* a, UInt64* b) { return a->_data + b->_data; }
static uint64_t sub_op(UInt64* a, UInt64* b) { return a->_data - b->_data; }
static uint64_t mul_op(UInt64* a, UInt64* b) { return a->_data * b->_data; }
static uint64_t div_op(UInt64* a, UInt64* b) {
if (b->_data == 0) PANIC_RUNTIME("Division by zero");
return a->_data / b->_data;
}
static uint64_t mod_op(UInt64* a, UInt64* b) {
if (b->_data == 0) PANIC_RUNTIME("Modulo by zero");
return a->_data % b->_data;
}
static uint64_t and_op(UInt64* a, UInt64* b) { return a->_data & b->_data; }
static uint64_t or_op(UInt64* a, UInt64* b)  { return a->_data | b->_data; }
static uint64_t xor_op(UInt64* a, UInt64* b) { return a->_data ^ b->_data; }

static uint64_t UInt64_vararg_reduce(UInt64* first, va_list args, UInt64Op op) {
if (!first) return 0;


uint64_t acc = first->_data;
UInt64* n = va_arg(args, UInt64*);
while (n) {
    UInt64 tmp = { ._data = acc };
    acc = op(&tmp, n);
    n = va_arg(args, UInt64*);
}

return acc;

}

#define VAR_METHOD(name, op) \
METHOD_IMPL(UInt64, void, name, UInt64* first, ...) { \
va_list args; va_start(args, first); \
self->_data = UInt64_vararg_reduce(first, args, op); \
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

METHOD_IMPL_NO_ARGS(UInt64, void, Not) {
self->_data = ~self->_data;
}

METHOD_IMPL(UInt64, void, Shl, uint64_t bits) {
if (bits > 63) PANIC_RUNTIME("Shift left out of bounds (0-63)");
self->_data <<= bits;
}

METHOD_IMPL(UInt64, void, Shr, uint64_t bits) {
if (bits > 63) PANIC_RUNTIME("Shift right out of bounds (0-63)");
self->_data >>= bits;
}

CONSTRUCTOR_OF(UInt64) {
UInt64* u64 = (UInt64*)malloc(sizeof(UInt64));
if (!u64) PANIC_RUNTIME("Failed to allocate UInt64");
return u64;
}

DESTRUCTOR_OF(UInt64) {
free(self);
}

DEFAULT_COPY_IMPL(UInt64)