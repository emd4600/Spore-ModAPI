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
//#define ida(address) (baseAddress + address - 0x400000)

#define VOID_THISCALL(address, object) ((void(__thiscall*)(void*))(address))((void*) object)

extern unsigned long baseAddress;

#define ENUM_OPERATORS(name) \
inline name operator |(const name selfValue, const name inValue) \
{ \
	return (name)(uint32_t(selfValue) | uint32_t(inValue)); \
} \
inline name operator &(const name selfValue, const name inValue) \
{ \
	return (name)(uint32_t(selfValue) & uint32_t(inValue)); \
}
//constexpr inline enum name operator ~(const enum name selfValue) \
//{ \
//	return (enum name)(~uint32_t(selfValue)); \
//} \

#define ENUM_FLAG_OPERATORS(ENUMTYPE) \
extern "C++" { \
inline ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((uint32_t)a) | ((uint32_t)b)); } \
inline ENUMTYPE &operator |= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((uint32_t &)a) |= ((uint32_t)b)); } \
inline ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((uint32_t)a) & ((uint32_t)b)); } \
inline ENUMTYPE &operator &= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((uint32_t &)a) &= ((uint32_t)b)); } \
inline ENUMTYPE operator ~ (ENUMTYPE a) { return ENUMTYPE(~((uint32_t)a)); } \
inline ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((uint32_t)a) ^ ((uint32_t)b)); } \
inline ENUMTYPE &operator ^= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((uint32_t &)a) ^= ((uint32_t)b)); } \
}


#define PARAMS(...) __VA_ARGS__

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

// We want to define addresses in a list so they can be easily used in detouring
/// Registers the address of a method of a certain class/namespace. This line must be used inside namespaces with names generated
/// with the InternalAddressList() macro.
#define DefineAddress(name, address) const int name = (address)
// Don't forget to add the base address! DefineAddress is processed on compilation, so they don't have baseAddress added
/// Gets the address of a method of the specified class/namespace; this only works for methods whose adresses have been registered.
#define GetMethodAddress(className, functionName) InternalAddressList(className)::functionName + baseAddress
#define InternalAddressList(className) className##_internal_address_list


// Methods that get the address from a list; they must not be in the class declaration

#define auto_METHOD(thisType, returnType, name, parameters, passedArguments) METHOD(GetMethodAddress(thisType, name), thisType, returnType, thisType::name, parameters, passedArguments)
#define auto_METHOD_VOID(thisType, name, parameters, passedArguments) METHOD_VOID(GetMethodAddress(thisType, name), thisType, thisType::name, parameters, passedArguments)

#define auto_METHOD_(thisType, returnType, name) METHOD_(GetMethodAddress(thisType, name), thisType, returnType, thisType::name)
#define auto_METHOD_VOID_(thisType, name) METHOD_VOID_(GetMethodAddress(thisType, name), thisType, thisType::name)

#define auto_METHOD_const(thisType, returnType, name, parameters, passedArguments) METHOD_const(GetMethodAddress(thisType, name), thisType, returnType, thisType::name, parameters, passedArguments)
#define auto_METHOD_VOID_const(thisType, name, parameters, passedArguments) METHOD_VOID_const(GetMethodAddress(thisType, name), thisType, thisType::name, parameters, passedArguments)

#define auto_METHOD_const_(thisType, returnType, name) METHOD_const_(GetMethodAddress(thisType, name), thisType, returnType, thisType::name)
#define auto_METHOD_VOID_const_(thisType, name) METHOD_VOID_const_(GetMethodAddress(thisType, name), thisType, thisType::name)

#define auto_METHOD_VIRTUAL(className, thisType, returnType, name, parameters, passedArguments) METHOD(GetMethodAddress(className, name), thisType, returnType, className::name, parameters, passedArguments)
#define auto_METHOD_VIRTUAL_VOID(className, thisType, name, parameters, passedArguments) METHOD_VOID(GetMethodAddress(className, name), thisType, className::name, parameters, passedArguments)

#define auto_METHOD_VIRTUAL_(className, thisType, returnType, name) METHOD_(GetMethodAddress(className, name), thisType, returnType, className::name)
#define auto_METHOD_VIRTUAL_VOID_(className, thisType, name) METHOD_VOID_(GetMethodAddress(className, name), thisType, className::name)

#define auto_METHOD_VIRTUAL_const(className, thisType, returnType, name, parameters, passedArguments) METHOD_const(GetMethodAddress(className, name), thisType, returnType, className::name, parameters, passedArguments)
#define auto_METHOD_VIRTUAL_VOID_const(className, thisType, name, parameters, passedArguments) METHOD_VOID_const(GetMethodAddress(className, name), thisType, className::name, parameters, passedArguments)

#define auto_METHOD_VIRTUAL_const_(className, thisType, returnType, name) METHOD_const_(GetMethodAddress(className, name), thisType, returnType, className::name)
#define auto_METHOD_VIRTUAL_VOID_const_(className, thisType, name) METHOD_VOID_const_(GetMethodAddress(className, name), thisType, className::name)

#define auto_STATIC_METHOD(className, returnType, name, parameters, passedArguments) STATIC_METHOD(GetMethodAddress(className, name), returnType, className::name, parameters, passedArguments)
#define auto_STATIC_METHOD_VOID(className, name, parameters, passedArguments) STATIC_METHOD_VOID(GetMethodAddress(className, name), className::name, parameters, passedArguments)

#define auto_STATIC_METHOD_(className, returnType, name) STATIC_METHOD_(GetMethodAddress(className, name), returnType, className::name)
#define auto_STATIC_METHOD_VOID_(className, name) STATIC_METHOD_VOID_(GetMethodAddress(className, name), className::name)



#if EXECUTABLE_TYPE == SPORE_STANDARD
	#if PATCHED_SPORE == 0
		#define GetAddress(addressStandard, addressSteam, addressSteamPatched) (baseAddress + addressStandard - 0x400000)
	#else
// I think the disk executable doesn't have a patched version
		#define GetAddress(addressStandard, addressSteam, addressSteamPatched) (baseAddress + addressStandard - 0x400000)
	#endif

#elif EXECUTABLE_TYPE == SPORE_STEAM
	#if PATCHED_SPORE == 0
		#define GetAddress(addressStandard, addressSteam, addressSteamPatched) (baseAddress + addressSteam - 0x400000)
	#else
		#define GetAddress(addressStandard, addressSteam, addressSteamPatched) (baseAddress + addressSteamPatched - 0x400000)
	#endif
#endif

#define ADDRESS_SPORE_NEW GetAddress(0xF47650, 0xF47240, 0xF47240)
#define ADDRESS_SPORE_DELETE GetAddress(0xF47630, 0xF47220, 0xF47220)

#define CALL_SPORE_NEW(size) ((void*(*)(size_t, const char*, int, unsigned, const char*, int)) ADDRESS_SPORE_NEW)(size, "ModAPI", 0, 0, __FILE__, __LINE__)
#define CALL_SPORE_DELETE(p) ((void(*)(void*)) ADDRESS_SPORE_DELETE)(p)


#define SP_NEW(type, size) (type*)SporeClass::operator new(sizeof(type) * size);
#define SP_DELETE(p) SporeClass::operator delete(p)


// To create managers
#define SINGLETON(className) struct className##Singleton {className* operator->() const{return className::Get();}}; extern className##Singleton