#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Graphics\Model.h>
#include <EASTL\array.h>
#include <EASTL\hash_map.h>
#include <EASTL\fixed_hash_map.h>
#include <EASTL\fixed_vector.h>

#define ObstacleManager (*Simulator::cObstacleManager::Get())

namespace Simulator
{
	class cObstacleManager
		: public App::IMessageListener
		, public cStrategy
	{
	public:
		static cObstacleManager* Get();

	public:
		/* 20h */	int mFlags;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
		/* 38h */	eastl::sp_fixed_hash_map<int, eastl::array<int, 4>, 256> field_38;
		/* 2094h */	eastl::sp_fixed_hash_map<int, eastl::array<int, 4>, 256> field_2094;
		/* 40F0h */	eastl::fixed_vector<int, 512> field_40F0;
		/* 4908h */ eastl::fixed_vector<int, 48> field_4908;
		/* 49E0h */	eastl::sp_fixed_hash_map<int, int, 64> field_49E0;
		/* 4F30h */	eastl::sp_fixed_hash_map<int, int, 64> field_4F30;
		/* 5480h */	float field_5480;
		/* 5484h */	float field_5484;
		/* 5488h */	float field_5488;
		/* 548Ch */	float field_548C;
		/* 5490h */	float field_5490;
		/* 5494h */	float field_5494;
		/* 5498h */	float field_5498;
		/* 549Ch */	float field_549C;
		/* 54A0h */	float field_54A0;
		/* 54A4h */	float field_54A4;
		/* 54A8h */	eastl::hash_map<int, int> field_54A8;
		/* 54C8h */	eastl::hash_map<int, int> field_54C8;
		/* 54E8h */	eastl::hash_map<int, int> field_54E8;
		/* 5508h */	eastl::fixed_vector<int, 32> field_5508;
		/* 55A0h */	uint32_t mPickObstacleTypes;
		/* 55A4h */	int field_55A4;
		/* 55A8h */	eastl::fixed_vector<ModelPtr, 64> mObstaclesToAdd;
		/* 56C0h */	eastl::hash_map<ResourceKey, ResourceKey> mTerrainModelReplacements;
	};
	ASSERT_SIZE(cObstacleManager, 0x56E0);

	namespace Addresses(cObstacleManager) {
		DeclareAddress(Get);  // 0xB3D320 0xB3D4C0
	}
}