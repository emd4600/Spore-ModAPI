#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Editors\BakeManager.h>
#include <Spore\Editors\ContentValidation.h>
#include <Spore\Editors\Editor.h>
#include <Spore\Editors\EditorModel.h>
#include <Spore\Editors\EditorCamera.h>
#include <Spore\Editors\EditorRequest.h>
#include <Spore\Editors\EditorRigblock.h>
#include <Spore\Editors\EditorUI.h>
#include <Spore\Editors\cEditorSkin.h>
#include <Spore\Editors\TuningSpine.h>
#include <Spore\Editors\PlayModeAnimations.h>
#include <Spore\Editors\EditorPlayMode.h>
#include <Spore\Editors\PlayModeUI.h>
#include <Spore\Editors\SpeciesManager.h>
#include <Spore\Editors\EditorCreatureController.h>
#include <Spore\Editors\PlayModeActor.h>
#include <Spore\Editors\PlayModeBackgrounds.h>
#include <Spore\Editors\cEditorAnimEvent.h>
#include <Spore\Editors\cEditorAnimWorld.h>
#include <Spore\Editors\cEditorSkinMesh.h>
#include <Spore\Editors\cCreatureDataResource.h>

#ifdef SDK_TO_GHIDRA
namespace Editors
{
	DefineAddress(sEditor, SelectAddress(0x15E9170, 0x15E4EF0));
}
#endif

namespace Editors
{
	namespace Addresses(IBakeManager)
	{
		DefineAddress(Get, SelectAddress(0x401010, 0x401010));
	}

	namespace Addresses(cTuningSpine)
	{
		DefineAddress(Get, SelectAddress(0x401070, 0x401070));
	}

	namespace Addresses(ContentValidation) {
#ifndef SDK_TO_GHIDRA
		DefineAddress(IllegalCharacters_ptr, SelectAddress(0x15DEA54, 0x15DA7C4));
		DefineAddress(ValidationEditableTests_ptr, SelectAddress(0x15DEA04, 0x15DA7D4));
#else
		DefineAddress(sIllegalCharacters, SelectAddress(0x15DEA54, 0x15DA7C4));
		DefineAddress(sValidationEditableTests, SelectAddress(0x15DEA04, 0x15DA7D4));
#endif
	}

	namespace Addresses(cEditor)
	{
		DefineAddress(sub_581F70, SelectAddress(0x581F70, 0x582250));
#ifndef SDK_TO_GHIDRA
		DefineAddress(ptr, SelectAddress(0x15E9170, 0x15E4EF0));
#endif

		DefineAddress(Initialize, SelectAddress(0x583FD0, 0x584300));
		DefineAddress(Dispose, SelectAddress(0x576B70, 0x576C50));
		DefineAddress(OnEnter, SelectAddress(0x58E3B0, 0x58E6D0));
		DefineAddress(OnExit, SelectAddress(0x5876F0, 0x587A20));
		DefineAddress(OnKeyDown, SelectAddress(0x58A8E0, 0x58AC10));
		DefineAddress(OnKeyUp, SelectAddress(0x585560, 0x585890));
		DefineAddress(OnMouseDown, SelectAddress(0x588240, 0x588570));
		DefineAddress(OnMouseUp, SelectAddress(0x58B320, 0x58B650));
		DefineAddress(OnMouseMove, SelectAddress(0x5736C0, 0x5737D0));
		DefineAddress(OnMouseWheel, SelectAddress(0x5859E0, 0x585D10));
		DefineAddress(Update, SelectAddress(0x58BB20, 0x58BE50));

		DefineAddress(SetEditorModel, SelectAddress(0x5867D0, 0x586B00));
		DefineAddress(CommitEditHistory, SelectAddress(0x5860E0, 0x586410));
		DefineAddress(Undo, SelectAddress(0x58A270, 0x58A5A0));
		DefineAddress(Redo, SelectAddress(0x58A620, 0x58A950));
		DefineAddress(SetActiveMode, SelectAddress(0x586F40, 0x587270));
		DefineAddress(SetCreatureToNeutralPose, SelectAddress(0x573860, 0x573970));
		DefineAddress(AddCreature, SelectAddress(0x582D00, 0x582FE0));
		DefineAddress(PostEventToActors, SelectAddress(0x574000, 0x574110));

		DefineAddress(HandleMessage, SelectAddress(0x591C80, 0x591FA0));
	}

