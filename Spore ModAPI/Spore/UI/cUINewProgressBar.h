#pragma once

#include <Spore\UTFWin\UILayout.h>
#include <Spore\App\PropertyList.h>

#define cUINewProgressBarPtr eastl::intrusive_ptr<UI::cUINewProgressBar>

namespace UI
{
	class cUINewProgressBar
		: public RefCountTemplate
	{
	public:

		/* 08h */	UILayoutPtr mpParentLayout;
		/* 0Ch */	PropertyListPtr mUIConfigPropList;
		/* 10h */	void* mpProgressCursorAnimator;
		/* 14h */	int mSegments[5];
		/* 28h */	float field_28;
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;  // -1
	};
	ASSERT_SIZE(cUINewProgressBar, 0x38);
}
