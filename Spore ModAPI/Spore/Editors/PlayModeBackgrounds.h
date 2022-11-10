#pragma once

#include <Spore\Object.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <EASTL\vector.h>

namespace Editors
{
	class EditorPlayModeBackground
		: public DefaultRefCounted
	{
	public:
		/* 08h */	uint32_t mEntryEffectID;
		/* 0Ch */	uint32_t mThumbnailID;
		/* 10h */	int mOrder;
		/* 14h */	uint32_t mLightingID;
	};
	ASSERT_SIZE(EditorPlayModeBackground, 0x18);

	class PlayModeBackgrounds
		: public IVirtual
	{
	public:
		// These functions cannot be called, they are here for detouring
		void SwitchBackground();
		void DisableBackground();

		/* 04h */	eastl::vector<eastl::intrusive_ptr<EditorPlayModeBackground>> mBackgrounds;
		/* 18h */	int mCurrentIndex;
		/* 1Ch */	int mTargetIndex;
		/* 20h */	uint32_t mCurrentEntryEffectID;
		/* 24h */	uint32_t mTargetEntryEffectID;
		/* 28h */	uint32_t mCrossFadeSnapEffectID;
		/* 2Ch */	uint32_t mPlayModeEntryEffectID;
		/* 30h */	int field_30;
		/* 34h */	int field_34;  // something related with UI
		/* 38h */	int mCurrentPageIndex;
		/* 3Ch */	int mPageCount;
		/* 40h */	ILightingWorldPtr mpLightingWorld;
		/* 44h */	bool field_44;
	};
	ASSERT_SIZE(PlayModeBackgrounds, 0x48);

	namespace Addresses(PlayModeBackgrounds)
	{
		DeclareAddress(SwitchBackground);
		DeclareAddress(DisableBackground);
	}
}