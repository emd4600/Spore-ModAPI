#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\App\IGameMode.h>
#include <Spore\Input.h>
#include <Spore\Clock.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cSimulatorSpaceGame.h>

namespace App
{
	class GameSpace
		/* 00h */	: public App::IGameMode
		/* 04h */	, public App::IMessageListener
		/* 08h */	, public Simulator::cStrategy
	{
	public:
		/* 24h */	bool field_24;
		/* 25h */	char _padding_25[0x68 - 0x25];
		/* 68h */	eastl::vector<int> field_68;
		/* 7Ch */	int field_7C;
		/* 80h */	int field_80;
		/* 84h */	int field_84;
		/* 88h */	bool field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	int field_98;
		/* 9Ch */	int field_9C;
		/* A0h */	int field_A0;
		/* A8h */	Simulator::cGonzagoTimer mSpaceGameTime;
		/* C8h */	GameInput mInput;
		/* 110h */	Clock field_110;
		/* 128h */	int field_128;  // not initialized
		/* 12Ch */	int field_12C;  // not initialized
		/* 130h */	bool field_130;  // not initialized
		/* 131h */	bool field_131;
		/* 134h */	int field_134;
		/* 138h */	int field_138;  // not initialized
		/* 13Ch */	int field_13C;  // not initialized
		/* 140h */	int field_140;
		/* 144h */	eastl::vector<int> field_144;
		/* 158h */	bool field_158;
		/* 15Ch */	cSimulatorSpaceGamePtr mpSimulator;
		/* 160h */	int field_160;
		/* 164h */	int field_164;
		/* 168h */	bool field_168;  // not initialized
		/* 169h */	bool field_169;
		/* 16Ah */	bool field_16A;  // true
		/* 16Ch */	int field_16C;
		/* 170h */	eastl::list<int> field_170;
		/* 17Ch */	eastl::list<int> field_17C;
		/* 188h */	ObjectPtr mEmpireGrowthSim;
		/* 18Ch */	bool field_18C;
		/* 18Dh */	bool field_18D;
		/* 18Eh */	bool field_18E;
		/* 18Fh */	bool field_18F;
		/* 190h */	bool field_190;
		/* 191h */	bool field_191;
		/* 192h */	bool field_192;
		/* 194h */	int field_194;
	};
	ASSERT_SIZE(GameSpace, 0x198);
}