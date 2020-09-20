#ifndef MODAPI_DLL_EXPORT
#include <Spore\UI\GameSettings.h>
#include <Spore\UI\EditorNamePanel.h>

namespace UI
{
	auto_STATIC_METHOD(GameSettings, bool, Show, Args(uint32_t gameModeID), Args(gameModeID));

	EditorNamePanel::EditorNamePanel()
		: field_10()
		, field_11(true)
		, mpValidationWinProc()
		, mpLayout()
		, mpNameableEntity()
		, mRandomNameType()
		, field_24()
		, mpContainerWindow()
	{
	}

	EditorNamePanel::~EditorNamePanel() {}

	int EditorNamePanel::AddRef() {
		return DefaultRefCounted::AddRef();
	}

	int EditorNamePanel::Release() {
		return DefaultRefCounted::Release();
	}

	void* EditorNamePanel::Cast(uint32_t type) const {
		CLASS_CAST(EditorNamePanel);
		CLASS_CAST(UTFWin::IWinProc);
		CLASS_CAST(Object);
		return nullptr;
	}

	int EditorNamePanel::GetEventFlags() const
	{
		return UTFWin::kEventFlagAdvanced | UTFWin::kEventFlagBasicInput;
	}

	auto_METHOD_VIRTUAL_VOID(EditorNamePanel, EditorNamePanel, SetExtended, Args(bool value), Args(value));
	auto_METHOD_VIRTUAL(EditorNamePanel, UTFWin::IWinProc, bool, HandleUIMessage,
		Args(UTFWin::IWindow* pWindow, const UTFWin::Message& message), Args(pWindow, message));
	
	auto_METHOD_VIRTUAL(EditorNamePanel, App::IMessageListener, bool, HandleMessage, 
		Args(uint32_t messageID, void* msg), Args(messageID, msg));

	auto_METHOD_VOID(EditorNamePanel, Initialize,
		Args(Editors::INameableEntity* pEntity, UTFWin::IWindow* pContainer, uint32_t layoutID, bool arg, uint32_t randomNameType),
		Args(pEntity, pContainer, layoutID, arg, randomNameType));

	auto_METHOD_VOID_(EditorNamePanel, Dispose);
}
#endif