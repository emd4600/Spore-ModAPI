#pragma once

#include <Spore\Simulator\cMovableDestructibleOrnament.h>

#define cToolObjectPtr eastl::intrusive_ptr<Simulator::cToolObject>

namespace Simulator
{
	class cToolObject
		: public cMovableDestructibleOrnament
	{
	public:
		static const uint32_t TYPE = 0x4E3FAAF;
		static const uint32_t NOUN_ID = 0x4E3FAB5;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 638h */	int field_638;
		/* 63Ch */	int field_63C;
		/* 640h */	int field_640;
		/* 644h */	int field_644;
		/* 648h */	int field_648;
		/* 64Ch */	int field_64C;
		/* 650h */	int field_650;
		/* 654h */	int field_654;
	};
	ASSERT_SIZE(cToolObject, 0x658);
}