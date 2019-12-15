// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "Debugging.h"
#include "DetouredSwarmManager.h"
#include "EffectEditorMode.h"
#include "EffectEditorCheat.h"
#include "Cheats.h"
#include "ThumbnailCaptureScript.h"
#include "AnimLogCheat.h"

#include <Spore\ModAPI.h>

void Initialize()
{
	Debugging::Initialize();
	EffectEditorCheat::AddCheat();
	EffectEditorMode::AddGameMode();
	ThumbnailCaptureScript::AddCheat();
	AddCheats();
}

void Dispose()
{
	Debugging::Dispose();
}

void AttachDetours()
{
	Debugging::AttachDetour();
	SwarmManager_detour::attach(GetAddress(Swarm::cSwarmManager, GetDirectoryAndEffectIndex));
	ReadAnimation_detour::AttachDetour();
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

