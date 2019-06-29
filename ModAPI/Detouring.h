#pragma once

#include <Spore\Internal.h>
#include <detours.h>

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

#define attach_detour(name, className, methodName) name::attach(GetMethodAddress(className, methodName))

#define DETOUR detour_object::detoured

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

template<typename T, typename U>
class static_detour_;

template<typename T, typename B, typename V, typename U>
class member_detour_;

///
/// The object used for detouring static functions. 
/// This is internal, for real usage check static_detour macro.
///
/// @tparam DetourClass The name of the class that is extending this object and is being used to hold the detour.
/// @tparam Result The return type of the function to detour, can be void.
/// @tparam Parameters The parameter types of the function to detour, can be empty.
template<typename DetourClass, typename Result, typename ... Parameters>
class static_detour_<DetourClass, Result(Parameters...)>
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

	static long attach(UINT function_address) {
		original_function = (detour_pointer)function_address;
		return DetourAttach(&(PVOID&)original_function, detoured_function);
	}
};

/// @tparam DetourClass The name of the class that is extending this object and is being used to hold the detour.
/// @tparam BaseClass The name of the class this object is simulating, must contain the method (or any of its superclasses must)
/// @tparam VirtualClass The name of the base class where the method was defined. For non-virtual methods, this must be the same as BaseClass.
/// @tparam Result The return type of the function to detour, can be void.
/// @tparam Parameters The parameter types of the function to detour, can be empty.
template<typename DetourClass, typename BaseClass, typename VirtualClass, typename Result, typename ... Arguments>
class member_detour_<DetourClass, BaseClass, VirtualClass, Result(Arguments...)> : public BaseClass
{
public:
	/// The type of function pointer used to keep track of the original function.
	typedef Result(__thiscall*detour_pointer)(VirtualClass*, Arguments...);

	typedef member_detour_<DetourClass, BaseClass, VirtualClass, Result(Arguments...)> detour_object;

	/// The pointer to the original function, you can call this with the same parameters as the function.
	static detour_pointer original_function;

	static Result __fastcall detoured_function(VirtualClass* object, int edx, Arguments... args) {
		return ((DetourClass*)object)->detoured(args...);
	}

	Result detoured(Arguments...);

	static long attach(UINT function_address) {
		original_function = (detour_pointer)function_address;
		return DetourAttach(&(PVOID&)original_function, detoured_function);
	}
};

template<class DetourClass, typename Result, typename ... Arguments>
typename static_detour_<DetourClass, Result(Arguments...)>::detour_pointer 
	static_detour_<DetourClass, Result(Arguments...)>::original_function;

template<class DetourClass, typename BaseClass, typename VirtualClass, typename Result, typename ... Arguments>
typename member_detour_<DetourClass, BaseClass, VirtualClass, Result(Arguments...)>::detour_pointer
member_detour_<DetourClass, BaseClass, VirtualClass, Result(Arguments...)>::original_function;

///
/// @param name The name of this detour object.
/// @param declaration The function declaration, with no names. For example, <code>void(int, float)</code>
#define static_detour(name, declaration) struct name : public static_detour_< name , declaration > 

///
/// @param name The name of this detour object.
/// @param baseClass The name of the class where the method is. From the detoured code you can access its members.
/// @param declaration The method declaration, with no names. For example, <code>void(int, float)</code>
#define member_detour(name, baseClass, declaration) struct name : public member_detour_< name , baseClass, baseClass, declaration > 

///
/// @param name The name of this detour object.
/// @param baseClass The name of the class where the method is.
/// @param virtualClass The name of the class where the method is declared. From the detoured code you can access its members.
/// @param declaration The method declaration, with no names. For example, <code>void(int, float)</code>
#define virtual_detour(name, baseClass, virtualClass, declaration) struct name : public member_detour_< name , baseClass, virtualClass, declaration > 