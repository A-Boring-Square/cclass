#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

METHOD_IMPL_NO_ARGS(UInt32, uint32_t, ToNumber) { return self->_data; }
METHOD_IMPL(UInt32, void, FromNumber, uint32_t num) { self->_data = num; }

typedef uint32_t (*UInt32Op)(UInt32*, UInt32*);
static uint32_t add_op(UInt32* a, UInt32* b) { return a->_data + b->_data; }
static uint32_t sub_op(UInt32* a, UInt32* b) { return a->_data - b->_data; }
static uint32_t mul_op(UInt32* a, UInt32* b) { return a->_data * b->_data; }
static uint32_t div_op(UInt32* a, UInt32* b) { if(b->_data==0) PANIC_RUNTIME("Division by zero"); return a->_data / b->_data; }
static uint32_t mod_op(UInt32* a, UInt32* b) { if(b->_data==0) PANIC_RUNTIME("Modulo by zero"); return a->_data % b->_data; }
static uint32_t and_op(UInt32* a, UInt32* b) { return a->_data & b->_data; }
static uint32_t or_op(UInt32* a, UInt32* b) { return a->_data | b->_data; }
static uint32_t xor_op(UInt32* a, UInt32* b) { return a->_data ^ b->_data; }

static uint32_t UInt32_vararg_reduce(UInt32* first, va_list args, UInt32Op op) {
if(!first) return 0;
uint32_t acc=first->_data;
UInt32* n=va_arg(args, UInt32*);
while(n){ UInt32 tmp={._data=acc}; acc=op(&tmp,n); n=va_arg(args,UInt32*); }
return acc;
}

#define VAR_METHOD(name, op) \
METHOD_IMPL(UInt32, void, name, UInt32* first, ...) { va_list args; va_start(args,first); self->_data=UInt32_vararg_reduce(first,args,op); va_end(args); }

VAR_METHOD(Add, add_op)
VAR_METHOD(Sub, sub_op)
VAR_METHOD(Mul, mul_op)
VAR_METHOD(Div, div_op)
VAR_METHOD(Mod, mod_op)
VAR_METHOD(And, and_op)
VAR_METHOD(Or, or_op)
VAR_METHOD(Xor, xor_op)

METHOD_IMPL_NO_ARGS(UInt32, void, Not) { self->_data=~self->_data; }
METHOD_IMPL(UInt32, void, Shl, uint32_t bits) { if(bits>31) PANIC_RUNTIME("Shift left out of bounds"); self->_data<<=bits; }
METHOD_IMPL(UInt32, void, Shr, uint32_t bits) { if(bits>31) PANIC_RUNTIME("Shift right out of bounds"); self->_data>>=bits; }

CONSTRUCTOR_OF(UInt32){ UInt32* u32=(UInt32*)malloc(sizeof(UInt32)); if(!u32) PANIC_RUNTIME("Failed to allocate UInt32"); return u32; }
DESTRUCTOR_OF(UInt32){ free(self); }

DEFAULT_COPY_IMPL(UInt32)