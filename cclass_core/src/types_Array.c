#include "cclass.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
METHOD_IMPL(Array, void, Push, void* element, size_t element_size) {
    if (element_size > self->_element_size) {
        PANIC_RUNTIME("Could not Push value to Array: element size too large");
    }
    if (self->_length >= self->_capacity) {
        PANIC_RUNTIME("Could not Push value to Array: capacity exceeded");
    }

    memcpy((char*)self->_data + self->_length * self->_element_size, element, element_size);
    self->_length += 1;
}
METHOD_IMPL(Array, void*, At, size_t index) {
    if (index >= self->_length) {
        PANIC_RUNTIME("Index out of bounds");
    }
    return (void*)((uint8_t*)self->_data + index * self->_element_size);
}
METHOD_IMPL_NO_ARGS(Array, size_t, Len) {
    return self->_length;
}
METHOD_IMPL(Array, void, Swizzle, const size_t* indices, size_t count) {
    if (count != self->_length) {
        PANIC_RUNTIME("Swizzle count must match array length");
    }
    void** temp = (void**)malloc(self->_length * sizeof(void*));
    if (!temp) PANIC_RUNTIME("Failed to allocate temporary buffer for Swizzle");
    SIMD_HINT
    for (size_t i = 0; i < self->_length; i++) {
        if (indices[i] >= self->_length) {
            free(temp);
            PANIC_RUNTIME("Swizzle index out of bounds");
        }
        temp[i] = ((void**)self->_data)[indices[i]];
    }
    memcpy(self->_data, temp, self->_length * sizeof(void*));
    free(temp);
}
METHOD_IMPL(Array, bool, Compare, Array* other) {
    if (!other) return false;
    if (self->_length != other->_length) return false;
    void** a = (void**)self->_data;
    void** b = (void**)other->_data;
    SIMD_HINT
    for (size_t i = 0; i < self->_length; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}
CONSTRUCTOR_OF(Array, size_t element_size, size_t capacity) {
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->_element_size = element_size;
    arr->_capacity = capacity;
    arr->_length = 0;
    arr->_data = calloc(capacity, element_size);
    REGISTER_METHOD(arr, Array, Push);
    REGISTER_METHOD(arr, Array, At);
    REGISTER_METHOD(arr, Array, Len);
    return arr;
}
DESTRUCTOR_OF(Array) {
    self->_capacity = 0;
    self->_element_size = 0;
    free(self->_data);
    self->_data = NULL;
    free(self);
}
COPY_OF(Array) {
    if (!obj) return NULL;
    Array* copy = NEW(Array, obj->_element_size, obj->_capacity);
    if (!copy) return NULL;
    copy->_length = obj->_length;
    if (obj->_data && obj->_length > 0) {
        memcpy(copy->_data, obj->_data, obj->_element_size * obj->_length);
    }
    return copy;
}