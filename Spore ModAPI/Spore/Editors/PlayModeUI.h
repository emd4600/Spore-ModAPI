#pragma once

#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\Clock.h>

#define PlayModeUIPtr eastl::intrusive_ptr<Editors::PlayModeUI>

namespace Editors
{
	class cEditor;
	class EditorPlayMode;

	class PlayModeUI
		: public UTFWin::IWinProc
		, public DefaultRefCounted
	{
	public:
		virtual bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

		/// Finds a window with the given control ID in the main PlayMode layout.
		/// @param controlID
		/// @returns
		UTFWin::IWindow* FindWindowByID(uint32_t controlID);

		/// Changes the visibility of a window inside the main PlayMode layout.
		/// @param controlID
		/// @param visible
		void SetWindowVisible(uint32_t controlID, bool visible);

	public:
		/* 0Ch */	cEditor* mpEditor;  // not initialized
		/* 10h */	EditorPlayMode* mpPlayMode;  // not initialized
		/// `PlayMode.spui`
		/* 14h */	UTFWin::UILayout mMainLayout;
		/* 2Ch */	UTFWin::UILayout mCameraControlsLayout;
		/* 44h */	bool field_44;
		/* 45h */	bool field_45;
		/* 48h */	Clock field_48;
		/* 60h */	bool field_60;  // not initialized
		/* 64h */	int field_64;
		/* 68h */	int field_68;
	};
	ASSERT_SIZE(PlayModeUI, 0x70);

	namespace Addresses(PlayModeUI)
	{
		DeclareAddress(HandleUIMessage);  // 0x6374B0 0x6377B0
		DeclareAddress(SetWindowVisible);  // 0x635450 0x635750
		DeclareAddress(FindWindowByID);  // 0x634AB0 0x634DB0
	}
}