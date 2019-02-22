/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
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

#pragma once

#include <detours.h>
// to avoid redefinition problems

#include "Internal.h"

// When detouring __thiscalls, optimization should be disabled to avoid __fastcall being replaced
//#pragma optimize( "", off )
//#pragma optimize( "", on )

#ifndef _DEBUG
#define DisableOptimization optimize( "", off )
#define EnableOptimization optimize( "", on )
#else
#define DisableOptimization
#define EnableOptimization
#endif

#define SetDetourAddress(name, address) name##_original = (name##_original_t) (address)
#define AttachDetourFunction(name, newName) DetourAttach(&(PVOID&)name##_original, newName)

// This goes on the source file. You must give the full name, i.e. MyUILayout::Load, not just Load
#define DetourDeclaration(fullName) fullName##_original_t fullName##_original


// this is used in DllMain before detouring
inline void PrepareDetours(HMODULE hModule)
{
	DisableThreadLibraryCalls(hModule);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
}

// returns a LONG (error)
inline LONG SendDetours()
{
	DetourUpdateThread(GetCurrentThread());
	return DetourTransactionCommit();
}


#define virtual_detour(ClassName, ThisType, FunctionName, decl, body) template<typename T> class ClassName##_##FunctionName ; \
template<typename Result, typename ... Arguments> class ClassName##_##FunctionName##<Result(Arguments...)> : public ClassName \
{ public: typedef Result(__thiscall*original_pointer)(ThisType *, Arguments...); static original_pointer FunctionName##_original; body \
static Result __fastcall FunctionName##_redirected(ThisType * _This, int, Arguments ... args) { \
return (( ClassName##_##FunctionName *)_This)-> FunctionName##_detoured (args...); } \
static inline long attach() { FunctionName##_original = (original_pointer)(GetMethodAddress(ClassName, FunctionName)); \
return DetourAttach(&(PVOID&) FunctionName##_original, FunctionName##_redirected); } }; \
ClassName##_##FunctionName < decl >::original_pointer ClassName##_##FunctionName < decl >:: FunctionName##_original; \
typedef ClassName##_##FunctionName < decl >

#define detour(ClassName, FunctionName, decl, body) virtual_detour(ClassName, ClassName, FunctionName, decl, body)

#define static_detour(ClassName, FunctionName, decl, body) template<typename T> class ClassName##_##FunctionName ; \
template<typename Result, typename ... Arguments> class ClassName##_##FunctionName##<Result(Arguments...)> \
{ public: typedef Result(*original_pointer)(Arguments...); static original_pointer FunctionName##_original; body \
static inline long attach() { FunctionName##_original = (original_pointer)(GetMethodAddress(ClassName, FunctionName)); \
return DetourAttach(&(PVOID&) FunctionName##_original, FunctionName##_detoured); } }; \
ClassName##_##FunctionName < decl >::original_pointer ClassName##_##FunctionName < decl >:: FunctionName##_original; \
typedef ClassName##_##FunctionName < decl >


/*
template<typename T> class								static_detour;
template<typename T, typename U> class					detour;

template<typename Result, typename ... Arguments>
class static_detour<Result(Arguments...)>
{
public:
	typedef Result(*original_pointer)(Arguments...);
	typedef Result(*detoured_pointer)(original_pointer, Arguments...);

	static_detour(DWORD functionAddress)
		: pOriginalFunction((original_pointer)functionAddress)
		, pDetouredFunction(nullptr)
	{
	}

	inline Result operator()(Arguments... args)
	{
		return pOriginalFunction(args);
	}

	inline long assign(detoured_pointer pNewFunction)
	{
		pDetouredFunction = pNewFunction;
		return DetourAttach(&(PVOID&)pOriginalFunction, pDetouredFunction);
	}

protected:
	original_pointer pOriginalFunction;
	detoured_pointer pDetouredFunction;
};

template<typename ThisType, typename Result, typename ... Arguments>
class detour<ThisType, Result(Arguments...)>
{
public:
	typedef Result(__thiscall*original_pointer)(ThisType*, Arguments...);
	typedef Result(__fastcall*detoured_pointer)(ThisType*, int, original_pointer, Arguments...);

	detour(DWORD functionAddress)
		: pOriginalFunction((original_pointer) functionAddress)
		, pDetouredFunction(nullptr)
	{
	}

	inline Result operator()(ThisType* pObject, Arguments... args)
	{
		return pOriginalFunction(pObject, args);
	}

	inline long assign(detoured_pointer pNewFunction)
	{
		pDetouredFunction = pNewFunction;
		return DetourAttach(&(PVOID&)pOriginalFunction, pDetouredFunction);
	}

protected:
	original_pointer pOriginalFunction;
	detoured_pointer pDetouredFunction;
};

#define static_detour(ClassName, FunctionName, decl) static_detour<decl>(GetMethodAddress(ClassName, FunctionName)); \
 typedef static_detour<decl>::original_pointer FunctionName##_original

#define virtual_detour(ThisType, ClassName, FunctionName, decl) typedef detour<ThisType, decl>::original_pointer FunctionName##_original; \
detour<ThisType, decl>(GetMethodAddress(ClassName, FunctionName))

#define detour(ClassName, FunctionName, decl) virtual_detour(ClassName, ClassName, FunctionName, decl)

#define detour2(ClassName, FunctionName, decl, body) template<typename T> class ClassName##_##FunctionName; \
 template<typename Result, typename ... Arguments> class ClassName##_##FunctionName<decl> : ClassName { body \
static Result __fastcall FunctionName##_redirected(ClassName* _This, int, Arguments ... args) { \
((ClassName*)_This)->FunctionName(); } };

*/

///
/// @page detouring Detouring
///
/// This page contains information about detouring (redirenting methods) with the ModAPI.
/// One of the things that makes the ModAPI powerful is the ability to redirect Spore methods. Most of the methods
/// that are documented can be detoured.
///
/// When a method is detoured, the new code is executed everytime the method is called (even if it is the Spore code the
/// one that calls it).
///
/// Detouring methods has now become a quite simple task if you have the ModAPI templates for Visual Studio installed.
/// When you use "Add new item..." in VS, you will find the item template "ModAPI Detouring" in the "ModAPI" category.
/// Each detouring item can only redirect methods from a specific class/namespace.
/// 
/// When clicking the item template a dialog will emerge. You must use fully-qualified names in everything you
/// write in the dialog (e.g. App::Property instead of just Property). You must fill the following:
/// - **Class/namespace**: The name of the class or namespace of which you are detouring methods, such as Palettes::PaletteUI.
/// - **Is namespace?**: Check this if you are detouring a namespace and not a class.
/// - Below that you will find two text fields: in the leftside one, insert the method declaration 
/// (which you can copy from the documentation), such as App::Property& SetValueBool(const bool &value) (remember, use
/// fully-qualified names!). The rightside field must only be used when the method you are detouring is virtual: you have to put
/// the full name of the class the virtual method belongs to.
/// If you want to add more methods, use the **Add** button at the bottom. When you are done, press **Finish** and .h and .cpp files
/// will be generated for you.
///
/// **Warning**: The template tries to guess which header file it must include in your .h file. It might fail for certain
/// classes and namespaces, so if it does not work it must be changed manually.
/// 
///
/// ## Calling the original method
///
/// Most detoured methods just check something, and end up executing the original code in most cases. Doing that is
/// very simple, just use the original function name with "_original" at the end. If the method is not static, the first
/// argument will be 'this', followed by whatever arguments the method needs. For example:
/// ~~~~~~~~~~~~~~~~~~{.cpp}
/// // Assuming we have detoured the App::Property::SetValueBool(const bool &value) method
/// return SetValueBool_original(this, value);
/// ~~~~~~~~~~~~~~~~~~
/// 
///
/// ## Additional notes
/// 
/// You will see lots of classes in the ModAPI are actually interfaces (that is, they have no implementation); those
/// are all the classes prefixed with I, for example IPropManager. If you want to detour methods for that, you have
/// to extend the classes that are prefixed with c, e.g. cPropManager. Note that not all interfaces have an implementation like
/// that, and therefore cannot be detoured.
///
