@page Sdk-Basics-Pointers ModAPI SDK Basics: Objects & Pointers
@brief Handling memory and pointers in Spore using Objects

In this tutorial, we assume that you already know of the existance in pointers. It's important that you understand them as they are used a lot in Spore.
As you learned, we can can allocate dynamic memory by using the keyword `new`; that returns a pointer, which will have to be deleted with `delete` later.

Since all new pointers have to be eventually deleted, this is one of the most common sources of errors: **memory leaks**. What happens if we forget to delete
a pointer? We will have memory allocated for an object that is no longer used, so we will wasting memory. But we could also introduce an error the other way round: 
what if we delete an object too soon, and it was being used somewhere else in the code? To fix this, Spore introduces **reference counting**.

@section Sdk-Basics-Pointers-RefCount Reference Counting

Reference counting is the way Spore has to manage dynamic memory: every objects keeps track of how many objects are using it. When the object is used, its
reference count increases by one; when it stops being used, it decreases by 1. 

Now you might be thinking this doesn't solve the problem, because we can just forget to count the reference. But the SDK has an object to do this automatically: `intrusive_ptr`.
An intrusive pointer will increase the reference count when it gets assigned a value, and decrease it when the intrusive pointer dies. The object will delete itself when
the count reaches 0. For example:
~~~~{.cpp}
// The old, unsafe way to do it
PropertyList* myList = new PropertyList();
...
...
delete myList;

// The new, safe way to do it
intrusive_ptr<PropertyList> myList = new PropertyList();
...
...
// We don't have to worry about deleting it, it's done automatically
~~~~

Most classes that support intrusive pointers also define an alias for the intrusive_ptr version, which is the type name finished in `Ptr`. For
`intrusive_ptr<App::PropertyList>` it would be `PropertyListPtr`, for `intrusive_ptr<Simulator::cVehicle>` it would be `cVehiclePtr`, etc

The pointer operators, like dereferrencing (`*`) and member accessing (`->`) are done in exactly the same way with intrusive pointers.
It's still possible to get the native `*` pointer (many methods in the SDK require it) by calling the method `.get()` (in the previous example you would do `myList.get()`); 
of course, do not try to delete the pointer it gives you, since that defeats the purpose.

Try to use intrusive pointers wherever possible, specially when you keep pointers as members of a class.

@note C++ has other pointer management objects like `auto_ptr`, `weak_ptr`, etc. We will never use them.

@subsection Sdk-Basics-Pointers-RefCount-1 Can all objects use reference counting?

No. First, you cannot use intrusive pointers on basic types like `int`, `float`, `vector<int>`, etc (you can have a vector of intrusive pointers though).
Intrusive pointers can only be used on classes that implement these two methods: `AddRef()`, `Release()`. Most Spore objects (or at east those where you can use `new`)
implement those methods.

@subsection Sdk-Basics-Pointers-RefCount-2 Ref. counting in custom objects

If you want to use reference counting on your own classes, you don't need to implement manually. You can just make your class inherit from DefaultRefCounted.
~~~~{.cpp}
class MyClass
	: public DefaultRefCounted
{

}
~~~~

Many interfaces in Spore, like UTFWin::IWinProc or App::IMessageListener require you to implement reference counting. In the cases that you inherit from such classes,
you will aslo need to explicitly tell that you are using the already-implemented methods, which is done like this:
~~~~{.cpp}
// In the .h file
class MyClass
	: public UTFWin::IWinProc
	, public DefaultRefCounted
{
public:
	// Tell the compiler that we are going to implement these methods
	int AddRef() override;
	int Release() override;
};


// In the .cpp file
// Instead of implementing them, we just call the existing implementation:
int MyClass::AddRef() {
	return DefaultRefCounted::AddRef();
}
int MyClass::Release() {
	return DefaultRefCounted::Release();
}
~~~~

@section Sdk-Basics-Pointers-Objects Objects

The most common reference counted class is the Object class. Not only it support reference counting, but it also implements a system for dynamic casting. Casting is
converting from one type to another.

Imagine you have a function that receives a generic object. You want to do something special if that object is actually a creature.
You can do that by using the `object_cast` function: if the object is of the required type, it will return it, otherwise it returns `nullptr`.
~~~~{.cpp}
void function(Object* object) 
{
    auto animal = object_cast<cCreatureAnimal>(object);
    if (animal) {
        // animal is a cCreatureAnimal* now
        animal->SetScale(2.5f);
    }
}
~~~~

You can cast to any class that has a `TYPE` field.

@subsection Sdk-Basics-Pointers-Objects-1 Implementing casting in custom classes

When you inherit your class from `Object`, not only you have to implement `AddRef()` and `Release()` (which you can do with DefaultRefCounted), you also have to
implement the cast method.

First of all, in your class declaration, you have to give the class a unique ID. You can do it by just using `id()` on the class name.
~~~~{.cpp}
// In the .h file
class MyClass
	: public Object
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("MyClass");

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) override;
};
~~~~

The implementation of a cast file is very easy, you just have to compare the given type. In fact, we provide some macros to help you.
 - `CLASS_CAST` should be used for all parent classes that the object can be casted to (i.e. that have a `TYPE` field).
 - If one of the parent classes also inherits from object, it's better to use `PARENT_CLASS` instead.
The first type you should compare is the class itself, then all its parents. At the end of the method return `nullptr`.

~~~~{.cpp}
void* MyClass::Cast(uint32_t type) const
{
	CLASS_CAST(MyClass);
	CLASS_CAST(Object);
	// If we inherited from IWinProc, since it's also an object, we would use PARENT_CAST(IWinProc);
	return nullptr;
}
~~~~