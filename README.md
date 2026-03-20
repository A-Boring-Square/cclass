<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
</head>
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
<p>This is a <strong>single-header library</strong>. There are no dependencies or additional files.</p>
<ol>
<li>Download or copy the <code>cclass.h</code> file into your project directory.</li>
<li>Include it in your source files:</li>
<pre>#include "cclass.h"</pre>
<li>Compile as usual with your C compiler, for example:</li>
<pre>gcc main.c -o main</pre>
<li>Run your program:</li>
<pre>./main</pre>
</ol>

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
<h2>Example</h2>
<pre>
// main.c
#include "cclass.h"

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
