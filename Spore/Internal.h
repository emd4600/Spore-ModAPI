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
#include <ModAPI\CppRevEng.h>

#define SPORE_STANDARD 0
#define SPORE_STEAM 1


/* Modify this according to your build */
// SPORE_STANDARD for Disk version, SPORE_STEAM for all the rest
//#define EXECUTABLE_TYPE SPORE_STANDARD
// Set to 1 to compile for the 2017 Spore patch
//#define PATCHED_SPORE 0

#ifndef EXECUTABLE_TYPE
	#define EXECUTABLE_TYPE SPORE_STANDARD
#endif
#ifndef PATCHED_SPORE
	#define PATCHED_SPORE 0
#endif

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


// believe me, it was the best way to do it I could come up with
#define ManualBreakpoint() ManualBreakpoint_(__FILE__, "Breakpoint");
#define ManualBreakpoint_(text, title) MessageBoxA(NULL, text, title, MB_OK);

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



#if EXECUTABLE_TYPE == SPORE_STANDARD
	#define SelectAddress(addressStandard, addressSteam, addressSteamPatched) addressStandard
#elif EXECUTABLE_TYPE == SPORE_STEAM
	#if PATCHED_SPORE == 0
		#define SelectAddress(addressStandard, addressSteam, addressSteamPatched) addressSteam
	#else
		#define SelectAddress(addressStandard, addressSteam, addressSteamPatched) addressSteamPatched
	#endif
#endif

#define ASSERT_SIZE(name, size) static_assert(sizeof(name) == size, "sizeof " #name " != " #size);