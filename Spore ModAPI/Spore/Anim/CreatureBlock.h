#pragma once

#include <Spore\MathUtils.h>

namespace Anim
{
	using namespace Math;

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

		struct Capabilities
		{
			/* 00h */	int capFlags;
			/* 04h */	int capLvlFlags;  // only added for a cap if level != 0
			/* 08h */	int* capabilities[32];  // PCTPCapability*
			/* 88h */	int8_t capLevels[32];
		};
		ASSERT_SIZE(Capabilities, 0xA8);

		struct Deforms
		{
			struct Deform {
				uint32_t id;
				int field_4;
				float field_8;
				int field_C;
				float field_10;
			};
			int count;
			Deform deforms[8];
		};

		/* 00h */	char name[260];
		/* 104h */	uint32_t instanceID;
		/* 108h */	uint32_t groupID;
		/* 10Ch */	Vector3 bboxCenter;
		/* 118h */	Quaternion orientation;
		/* 128h */	Quaternion field_128;
		/* 138h */	Vector3 bboxDirection;
		/* 144h */	Vector3 position;
		/* 150h */	Capabilities capabilities;
		/// The index within the block vector
		/* 1F8h */	int blockIndex;  // -1
		/// The index of the parent of this block within the block vector, -1 if no parent
		/* 1FCh */	int parentIndex;  // -1
		/* 200h */	int symmetricIndex;  // -1
		/* 204h */	int field_204;  // -1
		/* 208h */	int field_208;  // count of elements in field_218
		/* 20Ch */	int field_20C;
		/* 210h */	int field_210;
		/* 214h */	CreatureBlock* pParent;
		/* 218h */	CreatureBlock* field_218;
		/// A number that identifies this block when referenced from other blocks
		/* 21Ch */	int blockID;  // -1
		/* 220h */	char cal3DBoneName[260];
		/* 324h */	Vector3 cal3DOrigin;
		/* 330h */	Vector3 effectsOrigin;
		/* 33Ch */	int submeshIndex;  // -1
		/* 340h */	bool isLeftHanded;
		/* 344h */	float field_344[11];
		/* 370h */	bool field_370;
		/* 371h */	bool field_371;
		/* 374h */	float field_374;
		/* 378h */	float scale;
		/* 37Ch */	float field_37C;
		/* 380h */	Deforms deforms;
		/* 424h */	uint32_t soundIDFoot;  // -1
		/* 428h */	uint32_t soundIDMouth;  // -1
		/* 42Ch */	bool field_42C;
		/* 430h */	int field_430;  // -1
		/* 434h */	Vector3 field_434;
		/* 440h */	int field_440;  // -1
		/* 444h */	int field_444;  // -1
		/* 448h */	Vector3 field_448;
		/* 454h */	float field_454;
		/* 458h */	Vector3 field_458;
		/* 464h */	int field_464;  // not initialized
	};
	ASSERT_SIZE(CreatureBlock, 0x468);

	//struct CreatureBlock
	//{
	//	enum {
	//		kCapFlagRoot = 1,
	//		kCapFlagLimb = 2,
	//		kCapFlagFoot = 4,
	//		kCapFlagSpine = 8,
	//		kCapFlagPseudoFoot = 0x10,
	//		kCapFlagMouth = 0x20,
	//		kCapFlagGrasper = 0x40,
	//		kCapFlagNoStretch = 0x80,
	//	};
	//	
	//	/* 00h */	char name[256];
	//	/* 100h */	int field_100;  // ?

	//	/* 0Ch */	float mass;
	//	/* 10h */	Math::Vector3 position;
	//	/* 1Ch */	Math::Vector3 jointPosition;
	//	/* 28h */	Math::BoundingBox bbox;
	//	
	//	/* 104h */	uint32_t instanceID;
	//	/* 108h */	uint32_t groupID;
	//	/* 10Ch */	Math::Vector3 position;
	//	/* 118h */	Math::Vector4 orientation;
	//	/* 128h */	float field_128;
	//	/* 12Ch */	float field_12C;
	//	/* 130h */	float field_130;
	//	/* 134h */	float field_134;  // 1.0
	//	/* 138h */	Math::Vector3 bboxHalf;
	//	
	//	// It's actually a struct on its own
	//	/* 150h */	int capFlags;
	//	/* 154h */	int capLvlFlags;  // only added for a cap if level != 0
	//	/* 158h */	PCTPCapability* capabilities[32];
	//	/* 1D8h */	int8_t capLevels[32];
	//	
	//	/* 1F8h	*/	int field_1F8;  // ?
	//	/* 1FCh */	int parentIndex;  // -1 if no parent
	//	/* 200h */	int symmetricIndex;
	//	
	//	/* 220h */	char cal3DBoneName[256];
	//	/* 320h */	int field_320;  // ?
	//	/* 324h */	Math::Vector3 cal3DOrigin;
	//	/* 330h */	Math::Vector3 effectsOrigin;
	//	/* 33Ch */	int submeshIndex;
	//	/* 340h */	bool isLeftHanded;
	//	
	//	/* 378h */	float scale;
	//	
	//	/* 380h */	// related with deforms
	//	
	//	/* 428h */	uint32_t soundIDMouth;
	//	
	//	/* 434h */	uint32_t soundIDFoot;
	//};
}

