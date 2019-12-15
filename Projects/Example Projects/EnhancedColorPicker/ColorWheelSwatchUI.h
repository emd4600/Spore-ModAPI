#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Palettes\ColorSwatchUI.h>
#include "EnhancedColorListener.h"

using namespace Palettes;
using namespace UTFWin;

// A custom swatch UI that shows an HSV color wheel when pressed.
// It inherits from ColorSwatchUI (because it's basically that)
class ColorWheelSwatchUI
	: public ColorSwatchUI
{
private:
	// Hide the original ColorSwatchUI Load method, as we are not interested in that
	using ColorSwatchUI::Load;

public:
	// This allows us to use object_cast
	static const uint32_t TYPE = id("ColorWheelSwatchUI");

	ColorWheelSwatchUI();
	virtual ~ColorWheelSwatchUI();

	void* Cast(uint32_t type) const override;

	// We will use our own UI handling code
	bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

	virtual void Load(App::PropertyList* pConfigProp, union Math::Rectangle area,
		IWindow* pContainerWindow, Object* pExpansionObject);

	// ColorSwatchUI has its own Update method, problem: it's not virtual
	// So we can't override it, we will have to detour it
	virtual void Update(int, bool);

protected:
	// We separate the panel creation in multiple steps,
	// virtual for if anyone wants to extend this class
	virtual void InitPanel(uint32_t colorpickerImageGroupID);
	virtual void InitWheelWindow(uint32_t colorpickerImageGroupID);
	virtual void InitValueSlider(uint32_t colorpickerImageGroupID);
	virtual void InitPreviewWindow(uint32_t colorpickerImageGroupID);
	virtual void InitTextField(uint32_t colorpickerImageGroupID);

	// To keep everything organized, we will separate event handling depending on where the event happened
	virtual void WheelValueChanged(const Message& msg);
	virtual void SliderValueChanged(const Message& msg);
	virtual void TextValueChanged(const Message& msg);
	virtual void ColorChanged(bool sendSporeMessage);
	virtual void ColorChanged(bool fromTextField, bool sendSporeMessage);

	virtual void UpdateTints(bool updateText);

	// Position the value/hue cursors correctly
	virtual void UpdateCursorPositions();

	// Sets the hex color code text
	virtual void SetTextColor(Color intColor);

	virtual void SetPanelArea();

	void ChangeCreationColor(int regionFilter, const ColorRGB& color);

protected:
	// We save these fields as protected, for if anyone wants to inherit this class

	// The SPUI file loaded to show the color wheel panel
	UILayout mPanelLayout;

	// The wheel itself. Used to select hue and saturation.
	intrusive_ptr<IWindow> mpWheelWindow;
	// A window that acts as a slider to select the value (brightness)
	intrusive_ptr<IWindow> mpValueWindow;

	// A small window that is positioned over the wheel window, and acts as a cursor
	intrusive_ptr<IWindow> mpWheelCursor;
	// A small window that is positioned over the value window, and acts as a cursor
	intrusive_ptr<IWindow> mpValueCursor;

	// The panel that shows the selected color for preview
	intrusive_ptr<IWindow> mpPreviewWindow;

	// The text field that shows the web hex color
	intrusive_ptr<ITextEdit> mpTextField;

	intrusive_ptr<EnhancedColorListener> mpListener;

	// The currently selected color
	ColorHSV mHsvColor;

	bool mIsSelectingColor;

	// The value needed to scroll from value 0 to 1
	int mMouseWheelRange;
};

// As explained before, we cannot override the Update method as it's not virtual, so detour it
member_detour(ColorSwatchUI_Update_detour, ColorSwatchUI, void(int, bool)) {};