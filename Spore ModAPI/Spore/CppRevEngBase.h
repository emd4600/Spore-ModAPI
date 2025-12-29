#pragma once

/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of CppRevEng.
*
* CppRevEng is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/


#include <cstdint>
#include <Windows.h>

/*
This file defines the main basic utilities you will need if you are doing a DLL injection.

## ADDRESSES

The same executable has different base addresses every time it is executed. This base address
is reflected in the `baseAddress` field included here. Generally you won't need to use it manually,
as there is a macro to convert addresses: `Address()`.
This macro converts a standard address (that includes the standard base 0x400000, used by IDA, Ghidra,...)
into the correct address adapted to the current running program. Example:

myDetour.attach_detour(Address(0x45d230));

Our recomendation, however, is that you don't use addresses directly, since it might be hard to keep track of all of them.
For that, CppRevEng provides two more macros, `Addresses()` and `DeclareAddress()`. On a header file,
they can be used to create a namespace that assigns names to each address so they can be used later:

namespace Addresses(IO) {
	DeclareAddress(ReadInt, 0x45d230);
	DeclareAddress(OpenStream, 0x45e500);
};

Addresses declared like this can then be accessed using the `GetAddress()` macro:

myDetour.attach_detour(GetAddress(IO, ReadInt));

## ADDRESS METHODS

If you are reverse engineering an executable, you will often need to call a method that is part of the executable.
Normally, this would be done by making a function pointer type, casting the function address to that type and then call
it. Since this is very counter-intuitive, CppRevEng includes several macros to help with that.

Our preferred method is declaring the methods in a header pointer, as if they were part of your program.
Then in a .cpp file you use the macros to define their function body, which will just redirect the call to the corresponding address.
In general, all the macros take:
 - The address namespace name (or class name if it's a member method).
 - The function name.
 - The return type.
 - The parameters.
 - The parameter names (they can be generic, don't need to match the header file).

There are three main macros:
 - `RedirectStaticMethod`: used for static and namespace functions.
 - `RedirectMethod`: used non-virtual, non-static class methods.
 - `RedirectVirtualMethod`: used virtual, non-static class methods. This one takes an extra parameter, the virtual class.

These macros have multiple variants (which can be combined):
 - `..._noargs`: if the method does not take any parameters.
 - `..._structret`: if the method returns a struct by value (exactly, if sizeof() > 8)
 - `..._const`: if the method is declared as `const` (cannot be used in static functions).

These macros are meant to be used with the address namespace storage we recommended.
For example:

In the header file:
namespace Spore {
	bool CreateObject(const char* name);
}
namespace Addresses(Spore) { ... };

class Window {
	Window* GetParent() const;
}
namespace Addresses(Window) { ... };

In the source file:
RedirectStaticMethod(Spore, CreateObject, bool, Args(const char* name), Args(name));

RedirectMethod_noargs_const(Window, GetParent, Window*);
*/

// Internal note: Address() can either be used in compile-time declarations (like DeclareAddress()) or
// on runtime; in the first ones baseAddress is 0. Therefore, when using GetAddress() we have to add the base address again.

// Ensures that the address points in the correct address of the running program.
#define Address(value) (baseAddress + value - 0x400000)

// The namespace that contains the addresses for the given class/namespace.
#define Addresses(name) name##_addresses

// This macro is used inside an Addresses(...) namespace in order to store addresses. 
// This will call the Address(...) macro for the value automatically.
// Example:
//
// namespace Addresses(IO) {
//     DeclareAddress(ReadInt, 0x45d230);
//     DeclareAddress(OpenStream, 0x45e500);
// };
// Modified in the ModAPI
#ifdef SDK_TO_GHIDRA
#define DeclareAddress(name)
#else
#define DeclareAddress(name) extern MODAPI const uintptr_t name
#endif
#define DefineAddress(name, value) const uintptr_t name = value - 0x400000
#ifdef SDK_TO_GHIDRA
#define DefineAddressAlias(alias, name)
#else
#define DefineAddressAlias(alias, name) const uintptr_t alias = name
#endif

// Returns the address stored with a DeclareAddress() in the given addresses namespace.
#define GetAddress(namespaceName, name) (Addresses(namespaceName)::name + baseAddress)

// Used to define a variable number of arguments.
#define Args(...) __VA_ARGS__


// -- STATIC METHOS -- //

// Defines the body of a redirected static function whose address is stored in an address namespace. Examples:
//   RedirectStaticMethod(Spore, DestroyObject, void, Args(int index), Args(index));
//   RedirectStaticMethod_noargs(PhysicsEngine, GetGravity, float);
// Parameters:
//    namespaceName: The name of the namespace that stores the addresses.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectStaticMethod(namespaceName, name, returnType, args, argNames) returnType namespaceName::name(args) { return ((returnType(*)(args)) GetAddress(namespaceName, name))(argNames); }

