#pragma once

#include <EASTL\fixed_vector.h>
#include <Spore\ModAPI.h>
#include <Spore\Graphics\cMaterialManager.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\CommonIDs.h>
#include <Spore\Messaging.h>
#include <Spore\Cheats.h>

using namespace Graphics;
using namespace Resource;

virtual_detour(ShaderFragments_detour, cMaterialManager, IMaterialManager, bool(DatabasePackedFile*)) {};

extern void LoadMaterials(uint32_t, void*, void*);

namespace ModAPI
{
	const int MAX_MODS = 2048;
	extern fixed_vector<InitFunction, MAX_MODS> initFunctions;
	extern fixed_vector<InitFunction, MAX_MODS> postInitFunctions;
	extern fixed_vector<InitFunction, MAX_MODS> disposeFunctions;

	long AttachDetour();
	void DetachDetour();

	class UnkClass {};
	member_detour(sub_7E6C60_detour, UnkClass, int(int)) {};
	member_detour(AppInit_detour, UnkClass, int(int)) {};
	member_detour(AppShutdown_detour, UnkClass, int()) {};
}