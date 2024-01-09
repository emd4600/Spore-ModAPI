#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\SubSystem\StarManager.h>
#include <EASTL\string.h>

#define GamePersistenceManager (*Simulator::cGamePersistenceManager::Get())

namespace Simulator
{
	struct GameLoadParameters
	{
		/// This will be appended with `.spo` to create the game file name.
		/* 00h */	eastl::string16 mGameName;
		/* 10h */	eastl::string16 mStarName;
		/* 20h */	eastl::string16 field_20;
		/* 30h */	char padding_30[0x48 - 0x30];
		/* 48h */	cSpeciesProfile* mpCreatureSpecies;
		/* 4Ch */	ResourceKey mCreatureKey;
		/* 58h */	ResourceKey field_58;
		/* 5Ch */	char padding_64[0x7C - 0x64];
		/* 7Ch */	StarID mStarID {0};
		/* 80h */	char padding_80[0xA0 - 0x80];
		/* A0h */	Difficulty mDifficulty;
		/// Game mode to load
		/* A4h */	TechLevel mGameMode;
		/* A8h */	char padding_A8[0xB0 - 0xA8];
		/* B0h */	int field_B0;
	};
	ASSERT_SIZE(GameLoadParameters, 0xB4);  // I don't know if this is the real size

	class cGamePersistenceManager
		: public App::IMessageListener
		, public cStrategy
	{
	public:
		static cGamePersistenceManager* Get();

		/// Call GameNounManager.EnsurePlayer() to avoid game crashes.
		/* 10h */	virtual bool LoadGame(const GameLoadParameters& parameters);
		//TODO more methods

		/* 14h */	virtual void func14h(int);
		/* 18h */	virtual void func18h(int, int);
		/* 1Ch */	virtual bool func1Ch();
		/* 20h */	virtual bool func1Ch(uint32_t);

	public:
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
		/* 34h */	eastl::string16 field_34;
		/* 44h */	bool field_44;
		/* 45h */	bool field_45;
		/* 46h */	bool field_46;
		/* 47h */	bool field_47;
		/* 48h */	int field_48;
	};
	ASSERT_SIZE(cGamePersistenceManager, 0x4C);

	namespace Addresses(cGamePersistenceManager) {
		DeclareAddress(Get);  // 0xB3D2A0 0xB3D440
	}
}