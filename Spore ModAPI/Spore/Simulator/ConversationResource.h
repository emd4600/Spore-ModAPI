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
		/* 00h */	bitset<154> flags1;
		/* 14h */	bitset<154> flags2;
		/* 28h */	LocalizedString text;
		/* 3Ch */	uint32_t tableID;
		/* 40h */	uint32_t instanceID;
		/* 44h */	uint32_t emotion;
	};
	struct CnvAnimationVariation
	{
		/* 00h */	string name;
		/* 10h */	vector<uint32_t> idleAnimIDs;
		/* 24h */	vector<uint32_t> actionAnimIDs;
	};
	struct CnvAnimation
	{
		/* 00h */	string name;
		/* 10h */	map<uint32_t, CnvAnimationVariation> variations;
	};
	struct CnvEventLog
	{
		/* 00h */	string name;
		/* 10h */	vector<CnvText> texts;
	};
	struct CnvDialogResponse
	{
		/* 00h */	bitset<154> flags1;
		/* 14h */	bitset<154> flags2;
		/* 28h */	bitset<154> flags3;
		/* 3Ch */	bitset<154> flags4;
		/* 50h */	CnvAction action;
		/* 60h */	vector<CnvText> texts;
		/* 74h */	vector<uint32_t> ints1;
		/* 88h */	vector<uint32_t> ints2;
		/* 9Ch */	vector<uint32_t> ints3;
		/* B0h */	vector<uint32_t> ints4;
	};
	struct CnvDialog
	{
		/* 00h */	string name;
		/* 10h */	bool value1;
		/* 11h */	bool value2;
		/* 12h */	bool value3;
		/* 13h */	bool value4;
		/* 14h */	bool value5;
		/* 18h */	CnvAction action;
		/* 28h */	vector<CnvText> texts;
		/* 3Ch */	vector<CnvDialogResponse> responses;
	};
	struct CnvUnknown
	{
		/* 00h */	uint32_t missionID;
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	vector<int> field_10;
		/* 24h */	vector<int> field_24;
		/* 38h */	vector<int> field_38;
		/* 4Ch */	vector<int> field_4C;
	};

	class ConversationResource
		: public Resource::ResourceObject
	{
	public:

		/* 14h */	int field_14;
		/* 18h */	map<uint32_t, CnvDialog> dialogs;
		/* 34h */	map<uint32_t, CnvEventLog> eventLogs;
		/* 50h */	map<uint32_t, CnvAnimation> animations;
		/* 6Ch */	vector<CnvUnknown> field_6C;
	};
	ASSERT_SIZE(ConversationResource, 0x80);
}