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

		struct PlantSlot
		{
			/* 00h */	ResourceKey plantKey;
			/* 0Ch */	uint32_t mModelIDLOD0;
			/* 10h */	uint32_t mModelIDLOD1;
			/* 14h */	uint32_t mModelIDLOD2;
			/* 18h */	uint32_t mModelIDLOD3;
		};

	public:
		/* 20h */	int field_20;// bool?
		/* 24h */	float field_24;
		/* 28h */	int field_28;
		/* 2Ch */	int field_2C;
		/* 30h */	int mInitializationType;
		/* 34h */	bool IsPlanetExisted;
		/* 38h */	int field_38;//Property? Ptr of smh
		/* 3Ch */	ObjectPtr field_3C;
		/* 40h */	ObjectPtr field_40;
		/* 44h */	PlantSlot Plants[9];
		/* 140h */	int field_140;
		/* 144h */	int field_144;
		/* 148h */	int field_148;
		/* 14Ch */	int field_14C;
		/* 150h */	int field_150;
		/* 154h */	int field_154;
		/* 158h */	uint32_t GameModeID;
		/* 15Ch */	eastl::vector<int> field_15C;
		/* 170h */	int field_170;
		/* 174h */	int field_174;
		/* 178h */	int field_178;
		/* 17Ch */	int field_17C; //Simulator::cPlanetRecord* ? or cPlanetRecordPtr
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
		/* 1C8h */	int field_1C8; //?
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