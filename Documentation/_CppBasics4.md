@page CppBasics4 C++ Basics #4: Namespaces, Structs, Classes

@section CppBasics4-Namespaces Namespaces

When a program grows big, there are so many functions and variables that it's almost certain some of them will end up having the same name. In order
to avoid name collisions, C++ introduces **namespaces**. A namespace is a region of code that allows you to declare names without them colliding with
identical names in other namespaces. To access something inside a namespace, you have to prefix it with `namespace_name::`. For example:

```cpp
namespace A
{
	int myvar;
}

int myvar;
```

Here there are no name collisions, because one is `myvar`, whereas the one inside the namespace is `A::myvar`. You can also nest namespaces inside other
namespaces:

```cpp
namespace A
{
	namespace B
	{
		// This is A::B::myvar
		int myvar;
	}
}
```

For example, everything that belongs to the C++ Standard Library is inside the `std` namespace, so you access it like `std::vector`, `std::cin`,...

To avoid writing `::` all the time, there's an instruction that "removes" the namespace scope. `using namespace A;`, where `A` is the namespace name,
means you won't have to write `A::` all the time, C++ will assume it. However, this must be used carefully: think that it's defeating the reason namespaces were
added in the first place. If this instruction is put inside a function, it will only affect inside that function.

@note In the %ModAPI SDK namespaces are very common. Everything related to editors is inside `Editors::`, everything related to graphics is inside `Graphics::`,...

@section CppBasics4-Structs Structs

Quite often a single variable is not enough to represent an object. Imagine you want to represent an employee: you might need to save its ID, its wage, its age,...

```cpp
int joeAge;
int joeID;
float joeWage;

// What if we need another employee?
int kateAge;
int kateID;
float kateWage;
```

For situations like this, C++ introduces **structs** (short for structures). Structs let us create a new type with variables inside:

```cpp
struct Employee
{
	int age;
	int id;
	float wage;
};
```

@note Don't forget the semicolon `;` at the end! It's one of the most common C++ errors.

With that code we have created a new type, `Employee`, with those three variables; variables inside a structure are usually called *members* or *fields*. 
Note that `Employee` is a type, like `int` or `string`, but it's not an object yet. We can create employee objects just like we would with any other type:

```cpp
Employee joe;
Employee kate;
```

When we create a variable of an struct we call that an *instance* of the struct. We can access the members of a struct by using `.` and the member name:

```cpp
Employee joe;
joe.age = 27;
joe.id = 183902;
joe.wage = 1250.8;
```

Having to initialize each value line per line can be too long. We can use *uniform initialization*, which allows us to assign all the values in order:

```cpp
Employee joe = { 27, 183902, 1250.8 };
```

@section CppBasics4-Classes Classes

