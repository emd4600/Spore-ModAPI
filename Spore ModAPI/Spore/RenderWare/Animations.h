#pragma once

#include <Spore\RenderWare\KeyframeAnim.h>

namespace RenderWare
{
	struct Animations
	{
		/* 00h */	KeyframeAnim* mpAnims;
		/* 04h */	int mSize;

		static const uint32_t RW_TYPE = 0xff0001;
	};
}