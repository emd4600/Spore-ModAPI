@page CppBasics5 C++ Basics #5: Data Containers
@brief The basic data containers: vector, map, set, stack, queue

Data containers are used to store a collection of elements. In C++ these containers are provided by the **STL** (Standard Library); Spore uses
another library provided by EA called **EASTL**, but the containers are the same and used in the same way.

@section _CppBasics5-Vector Vectors

[Vectors](www.cplusplus.com/reference/vector/vector/) are sequence containers representing arrays that can change in size. 
It's a simple collection of elements stored in the order they are added. This is equivalent to *arrays* and *lists* in other programming languages.
You declare it like `vector<T>`, where `T` is the type of elements stored in the vector, such as `int`.

@note In standard C++, you need to do `std::vector`, or add `using namespace std;` in the file.

If you just declare the vector, it will have no elements by default. You can initialize it with values using `{}`:

~~~~{.cpp}
vector<int> v;  // no elements

vector<int> v = { 3, 19, 0, -4 };  // 4 elements
~~~~

You can access the elements of the vector with `[i]`, where `i` is the index of the element you want to access. These indices are 0-based, which means that 0 is the
first element, 1 is the second,...

~~~~{.cpp}
vector<int> v = { 3, 19, 0, -4 };  // 4 elements

v[2] = 7;

// now v is { 3, 19, 7, -4 }
~~~~

You can get the number of elements that are in the vector by calling `.size()`. This can be used to iterate through all the elements in the vector.

~~~~{.cpp}
// Print all elements in the vector
for (int i = 0; i < v.size(); ++i) {
	printf("%d", v[i]);
}
~~~~

It's also possible to use a *for-each* loop to iterate all elements. This code also prints all the elements:

~~~~{.cpp}
for (int x : v) {
	printf("%d", x);
}
~~~~

Finally, you can insert elements at the end of the vector by calling `.push_back(x)`, where `x` is the element that will be added. Similarly, you can 
remove the last element calling `.pop_back()`:

~~~~{.cpp}
vector<string> v = { "asd" };

v.push_back("water");
// Now v = { "asd", "water" }

v.pop_back();
// Now v = { "asd" };
~~~~

@section CppBasics5-Map Maps

[Maps](http://www.cplusplus.com/reference/map/map/) are associative containers that store elements as a combination of a *key* and its *value*. To each *key*
there is a *value* assigned. In other languages maps are known as *dictionaries*. You declare them like `map<K, V>`, where `K` is the type of the key and `V`
the type of the values. By default they don't have elements, but you can declare them with `{}`. Inside a map, elements are stored in order automatically.

~~~~{.cpp}
// This map assigns a string to every integer
map<int, string> m;

map<int, string> m = {
	{ 5, "water" },
	{192, "planet" }
};
~~~~

You can access elements using `[k]`, where `k` is a key; this will give you access to the value assigned to that key:
~~~~{.cpp}
map<int, string> m = {
	{ 5, "water" },
	{192, "planet" }
};

// Prints "water"
printf(m[5]);

m[13] = "air";
// Now the map will be {5, "water"}, {13, "air"}, {192, "planet"}
~~~~

You can iterate through all elements with a *for-each* loop. It will give you the elements ordered by the key, stored in [pairs](http://www.cplusplus.com/reference/utility/pair/),
where `.first` is the key and `.second` is the value.

~~~~{.cpp}
for (auto x : m) {
	printf("%d: %s", x.first, x.second);
}
~~~~

You can check if a key has a value assigned like this:

~~~~{.cpp}
if (m.find(4) != m.end()) {
	// m[4] exists
}
~~~~

@note If you don't care about the order of the elements, using `hash_map` is more efficient.

@section CppBasics5-Set Sets

[Sets](http://www.cplusplus.com/reference/set/set/) store elements unique elements in order. You can iterate all its elements 
in ascendent order using a *for-each* loop.
The key to sets is that elements are unique: if you have a set `{4, 5}` and insert another 5, the set will remain the same.
You insert elements by calling `.insert(x)`; you can erase an element calling `.erase(x)`:

~~~~{.cpp}
set<int> s = {3, 4, 7};

s.insert(5);
s.insert(10);
s.erase(4);

// the set is now {3, 5, 7, 10}

if (s.find(4) != s.end()) {
	// 4 is contained in the set
}
~~~~

@note Finding an element in a set is faster than finding it in a vector.

@section CppBasics5-Stack Stacks & Queues

[Stacks](http://www.cplusplus.com/reference/stack/stack/) contain elements as *LIFO*: last in, first out. In a stack you cannot access elements using `[i]`; 
instead, you can only access the last element, 
calling `.top()`. You add an element at the top of the stack with `.push(x)` and remove the top element calling `.pop()`. *LIFO* means that the last 
element added will be the first one to be removed.

~~~~{.cpp}
stack<int> s;

s.push(4);
s.push(5);
s.push(200);
s.pop();  // Removes 200

// This will print 5
printf("%d", s.top());
~~~~

[Queues](http://www.cplusplus.com/reference/queue/queue/) are similar to stacks, but they are *FIFO*: first in, first out. This means that
the first element you added will be the first one to be removed; elements will be removed in the order they were added. You can only access the
first element, using `.front()`:
~~~~{.cpp}
queue<int> q;

q.push(4);
q.push(5);
q.push(200);

// This will print 4
printf("%d", q.front());

q.pop();  // Removes 4

// This will print 5
printf("%d", q.front());
~~~~

@note Stacks & queues usually aren't used to store data, but they are very useful for certain algorithms.
