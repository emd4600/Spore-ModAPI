#pragma once

#include <Spore\Anim\CreatureBlock.h>
#include <EASTL\vector.h>

namespace Anim
{
	struct anim_csd
	{
		/* 00h */	char16_t name[0x100];
		/* 200h */	char padding_200[8];
		/* 208h */	char fileName[0x100];
		/* 308h */	char padding_308[8];
		/* 310h */	int field_310;
		/* 314h */	int field_314;
		/* 318h */	int field_318;
		/* 31Ch */	int field_31C;
		/* 320h */	int field_320;
		/* 324h */	Vector3 field_324;
		/* 330h */	Vector3 field_330;
		/* 33Ch */	Vector3 field_33C;
		/* 348h */	int refCount;
		/* 34Ch */	bool field_34C;  // true
		/* 350h */	int field_350;
		/* 354h */	int field_354;
		/* 358h */	Vector3 field_358;
		/* 364h */	Vector3 field_364;
		/* 370h */	int field_370;  // not initialized
		/* 374h */	float field_374;
		/* 378h */	int cal3DRootBlockIndex;  // -1
		/* 37Ch */	int field_37C;  // not initialized
		/* 380h */	bool field_380;
		/* 384h */	eastl::vector<CreatureBlock> blocks;
		/* 398h */	eastl::vector<int> field_398;
		/* 3ACh */	int field_3AC;  // -1
		/* 3B0h */	int field_3B0;  // -1
		/* 3B4h */	eastl::vector<int> field_3B4;
		/* 3C8h */	int field_3C8;  // not initialized
		/* 3CCh */	eastl::vector<int> field_3CC;
		/* 3E0h */	int field_3E0;
		/* 3E4h */	int field_3E4;  // not initialized
		/* 3E8h */	int field_3E8;  // not initialized
		/* 3ECh */	int field_3EC;  // not initialized
		/* 3F0h */	int isPlant;
		/* 3F4h */	bool field_3F4;  // not initialized
		/* 3F5h */	bool field_3F5;
		/* 3F8h */	eastl::vector<int> field_3F8;
		/* 40Ch */	int field_40C;  // not initialized
	};
	ASSERT_SIZE(anim_csd, 0x410);
}