#pragma once

#include <Spore\Simulator\Cell\cCellSerialiazibleData.h>
#include <Spore\Simulator\Cell\cCellResource.h>
#include <Spore\Simulator\Cell\cCellObjectData.h>
#include <Spore\Simulator\Cell\cCellQueryLinkedPool.h>
#include <Spore\Simulator\cObjectPool.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\map.h>

#define CellGame (*Simulator::Cell::cCellGame::Get())

namespace Simulator
{
	namespace Cell
	{
		enum class ScaleDifference
		{
			/// Cell is 2 or more levels smaller than player cell
			MuchSmaller = 0,
			/// Cell is 1 level smaller than player cell
			Smaller = 1,
			/// Cell is same level as player cell
			Equal = 2,
			/// Cell is 1 level larger than player cell
			Larger = 3,
			/// Cell is 2 or more levels larger than player cell
			MuchLarger = 4
		};

		////TODO
		//struct cCellLevelObject
		//	: public cObjectPoolClass
		//{
		//	char todo[0x300];
		//};
		//ASSERT_SIZE(cCellLevelObject, 0x304);

		class cCellGame
		{
		public:
			static cCellGame* Get();

			static void Initialize();

		public:
			/* 00h */	cAdvectResourcePtr mpCurrentAdvectionMap;
			/* 04h */	float field_4;  // related with advection
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	float field_10;
			/* 14h */	float field_14;
			/* 18h */	float field_18;
			/// 4096 objects of cCellObjectData
			/* 1Ch */	cObjectPool<cCellObjectData> mCells;
			/* 38h */	cObjectPool_ field_38;
			/* 54h */	cObjectPool_ field_54;
			/* 70h */	eastl::map<int, int> field_70;
			/* 8Ch */	cObjectPool_ field_8C;
			/* A8h */	cObjectPool_ field_A8;
			/* C4h */	cObjectPool_ field_C4;
			/* E0h */	eastl::fixed_vector<int, 4096> field_E0;
			/* 40F8h */	void* field_40F8;
			/* 40FCh */	cCellQueryLinkedPool* mpCellQuery;
			/* 4100h */	cCellQueryLinkedPool* mpCellQueryBackground;
			/* 4104h */	char padding_4104[0x4114 - 0x4104];
			/* 4114h */	cCellDataReference<cCellWorldResource>* mpCurrentWorld;
			/* 4118h */	cCellDataReference<cCellWorldResource>* mpCurrentWorldBackground;
			/// Index to the avatar cell in mCells
			/* 411Ch */	cObjectPoolIndex mAvatarCellIndex;
			/* 4120h */	int field_4120;
			/* 4124h */	int field_4124;
			/* 4128h */	eastl::fixed_vector<eastl::pair<int, int>, 512> field_4128;
			/* 5140h */	char padding_5140[0x514C - 0x5140];
			/* 514Ch */	float field_514C;  // global sizing factor? check E72320
			/* 5150h */	char padding_5150[0x5164 - 0x5150];
			/* 5164h */	ObjectPtr field_5164;
			/* 5168h */	int field_5168;
			/// In mCells
			/* 516Ch */	cObjectPoolIndex field_516C;
			/* 5170h */	eastl::map<int, int> field_5170;
			/* 518Ch */	int field_518C;
			/* 5190h */	cCellSerializableDataPtr mpSerializableData;
			/* 5194h */	char field_5194[0x51CC - 0x5194];
			/* 51CCh */	float mShowCallMateButtonCountdown;
			/* 51D0h */	float field_51D0;
			/* 51D4h */	int field_51D4;
			/* 51D8h */	int field_51D8;
			/* 51DCh */	int field_51DC;
			/* 51E0h */	int field_51E0;
		};
		ASSERT_SIZE(cCellGame, 0x51E4);	

		namespace Addresses(cCellGame)
		{
			DeclareAddress(_ptr);  // 0x16B7E84 0x16B3C04
			DeclareAddress(Initialize);  // 0xE81130 0xE80BA0
			DeclareAddress(CreateCellObject);  // 0xE74F60 0xE74A20
			DeclareAddress(MovePlayerToMousePosition);  // 0xE5BD90 0xE5B790
			DeclareAddress(GetScaleDifferenceWithPlayer);  // 0xE57940 0xE57340
			DeclareAddress(ShouldNotAttack);  // 0xE57A60 0xE57460
		}
	}
}