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

#include <Spore\Object.h>
#include <Spore\App\Property.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\Palettes\ColorSwatchUI.h>

#define ColorPickerUIPtr eastl::intrusive_ptr<Palettes::ColorPickerUI>

namespace Palettes
{
	using namespace eastl;

	///
	/// This class holds all information related with the color picker in editor categories and its user interface.
	/// A color picker is made of multiple color buttons, represented by the Palettes::ColorSwatchUI class.
	/// A color picker object can only have one selected color at a time.
	///
	class ColorPickerUI : public DefaultRefCounted, public Object
	{
	public:
		ColorPickerUI();
		virtual ~ColorPickerUI() {};

		///
		/// Loads and generates the UI for this color picker. This creates the layout for all the color buttons.
		/// @param pWindow The container window where the layout will be inserted.
		/// @param propID The instanceID of the property list that contains the properties of the color picker. The folder is assumed
		/// to be 'ColorPickerConfig'. 
		/// @param nRegionFilter Either the region filter ID (for block painting) or the skinpaint index.
		/// @param pColors [Optional] A list of the colors that must be generated. If it is not present, the list will be taken
		/// from the property 'colorpickerColors' of the .prop file.
		///
		bool Load(UTFWin::IWindow* pWindow, uint32_t propID, uint32_t regionFilter, vector<ColorRGB>* pColors = nullptr);

		///
		/// Toggles the visibility of this color picker. If bVisible is true, the color picker UI will be brought to the front
		/// of its parent window.
		/// @param bVisible Whether the color picker must be visible or not.
		///
		void SetVisible(bool visible);

		///
		/// Returns the area that a swatch in the given index would fit. It calculates it based on the 
		/// 'colorpickerGapPercent' property, the number of color buttons and the width/height of the container.
		/// @param nIndex The index of the swatch whose area will be calculated.
		///
		Math::Rectangle GetSwatchArea(int index, bool=false) const;

		void SetColor(const ColorRGB& color);

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

	public:
		/* 0Ch */	ObjectPtr field_0C;
		/// The container window where the layout is inserted.
		/* 10h */	UTFWin::IWindow* mpWindow;
		/// The total width of the container window.
		/* 14h */	float mWidth;
		/// The total height of the container window.
		/* 18h */	float mHeight;
		/// The currently selected color.
		/* 1Ch */	Math::ColorRGB mSelectedColor;
		/// The index of the button for setting a custom color, only used if the property 'colorpickerAddCustomColor' is true.
		/* 28h */	int mCustomColorIndex;  // -1
		/// The index of the button for setting the default color, only used if the property 'colorpickerAddDefaultColor' is true.
		/* 2Ch */	int mDefaultColorIndex;  // -1
		/// The user interfaces of the multiple color swatches that are shown in the color picker.
		/* 30h */	vector<ColorSwatchUIPtr> mpColorUIs;
		/// The number of color buttons that fit into the picker layout.
		/* 44h */	size_t mColorsCount;
		/// The PROP file that contains the configuration for this color picker.
		/* 48h */	PropertyListPtr mpPropList;
		/// In block painting, the instance ID of a file that defines which region is painted in partial styles;
		/// The file is assumed to be in the folder with group ID 0x406A6F00.
		/// In skinpaints, this is the skinpaint index (0 -> base, 1 -> coat, 2 -> detail).
		/* 4Ch */	uint32_t mRegionFilter;

	public:
		const static uint32_t TYPE = 0xD0D22119;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(ColorPickerUI) == 0x50, "sizeof(ColorPickerUI) != 50h");

	namespace Addresses(ColorPickerUI)
	{
		DeclareAddress(Load);
		DeclareAddress(SetVisible);
		DeclareAddress(GetSwatchArea);
		DeclareAddress(Update);
		DeclareAddress(SetColor);
	}
}