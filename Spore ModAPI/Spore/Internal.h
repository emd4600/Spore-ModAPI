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

#include <cstdint>
#include <cctype>
#include <windows.h>
#include <Spore\CppRevEng.h>


#ifdef MODAPI_DLL_EXPORT 
/*Enabled as "export" while compiling the dll project*/
#define MODAPI __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define MODAPI __declspec(dllimport)  
#endif

#ifdef MODAPI_DLL_EXPORT
	#if EXECUTABLE_TYPE == 0
		#define SelectAddress(addressDisk, unused, addressSteamPatched) addressDisk
	#elif EXECUTABLE_TYPE == 2
		#define SelectAddress(addressDisk, unused, addressSteamPatched) addressSteamPatched
	#endif
#endif


// The base address of the running program.
extern MODAPI uintptr_t baseAddress;


#define field(_This, offset) *(int*)(_This + offset)
#define vftable(_This, offset) *(int*)((*(int*)_This) + offset)

#define VOID_THISCALL(address, object) ((void(__thiscall*)(void*))(address))((void*) object)

#define METHOD(address, thisType, returnType, name, parameters, passedArguments) returnType name(parameters) { return ((returnType(__thiscall*)(thisType*, parameters)) (address))(this, passedArguments); }
#define METHOD_VOID(address, thisType, name, parameters, passedArguments) void name(parameters) { ((void(__thiscall*)(thisType*, parameters)) (address))(this, passedArguments); }

#define METHOD_(address, thisType, returnType, name) returnType name() { return ((returnType(__thiscall*)(thisType*)) (address))(this); }
#define METHOD_VOID_(address, thisType, name) void name() { ((void(__thiscall*)(thisType*)) (address))(this); }

#define METHOD_const(address, thisType, returnType, name, parameters, passedArguments) returnType name(parameters) const { return ((returnType(__thiscall*)(const thisType*, parameters)) (address))(this, passedArguments); }
#define METHOD_VOID_const(address, thisType, name, parameters, passedArguments) void name(parameters) const { ((void(__thiscall*)(const thisType*, parameters)) (address))(this, passedArguments); }

#define METHOD_const_(address, thisType, returnType, name) returnType name() const { return ((returnType(__thiscall*)(const thisType*)) (address))(this); }
#define METHOD_VOID_const_(address, thisType, name) void name() const { ((void(__thiscall*)(const thisType*)) (address))(this); }

#define STATIC_METHOD(address, returnType, name, parameters, passedArguments) returnType name(parameters) { return ((returnType(*)(parameters)) (address))(passedArguments); }
#define STATIC_METHOD_VOID(address, name, parameters, passedArguments) void name(parameters) { ((void(*)(parameters)) (address))(passedArguments); }

#define STATIC_METHOD_(address, returnType, name) returnType name() { return ((returnType(*)()) (address))(); }
#define STATIC_METHOD_VOID_(address, name) void name() { ((void(*)()) (address))(); }

#define CALL(address, returnType, parameters, passedArguments) ((returnType (__thiscall*)(parameters)) (address))(passedArguments)
#define CALL_(address, returnType) ((returnType (__thiscall*)()) address)()
#define STATIC_CALL(address, returnType, parameters, passedArguments) ((returnType (*)(parameters)) (address))(passedArguments)
#define STATIC_CALL_(address, returnType) ((returnType (*)()) (address))()


// Methods that get the address from a list; they must not be in the class declaration
// The VOID_ counterpart is actually not necessary, but we keep it here because old methods still use it
// Unfortunately we used a different argument order than in CppRevEng, so we have to keep these old macros

#define auto_METHOD(thisType, returnType, name, parameters, passedArguments) RedirectMethod(thisType, name, returnType, parameters, passedArguments)
#define auto_METHOD_VOID(thisType, name, parameters, passedArguments) METHOD_VOID(GetAddress(thisType, name), thisType, thisType::name, parameters, passedArguments)

#define auto_METHOD_(thisType, returnType, name) RedirectMethod_noargs(thisType, name, returnType)
#define auto_METHOD_VOID_(thisType, name) METHOD_VOID_(GetAddress(thisType, name), thisType, thisType::name)

#define auto_METHOD_const(thisType, returnType, name, parameters, passedArguments) RedirectMethod_const(thisType, name, returnType, parameters, passedArguments)
#define auto_METHOD_VOID_const(thisType, name, parameters, passedArguments) METHOD_VOID_const(GetAddress(thisType, name), thisType, thisType::name, parameters, passedArguments)

#define auto_METHOD_const_(thisType, returnType, name) RedirectMethod_noargs_const(thisType, name, returnType)
#define auto_METHOD_VOID_const_(thisType, name) METHOD_VOID_const_(GetAddress(thisType, name), thisType, thisType::name)

#define auto_METHOD_VIRTUAL(className, thisType, returnType, name, parameters, passedArguments) RedirectVirtualMethod(className, thisType, name, returnType, parameters, passedArguments)
#define auto_METHOD_VIRTUAL_VOID(className, thisType, name, parameters, passedArguments) METHOD_VOID(GetAddress(className, name), thisType, className::name, parameters, passedArguments)

#define auto_METHOD_VIRTUAL_(className, thisType, returnType, name) RedirectVirtualMethod_noargs(className, thisType, name, returnType)
#define auto_METHOD_VIRTUAL_VOID_(className, thisType, name) METHOD_VOID_(GetAddress(className, name), thisType, className::name)

#define auto_METHOD_VIRTUAL_const(className, thisType, returnType, name, parameters, passedArguments) RedirectVirtualMethod_const(className, thisType, name, returnType, parameters, passedArguments)
#define auto_METHOD_VIRTUAL_VOID_const(className, thisType, name, parameters, passedArguments) METHOD_VOID_const(GetAddress(className, name), thisType, className::name, parameters, passedArguments)

#define auto_METHOD_VIRTUAL_const_(className, thisType, returnType, name) RedirectVirtualMethod_noargs_const(className, thisType, name, returnType)
#define auto_METHOD_VIRTUAL_VOID_const_(className, thisType, name) METHOD_VOID_const_(GetAddress(className, name), thisType, className::name)

#define auto_STATIC_METHOD(className, returnType, name, parameters, passedArguments) RedirectStaticMethod(className, name, returnType, parameters, passedArguments)
#define auto_STATIC_METHOD_VOID(className, name, parameters, passedArguments) STATIC_METHOD_VOID(GetAddress(className, name), className::name, parameters, passedArguments)

#define auto_STATIC_METHOD_(className, returnType, name) RedirectStaticMethod_noargs(className, name, returnType)
#define auto_STATIC_METHOD_VOID_(className, name) STATIC_METHOD_VOID_(GetAddress(className, name), className::name)


#define ASSERT_SIZE(name, size) static_assert(sizeof(name) == size, "sizeof " #name " != " #size);

#ifdef _DEBUG
#define SporeDebugPrint(...) App::ConsolePrintF(__VA_ARGS__)
#else
#define SporeDebugPrint(...)
#endif

/// If compiled on a Debug configuration, triggers the Visual Studio Just-In-Time debugger,
/// allowing you to attach the debugger to Spore and continue executing from this instruction.
/// @returns false if there was an error.
bool ManualBreakpoint();

namespace Addresses(Internal)
{
	DeclareAddress(Allocator_ptr);
	DeclareAddress(new_);
	DeclareAddress(delete_);
}
