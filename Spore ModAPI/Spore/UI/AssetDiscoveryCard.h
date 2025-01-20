#pragma once

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\Sporepedia\AssetData.h>
#include <Spore\UI\cSPAssetView.h>

#define AssetDiscoveryCardPtr eastl::intrusive_ptr<UI::AssetDiscoveryCard>

namespace UI
{
	class AssetDiscoveryCard
		: public DefaultRefCounted
	{
	public:
		AssetDiscoveryCard();
		virtual ~AssetDiscoveryCard() {}

	public:
		/* 08h */	UILayoutPtr mLayout;
		/* 0Ch */	cSPSpaceAssetDataOTDBPtr mAssetData;
		/* 10h */	cSPAssetViewPtr mAssetView;
		/* 14h */	IWindowPtr mContainerWindow;
		/* 18h */	IWindowPtr mAssetWindow;
	};
	ASSERT_SIZE(AssetDiscoveryCard, 0x1C);
}