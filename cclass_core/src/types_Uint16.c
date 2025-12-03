#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
METHOD_IMPL_NO_ARGS(UInt16, uint16_t, ToNumber) { return self->_data; }
METHOD_IMPL(UInt16, void, FromNumber, uint16_t num) { self->_data = num; }
typedef uint16_t (*UInt16Op)(UInt16*, UInt16*);
static uint16_t add_op(UInt16* a, UInt16* b) { return a->_data + b->_data; }
static uint16_t sub_op(UInt16* a, UInt16* b) { return a->_data - b->_data; }
static uint16_t mul_op(UInt16* a, UInt16* b) { return a->_data * b->_data; }
static uint16_t div_op(UInt16* a, UInt16* b) { if(b->_data==0) PANIC_RUNTIME("Division by zero"); return a->_data/b->_data; }
static uint16_t mod_op(UInt16* a, UInt16* b) { if(b->_data==0) PANIC_RUNTIME("Modulo by zero"); return a->_data%b->_data; }
static uint16_t and_op(UInt16* a, UInt16* b) { return a->_data & b->_data; }
static uint16_t or_op(UInt16* a, UInt16* b) { return a->_data | b->_data; }
static uint16_t xor_op(UInt16* a, UInt16* b) { return a->_data ^ b->_data; }
static uint16_t UInt16_vararg_reduce(UInt16* first, va_list args, UInt16Op op) {
    if(!first) return 0;
    uint16_t acc = first->_data;
    UInt16* n = va_arg(args, UInt16*);
    while(n) { 
        UInt16 tmp={._data=acc};
        acc=op(&tmp,n);
        n=va_arg(args,UInt16*);
    }
    return acc;
}
#define VAR_METHOD(name, op) \
METHOD_IMPL(UInt16, void, name, UInt16* first, ...) { va_list args; va_start(args,first); self->_data=UInt16_vararg_reduce(first,args,op); va_end(args); }
VAR_METHOD(Add, add_op)
VAR_METHOD(Sub, sub_op)
VAR_METHOD(Mul, mul_op)
VAR_METHOD(Div, div_op)
VAR_METHOD(Mod, mod_op)
VAR_METHOD(And, and_op)
VAR_METHOD(Or, or_op)
VAR_METHOD(Xor, xor_op)
METHOD_IMPL_NO_ARGS(UInt16, void, Not) {
    self->_data=~self->_data;
}
METHOD_IMPL(UInt16, void, Shl, uint16_t bits) {
    if(bits>15) PANIC_RUNTIME("Shift left out of bounds");
    self->_data<<=bits;
}
METHOD_IMPL(UInt16, void, Shr, uint16_t bits) {
    if(bits>15) PANIC_RUNTIME("Shift right out of bounds");
    self->_data>>=bits;
}
CONSTRUCTOR_OF(UInt16){
    UInt16* u16=(UInt16*)malloc(sizeof(UInt16));
    if(!u16) PANIC_RUNTIME("Failed to allocate UInt16");
    return u16;
}
DESTRUCTOR_OF(UInt16){ free(self); }
DEFAULT_COPY_IMPL(UInt16)