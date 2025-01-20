#ifndef MODAPI_DLL_EXPORT
#include <Spore\UI\GameSettings.h>
#include <Spore\UI\EditorNamePanel.h>
#include <Spore\UI\cSPAssetView.h>
#include <Spore\UI\AssetDiscoveryCard.h>
#include <Spore\UI\SimulatorRollovers.h>

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


	cSPAssetView::cSPAssetView() {
		CALL(GetAddress(cSPAssetView, _ctor), void, Args(cSPAssetView*), Args(this));
	}
	// Leave empty implementations for everything, as these methods are never called
	// We sue Spore's vftable by calling the original constructor

	int cSPAssetView::AddRef() {
		return DefaultRefCounted::AddRef();
	}
	int cSPAssetView::Release() {
		return DefaultRefCounted::Release();
	}
	void* cSPAssetView::Cast(uint32_t) const {
		return 0;
	}
	int cSPAssetView::GetEventFlags() const {
		return 0;
	}
	bool cSPAssetView::HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) {
		return false;
	}

	void cSPAssetView::Load(UTFWin::IWindow* window, Sporepedia::IAssetData* assetData, bool, bool) {
	}
	void cSPAssetView::func20h() {
	}
	void cSPAssetView::func24h(int, int) {
	}
	void cSPAssetView::SetVisible(bool visible) {
	}

	auto_METHOD_(cSPAssetView, bool, sub_6590A0);

	AssetDiscoveryCard::AssetDiscoveryCard()
		: mLayout()
		, mAssetData()
		, mAssetView()
		, mContainerWindow()
		, mAssetWindow()
	{
	}


	auto_STATIC_METHOD(SimulatorRollover, SimulatorRolloverID, GetRolloverIdForObject,
		Args(Simulator::cGameData* object), Args(object));

	auto_STATIC_METHOD_VOID(SimulatorRollover, ShowRollover,
		Args(Simulator::cGameData* object), Args(object));
	
	auto_STATIC_METHOD(SimulatorRollover, SimulatorRollover*, ShowRolloverInternal,
		Args(Simulator::cGameData* object, SimulatorRolloverID rolloverId, float unk), Args(object, rolloverId, unk));
}
#endif