#pragma once

#include <Spore\Editors\INameableEntity.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\UILayout.h>

#define EditorNamePanelPtr eastl::intrusive_ptr<UI::EditorNamePanel>

namespace UI
{
	class EditorNamePanel
		: public UTFWin::IWinProc
		, public App::IMessageListener
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0xB037A53E;

		EditorNamePanel();
		~EditorNamePanel();

		/// Creates a functional renaming UI for a nameable entity (eg Tribes and Cities)
		/// allowRename when set to false will gray-out the name field
		/// randomNameType when set to 0x0 will hide the randomization button
		void Initialize(Editors::INameableEntity* pEntity, UTFWin::IWindow* pContainer, uint32_t layoutID,
			bool allowRename = true, uint32_t randomNameType = 0x0);
		void Dispose();

		virtual void SetExtended(bool extended);

		virtual int GetEventFlags() const override;
		virtual bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

		virtual bool HandleMessage(uint32_t messageID, void* msg) override;

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

	public:
		/* 10h */	bool field_10;
		/* 11h */	bool field_11;  // true
		/* 14h */	IWinProcPtr mpValidationWinProc;
		/* 18h */	UILayoutPtr mpLayout;
		/* 1Ch */	Editors::INameableEntity* mpNameableEntity;
		/* 20h */	uint32_t mRandomNameType;
		/* 24h */	eastl::string16 field_24;
		/* 34h */	UTFWin::IWindow* mpContainerWindow;
	};
	ASSERT_SIZE(EditorNamePanel, 0x38);

	namespace Addresses(EditorNamePanel)
	{
		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(HandleUIMessage);
		DeclareAddress(SetExtended);
		DeclareAddress(HandleMessage);
	}
}