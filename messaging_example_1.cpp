// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

class ColorListener
	: public App::DefaultMessageListener
{
public:
	bool HandleMessage(uint32_t messageID, void* message) {
		if (messageID == Editors::ColorChangedMessage::ID) {
			auto data = (Editors::ColorChangedMessage*) message;
			Color color = data->GetColor();
			App::ConsolePrintF("Player just selected color (%d, %d, %d)", color.r, color.g, color.b);
		}
		return false;
	}
};

void Initialize()
{
	MessageManager.AddListener(new ColorListener(), Editors::ColorChangedMessage::ID);
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

