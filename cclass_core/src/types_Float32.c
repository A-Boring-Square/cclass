#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

METHOD_IMPL_NO_ARGS(Float32, float, ToNumber) {
    return self->_data;
}

METHOD_IMPL(Float32, void, FromNumber, float num) {
    self->_data = num;
}

typedef float (*Float32Op)(Float32*, Float32*);
static float add_op(Float32* a, Float32* b) { return a->_data + b->_data; }
static float sub_op(Float32* a, Float32* b) { return a->_data - b->_data; }
static float mul_op(Float32* a, Float32* b) { return a->_data * b->_data; }
static float div_op(Float32* a, Float32* b) { if(b->_data==0) PANIC_RUNTIME("Division by zero"); return a->_data / b->_data; }

static float Float32_vararg_reduce(Float32* first, va_list args, Float32Op op) {
    if(!first) return 0.0f;
    float acc = first->_data;
    Float32* n = va_arg(args, Float32*);
    while(n) {
        Float32 tmp = { ._data = acc };
        acc = op(&tmp, n);
        n = va_arg(args, Float32*);
    }
    return acc;
}

#define VAR_METHOD(name, op) \
METHOD_IMPL(Float32, void, name, Float32* first, ...) { \
va_list args; va_start(args, first); \
self->_data = Float32_vararg_reduce(first, args, op); \
va_end(args); \
}

VAR_METHOD(Add, add_op)
VAR_METHOD(Sub, sub_op)
VAR_METHOD(Mul, mul_op)
VAR_METHOD(Div, div_op)

CONSTRUCTOR_OF(Float32) {
    Float32* f32 = (Float32*)malloc(sizeof(Float32));
    if(!f32) PANIC_RUNTIME("Failed to allocate Float32");
    return f32;
}

DESTRUCTOR_OF(Float32) { free(self); }

DEFAULT_COPY_IMPL(Float32)