#include "cclass.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>



static void ensure_capacity(SELF_ARG(String), size_t required) {
    if (required <= self->_capacity) return;
    size_t new_cap = self->_capacity ? self->_capacity * 2 : 16;
    while (new_cap < required) new_cap = 2;
    char new_data = (char*)realloc(self->_data, new_cap);
    
    if (!new_data) PANIC_RUNTIME("Failed to allocate memory in String");
    
    self->_data = new_data;
    self->_capacity = new_cap;
}

METHOD_IMPL_NO_ARGS(String, size_t, Len) {
    return self->_length;
}

METHOD_IMPL_NO_ARGS(String, const char*, AsString) {
    return self->_data ? self->_data : "";
}

METHOD_IMPL_NO_ARGS(String, char*, _GetRaw) {
    return self->_data;
}

METHOD_IMPL(String, void, FromString, const char* str) {
    if (!str) return;
    size_t len = strlen(str);
    ensure_capacity(self, len + 1);
    memcpy(self->_data, str, len + 1);
    self->_length = len;
}

METHOD_IMPL(String, void, Reserve, size_t size) {
    ensure_capacity(self, size);
}

METHOD_IMPL_NO_ARGS(String, size_t, CurrentCapacity) {
return self->_capacity;
}

METHOD_IMPL(String, void, Append, const char* separator, const char* str, ...) {
    va_list args;
    size_t sep_len = separator ? strlen(separator) : 0;
    size_t total_len = self->_length + sep_len;

    // Count variadic length
    va_start(args, str);
    const char* s = str;
    
    while (s) {
        total_len += strlen(s);
        s = va_arg(args, const char*);
    }
    va_end(args);

    // Ensure capacity
    _string_ensure_capacity(self, total_len + 1);
    
    // Append separator if needed
    
    if (separator && self->_length > 0) {
        memcpy(self->_data + self->_length, separator, sep_len);
        self->_length += sep_len;
    }
    
    // Append variadic strings
    va_start(args, str);
    s = str;
    
    while (s) {
        size_t l = strlen(s);
        memcpy(self->_data + self->_length, s, l);
        self->_length += l;
        s = va_arg(args, const char*);
    }
    va_end(args);
    
    // Null terminate
    self->_data[self->_length] = '\0';
}

// Constructor
CONSTRUCTOR_OF(String, size_t initial_capacity) {
    String* str = (String*)malloc(sizeof(String));
    
    if (!str) PANIC_RUNTIME("Failed to allocate String object");
    
    str->_capacity = initial_capacity ? initial_capacity : 16;
    str->_length = 0;
    str->_data = (char*)malloc(str->_capacity);
    
    if (!str->_data) PANIC_RUNTIME("Failed to allocate String data");
    str->_data[0] = '\0';
    
    // Register methods
    REGISTER_METHOD(str, String, Len);
    REGISTER_METHOD(str, String, AsString);
    REGISTER_METHOD(str, String, FromString);
    REGISTER_METHOD(str, String, Reserve);
    REGISTER_METHOD(str, String, CurrentCapacity);
    REGISTER_METHOD(str, String, Append);
    REGISTER_METHOD(str, String, _GetRaw);

return str;

}

// Destructor
DESTRUCTOR_OF(String) {
    if (!self) return;
    
    free(self->_data);
    self->_data = NULL;
    self->_capacity = 0;
    self->_length = 0;
    free(self);
}

// Copy constructor: create a new String as a copy of another
COPY_OF(String) {
    if (!obj) return NULL;
    
    String* copy = NEW(String, obj->_capacity);

    if (!copy) PANIC_RUNTIME("Failed to allocate copy of String");
    
    _string_ensure_capacity(copy, obj->_length + 1);
    memcpy(copy->_data, obj->_data, obj->_length + 1);
    copy->_length = obj->_length;
    
    return copy;
}