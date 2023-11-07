@page CppBasics1 C++ Basics #1: Variables & Functions

In the %ModAPI, mods are programmed in C++, one of the most famous programming languages (to be precise, we use a modified version called *Microsoft Visual C++*).
There are many extensive tutorials out there to learn C++, with [www.learn.cpp](https://www.learncpp.com/) being a good example. That webpage or other tutorials are the way to
go if you really want to learn C++ (which will be very useful, not only for Spore modding).

However, for people that is only interested in the basics and wants to get started with modding, I've written this series of *C++ Basics* where I'll walk you through
the basic features you must know in order to use the %ModAPI SDK.

The most basic thing: programming in C++ is just writing a series of statements, of instructions. Statements finish with a `;` symbol.

Another important thing: comments. They are parts of the code that C++ will just ignore, so we can use it to say things about our code.
If you use `//`, the rest of the line after those characters will be a comment, and therefore ignored by C++.
There are also block comments: anything enclosed between `/*` and `*/` will be a comment.
As general programming advice, remember this: *Comments should tell why, not how.*

@section CppBasics1_Variables Variables

First of all: **data**. Computers have memory, usually known as RAM; inside that memory, each program stores data. In programming languages, that data is accessed with **variables**,
which are just a name assigned to data in the program's memory. In C++, a variable has three things: the type (is it a number? text?), the name, and of course, the value itself.

~~~~{.cpp}
int x = 5;
~~~~

There, we've just declared the variable `x`, assiging the value 5 to it. So every time we use `x`, the program will read it as 5.
To declare a variable, first you declare its type: in this case, it was an `int`, that is, an integer number (more info on basic types below).

We can try a more complete example:
~~~~{.cpp}
int x = 5;
int y = 12;
int z = x + y;
~~~~

`z` will be 17, because it's adding `x` (which is 5) and `y` (which is 12) together: *5 + 12 = 17*. Pretty simple, right?


@section CppBasics1_Types Basic Data Types

There are some basic data types that you must know:
 - `int`: a signed integer, that is, a number without decimals. It can be any number from *-2147483648* to *2147483647*.
 - `float`: a floating point number, that is, a number with decimals, for example *3.14*. There's a similar type, called `double`, that has more precision, but in Spore it's rarely used.
 - `string`: text. In C++, you can declare text surrounding it with "" (called a string literal). For example: `string myText = "This is an example";`
 - `bool`: a binary variable, can only have values `true` or `false`.
 
@note Strings can also be written as `char*`, called *C-string*, which is an older, more limited version of `string`.


@section CppBasics1_Functions Functions

In most programming languages, we can group instructions inside **functions**. Functions are very useful because they allow us to group code and avoid repeating code.
Imagine you write a basic code, that is going to be used many times within your program. Would you copy it entirely every time you want to use it? No! You just define it
once, and then use it whenever you want.

Functions (sometimes also called **methods**) can receive parameters, which are like variables that can change every time you use the function. It can also "return" a variable,
which allows us to give a result to who called the function. For example, let's write a function that adds two numbers, multiplies them by 3, and then returns the result:
~~~~{.cpp}
int exampleFunc(int x, int y) {
	return (x + y) * 3;
}
~~~~

What says there is basically: create a function called `exampleFunc`, that returns an integer variable, and takes two integers (`x` and `y`) as parameters.
You can then use it in your code like this:
~~~~{.cpp}
// sum will be (5 + 4) * 3 = 27
int sum = exampleFunc(5, 4);
// You can also nest calls
// First the expression in the right will be evaluated, which will return 12
// Then the function will be called as exampleFunc(2, 12)
int sum2 = exampleFunc(2, exampleFunc(1, 3));
~~~~

Try to familiarize with the concept of functions, because in the %ModAPI we will be calling and creating them constantly.

@section CppBasics1_Console Printing to the console

At this point, it might be a good idea to start writing some code, just to get used to it.
Even though you can download programs to write C++ (such as Visual Studio, which the %ModAPI requires), for these simple programs you can just use an online compiler, like 
https://www.onlinegdb.com/online_c++_compiler. The code that will be executed is inside the function called `main`.

We can use the *output console* to write text to the screen. To do that, we will call the function `printf(text)`, where the parameter `text` is the string you want to print:
~~~~{.cpp}
printf("Hello World!");
~~~~

If we use `%` plus some character inside that text, C++ will replace it with the string representation of additional parameters that we pass to the function. 
You can use that to display the values of variables. For example, `%d` is used to display integers. You have more info about the possible formats in the [`printf` documentation](http://www.cplusplus.com/reference/cstdio/printf/).
~~~~{.cpp}
printf("Hello World! %d", 5);
// That will print "Hello World! 5"
~~~~

@note In C++, you should actually use `cout` to write to the console. However, since Spore uses something very similar to `printf`, we teach you this instead.

It is also possible to receive input from the console. Even though we won't use this in the %ModAPI, it's good to know and it will be useful to do tests while you are
learning C++. To receive data from the console, first you declare the variable where it will be stored (declaring means that you won't assign it a value yet). Then you use
`cin` to get the data, like this:
~~~~{.cpp}
int x;
cin >> x;
// Now x contains an integer written by the user to the console
~~~~

It is possible to get multiple things at the same time. The type of the variables will change what the user needs to write:
~~~~{.cpp}
printf("Type your name and age");

string name;
int age;
cin >> name >> age;

// To use a string in printf, you need to call .c_str()
printf("Your name is %s and you are %d years old", name.c_str(), age);
~~~~
