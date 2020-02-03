#include "stdafx.h"
#include "ColorWheelSwatchUI.h"
#include <Spore\UTFWin\ImageDrawable.h>
#include <Spore\Palettes\ColorPickerUI.h>
#include <Spore\Audio\AudioSystem.h>
#include <Spore\Editors\EditorMessages.h>
#include <Spore\Messaging.h>
#include <Spore\UI\LayerManager.h>
#include <Spore\UTFWin\Window.h>
// To use min and max
#include <algorithm>

ColorWheelSwatchUI::ColorWheelSwatchUI()
	: mPanelLayout()
	, mpWheelWindow()
	, mpValueWindow()
	, mpWheelCursor()
	, mpValueCursor()
	, mpPreviewWindow()
	, mpTextField()
	, mIsSelectingColor(false)
	, mMouseWheelRange(0)
	, mHsvColor(0, 0, 1.0f)
{
}

ColorWheelSwatchUI::~ColorWheelSwatchUI() {
}

void* ColorWheelSwatchUI::Cast(uint32_t type) const {
	CLASS_CAST(ColorWheelSwatchUI);
	return ColorSwatchUI::Cast(type);
}

void ColorWheelSwatchUI::TextValueChanged(const Message& msg)
{
	const char16_t* text = mpTextField->GetText();

	if (text[0] == L'#')
	{
		Color intColor = wcstoul((wchar_t*)&text[1], nullptr, 16);
		if (intColor != mColor.ToIntColor())
		{
			ColorRGB color(intColor);
			mColor = ColorRGB(color);
			mHsvColor = Math::RGBtoHSV(color);

			//TODO when should we send a spore message?
			ColorChanged(true, false);
		}
	}
}

void ColorWheelSwatchUI::WheelValueChanged(const Message& msg)
{
	// If this method gets called, we know the message is of mouse type, so we can use MouseEvent

	// Step 0: get center of window
	auto area = mpWheelWindow->GetArea();
	Point windowCenter(area.GetWidth() / 2.0f, area.GetHeight() / 2.0f);

	// Step 1: create vector from center to mouse
	Vector2 mouseVector(msg.Mouse.mouseX - windowCenter.x, -(msg.Mouse.mouseY - windowCenter.y));

	//Vector2 baseVector(1.0f, 0.0f);

	//// Step 2: u * v = |u| * |v| * cos(angle)
	// float angle = acosf((baseVector.x * mouseVector.x + baseVector.y * mouseVector.y) / 
	//	(sqrtf(baseVector.x*baseVector.x) * sqrtf(mouseVector.x*mouseVector.x)));

	float angle = Math::ToDegrees(atan2f(mouseVector.y, mouseVector.x));

	if (angle < 0)  angle += 360.0f;

	mHsvColor.h = angle;

	mHsvColor.s = sqrtf(mouseVector.x * mouseVector.x + mouseVector.y * mouseVector.y) / (area.GetWidth() / 2.0f);

	if (mHsvColor.s > 1.0f) mHsvColor.s = 1.0f;

	ColorChanged(false, false);
}

void ColorWheelSwatchUI::SliderValueChanged(const Message& msg)
{
	mHsvColor.v = 1.0f - msg.Mouse.mouseX / mpValueWindow->GetArea().GetWidth();

	mpValueWindow->SetShadeColor(ColorRGBA(mHsvColor.v, mHsvColor.v, mHsvColor.v, 1.0f).ToIntColor());
	ColorChanged(false, false);
}

