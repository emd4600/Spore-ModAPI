#pragma once

#include <Spore\App\PropertyList.h>

#define EditorAnimationsPtr eastl::intrusive_ptr<Editors::EditorAnimations>

namespace Editors
{
	class EditorAnimations
		: public DefaultRefCounted
		, public Object
	{
	public:
		static const uint32_t TYPE = 0x7150F635;

	public:
		/* 0Ch */	eastl::vector<PropertyListPtr> mPropLists;
	};
	ASSERT_SIZE(EditorAnimations, 0x20);
}