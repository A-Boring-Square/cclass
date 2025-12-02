#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

METHOD_IMPL_NO_ARGS(Int32, int32_t, ToNumber) { return self->_data; }
METHOD_IMPL(Int32, void, FromNumber, int32_t num) { self->_data = num; }

typedef int64_t (*Int32Op)(Int32*, Int32*);

static int64_t Int32_vararg_reduce(Int32* first, va_list args, Int32Op op) {
if (first == PTR_SENTINEL) return 0;
int64_t acc = first->_data;
Int32* n = va_arg(args, Int32*);
while (n != PTR_SENTINEL) { acc = op((Int32*)&acc, n); n = va_arg(args, Int32*); }
if (acc > INT32_MAX) acc = INT32_MAX;
else if (acc < INT32_MIN) acc = INT32_MIN;
return acc;
}

static int64_t add_op(Int32* a, Int32* b) { return a->_data + b->_data; }
static int64_t sub_op(Int32* a, Int32* b) { return a->_data - b->_data; }
static int64_t mul_op(Int32* a, Int32* b) { return a->_data * b->_data; }
static int64_t div_op(Int32* a, Int32* b) { if(b->_data==0)PANIC_RUNTIME("Division by zero"); return a->_data/b->_data; }
static int64_t mod_op(Int32* a, Int32* b) { if(b->_data==0)PANIC_RUNTIME("Modulo by zero"); return a->_data%b->_data; }
static int64_t and_op(Int32* a, Int32* b) { return a->_data & b->_data; }
static int64_t or_op(Int32* a, Int32* b)  { return a->_data | b->_data; }
static int64_t xor_op(Int32* a, Int32* b) { return a->_data ^ b->_data; }

#define VAR_METHOD(name, op) \
METHOD_IMPL(Int32, void, name, Int32* first, ...) { va_list args; va_start(args, first); self->_data = (int32_t)Int32_vararg_reduce(first, args, op); va_end(args); } \

VAR_METHOD(Add, add_op)
VAR_METHOD(Sub, sub_op)
VAR_METHOD(Mul, mul_op)
VAR_METHOD(Div, div_op)
VAR_METHOD(Mod, mod_op)
VAR_METHOD(And, and_op)
VAR_METHOD(Or, or_op)
VAR_METHOD(Xor, xor_op)

METHOD_IMPL_NO_ARGS(Int32, void, Not) { self->_data = ~self->_data; }
METHOD_IMPL(Int32, void, Shl, int32_t bits) { if(bits<0||bits>31)PANIC_RUNTIME("Shift left out of bounds (0-31)"); self->_data = (int32_t)((uint32_t)self->_data<<bits); }
METHOD_IMPL(Int32, void, Shr, int32_t bits) { if(bits<0||bits>31)PANIC_RUNTIME("Shift right out of bounds (0-31)"); self->_data = (int32_t)((uint32_t)self->_data>>bits); }

CONSTRUCTOR_OF(Int32) { Int32* i32 = (Int32*)malloc(sizeof(Int32)); if(!i32)PANIC_RUNTIME("Failed to allocate Int32"); return i32; }
DESTRUCTOR_OF(Int32) { free(self); }

DEFAULT_COPY_IMPL(Int32)