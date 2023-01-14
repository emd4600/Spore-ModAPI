#pragma once

#include <Spore\Simulator\cScenarioResource.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cScenarioEconomy.h>
#include <Spore\Simulator\cOrnament.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Editors\INameableEntity.h>
#include <Spore\App\MessageListenerData.h>
#include <Spore\Graphics\Texture.h>
#include <EASTL\hash_map.h>

#define cScenarioDataPtr eastl::intrusive_ptr<Simulator::cScenarioData>

namespace Simulator
{
	class cScenarioData
		/* 04h */	: public App::IUnmanagedMessageListener
		/* 04h */	, public Editors::INameableEntity
		/* 08h */	, public DefaultRefCounted
	{
	public:
		/* 0Ch */	virtual ScenarioGenre GetGenre();
		/* 10h */	virtual void SetGenre(ScenarioGenre genre);

		void Initialize(bool);

		/// Starts a history entry (i.e. one undo/redo action) based on the current state of the scenario data
		/// (the `mpResource` field). This must be called before changing the data; after the data has been modified,
		/// call CommitHistoryEntry() to finish this history entry.
		void StartHistoryEntry();

		/// Commits an on-going history entry (i.e. one undo/redo action) based on the current state of the scenario data
		/// (the `mpResource` field). This must be called after changing the data; before modifying the data you must have
		/// called StartHistoryEntry().
		void CommitHistoryEntry();

		/// Returns the scenario class identified by the given index.
		/// @param index
		/// @returns
		cScenarioClass* GetClass(int index);

		/// Retrieves the scenario act-specific data of a certain object.
		/// @param pObject
		/// @returns
		cScenarioClassAct* GetCurrentClassAct(cGameData* pObject);

		/// Returns the game data object that represents the given marker
		/// @param pMarker
		/// @returns
		cGameData* GetObjectForMarker(cScenarioMarker* pMarker);

		/// Returns the scenario marker information that is represented by the given game data object
		/// @param pGameData
		/// @returns
		cScenarioMarker* GetMarkerForObject(cGameData* pGameData);

		/// Returns the index of the current act in the adventure edit mode.
		/// @returns
		static int GetEditModeActIndex();

		/// Create an Simulator object instance for a scenario object class. It also calls the
		/// cGameNounManager::UpdateModels() method.
		/// @param name File name of the object to create (usually a `.crt`, `.bld`, `.prop` etc)
		/// @param position World position for the newly created object
		/// @param orientation World orientation for the newly created object
		/// @param scale Scale of the object
		/// @param isAvatar True if the object being created is the avatar (i.e. the player creature)
		/// @param scenarioClassIndex Index to the scenario class that describes this object (within the cScenarioResource classes vector)
		/// @param pMarker 
		static cGameData* CreateObjectInstance(const ResourceKey& name, const Vector3& position, const Quaternion& orientation,
			float scale, bool isAvatar, int scenarioClassIndex, cScenarioMarker* pMarker, cScenarioMarkerAct* pActs, int actIndex);

		/// Called by CreateObjectInstance() (and another method related with respawners), creates the object instance of a powerup
		/// adventure object. The instance is a cOrnament for most objects, or a cInteractiveOrnament for objects that can be 
		/// picked up. Teleporters create two objects (for the entrance and exit teleporters) and return the entrance one.
		/// @param pPropList
		/// @param pMarker
		/// @param scenarioClassIndex
		/// @returns The created game object
		static cGameData* CreatePowerupObjectInstance(App::PropertyList* pPropList, cScenarioMarker* pMarker, int scenarioClassIndex);

	public:
		/* 10h */	cScenarioResourcePtr mpResource;
		/* 14h */	bool mHadMissingAssets;
		/* 18h */	int field_18;
		/* 1Ch */	bool field_1C;  // true
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	bool field_2C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
		/* 38h */	TexturePtr mThumbnail;
		/* 3Ch */	TexturePtr mLargeThumbnail;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/// Whenever the name is changed (use the SetName() method) it sends a `0x7AA519DC` message
		/* 4Ch */	eastl::string16 mName;
		/// Whenever the description is changed (use the SetDescription() method) it sends a `0x14418C3F` message
		/* 5Ch */	eastl::string16 mDescription;
		/// Whenever the tags are changed (use the SetTags() method) it sends a `0x73127E6` message
		/* 6Ch */	eastl::string16 mTags;
		/* 7Ch */	ScenarioGenre mGenre;  // ScenarioUnset
		/* 80h */	int field_80;
		/// Set by the SetGenre() function when the genre changes
		/* 84h */	bool mGenreHasChanged;
		/// Set to true when the name, description, or tags are changed
		/* 85h */	bool mMetadataHasChanged;
		/* 88h */	int field_88;  // not initialized
		/* 8Ch */	cScenarioMarker* mpAvatarMarker;
		/// Maps to each scenario marker (its index) its instantiated cGameData object
		/* 90h */	eastl::hash_map<cGameData*, int> mObjectsToMarkersMap;  // maybe it's a cGameDataPtr but compiler complains
		/// Maps each scenario marker (its index) to its instantiated cGameData object
		/* B0h */	eastl::hash_map<int, cGameDataPtr> mMarkersToObjectsMap;
		/* D0h */	cScenarioDataEconomyPtr mpEconomy;
		/* D4h */	App::MessageListenerData field_D4;  // some container
		/* E8h */	int field_E8;
		/* ECh */	int field_EC;
		/* F0h */	int field_F0;
		/* F4h */	int field_F4;
		/* F8h */	int field_F8;
		/* FCh */	int field_FC;
		/* 100h */	int field_100;
		/* 104h */	int field_104;
		/* 108h */	int field_108;
		/* 10Ch */	int field_10C;
		/* 110h */	int field_110;
		/* 114h */	int field_114;
		/* 118h */	int field_118;
		/* 11Ch */	int field_11C;
		/* 120h */	int field_120;
		/* 124h */	bool mHasLoaded;
		/* 128h */	eastl::vector<int> field_128;
		/* 13Ch */	eastl::hash_map<int, int> field_13C;
		/* 15Ch */	eastl::hash_map<int, int> field_15C;
		/* 17Ch */	eastl::hash_map<int, int> field_17C;
		/* 19Ch */	eastl::hash_map<int, int> field_19C;
		/* 1BCh */	eastl::hash_map<int, int> field_1BC;
		/* 1DCh */	eastl::hash_map<int, int> field_1DC;
	};
	ASSERT_SIZE(cScenarioData, 0x1FC);

	namespace Addresses(cScenarioData)
	{
		DeclareAddress(Initialize);  // 0xF44AC0
		DeclareAddress(StartHistoryEntry);  // 0xF45C40
		DeclareAddress(CommitHistoryEntry);
		DeclareAddress(GetClass);  // 0xF3EBA0
		DeclareAddress(GetCurrentClassAct);  // 0xF3FC50
		DeclareAddress(GetEditModeActIndex);
		DeclareAddress(CreateObjectInstance);  // 0xEEE090, 0xEEDD40
		DeclareAddress(CreatePowerupObjectInstance);
		DeclareAddress(GetObjectForMarker);  // 0xF3D810, 0xF3D620
		DeclareAddress(GetMarkerForObject);  // 0xF3DD80, 0xF3DB10
	}
}