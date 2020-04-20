#ifdef MODAPI_DLL_EXPORT
// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <string>
#include <Spore\Internal.h>
#include <Spore\ModAPI.h>
#include "Application.h"
#include "TextureOverride.h"

uintptr_t baseAddress;
ArgScript::PrintF_ptr ArgScript::PrintF;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		baseAddress = (uintptr_t)GetModuleHandleA(NULL);

		ArgScript::PrintF = (ArgScript::PrintF_ptr) Address(SelectAddress(0x8418C0, 0x841050, 0x8410D0));

		PrepareDetours(hModule);
		ModAPI::AttachDetour();
		TextureOverride::AttachDetour();
		CommitDetours();
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		PrepareDetours(hModule);
		ModAPI::DetachDetour();
		CommitDetours();
		break;
	}
	return TRUE;
}

#endif
