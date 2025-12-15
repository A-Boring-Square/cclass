#ifndef C_CLASS_H
#define C_CLASS_H

#define C_CLASS_VERSION_MAJOR 1
#define C_CLASS_VERSION_MINOR 1
#define C_CLASS_VERSION_PATCH 0

#define C_CLASS_VERSION_NUM \
    (C_CLASS_VERSION_MAJOR * 10000 + \
     C_CLASS_VERSION_MINOR * 100 +  \
     C_CLASS_VERSION_PATCH)

#ifndef C_CLASS_USE_SIMD
#define C_CLASS_USE_SIMD 1
#endif

#define PTR_SENTINEL NULL
#define INT_SENTINEL 0

// Internal do not use
#define C_CLASS_VARG_MAX_ARGS 64

#define MAX_ARGS C_CLASS_VARG_MAX_ARGS

#define ANY_CLASS void*

// Helper to stringify a macro argument
#define STR(x) STR_IMPL(x)
#define STR_IMPL(x) #x

// Compile-time panic
#define PANIC_COMPTIME(msg) _Static_assert(0, "COMPILE-TIME PANIC at " __FILE__ ":" STR(__LINE__) " - " msg)

// Runtime panic
// NOTE(A-Boring-Square): This requires `stdio.h` or a compatable `fprintf` impl
#define PANIC_RUNTIME(msg) do { \
    fprintf(stderr, "RUNTIME PANIC %s:%d - %s\n", __FILE__, __LINE__, msg); \
    abort(); \
} while (0)

#if C_CLASS_USE_SIMD
    #if defined(_MSC_VER)
        #define SIMD_HINT __pragma(loop(ivdep))
    #elif defined(__clang__) || defined(__GNUC__)
        #define SIMD_HINT _Pragma("omp simd")
    #else
        #define SIMD_HINT
    #endif
#else
    #define SIMD_HINT
#endif

#define THREAD_LOCAL _Thread_local

#define SELF(obj) (obj)
#define SELF_ARG(cls) cls* self

#define CLASS(name) \
    typedef struct name name; \
    struct name

#define METHOD_PTR(cls, ret, name, ...) \
    ret (*name)(SELF_ARG(cls) , ##__VA_ARGS__)

#define METHOD_IMPL(cls, ret, name, ...) \
    ret cls##_##name(SELF_ARG(cls) , ##__VA_ARGS__)


#define CONSTRUCTOR_OF(cls, ...) \
    cls* cls##_new(__VA_ARGS__)

#define DESTRUCTOR_OF(cls) \
    void cls##_delete(cls* self)

#define NEW(cls, ...) cls##_new(__VA_ARGS__)
#define DELETE(cls, obj) cls##_delete(obj)

#define REGISTER_METHOD(obj, cls, method) \
    (obj)->method = cls##_##method

#define METHOD_CALL(obj, method, ...) \
    ((obj)->method((obj), ##__VA_ARGS__))

#define COPY_OF(cls) cls* cls##_copy(const cls* self)
#define COPY(cls, obj) cls##_copy(obj)

#endif /* C_CLASS_H */