bool ColorWheelSwatchUI::HandleUIMessage(IWindow* window, const Message& msg)
{
	if (msg.IsType(kMsgKeyDown) && msg.Key.vkey == VK_RETURN) {
		// Some users like pressing the Enter key when finished changing the color. 
		// We replace the ENTER key behaviour this here so it doesn't exit the editor like it would normally do.
		// Returning true tells the event was handled, so it stops being propagated
		return true;
	}

	/* Update color (if the event happened in the wheel or value windows) */
	if (msg.IsType(kMsgMouseMove) || msg.IsType(kMsgMouseDown))
	{
		if (msg.IsType(kMsgMouseDown) && (window == mpWheelWindow || window == mpValueWindow)) {
			mIsSelectingColor = true;
		}

		if (mIsSelectingColor)
		{
			if (window == mpWheelWindow)
			{
				if (msg.Mouse.IsLeftButton()) WheelValueChanged(msg);
				return true;
			}
			else if (window == mpValueWindow)
			{
				if (msg.Mouse.IsLeftButton()) SliderValueChanged(msg);
				return true;
			}
		}
	}
	/* Set we aren't editing the color anymore, send that color as Spore so it does whatever it
	has to do (for example, adding an undo action) */
	else if (msg.IsType(kMsgMouseUp))
	{
		if (mIsSelectingColor)
		{
			mIsSelectingColor = false;

			if (window == mpWheelWindow || window == mpValueWindow) ColorChanged(false, true);
		}
	}
	/* Update color when we change the text field */
	else if (msg.IsType(kMsgKeyUp) && object_cast<ITextEdit>(window) == mpTextField)
	{
		TextValueChanged(msg);
	}
	/* Send the color (if necessary) when we have finished editing */
	else if (msg.IsType(kMsgMouseLeave) && object_cast<ITextEdit>(window) == mpTextField)
	{
		ColorChanged(true);
	}
	else if (msg.IsType(kMsgMouseWheel) && mIsSelectingColor &&
		(window == mpWheelWindow || window == mpValueWindow))
	{
		mHsvColor.v += msg.Mouse.wheelDelta / (float)mMouseWheelRange;
		mHsvColor.v = min(max(mHsvColor.v, 0.0f), 1.0f);
		ColorChanged(false, false);
	}

	if (window == mpValueWindow || window == mpWheelWindow || (mpTextField &&
		(window == mpTextField->ToWindow() || window == mpTextField->ToWindow()->GetParent()))) {
		return true;
	}

	if (msg.Refresh.window == mpValueWindow || msg.Refresh.window == mpWheelWindow || (mpTextField != nullptr &&
		(msg.Refresh.window == mpTextField->ToWindow() || msg.Refresh.window == mpTextField->ToWindow()->GetParent()))) {
		return true;
	}

	return ColorSwatchUI::HandleUIMessage(window, msg);
}

void ColorWheelSwatchUI::InitPanel(uint32_t colorpickerImageGroupID)
{
	mpExpansionWindow = mPanelLayout.FindWindowByID(id("PanelWindow"));
	mpExpansionWindow->SetFlag(kWinFlagVisible, false);
	// We want this window to ignore mouse events
	mpExpansionWindow->SetFlag(kWinFlagIgnoreMouse, false);
	// Doing this, whenever an event happens in the main window our class gets notified
	mpExpansionWindow->AddWinProc(this);
}

void ColorWheelSwatchUI::InitWheelWindow(uint32_t colorpickerImageGroupID)
{
	uint32_t colorpickerEnhancedCursorImage;
	App::Property::GetKeyInstanceID(mpConfigProp.get(), id("colorpickerEnhancedCursorImage"), colorpickerEnhancedCursorImage);


	mpWheelWindow = mPanelLayout.FindWindowByID(id("WheelWindow"));

	mpWheelWindow->AddWinProc(this);

	mpWheelWindow->SetFlag(kWinFlagVisible, true);
	mpWheelWindow->SetFlag(kWinFlagEnabled, true);

	// We can use the AddImageWindow method to generate a window with an image,
	// specified by the ID in the property we got
	mpWheelCursor = IImageDrawable::AddImageWindow({ colorpickerEnhancedCursorImage, Image::kTypePNG, colorpickerImageGroupID },
		0, 0, mpExpansionWindow.get());

	mpWheelCursor->SetFlag(kWinFlagVisible, true);
	mpWheelCursor->SetFlag(kWinFlagIgnoreMouse, true);
}

