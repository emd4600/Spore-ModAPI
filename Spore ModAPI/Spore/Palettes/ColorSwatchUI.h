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

#include <Spore\App\PropertyList.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\Object.h>
#include <Spore\Clock.h>

#define ColorSwatchUIPtr intrusive_ptr<Palettes::ColorSwatchUI>

namespace Palettes
{
	///
	/// This class holds all information related with a single color button in editor categories and its user interface.
	/// A color swatch is a button used to select a color, and it can optionally be expanded to show more color buttons.
	/// The multiple color swatches in the category are grouped in the Palettes::ColorPickerUI class.
	///
	class ColorSwatchUI 
		: public UTFWin::IWinProc
		, public DefaultRefCounted
	{
	public:
		ColorSwatchUI();
		virtual ~ColorSwatchUI() {};
		
		///
		/// Loads and generates the user interface for this color swatch, using the given color and area, as well
		/// as some properties of the configuration PROP file given. The user interface will be inserted into the container
		/// window that is provided.
		/// @param pConfigProp The PROP file that contains the configuration of the color picker.
		/// @param color The main color of this swatch button.
		/// @param area The area, relative to the parent window, that this button must have.
		/// @param pContainerWindow The window that will contain the button.
		/// @param pExpansionObject An object necessary to do the swatch expansion; generally this is the color picker.
		///
		void Load(
			App::PropertyList* pConfigProp, struct Math::ColorRGB color, union Math::Rectangle area, 
			UTFWin::IWindow* pContainerWindow, Object* pExpansionObject);

		///
		/// Sets the area of this swatch, updating the area of all the windows used by it.
		/// @param area The new area for the swatch windows.
		/// @param bUpdateSwatch [Optional] If true, it changes the Palettes::ColorSwatchUI::mArea field.
		///
		void SetArea(union Math::Rectangle area, bool bUpdateSwatch = false);

		///
		/// Calculates and sets the area of the expansion window for this swatch, based on the
		/// 'colorpickerExpansionSize' property. The value of that property is for a game with a width of 800 px,
		/// but in this method it is scaled accordingly to the current game dimensions.
		/// @param bFitWindow [Optional] If true, the area width is limited so it fits into the game window.
		///
		void GenerateExpansionArea(bool bFitWindow = false);

		///
		/// Adds a tooltip to this swatch, using the localized string with the given instance ID (the tableID is 'editor').
		/// @param instanceID The instance ID of the tooltip text, inside the 'editor' locale table.
		///
		void AddTooltip(uint32_t instanceID);

		void Update(int msTime, bool);

		void Destroy();

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual int GetEventFlags() const override;
		virtual bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

	public:
		/// Whether the user interface for this color swatch has already been loaded. This is set 
		/// to true in the Load method.
		/* 0Ch */	bool mIsLoaded;
		/// Whether the button is on rollover state (that is, the mouse is over the button).
		/* 0Dh */	bool mIsRollover;
		/// Whether the swatch button is being pressed with the left mouse click.
		/* 0Eh */	bool mIsMouseDown;
		/// Whether the expansion panel is being shown.-
		/* 0Fh */	bool mIsShowingPanel;
		/* 10h */	bool field_10;
		/// Whether this swatch is the button used to set a custom color in the color picker.
		/* 11h */	bool mIsCustomColor;
		/// Whether this swatch is the button used to set the default color in the color picker.
		/* 12h */	bool mIsDefaultColor;
		/* 14h */	float mMouseRolloverTime;
		/* 18h */	float field_18;
		/* 1Ch */	float mMouseDownTime;
		/* 20h */	float mMouseSelectTime;
		/// The original color with which this swatch was loaded. This never changes.
		/* 24h */	Math::ColorRGB mOriginalColor;
		/// The current selected color of the swatch.
		/* 30h */	Math::ColorRGB mColor;
		/// The area (relative to the container window) that this swatch button fits.
		/* 3Ch */	Math::Rectangle mArea;  // not initialized
		/// The window that displays the frame of the swatch. It displays the image determined by the 
		/// property 'colorpickerImageDefaultFrame'.
		/* 4Ch */	IWindowPtr mpFrameWindow;
		/// The window that displays the frame glow of the swatch. It displays the image determined by the 
		/// property 'colorpickerImageDefaultFrameGlow'.
		/* 50h */	IWindowPtr mpFrameGlowWindow;
		/// The window that displays the frame shine of the swatch. It displays the image determined by the 
		/// property 'colorpickerImageDefaultFrameShine'.
		/* 54h */	IWindowPtr mpFrameShineWindow;
		/// The window that displays the current selected color. It uses the image determined by the 
		/// property 'colorPickerImageDefaultColor' as background.
		/* 58h */	IWindowPtr mpColorWindow;
		/// The main window that contains all the other windows of the swatch. This one is added
		/// into the container window provided in the method Load, and has this class added as a 
		/// window procedure.
		/* 5Ch */	IWindowPtr mpMainWindow;
		/// The panel that shows when the swatch is pressed, and that expands the swatch to show multiple colors.
		/// This shows the image determined by the property 'colorpickerImageExpansionBackground', and it is not added
		/// into mpMainWindow, but into the main game window instead.
		/* 60h */	IWindowPtr mpExpansionWindow;
		/// An object necessary to do the swatch expansion; generally this is the color picker.
		/* 64h */	ObjectPtr mpExpansionObject;
		/// All the color swatch UIs that are shown in the expansion panel of this swatch.
		/* 68h */	vector<ColorSwatchUIPtr> mExpansionSwatches;
		/// The PROP file used to configurate the color picker.
		/* 7Ch */	PropertyListPtr mpConfigProp;
		/// A milliseconds clock used to measure click time.
		/* 80h */	Clock mClock;
		/// In milliseconds, the last time when the mouse was being pressed over the button.
		/* 98h */	int mClickTime;
		/// In milliseconds, the previous time when the mouse was being pressed over the button.
		/* 9Ch */	int mPreviousClickTime;
		/// The index of this color inside the color picker.
		/* A0h */	int mColorIndex;  // -1
		/* A4h */	int field_A4;  // not initialized  // set to -1 in Load

	public:
		const static uint32_t TYPE = 0x03B26CA5;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(ColorSwatchUI) == 0xA8, "sizeof(ColorSwatchUI) != A8h");

	namespace Addresses(ColorSwatchUI)
	{
		DeclareAddress(Load);
		DeclareAddress(SetArea);
		DeclareAddress(GenerateExpansionArea);
		DeclareAddress(AddTooltip);
		DeclareAddress(Update);
		DeclareAddress(Destroy);

		DeclareAddress(HandleUIMessage);
	}
}
