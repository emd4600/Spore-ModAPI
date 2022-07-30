#pragma once

#include <Spore\Simulator\cSpaceInventoryItem.h>
#include <Spore\Simulator\cSpeciesProfile.h>

#define cPlantCargoInfoPtr eastl::intrusive_ptr<Simulator::cPlantCargoInfo>

namespace Simulator
{
	// created with function B8FB80?
	class cPlantCargoInfo
		: public cSpaceInventoryItem
	{
	public:
		static const uint32_t TYPE = 0x70A2863C;

	public:
		/* 7Ch */	uint32_t mModelIDLOD0;
		/* 80h */	uint32_t mModelIDLOD1;
		/* 84h */	uint32_t mModelIDLOD2;
		/* 88h */	uint32_t mModelIDLOD3;
		/* 8Ch */	uint32_t mAlphaModel;
		/* 90h */	float field_90;  // 2.0
		/* 94h */	float mBaseRadius;
		/* 98h */	float mCanopyRadius;
		/* 9Ch */	float mHeight;
		/* A0h */	int field_A0;  //species profile? //TODO what is this type?
	};
	ASSERT_SIZE(cPlantCargoInfo, 0xA4);
}