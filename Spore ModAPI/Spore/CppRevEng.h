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


#include "CppRevEngBase.h"
#include <detours.h>

/*
This class is used to simplify the process of detouring functions. When using DLL injection,
detouring is the most important technique: it allows you to hook the executable methods and
override them with your own functionality.

This header file defines 3 macros:
 - `static_detour`: for static functions.
 - `member_detour`: for non-static, non-virtual methods.
 - `virtual_detour`: for non-static, virtual methods.

These macros are class declarations, so you must follow them with a {};  - don't forget the final semicolon!
Also, use the `public:` keyword when defining the detoured method.

All macros take at least two parameters:
 - `name`: A unique name to identify the detour object. You will use it to attach the detour.
 - `declaration`: The type and parameter types of the function. Examples: `void(int)`, `bool()`, `const float&(const vector<int>, int**)`

## Detouring static functions

Imagine you want to detour a static function that returns a float, and takes a const char* as parameter. You would do it like this:

```cpp
static_detour(MyDetour1, float(const char*)) {
public:
	float detoured(const char* pString) {
		if (pString[0] == '_') return -1.0f;
		else {
			// We call the original function; as you can see you can use any parameter you want
			return original_function(pString) + original_function("object");
		}
	}
};
```

## Detouring a member method

Imagine you want to detour a method that is mebmer of a certain class. It returns void, and does not take any parameter.
You would do it like this:
```cpp
// A class declaration, the method belongs to this class
class ClassManager {
protected:
	vector<void*> mObjects;
}

member_detour(MyDetour2, ClassManager, void()) {
public:
	void detoured() {
		MessageBox("Objects are being deleted");
		// You can access the public and protected fields:
		mObjects.clear();
	}
};
```

## Detouring a virtual member method

Imagine you want to detour a virtual method that is member of a certain class. It returns void, and takes 2 float parameters.
You would do it like this:
```cpp
// A class declaration, the method belongs to this class
// It's important to know in which class the method was declared. In this case, let's imagine it was declared in ICombatant
class cCreature : public IObject, public ICombatant {
protected:
	float mHealthPoints;
}

virtual_detour(MyDetour3, cCreature, ICombatant, void(float, float)) {
public:
	void detoured(float strength, float distance) {
		// I want to be immortal!
		if (mHealthPoints < 10) mHealthPoints += 1000.0f;
		original_function(strength, distance);
	}
}
```

## Attaching/detaching detours

Detours must be attached/detached in the DllMain function. This header provides two functions:
- `PrepareDetours(HANDLE)`: must be called before using any detours.
- `CommitDetours()`: must be used after using detours

An example DllMain would look like this:
```cpp
switch (dwReason) {
	case DLL_PROCESS_ATTACH:
	PrepareDetours(hHandle);
	MyDetour1.attach(Address(0x405810));
	// You can also use address lists
	MyDetour2.attach(GetAddress(ClassManager, Create));
	CommitDetours();
	break;

case DLL_PROCESS_DETACH:
	PrepareDetours(hHandle);
	MyDetour1.detach();
	MyDetour2.detach();
	CommitDetours();
	break;
}
```

## Separating header/cpp files

If you want, you can declare the detour in a header file, and specify the code in a cpp file. It would look like this:

```cpp
// In the header file:
static_detour(MyDetour1, float(const char*)) {};

// In the cpp file:
// Use the macro DETOUR to access the method
float MyDetour1::DETOUR(const char* pString) {
	if (pString[0] == '_') return -1.0f;
	else {
		// We call the original function; as you can see you can use any parameter you want
		return original_function(pString) + original_function("object");
	}
}
```
*/

// When detouring __thiscalls, optimization should be disabled to avoid __fastcall being replaced

#define DisableOptimization optimize( "", off )
#define EnableOptimization optimize( "", on )

// Attaches a detour with the address taken from an address namespace.
#define attach_detour(name, className, methodName) name::attach(GetAddress(className, methodName))

// A macro to make code shorter
#define DETOUR detour_object::detoured

// Call in DllMain before attaching/detaching any detours.
inline void PrepareDetours(HMODULE hModule)
{
	DisableThreadLibraryCalls(hModule);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
}

// Commits all the detours. This must be called in DllMain after all detours have been attached.
// Returns NO_ERROR if the detours were commited successfully, otherwise returns error code defined in DetourTransactionCommit
inline LONG CommitDetours()
{
	DetourUpdateThread(GetCurrentThread());
	return DetourTransactionCommit();
}

template<typename T, typename U>
class static_detour_;

template<typename T, typename B, typename V, typename U>
class member_detour_;

/// The object used for detouring static functions. 
/// This is internal, for real usage check static_detour macro.
///
/// @tparam DetourClass The name of the class that is extending this object and is being used to hold the detour.
/// @tparam Result The return type of the function to detour, can be void.
/// @tparam Parameters The parameter types of the function to detour, can be empty.
template<typename DetourClass, typename Result, typename ... Parameters>
struct static_detour_<DetourClass, Result(Parameters...)>
{
public:
	/// The type of function pointer used to keep track of the original function.
	typedef Result(*detour_pointer)(Parameters...);

	typedef static_detour_<DetourClass, Result(Parameters...)> detour_object;

	/// The pointer to the original function, you can call this with the same parameters as the function.
	static detour_pointer original_function;

	static Result detoured_function(Parameters... args) {
		int fake;
		return ((DetourClass*)&fake)->detoured(args...);
	}

	Result detoured(Parameters...);

