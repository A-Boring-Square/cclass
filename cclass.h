#ifndef C_CLASS_H
#define C_CLASS_H

#define C_CLASS_VERSION_MAJOR 1
#define C_CLASS_VERSION_MINOR 0
#define C_CLASS_VERSION_PATCH 0


#define C_CLASS_VERSION_STRING \
    C_CLASS_VERSION_STRING_IMPL(C_CLASS_VERSION_MAJOR, C_CLASS_VERSION_MINOR, C_CLASS_VERSION_PATCH)

#define C_CLASS_VERSION_STRING_IMPL(major, minor, patch) #major "." #minor "." #patch

#define C_CLASS_VERSION_NUM (C_CLASS_VERSION_MAJOR * 100) + (C_CLASS_VERSION_MINOR * 10) + C_CLASS_VERSION_PATCH

/* ==========================================================
   MACRO-BASED CLASS SYSTEM FOR PURE C
   ----------------------------------------------------------
   Features:
   - Lightweight, vtable-free "classes"
   - Supports constructors, destructors
   - Function pointers stored in struct as methods
   - Safe for methods with and without arguments
   ========================================================== */

/* ---------------------- SELF MACROS ---------------------- */
/*
   SELF(obj)
   - Used when calling a method to pass the object pointer.
   - Expands to just the object itself.
   Example:
       METHOD_CALL(b, say_hi)(SELF(b));
*/
#define SELF(obj) (obj)

/*
   SELF_ARG(classname)
   - Used in method declaration/definition to define the first argument as the object pointer.
   - Expands to: classname* self
   Example:
       METHOD_DEF_NO_ARGS(Bob, void, say_hi)
       expands to: void Bob_say_hi(Bob* self)
*/
#define SELF_ARG(classname) classname* self

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
#define CLASS(name) \
    typedef struct name name; \
    struct name

/* ---------------------- METHOD POINTERS ---------------------- */
/*
   METHOD_PTR(classname, ret, method, ...)
   - Declares a function pointer inside the struct to represent a method.
   - Can have additional arguments after SELF_ARG.
   Example:
       METHOD_PTR(Bob, void, say_hi, );           // no extra arguments
       METHOD_PTR(Bob, int, add, int a, int b);   // with arguments
*/
#define METHOD_PTR(classname, ret, method, ...) \
    ret (*method)(SELF_ARG(classname), ##__VA_ARGS__)

/* ---------------------- METHOD DECLARATION ---------------------- */
/* Normal methods with arguments */
#define METHOD_DEF(classname, ret, method, ...) \
    ret classname##_##method(SELF_ARG(classname), __VA_ARGS__)

/* Methods with NO additional arguments */
#define METHOD_DEF_NO_ARGS(classname, ret, method) \
    ret classname##_##method(SELF_ARG(classname))

/* ---------------------- METHOD IMPLEMENTATION ---------------------- */
/* Normal methods with arguments */
#define METHOD_IMPL(classname, ret, method, ...) \
    ret classname##_##method(SELF_ARG(classname), __VA_ARGS__)

/* Methods with NO additional arguments */
#define METHOD_IMPL_NO_ARGS(classname, ret, method) \
    ret classname##_##method(SELF_ARG(classname))

/* ---------------------- CONSTRUCTOR / DESTRUCTOR ---------------------- */
/* Constructor generator macro */
#define CONSTRUCTOR_OF(classname, ...) \
    classname* classname##_new(__VA_ARGS__)

/* Destructor generator macro */
#define DESTRUCTOR_OF(classname) \
    void classname##_delete(classname* self)

/* ---------------------- OBJECT MANAGEMENT ---------------------- */
/* Allocate new object */
#define NEW(classname, ...) classname##_new(__VA_ARGS__)
/* Delete object */
#define DELETE(classname, obj) classname##_delete(obj)

/* ---------------------- REGISTER METHOD ---------------------- */
/*
   REGISTER_METHOD(obj, method)
   - Assigns a method implementation to the function pointer in the struct.
   - Typically used inside the constructor.
   Example:
       REGISTER_METHOD(obj, say_hi); // assigns Bob_say_hi
*/
#define REGISTER_METHOD(obj, method) \
    (obj)->method = classname##_##method

/* ---------------------- METHOD CALL ---------------------- */
/*
   METHOD_CALL(obj, method, ...)
   - Calls a method stored in the struct pointer with extra arguments.
   - The first argument (self) is automatically passed.
   Example:
       int result = METHOD_CALL(b, add, 5, 6);
*/
#define METHOD_CALL(obj, method, ...) ((obj)->method(SELF(obj), ##__VA_ARGS__))

/*
   METHOD_CALL_NO_ARGS(obj, method)
   - Calls a method stored in the struct pointer that takes no extra arguments.
   - Only the object itself (self) is passed automatically.
   Example:
       METHOD_CALL_NO_ARGS(b, say_hi);
*/
#define METHOD_CALL_NO_ARGS(obj, method) ((obj)->method(SELF(obj)))

#endif // C_CLASS_H