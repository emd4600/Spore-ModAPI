/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once

#include <Spore\UTFWin\InteractiveWindow.h>
#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\TreeNode.h>

#include <Spore\Timer.h>

namespace UTFWin
{

	class ITreeView : public UTFWinObject
	{
	public:
		static const uint32_t TYPE = 0xB02AECEC;

		enum
		{
			kColorText = 0,
			kColorBackground = 1,
			kColorDisabledText = 2,
			kColorDisabledBackground = 3,
			kColorSelectedText = 4,
			kColorSelectedBackground = 5,
			kColorHighlightedText = 6,
			kColorHighlightedBackground = 7,
			kColorConnectorLines = 8,

		};

		enum
		{
			kParamIndentWidth = 0,
			kParamLineWidth = 1,
			kParamLineIndent = 2,
			kParamIconSpacing = 3
		};

		/* 10h */	virtual IWindow* ToWindow() = 0;

		///
		/// Gets the color used for the specific component.
		/// @param index The component, in the ITreeView::kColor... values
		///
		/* 14h */	virtual Color GetColor(int index) const = 0;

		///
		/// Sets the color used for the specific component.
		/// @param index The component, in the ITreeView::kColor... values
		/// @param color The new color value.
		///
		/* 18h */	virtual void SetColor(int index, Color color) = 0;

		///
		/// Gets the width of the borders.
		///
		/* 1Ch */	virtual const Math::Rectangle& GetBorderWidth() const = 0;

		///
		/// Sets the width of the borders.
		/// @param value A Rectangle with the new borders width.
		///
		/* 20h */	virtual void SetBorderWidth(const Math::Rectangle& value) = 0;

		///
		/// Sets the value of the specified tree view flag. The flag must be one of the ITreeView::kFlag... values.
		/// @param flag The flag to set, one of the ITreeView::kFlag... values.
		/// @param value The new bool value of that flag.
		///
		/* 24h */	virtual void SetTreeViewFlag(int flag, bool value) = 0;

		///
		/// Gets the value of the tree view flags, which are the ITreeView::kFlag... values.
		///
		/* 28h */	virtual bool GetTreeViewFlags() const = 0;

		///
		/// Sets the height of individual rows.
		/// @param value The new row height.
		/// 
		/* 2Ch */	virtual void SetItemHeight(size_t value) = 0;

		///
		/// Gets the height of individual rows.
		///
		/* 30h */	virtual size_t GetItemHeight() const = 0;

		///
		/// Chagnes the value of the specified parameter, which can be one of the following:
		/// ITreeView::kParamIdentWidth, ITreeView::kParamLineWidth, ITreeView::kParamLineIndent and ITreeView::kParamIconSpacing
		/// @param paramIndex The parameter to change.
		/// @param value The new value of the parameter.
		///
		/* 34h */	virtual void SetParameter(int paramIndex, size_t value) = 0;

		///
		/// Gets the value of the specified parameter, which can be one of the following:
		/// ITreeView::kParamIdentWidth, ITreeView::kParamLineWidth, ITreeView::kParamLineIndent and ITreeView::kParamIconSpacing
		/// @param paramIndex The parameter whose value will be returned.
		///
		/* 38h */	virtual size_t GetParameter(int paramIndex) = 0;

		///
		/// Sets the icon that is drawn by default on each item.
		/// @param pIconDrawable The IDrawable that will render the icon.
		/// 
		/* 3Ch */	virtual void SetDefaultIcon(IDrawable* pIconDrawable) = 0;

		///
		/// Gets the icon that is drawn by default on each item.
		/// 
		/* 40h */	virtual IDrawable* GetDefaultIcon() const = 0;

		///
		/// Sets the IDrawable of the expander button that is rendered before every icon.
		/// @param pExpanderDrawable The IDrawable that will render the icon (usually a TreeExpanderDrawable)
		/// 
		/* 44h */	virtual void SetExpanderDrawable(IDrawable* pExpanderDrawable) = 0;

		///
		/// Gets the IDrawable of the expander button that is rendered before every icon.
		/// 
		/* 48h */	virtual IDrawable* GetExpanderDrawable() const = 0;


		/* 4Ch */	virtual TreeNode& GetRootNode() = 0;
	};

	class WinTreeView : public InteractiveWindow, public ITreeView
	{
	public:
		using InteractiveWindow::AddRef;
		using InteractiveWindow::Release;
		using InteractiveWindow::Cast;

		enum
		{
			kScrollbarNever = 0,
			kScrollbarAsNeeded = 1,
			kScrollbarAlways = 2,
		};

		TreeNode* GetSelectedNode();

	protected:
		class Scrollbar
		{
			/* 00h */	IDrawablePtr mpDrawable;
			/* 04h */	int mnDisplayPolicy;
			/* 08h */	int field_08;  // not initialized
			/* 0Ch */	int field_0C;  // not initialized
			/* 10h */	ObjectPtr field_10;
		};
		ASSERT_SIZE(Scrollbar, 0x14);

		/* 210h */	bool field_210;
		/* 214h */	TreeNode mRootNode;
		/* 264h */	Math::Rectangle mBorderWidth;
		/* 274h */	Math::Rectangle field_274;
		/* 284h */	int mTreeViewFlags;  // 0x0B
		/* 288h */	Color mColors[9];
		/* 2ACh */	size_t mnItemHeight;
		/* 2B0h */	IDrawablePtr mpDefaultIcon;
		/* 2B4h */	IDrawablePtr mpExpanderDrawable;
		/* 2B8h */	size_t mnIndentWidth;  // 0x18
		/* 2BCh */	size_t mnLineWidth;  // 2
		/* 2C0h */	size_t mnLineIndent;  // 8
		/* 2C4h */	size_t mnIconSpacing;  // 4
		/* 2C8h */	Math::Dimensions mExpanderDimensions;
		/* 2D0h */	float field_2D0;
		/* 2D4h */	eastl::vector<int> field_2D4;
		/* 2E8h */	int field_2E8;
		/* 2ECh */	TreeNode* field_2EC;  // selected TreeNode?
		/* 2F0h */	int field_2F0;
		/* 2F4h */	ObjectPtr field_2F4;
		/* 2F8h */	Scrollbar field_2F8;
		/* 30Ch */	Scrollbar field_30C;
		char padding_320[0x10];
		/* 330h */	Timer field_330;
		/* 348h */	Timer field_348;
		/* 360h */	float field_360;
		/* 364h */	int field_364;  // not initialized
	};
	ASSERT_SIZE(WinTreeView, 0x368);

	inline TreeNode* WinTreeView::GetSelectedNode()
	{
		return field_2EC;
	}
}