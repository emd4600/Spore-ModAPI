#pragma once

#include <Spore\Object.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Editors\PlayModeUI.h>
#include <EASTL\vector.h>

#define EditorPlayModeBackgroundPtr eastl::intrusive_ptr<Editors::EditorPlayModeBackground>

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
		void SwitchBackground();
		void DisableBackground();

		void Load(PlayModeUI* playModeUI, uint32_t entryEffectID, uint32_t crossFadeSnapEffectID, Graphics::ILightingWorld* lightingWorld, int8_t backgroundSet);

		void LoadBackgroudFiles(int8_t backgroundSet);

		bool HandleUIButton(uint32_t controlID);

		void ToggleBackgroundButtonHighlights(uint32_t backgroundButtonID);

		void UpdatePageNumbers();

		void UpdateBackgroundButtons();

		/// Returns true if the current background has `mOrder == 4`, which is assumed to be the black background.
		bool IsBlackBackground();

	public:
		/* 04h */	eastl::vector<EditorPlayModeBackgroundPtr> mBackgrounds;
		/* 18h */	int mCurrentIndex;
		/* 1Ch */	int mTargetIndex;
		/* 20h */	uint32_t mCurrentEntryEffectID;
		/* 24h */	uint32_t mTargetEntryEffectID;
		/* 28h */	uint32_t mCrossFadeSnapEffectID;
		/* 2Ch */	uint32_t mPlayModeEntryEffectID;
		/* 30h */	bool field_30;
		/* 34h */	PlayModeUI* mpPlayModeUI;
		/* 38h */	int mCurrentPageIndex;
		/// The total number of pages is this + 1
		/* 3Ch */	int mExtraPageCount;
		/* 40h */	Graphics::ILightingWorld* mpLightingWorld;
		/* 44h */	bool mIsSwitchingBackground;
	};
	ASSERT_SIZE(PlayModeBackgrounds, 0x48);

	namespace Addresses(PlayModeBackgrounds)
	{
		DeclareAddress(SwitchBackground);
		DeclareAddress(DisableBackground);
		DeclareAddress(Load);  // 0x62FC70 0x62FCC0
		DeclareAddress(LoadBackgroudFiles);  // 0x62FBA0 0x62FBF0
		DeclareAddress(HandleUIButton);  // 0x62F7D0 0x62F820
		DeclareAddress(ToggleBackgroundButtonHighlights);  // 0x62F320 0x62F370
		DeclareAddress(UpdatePageNumbers);  // 0x62F520 0x62F570
		DeclareAddress(UpdateBackgroundButtons);  // 0x62F6C0 0x62F710
		DeclareAddress(IsBlackBackground);  // 0x62F6A0 0x62F6F0
	}
}