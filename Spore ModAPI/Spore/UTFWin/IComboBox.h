#pragma once

#include <Spore\UTFWin\ComboBoxDrawable.h>
#include <Spore\UTFWin\ScrollbarDrawable.h>
#include <EASTL\string.h>

#define IComboBoxPtr eastl::intrusive_ptr<UTFWin::IComboBox>

namespace UTFWin
{
	enum ComboBoxFlags
	{
		/// An outline is drawn around the control when highlighted
		kComboBoxOutline = 0x00000001
	};

	enum class ComboBoxColors
	{
		Foreground = 0,
		Background = 1,
		HighlightedForeground = 2,
		HighlightedBackground = 3,
		SelectedForeground = 4,
		SelectedBackground = 5
	};

	class IComboBox 
		: public UTFWinObject
	{
	public:
		static const uint32_t TYPE = 0x2F5528D9;

		/* 10h */	virtual IWindow* ToWindow() = 0;
		/* 14h */	virtual int GetComboBoxFlags() = 0;
		/* 18h */	virtual void SetComboBoxFlags(int flags) = 0;
		/* 1Ch */	virtual void SetComboBoxFlag(int flag, bool value) = 0;
		/* 24h */	virtual void AddValue(const char16_t* value) = 0;
		/* 24h */	virtual bool InsertValue(int index, const char16_t* value) = 0;
		/* 28h */	virtual void ReserveValues(int count) = 0;
		/* 2Ch */	virtual void ClearValues() = 0;
		/* 30h */	virtual bool SetValue(int index, const char16_t* value) = 0;
		/* 34h */	virtual eastl::string16 GetValue(int index) = 0;
		/* 38h */	virtual int GetIndexOf(const char16_t* value) = 0;
		/* 3Ch */	virtual int GetValueCount() = 0;
		/* 40h */	virtual int GetSelectedValue() = 0;
		/* 44h */	virtual void SetSelectedValue(int index, bool value) = 0;
		/// Set the text foreground and background colors.
		/* 48h */	virtual void SetColor(ComboBoxColors index, Color color) = 0;
		/// Get the text foreground and background colors.
		/* 4Ch */	virtual Color GetColor(ComboBoxColors index) = 0;
		/// Set how many values should be shown at once in the pull-down list.
		/* 50h */	virtual void SetVisibleValuesCount(unsigned int count) = 0;
		/// Get how many values should be shown at once in the pull-down list.
		/* 54h */	virtual unsigned int GetVisibleValuesCount() = 0;
		/// Set the horizontal alignment of the pull-down button within the window area.
		/* 58h */	virtual void SetAlignment(AlignmentH alignment) = 0;
		/// Get the horizontal alignment of the pull-down button within the window area.
		/* 5Ch */	virtual AlignmentH GetAlignment() = 0;
		/// Set custom scrollbar drawable for pull down menu.
		/* 60h */	virtual void SetScrollbarDrawable(IScrollbarDrawable* drawable) = 0;
		/// Get custom scrollbar drawable for pull down menu.
		/* 64h */	virtual IScrollbarDrawable* GetScrollbarDrawable() = 0;
		/// Set the object to render combo box appearance.
		/* 68h */	virtual void SetComboBoxDrawable(IComboBoxDrawable* drawable) = 0;
		/// Get the object to render combo box appearance.
		/* 6Ch */	virtual IComboBoxDrawable* GetComboBoxDrawable() = 0;
	};
}