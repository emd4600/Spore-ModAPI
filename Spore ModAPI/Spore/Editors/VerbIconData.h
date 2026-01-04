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
		//: public Object
		: public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x4AA0ACD;
		
		enum InterfaceId
		{
			kIIDMin = 0,
			kIIDFactory = 1,
			kIIDMax = 0xffffffff,
		};

		/* 00h */	virtual int AddRef();
		/* 04h */	virtual int Release();
		/* 08h */	virtual void* Dispose();
		/* 0Ch */	virtual void* AsInterface(InterfaceId propList);
		/* 10h */	virtual void Init(App::PropertyList* propList);
		/* 14h */	virtual void Shutdown();
		/* 18h */	virtual void SetArrayIndex(int arrayIndex);
		/// Used to generate text
		/* 1Ch */	virtual void SetHotKey(int verbIconTriggerKey);
		/* 20h */	virtual eastl::string16 GetIconName(eastl::string16* iconName,bool includeLevel);
		/* 24h */	virtual eastl::string16 GetIconDescription(eastl::string16* iconDesc);

		enum eVerbIconCategory
		{
			kVerbCategoryNULL = 0,
			kVerbCategoryTribeAttack = 180661997,
			kVerbCategoryVehiclePower = 360359141,
			kVerbCategorySpeed = 640949982,
			kVerbCategoryTribeArmor = 662199250,
			kVerbCategoryHerbivore = 771444639,
			kVerbCategorySpit = 823131355,
			kVerbCategoryCellCilia = 835506386,
			kVerbCategoryVehicleDefense = 886488350,
			kVerbCategoryCellJaw = 1101458518,
			kVerbCategoryCellJet = 1168568857,
			kVerbCategorySprint = 1296465089,
			kVerbCategoryCellOmnivore = 1377441237,
			kVerbCategoryCellElectric = 1470348634,
			kVerbCategoryVehicleSpeed = 1501155019,
			kVerbCategoryOmnivore = 1557282664,
			kVerbCategoryTribeSocial = 1589650888,
			kVerbCategoryCellPoison = 1601154124,
			kVerbCategoryBite = 1645043423,
			kVerbCategoryDance = 1924791374,
			kVerbCategoryStarvivore = 2095425492,
			kVerbCategoryCellFlagella = 2165516464,
			kVerbCategoryGesture = 2167648234,
			kVerbCategoryPower = 2391494160,
			kVerbCategoryDefense = 2564315215,
			kVerbCategoryCarnivore = 2726979560,
			kVerbCategoryStealth = 2909291642,
			kVerbCategoryPosture = 2909789983,
			kVerbCategoryCellHealth = 2964572918,
			kVerbCategoryGlide = 2968795556,
			kVerbCategoryCellPoker = 3013574067,
			kVerbCategoryCellFilter = 3020374546,
			kVerbCategoryTribeFishing = 3188984297,
			kVerbCategoryTribeGather = 3253334812,
			kVerbCategoryVocalize = 3478552014,
			kVerbCategoryCellStarvivore = 3610717237,
			kVerbCategoryCellSpike = 3634179486,
			kVerbCategoryCellHerbivore = 3653024240,
			kVerbCategoryHealth = 3677180323,
			kVerbCategoryCellCarnivore = 3751859903,
			kVerbCategoryCall = 3753286133,
			kVerbCategoryJump = 3833651337,
			kVerbCategoryBlock = 4001580976,
			kVerbCategorySense = 4069948569,
			kVerbCategoryStrike = 4110605575,
			kVerbCategoryGrasp = 4248645338,
			kVerbCategoryCharge = 4285247397
		};

	public:
		/* 0Ch */	bool mVerbIconUseDescription;  // true
		/* 0Dh */	bool mVerbIconShowLevel;  // true
		/* 0Eh */	bool mPaletteItemRolloverShowLevel;  // true
		/* 0Fh */	bool mVerbIconRolloverShowLevel;  // true
		/* 10h */	bool mShowHotKey;
		/* 11h */	bool mVerbIconShowZeroLevel;
		/* 14h */	int mVerbIconTriggerKey;  // -1
		/* 18h */	float mVerbIconLevel;  // not initialized
		/* 1Ch */	float mVerbIconMaxLevel;
		/* 20h */	int field_20;  // not initialized
		/* 24h */	eVerbIconCategory mVerbIconCategory;
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
	ASSERT_SIZE(VerbIconData, 0xC0);

	namespace Addresses(VerbIconData)
	{
		DeclareAddress(AddRef);
		DeclareAddress(Release);
		DeclareAddress(Dispose);
		DeclareAddress(AsInterface);
		DeclareAddress(Init);
		DeclareAddress(Shutdown);
		DeclareAddress(SetArrayIndex);
		DeclareAddress(SetHotKey);
		DeclareAddress(GetIconName);
		DeclareAddress(OnKeyDown);
		DeclareAddress(GetIconDescription);
	}
}