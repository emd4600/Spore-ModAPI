#pragma once

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\UTFWinObject.h>
#include <Spore\UTFWin\OutlineFormat.h>

#define ITextPtr intrusive_ptr<UTFWin::IText>

namespace UTFWin
{
	class IText : public UTFWinObject
	{
	public:
		static const uint32_t TYPE = 0xF15F4BD;

		/* 10h */	virtual IWindow* ToWindow() = 0;
		/* 14h */	virtual void func14h(bool) = 0;
		/* 18h */	virtual void func18h(bool) = 0;
		/* 1Ch */	virtual void func1Ch(bool) = 0;
		/* 20h */	virtual Math::Rectangle GetTextBounds(bool, bool) = 0;
		/* 24h */	virtual Color GetTextColor() const = 0;
		/* 28h */	virtual void SetTextColor(Color color) = 0;
		/* 2Ch */	virtual float func2Ch() = 0;
		/* 30h */	virtual void func30h(float) = 0;
		/* 34h */	virtual void GetTextBorders(struct Borders& dst) const = 0;
		/* 38h */	virtual void SetTextBorders(const struct Borders& borders) = 0;
	};
}