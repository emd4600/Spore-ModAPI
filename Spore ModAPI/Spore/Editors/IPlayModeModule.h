#pragma once

#include <Spore\Input.h>

namespace Editors
{
	class IPlayModeModule
	{
	public:
		/* 00h */	virtual ~IPlayModeModule();
		/* 04h */	virtual void Load();
		/* 08h */	virtual void Dispose();
		/* 0Ch */	virtual bool OnEnter();
		/* 10h */	virtual void OnExit();
		/* 14h */	virtual void Update(int deltaTimeMS);
		/* 18h */	virtual bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState);
		/* 1Ch */	virtual bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState);
		/* 20h */	virtual bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState);
		/* 24h */	virtual bool OnKeyDown(int virtualKey, KeyModifiers modifiers);
		/* 28h */	virtual bool OnKeyUp(int virtualKey, KeyModifiers modifiers);
		/* 2Ch */	virtual bool HandleUIButton(uint32_t controlID);
	};
}