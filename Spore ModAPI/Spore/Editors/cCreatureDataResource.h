#pragma once

#include <Spore\Resource\ResourceObject.h>
#include <Spore\Editors\cEditorResourceProperties.h>
#include <Spore\IO\IStream.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

namespace Editors
{
	class cCreatureDataResource
		: public Resource::ResourceObject
	{
	public:
		static const uint32_t TYPE = 0x3E1C247;

		static bool Read(IO::IStream* stream, cCreatureDataResource* dst);
		static bool Write(IO::IStream* stream, cCreatureDataResource* src);

	public:
		struct CapabilityTag
		{
			char chars[4];
		};

		enum class RigblockDataType : int8_t
		{
			NullBlock = 0,
			Unk1 = 1,
			Standard = 2,
			Unk3 = 3,
			PlantRoot = 4,
			Vertebra = 5
		};

		enum
		{
			kFlagNotUseSkin = 1,
			//TODO 4 hasBallConnector?
			kFlagIsBaked = 8,
			//TODO 0x10 is related with limb type
			kFlagIsFoot = 0x20,

			kFlagIsWeapon = 0x80,

			kFlagIsJiggable = 0x200,

			kFlagExtraJiggly = 0x800,
			kFlagIsAsymmetric = 0x1000,
		};

		struct RigblockData
		{
			/* 00h */	int16_t mIndex;
			/* 02h */	int16_t field_2;
			/* 04h */	int16_t mParentIndex;
			/* 06h */	int16_t mSymmetricIndex;
			/* 08h */	int16_t mFlags;
			/* 0Ah */	int8_t field_A;
			/* 0Bh */	RigblockDataType mType;
			/// Start index in capabilities vector
			/* 0Ch */	int16_t mCapabilityIndex;
			/// Start index in morphs vector
			/* 0Eh */	int16_t mMorphsIndex;
			/* 10h */	int8_t mNumCapabilities;
			/* 14h */	Math::BoundingBox mBoundingBox;
			/* 2Ch */	float mScale;
			/* 30h */	Math::Matrix3 mTotalOrientation;
			/* 54h */	Math::Vector3 mPosition;
			/* 60h */	Math::Vector3 mEffectOffset;
			/* 6Ch */	float mScaleRelative;
			/* 70h */	float mSocketConnectorDistance;  //TODO maybe bounding radius?
			/* 74h */	float mMuscleScale;
			/* 78h */	float mBaseMuscleScale;
			/* 7Ch */	float field_7C;
			/* 80h */	uint32_t mFootWeaponOrMouthType;
			/* 84h */	uint32_t mGroupID;
			/* 88h */	uint32_t mInstanceID;
		};
		ASSERT_SIZE(RigblockData, 0x8C);

		/* 14h */	int field_14;
		/* 18h */	cEditorResourceProperties mProperties;
		/* 98h */	eastl::vector<RigblockData> mRigblocks;
		/// PCTP identifiers grouped in 4 characters, like 'spin', 'wing',...
		/* ACh */	eastl::vector<CapabilityTag> mCapabilityIDs;
		/* C0h */	eastl::vector<int8_t> mCapabilityLevels;
		/* D4h */	eastl::vector<uint32_t> mAnimationIDs;
		/* E8h */	eastl::vector<float> mAnimationValues;
		/* FCh */	eastl::vector<float> mAnimationWeights;
		/* 110h */	int field_110;
		/* 114h */	eastl::vector<int> mEffects;  // size 38h
	};
	ASSERT_SIZE(cCreatureDataResource, 0x128);

	namespace Addresses(cCreatureDataResource)
	{
		DeclareAddress(Read);  // 0x4BECA0 0x4BF970
		DeclareAddress(Write);  // 0x4BEFE0 0x4BFCB0
	}
}