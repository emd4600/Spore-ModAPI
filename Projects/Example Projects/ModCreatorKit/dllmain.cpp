// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "Debugging.h"
#include "DetouredSwarmManager.h"
#include "EffectEditorMode.h"
#include "EffectEditorCheat.h"
#include "Cheats.h"
#include "ThumbnailCaptureScript.h"
#include "AnimLogCheat.h"
#include "UILogCheat.h"
#include "AnimEditorMode.h"

#include <Spore\ModAPI.h>

#include <Spore\Simulator\SubSystem\CommManager.h>

class Cheat : public ArgScript::ICommand
{
public:
	void ParseLine(const ArgScript::Line& line) override
	{
		/*CommManager.ShowCommEvent(CommManager.CreateCommEvent(
			Simulator::GetPlayerEmpireID(), Simulator::GetActivePlanetRecord()->GetID(), 
			id("mission_destroy_turrets"), id("mission_clues")
		));*/

		bool b = CALL(Address(0xAE8EA0), bool, Args(Simulator::cCommManager*), Args(Simulator::cCommManager::Get()));
		App::ConsolePrintF("%d", b);

		App::ConsolePrintF("Star Type: %d", Simulator::GetActiveStarRecord()->GetType());

		/*CALL(Address(0xAE9E20), void, Args(Simulator::cCommManager*), Args(Simulator::cCommManager::Get()));

		//CALL(Address(0xAECC30), void, Args(Simulator::cCommManager*, uint32_t, Simulator::PlanetID),
		//	Args(Simulator::cCommManager::Get(), Simulator::GetPlayerEmpireID(), Simulator::GetActivePlanetRecord()->GetID()));

		b = CALL(Address(0xAE8EA0), bool, Args(Simulator::cCommManager*), Args(Simulator::cCommManager::Get()));
		App::ConsolePrintF("%d", b);*/

		/*using namespace Simulator;
		if (auto args = line.GetArguments(1)) {
			StarRequestFilter filter;
			filter.starTypes = 0;
			filter.starTypes |= 1 << mpFormatParser->ParseInt(args[0]);

			auto star = CALL(Address(0xBAFD80), cStarRecord*, Args(cStarManager*, const Vector3&, const StarRequestFilter&),
				Args(cStarManager::Get(), SimulatorPlayerUFO.GetUFO()->GetPosition(), filter));

			if (star) {
				SpaceTeleportTo(star);
			}
		}*/

		//void* p = STATIC_CALL(Address(0x67CC10), void*, Args(), Args());
		//CALL(Address(0x67C980), void, Args(void*, uint32_t), Args(p, 0x9A16D07E));

		//using namespace Simulator;
		//auto ev = CommManager.CreateSpaceCommEvent(GetPlayerEmpireID(), GetPlayerEmpire()->mHomePlanet, 0xC8FBF7D7, id("greetings"));
		//CommManager.ShowCommEvent(ev);

		//MessageManager.PostMSG(0x6527EAF, nullptr);

		/*uint32_t eventID = UIEventLog.ShowEvent(id("SpiceFull"), GroupIDs::SpacePopups);

		CALL(Address(0xDD6120), void, Args(Simulator::cUIEventLog*, uint32_t, const char16_t*),
			Args(Simulator::cUIEventLog::Get(), eventID, u"This is my custom text"));

		//CALL(Address(0xDD6040), void, Args(Simulator::cUIEventLog*, uint32_t, bool),
		//	Args(Simulator::cUIEventLog::Get(), eventID, true));

		CALL(Address(0xDD7F70), void, Args(Simulator::cUIEventLog*, bool), Args(Simulator::cUIEventLog::Get(), false));*/

		LocaleManager.SetLanguage(u"ru-ru");
	}
};

void Initialize()
{
	Debugging::Initialize();
	EffectEditorCheat::AddCheat();
	EffectEditorMode::AddGameMode();
	ThumbnailCaptureScript::AddCheat();
	AddCheats();
	GameModeManager.AddGameMode(new AnimEditorMode(), AnimEditorMode::MODE_ID, "AnimEditorMode");

	CheatManager.AddCheat("spacetest", new Cheat());
}

void Dispose()
{
	Debugging::Dispose();
}

void AttachDetours()
{
	Debugging::AttachDetour();
	SwarmManager_detour::attach(GetAddress(Swarm::cSwarmManager, GetDirectoryAndEffectIndex));
	AnimLogCheat::AttachDetour();
	UILogCheat::AttachDetour();
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

