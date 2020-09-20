#pragma once

#include <Spore\Resource\ResourceObject.h>
#include <EASTL\vector.h>

namespace Sporepedia
{
	namespace OTDB
	{
		struct Parameter
		{
			enum ParamTypes
			{
				kInt = 0x2E1A75D,
				kFloat = 0x2E1A7FF
			};

			/* 00h */	uint32_t paramID;
			/* 04h */	uint32_t type;
			/* 08h */	union {
				int valueInt;
				float valueFloat;
			};

			static Parameter Int(uint32_t paramID, int value);
			static Parameter Float(uint32_t paramID, float value);
		};
		ASSERT_SIZE(Parameter, 0xC);

		class ParameterResource
			: public Resource::ResourceObject
		{
		public:
			static const uint32_t TYPE = 0x670DA17;
			static const uint32_t RESOURCE_TYPE = 0x2D5C9AF;  // .summary

			/* 14h */	int field_14;
			/* 18h */	vector<Parameter> mParameters;
		};
		ASSERT_SIZE(ParameterResource, 0x2C);

		struct QueryParameter
		{
			/* 00h */	uint32_t paramID;
			/* 04h */	uint32_t type;  // 0x2E1A7FF
			union {
				struct {
					/* 08h */	float fminValue;
					/* 0Ch */	float fmaxValue;
				};
				struct {
					/* 08h */	int iminValue;
					/* 0Ch */	int imaxValue;
				};
			};
			/* 10h */	vector<QueryParameter> field_10;

			static QueryParameter Int(uint32_t paramID, int minValue, int maxValue);
			static QueryParameter Float(uint32_t paramID, float minValue, float maxValue);
		};
		ASSERT_SIZE(QueryParameter, 0x24);

		// 0x165E841 messageID for saving summary, receives resourcekey


		namespace Parameters
		{
			enum : uint32_t
			{
				type = 0x2DD90AF,
				subtype = 0x2DC9D1E,
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

		inline Parameter Parameter::Int(uint32_t paramID, int value)
		{
			Parameter p;
			p.paramID = paramID;
			p.type = Parameter::kInt;
			p.valueInt = value;
			return p;
		}
		inline Parameter Parameter::Float(uint32_t paramID, float value)
		{
			Parameter p;
			p.paramID = paramID;
			p.type = Parameter::kFloat;
			p.valueFloat = value;
			return p;
		}

		inline QueryParameter QueryParameter::Int(uint32_t paramID, int minValue, int maxValue)
		{
			QueryParameter p;
			p.paramID = paramID;
			p.type = Parameter::kInt;
			p.iminValue = minValue;
			p.imaxValue = maxValue;
			return p;
		}
		inline QueryParameter QueryParameter::Float(uint32_t paramID, float minValue, float maxValue)
		{
			QueryParameter p;
			p.paramID = paramID;
			p.type = Parameter::kFloat;
			p.fminValue = minValue;
			p.fmaxValue = maxValue;
			return p;
		}
	}
}

typedef Sporepedia::OTDB::Parameter OTDBParameter;
typedef Sporepedia::OTDB::QueryParameter OTDBQueryParameter;