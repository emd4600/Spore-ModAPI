#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\UTFWin\Allocator.h>
#include <Spore\UTFWin\ButtonDrawableRadio.h>
#include <Spore\UTFWin\ButtonDrawableStandard.h>
#include <Spore\UTFWin\CascadeEffect.h>
#include <Spore\UTFWin\ComboBoxDrawable.h>
#include <Spore\UTFWin\cSPUIMessageBox.h>
#include <Spore\UTFWin\DialogDrawable.h>
#include <Spore\UTFWin\Effect.h>
#include <Spore\UTFWin\FadeEffect.h>
#include <Spore\UTFWin\FrameDrawable.h>
#include <Spore\UTFWin\GlideEffect.h>
#include <Spore\UTFWin\Graphics2D.h>
#include <Spore\UTFWin\IButton.h>
#include <Spore\UTFWin\Image.h>
#include <Spore\UTFWin\ImageDrawable.h>
#include <Spore\UTFWin\InflateEffect.h>
#include <Spore\UTFWin\InteractiveWinProc.h>
#include <Spore\UTFWin\ITextEdit.h>
#include <Spore\UTFWin\IWindowManager.h>
#include <Spore\UTFWin\ModulateEffect.h>
#include <Spore\UTFWin\PerspectiveEffect.h>
#include <Spore\UTFWin\ProportionalLayout.h>
#include <Spore\UTFWin\RotateEffect.h>
#include <Spore\UTFWin\ScrollbarDrawable.h>
#include <Spore\UTFWin\SimpleLayout.h>
#include <Spore\UTFWin\SliderDrawable.h>
#include <Spore\UTFWin\SpinnerDrawable.h>
#include <Spore\UTFWin\SporeStdDrawable.h>
#include <Spore\UTFWin\SporeStdDrawableImageInfo.h>
#include <Spore\UTFWin\SporeTooltipWinProc.h>
#include <Spore\UTFWin\StdDrawable.h>
#include <Spore\UTFWin\TreeNode.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\UIRenderer.h>
#include <Spore\UTFWin\VariableWidthDrawable.h>
#include <Spore\UTFWin\Window.h>
#include <Spore\UTFWin\CursorManager.h>

namespace Addresses(UTFWin)
{
	DefineAddress(GetAllocator, SelectAddress(0x951750, 0x951220));
}

namespace UTFWin
{
	namespace Addresses(UTFWinObject)
	{
		DefineAddress(new_, SelectAddress(0x951760, 0x951230));
		DefineAddress(delete_, SelectAddress(0x9517C0, 0x951290));
	}

