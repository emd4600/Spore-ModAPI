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
#include <Spore\UTFWin\ITreeView.h>
#include <Spore\Clock.h>

namespace UTFWin
{

	class WinTreeView : public InteractiveWindow, public ITreeView
	{
	public:
		using InteractiveWindow::AddRef;
		using InteractiveWindow::Release;
		using InteractiveWindow::Cast;

		enum ScrollbarMode
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
		/* 330h */	Clock field_330;
		/* 348h */	Clock field_348;
		/* 360h */	float field_360;
		/* 364h */	int field_364;  // not initialized
	};
	ASSERT_SIZE(WinTreeView, 0x368);

	inline TreeNode* WinTreeView::GetSelectedNode()
	{
		return field_2EC;
	}
}