void ColorWheelSwatchUI::InitPreviewWindow(uint32_t colorpickerImageGroupID)
{
	mpPreviewWindow = mPanelLayout.FindWindowByID(id("PreviewWindow"));
	mpPreviewWindow->SetFlag(kWinFlagVisible, true);
	mpPreviewWindow->SetFlag(kWinFlagIgnoreMouse, true);
}

void ColorWheelSwatchUI::InitValueSlider(uint32_t colorpickerImageGroupID)
{
	uint32_t colorpickerEnhancedCursorImage;
	App::Property::GetKeyInstanceID(mpConfigProp.get(), id("colorpickerEnhancedCursorImage"), colorpickerEnhancedCursorImage);

	mpValueWindow = mPanelLayout.FindWindowByID(id("ValueWindow"));
	mpValueWindow->AddWinProc(this);
	mpValueWindow->SetFlag(kWinFlagVisible, true);
	mpValueWindow->SetFlag(kWinFlagEnabled, true);

	mpValueCursor = IImageDrawable::AddImageWindow({ colorpickerEnhancedCursorImage, Image::kTypePNG, colorpickerImageGroupID },
		0, 0, mpExpansionWindow.get());
	mpValueCursor->SetFlag(kWinFlagVisible, true);
	mpValueCursor->SetFlag(kWinFlagEnabled, true);
}

void ColorWheelSwatchUI::InitTextField(uint32_t colorpickerImageGroupID)
{
	mpTextField = object_cast<ITextEdit>(mPanelLayout.FindWindowByID(id("TextField")));
	mpTextField->ToWindow()->SetFlag(kWinFlagVisible, true);
	mpTextField->ToWindow()->AddWinProc(this);
}

