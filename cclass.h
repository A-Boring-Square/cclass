#ifndef C_CLASS_H
#define C_CLASS_H


#define C_CLASS_VERSION_MAJOR 1
#define C_CLASS_VERSION_MINOR 0
#define C_CLASS_VERSION_PATCH 0


#define C_CLASS_VERSION_STRING_IMPL(major, minor, patch) #major "." #minor "." #patch

#define C_CLASS_VERSION_STRING \
    C_CLASS_VERSION_STRING_IMPL(C_CLASS_VERSION_MAJOR, C_CLASS_VERSION_MINOR, C_CLASS_VERSION_PATCH)


#define C_CLASS_VERSION_NUM (C_CLASS_VERSION_MAJOR * 100) + (C_CLASS_VERSION_MINOR * 10) + C_CLASS_VERSION_PATCH

#undef C_CLASS_VERSION_STRING_IMPL

// NOTE(A-Boring-Square): does not guarantee that cclass will use SIMD it only enables it as an option
#ifndef C_CLASS_USE_SIMD
#define C_CLASS_USE_SIMD 1
#endif // C_CLASS_USE_SIMD

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
    fprintf(stderr, "RUNTIME PANIC at %s:%d - %s\n", __FILE__, __LINE__, msg); \
    abort(); \
} while(0)

#undef STR
#undef STR_IMPL

#if C_CLASS_USE_SIMD == 1
#if defined(_MSC_VER)
    // SIMD_HINT macro for cross-compiler vectorization hints
    #define SIMD_HINT __pragma(loop(ivdep))
#elif defined(__clang__) || defined(__GNUC__)
    // SIMD_HINT macro for cross-compiler vectorization hints
    #define SIMD_HINT _Pragma("omp simd")
#else
    // SIMD_HINT macro for cross-compiler vectorization hints
    #define SIMD_HINT
#endif
#define THREAD_LOCAL _Thread_local
#define BY_PTR restrict
#define BY_REGISTER register
#endif

#ifdef _C_CLASS_MACRO_COMMENT
/* ==========================================================
   MACRO-BASED CLASS SYSTEM FOR PURE C
   ----------------------------------------------------------
   Features:
   - Lightweight, vtable-free "classes"
   - Supports constructors, destructors
   - Function pointers stored in struct as methods
   - Safe for methods with and without arguments
   ========================================================== */
#endif // _C_CLASS_MACRO_COMMENT
#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- SELF MACROS ---------------------- */
/*
   SELF(obj)
   - Used when calling a method to pass the object pointer.
   - Expands to just the object itself.
   Example:
       METHOD_CALL(b, say_hi)(SELF(b));
*/
#endif // _C_CLASS_MACRO_COMMENT

#define SELF(obj) (obj)

#ifdef _C_CLASS_MACRO_COMMENT
/*
   SELF_ARG(classname)
   - Used in method declaration/definition to define the first argument as the object pointer.
   - Expands to: classname* self
   Example:
       METHOD_DEF_NO_ARGS(Bob, void, say_hi)
       expands to: void Bob_say_hi(Bob* self)
*/
#endif // _C_CLASS_MACRO_COMMENT
#define SELF_ARG(classname) classname* self

#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- CLASS DECLARATION ---------------------- */
/*
   CLASS(name)
   - Declares a struct for a "class".
   - Use at the top of the header file for your class.
   Example:
       CLASS(Bob) {
           int x;
           METHOD_PTR(Bob, void, say_hi, );
           METHOD_PTR(Bob, int, add, int a, int b);
       };
*/
#endif // _C_CLASS_MACRO_COMMENT

#define CLASS(name) \
    typedef struct name name; \
    struct name

#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- METHOD POINTERS ---------------------- */
/*
   METHOD_PTR(classname, ret, method, ...)
   - Declares a function pointer inside the struct to represent a method.
   - Can have additional arguments after SELF_ARG.
   Example:
       METHOD_PTR(Bob, void, say_hi, );           // no extra arguments
       METHOD_PTR(Bob, int, add, int a, int b);   // with arguments
*/
#endif // _C_CLASS_MACRO_COMMENT

