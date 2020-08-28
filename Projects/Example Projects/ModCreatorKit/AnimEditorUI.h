#pragma once

#include <Spore\BasicIncludes.h>

#define AnimEditorUIPtr intrusive_ptr<AnimEditorUI>

// To avoid repeating UTFWin:: all the time.
using namespace UTFWin;

class AnimEditorUI 
	: public IWinProc
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("AnimEditorUI");
	
	AnimEditorUI();
	~AnimEditorUI();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	
	int GetEventFlags() const override;
	bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

	void Load();

	void GenerateChannels(Anim::SPAnimation* pAnimation);
	
private:
	UILayout mLayout;
	IWindowPtr mpMainWindow;
	IWindowPtr mpChannelsPanel;
	IWindowPtr mpPropertiesPanel;
};
