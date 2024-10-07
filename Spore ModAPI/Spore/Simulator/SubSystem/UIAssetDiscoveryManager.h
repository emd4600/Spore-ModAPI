#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\UI\AssetDiscoveryCard.h>
#include <EASTL\deque.h>

//#define UIAssetDiscoveryManager (*Simulator::cUIAssetDiscoveryManager::Get())

namespace Simulator
{
	class cUIAssetDiscoveryManager
		: public cStrategy
		, public App::IMessageListener
	{
	public:
		//static cUIAssetDiscoveryManager* Get();

	public:
		/* 20h */	int field_20;
		/* 24h */	eastl::deque<AssetDiscoveryCardPtr> mDiscoveryCards;
		/* 50h */	char padding_50[0xA8 - 0x50];
	};
	ASSERT_SIZE(cUIAssetDiscoveryManager, 0xA8);

	//namespace Addresses(cUIAssetDiscoveryManager) {
	//	DeclareAddress(Get);  // 0xB3D450 TODO
	//}
}