	static LONG attach(UINT function_address) {
		original_function = (detour_pointer)function_address;
		return DetourAttach(&(PVOID&)original_function, detoured_function);
	}

	static LONG detach() {
		return DetourDetach(&(PVOID&)original_function, detoured_function);
	}
};

/// @tparam DetourClass The name of the class that is extending this object and is being used to hold the detour.
/// @tparam BaseClass The name of the class this object is simulating, must contain the method (or any of its superclasses must)
/// @tparam VirtualClass The name of the base class where the method was defined. For non-virtual methods, this must be the same as BaseClass.
/// @tparam Result The return type of the function to detour, can be void.
/// @tparam Parameters The parameter types of the function to detour, can be empty.
template<typename DetourClass, typename BaseClass, typename VirtualClass, typename Result, typename ... Arguments>
struct member_detour_<DetourClass, BaseClass, VirtualClass, Result(Arguments...)> : public BaseClass
{
public:
	/// The type of function pointer used to keep track of the original function.
	typedef Result(__thiscall*detour_pointer)(VirtualClass*, Arguments...);

	typedef member_detour_<DetourClass, BaseClass, VirtualClass, Result(Arguments...)> detour_object;

	/// The pointer to the original function, you can call this with the same parameters as the function.
	static detour_pointer original_function;

#pragma DisableOptimization
	static Result __fastcall detoured_function(VirtualClass* object, int edx, Arguments... args) {
		return ((DetourClass*)object)->detoured(args...);
	}
#pragma EnableOptimization

	Result detoured(Arguments...);

	static LONG attach(UINT function_address) {
		original_function = (detour_pointer)function_address;
		return DetourAttach(&(PVOID&)original_function, detoured_function);
	}

	static LONG detach() {
		return DetourDetach(&(PVOID&)original_function, detoured_function);
	}
};

template<class DetourClass, typename Result, typename ... Arguments>
typename static_detour_<DetourClass, Result(Arguments...)>::detour_pointer
static_detour_<DetourClass, Result(Arguments...)>::original_function;

template<class DetourClass, typename BaseClass, typename VirtualClass, typename Result, typename ... Arguments>
typename member_detour_<DetourClass, BaseClass, VirtualClass, Result(Arguments...)>::detour_pointer
member_detour_<DetourClass, BaseClass, VirtualClass, Result(Arguments...)>::original_function;


/// Detours an static method. In the macro parameters you must specify:
/// - name: A name given to this detour object, to differentiate it from the rest.
/// - delcaration: The return and parameter types, such as `bool(int, float)`
///
/// Inside the detoured function, you can call the original function using `original_function()` with 
/// the appropiate parameters. For example, `original_function(3, myObject, 4.0)`
///
/// This is a class object, so you must follow this declaration with {}. Inside you can define
/// static functions and static variables as well.
///
/// @param name The name of this detour object.
/// @param declaration The function declaration, with no names. For example, <code>void(int, float)</code>
#define static_detour(name, declaration) struct name : public static_detour_< name , declaration > 

/// Detours a class member method. In the macro parameters you must specify:
/// - name: A name given to this detour object, to differentiate it from the rest.
/// - baseClass: The class that the method belongs to.
/// - delcaration: The return and parameter types, such as `bool(int, float)`
///
/// Inside the detoured function, you can call the original function using `original_function()` with 
/// the appropiate parameters; the first parameter must be the `this` pointer (or any other object of the class) pointer. 
/// For example, `original_function(this, 3, myObject, 4.0)`
///
/// Inside the detoured function, you can can access the `this` pointer and any public/protected fields of the base class.
///
/// This is a class object, so you must follow this declaration with {}. Inside you can define
/// methods (static and member) and static variables as well. You cannot add member variables.
///
/// @param name The name of this detour object.
/// @param baseClass The name of the class where the method is. From the detoured code you can access its members.
/// @param declaration The method declaration, with no names. For example, <code>void(int, float)</code>
#define member_detour(name, baseClass, declaration) struct name : public member_detour_< name , baseClass, baseClass, declaration > 

/// Detours a virtual class member method. In the macro parameters you must specify:
/// - name: A name given to this detour object, to differentiate it from the rest.
/// - baseClass: The class that the method belongs to.
/// - virtualClass: The parent class that declared the virtual method.
/// - delcaration: The return and parameter types, such as `bool(int, float)`
///
/// Not assigning `virtualClass` correctly might lead to crashes or unexpected behaviour. For example:
///
/// ```cpp
/// class A {
///    virtual void func_A();
/// }
/// class B {
///    virtual void func_B(int);
/// }
/// class C : public A, public B {
///    virtual void func_B(int) override;
/// }
/// ```
///
/// If you want to detour `func_B`, you need to use the macro `virtual_detour(MyDetour, C, B, void(int))`
///
/// Inside the detoured function, you can call the original function using `original_function()` with 
/// the appropiate parameters; the first parameter must be the `this` pointer (or any other object of the class) pointer. 
/// For example, `original_function(this, 3, myObject, 4.0)`
///
/// Inside the detoured function, you can can access the `this` pointer and any public/protected fields of the base class.
///
/// This is a class object, so you must follow this declaration with {}. Inside you can define
/// methods (static and member) and static variables as well. You cannot add member variables.
///
/// @param name The name of this detour object.
/// @param baseClass The name of the class where the method is. From the detoured code you can access its members.
/// @param virtualClass The name of the class where the method is declared.
/// @param declaration The method declaration, with no names. For example, <code>void(int, float)</code>
#define virtual_detour(name, baseClass, virtualClass, declaration) struct name : public member_detour_< name , baseClass, virtualClass, declaration > 