void ColorWheelSwatchUI::Load(App::PropertyList* pConfigProp, union Math::Rectangle area,
	IWindow* pContainerWindow, Object* pExpansionObject)
{
	mClock.Start();

	mpConfigProp = pConfigProp;
	mpExpansionObject = pExpansionObject;
	// I don't know, Spore does this
	field_A4 = -1;
	// We will set this to true at the end of the method
	mIsLoaded = false;

	// Default color will be white (1, 1, 1)
	mColor.r = mOriginalColor.r = 1.0f;
	mColor.g = mOriginalColor.g = 1.0f;
	mColor.b = mOriginalColor.b = 1.0f;

	uint32_t colorpickerImageGroupID = 0;
	uint32_t colorpickerEnhancedIconImage = 0;
	uint32_t colorpickerImageDefaultFrame = 0;
	uint32_t colorpickerImageDefaultFrameGlow = 0;
	uint32_t colorpickerImageDefaultFrameShine = 0;
	uint32_t colorpickerImageExpansionBackground = 0;

	uint32_t colorpickerEnhancedPanelUI = 0;

	App::Property::GetKeyInstanceID(mpConfigProp.get(), 0xD29675E0, colorpickerImageGroupID);
	App::Property::GetKeyInstanceID(mpConfigProp.get(), id("colorpickerEnhancedIconImage"), colorpickerEnhancedIconImage);
	App::Property::GetKeyInstanceID(mpConfigProp.get(), 0xD29675E1, colorpickerImageDefaultFrame);
	App::Property::GetKeyInstanceID(mpConfigProp.get(), 0xD29675E2, colorpickerImageDefaultFrameGlow);
	App::Property::GetKeyInstanceID(mpConfigProp.get(), 0xD29675E3, colorpickerImageDefaultFrameShine);
	App::Property::GetKeyInstanceID(mpConfigProp.get(), 0xD29675E4, colorpickerImageExpansionBackground);

	App::Property::GetKeyInstanceID(mpConfigProp.get(), id("colorpickerEnhancedPanelUI"), colorpickerEnhancedPanelUI);

	App::Property::GetInt32(mpConfigProp.get(), id("colorpickerMouseWheelRange"), mMouseWheelRange);

	mpMainWindow = new Window();
	pContainerWindow->AddWindow(mpMainWindow.get());
	pContainerWindow->BringToFront(mpMainWindow.get());

	mpMainWindow->SetShadeColor(0xFFFFFFFF);
	mpMainWindow->SetFillColor(0x00FFFFFF);
	// So our class receives its events
	mpMainWindow->AddWinProc(this);

	// Now we just generate the small button frames, just like Spore does

	/* -- colorpickerEnhancedIconImage -- */
	mpColorWindow = IImageDrawable::AddImageWindow(
		{ colorpickerEnhancedIconImage, Image::kTypePNG, colorpickerImageGroupID }, 0, 0, mpMainWindow.get());

	object_cast<IImageDrawable>(mpColorWindow->GetDrawable())->SetTiling(ImageTiling::None);
	mpColorWindow->SetFlag(kWinFlagEnabled, true);
	mpColorWindow->SetFlag(kWinFlagIgnoreMouse, true);

	/* -- colorpickerImageDefaultFrame -- */
	mpFrameWindow = IImageDrawable::AddImageWindow(
		{ colorpickerImageDefaultFrame, Image::kTypePNG, colorpickerImageGroupID }, 0, 0, mpMainWindow.get());

	object_cast<IImageDrawable>(mpFrameWindow->GetDrawable())->SetTiling(ImageTiling::None);
	mpFrameWindow->SetFlag(kWinFlagEnabled, true);
	mpFrameWindow->SetFlag(kWinFlagIgnoreMouse, true);

	/* -- colorpickerImageDefaultFrameGlow -- */
	mpFrameGlowWindow = IImageDrawable::AddImageWindow(
		{ colorpickerImageDefaultFrameGlow, Image::kTypePNG, colorpickerImageGroupID }, 0, 0, mpMainWindow.get());

	object_cast<IImageDrawable>(mpFrameGlowWindow->GetDrawable())->SetTiling(ImageTiling::None);
	mpFrameGlowWindow->SetFlag(kWinFlagEnabled, true);
	mpFrameGlowWindow->SetFlag(kWinFlagIgnoreMouse, true);

	/* -- colorpickerImageDefaultFrameShine -- */
	mpFrameShineWindow = IImageDrawable::AddImageWindow(
		{ colorpickerImageDefaultFrameShine, Image::kTypePNG, colorpickerImageGroupID }, 0, 0, mpMainWindow.get());

	mpFrameShineWindow->SetFlag(kWinFlagEnabled, true);
	mpFrameShineWindow->SetFlag(kWinFlagIgnoreMouse, true);

	// It also sets the bounds for all the sub-windows
	SetArea(area, true);


	// Load the panel UI, error if cannot be loaded
	if (colorpickerEnhancedPanelUI == 0 ||
		!mPanelLayout.LoadByID(colorpickerEnhancedPanelUI)) return;

	InitPanel(colorpickerImageGroupID);
	InitWheelWindow(colorpickerImageGroupID);
	InitValueSlider(colorpickerImageGroupID);
	InitPreviewWindow(colorpickerImageGroupID);
	InitTextField(colorpickerImageGroupID);

	// If we arrived here, everything was loaded fine
	mIsLoaded = true;
}

void ColorWheelSwatchUI::UpdateTints(bool updateText)
{
	Color intColor = ColorRGBA(mColor.r, mColor.g, mColor.b, 1.0f).ToIntColor();

	mpPreviewWindow->SetShadeColor(intColor);
	mpWheelWindow->SetShadeColor(ColorRGBA(mHsvColor.v, mHsvColor.v, mHsvColor.v, 1.0f).ToIntColor());

	ColorRGB valueTint = Math::HSVtoRGB({ mHsvColor.h, mHsvColor.s, 1.0f });
	mpValueWindow->SetShadeColor(ColorRGBA(valueTint.r, valueTint.g, valueTint.b, 1.0f).ToIntColor());

	if (updateText) SetTextColor(intColor);
}

