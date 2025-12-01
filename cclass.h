#ifndef C_CLASS_H
#define C_CLASS_H


#define C_CLASS_VERSION_MAJOR 1
#define C_CLASS_VERSION_MINOR 0
#define C_CLASS_VERSION_PATCH 0


#define C_CLASS_VERSION_STRING \
    C_CLASS_VERSION_STRING_IMPL(C_CLASS_VERSION_MAJOR, C_CLASS_VERSION_MINOR, C_CLASS_VERSION_PATCH)

#define C_CLASS_VERSION_STRING_IMPL(major, minor, patch) #major "." #minor "." #patch

#define C_CLASS_VERSION_NUM (C_CLASS_VERSION_MAJOR * 100) + (C_CLASS_VERSION_MINOR * 10) + C_CLASS_VERSION_PATCH


// NOTE(A-Boring-Square): does not guarantee that cclass will use SIMD it only enables it as an option
#ifndef C_CLASS_USE_SIMD
#define C_CLASS_USE_SIMD 1
#endif // C_CLASS_USE_SIMD


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

#endif // C_CLASS_H