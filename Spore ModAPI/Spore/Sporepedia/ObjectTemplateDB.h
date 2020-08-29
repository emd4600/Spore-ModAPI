#pragma once

#include <Spore\Object.h>
#include <EASTL\vector.h>

#define ObjectTemplateDB (*Sporepedia::cObjectTemplateDB::Get())

namespace Sporepedia
{
	struct OTDBParameter
	{
		OTDBParameter();
		OTDBParameter(uint32_t paramID, float minValue, float maxValue);

		/* 00h */	uint32_t paramID;
		/* 04h */	uint32_t type;  // 0x2E1A7FF
		/* 08h */	float minValue;
		/* 0Ch */	float maxValue;
		/* 10h */	vector<OTDBParameter> field_10;
	};

	class cObjectTemplateDB
		: public Object
	{
	public:
		/* 10h */	virtual bool Initialize();
		/* 14h */	virtual bool Dispose();
		/* 18h */	virtual bool func18h(int, int);
		/* 1Ch */	virtual bool func1Ch();
		/* 20h */	virtual void func20h();
		/* 24h */	virtual bool func24h(int, int, int);
		/* 28h */	virtual bool func28h(int, int, int);
		/* 2Ch */	virtual void FindObjects(vector<ResourceKey>& dst, const vector<OTDBParameter>& parameters);
		//TODO there are more functions

		static cObjectTemplateDB* Get();
	};

	namespace OTDBParameters
	{
		enum : uint32_t
		{
			cost = 0x5B06E36,
			baseGear = 0x2F05C60,
			height = 0x7358629A,
			carnivore = 0x2F05C58,
			herbivore = 0x2F05C59,
			cuteness = 0x2F05C5E,
			totalSocial = 0x2F05C5F,
			social = 0x5B15AA5,
			numGraspers = 0x2F05C61,
			meanLookingScore = 0x3FEA210,
			totalAttack = 0x3FEA1A0,
			attack = 0x5B15A92,
			numFeet = 0x3FEA1C0,
			biteCapRange = 0x4AB3BD8,
			strikeCapRange = 0x4AB3BD9,
			chargeCapRange = 0x4AB3BDA,
			spitCapRange = 0x4AB3BDB,
			singCapRange = 0xF42136D5,
			danceCapRange = 0xF42136D6,
			charmCapRange = 0xF42136D7,
			poseCapRange = 0xF42136D8,
			glideCapRange = 0x5AC2B96,
			stealthCapRange = 0x5AC2B97,
			sprintCapRange = 0x5AC2B98,
			senseCapRange = 0x68DE3E8,
			healthCapRange = 0x5AC2B99,
		};
	}

	namespace Addresses(cObjectTemplateDB)
	{
		DeclareAddress(Get);
	}
}