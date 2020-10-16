#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Editors\BakeManager.h>
#include <Spore\Editors\ContentValidation.h>
#include <Spore\Editors\Editor.h>
#include <Spore\Editors\EditorModel.h>
#include <Spore\Editors\EditorCamera.h>
#include <Spore\Editors\EditorRequest.h>
#include <Spore\Editors\EditorUI.h>
#include <Spore\Editors\PlayModeAnimations.h>
#include <Spore\Editors\SpeciesManager.h>
#include <Spore\Editors\CreatureWalkController.h>
#include <Spore\Editors\PlayModeActor.h>
#include <Spore\Editors\PlayModeBackgrounds.h>

namespace Editors
{
	namespace Addresses(IBakeManager)
	{
		DefineAddress(Get, SelectAddress(0x401010, 0x401010, 0x401010));
	}

	namespace Addresses(ContentValidation) {
		DefineAddress(IllegalCharacters_ptr, SelectAddress(0x15DEA54, , 0x15DA7C4));
		DefineAddress(ValidationEditableTests_ptr, SelectAddress(0x15DEA04, , 0x15DA7D4));
	}

	namespace Addresses(cEditor)
	{
		DefineAddress(sub_581F70, SelectAddress(0x581F70, 0x582250, 0x582250));
		DefineAddress(ptr, SelectAddress(0x15E9170, 0x015E5EF0, 0x15E4EF0));

		DefineAddress(Initialize, SelectAddress(0x583FD0, , 0x584300));
		DefineAddress(Dispose, SelectAddress(0x576B70, , 0x576C50));
		DefineAddress(OnEnter, SelectAddress(0x58E3B0, , 0x58E6D0));
		DefineAddress(OnExit, SelectAddress(0x5876F0, , 0x587A20));
		DefineAddress(OnKeyDown, SelectAddress(0x58A8E0, , 0x58AC10));
		DefineAddress(OnKeyUp, SelectAddress(0x585560, , 0x585890));
		DefineAddress(OnMouseDown, SelectAddress(0x588240, , 0x588570));
		DefineAddress(OnMouseUp, SelectAddress(0x58B320, , 0x58B650));
		DefineAddress(OnMouseMove, SelectAddress(0x5736C0, , 0x5737D0));
		DefineAddress(OnMouseWheel, SelectAddress(0x5859E0, , 0x585D10));
		DefineAddress(Update, SelectAddress(0x58BB20, , 0x58BE50));
	}

	namespace Addresses(EditorCamera)
	{
		DefineAddress(AddRef, SelectAddress(0xCF91C0, 0x671F20, 0x671F20));
		DefineAddress(Release, SelectAddress(0xD57BB0, 0xAE05F0, 0xAE0620));
		DefineAddress(Cast, SelectAddress(0x7C6A50, 0x5A2030, 0x5A2030));
		DefineAddress(OnAttach, SelectAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(OnDeattach, SelectAddress(0x66AD60, 0xB1E3E0, 0xB1E410));
		DefineAddress(OnEnter, SelectAddress(0x5A2040, 0x5A22F0, 0x5A22F0));
		DefineAddress(OnExit, SelectAddress(0x7E66D0, 0xC2E620, 0xC2E640));
		DefineAddress(Update, SelectAddress(0x5A3B40, 0x5A3E00, 0x5A3E00));
		DefineAddress(func24h, SelectAddress(0x5A1D90, 0x5A2050, 0x5A2050));
		DefineAddress(OnKeyDown, SelectAddress(0x5A1DA0, 0x5A2060, 0x5A2060));
		DefineAddress(OnKeyUp, SelectAddress(0x5A1E40, 0x5A2100, 0x5A2100));
		DefineAddress(OnMouseDown, SelectAddress(0x5A2C50, 0x5A2F00, 0x5A2F00));
		DefineAddress(OnMouseUp, SelectAddress(0x5A1EE0, 0x5A21A0, 0x5A21A0));
		DefineAddress(OnMouseMove, SelectAddress(0x5A2CB0, 0x5A2F70, 0x5A2F70));
		DefineAddress(OnMouseWheel, SelectAddress(0x5A22B0, 0x5A2560, 0x5A2560));
		DefineAddress(func40h, SelectAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(func44h, SelectAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(func48h, SelectAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(GetPropertyList, SelectAddress(0x6BD860, 0x7F5550, 0x7F55C0));
		DefineAddress(Initialize, SelectAddress(0x5A2330, 0x5A25E0, 0x5A25E0));
		DefineAddress(func54h, SelectAddress(0x5A2070, 0x5A2320, 0x5A2320));
	}

	namespace Addresses(EditorRequest) 
	{
		DefineAddress(Submit, SelectAddress(0x5A9090, , 0x5A92C0));
	}

	namespace Addresses(EditorUI)
	{
		DefineAddress(HandleMessage, SelectAddress(0x5DED50, 0x5DEEB0, 0x5DEEB0));

		DefineAddress(HandleUIMessage, SelectAddress(0x5DFEE0, 0x5E0040, 0x5E0040));

		DefineAddress(Load, SelectAddress(0x5DDC40, 0x5DDDA0, 0x5DDDA0));
	}

	namespace Addresses(PlayAnimButton)
	{
		DefineAddress(ReadAnimations, SelectAddress(0x62F1C0, 0x62F230, 0x62F210));
		DefineAddress(ReadPanel, SelectAddress(0x62EF90, 0x62F000, 0x62EFE0));
		DefineAddress(ReadAnimButton, SelectAddress(0x62EC70, 0x62ECE0, 0x62ECC0));
		DefineAddress(GenerateUI, SelectAddress(0x62E7C0, 0x62E830, 0x62E810));
	}

	namespace Addresses(cSpeciesManager) 
	{
		DefineAddress(Get, SelectAddress(0x401090, NO_ADDRESS, 0x401090));

		DefineAddress(GetSpeciesProfile, SelectAddress(0x4DF3E0, NO_ADDRESS, 0x4DF5C0));
	}

	namespace Addresses(EditorModel)
	{
		DefineAddress(GetCreationName, SelectAddress(0x4ADEA0, 0x4AE520, 0x4AE520));
		DefineAddress(SetColor, SelectAddress(0x4ADBF0, 0x4AE250, 0x4AE250));
	}

	namespace Addresses(CreatureWalkController)
	{
		DefineAddress(Update, SelectAddress(0x59B190, , 0x59B4B0));
		DefineAddress(SetTargetPosition, SelectAddress(0x59ADD0, , 0x59B0F0));
	}

	namespace Addresses(PlayModeActor)
	{
		DefineAddress(AddWalkAction, SelectAddress(0x62CE10, , 0x62CE30));
	}

	namespace Addresses(PlayModeBackground)
	{
		DefineAddress(SwitchBackground, SelectAddress(0x62F5F0, , 0x62F640));
		DefineAddress(DisableBackground, SelectAddress(0x62F900, , 0x62F950));
	}
}
#endif