// Defines the body of a redirected static function with no parameters whose address is stored in an address namespace. Examples:
//   RedirectStaticMethod_noargs(PhysicsEngine, GetGravity, float);
// Parameters:
//    namespaceName: The name of the namespace that stores the addresses.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectStaticMethod_noargs(namespaceName, name, returnType) returnType namespaceName::name() { return ((returnType(*)()) GetAddress(namespaceName, name))(); }

// Defines the body of a redirected static function whose address is stored in an address namespace. 
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectStaticMethod_structret(Math, Normalize, Vector3, Args(const Vector3& v), Args(v));
// Parameters:
//    namespaceName: The name of the namespace that stores the addresses.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectStaticMethod_structret(namespaceName, name, returnType, args, argNames) returnType namespaceName::name(args) { returnType ret; ((void(*)(returnType&, args)) GetAddress(namespaceName, name))(ret, argNames); return ret; }

// Defines the body of a redirected static function with no arguments whose address is stored in an address namespace. 
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectStaticMethod_structret(Math, GetZ, Vector3);
// Parameters:
//    namespaceName: The name of the namespace that stores the addresses.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function.
#define RedirectStaticMethod_noargs_structret(namespaceName, name, returnType) returnType namespaceName::name() { returnType ret; ((void(*)(returnType&)) GetAddress(namespaceName, name))(ret); return ret; }

// -- NON-STATIC METHOS -- //

// Defines the body of a redirected member method with no parameters whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method. Examples:
//   RedirectMethod_noargs(Object, GetId, uint32_t);
// Parameters:
//    className: The name of the class that has the method.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectMethod_noargs(className, name, returnType) returnType className::name() { return ((returnType(__thiscall*)(className*)) GetAddress(className, name))(this); }

// Defines the body of a redirected member method whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method. Examples:
//   RedirectMethod(Window, AddChild, void, Args(int index), Args(index));
//   RedirectMethod_const(Vector3, Scale, float, Args(float factor), Args(factor));
// Parameters:
//    className: The name of the class that has the method.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectMethod(className, name, returnType, args, argNames) returnType className::name(args) { return ((returnType(__thiscall*)(className*, args)) GetAddress(className, name))(this, argNames); }

// Defines the body of a redirected const member method with no parameters whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method. Examples:
//   RedirectMethod_noargs_const(Object, GetId, uint32_t);
// Parameters:
//    className: The name of the class that has the method.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectMethod_noargs_const(className, name, returnType) returnType className::name() const { return ((returnType(__thiscall*)(const className*)) GetAddress(className, name))(this); }

// Defines the body of a redirected const member method whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method. Examples:
//   RedirectMethod_const(Vector3, Get, float, Args(int index), Args(index));
// Parameters:
//    className: The name of the class that has the method.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectMethod_const(className, name, returnType, args, argNames) returnType className::name(args) const { return ((returnType(__thiscall*)(const className*, args)) GetAddress(className, name))(this, argNames); }

// Defines the body of a redirected member method with no parameters whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method.
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectMethod_noargs_structret(Vector3, GetInverse(), Vector3);
// Parameters:
//    className: The name of the class that has the method.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectMethod_noargs_structret(className, name, returnType) returnType className::name() { returnType ret; ((void(__thiscall*)(className*, returnType&)) GetAddress(className, name))(this, ret); return ret; }

// Defines the body of a redirected member method whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method.
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectMethod_structret(Vector3, GetScaled, Vector3, Args(float factor), Args(factor));
// Parameters:
//    className: The name of the class that has the method.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectMethod_structret(className, name, returnType, args, argNames) returnType className::name(args) { returnType ret; ((void(__thiscall*)(className*, returnType&, args)) GetAddress(className, name))(this, ret, argNames); return ret; }

// Defines the body of a redirected const member method with no parameters whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method.
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectMethod_noargs_structret_const(Vector3, GetInverse(), Vector3);
// Parameters:
//    className: The name of the class that has the method.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectMethod_noargs_structret_const(className, name, returnType) returnType className::name() const { returnType ret; ((void(__thiscall*)(const className*, returnType&)) GetAddress(className, name))(this, ret); return ret; }

// Defines the body of a redirected const member method whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method.
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectMethod(Window, AddChild, void, Args(int index), Args(index));
//   RedirectMethod_const(Vector3, Normalized, uint32_t, Args(int index), Args(index));
// Parameters:
//    className: The name of the class that has the method.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectMethod_structret_const(className, name, returnType, args, argNames) returnType className::name(args) const { returnType ret; ((void(__thiscall*)(const className*, returnType&, args)) GetAddress(className, name))(this, ret, argNames); return ret; }


// -- VIRTUAL NON-STATIC METHOS -- //


