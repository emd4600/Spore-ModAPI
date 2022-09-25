#pragma once

#include <Spore\Simulator\cScenarioData.h>
#include <Spore\Simulator\cScenarioResource.h>
#include <Spore\Simulator\cScenarioTerraformMode.h>


#define ScenarioEditHistory (*Simulator::cScenarioEditHistory::Get())

#define IScenarioEditHistoryEntryPtr eastl::intrusive_ptr<Simulator::IScenarioEditHistoryEntry>

namespace Simulator
{
	/// A generic entry of undo/redo history in the adventure editor.
	class IScenarioEditHistoryEntry : public Object
	{
	public:
		static const uint32_t TYPE = 0x73E4EFE;

		/* 10h */	virtual void Undo() = 0;
		/* 14h */	virtual void Redo() = 0;
	};

	/// Undo/redo history entry for terraform (or planet color, etc) actions.
	class cScenarioTerraformHistoryEntry
		: public IScenarioEditHistoryEntry
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x73E4F04;

	public:
		/* 0Ch */	PropertyListPtr mpPropList;
		/* 10h */	vector<int> field_10;
		/* 24h */	PropertyListPtr field_24;
		/* 28h */	vector<int> field_28;
		/* 3Ch */	cScenarioTerraformMode* mpTerraformMode;  // scenario planet?
	};
	ASSERT_SIZE(cScenarioTerraformHistoryEntry, 0x40);

	/// Undo/redo history entry for scenario data actions (anything related with objects, creatures, etc), that is, 
	/// changes to the cScenarioResource.
	class cScenarioDataHistoryEntry
		: public IScenarioEditHistoryEntry
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x743BB11;

	public:
		/* 0Ch */	cScenarioData* mpParent;
		/* 10h */	cScenarioResourcePtr mpUndoResource;
		/* 14h */	cScenarioResourcePtr mpRedoResource;
	};
	ASSERT_SIZE(cScenarioDataHistoryEntry, 0x18);

	/// Class that manages the undo/redo history of the adventure editor.
	/// The history is made up by a vector of "entries" (IScenarioEditHistoryEntry), which are individual actions
	/// that can be undone/redone.
	class cScenarioEditHistory
	{
	public:
		static cScenarioEditHistory* Get();

	public:
		/* 00h */	vector<IScenarioEditHistoryEntryPtr> mEntries;
		/// Index that points to the current entry in `mEntries`
		/* 14h */	int mCurrentIndex;
		/* 18h */	int field_18;  // some count
		/* 1Ch */	int field_1C;  // some count
		/// False if there is a history entry that is being edited and needs to be commited
		/* 20h */	bool mIsNotEditing;
		/// In progress entry being edited, nullptr when there is no editing action in progress
		/* 24h */	IScenarioEditHistoryEntryPtr mEditingEntry;
	};
	ASSERT_SIZE(cScenarioEditHistory, 0x28);

	namespace Addresses(cScenarioEditHistory)
	{
		DeclareAddress(ptr);
	}
}