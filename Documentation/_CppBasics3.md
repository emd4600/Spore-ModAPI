@page CppBasics3 C++ Basics #3: Header and Source, Includes

In C++, the code you write is not really what gets executed by the computer. There's a process that converts your C++ code into something the
computer can understand (commonly known as *machine language*); this process is divided in two steps:
 - **Compiling**: A program, called the *compiler*, reads each one of your C++ files and converts them to *object files* (usually `.o` or `.obj` files), 
 which are similar to machine language.
 - **Linking**: The *linker* grabs each of the object files and links them together, building an executable (`.exe`, `.dll`, etc)
 
Usually, the linker and the compiler are the same program: *g++*, *Visual Studio*, *Code::Blocks*,... (for the Spore ModAPI you will end up using 
Visual Studio 2019).

@section CppBasics3-Organization Project organization

When you are working on a big project, you can't have all the code in a single file. C++ organizes its code in `.cpp` (other people might use `.cc`) files. 
But of course, these files are not isolated things: in file `A.cpp` you might want to use functions defined in file `B.cpp`. How could we do that?

For that, C++ introduces the `#include` instruction. With this instruction we can get the contents of one file into another.

```cpp
#include "B.cpp"
#include <vector>
```

`""` is used for files that are inside the same folder; `<>` are used for *library* files, such as the files provided by the C++ library or by the %ModAPI SDK.
The `#include` instruction actually just copies the contents of the file into your file before compiling it (the step before compilation is called *preprocessing*).

Remember we said the compiler compiles each C++ file separately? It compiles every `.cpp` file it finds. Now, let's think about that slowly with an example.
Imagine file `B.cpp` defines a function `void myfunc()`. First, the compiler finds `B.cpp` and generates `B.obj`, which contains the object for `myfunc`. Now,
the compiler finds `A.cpp`; since we have that include instruction, the code of `B.cpp` will be copied into it. 

Now the linker grabs `A.obj` and `B.obj` and tries to link them together, and.... ERROR! Do you see why? Both objects have code for `myfunc`, so the linker does
not know which one it should use. For this reason, you should **never include `.cpp` files**. But then, how do we use code from other files?

@note For if it wasn't clear: **NEVER INCLUDE `.cpp` FILES!**

@section CppBasics3-Declare Declare vs. Define

First we must understand the difference between *declaring* and *defining*. In C++, *declaring* something (a variable, a function, a class,...) means telling
the compiler that it exists, but without giving it any value or code. For example, in this code we define a variable and a function:

```cpp
int myVar;

void myfunc(float radius, float distance);
```

You see? We are telling the compiler that there is an integer variable called `myVar`, and that there is a function with two float parameters called `myfunc`, but we
are not giving it any value nor defining any code. We are just **declaring**.

On the other hand, **defining** is giving value or code to variables and functions. For example, if we wanted to define what we declared before:

```cpp
int myVar = 5;

void myfunc(float radius, float distance) {
	float x = radius * distance;
	printf("x = %f", x);
}
```

You can define in the same file you declare, but you can also define in a different file (that's the trick!)

@section CppBasics3-Header Header files

In real C++ development, a file is actualy splitted: one file will contain declarations (the **header** file, `.h`) and the other will contain the definitions
(the **source** file, `.cpp`). When we include a `.h` file, since it will only have declarations, we won't have any code conflicts.

Notice that even with this separation, the same `.h` could end up included multiple times in a file, which means there would be repeated declarations. To avoid that,
the first line in a header file is always `#pragma once` (or a [header guard](https://www.learncpp.com/cpp-tutorial/header-guards/)); that line ensures that the file
is only copied once.

The previous example with splitted files would look something like this:

*A.h*:
```cpp
#pragma once

int myVar;

void myfunc(float radius, float distance);
```

*A.cpp*:
```cpp
#include "A.h"

int myVar = 5;

void myfunc(float radius, float distance) {
	float x = radius * distance;
	printf("x = %f", x);
}
```

@note When using the %ModAPI SDK, `.cpp` files must always include `"stdafx.h"` in the first line.
