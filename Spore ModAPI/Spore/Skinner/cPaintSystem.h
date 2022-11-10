#pragma once

#include <Spore\Skinner\cSkinPainter.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\cJob.h>
#include <Spore\MathUtils.h>
#include <EASTL\fixed_vector.h>

#define PaintSystem (*Skinner::cPaintSystem::Get())

namespace Skinner
{
	class cPaintSystem
		: public App::IMessageListener
		, public RefCountTemplate
	{
	public:
		static cPaintSystem* Get();

		/* 0Ch */	cSkinPainter* mpPainter;
		/* 10h */	int field_10;
		/* 14h */	int mpMeshAORender;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int field_20;  // not initialized
		/* 24h */	Math::BoundingBox field_24;
		/* 3Ch */	eastl::vector<int> field_3C;
		/* 50h */	char padding_50[0x80 - 0x50];
		/* 80h */	eastl::vector<int> field_80;
		/* 94h */	eastl::fixed_vector<int, 16> field_94;
		/* ECh */	int field_EC;  // not initialized
		/* F0h */	int field_F0;
		/* F4h */	int field_F4;
		/* F8h */	cJobPtr field_F8;
		/* FCh */	cJobPtr mpUVUnwrapJob;
		/* 100h */	int field_100;
		/* 104h */	int field_104;
	};
	ASSERT_SIZE(cPaintSystem, 0x108);

	namespace Addresses(cPaintSystem)
	{
		DeclareAddress(Get);  // 0x401080 TODO
	}
}