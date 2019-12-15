// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "ColorPickerUIDetour.h"
#include "ColorWheelSwatchUI.h"

void Initialize()
{
}

void Dispose()
{
}

void AttachDetours()
{
	ColorPickerUI_Load_detour::attach(GetAddress(ColorPickerUI, Load));
	ColorSwatchUI_Update_detour::attach(GetAddress(ColorSwatchUI, Update));
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

