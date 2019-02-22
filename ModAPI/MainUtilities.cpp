#include "MainUtilities.h"
#include "..\Spore\Internal.h"
#include "..\Spore\ArgScript\FormatParser.h"
#include <Windows.h>

using namespace ModAPI;

DWORD baseAddress = 0;

ModAPIUtils* ModAPIUtils::Utils;

ArgScript::PrintF_ptr ArgScript::PrintF;

ModAPIUtils::ModAPIUtils()
{
#if EXECUTABLE_TYPE == SPORE_STEAM
#if PATCHED_SPORE == 0
	hModAPIDLL = GetModuleHandleA("SporeModAPI-steam.dll");
#else
	hModAPIDLL = GetModuleHandleA("SporeModAPI-steam_patched.dll");
#endif
#else
	hModAPIDLL = GetModuleHandleA("SporeModAPI-disk.dll");
#endif

	pAddInitFunction = GetProcAddress(hModAPIDLL, "AddInitFunction");
	pAddInitUIEventListener = GetProcAddress(hModAPIDLL, "AddUIEventListener");
	pGetShaderConstantsManager = GetProcAddress(hModAPIDLL, "GetShaderConstantsManager");

}

void ModAPIUtils::InitModAPI()
{
	// baseAddress = (DWORD)GetModuleHandleA("SporeApp.exe");
	baseAddress = (DWORD)GetModuleHandleA(NULL);

	ArgScript::PrintF = (ArgScript::PrintF_ptr) GetAddress(0x8418C0, 0x841050, 0x8410D0);

	Utils = new ModAPIUtils();
}


void ModAPIUtils::AddInitFunction(InitFunction function)
{
	((void(*)(InitFunction)) Utils->pAddInitFunction)(function);
}

void ModAPIUtils::AddUIEventListener(UIEventListener* listener, UIEventContext context)
{
	((void(*)(UIEventListener*, UIEventContext)) Utils->pAddInitUIEventListener)(listener, context);
}

ShaderConstantsManager* ModAPIUtils::GetShaderConstantsManager()
{
	return ((ShaderConstantsManager*(*)()) Utils->pGetShaderConstantsManager)();
}