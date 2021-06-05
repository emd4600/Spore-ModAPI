#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>

#define cGameplayMarkerPtr eastl::intrusive_ptr<Simulator::cGameplayMarker>

namespace Simulator
{
	class cGameplayMarker
		: public cGameData
		, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x36BE278;
		static const uint32_t NOUN_ID = 0x36BE27E;

		/* 108h */	uint32_t mType;
		/* 10Ch */	uint32_t mId;
		/* 110h */	uint32_t mDefinitionId;
		union {
			char raw[0x88];
			struct MigrationPoint
			{
				/* 114h */	int field_114;
				/* 118h */	int field_118;
				/* 11Ch */	int field_11C;
				/* 120h */	int field_120;
				/* 124h */	int field_124;
			};
		} mData;
		///* 114h */	char mData[0x88];  // possibly a union
		/* 19Ch */	cGameplayMarkerPtr mpNextMarker;
		/* 1A0h */	cGameplayMarkerPtr mpHeadMarker;
		/* 1A4h */	cGameDataPtr mpAssociatedNoun;
		/* 1A8h */	Vector3 mNounPosition;
		/* 1B4h */	Quaternion mNounOrientation;
		/* 1C4h */	bool mbNounRemoved;
	};
	ASSERT_SIZE(cGameplayMarker, 0x1C8);
}