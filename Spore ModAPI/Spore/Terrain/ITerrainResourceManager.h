#pragma once

#include <Spore\Internal.h>
#include <Spore\App\PropertyList.h>
#include <Spore\Terrain\ITerrain.h>

#define TerrainResourceManager (*Terrain::ITerrainResourceManager::Get())

namespace Terrain
{
	class ITerrainResourceManager
	{
	public:
		virtual ~ITerrainResourceManager();

		virtual App::PropertyList* GetPropertyList(const ResourceKey& planetKey) = 0;
		/// returns wta and planetinfo?
		virtual void func08h(const ResourceKey& key, int* dst) = 0;
		virtual void func0Ch(const ResourceKey& key) = 0;  // removes player effects and models?
		virtual App::PropertyList* func10h(int, uint32_t instanceID, uint32_t groupID) = 0;  // create copy of planet?
		virtual bool LoadPlanet(const ResourceKey& key, ITerrainPtr& dst, bool = false, bool generateSingleStep = true, float generateTimeLimit = 10.0) = 0;
		virtual void func18h(int) = 0;  // maybe update? does nothing
		virtual bool func1Ch(int) = 0;  // related with saving
		virtual bool func20h(const char16_t*) = 0;  // related with saving
		virtual void func24h() = 0;
		virtual int func28h(int) = 0;

		static ITerrainResourceManager* Get();

		/*
		04h	another vftable
		08h int field_8;
		0Ch	bool field_C;
		10h	vector field_10;
		24h	vector field_24;
		38h	vector field_38;
		4Ch	vector field_4C;
		60h	bool field_60;
		64h	DatabasePackedFilePtr field_64;
		*/
	};

	namespace Addresses(ITerrainResourceManager)
	{
		DeclareAddress(Get);
	}
}