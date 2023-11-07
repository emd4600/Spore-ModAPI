@page CppBasics2 C++ Basics #2: Control Flow, Conditions, Loops

The kind of programs that we have seen in the first tutorial are sequential: they just execute a sequence of instructions in order, always the same.
In this tutorial we introduce **control flow**: how do we make the program change its behaviour depending on the situation?

@section CppBasics2_Conditions Conditions

Conditional statements allow us to execute an instruction only if a condition is met. They look something like this:
~~~~{.cpp}
if (expression) 
{
	code1
}
else
{
	code2
}
~~~~

If `expression` evalutes to true, the `code1` will be executed, the other will not. If `expression` evaluates to false, only `code2` will be executed.
For example, try this code:
~~~~{.cpp}
int x;
cin >> x;

if (x == 5) 
{
	printf("Your number is 5");
}
else
{
	printf("Your number is not 5");
}
~~~~

The `else` branch is optional.

You can also chain if-else statements like this:
~~~~{.cpp}
if (expression1) 
{
	code1
}
else if (expression2)
{
	code2
}
else if (expression3)
{
	code3
}
else 
{
	code4
}
~~~~

If `expression1` is true, then `code1` will be executed. If not, it will try with `expression2`, etc

For the conditions, you can use any of these operators: `==` (equal), `!=` (not equal), `>` (greater than), `<` (smaller than), `>=` (greater or equal than), `<=` (smaller or equal than).
You can also use any `bool` variable.

@section CppBasics2_Loops Loops

Let's say you want to count numbers from 0 to 10. With what we know right now, you would do:
~~~~{.cpp}
printf("0");
printf("1");
printf("2");
printf("3");
printf("4");
printf("5");
printf("6");
printf("7");
printf("8");
printf("9");
printf("10");
~~~~

There is a simpler way to do this, **loops**: repeat a piece of code a certain number of times.
~~~~{.cpp}
for (int i = 0; i <= 10; ++i)
{
	printf("%d", i);
}
~~~~

Don't get scared by the syntax, what it says here is: create a variable called `i`, with value 0. While `i` is smaller or equal to 10, execute the code inside the {} braces. 
At the end of the code, execute `++i`, which increments variable `i` by 1. This is a **for** loop, and every execution of the code inside is called an **iteration**.


There's another type of loop, that will be executed as long as a condition is met:
~~~~{.cpp}
int x;
cin >> x;
while (x != 0)
{
	printf("Wrong number! Try again");
	cin >> x;
}
~~~~