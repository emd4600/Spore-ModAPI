#pragma once

#include <Spore\UTFWin\UTFWinObject.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IButton.h>

#define IDialogPtr eastl::intrusive_ptr<UTFWin::IDialog>

namespace UTFWin
{
	class IDialog : public UTFWinObject
	{
	public:
		static const uint32_t TYPE = 0x6F0B8AC9;

		static const uint32_t WinDialog_ID = 0x0f0b8b73;

		/// Returns the UTFWin::IWindow representation of this dialog.
		/* 10h */	virtual IWindow* ToWindow() = 0;

		/* 14h */	virtual int GetDialogFlags() = 0;
		/* 18h */	virtual void SetDialogFlags(int) = 0;
		/* 1Ch */	virtual void SetDialogFlag(int flag, bool value) = 0;
		/* 20h */	virtual void func20h() = 0;
		/* 24h */	virtual void GetMinDimensions(float& minWidth, float& minHeight) = 0;
		/* 28h */	virtual void SetMinDimensions(float minWidth, float minHeight) = 0;
		/* 2Ch */	virtual void GetMaxDimensions(float& maxWidth, float& maxHeight) = 0;
		/* 30h */	virtual void SetMaxDimensions(float maxWidth, float maxHeight) = 0;
		/* 34h */	virtual int* func34h() = 0;
		/* 38h */	virtual void GetClientAreaBorder(union Math::Rectangle& dst) = 0;
		/* 3Ch */	virtual void SetClientAreaBorder(const union Math::Rectangle& border) = 0;
		/* 40h */	virtual const char16_t* GetTitleText() = 0;
		/* 44h */	virtual void SetTitleText(const char16_t* text) = 0;
		/* 48h */	virtual uint32_t GetTitleTextStyle() = 0;
		/* 4Ch */	virtual void SetTitleTextStyle(uint32_t styleID) = 0;
		/* 50h */	virtual Color GetTitleTextColor() = 0;
		/* 54h */	virtual void SetTitleTextColor(Color color) = 0;
		/* 58h */	virtual void GetTitleTextBorder(union Math::Rectangle& dst) = 0;
		/* 5Ch */	virtual void SetTitleTextBorder(const union Math::Rectangle& border) = 0;
		/* 60h */	virtual void GetCloseButtonBorder(union Math::Rectangle& dst) = 0;
		/* 64h */	virtual void SetCloseButtonBorder(const union Math::Rectangle& border) = 0;
		/* 68h */	virtual IButtonDrawable* GetCloseButtonDrawable() = 0;
		/* 6Ch */	virtual void SetCloseButtonDrawable(IButtonDrawable* drawable) = 0;

		// 214h	DialogFlags
		// 224h	CloseButtonDrawable
		// 2E0h	ClientAreaBorder
		// 2F0h TitleTextBorder
		// 300h	CloseButtonBorder
		// 310h MaxWidth
		// 314h	MaxHeight
		// 318h MinWidth
		// 31Ch MinHeight
		// 320h TitleTextColor
		// 324h TitleTextStyle
		// 328h	TitleText

	};
}