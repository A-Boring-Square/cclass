<!DOCTYPE html>
<html lang="en">
<body>

<h1>cclass</h1>
<p><strong>Lightweight macro-based classes for C</strong></p>

<h2>Overview</h2>
<p>
    <strong>cclass</strong> is a macro-based system for adding class-like structures to C. It allows structs to store function pointers as methods, supports constructors and destructors, and enables safe method calls with or without additional arguments. Unlike C++, it avoids templates, vtables, exceptions, and complex language rules while remaining fully compatible with C.
</p>

<div class="rant">
<h3>Motivation</h3>
<p>
    C++ often adds complexity and hidden behaviors that are unnecessary for many C projects. Multiple inheritance, templates, and compiler intricacies make maintenance difficult, especially in low-level or embedded systems. <strong>cclass</strong> provides a predictable, lightweight alternative for developers who want class-like organization without C++ overhead.
</p>
<ul>
    <li>Explicit memory management</li>
    <li>Lightweight, easy-to-read syntax</li>
    <li>Optional object-oriented abstraction</li>
    <li>Structs remain fully accessible</li>
    <li>Compatible with any C compiler</li>
</ul>
</div>

<h2>API Overview</h2>

<h3>Class Declaration</h3>
<pre>
CLASS(Bob) {
    int x;
    METHOD_PTR(Bob, void, say_hi,);          // No arguments
    METHOD_PTR(Bob, int, add, int a, int b); // With arguments
};
</pre>

<h3>Constructor / Destructor</h3>
<pre>
CONSTRUCTOR_OF(Bob, int x_val); // Generates Bob_new(int x_val)
DESTRUCTOR_OF(Bob);             // Generates Bob_delete(Bob* self)
</pre>

<h3>Method Declaration</h3>
<pre>
// With arguments
METHOD_DEF(Bob, int, add, int a, int b);  

// No additional arguments
METHOD_DEF_NO_ARGS(Bob, void, say_hi);
</pre>

<h3>Method Implementation</h3>
<pre>
// With arguments
METHOD_IMPL(Bob, int, add, int a, int b) {
    return self->x + a + b;
}

// No additional arguments
METHOD_IMPL_NO_ARGS(Bob, void, say_hi) {
    printf("Hi! My x is %d\n", self->x);
}
</pre>

<h3>Register Methods</h3>
<pre>
Bob* obj = malloc(sizeof(Bob));
obj->x = x_val;
REGISTER_METHOD(obj, say_hi); // assigns Bob_say_hi
REGISTER_METHOD(obj, add);    // assigns Bob_add
</pre>

<h3>Method Call Usage</h3>
<p>Call methods using macros:</p>
<pre>
// No extra arguments
METHOD_CALL_NO_ARGS(b, say_hi);

// With extra arguments
int result = METHOD_CALL(b, add, 5, 6);
</pre>

<h3>Direct Struct Access</h3>
<p>You can bypass method pointers entirely and access the struct fields directly:</p>
<pre>
Bob* b2 = NEW(Bob, 100);
printf("Direct access x = %d\n", b2->x);
b2->x = 200;
printf("Updated x = %d\n", b2->x);

// Call function implementations directly
int sum = Bob_add(b2, 5, 6);
printf("Sum: %d\n", sum);
DELETE(Bob, b2);
</pre>

<h2>OOP Philosophy</h2>
<p>
Object-oriented programming is a tool, not a requirement. It is appropriate when grouping data and behavior improves clarity, but it is not universally superior. Developers should choose the right paradigm for the task—sometimes direct struct access and functional patterns are simpler, faster, and more maintainable. <strong>cclass</strong> gives the option of object-oriented design in C without enforcing it.
</p>

<h2>Quick Reference: Macros</h2>
<table>
<tr>
<th>Macro</th><th>Purpose</th><th>Example</th><th>Required / Optional</th>
</tr>
<tr>
<td>CLASS(name)</td>
<td>Declare a struct as a "class"</td>
<td>CLASS(Bob) { int x; METHOD_PTR(Bob, void, say_hi,); };</td>
<td class="required">Required</td>
</tr>
<tr>
<td>METHOD_PTR(class, ret, method, ...)</td>
<td>Function pointer inside struct as method</td>
<td>METHOD_PTR(Bob, int, add, int a, int b);</td>
<td class="optional">Optional</td>
</tr>
<tr>
<td>METHOD_DEF(class, ret, method, ...)</td>
<td>Declare method with arguments</td>
<td>METHOD_DEF(Bob, int, add, int a, int b);</td>
<td class="required">Required if using method pointers</td>
</tr>
<tr>
<td>METHOD_DEF_NO_ARGS(class, ret, method)</td>
<td>Declare method without extra arguments</td>
<td>METHOD_DEF_NO_ARGS(Bob, void, say_hi);</td>
<td class="required">Required if using method pointers</td>
</tr>
<tr>
<td>METHOD_IMPL(class, ret, method, ...)</td>
<td>Implement method with arguments</td>
<td>METHOD_IMPL(Bob, int, add, int a, int b) { ... }</td>
<td class="required">Required</td>
</tr>
<tr>
<td>METHOD_IMPL_NO_ARGS(class, ret, method)</td>
<td>Implement method with no extra arguments</td>
<td>METHOD_IMPL_NO_ARGS(Bob, void, say_hi) { ... }</td>
<td class="required">Required</td>
</tr>
<tr>
<td>CONSTRUCTOR_OF(class, ...)</td>
<td>Generate constructor function</td>
<td>CONSTRUCTOR_OF(Bob, int x_val);</td>
<td class="required">Required</td>
</tr>
<tr>
<td>DESTRUCTOR_OF(class)</td>
<td>Generate destructor function</td>
<td>DESTRUCTOR_OF(Bob);</td>
<td class="required">Required</td>
</tr>
<tr>
<td>REGISTER_METHOD(obj, method)</td>
<td>Assign implementation to function pointer</td>
<td>REGISTER_METHOD(obj, say_hi);</td>
<td class="optional">Optional (only if using METHOD_PTR)</td>
</tr>
<tr>
<td>NEW(class, ...)</td>
<td>Allocate and construct object</td>
<td>Bob* b = NEW(Bob, 42);</td>
<td class="required">Required</td>
</tr>
<tr>
<td>DELETE(class, obj)</td>
<td>Destroy and free object</td>
<td>DELETE(Bob, b);</td>
<td class="required">Required</td>
</tr>
<tr>
<td>METHOD_CALL(obj, method, ...)</td>
<td>Call method with extra arguments</td>
<td>int result = METHOD_CALL(b, add, 5, 6);</td>
<td class="optional">Optional</td>
</tr>
<tr>
<td>METHOD_CALL_NO_ARGS(obj, method)</td>
<td>Call method with no extra arguments</td>
<td>METHOD_CALL_NO_ARGS(b, say_hi);</td>
<td class="optional">Optional</td>
</tr>
<tr>
<td>SELF(obj)</td>
<td>Pass object as first argument to method</td>
<td>METHOD_CALL_NO_ARGS(b, say_hi);</td>
<td class="required</td>
</tr>
<tr>
<td>SELF_ARG(class)</td>
<td>Used in method definition for self pointer</td>
<td>ret METHOD_NAME(class)(SELF_ARG(class)) { ... }</td>
<td class="required</td>
</tr>
</table>


</body>
</html>
