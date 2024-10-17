#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <EASTL\vector.h>
#include <EASTL\map.h>

#define GamePlantManager (*Simulator::cGamePlantManager::Get())

namespace Simulator
{
	class cGamePlantManager
		/* 00h */	: public App::IMessageListener
		/* 04h */	, public Simulator::cStrategy
	{
	public:
		static cGamePlantManager* Get();

	public:
		/* 20h */	int field_20;
		/* 24h */	float field_24;
		/* 28h */	int field_28;
		/* 2Ch */	int field_2C;
		/* 30h */	int mInitializationType;
		/* 34h */	int field_34;
		/* 38h */	int field_38;
		/* 3Ch */	ObjectPtr field_3C;
		/* 40h */	ObjectPtr field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	int field_54;
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
		/* 70h */	int field_70;
		/* 74h */	int field_74;
		/* 78h */	int field_78;
		/* 7Ch */	int field_7C;
		/* 80h */	int field_80;
		/* 84h */	int field_84;
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	int field_98;
		/* 9Ch */	int field_9C;
		/* A0h */	int field_A0;
		/* A4h */	int field_A4;
		/* A8h */	int field_A8;
		/* ACh */	int field_AC;
		/* B0h */	int field_B0;
		/* B4h */	int field_B4;
		/* B8h */	int field_B8;
		/* BCh */	int field_BC;
		/* C0h */	int field_C0;
		/* C4h */	int field_C4;
		/* C8h */	int field_C8;
		/* CCh */	int field_CC;
		/* D0h */	int field_D0;
		/* D4h */	int field_D4;
		/* D8h */	int field_D8;
		/* DCh */	int field_DC;
		/* E0h */	int field_E0;
		/* E4h */	int field_E4;
		/* E8h */	int field_E8;
		/* ECh */	int field_EC;
		/* F0h */	int field_F0;
		/* F4h */	int field_F4;
		/* F8h */	int field_F8;
		/* FCh */	int field_FC;
		/* 100h */	int field_100;
		/* 104h */	int field_104;
		/* 108h */	int field_108;
		/* 10Ch */	int field_10C;
		/* 110h */	int field_110;
		/* 114h */	int field_114;
		/* 118h */	int field_118;
		/* 11Ch */	int field_11C;
		/* 120h */	int field_120;
		/* 124h */	int field_124;
		/* 128h */	int field_128;
		/* 12Ch */	int field_12C;
		/* 130h */	int field_130;
		/* 134h */	int field_134;
		/* 138h */	int field_138;
		/* 13Ch */	int field_13C;
		/* 140h */	int field_140;
		/* 144h */	int field_144;
		/* 148h */	int field_148;
		/* 14Ch */	int field_14C;
		/* 150h */	int field_150;
		/* 154h */	int field_154;
		/* 158h */	int field_158;
		/* 15Ch */	eastl::vector<int> field_15C;
		/* 170h */	int field_170;
		/* 174h */	int field_174;
		/* 178h */	int field_178;
		/* 17Ch */	int field_17C;
		/* 180h */	int field_180;
		/* 184h */	int field_184;
		/* 188h */	int field_188;
		/* 18Ch */	int field_18C;
		/* 190h */	eastl::map<int, int> field_190;
		/* 1ACh */	int field_1AC;
		/* 1B0h */	int field_1B0;
		/* 1B4h */	int field_1B4;
		/* 1B8h */	int field_1B8;
		/* 1BCh */	int field_1BC;
		/* 1C0h */	int field_1C0;
		/* 1C4h */	int field_1C4;
		/* 1C8h */	int field_1C8;
		/* 1CCh */	int field_1CC;
		/* 1D0h */	int field_1D0;
		/* 1D4h */	int field_1D4;
		/* 1D8h */	int field_1D8;
		/* 1DCh */	int field_1DC;
		/* 1E0h */	int field_1E0;
		/* 1E4h */	int field_1E4;
	};
	ASSERT_SIZE(cGamePlantManager, 0x1E8);

	namespace Addresses(cGamePlantManager) {
		DeclareAddress(Get);  // 0xB3D310 0xB3D4B0
	}
}