	namespace Addresses(EditorCamera)
	{
		DefineAddress(AddRef, SelectAddress(0xCF91C0, 0x671F20));
		DefineAddress(Release, SelectAddress(0xD57BB0, 0xAE0620));
		DefineAddress(Cast, SelectAddress(0x7C6A50, 0x5A2030));
		DefineAddress(OnAttach, SelectAddress(0x101B0F0, 0xDDE930));
		DefineAddress(OnDeattach, SelectAddress(0x66AD60, 0xB1E410));
		DefineAddress(OnEnter, SelectAddress(0x5A2040, 0x5A22F0));
		DefineAddress(OnExit, SelectAddress(0x7E66D0, 0xC2E640));
		DefineAddress(Update, SelectAddress(0x5A3B40, 0x5A3E00));
		DefineAddress(func24h, SelectAddress(0x5A1D90, 0x5A2050));
		DefineAddress(OnKeyDown, SelectAddress(0x5A1DA0, 0x5A2060));
		DefineAddress(OnKeyUp, SelectAddress(0x5A1E40, 0x5A2100));
		DefineAddress(OnMouseDown, SelectAddress(0x5A2C50, 0x5A2F00));
		DefineAddress(OnMouseUp, SelectAddress(0x5A1EE0, 0x5A21A0));
		DefineAddress(OnMouseMove, SelectAddress(0x5A2CB0, 0x5A2F70));
		DefineAddress(OnMouseWheel, SelectAddress(0x5A22B0, 0x5A2560));
		DefineAddress(func40h, SelectAddress(0x101B0F0, 0xDDE930));
		DefineAddress(func44h, SelectAddress(0x101B0F0, 0xDDE930));
		DefineAddress(func48h, SelectAddress(0x101B0F0, 0xDDE930));
		DefineAddress(GetPropertyList, SelectAddress(0x6BD860, 0x7F55C0));
		DefineAddress(Initialize, SelectAddress(0x5A2330, 0x5A25E0));
		DefineAddress(func54h, SelectAddress(0x5A2070, 0x5A2320));
	}

	namespace Addresses(EditorRequest) 
	{
		DefineAddress(Submit, SelectAddress(0x5A9090, 0x5A92C0));
	}

	namespace Addresses(EditorUI)
	{
		DefineAddress(HandleMessage, SelectAddress(0x5DED50, 0x5DEEB0));

		DefineAddress(HandleUIMessage, SelectAddress(0x5DFEE0, 0x5E0040));

		DefineAddress(Load, SelectAddress(0x5DDC40, 0x5DDDA0));
	}

	namespace Addresses(PlayAnimButton)
	{
		DefineAddress(ReadAnimations, SelectAddress(0x62F1C0, 0x62F210));
		DefineAddress(ReadPanel, SelectAddress(0x62EF90, 0x62EFE0));
		DefineAddress(ReadAnimButton, SelectAddress(0x62EC70, 0x62ECC0));
		DefineAddress(GenerateUI, SelectAddress(0x62E7C0, 0x62E810));
	}
	namespace Addresses(PlayModeAnimations)
	{
		DefineAddress(ReadAnimations, SelectAddress(0x62F1C0, 0x62F210));
		DefineAddress(ReadPanel, SelectAddress(0x62EF90, 0x62EFE0));
		DefineAddress(ReadAnimButton, SelectAddress(0x62EC70, 0x62ECC0));
		DefineAddress(GenerateUI, SelectAddress(0x62E7C0, 0x62E810));
	}

	namespace Addresses(cSpeciesManager) 
	{
		DefineAddress(Get, SelectAddress(0x401090, 0x401090));

		DefineAddress(GetSpeciesProfile, SelectAddress(0x4DF3E0, 0x4DF5C0));
	}

	namespace Addresses(EditorModel)
	{
		DefineAddress(SetName, SelectAddress(0x4ADC20, 0x4AE280));
		DefineAddress(SetDescription, SelectAddress(0x4ADDE0, 0x4AE440));
		DefineAddress(GetCreationName, SelectAddress(0x4ADEA0, 0x4AE520));
		DefineAddress(SetColor, SelectAddress(0x4ADBF0, 0x4AE250));
		DefineAddress(Load, SelectAddress(0x4AE240, 0x4AE8D0));
		DefineAddress(Save, SelectAddress(0x4AF0F0, 0x4AF780));
		DefineAddress(Dispose, SelectAddress(0x4AD1F0, 0x4AD850));
	}

