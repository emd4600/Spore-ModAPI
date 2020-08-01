#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\App\PropertyList.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\UILayout.h>

/// The system that manages event logs. For more info, check Simulator::cUIEventLog
#define UIEventLog (*Simulator::cUIEventLog::Get())

namespace Simulator
{
	struct UnkRefCounted
	{
		virtual int AddRef();
		virtual int Release();
		virtual ~UnkRefCounted();
	};

	class cFeedbackEvent
		: UnkRefCounted
		, public DefaultRefCounted
	{
	public:
		/* 0Ch */	int mFlags;  // 100h has layout
		/* 10h */	int mEventCategoryIndex;
		/* 14h */	int mEventAwardSubCategoryIndex;
		/* 18h */	float field_18;  // 1.0
		/* 1Ch */	int field_1C;  // 255
		/* 20h */	Vector3 field_20;
		/* 2Ch */	float field_2C;
		/* 30h */	int field_30;  // not initialized
		/* 34h */	float mEventStartFadeTime;  // 10.0
		/* 38h */	float mEventRemoveTime;  // -1.0
		/* 3Ch */	int field_3C;  // not initialized
		/* 40h */	bool mEventRemoveOnContextChange;  // not initialized
		/* 44h */	int mCurrentContext;  // not initialized
		/* 48h */	uint32_t mCommandID;
		/* 4Ch */	uint32_t field_4C;
		/* 50h */	int field_50;
		/* 54h */	int field_54;  // not initialized
		/* 58h */	ObjectPtr field_58;
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	string16 mEventDescription;
		/* 78h */	UTFWin::UILayout* mpItemLayout;
		/* 7Ch */	int field_7C;
		/* 80h */	int field_80[4];  // not initialized
		/* 90h */	float field_90;  // 200.0
	};
	ASSERT_SIZE(cFeedbackEvent, 0x94);

	/// This class manages event logs in Simulator game modes. Event logs are small alerts shown on the left side of the screen,
	/// such as "There's a ecodisaster in this planet!". An example of usage of this class:
	/// ```cpp
	/// UIEventLog.ShowEvent(id("PirateAmbush"), GroupIDs::SpacePopups);
	/// ```
	/// The ShowEvent() method returns an ID that identifies that event log. Sometimes it's useful to save that ID to use it
	/// in other methods. For example, you can use it to change the text of the event log:
	/// ```cpp
	/// uint32_t eventID = UIEventLog.ShowEvent(id("GenericMissionProgress"), GroupIDs::SpacePopups);
	/// UIEventLog.SetDescription(eventID, u"The mission is almost complete!");
	/// ```
	class cUIEventLog
		: public UTFWin::IWinProc
		, public cStrategy
	{
	public:
		/// Shows an event log item, with the given instance and group ID. This method returns an ID that uniquely identifies
		/// the event log item created by this method; that id can be used in other methods.
		/// @param instanceID The ID of the prop file used for this event.
		/// @param groupID The ID of the folder of the prop file, usually GroupIDs::SpacePopups or GroupIDs::CivPopups.
		/// @param dontAllowDuplicates If the prop file doesn't define `eventAllowDuplicates`, this parameter will be used to know
		/// if you can't have more than one event of that same prop.
		/// @param
		uint32_t ShowEvent(uint32_t instanceID, uint32_t groupID, int=0, Vector3* = nullptr, bool dontAllowDuplicates = true, int=0);

		/// Hides an event log, either totally or partially. Hiding it partially (second parameter set to `true`)
		/// means the icon still shows; if oyu hide it totally, you delete the event completely.
		/// @param eventID The ID of the event, as returned by ShowEvent()
		/// @param partially If true, only the text is hidden; if false, the entire event item is destroyed
		void HideEvent(uint32_t eventID, bool partially);

		/// Changes the description text of the event log.
		/// @param eventID The ID of the event, as returned by ShowEvent()
		/// @param pText The new text of the event.
		void SetDescription(uint32_t eventID, const char16_t* pText);

		/// Changes the visibility of all the event log items. 
		/// @param visible
		void SetVisible(bool visible);

		static cUIEventLog* Get();

	protected:
		/* 20h */	int field_20;  // 255
		/* 24h */	bool field_24;  // true
		/* 28h */	map<uint32_t, intrusive_ptr<cFeedbackEvent>> mEvents;
		/* 44h */	int field_44;
		/* 48h */	float field_48;
		/* 4Ch */	char padding_4C[0x10];
		/* 5Ch */	float field_5C;
		/* 60h */	float field_60;
		/* 64h */	int field_64;
		/* 68h */	int field_68;  // UI::Animator*
		/* 6Ch */	PropertyListPtr mpPropList;  // global~!ui
	};
	ASSERT_SIZE(cUIEventLog, 0x70);

	namespace Addresses(cUIEventLog)
	{
		DeclareAddress(Get);
		DeclareAddress(ShowEvent);
		DeclareAddress(SetDescription);
		DeclareAddress(HideEvent);
		DeclareAddress(SetVisible);
	}
}