void ColorWheelSwatchUI::ColorChanged(bool frommTextField, bool sendSporeMessage)
{
	mColor = Math::HSVtoRGB(mHsvColor);

	UpdateCursorPositions();
	UpdateTints(!frommTextField);
	ColorChanged(sendSporeMessage);
}

void ColorWheelSwatchUI::ColorChanged(bool sendSporeMessage)
{
	if (mpExpansionObject)
	{
		if (mColor.ToIntColor() == mOriginalColor.ToIntColor()) return;

		// We know it's the color picker, we cast it to get information
		auto chooser = object_cast<ColorPickerUI>(mpExpansionObject.get());

		chooser->SetColor(mColor);
		mOriginalColor = mColor;

		if (sendSporeMessage)
		{
			Editors::ColorChangedMessage msg(
				mColor.ToIntColor(), mpExpansionObject.get(), chooser->mRegionFilter, mIsDefaultColor, mColorIndex);
			MessageManager.PostMSG(msg.id, &msg);
		}
		else {
			ChangeCreationColor(chooser->mRegionFilter, mColor);
		}

		// must replace loc_592D6D
	}
}


void ColorWheelSwatchUI::Update(int msTime, bool arg_4)
{
	// Hoenstly: I haven't thought this method much. Just copied what Spore does and added my modification

	// Some default values, although we get them from the PROP list
	float colorpickerRolloverMaxTime = 0.25f;
	float colorpickerMouseDownMaxTime = 0.25f;
	float colorpickerSelectMaxTime = 0.25f;
	float colorpickerMaxInflation = 3.0;
	float colorpickerExpansionCatchUpSpeed = 12.0f;
	int colorpickerNumExpansionSwatches = 5;
	int colorpickerDoubleClickInterval = 400;
	float colorpickerGapPercent = 0.1f;

	// milliseconds to seconds
	float seconds = msTime * 0.001f;

	App::Property::GetInt32(mpConfigProp.get(), 0x41C3428, colorpickerDoubleClickInterval);
	App::Property::GetInt32(mpConfigProp.get(), 0xD29675EB, colorpickerNumExpansionSwatches);
	App::Property::GetFloat(mpConfigProp.get(), 0xD29675E6, colorpickerRolloverMaxTime);
	App::Property::GetFloat(mpConfigProp.get(), 0xD29675E7, colorpickerMouseDownMaxTime);
	App::Property::GetFloat(mpConfigProp.get(), 0xD297BFC6, colorpickerSelectMaxTime);
	App::Property::GetFloat(mpConfigProp.get(), 0xD29675E8, colorpickerMaxInflation);
	App::Property::GetFloat(mpConfigProp.get(), 0xD29675EF, colorpickerExpansionCatchUpSpeed);
	App::Property::GetFloat(mpConfigProp.get(), 0x4120847, colorpickerGapPercent);

	float value = arg_4 ? 1.0f : -1.0f;
	mMouseSelectTime += value * seconds;
	// Convert into range [0, colorpickerSelectMaxTime], so generally [0, 0.25]
	mMouseSelectTime = std::min(std::max(mMouseSelectTime, 0.0f), colorpickerSelectMaxTime);

	value = mIsRollover ? 1.0f : -1.0f;
	mMouseRolloverTime += value * seconds;
	mMouseRolloverTime = std::min(std::max(mMouseRolloverTime, 0.0f), colorpickerRolloverMaxTime);

	value = mIsMouseDown ? 1.0f : -1.0f;
	mMouseDownTime += value * seconds;
	mMouseDownTime = std::min(std::max(mMouseDownTime, 0.0f), colorpickerMouseDownMaxTime);

	value = mIsShowingPanel ? 1.0f : -1.0f;
	field_18 += value * seconds;
	field_18 = std::min(std::max(field_18, 0.0f), 0.5f);

	if (mpMainWindow && mIsLoaded)
	{
		value = colorpickerMaxInflation / colorpickerRolloverMaxTime * mMouseRolloverTime;
		SetArea(Math::Rectangle(
			mArea.x1 - value,
			mArea.y1 - value,
			mArea.x2 + value,
			mArea.y2 + value));

		// Play with opacity
		mpMainWindow->SetShadeColor(ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f - field_18 * 2.0f).ToIntColor());
	}

	if (mpFrameGlowWindow != nullptr)
	{
		mpFrameGlowWindow->SetShadeColor(ColorRGBA(1.0f, 1.0f, 1.0f,
				mMouseSelectTime > 0 ? (mMouseSelectTime / colorpickerSelectMaxTime) : (mMouseDownTime / colorpickerMouseDownMaxTime)).ToIntColor());
	}

	bool isDoubleClick = false;
	if (mClickTime != 0 && mPreviousClickTime != 0)
	{
		isDoubleClick = (mClickTime - mPreviousClickTime) < colorpickerDoubleClickInterval;
	}

	if (!mIsDefaultColor)
	{
		if (mMouseDownTime == colorpickerMouseDownMaxTime ||
			(isDoubleClick && !mIsShowingPanel))
		{
			mMouseDownTime = 0.0f;
			mIsRollover = false;
			mIsMouseDown = false;
			mClickTime = 0;
			mPreviousClickTime = 0;

			if (mpExpansionWindow)
			{
				SetPanelArea();

				Audio::PlayAudio(0xA9E589E1);

				UpdateCursorPositions();
				SetTextColor(ColorRGBA(mColor.r, mColor.g, mColor.b, 1.0f).ToIntColor());
				mpExpansionWindow->SetFlag(kWinFlagVisible, true);
				mpExpansionWindow->GetParent()->BringToFront(mpExpansionWindow.get());

				mIsShowingPanel = true;

				if (mpExpansionObject)
				{
					auto chooser = object_cast<ColorPickerUI>(mpExpansionObject.get());
					if (chooser && chooser->mpWindow && chooser->mpWindow->GetParent()) {
						chooser->mpWindow->GetParent()->BringToFront(chooser->mpWindow);
					}
				}

				// UI Layer manager, PLACEHOLDER what does this do?
				CALL(Address(ModAPI::ChooseAddress(0x80DD00, 0x80D7B0)), void, 
					Args(UI::cLayerManager*, IWindow*, int, int),
					Args(UI::cLayerManager::Get(), mpExpansionWindow.get(), 2, 1));
			}
		}
	}

	if (field_10)
	{
		value = seconds * colorpickerExpansionCatchUpSpeed;
		if (value > 1.0f) {
			value = 1.0f;
		}
		// more things here, but I think they never happen
	}
}

