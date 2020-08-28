#include "stdafx.h"
#include "AnimEditorUI.h"
#include <Spore\UTFWin\ButtonDrawableStandard.h>

AnimEditorUI::AnimEditorUI()
	: mLayout()
	, mpChannelsPanel()
	, mpPropertiesPanel()
{
}


AnimEditorUI::~AnimEditorUI()
{
}

// For internal use, do not modify.
int AnimEditorUI::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int AnimEditorUI::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* AnimEditorUI::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(AnimEditorUI);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int AnimEditorUI::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool AnimEditorUI::HandleUIMessage(IWindow* window, const Message& message)
{
	//if (id("AnimChannelItem"))
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}

void AnimEditorUI::Load()
{
	mLayout = UILayout();
	if (!mLayout.LoadByID(id("AnimEditorUI")))
	{
		App::ConsolePrintF("Error loading AnimEditorUI.spui");
		return;
	}

	mpMainWindow = mLayout.FindWindowByID(0xFFFFFFFF);
	mpChannelsPanel = mLayout.FindWindowByID(id("channelsPanel"));
	mpPropertiesPanel = mLayout.FindWindowByID(id("propertiesPanel"));
}

void AnimEditorUI::GenerateChannels(Anim::SPAnimation* pAnimation)
{
	const Color buttonColor = 0xFFe6e699;
	const float itemHeight = 24.0;
	const float itemBorder = 3.0;
	float currentY = 0.0f;
	auto area = mpChannelsPanel->GetRealArea();
	float width = area.GetWidth() - 2*itemBorder;
	/*{
		IWindow* button = (IWindow*)ClassManager.Create(IButton::WinButton_ID);
		button->SetCaption(u"Animation");
		button->SetArea({ itemBorder, currentY + itemBorder, itemBorder + width, currentY + itemBorder + itemHeight });
		button->SetFlag(kWinFlagVisible, true);
		button->SetFillColor(buttonColor);
		button->SetDrawable(new ButtonDrawableStandard());
		IButton* = object_cast<IButton>(button);
		mpChannelsPanel->AddWindow(button);
		currentY += itemBorder + itemHeight;
	}*/

	for (int i = 0; i < pAnimation->channelCount; ++i)
	{
		string16 str = string16(pAnimation->pChannels[i]->name);
		IWindow* item = (IWindow*)ClassManager.Create(IButton::WinButton_ID);
		item->SetCaption(str.c_str());
		item->SetArea({ itemBorder, currentY + itemBorder, itemBorder + width, currentY + itemBorder + itemHeight });
		item->SetFlag(kWinFlagVisible, true);
		item->SetFillColor(buttonColor);
		item->SetDrawable(new ButtonDrawableStandard());
		item->SetTextFontID(0x00aebb69);
		IButton* button = object_cast<IButton>(item);
		for (int i = 0; i < 8; ++i) {
			button->SetCaptionColor(StateIndices(i), Color::BLACK);
		}
		mpChannelsPanel->AddWindow(item);
		currentY += itemBorder + itemHeight;
	}
}