#pragma once

#include <Spore\Swarm\Components\cDescription.h>
#include <Spore\Swarm\IComponent.h>
#include <Spore\MathUtils.h>
#include <Spore\ResourceID.h>

namespace Swarm
{
	class cSkinpaintSettingsDescription 
		: public cDescription
	{
	public:
		/* 08h */	int diffuseColorIndex;
		/* 0Ch */	Math::ColorRGB diffuseColor;
		/* 18h */	float spec;
		/* 1Ch */	float specExp;
		/* 20h */	float bump;
		/* 24h */	float gloss;
		/* 28h */	float phong;
		/* 2Ch */	float partBumpScale;
		/* 30h */	float partSpecScale;
		/* 34h */	float field_34;
		/* 38h */	float field_38;
		/* 3Ch */	float field_3C;
		/* 40h */	float field_40;
		/* 44h */	float field_44;
		/* 48h */	float field_48;
		/* 4Ch */	float field_4C;
		/* 50h */	float field_50;
		/* 54h */	bool field_54;
		/* 58h */	ResourceID hairTexture;
		/* 60h */	ResourceID hairPrintGeom;
		/* 68h */	int flags;
		/* 6Ch */	int field_6C;
	};
	ASSERT_SIZE(cSkinpaintSettingsDescription, 0x70);

	class cSkinpaintSettingsEffect
		: public cComponentBase
	{
	public:
		virtual void ApplyEffect(float, float, cComponentStats*) override;

	public:
		/* 0Ch */	cSkinpaintSettingsDescription* mpDescription;
		/* 10h */	bool field_10;
	};
	ASSERT_SIZE(cSkinpaintSettingsEffect, 0x14);

	namespace Addresses(cSkinpaintSettingsEffect)
	{
		DeclareAddress(ApplyEffect);  // 0x52EAC0 TODO
	}
}