void ColorWheelSwatchUI::UpdateCursorPositions()
{
	Math::Rectangle area;
	Math::Point point;

	auto valueCursorArea = mpValueCursor->GetArea();
	auto valueWindowArea = mpValueWindow->GetArea();

	point.x = valueWindowArea.x1 + (1.0f - mHsvColor.v) * valueWindowArea.GetWidth();
	point.y = valueWindowArea.y1 + valueWindowArea.GetHeight() / 2.0f;
	float halfWidth = valueCursorArea.GetWidth() / 2.0f;
	float halfHeight = valueCursorArea.GetHeight() / 2.0f;

	area.x1 = point.x - halfWidth;
	area.y1 = point.y - halfHeight;
	area.x2 = point.x + halfWidth;
	area.y2 = point.y + halfHeight;

	mpValueCursor->SetArea(area);


	auto wheelCursorArea = mpWheelCursor->GetArea();
	auto wheelWindowArea = mpWheelWindow->GetArea();
	float radius = mHsvColor.s * wheelWindowArea.GetWidth() / 2.0f;

	point.x = wheelWindowArea.x1 + wheelWindowArea.GetWidth() / 2.0f + radius * cosf(Math::ToRadians(mHsvColor.h));
	point.y = wheelWindowArea.y1 + wheelWindowArea.GetHeight() / 2.0f - radius * sinf(Math::ToRadians(mHsvColor.h));
	halfWidth = wheelCursorArea.GetWidth() / 2.0f;
	halfHeight = wheelCursorArea.GetHeight() / 2.0f;

	area.x1 = point.x - halfWidth;
	area.y1 = point.y - halfHeight;
	area.x2 = point.x + halfWidth;
	area.y2 = point.y + halfHeight;

	mpWheelCursor->SetArea(area);
}

