#pragma once

#include <Spore\UI\CursorAttachment.h>
#include <Spore\LocalizedString.h>
#include <EASTL\map.h>

#define CivCommCursorAttachmentPtr eastl::intrusive_ptr<UI::CivCommCursorAttachment>

namespace UI
{
	/// Class that controls the rollover that shows the relations with another civilization.
	/// Uses the `CivCommRollover.spui` layout.
	/// It gets the localized texts from 0xA14EE9B6
	class CivCommCursorAttachment
		: public UI::CursorAttachment
	{
	public:
		/* 78h */	LocalizedString mTextNationTooBig;
		/* 8Ch */	LocalizedString mTextBoundariesTooClose;
		/* A0h */	LocalizedString mTextThreatToUs;
		/* B4h */	LocalizedString mTextSoothingSong;
		/// [0]: Military, [1]: Economic, [2]: Religious
		/* C8h */	vector<LocalizedString> mTextsYouAreMilitaryNation;
		/* DCh */	map<int, LocalizedString> mRelationshipTexts;
		/* F8h */	int field_F8;
	};
	ASSERT_SIZE(CivCommCursorAttachment, 0x100);
}