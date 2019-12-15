// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <Spore\ModAPI.h>
#include "GmdlExportCheat.h"

// The only thing we need to do in dllmain.cpp is register our cheat

void Initialize()
{
	GmdlExportCheat::AddCheat();
}

void Dispose()
{
}

void AttachDetours()
{
}

// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