// Defines the body of a redirected virtual method with no parameters whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method. Examples:
//   RedirectVirtualMethod_noargs(Object, GetId, uint32_t);
// Parameters:
//    className: The name of the class that has the method.
//    virtualType: The name of the base class that first declared the virtual method. If there is no mulitple inheritance, use same as `className`.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectVirtualMethod_noargs(className, virtualType, name, returnType) returnType className::name() { return ((returnType(__thiscall*)(virtualType*)) GetAddress(className, name))(this); }

// Defines the body of a redirected virtual method whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method. Examples:
//   RedirectVirtualMethod(Window, AddChild, void, Args(int index), Args(index));
//   RedirectVirtualMethod_const(Vector3, Get, float, Args(int index), Args(index));
// Parameters:
//    className: The name of the class that has the method.
//    virtualType: The name of the base class that first declared the virtual method. If there is no mulitple inheritance, use same as `className`.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectVirtualMethod(className, virtualType, name, returnType, args, argNames) returnType className::name(args) { return ((returnType(__thiscall*)(virtualType*, args)) GetAddress(className, name))(this, argNames); }

// Defines the body of a redirected const virtual method with no parameters whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method. Examples:
//   RedirectVirtualMethod_noargs_const(Object, GetId, uint32_t);
// Parameters:
//    className: The name of the class that has the method.
//    virtualType: The name of the base class that first declared the virtual method. If there is no mulitple inheritance, use same as `className`.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectVirtualMethod_noargs_const(className, virtualType, name, returnType) returnType className::name() const { return ((returnType(__thiscall*)(const virtualType*)) GetAddress(className, name))(this); }

// Defines the body of a redirected const virtual method whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method. Examples:
//   RedirectVirtualMethod_const(Vector3, Get, float, Args(int index), Args(index));
// Parameters:
//    className: The name of the class that has the method.
//    virtualType: The name of the base class that first declared the virtual method. If there is no mulitple inheritance, use same as `className`.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectVirtualMethod_const(className, virtualType, name, returnType, args, argNames) returnType className::name(args) const { return ((returnType(__thiscall*)(const virtualType*, args)) GetAddress(className, name))(this, argNames); }

// Defines the body of a redirected virtual method with no parameters whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method.
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectVirtualMethod_noargs(Object, GetId, uint32_t);
// Parameters:
//    className: The name of the class that has the method.
//    virtualType: The name of the base class that first declared the virtual method. If there is no mulitple inheritance, use same as `className`.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectVirtualMethod_noargs_structret(className, virtualType, name, returnType) returnType className::name() { returnType ret; ((void(__thiscall*)(virtualType*, returnType&)) GetAddress(className, name))(this, ret); return ret; }

// Defines the body of a redirected virtual method whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method.
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectVirtualMethod(Window, AddChild, void, Args(int index), Args(index));
//   RedirectVirtualMethod_const(Vector3, Normalized, uint32_t, Args(int index), Args(index));
// Parameters:
//    className: The name of the class that has the method.
//    virtualType: The name of the base class that first declared the virtual method. If there is no mulitple inheritance, use same as `className`.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectVirtualMethod_structret(className, virtualType, name, returnType, args, argNames) returnType className::name(args) { returnType ret; ((void(__thiscall*)(virtualType*, returnType&, args)) GetAddress(className, name))(this, ret, argNames); return ret; }

// Defines the body of a redirected const virtual method with no parameters whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method.
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectVirtualMethod_noargs(Object, GetId, uint32_t);
// Parameters:
//    className: The name of the class that has the method.
//    virtualType: The name of the base class that first declared the virtual method. If there is no mulitple inheritance, use same as `className`.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
#define RedirectVirtualMethod_noargs_structret_const(className, virtualType, name, returnType) returnType className::name() const { returnType ret; ((void(__thiscall*)(const virtualType*, returnType&)) GetAddress(className, name))(this, ret); return ret; }

// Defines the body of a redirected const virtual method whose address is stored in an address namespace. 
// The addresses namespace must use the same name as the class that has the method.
// This should only be used if it returns a big struct (i.e. sizeof() > 8) by value. Examples:
//   RedirectVirtualMethod(Window, AddChild, void, Args(int index), Args(index));
//   RedirectVirtualMethod_const(Vector3, Normalized, uint32_t, Args(int index), Args(index));
// Parameters:
//    className: The name of the class that has the method.
//    virtualType: The name of the base class that first declared the virtual method. If there is no mulitple inheritance, use same as `className`.
//    name: The name of the function declared in the header.
//    returnType: The return type of the function, can be void.
//    args: The parameter types of this function, use `Args()` to define it (even if it has no parameters).
//    argNames: The parameter names of this function (don't need to match the header), 
//       use `Args()` to define it (even if it has no parameters).
#define RedirectVirtualMethod_structret_const(className, virtualType, name, returnType, args, argNames) returnType className::name(args) const { returnType ret; ((void(__thiscall*)(const virtualType*, returnType&, args)) GetAddress(className, name))(this, ret, argNames); return ret; }