void ColorWheelSwatchUI::SetPanelArea() {
	float colorpickerEnhancedMinSeparation = 10.0f;

	App::Property::GetFloat(mpConfigProp.get(), id("colorpickerEnhancedMinSeparation"), colorpickerEnhancedMinSeparation);


	auto parentArea = WindowManager.GetMainWindow()->GetArea();
	auto mainWindowArea = mpMainWindow->GetRealArea();

	Point point = mpMainWindow->GetParent()->func48(
		(mainWindowArea.x1 + mainWindowArea.x2) / 2.0f,
		(mainWindowArea.y1 + mainWindowArea.y2) / 2.0f);

	point = WindowManager.GetMainWindow()->func49(point.x, point.y);

	Math::Rectangle panelArea = mpExpansionWindow->GetArea();

	float totalWidth = panelArea.GetWidth();
	float totalHeight = panelArea.GetHeight();

	float halfWidth = totalWidth / 2.0f;
	float halfHeight = totalHeight / 2.0f;

	if (point.x + halfWidth + colorpickerEnhancedMinSeparation > parentArea.x2) {
		point.x = parentArea.x2 - halfWidth - colorpickerEnhancedMinSeparation;
	}

	// fix y too
	if (point.y - halfHeight - colorpickerEnhancedMinSeparation < parentArea.y1) {
		point.y = parentArea.y1 + halfHeight + colorpickerEnhancedMinSeparation;
	}

	panelArea.x1 = point.x - halfWidth;
	panelArea.x2 = point.x + halfWidth;
	panelArea.y1 = point.y - halfHeight;
	panelArea.y2 = point.y + halfHeight;

	mpExpansionWindow->SetFlag(kWinFlagVisible, false);
	mpExpansionWindow->SetArea(panelArea);
}

void ColorWheelSwatchUI::SetTextColor(Color intColor)
{
	// if the string isn't initialized sprintf gives errors
	string16 str = u"";
	str.sprintf(u"#%06X", intColor.value & 0xFFFFFF);

	mpTextField->SetText(str.c_str(), 0);
}

void ColorWheelSwatchUI::ChangeCreationColor(int index, const ColorRGB& color)
{
	if (Editor.field_150 &&
		CALL(Address(ModAPI::ChooseAddress(0x4C4280, 0x4C4A50)), void*, Args(Object*, int), Args(Editor.field_150.get(), 1)) &&
		Editor.mpEditorModel)
	{
		if (index == -1) {
			index = 0;
		}
		if (index >= 0 && index <= 2)
		{
			Editor.mpEditorModel->SetColor(index, color);
			Editor.field_4B2 = true;

			// sub_4C4AA0
			CALL(Address(ModAPI::ChooseAddress(0x4C4AA0, 0x4C5270)), void,
				Args(Object*, Editors::EditorModel*),
				Args(Editor.field_150.get(), Editor.mpEditorModel));
		}
	}
}


void ColorSwatchUI_Update_detour::DETOUR(int msTime, bool arg2) {
	// If this is being called on our class, call our own method
	auto p = object_cast<ColorWheelSwatchUI>(this);
	if (p)
		return p->Update(msTime, arg2);
	else
		// We cannot call ColorSwatchUI::Update(), because we detoured that! We would enter an infinite cycle.
		// Instead, we must use 'original_function' to avoid the detour
		return original_function(this, msTime, arg2);
}