#pragma once

#include <Spore\RenderWare\KeyframeAnim.h>

namespace RenderWare
{
	struct MorphHandle
	{
		/* 00h */	int mID;
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	float field_C;
		/* 10h */	int field_10;
		/* 14h */	float field_14;
		/* 18h */	int field_18;
		/* 1Ch */	float field_1C;
		/* 20h */	int field_20;
		/* 24h */	float field_24;
		/* 28h */	int field_28;
		/* 2Ch */	float field_2C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
		/// The progress of the moprh animation when no handles have been modified
		/* 38h */	float mDefaultTime;
		/* 3Ch */	KeyframeAnim* mpAnim;

		static const uint32_t TYPE = 0xff0000;
	};
}