#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

METHOD_IMPL_NO_ARGS(Int16, int16_t, ToNumber) {
return self->_data;
}

METHOD_IMPL(Int16, void, FromNumber, int16_t num) {
self->_data = num;
}

typedef int32_t (*Int16Op)(Int16*, Int16*);

static int32_t Int16_vararg_reduce(Int16* first, va_list args, Int16Op op) {
if (first == PTR_SENTINEL) return 0;


int32_t acc = first->_data;
Int16* n = va_arg(args, Int16*);
while (n != PTR_SENTINEL) {
    acc = op((Int16*)&acc, n);
    n = va_arg(args, Int16*);
}

if (acc > INT16_MAX) acc = INT16_MAX;
else if (acc < INT16_MIN) acc = INT16_MIN;

return acc;


}

static int32_t add_op(Int16* a, Int16* b) { return a->_data + b->_data; }
static int32_t sub_op(Int16* a, Int16* b) { return a->_data - b->_data; }
static int32_t mul_op(Int16* a, Int16* b) { return a->_data * b->_data; }
static int32_t div_op(Int16* a, Int16* b) {
if (b->_data == 0) PANIC_RUNTIME("Division by zero");
return a->_data / b->_data;
}
static int32_t mod_op(Int16* a, Int16* b) {
if (b->_data == 0) PANIC_RUNTIME("Modulo by zero");
return a->_data % b->_data;
}
static int32_t and_op(Int16* a, Int16* b) { return a->_data & b->_data; }
static int32_t or_op(Int16* a, Int16* b)  { return a->_data | b->_data; }
static int32_t xor_op(Int16* a, Int16* b) { return a->_data ^ b->_data; }

#define VAR_METHOD(name, op) \
METHOD_IMPL(Int16, void, name, Int16* first, ...) { \
va_list args; va_start(args, first); \
self->_data = (int16_t)Int16_vararg_reduce(first, args, op); \
va_end(args); \
} \

VAR_METHOD(Add, add_op)
VAR_METHOD(Sub, sub_op)
VAR_METHOD(Mul, mul_op)
VAR_METHOD(Div, div_op)
VAR_METHOD(Mod, mod_op)
VAR_METHOD(And, and_op)
VAR_METHOD(Or, or_op)
VAR_METHOD(Xor, xor_op)

METHOD_IMPL_NO_ARGS(Int16, void, Not) {
self->_data = ~self->_data;
}

METHOD_IMPL(Int16, void, Shl, int16_t bits) {
if (bits < 0 || bits > 15) PANIC_RUNTIME("Shift left out of bounds (0-15)");
self->_data = (int16_t)((uint16_t)self->_data << bits);
}

METHOD_IMPL(Int16, void, Shr, int16_t bits) {
if (bits < 0 || bits > 15) PANIC_RUNTIME("Shift right out of bounds (0-15)");
self->_data = (int16_t)((uint16_t)self->_data >> bits);
}

CONSTRUCTOR_OF(Int16) {
Int16* i16 = (Int16*)malloc(sizeof(Int16));
if (!i16) PANIC_RUNTIME("Failed to allocate Int16");
return i16;
}

DESTRUCTOR_OF(Int16) {
free(self);
}

DEFAULT_COPY_IMPL(Int16)