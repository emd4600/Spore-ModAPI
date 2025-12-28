#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cCommEvent.h>
#include <Spore\Simulator\ConversationResource.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IWindowManager.h>
#include <Spore\UTFWin\IButton.h>

#define CommManager (*Simulator::cCommManager::Get())

namespace Simulator
{
	// Corresponds to window controlIDs in CommScreen-3.spui
	enum CommWindowIDs {
		// Panels containing windows
		kWindowPanelViewport = 0x06429C80,
		kWindowPanelLower = 0x05E4E5F0,

		// Windows inside panels
		kWindowBackground = 0x05EDFF88,
		//kCnvWindowViewport = 0x06243260, // Needs verification
		kWindowTrading = 0x05E62A48,
		kWindowText = 0x018072CB,

	};

	// Corresponds to button controlIDs in CommScreen-3.spui
	enum CommButtonIDs {

		// Space only Buttons
		kBtnTrade = 0x057DF5CA,
		kBtnRepair = 0x057DF5C8,
		kBtnRecharge = 0x057DF5C9,

		kBtnMissions = 0x05E51D28,
		kBtnDiplomacy = 0x05E51D30,

		kBtnMenu = 0x05DFF098, // Satellite icon
		kBtnExit = 0x05E4F778, // Goodbye

		kBtnAccept = 0x05E4F788, // Red in spui
		kBtnDecline = 0x05E4F770,

		kBtnTradeBuy = 0x04C1510A,
		kBtnTradeSell = 0x04C1510C,
	};


	class cCommManager
		: public cStrategy
	{
	public:		
		cCommEvent* CreateCivCommEvent(cCivilization* pSourceCivilization, cCity* pTargetCity, PlanetID planetKey, 
			uint32_t fileID, uint32_t dialogID, int priority = 0);

		cCommEvent* CreateSpaceCommEvent(uint32_t sourceEmpireID, PlanetID planetKey, uint32_t fileID,
			uint32_t dialogID, cMission* pMission = nullptr, int priority = 0, unsigned int duration = 0);

		void ShowCommEvent(cCommEvent* pEvent);

		bool IsCommScreenActive() const;

		void HandleCivCommAction(const CnvAction& action, cCivilization* pSourceCiv, cCity* pSourceCity, cCity* pTargetCity);

		void HandleSpaceCommAction(const CnvAction& action, uint32_t sourceEmpireID, PlanetID planetKey, cMission* pMission);


		UTFWin::IWindow* GetCommBackgroundWindow();
		UTFWin::IWindow* GetCommWindow(uint32_t windowid);
		UTFWin::IButton* GetCommButton(uint32_t buttonid);

	public:
		/* 20h */	cCommEventPtr mCurrentCommEvent;
		/* 24h */	eastl::vector<cCommEventPtr> mListCommEvents;
		/* 38h */	int field_38;  // -1
		/* 3Ch */	ObjectPtr field_3C;
		/* 40h */	eastl::hash_map<uint32_t, eastl::vector<uint32_t>> mTransmissionCancelConditions;
		/* 60h */	bool field_60;
		/* 64h */	int field_64;

	public:
		static cCommManager* Get();
	};

	namespace Addresses(cCommManager)
	{
		DeclareAddress(Get);

		DeclareAddress(CreateCivCommEvent);
		DeclareAddress(CreateSpaceCommEvent);
		DeclareAddress(ShowCommEvent);
		DeclareAddress(HandleCivCommAction);
		DeclareAddress(HandleSpaceCommAction);
		DeclareAddress(IsCommScreenActive);
	}
}