More advanced C++, such as in the %ModAPI SDK, uses a coding technique known as [**object-oriented programming**](https://en.wikipedia.org/wiki/Object-oriented_programming).
It basically consists in representing everything as objects, with an object being a collection of attributes (for object `Person`, age, height, gender,...) and
behaviours it can exhibit (walk, dance, talk,...).

In C++, we can represent those objects as a `class`:

```cpp
class Date
{
public:
	int day;
	int month;
	int year;
};
```

Notice that the difference with structs is only in the `public:` line; if you want to know more about what it means, check [this learncpp.com tutorial](https://www.learncpp.com/cpp-tutorial/83-public-vs-private-access-specifiers/).
Generally you will use classes, and structs only for very simple structures. 

Classes can also have functions. A *member function* (a function inside of a class), sometimes also called *method*, has access to the variables of the class.

```cpp
class Date
{
public:
	int day;
	int month;
	int year;
	
	void print() {
		printf("%d/%d/%d", day, month, year);
	}
};
```

Just as you can access member by using `.member_name`, you can call methods by using `.method_name(parameters)`:

```cpp
Date date = { 02, 02, 2020 };
Date date2 = { 25, 11, 1975 };

// This prints "2/2/2020"
date.print();

// This prints "25/11/1975"
date2.print();
```

@subsection CppBasics4-Classes-Constructors Constructors & Destructors

By default, when we define a new instance of a class/struct, all its members receive a *default initialization*: if it's an `int`, it gets assigned to 0,
if it's a *float*, it gets assigned to 0.0, etc

That might not be the behaviour we want. For example, if we want to create a `Color` class, we might want it to be a white color by default. We can do this
with **constructors**: a function called when an object is initialized. Constructors are functions that don't have a return type and have the same name
as the class.

```cpp
class Color
{
public:
	int red;
	int green;
	int blue;
	
	// constructor
	Color() {
		red = 255;
		green = 255;
		blue = 255;
	}
};
```

Inside constructors it's common to use *initializer lists*, which are used to assign values to the class members:

```cpp
class Color
{
public:
	int red;
	int green;
	int blue;
	
	// constructor
	Color()
		: red(255)
		, green(255)
		, blue(255)
	{
	}
};
```

Constructors can also receive parameters; the constructor without parameters is the *default* constructor. It's called like that because if no 
constructor is defined, that one is created by default.

```cpp
class Color
{
public:
	int red;
	int green;
	int blue;
	
	// constructor
	Color()
		: red(255)
		, green(255)
		, blue(255)
	{
	}
	
	Color(int value)
		: red(value)
		, green(value)
		, blue(value)
	{
	}
};
```

By default, the constructor is not called; this means that if we do `Color color;`, we cannot assume what the values will be: we say that
the variable is *uninitialized*. There are multiple ways to call the constructor:

```cpp
Color color();
Color color = Color();

Color color(128);
Color color = Color(128);
``` 

@note If you define constructors with parameters, the *default constructor* is not created by default. If you want it, you will have to declare it explicitly.

It's also possible to execute code when an object is destroyed, using a **destructor**. Destructors are defined like a contructor, but prefixed with `~`: `~Color()`

@subsection CppBasics4-Classes-Static Static members

Sometimes, we will want to have members or methods in a class that don't really belong to each instance, but to the class itself. Let's see it with an example:
imagine we want to define a variable that is the class name. That variable doesn't belong to each instance, because all instances of the class must have the same
class name. We can define such variables (and methods) using the `static` keyword.

```cpp
class Date
{
public:
	static string CLASS_NAME = "Date";

	int day;
	int month;
	int year;
	
	void print() {
		printf("%d/%d/%d", day, month, year);
	}
};
```

If we define a `Date date;` instance, we won't be able to do `date.CLASS_NAME`, because as we said the static variable does not belong to the instance, but
to the class itself. We can access it like we accessed names inside a namespace: `Date::CLASS_NAME`.

@note It wouldn't make sense to assign `Date::CLASS_NAME` to anything else. We can use the keyword `const` to ensure that a variable cannot be changed.

@subsection CppBasics4-Classes-Separate Separating in header and source

Remember in the last tutorial when we talked about the [importance of separating in header and source files](_cpp_basics3.html)? We must do the same when
defining a class. 

*Date.h*:
```cpp
#pragma once

class Date
{
public:
	int day;
	int month;
	int year;
	
	Date();
	Date(int d, int m, int y);
	
	void print();
	
	static string CLASS_NAME;
};
```

*Date.cpp*:
```cpp
#include "Date.h"

string Date::CLASS_NAME = "Date";

Date::Date()
	: day(0)
	, month(0)
	, year(0)
{
}

Date::Date(int d, int m, int y)
	: day(d)
	, month(m)
	, year(y)
{
}

void Date::print() {
	printf("%d/%d/%d", day, month, year);
}
```

@section CppBasics4-Polymorphism Polymorphism

Imagine you create a class for `Employer`, and another for `Employee`. They have different attributes and behaviours, yes, but they also have some of them in common:
they both have an age, a name, etc as they both are a person. **Polymorphism** allows us to define a hierarchy between classes that helps us deal with this kind of
situations.

Polymorphism consists in **class inheritance**: classes can inherit (aka *implement* or *extend*) from other classes, automatically gaining all itrs attributes and 
behaviours. Following the previous example, we would create a `Person` class, and then the `Employer` and `Employee` classes would inherit from `Person`:

```cpp
class Person {
public:
	string name;
	int age;
};

class Employee
	: public Person  // this means inherit from Person
{
public:
	float wage;
}
```

If we declare an instance of employee, we will also be able to access the person fields; but if we declare a person, we won't be able to access the wage,
as that is a field for only certain types of person.

```cpp
Employee emp;
emp.name = "Mike";
emp.wage = 1576.0;

Person person;
person.wage = 10;  // ERROR!
```

It's possible to extend more than one class. The extended classes are called *base classes*.

@subsection CppBasics4-Polymorphism-Virtual Virtual methods

Quite often subclasses won't have the same behaviour as their base class. For example, the `Captain` class shouldn't have the same `attack` behaviour than
its base `Creature` class. C++ has a mechanic to *override* methods from a base class: **virtual** methods.

When a method in a base class is declared as `virtual`, it means subclasses can override the code of that method and give it its own behaviour. To override
a method you just have to give it the same declaration: same name, same return type, same parameters, same specifiers.

```cpp
class A {
public:
	virtual void print() {
		printf("This is class A");
	}
};

class B : public A {
public:
	virtual void print() override {
		printf("This is class B");
	}
};
```

```cpp
A a;
// prints "This is class A"
a.print();

B b;
// prints "This is class B"
b.print();
```

@note The `override` keyword is optional. If you have it, the compiler will show you an error in case you declared your method wrong.

There's another concept to learn, *pure virtual* methods. A pure virtual method does not have code; it's a way for the base class to tell that
subclasses should provide their own implementation for those methods. If a class has a pure virtual method, you cannot create new instances of it;
so subclasses will be forced to implement them.

```cpp
class A {
public:
	virtual void print() = 0;  // pure virtual
};

class B : public A {

}

B b;  // ERROR! you haven't implemented print()
```
