#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>
#include <Spore\Terrain\ITerrain.h>
#include <Spore\Simulator\cScenarioEconomy.h>
#include <Spore\Simulator\cScenarioData.h>
#include <EASTL\vector.h>

#define cScenarioTerraformModePtr eastl::intrusive_ptr<Simulator::cScenarioTerraformMode>

namespace Simulator
{
	class cScenarioTerraformMode
		: public App::IMessageListener
		, public DefaultRefCounted
	{
	public:
		/* 10h */	virtual bool func10h(uint32_t);

		/// Starts a history entry (i.e. one undo/redo action) based on the current state of the scenario terraform data
		/// (the `mpPropList` field). This must be called before changing the data; after the data has been modified,
		/// call CommitHistoryEntry() to finish this history entry.
		void StartHistoryEntry();

		/// Commits an on-going history entry (i.e. one undo/redo action) based on the current state of the scenario terraform data
		/// (the `mpPropList` field). This must be called after changing the data; before modifying the data you must have
		/// called StartHistoryEntry().
		void CommitHistoryEntry();

		void SetWaterColor(const ColorRGB& color);
		void SetAtmosphereColor(const ColorRGB& color);
		void SetCliffColor(const ColorRGB& color);
		void SetBeachColor(const ColorRGB& color);

	public:
		/* 0Ch */	PropertyListPtr mpPropList;
		/* 10h */	cScenarioTerraformEconomyPtr mpEconomy;
		/* 14h */	eastl::vector<uint32_t> mTerrainScriptEffects;
		/* 28h */	eastl::vector<Transform> mTerrainScriptEffectTransforms;
		/* 3Ch */	eastl::vector<float> mTerrainScriptEffectIntensities;
		/* 50h */	eastl::vector<float> mTerrainScriptEffectTimes;
		/* 64h */	eastl::vector<float> mTerrainScriptEffectSeeds;
		/* 78h */	eastl::vector<int> field_78;
		/* 8Ch */	eastl::vector<float> mTerrainScriptEffectWaterLevels;
		/* A0h */	eastl::vector<ResourceKey> mTerrainScriptModels;
		/* B4h */	eastl::vector<Transform> mTerrainScriptModelTransforms;
		/* C8h */	Vector3 mTerrainScriptWTALevels;  // not initialized
		/// First value is percentage of day
		/* D4h */	Vector3 mTerrainScriptERLLevels;  // not initialized
		/// terrain/dead/atmosphere types
		/* E0h */	Vector3 mTerrainScriptPlanetInfo;  // not initialized
		/// Determines base water color
		/* ECh */	int mWaterType;  // not initialized
		/// Determines base atmosphere color
		/* F0h */	int mAtmosphereType;  // not initialized
		/* F4h */	ResourceKey mVisualStyleId;
		/* 100h */	IVisualEffectPtr mpVisualStyleEffect;
		/// Related with colors
		/* 104h */	bool mTerrainOverrideMode;  // true
		/* 108h */	eastl::vector<ColorRGB> mTerrainColors;
		/* 11Ch */	eastl::vector<float> mTerrainColorsElevations;
		/* 130h */	ColorRGB mBeachColor;  // not initialized
		/* 13Ch */	ColorRGB mCliffColor;  // not initialized
		/* 148h */	ColorRGB mWaterColor;  // not initialized
		/* 154h */	ColorRGB mAtmosphereColor;  // not initialized
		/* 160h */	uint32_t mGroundEffectId;  // not initialized
		/// Points of no flora in the planet. x,y,z are the position, w is the radius in which flora is removed
		/* 164h */	eastl::vector<Vector4> mClearFloraAround;
		/* 178h */	App::MessageListenerData mMessageListenerData;
		/* 18Ch */	bool field_18C;  // not initialized
		/* 18Dh */	bool mTerrainHazardsEnable;  // true
		/* 190h */	Terrain::ITerrain* mpTerrain;
		/* 194h */	Terrain::cTerrainStateMgr* mpTerrainStateMgr;
		/* 198h */	cScenarioData* mpScenarioData;  // not initialized
		/* 19Ch */	eastl::vector<int> field_19C;  // cGameDataPtr, Vector3?, related with terrain effect handles?
		/* 1B0h */	int field_1B0;
		/* 1B4h */	int field_1B4;  // not initialized
		/* 1B8h */	bool field_1B8;
		/* 1BCh */	Vector3 field_1BC;  // not initialized
		/* 1C8h */	float field_1C8;  // not initialized
	};
	ASSERT_SIZE(cScenarioTerraformMode, 0x1CC);

	namespace Addresses(cScenarioTerraformMode)
	{
		DeclareAddress(StartHistoryEntry);  // 0xF33AD0, 0xF33A90
		DeclareAddress(CommitHistoryEntry);  // 0xF45D50, 0xF34400
		DeclareAddress(SetWaterColor);  // 0xF32140, 0xF31FA0
		DeclareAddress(SetAtmosphereColor);  // 0xF32190, 0xF31FF0
		DeclareAddress(SetBeachColor);  // 0xF321E0, 0xF32040
		DeclareAddress(SetCliffColor);  // 0xF32230, 0xF32090
	}
}