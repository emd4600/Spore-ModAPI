#ifndef MODAPI_DLL_EXPORT
#include <Spore\Palettes\IItemFrameUI.h>
#include <Spore\App\IMessageManager.h>
#include <Spore\Audio\AudioSystem.h>
#include <Spore\UTFWin\IWindowManager.h>
#include <Spore\Input.h>

namespace Palettes
{
	int UnkItemFrameMessage::AddRef() {
		++mnRefCount;
		return mnRefCount;
	}

	int UnkItemFrameMessage::Release() {
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}


	IItemFrameUI::IItemFrameUI()
		: mpItem()
		, mFrameTypeID(0xFFFFFFFF)
	{
	}

	DefaultItemFrameUI::DefaultItemFrameUI()
		: field_14()
		, mIsHovering()
		, mpWindow()
	{
	}

	void DefaultItemFrameUI::Initialize(PaletteItem* pItem, UTFWin::IWindow* pWindow, UTFWin::IWindow* pItemsPanel, PaletteInfo*)
	{
		mpItem = pItem;
		mpWindow = pWindow;
		mpWindow->AddWinProc(this);
	}
	void DefaultItemFrameUI::Dispose()
	{
		if (mpWindow) {
			mpWindow->RemoveWinProc(this);
			mpWindow = nullptr;
		}
		if (mpItem) {
			mpItem->field_50 = nullptr;
			mpItem = nullptr;
		}
		mIsHovering = false;
	}

	void DefaultItemFrameUI::SetPaletteItem(PaletteItem* pItem)
	{
		this->mpItem = pItem;
	}
	PaletteItem* DefaultItemFrameUI::GetPaletteItem()
	{
		return mpItem.get();
	}

	void DefaultItemFrameUI::func14h() 
	{
		UnkItemFrameMessage message;
		message.messageID = 0xB2E18705;
		message.frameTypeID = mFrameTypeID;
		message.field_20 = object_cast<Object>(GetPaletteItem());

		MessageManager.PostMSG(message.messageID, &message);
	}

	void DefaultItemFrameUI::Update(int dt) {
	}

	void DefaultItemFrameUI::OnMouseEnter() {
		int message[4];
		message[0] = (int)static_cast<UTFWin::IWinProc*>(this);
		message[2] = 0x522F9CD;

		MessageManager.PostMSG(message[2], message);
	}
	void DefaultItemFrameUI::OnMouseLeave() {
		int message[4];
		message[0] = (int)static_cast<UTFWin::IWinProc*>(this);
		message[2] = 0x522F9CE;

		MessageManager.PostMSG(message[2], message);
	}

	void DefaultItemFrameUI::OnMouseDown() {
	}
	void DefaultItemFrameUI::OnMouseUp() {
	}

	void DefaultItemFrameUI::SetVisible(bool visible)
	{
		if (mpWindow) {
			mpWindow->SetFlag(UTFWin::kWinFlagVisible, visible);
		}
	}


	int DefaultItemFrameUI::AddRef() {
		return DefaultRefCounted::AddRef();
	}
	int DefaultItemFrameUI::Release() {
		return DefaultRefCounted::Release();
	}
	void* DefaultItemFrameUI::Cast(uint32_t type) const {
		CLASS_CAST(IItemFrameUI);
		CLASS_CAST(DefaultItemFrameUI);
		CLASS_CAST(IWinProc);
		CLASS_CAST(Object);
		return nullptr;
	}


	int DefaultItemFrameUI::GetEventFlags() const
	{
		return UTFWin::kEventFlagBasicInput | UTFWin::kEventRefresh;
	}

	bool DefaultItemFrameUI::HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message)
	{
		switch (message.eventType) 
		{
		case UTFWin::kMsgMouseDown:
			if (message.Mouse.IsLeftButton())
				this->OnMouseDown();
			return false;

		case UTFWin::kMsgMouseUp:
			if (message.Mouse.IsLeftButton()) {
				this->OnMouseUp();
				Audio::PlayAudio(0xA03E74B2);
			}
			return false;

		case UTFWin::kMsgMouseEnter:
			if (message.MouseEnter.field_0C == 1 && !this->mIsHovering) {
				if (!GameInput::IsMouseButtonDown(MouseButton::kMouseButtonLeft) &&
					!GameInput::IsMouseButtonDown(MouseButton::kMouseButtonRight) &&
					!GameInput::IsMouseButtonDown(MouseButton::kMouseButtonWheel)) {
					this->OnMouseEnter();
				}
			}
			return false;

		case UTFWin::kMsgMouseLeave:
			if (message.MouseEnter.field_0C == 1 && this->mIsHovering) {
				if (WindowManager.GetMainWindowIndex(1)->IsAncestorOf(mpWindow.get())) {
					this->OnMouseLeave();
				}
			}
			return false;

		default:
			return false;
		}
	}
}
#endif