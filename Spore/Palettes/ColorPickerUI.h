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

namespace Palettes
{
	using namespace UTFWin;
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
		void Load(IWindow* pWindow, uint32_t propID, uint32_t nRegionFilter, vector<ColorRGB>* pColors = nullptr);

		///
		/// Toggles the visibility of this color picker. If bVisible is true, the color picker UI will be brought to the front
		/// of its parent window.
		/// @param bVisible Whether the color picker must be visible or not.
		///
		void SetVisible(bool bVisible);

		///
		/// Returns the area that a swatch in the given index would fit. It calculates it based on the 
		/// 'colorpickerGapPercent' property, the number of color buttons and the width/height of the container.
		/// @param nIndex The index of the swatch whose area will be calculated.
		///
		Math::Rectangle GetSwatchArea(int nIndex);

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

	protected:
		/* 0Ch */	intrusive_ptr<Object> field_0C;
		/// The container window where the layout is inserted.
		/* 10h */	IWindow* mpWindow;
		/// The total width of the container window.
		/* 14h */	float mfWidth;
		/// The total height of the container window.
		/* 18h */	float mfHeight;
		/// The currently selected color.
		/* 1Ch */	Math::ColorRGB mSelectedColor;
		/// The index of the button for setting a custom color, only used if the property 'colorpickerAddCustomColor' is true.
		/* 28h */	int mnCustomColorIndex;  // -1
		/// The index of the button for setting the default color, only used if the property 'colorpickerAddDefaultColor' is true.
		/* 2Ch */	int mnDefaultColorIndex;  // -1
		/// The user interfaces of the multiple color swatches that are shown in the color picker.
		/* 30h */	vector<intrusive_ptr<ColorSwatchUI>> mpColorUIs;
		/// The number of color buttons that fit into the picker layout.
		/* 44h */	size_t mnColorsCount;
		/// The PROP file that contains the configuration for this color picker.
		/* 48h */	intrusive_ptr<App::PropertyList> mpPropList;
		/// In block painting, the instance ID of a file that defines which region is painted in partial styles;
		/// The file is assumed to be in the folder with group ID 0x406A6F00.
		/// In skinpaints, this is the skinpaint index (0 -> base, 1 -> coat, 2 -> detail).
		/* 4Ch */	uint32_t mnRegionFilter;

	public:
		const static uint32_t TYPE = 0xD0D22119;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(ColorPickerUI) == 0x50, "sizeof(ColorPickerUI) != 50h");

	namespace InternalAddressList(ColorPickerUI)
	{
		DefineAddress(Load, GetAddress(0x5A5D50, 0x5A5EB0, 0x5A5EB0));
		DefineAddress(SetVisible, GetAddress(0x5A3F30, 0x5A41F0, 0x5A41F0));
		DefineAddress(GetSwatchArea, GetAddress(0x5A4480, 0x5A4740, 0x5A4740));
		DefineAddress(Update, GetAddress(0x5A6C40, 0x5A6DA0, 0x5A6DA0));
	}

	//class ColorPickerUI : public DefaultRefCounted /*, public IColorPicker*/
	//{
	//public:
	//	//
	//	///* 0Ch */	intrusive_ptr<Object> field_0C;
	//	///* 10h */	intrusive_ptr<IWindow> parentWindow;
	//	///* 14h */	float width;
	//	///* 18h */	float height;
	//	///* 1Ch */	ColorRGB selectedColor;
	//	///* 28h */	int customColorIndex = -1;
	//	///* 2Ch */	int defaultColorIndex = -1;
	//	///* 30h */	vector<intrusive_ptr<ColorSwatch>> colors;
	//	///* 44h */	int colorCount;
	//	///* 48h */	intrusive_ptr<App::PropertyList> propList;
	//	///* 4Ch */	int field_4C;

	//	//METHOD_VOID(GetAddress(0x5A4480, 0x5A4740, 0x5A4740), ColorPicker, GetSwatchBounds, PARAMS(Math::Rectangle& dst, int index, int arg_8), PARAMS(dst, index, arg_8));

	//	//METHOD_VOID(GetAddress(0x5A4B50, 0x5A4E10, 0x5A4E10), ColorPicker, sub_5A4B50, PARAMS(ColorRGB& color), PARAMS(color));

	//	//static const uint32_t TYPE = 0xD0D22119;
	//	//
	//};

	// static_assert(sizeof(ColorPicker) == 0x50, "sizeof(ColorPicker) != 50h");
}