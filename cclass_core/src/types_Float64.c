#include "cclass.h"
#include "types.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

METHOD_IMPL_NO_ARGS(Float64, double, ToNumber) { return self->_data; }
METHOD_IMPL(Float64, void, FromNumber, double num) { self->_data = num; }

typedef double (*Float64Op)(Float64*, Float64*);
static double add_op(Float64* a, Float64* b) { return a->_data + b->_data; }
static double sub_op(Float64* a, Float64* b) { return a->_data - b->_data; }
static double mul_op(Float64* a, Float64* b) { return a->_data * b->_data; }
static double div_op(Float64* a, Float64* b) { if(b->_data==0) PANIC_RUNTIME("Division by zero"); return a->_data / b->_data; }

static double Float64_vararg_reduce(Float64* first, va_list args, Float64Op op) {
if(!first) return 0.0;
double acc = first->_data;
Float64* n = va_arg(args, Float64*);
while(n) {
Float64 tmp = { ._data = acc };
acc = op(&tmp, n);
n = va_arg(args, Float64*);
}
return acc;
}

#define VAR_METHOD(name, op) \
METHOD_IMPL(Float64, void, name, Float64* first, ...) { \
va_list args; va_start(args, first); \
self->_data = Float64_vararg_reduce(first, args, op); \
va_end(args); \
}

VAR_METHOD(Add, add_op)
VAR_METHOD(Sub, sub_op)
VAR_METHOD(Mul, mul_op)
VAR_METHOD(Div, div_op)

CONSTRUCTOR_OF(Float64) {
Float64* f64 = (Float64*)malloc(sizeof(Float64));
if(!f64) PANIC_RUNTIME("Failed to allocate Float64");
return f64;
}

DESTRUCTOR_OF(Float64) { free(self); }

DEFAULT_COPY_IMPL(Float64)