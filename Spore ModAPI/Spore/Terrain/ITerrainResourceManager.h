#pragma once

#include <Spore\Internal.h>
#include <Spore\App\PropertyList.h>
#include <Spore\Resource\Database.h>
#include <Spore\Terrain\ITerrain.h>

#define TerrainResourceManager (*Terrain::ITerrainResourceManager::Get())

namespace Terrain
{
	class ITerrainResourceManager
	{
	public:
		virtual ~ITerrainResourceManager();

		/* 04h */	virtual App::PropertyList* GetPropertyList(const ResourceKey& planetKey) = 0;
		/// returns wta and planetinfo?
		/* 08h */	virtual void func08h(const ResourceKey& key, int* dst) = 0;
		/* 0Ch */	virtual void func0Ch(const ResourceKey& key) = 0;  // removes player effects and models?

		/// Creates a property list and saves it to a file with key `outputKey`,
		/// copying to it the terrain script identified with `groupID!instanceID`.
		/// This will also rewrite the DBPF that stores the planet property lists.
		/// @param outputKey
		/// @param instanceID
		/// @param groupID
		/* 10h */	virtual App::PropertyList* SaveTerrain(const ResourceKey& outputKey, uint32_t instanceID, uint32_t groupID) = 0;

		/* 14h */	virtual bool LoadPlanet(const ResourceKey& key, ITerrainPtr& dst, bool = false, bool generateSingleStep = true, float generateTimeLimit = 10.0) = 0;
		/* 18h */	virtual void func18h(int) = 0;  // maybe update? does nothing
		/* 1Ch */	virtual bool func1Ch(int) = 0;  // related with saving
		/* 20h */	virtual bool func20h(const char16_t*) = 0;  // related with saving
		/* 24h */	virtual void func24h() = 0;
		/* 28h */	virtual int func28h(int) = 0;

		static ITerrainResourceManager* Get();

	public:
		/* 04h */	int vftable_4;
		/* 08h */	int field_8;
		/* 0Ch */	bool mIsInitialized;
		/* 10h */	eastl::vector<ResourceKey> field_10;
		/* 24h */	eastl::vector<ResourceKey> field_24;
		/* 38h */	eastl::vector<ResourceKey> field_38;
		/* 4Ch */	eastl::vector<ResourceKey> field_4C;
		/* 60h */	bool field_60;
		/* 64h */	DatabasePtr field_64;
	};
	ASSERT_SIZE(ITerrainResourceManager, 0x68);

	namespace Addresses(ITerrainResourceManager)
	{
		DeclareAddress(Get);
	}
}