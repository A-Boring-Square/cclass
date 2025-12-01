<!DOCTYPE html>
<html lang="en">
<body>

<h1>CClass</h1>
<p><strong>Lightweight C dialect for classes and object-oriented macros</strong></p>

<!-- Badges -->
<p>
<img src="https://img.shields.io/badge/status-beta-yellow" alt="status-beta">
<img src="https://img.shields.io/badge/license-MIT-green" alt="license-MIT">
<img src="https://img.shields.io/badge/compiler-GCC%20/%20Clang%20/%20MSVC-blue" alt="compiler">
</p>

<h2>Overview</h2>
<p>
CClass is a lightweight C dialect that adds class-like syntax to C. It is a superset of C, fully compatible with any C compiler. All code is passed directly to the C compiler after macro expansion. CClass introduces optional OOP-like abstractions while keeping full access to structs and standard C features.
</p>

<div class="rant">
<h3>Motivation</h3>
<p>
C++ adds complexity, templates, multiple inheritance, and hidden behaviors that are unnecessary for many C projects. Maintenance becomes difficult, especially for low-level and embedded systems. CClass solves this by providing a simple, predictable macro-based system that adds class-like features without any new runtime or compiler.
</p>
<ul>
<li>Explicit, predictable memory management</li>
<li>Lightweight and readable syntax</li>
<li>Optional object-oriented abstraction</li>
<li>Structs remain fully accessible</li>
<li>Fully compatible with any C compiler</li>
</ul>
</div>

<h2>Installation</h2>
1. Download the repository or the provided ZIP with headers and static library.
    For example, unzip into a folder called `cclass`.

2. Include the main header in your project:
    `#include "cclass.h"`

3. Include additional modules as needed:
    `#include "cclass_core/math.hclass"`

4. Link against the static library when compiling:
    `gcc main.c -Icclass -Lcclass -lcclass -o main`

5. Run your program
    `./main`
</pre>

<h2>Quick Start</h2>

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
CONSTRUCTOR_OF(Bob, int x_val); // Bob_new(int x_val)
DESTRUCTOR_OF(Bob);             // Bob_delete(Bob* self)
</pre>

<h3>Method Declaration & Implementation</h3>
<pre>
// Declare methods
METHOD_DEF(Bob, int, add, int a, int b);
METHOD_DEF_NO_ARGS(Bob, void, say_hi);

// Implement methods
METHOD_IMPL(Bob, int, add, int a, int b) {
    return self->x + a + b;
}

METHOD_IMPL_NO_ARGS(Bob, void, say_hi) {
    printf("Hi! My x is %d\n", self->x);
}
</pre>

<h3>Object Management</h3>
<pre>
// Allocate and construct object
Bob* b = NEW(Bob, 42);

// Call methods
METHOD_CALL_NO_ARGS(b, say_hi);
int result = METHOD_CALL(b, add, 5, 6);

// Direct struct access
b->x = 100;

// Call implementation directly
int sum = Bob_add(b, 2, 3);

// Destroy object
DELETE(Bob, b);
</pre>

<h2>OOP Philosophy</h2>
<p>
Object-oriented programming is a tool, not a requirement. Use it where grouping data and behavior improves clarity. CClass allows mixing pure C style and optional OOP design seamlessly, without enforcing any runtime overhead.
</p>

<h2>Quick Reference: Macros</h2>
<table>
<tr>
<th>Macro</th><th>Purpose</th><th>Example</th><th>Required / Optional</th>
</tr>
<tr>
<td>CLASS(name)</td>
<td>Declare a struct as a class</td>
<td>CLASS(Bob) { int x; METHOD_PTR(Bob, void, say_hi,); };</td>
<td class="required">Required</td>
</tr>
<tr>
<td>METHOD_PTR(class, ret, method, ...)</td>
<td>Function pointer inside struct</td>
<td>METHOD_PTR(Bob, int, add, int a, int b);</td>
<td class="optional">Optional</td>
</tr>
<tr>
<td>METHOD_DEF(class, ret, method, ...)</td>
<td>Declare method with arguments</td>
<td>METHOD_DEF(Bob, int, add, int a, int b);</td>
<td class="required if using METHOD_PTR">Required</td>
</tr>
<tr>
<td>METHOD_DEF_NO_ARGS(class, ret, method)</td>
<td>Declare method without arguments</td>
<td>METHOD_DEF_NO_ARGS(Bob, void, say_hi);</td>
<td class="required if using METHOD_PTR">Required</td>
</tr>
<tr>
<td>METHOD_IMPL / METHOD_IMPL_NO_ARGS</td>
<td>Implement methods</td>
<td>METHOD_IMPL(Bob, int, add, int a, int b) { ... }</td>
<td class="required">Required</td>
</tr>
<tr>
<td>CONSTRUCTOR_OF / DESTRUCTOR_OF</td>
<td>Create constructor / destructor functions</td>
<td>CONSTRUCTOR_OF(Bob, int x_val);</td>
<td class="required">Required</td>
</tr>
<tr>
<td>REGISTER_METHOD(obj, method)</td>
<td>Assign function pointer</td>
<td>REGISTER_METHOD(obj, say_hi);</td>
<td class="optional">Optional</td>
</tr>
<tr>
<td>NEW / DELETE</td>
<td>Allocate and free objects</td>
<td>Bob* b = NEW(Bob, 42);</td>
<td class="required">Required</td>
</tr>
<tr>
<td>METHOD_CALL / METHOD_CALL_NO_ARGS</td>
<td>Call methods via macros</td>
<td>METHOD_CALL(b, add, 5, 6);</td>
<td class="optional">Optional</td>
</tr>
<tr>
<td>SELF / SELF_ARG</td>
<td>Used for object pointer</td>
<td>SELF(b), SELF_ARG(Bob)</td>
<td class="required">Required</td>
</tr>
</table>

<h2>Examples</h2>
<pre>
// main.cclass
#include "Bob.hclass"

int main() {
    Bob* b = NEW(Bob, 10);
    METHOD_CALL_NO_ARGS(b, say_hi);
    int total = METHOD_CALL(b, add, 5, 5);
    printf("Total: %d\n", total);
    DELETE(Bob, b);
    return 0;
}
</pre>

<h2>License</h2>
<p>MIT License. See LICENSE file for details.</p>

</body>
</html>
