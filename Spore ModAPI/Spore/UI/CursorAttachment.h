#pragma once

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\App\Property.h>
#include <EASTL\vector_map.h>
#include <Spore\Clock.h>

#define CursorAttachmentPtr eastl::intrusive_ptr<UI::CursorAttachment>

namespace UI
{
	/// Used to create mouse rollovers (like "tooltips").
	/// Usually this class is inherited to display custom functionality
	/// This class is inherited to create the timeline rollovers, vehicle editor speed/attack/health rollovers,...
	class CursorAttachment
		: public UTFWin::IWinProc
		, public DefaultRefCounted
	{
	public:
		/* 1Ch */	virtual bool Initialize();
		/* 20h */	virtual void func20h();
		/* 24h */	virtual bool Dispose();

	public:
		/* 0Ch */	UTFWin::UILayout mLayout;
		/* 24h */	uint32_t mLayoutInstanceID;  // -1
		/* 28h */	uint32_t mLayoutGroupID;  // -1
		/* 2Ch */	vector_map<int, int> field_2C;  // The structure is int, ObjectPtr, Property ?
		/* 44h */	bool field_44;
		/// Control ID of the main window in the layout
		/* 48h */	uint32_t mMainWindowID;
		/* 4Ch */	float field_4C;  // 1.0
		/* 50h */	Clock field_50;
		/* 68h */	float field_68;  // 1.0e30
		/* 6Ch */	int field_6C;  // not initialized
		/* 70h */	int field_70;  // not initialized
		/* 74h */	bool field_74;  // true
	};
	ASSERT_SIZE(CursorAttachment, 0x78);
}