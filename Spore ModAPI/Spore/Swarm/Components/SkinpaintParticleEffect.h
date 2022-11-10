#pragma once

#include <Spore\Swarm\Components\cDescription.h>
#include <Spore\Swarm\IComponent.h>
#include <Spore\Transform.h>
#include <Spore\MathUtils.h>
#include <Spore\resourceID.h>
#include <EASTL\vector.h>

namespace Swarm
{
	class cSkinpaintParticleDescription
		: public cDescription
	{
	public:
		struct VarModifier
		{
			/* 00h */	float values[3];
			/* 0Ch */	int8_t modifierType;
			/* 0Dh */	int8_t valueCount;
			/* 0Eh */	int16_t valueIndex;
		};
		ASSERT_SIZE(VarModifier, 0x10);

		struct Variable
		{
			/* 00h */	float range[2];
			/* 08h */	float values[2];
			/* 10h */	int8_t channel;
			/* 11h */	int8_t varModifierIndex;
			/* 12h */	int8_t operationType;
			/* 13h */	int8_t flag;
		};
		ASSERT_SIZE(Variable, 0x14);

		struct Data
		{
			/* 00h */	int vftable2;
			/* 04h */	eastl::vector<uint32_t> brushes;
			/* 18h */	int chainIndex;
			/* 1Ch */	int flags;
			/* 20h */	Math::ColorRGB diffuseColor;
			/* 2Ch */	int8_t diffuseColorIndex;
			/* 2Dh */	int8_t alignFlag;
			/* 2Eh */	int8_t initDirFlag;
			/* 2Fh */	int8_t attractFlag;
			/* 30h */	Math::Vector3 align;
			/* 3Ch */	Math::Vector3 initDir;
			/* 48h */	Math::Vector3 attract;
			/* 54h */	float attractForce;
			/* 58h */	float delay0;
			/* 5Ch */	float delay1;
			/* 60h */	float life0;
			/* 64h */	float life1;
			/* 68h */	int inheritFlags;
			/* 6Ch */	eastl::vector<VarModifier> varModifiers;
			/* 80h */	eastl::vector<Variable> variables;
			/* 94h */	eastl::vector<float> variableValues;
			/* A8h */	int8_t diffuseBlend;
			/* A9h */	int8_t specularBlend;
			/* AAh */	int8_t bumpBlend;
		};

		/* 08h */	Data mData;
		/* B4h */	int field_B4;
	};
	ASSERT_SIZE(cSkinpaintParticleDescription, 0xB8);

	class cSkinpaintParticleEffect
		: public cComponentBase
	{
	public:
		/* 0Ch */	Transform mTransform;
		/* 44h */	bool field_44;  // not initialized
		/* 48h */	cSkinpaintParticleDescription* mpDescription;
		/* 4Ch */	int field_4C;
	};
	ASSERT_SIZE(cSkinpaintParticleEffect, 0x50);
}