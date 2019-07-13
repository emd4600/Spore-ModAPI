#include <ModAPI\MainUtilities.h>
#include <Spore\Internal.h>
#include <Spore\ArgScript\FormatParser.h>
#include <Windows.h>

using namespace ModAPI;

BaseAddressDeclare;

ArgScript::PrintF_ptr ArgScript::PrintF;

namespace ModAPI
{
	HINSTANCE ModAPIUtils::hModAPIDLL;
	FARPROC ModAPIUtils::pAddInitFunction;

	void ModAPIUtils::InitModAPI()
	{
		baseAddress = (DWORD)GetModuleHandleA(NULL);

		ArgScript::PrintF = (ArgScript::PrintF_ptr) Address(SelectAddress(0x8418C0, 0x841050, 0x8410D0));

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
	}


	void ModAPIUtils::AddInitFunction(InitFunction function)
	{
		((void(*)(InitFunction)) pAddInitFunction)(function);
	}
}