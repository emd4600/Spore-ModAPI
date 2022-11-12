#include "stdafx.h"

class GasTestCheat 
	: public ArgScript::ICommand
{
public:
	void ParseLine(const ArgScript::Line& line) override {
		for (int i = 0; i < 12; ++i) {
			IVisualEffectPtr effect;
			// 0x03F54A4F is SG_gasGiant_01~
			if (EffectsManager.CreateVisualEffect(0x03F54A4F + i, 0, effect)) {
				// X and Y can go negative, but we will only use positive Z so it doesn't go below the ground
				effect->SetSourceTransform(Transform()
					.SetOffset(Math::randf(-7, 7), Math::randf(-7, 7), Math::randf(0, 7))
					.SetScale(0.08f));
				effect->Start();
			}
		}
	}
};

void Initialize()
{
	CheatManager.AddCheat("gasTest", new GasTestCheat());
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

