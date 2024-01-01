#pragma once

#include <Spore\Object.h>
#include <Spore\LocalizedString.h>
#include <Spore\ResourceKey.h>
#include <Spore\App\PropertyList.h>
#include <EASTL\vector.h>

#define VerbIconDataPtr eastl::intrusive_ptr<Editors::VerbIconData>

namespace Editors
{
	class VerbIconData
		: public Object
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x4AA0ACD;

		/* 10h */	virtual void ParseProp(App::PropertyList* propList);
		/// Resets mpPropList
		/* 14h */	virtual void ClearPropList();
		/* 18h */	virtual void func18h(int);
		/// Used to generate text
		/* 20h */	virtual void SetKey(int verbIconTriggerKey);
		/* 24h */	virtual eastl::string16 GetName(bool includeLevel);
		/* 28h */	virtual eastl::string16 GetDescription();

	public:
		/* 0Ch */	bool mVerbIconUseDescription;  // true
		/* 0Dh */	bool mVerbIconShowLevel;  // true
		/* 0Eh */	bool mPaletteItemRolloverShowLevel;  // true
		/* 0Fh */	bool mVerbIconRolloverShowLevel;  // true
		/* 10h */	bool field_10;
		/* 11h */	bool mVerbIconShowZeroLevel;
		/* 14h */	int mVerbIconTriggerKey;  // -1
		/* 18h */	int field_18;  // not initialized
		/* 1Ch */	float mVerbIconMaxLevel;
		/* 20h */	int field_20;  // not initialized
		/* 24h */	uint32_t mVerbIconCategory;
		/* 28h */	uint32_t mVerbIconRepresentativeAnimation;  // -1
		/* 2Ch */	Math::ColorRGBA mVerbIconColor;
		/* 3Ch */	uint32_t mVerbIconRolloverLevelImageID;
		/* 40h */	ResourceKey mVerbIconRolloverLevelLayoutID;
		/* 4Ch */	bool mVerbIconRolloverShowIcon;  // not initialized
		/* 4Dh */	bool mVerbIconEnforceMaxLevel;
		/* 50h */	uint32_t mCreatureAbilityCategory;  // not initialized
		/* 54h */	LocalizedString mCreatureAbilityName;
		/* 68h */	eastl::string16 field_68;
		/* 78h */	uint32_t mTriggerKeyForLocalization;
		/* 7Ch */	int field_7C;  // -1
		/* 80h */	int field_80;  // -1
		/* 84h */	int field_84;
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	uint32_t mVerbIconImageID;  // not initialized
		/* 94h */	uint32_t mVerbIconTrayOverrideImageID;
		/* 98h */	uint32_t mVerbIconTraySmallCardOverrideImageID;  // not initialized
		/* 9Ch */	ResourceKey mVerbIconLayout;
		/* A8h */	ResourceKey mVerbIconGameLayout;
		/* B4h */	ResourceKey mVerbIconStaticLayout;
		/* C0h */	PropertyListPtr mpPropList;
	};
	ASSERT_SIZE(VerbIconData, 0xC4);
}