	namespace Addresses(ButtonDrawableRadio)
	{
		DefineAddress(Paint, SelectAddress(0x965970, 0x9655F0));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x964A60, 0x9646D0));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));
		DefineAddress(GetTexCoords, SelectAddress(0x966E50, 0x966AD0));

		DefineAddress(SetSerializer, SelectAddress(0x9658E0, 0x965560));
		DefineAddress(GetProxyID, SelectAddress(0x964A10, 0x964680));

		DefineAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(SetImage, SelectAddress(0x9649C0, 0x964630));
	}

	namespace Addresses(ButtonDrawableStandard)
	{
		DefineAddress(Paint, SelectAddress(0x965970, 0x9655F0));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x964A20, 0x964690));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));
		DefineAddress(GetTexCoords, SelectAddress(0x966DC0, 0x966A40));

		DefineAddress(SetSerializer, SelectAddress(0x9658E0, 0x965560));
		DefineAddress(GetProxyID, SelectAddress(0x964A10, 0x964680));

		DefineAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(SetImage, SelectAddress(0x9649C0, 0x964630));
	}

	namespace Addresses(CascadeEffect)
	{
		DefineAddress(GetEventFlags, SelectAddress(0x9675B0, 0x8F2720));
		DefineAddress(HandleUIMessage, SelectAddress(0x967650, 0x9672D0));

		DefineAddress(SetSerializer, SelectAddress(0x967620, 0x9672A0));
		DefineAddress(GetProxyID, SelectAddress(0x9675E0, 0x967260));

		DefineAddress(ToWinProc, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(GetDelay, SelectAddress(0x980800, 0x97E440));
		DefineAddress(SetDelay, SelectAddress(0x9638F0, 0x967220));
		DefineAddress(GetInterval, SelectAddress(0x97F190, 0x97EE80));
		DefineAddress(SetInterval, SelectAddress(0x9675C0, 0x967240));
	}

	namespace Addresses(ComboBoxDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x969090, 0x968CC0));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x9681C0, 0x967E20));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));
		DefineAddress(GetImage, SelectAddress(0x968200, 0x967E60));

		DefineAddress(SetSerializer, SelectAddress(0x968FC0, 0x968C00));
		DefineAddress(GetProxyID, SelectAddress(0x968170, 0x967DD0));

		DefineAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(SetImage, SelectAddress(0x968220, 0x967E80));
	}

	namespace Addresses(cSPUIMessageBox)
	{
		DefineAddress(ShowDialog, SelectAddress(0x80A3B0, 0x809E60));
	}

	namespace Addresses(DialogDrawable)
	{
		DefineAddress(SetSerializer, SelectAddress(0x96D960, 0x96D560));
		DefineAddress(GetProxyID, SelectAddress(0x96BD30, 0x96B940));

		DefineAddress(Paint, SelectAddress(0x96DA20, 0x96D620));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x96BD70, 0x96B980));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));

		DefineAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(SetImage, SelectAddress(0x96BE50, 0x96BA60));
		DefineAddress(GetBackgroundColor, SelectAddress(0x96BE90, 0x96BAA0));
		DefineAddress(SetBackgroundColor, SelectAddress(0x980670, 0xFCCD90));
		DefineAddress(GetBackgroundTiling, SelectAddress(0x96BEB0, 0x96BAC0));
		DefineAddress(SetBackgroundTiling, SelectAddress(0x96BEA0, 0x96BAB0));
	}

	namespace Addresses(BiStateEffect)
	{
		DefineAddress(SetSerializer, SelectAddress(0x964000, 0x963CA0));

		DefineAddress(GetEventFlags, SelectAddress(0x9636E0, 0x9633E0));
		DefineAddress(HandleUIMessage, SelectAddress(0x9639F0, 0x9636A0));

		DefineAddress(ToWinProc, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(GetTime, SelectAddress(0x980800, 0x97E440));
		DefineAddress(SetTime, SelectAddress(0x9638F0, 0x967220));
		DefineAddress(GetTriggerType, SelectAddress(0x804E30, 0xFF3480));
		DefineAddress(SetTriggerType, SelectAddress(0x112EBC0, 0x987900));
		DefineAddress(GetEase, SelectAddress(0x97F110, 0x9635F0));
		DefineAddress(SetEase, SelectAddress(0x963910, 0x963610));
		DefineAddress(GetInterpolationType, SelectAddress(0xFCE1D0, 0x641760));
		DefineAddress(SetInterpolationType, SelectAddress(0x841AC0, 0xA6FE70));
		DefineAddress(GetDamping, SelectAddress(0x963980, 0x97EE60));
		DefineAddress(SetDamping, SelectAddress(0x963990, 0x963680));
	}

	namespace Addresses(FadeEffect)
	{
		DefineAddress(SetSerializer, SelectAddress(0x964000, 0x963CA0));
		DefineAddress(GetProxyID, SelectAddress(0x96F3C0, 0x96F020));

		DefineAddress(func84h, SelectAddress(0x96F380, 0x96EFE0));
	}

	namespace Addresses(FrameDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x96F6B0, 0x96F350));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x9516A0, 0x951190));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));

		DefineAddress(SetSerializer, SelectAddress(0x96F680, 0x96F320));
		DefineAddress(GetProxyID, SelectAddress(0x96F570, 0x96F1D0));
	}

	namespace Addresses(GlideEffect)
	{
		DefineAddress(GetEventFlags, SelectAddress(0x9636E0, 0x9633E0));
		DefineAddress(HandleUIMessage, SelectAddress(0x9639F0, 0x9636A0));

		DefineAddress(SetSerializer, SelectAddress(0x970380, 0x96FFE0));
		DefineAddress(GetProxyID, SelectAddress(0x970250, 0x96FEC0));

		DefineAddress(func80h, SelectAddress(0xE1CF40, 0x1154790));
		DefineAddress(func88h, SelectAddress(0x970310, 0x96FF70));

		DefineAddress(ToWinProc, SelectAddress(0x980500, 0x980230));
		DefineAddress(GetOffset, SelectAddress(0x766FC0, 0x6E6560));
		DefineAddress(SetOffset, SelectAddress(0x970360, 0x96FFC0));
	}

	namespace Addresses(Graphics2D)
	{
		DefineAddress(DrawTiledImage, SelectAddress(0x95CAA0, 0x95C550));
		DefineAddress(DrawSlicedTiledImage, SelectAddress(0x95CEF0, 0x95C9A0));
		DefineAddress(DrawSlicedStretchedImage, SelectAddress(0x95D4B0, 0x95CF60));
	}

	namespace Addresses(IButton)
	{
		DefineAddress(Create, SelectAddress(0x967420, 0x9670A0));
	}

	namespace Addresses(Image)
	{
		DefineAddress(SetSerializer, SelectAddress(0x957A60, 0x957510));
		DefineAddress(GetProxyID, SelectAddress(0x957A90, 0x957540));
		DefineAddress(GetImage, SelectAddress(0x806870, 0x806320));
		DefineAddress(SetBackground, SelectAddress(0x806F10, 0x8069C0));
		DefineAddress(SetBackgroundByKey, SelectAddress(0x8081F0, 0x807CA0));
	}

	namespace Addresses(ImageDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x97D520, 0x97D1E0));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x97D420, 0x97D0E0));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));

		DefineAddress(SetSerializer, SelectAddress(0x97D4B0, 0x97D170));
		DefineAddress(GetProxyID, SelectAddress(0x97D370, 0x97D020));

		DefineAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(SetImage, SelectAddress(0x97D3C0, 0x97D070));
		DefineAddress(GetImage, SelectAddress(0xFC8510, 0x6C0230));
		DefineAddress(GetImageDrawableFlags, SelectAddress(0x923C40, 0x93B630));
		DefineAddress(SetImageDrawableFlags, SelectAddress(0x980680, 0xFCC100));
		DefineAddress(SetImageDrawableFlag, SelectAddress(0x97D3F0, 0x97D0A0));
		DefineAddress(SetTiling, SelectAddress(0xA67DB0, 0xFD9460));
		DefineAddress(GetTiling, SelectAddress(0x80E390, 0xFC7E10));
		DefineAddress(SetScale, SelectAddress(0x97E770, 0x980500));
		DefineAddress(GetScale, SelectAddress(0x980800, 0x97E440));
		DefineAddress(SetAlignmentHorizontal, SelectAddress(0xA702D0, 0x985CE0));
		DefineAddress(GetAlignmentHorizontal, SelectAddress(0x6BD860, 0x7F5550));
		DefineAddress(SetAlignmentVertical, SelectAddress(0x985FC0, 0x97D0D0));
		DefineAddress(GetAlignmentVertical, SelectAddress(0x8D88F0, 0xFF02D0));
	}

	namespace Addresses(IImageDrawable)
	{
		DefineAddress(AddImageWindow, SelectAddress(0x807EC0, 0x807970));
	}

	namespace Addresses(InflateEffect)
	{
		DefineAddress(GetEventFlags, SelectAddress(0x9636E0, 0x9633E0));
		DefineAddress(HandleUIMessage, SelectAddress(0x9639F0, 0x9636A0));

		DefineAddress(SetSerializer, SelectAddress(0x97E8C0, 0x97E5D0));
		DefineAddress(GetProxyID, SelectAddress(0x97E780, 0x97E450));

		DefineAddress(func80h, SelectAddress(0xE1CF40, 0x1154790));
		DefineAddress(func88h, SelectAddress(0x97E840, 0x97E550));

		DefineAddress(ToWinProc, SelectAddress(0x980500, 0x980230));
		DefineAddress(GetScale, SelectAddress(0x980800, 0x97E440));
		DefineAddress(SetScale, SelectAddress(0x97E770, 0x980500));
	}

	namespace Addresses(InteractiveWinProc)
	{
		DefineAddress(HandleUIMessage, SelectAddress(0x951370, 0x950E50));
	}

	namespace Addresses(ITextEdit)
	{
		DefineAddress(Create, SelectAddress(0x98CDC0, 0x98CAA0));
	}

	namespace Addresses(IWindowManager)
	{
		DefineAddress(Get, SelectAddress(0x67CBF0, 0x67CA60));
	}

	namespace Addresses(ModulateEffect)
	{
		DefineAddress(GetEventFlags, SelectAddress(0x9636E0, 0x9633E0));
		DefineAddress(HandleUIMessage, SelectAddress(0x9639F0, 0x9636A0));

		DefineAddress(SetSerializer, SelectAddress(0x9804D0, 0x980200));
		DefineAddress(GetProxyID, SelectAddress(0x980410, 0x980140));

		DefineAddress(func84h, SelectAddress(0x9803A0, 0x9800D0));

		DefineAddress(ToWinProc, SelectAddress(0x980500, 0x980230));
		DefineAddress(GetColors, SelectAddress(0x9803D0, 0x980100));
		DefineAddress(SetColors, SelectAddress(0x9803F0, 0x980120));
	}

	namespace Addresses(PerspectiveEffect)
	{
		DefineAddress(GetEventFlags, SelectAddress(0x980770, 0x980470));
		DefineAddress(HandleUIMessage, SelectAddress(0x980780, 0x980480));

		DefineAddress(SetSerializer, SelectAddress(0x980850, 0x980590));
		DefineAddress(GetProxyID, SelectAddress(0x980810, 0x980510));

		DefineAddress(func80h, SelectAddress(0x9807E0, 0x9804E0));

		DefineAddress(ToWinProc, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(GetNearPlane, SelectAddress(0x980800, 0x97E440));
		DefineAddress(SetNearPlane, SelectAddress(0x97E770, 0x980500));
	}

	namespace Addresses(ProportionalLayout)
	{
		DefineAddress(Cast, SelectAddress(0x97EA40, 0x97E760));

		DefineAddress(SetSerializer, SelectAddress(0x97EDB0, 0x97EAD0));
		DefineAddress(GetProxyID, SelectAddress(0x97EAB0, 0x97E7D0));

		DefineAddress(ApplyLayout, SelectAddress(0x97ECC0, 0x97E9E0));
		DefineAddress(RevertLayout, SelectAddress(0x97ED30, 0x97EA50));

		DefineAddress(OnLayout, SelectAddress(0x97EAF0, 0x97E810));
	}

	namespace Addresses(RotateEffect)
	{
		DefineAddress(GetEventFlags, SelectAddress(0x9636E0, 0x9633E0));
		DefineAddress(HandleUIMessage, SelectAddress(0x9639F0, 0x9636A0));

		DefineAddress(SetSerializer, SelectAddress(0x9810B0, 0x980D60));
		DefineAddress(GetProxyID, SelectAddress(0x980EC0, 0x980BB00));

		DefineAddress(func80h, SelectAddress(0xE1CF40, 0x1154790));
		DefineAddress(func88h, SelectAddress(0x980FA0, 0x980C50));

		DefineAddress(ToWinProc, SelectAddress(0x980500, 0x980230));
		DefineAddress(GetRotationAxis, SelectAddress(0x766FC0, 0x6E6560));
		DefineAddress(SetRotationAxis, SelectAddress(0x980EA0, 0x980B80));
		DefineAddress(GetRotationAngle, SelectAddress(0xA0AAB0, 0xA0AAC0));
		DefineAddress(SetRotationAngle, SelectAddress(0xA0AAC0, 0x980BA0));
	}

	namespace Addresses(ScrollbarDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x982A00, 0x9826D0));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x981AC0, 0x981760));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));

		DefineAddress(SetSerializer, SelectAddress(0x982980, 0x982640));
		DefineAddress(GetProxyID, SelectAddress(0x981A70, 0x981710));

		DefineAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(SetImage, SelectAddress(0x981B20, 0x9817C0));
	}

	namespace Addresses(SimpleLayout)
	{
		DefineAddress(Cast, SelectAddress(0x97EA40, 0x97E760));

		DefineAddress(SetSerializer, SelectAddress(0x97EC70, 0x97E990));
		DefineAddress(GetProxyID, SelectAddress(0x97EAA0, 0x97E7B0));

		DefineAddress(ApplyLayout, SelectAddress(0x97EB70, 0x97E890));
		DefineAddress(RevertLayout, SelectAddress(0x97EBE0, 0x97E900));

		DefineAddress(OnLayout, SelectAddress(0x97EAF0, 0x97E810));
	}

	namespace Addresses(SliderDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x984C70, 0x9849A0));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x984240, 0x983F20));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));

		DefineAddress(SetSerializer, SelectAddress(0x984BA0, 0x9848D0));
		DefineAddress(GetProxyID, SelectAddress(0x9841E0, 0x983ED0));

		DefineAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(SetImage, SelectAddress(0x9863B0, 0x983F70));
	}

	namespace Addresses(SpinnerDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x984C70, 0x9849A0));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x984240, 0x983F20));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));

		DefineAddress(SetSerializer, SelectAddress(0x984BA0, 0x9848D0));
		DefineAddress(GetProxyID, SelectAddress(0x9841E0, 0x983ED0));

		DefineAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0));
		DefineAddress(SetImage, SelectAddress(0x9863B0, 0x983F70));
	}

	namespace Addresses(SporeStdDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x8320F0, 0x8318F0));
		DefineAddress(IsColliding, SelectAddress(0x831EA0, 0x8316A0));
		DefineAddress(GetDimensions, SelectAddress(0x831E10, 0x831610));
		DefineAddress(UseCollision, SelectAddress(0x988640, 0x9882F0));
		DefineAddress(GetScale, SelectAddress(0x8313F0, 0x830BF0));

		DefineAddress(SetSerializer, SelectAddress(0x831200, 0x8309F0));
		DefineAddress(GetProxyID, SelectAddress(0x831360, 0x830B60));
	}

	namespace Addresses(SporeStdDrawableImageInfo)
	{
		DefineAddress(SetSerializer, SelectAddress(0x8310D0, 0x8308C0));
		DefineAddress(GetProxyID, SelectAddress(0x8311E0, 0x8309D0));
	}

	namespace Addresses(SporeTooltipWinProc)
	{
		DefineAddress(GetEventFlags, SelectAddress(0x835B00, 0x835380));
		DefineAddress(HandleUIMessage, SelectAddress(0x8362B0, 0x835B30));

		DefineAddress(SetSerializer, SelectAddress(0x835E40, 0x8356C0));
		DefineAddress(GetProxyID, SelectAddress(0x8365C0, 0x8365C0));
	}

	namespace Addresses(StdDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x987FC0, 0x987C70));
		DefineAddress(IsColliding, SelectAddress(0x988360, 0x988010));
		DefineAddress(GetDimensions, SelectAddress(0x988670, 0x988320));
		DefineAddress(UseCollision, SelectAddress(0x988640, 0x9882F0));

		DefineAddress(SetSerializer, SelectAddress(0x987D60, 0x987A10));
		DefineAddress(GetProxyID, SelectAddress(0x987C60, 0x987910));

		DefineAddress(GetImage, SelectAddress(0x987C40, 0x9878E0));
		DefineAddress(SetImage, SelectAddress(0x987C00, 0x9878A0));
		DefineAddress(GetScaleType, SelectAddress(0x804E30, 0xFF3480));
		DefineAddress(SetScaleType, SelectAddress(0x112EBC0, 0x987900));
		DefineAddress(GetScaleArea, SelectAddress(0xFF0B60, 0x830B30));
		DefineAddress(SetScaleArea, SelectAddress(0x8313B0, 0x830BB0));
		DefineAddress(GetScaleFactor, SelectAddress(0xAD25F0, 0xAD2740));
		DefineAddress(SetScaleFactor, SelectAddress(0x8313D0, 0x830BD0));
		DefineAddress(GetHitMask, SelectAddress(0x97F0E0, 0xA1ACE0));
		DefineAddress(SetHitMask, SelectAddress(0x987E30, 0x987AE0));
		DefineAddress(GetHitFactor, SelectAddress(0x831340, 0x830B40));
		DefineAddress(SetHitFactor, SelectAddress(0x831350, 0x830B50));
	}

	namespace Addresses(TreeNode)
	{
		DefineAddress(SetSerializer, SelectAddress(0x990250, 0x98FF40));
		DefineAddress(GetProxyID, SelectAddress(0x98F960, 0x98F640));
		DefineAddress(func18h, SelectAddress(0x1053A60, 0xB267D0));
		DefineAddress(func1Ch, SelectAddress(0x991930, 0x991620));
		DefineAddress(func20h, SelectAddress(0x991940, 0x991630));
		DefineAddress(func24h, SelectAddress(0x9916B0, 0x9913A0));
		DefineAddress(func28h, SelectAddress(0x98F970, 0x98F650));
		DefineAddress(func2Ch, SelectAddress(0x66AD60, 0xB1E410));
		DefineAddress(func30h, SelectAddress(0xA36AD0, 0x1082A20));
		DefineAddress(func34h, SelectAddress(0x1053A60, 0xB267D0));
	}

	namespace Addresses(UILayout)
	{
		DefineAddress(Delete, SelectAddress(0x812130, 0x811BC0));
		DefineAddress(Load, SelectAddress(0x812730, 0x8121C0));
		DefineAddress(LoadByName, SelectAddress(0x8127C0, 0x812250));

		DefineAddress(FindWindowByID, SelectAddress(0x810C10, 0x810650));

		DefineAddress(SetParentWindow, SelectAddress(0x812810, 0x8122A0));
		DefineAddress(SetVisible, SelectAddress(0x810BF0, 0x810630));
		DefineAddress(GetContainerWindow, SelectAddress(0x810BD0, 0x810610));
		DefineAddress(IsVisible, SelectAddress(0x8106D0, 0x810110));
	}

	namespace Addresses(UIRenderer)
	{
		DefineAddress(GetGraphics2D, SelectAddress(0x95C0C0, 0x95BB70));
	}

	namespace Addresses(VariableWidthDrawable)
	{
		DefineAddress(Paint, SelectAddress(0x836840, 0x8360C0));
		DefineAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30));
		DefineAddress(GetDimensions, SelectAddress(0x9516A0, 0x951190));
		DefineAddress(UseCollision, SelectAddress(0x951320, 0x950E00));

		DefineAddress(SetSerializer, SelectAddress(0x836800, 0x836080));
		DefineAddress(GetProxyID, SelectAddress(0x836CB0, 0x836530));
	}

	namespace Addresses(Window)
	{
		DefineAddress(SetSerializer, SelectAddress(0x9609E0, 0x960480));
		DefineAddress(GetProxyID, SelectAddress(0x7F3780, 0x7F3250));
		DefineAddress(Initialize, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(Dispose, SelectAddress(0x9621D0, 0x961DD0));
		DefineAddress(DoMessage, SelectAddress(0x9608D0, 0x960370));
		DefineAddress(OnPaint, SelectAddress(0x9607D0, 0x960270));

		DefineAddress(GetParent, SelectAddress(0x95FE70, 0x95F930));
		DefineAddress(GetWindowManager, SelectAddress(0x804E60, 0x5AADB0));
		DefineAddress(func6, SelectAddress(0x95FE80, 0x1030E20));
		DefineAddress(GetControlID, SelectAddress(0xF3E580, 0xA02C70));
		DefineAddress(GetCommandID, SelectAddress(0x95FE90, 0xC2F7E0));
		DefineAddress(func9, SelectAddress(0x95FEA0, 0x575EA0));
		DefineAddress(GetCursorID, SelectAddress(0x95FEA0, 0x575EA0));
		DefineAddress(GetFlags, SelectAddress(0xFCE1D0, 0x641760));
		DefineAddress(GetState, SelectAddress(0xE464D0, 0x98F870));
		DefineAddress(GetShadeColor, SelectAddress(0x95FEB0, 0x95F940));
		DefineAddress(GetArea, SelectAddress(0x95FEC0, 0x95F950));
		DefineAddress(GetRealArea, SelectAddress(0xBFFB20, 0x95F960));
		DefineAddress(GetCaption, SelectAddress(0x8D6580, 0x8D6270));
		DefineAddress(GetTextFontID, SelectAddress(0x95FF10, 0x95F9B0));
		DefineAddress(func17, SelectAddress(0x95FED0, 0x95F970));
		DefineAddress(func18, SelectAddress(0x960210, 0x95FCB0));
		DefineAddress(func19, SelectAddress(0x960220, 0x6E8850));
		DefineAddress(SetControlID, SelectAddress(0x95FEE0, 0x95F980));
		DefineAddress(SetCommandID, SelectAddress(0x95FEF0, 0x95F990));
		DefineAddress(SetState, SelectAddress(0x960230, 0x95FCC0));
		DefineAddress(SetShadeColor, SelectAddress(0x960290, 0x95FD20));
		DefineAddress(SetArea, SelectAddress(0x960310, 0x95FDA0));
		DefineAddress(SetLocation, SelectAddress(0x960390, 0x95FE20));
		DefineAddress(SetSize, SelectAddress(0x9603F0, 0x95FE80));
		DefineAddress(SetLayoutArea, SelectAddress(0x960D30, 0x960820));
		DefineAddress(SetLayoutLocation, SelectAddress(0x960440, 0x95FED0));
		DefineAddress(SetLayoutSize, SelectAddress(0x9604A0, 0x95FF30));
		DefineAddress(func30, SelectAddress(0x9604F0, 0x95FF80));
		DefineAddress(SetCursorID, SelectAddress(0x9604F0, 0x95FF80));
		DefineAddress(SetFlag, SelectAddress(0x961B00, 0x9616B0));
		DefineAddress(SetCaption, SelectAddress(0x962270, 0x961E70));
		DefineAddress(SetTextFontID, SelectAddress(0x95FF00, 0x95F9A0));
		DefineAddress(func34, SelectAddress(0x960520, 0x95FFB0));
		DefineAddress(func35, SelectAddress(0x9602D0, 0x95FD60));
		DefineAddress(Invalidate, SelectAddress(0x960570, 0x960000));
		DefineAddress(Revalidate, SelectAddress(0x960E20, 0x960910));
		DefineAddress(InvalidateTransform, SelectAddress(0x9605A0, 0x960030));
		DefineAddress(func39, SelectAddress(0x961C00, 0x9617B0));
		DefineAddress(func40, SelectAddress(0x961C80, 0x961830));
		DefineAddress(GetFillColor, SelectAddress(0xBA5DD0, 0x885D80));
		DefineAddress(GetDrawable, SelectAddress(0xBFDB80, 0x960050));
		DefineAddress(SetFillColor, SelectAddress(0x95FF20, 0x95F9C0));
		DefineAddress(SetDrawable, SelectAddress(0x961390, 0x960E80));
		DefineAddress(func45, SelectAddress(0x961CF0, 0x9618A0));
		DefineAddress(func46, SelectAddress(0x962730, 0x962480));
		DefineAddress(func47, SelectAddress(0x961450, 0x960F40));
		DefineAddress(func48, SelectAddress(0x9605C0, 0x960060));
		DefineAddress(func49, SelectAddress(0x960640, 0x9600E0));
		DefineAddress(func50, SelectAddress(0x9615C0, 0x9610B0));
		DefineAddress(ContainsPoint, SelectAddress(0x961450, 0x960F40));
		DefineAddress(ToGlobalCoordinates, SelectAddress(0x9605C0, 0x960060));
		DefineAddress(ToLocalCoordinates, SelectAddress(0x960640, 0x9600E0));
		DefineAddress(ToLocalCoordinates2, SelectAddress(0x9615C0, 0x9610B0));
		// DefineAddress(GetChildrenBegin, SelectAddress(0x9616D0, 0x9611C0));
		// DefineAddress(GetChildrenEnd, SelectAddress(0x9616E0, 0x9611D0));
		DefineAddress(LocateChild, SelectAddress(0x9606A0, 0x960140));
		DefineAddress(AddWindow, SelectAddress(0x962A40, 0x962780));
		DefineAddress(RemoveWindow, SelectAddress(0x962AF0, 0x962830));
		DefineAddress(DisposeWindowFamily, SelectAddress(0x9606F0, 0x960190));
		DefineAddress(DisposeAllWindowFamilies, SelectAddress(0x960740, 0x9601E0));
		DefineAddress(BringToFront, SelectAddress(0x9616F0, 0x9611E0));
		DefineAddress(SendToBack, SelectAddress(0x961770, 0x961260));
		DefineAddress(FindWindowByID, SelectAddress(0x962780, 0x9624D0));
		DefineAddress(FindWindowTypeByID, SelectAddress(0x9627B0, 0x962500));
		DefineAddress(IsAncestorOf, SelectAddress(0x95FF90, 0x95FA30));
		DefineAddress(func63, SelectAddress(0x95FFE0, 0x95FA80));
		DefineAddress(func64, SelectAddress(0x960020, 0x95FAC0));
		DefineAddress(AddWinProc, SelectAddress(0x962310, 0x961F10));
		DefineAddress(RemoveWinProc, SelectAddress(0x961DD0, 0x961980));
		DefineAddress(GetNextWinProc, SelectAddress(0x961810, 0x961300));
		DefineAddress(func68, SelectAddress(0x960780, 0x960220));
		DefineAddress(SendMsg, SelectAddress(0x9607B0, 0x960250));
		DefineAddress(GetComponentName, SelectAddress(0x7F3770, 0x7F3240));
	}

	namespace Addresses(cCursorManager)
	{
		DefineAddress(Get, SelectAddress(0x67CC00, 0x67CA70));
		DefineAddress(Load, SelectAddress(0x802680, 0x802140));
		DefineAddress(GetActiveCursor, SelectAddress(0x8019F0, 0x801500));
		DefineAddress(SetActiveCursor, SelectAddress(0x802210, 0x801CF0));
		DefineAddress(ShowCursor, SelectAddress(0x801A00, 0x801510));
		DefineAddress(UseDropCursorIcon, SelectAddress(0x801F50, 0x801A90));
		DefineAddress(ShowDropCursorIcon, SelectAddress(0x801F80, 0x801AC0));
	}
}
#endif
