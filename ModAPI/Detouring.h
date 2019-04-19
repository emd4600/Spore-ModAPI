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

#define DETOUR detour::detoured

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

template<class T, typename Result, typename ... Arguments>
class static_detour_<T, Result(Arguments...)>
{
public:
	/// The type of function pointer used to keep track of both the original and the detoured function.
	typedef Result(*detour_pointer)(Arguments...);

	typedef static_detour_<T, Result(Arguments...)> detour;

	/// The pointer to the original function, you can call this with the same parameters as the function.
	static detour_pointer original_function;

	static Result detoured_function(Arguments... args) {
		int fake = 0;
		//return (*((T*)&fake))(args...);
		return ((T*)&fake)->detoured(args...);
	}
	
	Result detoured(Arguments...);

	static long attach(UINT function_address) {
		original_function = (detour_pointer)function_address;
		return DetourAttach(&(PVOID&)original_function, detoured_function);
	}
};

template<class T, typename Result, typename ... Arguments>
//typename static_detour_<T, D>::detour_pointer static_detour_<T, D>::original_function;
typename static_detour_<T, Result(Arguments...)>::detour_pointer static_detour_<T, Result(Arguments...)>::original_function;

#define static_detour(name, declaration) struct name : public static_detour_< name , declaration > 