#pragma once

#include <Spore\Simulator\cSpaceInventoryItem.h>
#include <Spore\Simulator\cSpeciesProfile.h>
#include <Spore\Simulator\cGameData.h>

#define cObjectInstanceInventoryItemPtr eastl::intrusive_ptr<Simulator::cObjectInstanceInventoryItem>

namespace Simulator
{
	class cObjectInstanceInventoryItem
		: public cSpaceInventoryItem
	{
	public:
		static const uint32_t TYPE = 0x73905AE;

	public:
		/* 7Ch */	cGameDataPtr mObject;
	};
	ASSERT_SIZE(cObjectInstanceInventoryItem, 0x80);
}