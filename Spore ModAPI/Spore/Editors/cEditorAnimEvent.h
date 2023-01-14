#pragma once

#include <Spore\Editors\EditorModel.h>
#include <Spore\App\IMessageRC.h>
#include <Spore\Object.h>

#define cEditorAnimEventPtr eastl::intrusive_ptr<Editors::cEditorAnimEvent>

namespace Editors
{
	class cEditorAnimEvent
		: public App::IMessageRC
		, public DefaultRefCounted
	{
	public:
		static const uint32_t MESSAGE_ID = 0xD1511790;

		cEditorAnimEvent();

		virtual int AddRef() override;
		virtual int Release() override;
		virtual int GetReferenceCount() override;

		void MessageSend(uint32_t eventID, int, EditorModel* editorModel, int = 0, bool = false, float = 0.0f, bool = false, int = -1, float = 1.0f);
		void MessagePost(uint32_t eventID, int, EditorModel* editorModel, int = 0, bool = false, float = 0.0f, bool = false, int = -1, float = 1.0f);

	public:
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	EditorModel* mpEditorModel;
		/* 18h */	uint32_t mEventID;
		/* 1Ch */	bool field_1C;
		/* 20h */	float field_20;
		/* 24h */	bool field_24;
		/* 28h */	int field_28;  // -1
		/* 2Ch */	float field_2C;  // 1.0
	};
	ASSERT_SIZE(cEditorAnimEvent, 0x30);

	namespace Addresses(cEditorAnimEvent)
	{
		DeclareAddress(MessageSend);  // 0x59D610 0x59D8B0
		DeclareAddress(MessagePost);  // 0x59D5A0 0x59D840
	}
}