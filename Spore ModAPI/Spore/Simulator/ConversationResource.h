#pragma once

#include <Spore\Resource\ResourceObject.h>
#include <Spore\LocalizedString.h>
#include <EASTL\map.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\bitset.h>

namespace Simulator
{
	struct CnvAction
	{
		uint32_t actionID;
		ResourceKey key;
	};
	struct CnvText
	{
		/* 00h */	eastl::bitset<154> flags1;
		/* 14h */	eastl::bitset<154> flags2;
		/* 28h */	LocalizedString text;
		/* 3Ch */	uint32_t tableID;
		/* 40h */	uint32_t instanceID;
		/* 44h */	uint32_t emotion;
	};
	struct CnvAnimationVariation
	{
		/* 00h */	eastl::string name;
		/* 10h */	eastl::vector<uint32_t> idleAnimIDs;
		/* 24h */	eastl::vector<uint32_t> actionAnimIDs;
	};
	struct CnvAnimation
	{
		/* 00h */	eastl::string name;
		/* 10h */	eastl::map<uint32_t, CnvAnimationVariation> variations;
	};
	struct CnvEventLog
	{
		/* 00h */	eastl::string name;
		/* 10h */	eastl::vector<CnvText> texts;
	};
	struct CnvDialogResponse
	{
		/* 00h */	eastl::bitset<154> flags1;
		/* 14h */	eastl::bitset<154> flags2;
		/* 28h */	eastl::bitset<154> flags3;
		/* 3Ch */	eastl::bitset<154> flags4;
		/* 50h */	CnvAction action;
		/* 60h */	eastl::vector<CnvText> texts;
		/* 74h */	eastl::vector<uint32_t> ints1;
		/* 88h */	eastl::vector<uint32_t> ints2;
		/* 9Ch */	eastl::vector<uint32_t> ints3;
		/* B0h */	eastl::vector<uint32_t> ints4;
	};
	struct CnvDialog
	{
		/* 00h */	eastl::string name;
		/* 10h */	bool value1;
		/* 11h */	bool value2;
		/* 12h */	bool value3;
		/* 13h */	bool value4;
		/* 14h */	bool value5;
		/* 18h */	CnvAction action;
		/* 28h */	eastl::vector<CnvText> texts;
		/* 3Ch */	eastl::vector<CnvDialogResponse> responses;
	};
	struct CnvUnknown
	{
		/* 00h */	uint32_t missionID;
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	eastl::vector<int> field_10;
		/* 24h */	eastl::vector<int> field_24;
		/* 38h */	eastl::vector<int> field_38;
		/* 4Ch */	eastl::vector<int> field_4C;
	};

	class ConversationResource
		: public Resource::ResourceObject
	{
	public:

		/* 14h */	int field_14;
		/* 18h */	eastl::map<uint32_t, CnvDialog> dialogs;
		/* 34h */	eastl::map<uint32_t, CnvEventLog> eventLogs;
		/* 50h */	eastl::map<uint32_t, CnvAnimation> animations;
		/* 6Ch */	eastl::vector<CnvUnknown> field_6C;
	};
	ASSERT_SIZE(ConversationResource, 0x80);
}