#define METHOD_PTR(classname, ret, method, ...) \
    ret (*method)(SELF_ARG(classname), ##__VA_ARGS__)

#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- METHOD IMPLEMENTATION ---------------------- */
#endif // _C_CLASS_MACRO_COMMENT
#ifdef _C_CLASS_MACRO_COMMENT
/* Normal methods with arguments */
#endif // _C_CLASS_MACRO_COMMENT

#define METHOD_IMPL(classname, ret, method, ...) \
    ret classname##_##method(SELF_ARG(classname), __VA_ARGS__)

#ifdef _C_CLASS_MACRO_COMMENT
/* Methods with NO additional arguments */
#endif // _C_CLASS_MACRO_COMMENT

#define METHOD_IMPL_NO_ARGS(classname, ret, method) \
    ret classname##_##method(SELF_ARG(classname))

#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- CONSTRUCTOR / DESTRUCTOR ---------------------- */
#endif // _C_CLASS_MACRO_COMMENT
#ifdef _C_CLASS_MACRO_COMMENT
/* Constructor generator macro */
#endif

#define CONSTRUCTOR_OF(classname, ...) \
    classname* classname##_new(__VA_ARGS__)

#ifdef _C_CLASS_MACRO_COMMENT
/* Destructor generator macro */
#endif // _C_CLASS_MACRO_COMMENT

#define DESTRUCTOR_OF(classname) \
    void classname##_delete(classname* self)

#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- OBJECT MANAGEMENT ---------------------- */
#endif // _C_CLASS_MACRO_COMMENT
#ifdef _C_CLASS_MACRO_COMMENT
/* Allocate new object */
#endif // _C_CLASS_MACRO_COMMENT

#define NEW(classname, ...) classname##_new(__VA_ARGS__)

#define NEW_NO_ARGS(classname) classname##_new()

#ifdef _C_CLASS_MACRO_COMMENT
/* Delete object */
#endif // _C_CLASS_MACRO_COMMENT

#define DELETE(classname, obj) classname##_delete(obj)

#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- REGISTER METHOD ---------------------- */
/*
   REGISTER_METHOD(obj, classname, method)
   - Assigns a method implementation to the function pointer in the struct.
   - Typically used inside the constructor.
   Example:
       REGISTER_METHOD(a, Bob, say_hi); // assigns Bob_say_hi in the object a
*/
#endif // _C_CLASS_MACRO_COMMENT

#define REGISTER_METHOD(obj, classname, method) \
    (obj)->method = classname##_##method

#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- METHOD CALL ---------------------- */
/*
   METHOD_CALL(obj, method, ...)
   - Calls a method stored in the struct pointer with extra arguments.
   - The first argument (self) is automatically passed.
   Example:
       int result = METHOD_CALL(b, add, 5, 6);
*/
#endif // _C_CLASS_MACRO_COMMENT

#define METHOD_CALL(obj, method, ...) ((obj)->method(SELF(obj), ##__VA_ARGS__))

#ifdef _C_CLASS_MACRO_COMMENT
/*
   METHOD_CALL_NO_ARGS(obj, method)
   - Calls a method stored in the struct pointer that takes no extra arguments.
   - Only the object itself (self) is passed automatically.
   Example:
       METHOD_CALL_NO_ARGS(b, say_hi);
*/
#endif // _C_CLASS_MACRO_COMMENT

#define METHOD_CALL_NO_ARGS(obj, method) ((obj)->method(SELF(obj)))

#ifdef _C_CLASS_MACRO_COMMENT
/* ---------------------- COPY SUPPORT ---------------------- */
/*
   DEFAULT_COPY_DEF(classname)
   - Declares a default shallow copy function for a class.
   - Automatically allocates memory and memcpy's the object.
*/
#endif // _C_CLASS_MACRO_COMMENT
#define DEFAULT_COPY_DEF(classname) \
    classname* classname##_copy(classname* obj)

/*
   DEFAULT_COPY_IMPL(classname)
   - Implements the default shallow copy using malloc + memcpy.
*/
#define DEFAULT_COPY_IMPL(classname) \
    classname* classname##_copy(classname* obj) { \
        classname* copy = malloc(sizeof(classname)); \
        if (!copy) PANIC_RUNTIME("Failed to allocate memory for COPY"); \
        memcpy(copy, obj, sizeof(classname)); \
        return copy; \
    }

/*
   COPY_OF(classname, ...)
   - Optional macro to declare a custom copy function for a class.
   - Allows deep copy overrides.
*/
#define COPY_OF(classname) DEFAULT_COPY_DEF(classname)

/*
   COPY(obj, classname)
   - Generic macro to copy an object.
   - Uses the class's copy function (custom or default).
*/
#define COPY(classname, obj) classname##_copy(obj)

#endif // C_CLASS_H