	namespace Addresses(CreatureWalkController)
	{
		DefineAddress(Update, SelectAddress(0x59B190, 0x59B4B0));
		DefineAddress(SetTargetPosition, SelectAddress(0x59ADD0, 0x59B0F0));
	}

	namespace Addresses(EditorCreatureController)
	{
		DefineAddress(Update, SelectAddress(0x59B190, 0x59B4B0));
		DefineAddress(SetTargetPosition, SelectAddress(0x59ADD0, 0x59B0F0));
	}

	namespace Addresses(PlayModeActor)
	{
		DefineAddress(AddWalkAction, SelectAddress(0x62CE10, 0x62CE30));
	}

	namespace Addresses(PlayModeBackgrounds)
	{
		DefineAddress(SwitchBackground, SelectAddress(0x62F5F0, 0x62F640));
		DefineAddress(DisableBackground, SelectAddress(0x62F900, 0x62F950));
		DefineAddress(Load, SelectAddress(0x62FC70, 0x62FCC0));
		DefineAddress(LoadBackgroudFiles, SelectAddress(0x62FBA0, 0x62FBF0));
		DefineAddress(HandleUIButton, SelectAddress(0x62F7D0, 0x62F820));
		DefineAddress(ToggleBackgroundButtonHighlights, SelectAddress(0x62F320, 0x62F370));
		DefineAddress(UpdatePageNumbers, SelectAddress(0x62F520, 0x62F570));
		DefineAddress(UpdateBackgroundButtons, SelectAddress(0x62F6C0, 0x62F710));
		DefineAddress(IsBlackBackground, SelectAddress(0x62F6A0, 0x62F6F0));
	}

	namespace Addresses(cEditorSkin)
	{
		DefineAddress(GetMesh, SelectAddress(0x4C4280, 0x4C4A50));
		DefineAddress(HasFinishedPainting, SelectAddress(0x4C5170, 0x4C5920));
		DefineAddress(PaintSkin, SelectAddress(0x4C4AA0, 0x4C5270));
	}

	namespace Addresses(cEditorAnimEvent)
	{
		DefineAddress(MessageSend, SelectAddress(0x59D610, 0x59D8B0));
		DefineAddress(MessagePost, SelectAddress(0x59D5A0, 0x59D840));
	}

	namespace Addresses(cEditorAnimWorld)
	{
		DefineAddress(GetCreatureController, SelectAddress(0x59C820, 0x59CAC0));
		DefineAddress(GetAnimatedCreature, SelectAddress(0x59C7D0, 0x59CA70));
		DefineAddress(DestroyCreature, SelectAddress(0x59C440, 0x59C6E0));
		DefineAddress(SetTargetPosition, SelectAddress(0x59CC60, 0x59CF00));
		DefineAddress(SetTargetAngle, SelectAddress(0x59CC00, 0x59CEA0));
	}

	namespace Addresses(cCreatureDataResource)
	{
		DefineAddress(Read, SelectAddress(0x4BECA0, 0x4BF970));
		DefineAddress(Write, SelectAddress(0x4BEFE0, 0x4BFCB0));
	}

	namespace Addresses(EditorRigblock)
	{
		DefineAddress(SetShadedDisplay, SelectAddress(0x43A980, 0x43ACF0));
	}

	namespace Addresses(cEditorSkinMeshBase)
	{
		DefineAddress(FromRigblocks, SelectAddress(0x4C6E90, 0x4C7460));
	}

	namespace Addresses(EditorPlayMode)
	{
		DefineAddress(Load, SelectAddress(0x62A3F0, 0x62A400));
		DefineAddress(Dispose, SelectAddress(0x62C930, 0x62C940));
		DefineAddress(GetNextEnvironmentReactionAnimID, SelectAddress(0x6286C0, 0x6286D0));
		DefineAddress(sub_628CC0, SelectAddress(0x628CC0, 0x628CD0));
		DefineAddress(HandleUIButton, SelectAddress(0x628D70, 0x628D80));
	}

	namespace Addresses(PlayModeUI)
	{
		DefineAddress(HandleUIMessage, SelectAddress(0x6374B0, 0x6377B0));
		DefineAddress(SetWindowVisible, SelectAddress(0x635450, 0x635750));
		DefineAddress(FindWindowByID, SelectAddress(0x634AB0, 0x634DB0));
	}
}
#endif
