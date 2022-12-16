#pragma once

#include <Spore\Anim\anim_csd.h>
#include <Spore\Graphics\Model.h>
#include <EASTL\intrusive_ptr.h>
#include <EASTL\map.h>

namespace Anim
{
	class AnimatedCreature;

	struct anim_cid;

	// check address 9C7565
	struct anim_cid_unk
	{
		struct model_unk
		{
			/* 00h */	int field_0;
			/* 04h */	int field_4;
			/* 08h */	int field_8;
			/* 0Ch */	ModelPtr pModel;
			/* 10h */	int field_10;
		};
		ASSERT_SIZE(model_unk, 0x14);

		/* 00h */	char padding_0[0x28];
		/* 28h */	eastl::vector<model_unk> models;
	};

	struct anim_block
	{
		/* 00h */	CreatureBlock* pBlock;
		/* 04h */	anim_cid* p_cid;
		/* 08h */	anim_block* pParent;
		/* 0Ch */	anim_block* field_C;
		/* 10h */	Vector3 bboxCenter;
		/* 1Ch */	Quaternion orientation;
		/* 2Ch */	Vector3 field_2C;
		/* 38h */	bool field_38;
		/* 3Ch */	Vector3 field_3C;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	bool field_54;
		/* 55h */	bool field_55;
		/* 58h */	float field_58[18];
		/* A0h */	int field_A0;
		/* A4h */	char padding_A4[0x144 - 0xA4];
		/* 144h */	int field_144;
		/* 148h */	Quaternion field_148;
		/* 158h */	Vector3 field_158;
		/* 164h */	char padding_164[0x2A0 - 0x164];
		/* 2A0h */	bool field_2A0;
		/* 2A4h */	char padding_2A4[0x2BC - 0x2A4];
	};
	ASSERT_SIZE(anim_block, 0x2BC);

	struct anim_cid
	{
		/* 00h */	eastl::intrusive_ptr<anim_csd> csd;
		/* 04h */	eastl::intrusive_ptr<AnimatedCreature> pCreature;
		/* 08h */	char padding_8[0xC];
		/* 14h */	int refCount;
		/* 18h */	char padding_18[0x3c - 0x18];
		/* 3Ch */	Quaternion field_3C;
		/* 4Ch */	char padding_4C[0x2C0 - 0x4C];
		// 3Ch is a Quaternion
		// Contains the models?
		/* 2C0h */	anim_cid_unk* field_2C0;
		/* 2C4h */	char padding_2C4[0x2E4 - 0x2C4];
		/* 2E4h */	eastl::vector<anim_block> blocks;
		/* 2F8h */	char padding_2F8[0x1930 - 0x2F8];
	};
	ASSERT_SIZE(anim_cid, 0x1930);
}