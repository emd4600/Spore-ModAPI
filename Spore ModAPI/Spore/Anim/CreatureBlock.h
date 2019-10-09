#pragma once

#include <Spore\MathUtils.h>

namespace Anim
{
	struct CreatureBlock
	{
		enum {
			kCapFlagRoot = 1,
			kCapFlagLimb = 2,
			kCapFlagFoot = 4,
			kCapFlagSpine = 8,
			kCapFlagPseudoFoot = 0x10,
			kCapFlagMouth = 0x20,
			kCapFlagGrasper = 0x40,
			kCapFlagNoStretch = 0x80,
		};
		
		/* 00h */	char name[256];
		/* 100h */	int field_100;  // ?

		/* 0Ch */	float mass;
		/* 10h */	Math::Vector3 position;
		/* 1Ch */	Math::Vector3 jointPosition;
		/* 28h */	Math::BoundingBox bbox;
		
		/* 104h */	uint32_t instanceID;
		/* 108h */	uint32_t groupID;
		/* 10Ch */	Math::Vector3 position;
		/* 118h */	Math::Vector4 orientation;
		/* 128h */	float field_128;
		/* 12Ch */	float field_12C;
		/* 130h */	float field_130;
		/* 134h */	float field_134;  // 1.0
		/* 138h */	Math::Vector3 bboxHalf;
		
		// It's actually a struct on its own
		/* 150h */	int capFlags;
		/* 154h */	int capLvlFlags;  // only added for a cap if level != 0
		/* 158h */	PCTPCapability* capabilities[32];
		/* 1D8h */	int8_t capLevels[32];
		
		/* 1F8h	*/	int field_1F8;  // ?
		/* 1FCh */	int parentIndex;  // -1 if no parent
		/* 200h */	int symmetricIndex;
		
		/* 220h */	char cal3DBoneName[256];
		/* 320h */	int field_320;  // ?
		/* 324h */	Math::Vector3 cal3DOrigin;
		/* 330h */	Math::Vector3 effectsOrigin;
		/* 33Ch */	int submeshIndex;
		/* 340h */	bool isLeftHanded;
		
		/* 378h */	float scale;
		
		/* 380h */	// related with deforms
		
		/* 428h */	uint32_t soundIDMouth;
		
		/* 434h */	uint32_t soundIDFoot;
	};
}
