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

#include <Spore\Clock.h>
#include <Spore\MathUtils.h>

#include <Spore\App\PropertyList.h>
#include <Spore\App\cViewer.h>
#include <Spore\App\IGameMode.h>
#include <Spore\App\IGameModeManager.h>

#include <Spore\Palettes\PaletteMain.h>
#include <Spore\Palettes\PaletteUI.h>
#include <Spore\Editors\EditorRigblock.h>
#include <Spore\Editors\EditorCamera.h>
#include <Spore\Editors\EditorModel.h>
#include <Spore\Editors\EditorPlayMode.h>
#include <Spore\Editors\EditorRequest.h>
#include <Spore\Editors\EditorLimits.h>
#include <Spore\Editors\INameableEntity.h>
#include <Spore\Editors\cEditorSkin.h>
#include <Spore\Editors\cEditorAnimEvent.h>
#include <Spore\Editors\cEditorAnimWorld.h>

#include <Spore\Graphics\Model.h>
#include <Spore\Graphics\ILayer.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Graphics\IShadowWorld.h>
#include <Spore\Graphics\ShaderData.h>

#include <Spore\Swarm\IEffectsWorld.h>

#include <Spore\UI\HintManager.h>
#include <Spore\UI\EditorNamePanel.h>

#include <Spore\UTFWin\UILayout.h>

#include <EASTL\map.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

/// Access the active editor object; check Editors::cEditor
#define Editor (*Editors::GetEditor())

#define cEditorPtr eastl::intrusive_ptr<Editors::cEditor>

// these are still placeholders
typedef void UnkClass1;
typedef void UnkClass2;
typedef void UnkClass4;

/// @brief Everything related with the editors (except adventure editor)
namespace Editors
{
	class EditorUI;

	enum class Mode : int
	{
		BuildMode = 0,
		PaintMode = 1,
		PlayMode = 2
	};

	enum EditorRenderLayers
	{
		/// Renders the background model world without shadows.
		kRenderLayerBackground = 0xC,
		/// Renders the creation and the pedestal (with shadows) 
		kRenderLayerPedestalCreation = 0xD,
		// 0x0F  only for paint mode
		// 0x11  pedestal
		// 0x14
		// 0x1A
	};

	enum ComplexityFlags
	{
		kComplexityFlagBlock = 0x1,
		kComplexityFlagBone = 0x2,
		kComplexityFlagBakedBlock = 0x4,
	};

	/// Structure that records the state of the editor (current mode, budget, etc) for undo/redo history
	class EditorStateEditHistory
		: public DefaultRefCounted
	{
	public:
		/* 08h */	int mBudget;
		/* 0Ch */	Mode mMode;
		/* 10h */	int field_10;
		/* 14h */	bool field_14;
		/* 15h */	bool field_15;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
	};
	ASSERT_SIZE(EditorStateEditHistory, 0x2C);

	/// Main class for editors. A single instance of this class exists during the whole game, and is used for all
	/// editors (except the Adventure editor, that one uses App::cScenarioMode); you can access it with the Editor macro.
	class cEditor 
		: public App::IGameMode
		, public Graphics::ILayer
		, public UI::IHintConditioner
		, public INameableEntity
		, public App::IMessageListener
		, public DefaultRefCounted
		//TODO one vftable more
	{
	public:

		virtual bool HandleMessage(uint32_t messageID, void* msg) override;

		/* 10h */	virtual bool Initialize(App::IGameModeManager* pManager) override;
		/* 14h */	virtual bool Dispose() override;
		/* 18h */	virtual bool OnEnter() override;
		/* 1Ch */	virtual void OnExit() override;
		/* 24h */	virtual bool OnKeyDown(int virtualKey, KeyModifiers modifiers) override;
		/* 28h */	virtual bool OnKeyUp(int virtualKey, KeyModifiers modifiers) override;
		/* 2Ch */	virtual bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
		/* 30h */	virtual bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
		/* 34h */	virtual bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState) override;
		/* 38h */	virtual bool OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState) override;
		/* 3Ch */	virtual void Update(float delta1, float delta2) override;


		//PLACEHOLDER virtual method 54h -> reads temporary database
		//PLACEHOLDER virtual method 58h -> wrties temporary database

		/// Changes the current editor model, updating the creation with the parts and paints of the new editor model.
		/// @param pEditorModel
		void SetEditorModel(EditorModel* pEditorModel);

		/// Get current editor model, which is the creation with the parts and paints.
		/// @returns
		inline EditorModel* GetEditorModel() const;

		/// Adds an edit history (undo/redo) entry based on the current model of the editor.
		/// @param arg1
		/// @param pStateHistory
		void CommitEditHistory(bool arg1, EditorStateEditHistory* pStateHistory = nullptr);

		void Undo(bool, bool);
		void Redo();

		/// Returns true if the editor is currently in the given mode.
		/// @param mode Either build, paint or play mode.
		/// @returns
		bool IsMode(Mode mode) const;

		void SetActiveMode(Mode mode, bool);

		/// Returns true if the editor is currently active.
		/// @returns
		bool IsActive() const;

		/// Returns the camera used to navigate and view the editor.
		/// @returns
		EditorCamera* GetCamera();

		/// Returns the editor skin, which is the model and texture generating system for creations that use
		/// skinpaints and metaballs (i.e. creatures and flora). For the rest of creation types, this returns nullptr.
		/// @returns
		cEditorSkin* GetSkin();

		/// Returns the class that manages the creature animations in the editor.
		/// @returns
		cEditorAnimWorld* GetAnimWorld();

		// _ZN6Editor9ScalePartEP14EditorRigblockii
		// Editor::ScalePart(EditorRigblock *, int, int)


		bool sub_581F70(EditorRigblock* part, void* activeHandle, int value);

		// loc_573BB1 -> set part is hovered?


		void RemovePart(EditorRigblock* part);  //PLACEHOLDER

		/// Emits a `cEditorAnimEvent` with ID `0x6581B78E`, which makes the creature (if any) stop
		/// its current animation and return to the neutral, motionless pose.
		void SetCreatureToNeutralPose();

		bool AddCreature(int, const ResourceKey* key = nullptr);

	public:

		int vftable_1C;

		/// The App::IGameModeManager that holds this editor.
		/* 20h */	IGameModeManagerPtr	mpGameModeMgr;
		/// The App::PropertyList that contains the configuration of the current editor.
		/* 24h */	PropertyListPtr		mpPropList;

		/// The current position of the cursor in the editor.
		/* 28h */	Math::Point mMousePosition;
		/* 30h */	int mMouseFlags;
		/* 34h */	MouseState mMouseState;

		/* 38h */	bool field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	int field_40;  // not initialized
		/* 44h */	int field_44;  // not initialized
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	int field_54;
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	float field_68;  // Set to 0 when mouse click, and when changing mode
		/// Time to wait before starting animated creature (in milliseconds).
		/* 6Ch */	float mCreatureIdleActivationTime;
		/* 70h */	float field_70;
		/* 74h */	bool field_74;

		//TODO ManagedPtr
		/* 78h */	EditorUI* mpEditorUI;

		/* 7Ch */	EditorPlayMode* mpPlayMode;  // TODO intrusive_ptr
		/// THe light to be used by the editor.
		/* 80h */	ILightingWorldPtr mpLightingWorld;
		/// The model world that contains the pedestal and test environment model, and also editor rigblocks
		/* 84h */	IModelWorldPtr mpMainModelWorld;
		/* 88h */	IModelWorldPtr field_88;
		/// The model world that contains the background model.
		/* 8Ch */	IModelWorldPtr mpBackgroundModelWorld;
		/* 90h */	int field_90;  // related with havok world?
		/* 94h */	IEffectsWorldPtr mpEffectWorld;

		// use appropiate container!
		// you can get it with virtual function 40h
		/* 98h */	EditorModel* mpEditorModel;	// TODO is it intrusive_ptr?

		/* 9Ch */	int field_9C;  // another editor model?
		/// The model to be used for the pedestal in the editor. It belongs to mpPedestalModelWorld.
		/* A0h */	ModelPtr mpPedestalModel;
		/// The model to be used for the test environment in the editor. It belongs mpPedestalModelWorld.
		/* A4h */	ModelPtr mpTestEnvironmentModel;
		/// The model to be used for the background in the editor. It belongs to mpBackgroundModelWorld.
		/* A8h */	ModelPtr mpBackgroundModel;  // used in loc_5874D8
		/// A background model used in accessories editors. It belongs to mpBackgroundModelWorld.
		/* ACh */	ModelPtr mpAccBackgroundModel;
		/* B0h */	eastl::string16 field_B0;
		// /* B9h */	bool editorShowAbilityIcons;  // might also be 4B6h ?

		/* C0h */	int field_C0;  // not initialized  // lastMouseClick[2] ?
		/* C4h */	int field_C4;  // not initialized
		/* C8h */	int field_C8;  // not initialized

		// also valid for spines
		/// Rigblock that is being hovered, and where actions like mouse wheel scaling will be applied
		/* CCh */	EditorRigblockPtr mpActivePart;
		/* D0h */	EditorRigblockPtr mpMovingPart;  // the part that is being moved, only when mouse is being clicked
		/* D4h */	EditorRigblockPtr mpSelectedPart;  // also valid for spines
		/* D8h */	EditorRigblockPtr field_D8;
		/* DCh */	EditorRigblockPtr field_DC;
		/* E0h */	bool field_E0;
		/* E4h */	EditorBaseHandle* mpActiveHandle;  // morph handles
		/// Is the mouse over the skin of the creature?
		/* E8h */	bool mbMouseIsInSkin;
		/* E9h */	bool field_E9;
		/* ECh */	int field_EC;
		/* F0h */	int field_F0;
		/* F4h */	int field_F4;

		// /* FCh */	ResourceKey editorVertebraModel; ??
		// /* 110h */	intrusive_ptr<UTFWin::UILayout> activeDialog; ??
		char _padding_F8[0x48];

		/* 140h */	bool field_140;  // true
		/* 141h */	bool field_141;
		/* 142h */	bool field_142;
		/* 143h */	bool field_143;  // not initialized
		/* 144h */	bool field_144;  // true
		/* 148h */	ObjectPtr field_148;
		/* 14Ch */	int field_14C; // vertebra? only present in creature-like editor
		/* 150h */	cEditorSkinPtr mpEditorSkin;  // something related with painting?  uses sub_4C3E70 to return something that parts also use
		/* 154h */	cEditorSkinPtr field_154;

		//// just guesses, apparently it calls DefaultRefCounted.Unuse()
		///* 158h */	DefaultRefCounted* field_158;
		///* 15Ch */	DefaultRefCounted* field_15C;  // something related with "UTFWin/RWTextureResource" ?
		///* 160h */	eastl::vector<DefaultRefCounted*> field_160;  // we only know it calls the DefaultRefCounted* destructor

		/* 158h */	int field_158;
		/* 15Ch */	int field_15C;
		/* 160h */	eastl::vector<eastl::intrusive_ptr<EditorStateEditHistory>> mStateEditHistory;
		/* 174h */	eastl::vector<cEditorResourcePtr> mEditHistory;
		/* 188h */	int mEditHistoryIndex;
		/// The ID of the .prop configuration file of the current editor.
		/* 18Ch */	uint32_t mEditorName;  // 0x465C50BA
		/* 190h */	bool mbTransitionHideUI;  // true
		/* 191h */	bool mbTransitionCenterCamera;  // true
		/* 194h */	uint32_t mTransitionAnimationID;
		/* 198h */	int field_198;  // 2
		/* 19Ch */	uint32_t mTransitionEffectID;
		/* 1A0h */	int field_1A0;  // 2
		/* 1A4h */	int field_1A4;  // 2
		/* 1A8h */	int field_1A8;  // 2
		/* 1ACh */	int field_1AC;
		/// Maps a creation format extension to its default editor. For example, 'crt' is mapped to 'CreatureEditorExtraLarge'.
		/* 1B0h */	eastl::map<uint32_t, uint32_t> mDefaultEditors;
		/* 1CCh */	EditorRequestPtr mEditorRequest;	// in 35h there is bool editorAllowNameEdit;
		/* 1D0h */	ResourceKey mParentAssetKey;
		/* 1DCh */	eastl::string16 field_1DC;
		/* 1ECh */	int field_1EC;
		/* 1F0h	*/	int field_1F0;
		/* 1F4h	*/	int field_1F4;
		/// Thumbnail camera, when editor asset is saved, this is the camera used to generate the thumbnail
		/* 1F8h	*/	uint32_t mCameraThumbnailID;
		/// Palette camera, this is the camera that will be used to take thumbnails and display 3d swatches in the editor
		/* 1FCh	*/	uint32_t mCameraPaletteID;
		/// Key to png icon for editor currency
		/* 200h	*/	ResourceKey mCurrencyIconName;
		/// Unicode character for editor currency
		/* 20Ch */	char16_t mCurrencyChar;  // not initialized
		/* 20Dh */	bool field_20D;   // not initialized
		/// Whether a background music is played or not.
		/* 20Eh */	bool mbBackgroundMusic;
		/// The key to the sound patch to play for the background music.
		/* 210h */	uint32_t mBackgroundMusicPatchID;
		/// Instance ID for part mode tutorial.
		/* 214h */	uint32_t mTutorialPartModeID;
		/// Instance ID for play mode tutorial.
		/* 218h */	uint32_t mTutorialPlayModeID;
		/// Instance ID for paint mode tutorial.
		/* 21Ch */	uint32_t mTutorialPaintModeID;
		/* 220h */	int field_220;
		/* 224h */	int field_224;
		/* 228h */	int field_228;
		/* 22Ch */	int field_22C;
		/* 230h */	int field_230;
		/* 234h */	int field_234;
		/* 238h */	int field_238;
		/* 23Ch */	int field_23C;
		/* 240h */	int field_240;
		/* 244h */	int field_244;
		/* 248h */	int field_248;
		/* 24Ch */	int field_24C;
		/* 250h */	int field_250;
		/* 254h */	int field_254;
		/* 258h */	int field_258;
		/* 25Ch */	int field_25C;
		/* 260h */	int field_260;
		/* 264h */	int field_264;
		/* 268h */	int field_268;
		/* 26Ch */	int field_26C;
		/* 270h */	int field_270;
		/* 274h */	int field_274;
		/* 278h */	uint32_t mPlayModeEntryEffectID;
		/* 27Ch */	uint32_t mPlayModeExitEffectID;
		/// The ID for the sky box effect.
		/* 280h */	uint32_t mSkyBoxEffectID;
		/* 284h */	int field_284;
		/* 288h */	float field_288;  // 1.2
		/* 28Ch */	TexturePtr mpThumbnailTexture;
		/* 290h */	int field_290;
		/* 294h */	IShadowWorldPtr mpShadowWorld;
		/* 298h */	Graphics::ShadowMapInfo* mpShadowMapInfo;
		/* 29Ch */	int field_29C;
		/* 2A0h */	int field_2A0;
		/* 2A4h */	int field_2A4;
		/// The save extension key which will be parsed both into a key and a three letter extension.
		/* 2A8h */	uint32_t mSaveExtension;
		/// The save directory key, Resource::SaveAreaID
		/* 2ACh */	uint32_t mSaveDirectory;
		/* 2B0h */	bool mIsActive;
		/* 2B1h */	char field_2B1;  // not initialized
		/* 2B2h */	bool mbShowVertebrae;  // true
		/* 2B3h */	char field_2B3;
		/* 2B4h */	char field_2B4;
		/* 2B5h */	bool mbDisableCreatureAnimIK;  // not initialized
		/// The width of the space that the model skin is constrained to.
		/* 2B8h */	float mBoundSize;  // 2.0
		/// The width of the space that the feet are constrained to.
		/* 2BCh */	float mFeetBoundSize;  // 2.0
		/// The base of the cylinder.
		/* 2C0h */	float mMinHeight;  // -2.0
		/// The height of te cylinder.
		/* 2C4h */	float mfMaxHeight;  // 2.0
		/// Minimum width a model has to be to be playable.
		/* 2C8h */	float mMinPlayableWidth;  // MAX_FLOAT
		/// Minimum depth a model has to be to be playable.
		/* 2CCh */	float mMinPlayableDepth;  // MAX_FLOAT
		/// Minimum height a model has to be to be playable.
		/* 2D0h */	float mMinPlayableHeight;  // MAX_FLOAT
		/// The minimum height a legless creature is allowed to be on load.
		/* 2D4h */	float mMinimumLeglessCreatureHeight;
		/// Which complexity limits to show in meter, possible values in the ComplexityFlags enum.
		/* 2D8h */	uint32_t mViewableComplexityFlags;  
		/// Maximum complexity of blocks allowed in this editor.
		/* 2DCh */	int mComplexityLimit;  // -1
		/// Maximum bone complexity of blocks allowed in this editor
		/* 2E0h */	int mBoneComplexityLimit;  // -1
		/// Maximum number of baked blocks allowed in this editor
		/* 2E4h */	int mMaxBakedBlocks;  // -1
		/* 2E8h */	int field_2E8;  // not initialized
		/// Maximum geometric score (from vertices/indices) allowed in this editor
		/* 2ECh */	float mMaxGeomScore;
		/* 2F0h */	bool mbCellPinningToRigBlocks;  // not initialized
		/* 2F1h */	bool mbUseSkin;
		/* 2F2h */	bool mbUseSpine;
		/* 2F3h */	bool mbInitSpine;
		/* 2F4h */	bool field_2F4;
		/* 2F5h */	bool mbAllowAsymmetry;
		/* 2F6h */	bool mbOnlyEditFromPalette;
		/* 2F7h */	bool mbMoveModelToGround;
		/* 2F8h */	bool mbMoveModelToCenterOfMass;
		/// Has the editor use the bounds as a deletion option.
		/* 2F9h */	bool mbUseBoundsForDelete;  // true
		/* 2FAh */	bool editorTranslateModelOnSave;
		/// The ID for the sporepedia config to launch from the editor.
		/* 2FCh */	uint32_t mSporepediaConfigID;
		/// The ID for the sporepedia config to launch from the editor when you can switch editors
		/* 300h */	uint32_t mSporepediaCanSwitchConfigID;
		/// Translation flags.
		/* 304h */	uint32_t mModelTranslationOptions;
		/* 308h */	int field_308;
		/* 30Ch */	int field_30C;
		/// Whether to save the parent key to newly saved assets
		/* 310h */	bool mbPreserveLineage;  // true
		/* 314h */	float field_314;  // 0.5  //PLACEHOLDER wrong, this is TexturePtr mpThumbnail, 28Ch too
		/* 318h */	uint32_t field_318;	// property 0x9036D280.instanceID
		/* 31Ch */	Mode mMode;
		/* 320h */	eastl::vector<uint32_t> mEnabledManipulators;
		/// The list of model types that this editor supports, ie. VehicleMilitaryAir, VehicleEconomicLand, BuildingIndustry, BuildingHouse, etc
		/* 334h */	eastl::vector<uint32_t> mModelTypes;
		/* 348h */	int field_348;
		/* 34Ch */	int mnDefaultBrainLevel;
		/* 350h	*/	int field_350;	/* 350h -> UI? */
		/* 354h	*/	int field_354;
		/* 358h	*/	EditorNamePanelPtr mpEditorNamePanel;
		/* 35Ch	*/	int field_35C;
		/* 360h	*/	cEditorAnimWorldPtr mpEditorAnimWorld;
		/// ID used in `mpEditorAnimWorld` for the current editing creature
		/* 364h	*/	int mCurrentCreatureID;
		/* 368h	*/	int field_368;
		/* 36Ch	*/	eastl::vector<int> field_36C;  //TODO vector of creatures? Check sub_629130
		/// Anim event that will be played on the creature on the next Update() call
		/* 380h */	cEditorAnimEventPtr mpAnimEvent;
		/* 384h */	bool field_384;
		/* 385h */	bool field_385;
		/* 388h */	int field_388;  // not initialized
		/* 38Ch */	int field_38C;
		/* 390h */	int field_390;
		/* 394h */	bool field_394;
		/* 395h */	bool field_395;
		/* 396h */	bool field_396;  // not initialized
		/* 397h */	bool field_397;
		/* 398h */	bool field_398;  // true
		/* 399h */	bool field_399;  // true
		/* 39Ah */	bool field_39A;  // true
		/* 39Ch */	eastl::vector<EditorRigblockPtr> field_39C;
		/* 3B0h */	int field_3B0;  // not initialized, a paint region for building/vehicle parts
		/* 3B4h */	int field_3B4;  // not initialized
		/* 3B8h */	PaletteMainPtr mpPartsPalette;
		/* 3BCh */	PaletteUIPtr mpPartsPaletteUI;
		/* 3C0h */	PaletteMainPtr mpPaintPalette;
		/* 3C4h */	PaletteUIPtr mpPaintPaletteUI;
		/* 3C8h */	bool field_3C8;
		/* 3C9h */	bool field_3C9;  // true

		/* 3CCh */	App::cViewer* field_3CC;  // not initialized
		/* 3D0h */	App::cViewer* field_3D0;  // not initialized
		/* 3D4h */	App::cViewer* field_3D4;  // not initialized
		/* 3D8h */	App::cViewer* field_3D8;  // not initialized
		/* 3DCh */	App::cViewer* field_3DC;  // not initialized

		/* 3E0h */	bool mIsRecordingGIF;
		/* 3E1h */	bool field_3E1;
		/* 3E4h */	int field_3E4;
		/* 3E8h */	int field_3E8;  // 5
		/* 3ECh */	int field_3EC;
		/* 3F0h */	int field_3F0;
		/* 3F4h */	int field_3F4;
		/* 3F8h */	int field_3F8;
		/* 3FCh */	int field_3FC;  // 24h
		/* 400h */	int field_400;
		/* 404h */	int field_404;  // 1
		/* 408h */	int field_408;
		/* 40Ch */	int field_40C;
		/* 410h */	int field_410;
		/* 414h */	int field_414;
		/* 418h */	int field_418;
		/* 41Ch */	int field_41C;
		/* 420h */	int field_420;
		/* 424h */	int field_424;
		/* 428h */	int field_428;
		/* 42Ch */	int field_42C;
		/* 430h */	bool field_430;
		/* 434h */	StdEditorLimitsPtr mpEditorLimits;
		/* 438h */	int field_438;
		/* 43Ch */	int field_43C;
		/* 440h */	int field_440;
		/* 444h */	int field_444;
		/* 448h */	int field_448;
		/* 44Ch */	int field_44C;
		/* 450h */	int field_450;  // 1
		/* 454h */	eastl::map<int, int> field_454;
		/* 470h */	bool field_470;  // property 0x46082CA
		/// Tells the editor whether or not to show the bone length handle.
		/* 471h */	bool mbShowBoneLengthHandles;
		/* 472h */	bool field_472;  // whether the creature gets frozen when editing? 
		/* 474h */	float field_474;
		/// The amount of idle time it takes for a mouse wheel operation to register finished.
		/* 478h */	float mfMouseWheelTimeout;  // 0.3
		/// The distance the mouse has to travel for a mouse wheel operation to register finished.
		/* 47Ch */	float mfMouseWheelDistanceThreshold;  // 10.0
		/* 480h */	float field_480;
		/* 484h */	float field_484;
		/// The distance the mouse has to travel to interrupt a reactive animation.
		/* 488h */	float mAnimationInterruptDistance;  // 30.0

		/* 48Ch */	int field_48C;  // not initialized
		/* 490h */	int field_490;  // not initialized
		/* 494h */	int field_494;  // something related with the RolloverEditorSellBack layout ?
		/* 498h */	int field_498;  // something related with the RolloverEditorSellBack layout ?
		/* 49Ch */	int field_49C;  // something related with the RolloverEditorMessage layout ?
		/* 4A0h */	int field_4A0;
		/* 4A4h */	int field_4A4;
		/* 4A8h */	int field_4A8;  // not initialized
		/* 4ACh */	int mRenderingQuality;  // 1
		/* 4B0h */	bool field_4B0;  // true
		/* 4B1h */	bool field_4B1;  // true
		/* 4B2h */	bool field_4B2;
		/* 4B3h */	bool field_4B3;  // not initialized
		/* 4B4h */	bool field_4B4;  // not initialized
		/* 4B5h */	bool field_4B5;
		/* 4B6h */	bool field_4B6;  // not initialized
		/* 4B7h */	bool mbModelForceSaveOver;
		/* 4B8h */	bool mbModelCopyConsequence;
		/* 4B9h */	bool mbModelSaveLastChild;
		/* 4BCh	*/	int field_4BC;
		/* 4C0h	*/	int field_4C0;
		/* 4C4h	*/	int field_4C4;
		/* 4C8h	*/	bool field_4C8;
		/* 4C9h	*/	bool field_4C9;
		/* 4CCh */	int field_4CC;
		/* 4D0h */	float field_4D0;  // 5.7295780181884765625E1
		/* 4D4h */	int field_4D4;  // not initialized
		/* 4D8h */	int field_4D8;
		/* 4DCh */	int field_4DC;
		/* 4E0h */	int field_4E0;
		/* 4E4h */	int field_4E4[9];
		/* 508h */	eastl::vector<int> field_508;
		/* 51Ch */	eastl::vector<int> field_51C;
		/* 530h */	eastl::vector<int> field_530;
		/* 544h */	eastl::vector<int> field_544;
		/* 558h */	eastl::vector<int> field_558;
		/* 56Ch */	eastl::vector<int> field_56C;
		/* 580h */	int field_580;  // not initialized
		/* 584h */	int field_584;  // not initialized
		/* 588h */	eastl::vector<int> field_588;
		/// Used by audio system to play different footsteps based on type of material used in the dais construction.
		/* 59Ch */	uint32_t mDaisType;
		/// Used by audio system to determine if foot is on dais or floor.
		/* 5A0h */	float mfDaisRadius;
		/* 5A4h */	int field_5A4;
		/* 5A8h */	Clock field_5A8;
		/* 5C0h */	int field_5C0;
		/* 5C4h */	int field_5C4;
		/* 5C8h */	int field_5C8;
		/* 5CCh */	int field_5CC;
		/* 5D0h */	int field_5D0;
		/* 5D4h */	int field_5D4;
		/* 5D8h */	int field_5D8;
		/* 5DCh */	int field_5DC;
		/* 5E0h */	int field_5E0;
		/* 5E4h */	int field_5E4;
		/* 5E8h */	int field_5E8;
		/* 5ECh */	int field_5EC;
		/* 5F0h */	int field_5F0;
		/* 5F4h */	int field_5F4;
		/* 5F8h */	int field_5F8;
		/* 5FCh */	int field_5FC;  // not initialized
	};
	ASSERT_SIZE(cEditor, 0x600);

	namespace Addresses(cEditor) {
		DeclareAddress(sub_581F70);
		DeclareAddress(ptr);

		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(OnEnter);
		DeclareAddress(OnExit);
		DeclareAddress(OnKeyDown);
		DeclareAddress(OnKeyUp);
		DeclareAddress(OnMouseDown);
		DeclareAddress(OnMouseUp);
		DeclareAddress(OnMouseMove);
		DeclareAddress(OnMouseWheel);
		DeclareAddress(Update);

		DeclareAddress(SetEditorModel);  // 0x5867D0, 0x586B00
		DeclareAddress(CommitEditHistory);  // 0x5860E0, 0x586410
		DeclareAddress(Undo);  // 0x58A270, 0x58A5A0
		DeclareAddress(Redo);  // 0x58A620, 0x58A950
		DeclareAddress(SetActiveMode);  // 0x586F40 0x587270
		DeclareAddress(SetCreatureToNeutralPose);  // 0x573860 0x573970
		DeclareAddress(AddCreature);  // 0x582D00 0x582FE0

		DeclareAddress(HandleMessage);  // 0x591C80 0x591FA0
	}

#ifdef SDK_TO_GHIDRA
	cEditor* sEditor;
#endif

#ifndef SDK_TO_GHIDRA
	/// Returns the Editor instance (there can only be one at a time).
	inline cEditor* GetEditor()
	{
		return *((cEditor**) GetAddress(cEditor, ptr));
	}

	inline EditorCamera* cEditor::GetCamera()
	{
		return object_cast<EditorCamera>(mpGameModeMgr->GetCameraManager()->GetActiveCamera());
	}

	inline bool cEditor::IsMode(Mode mode) const {
		return mMode == mode;
	}

	inline bool cEditor::IsActive() const {
		return mIsActive;
	}

	inline EditorModel* cEditor::GetEditorModel() const
	{
		return mpEditorModel;
	}

	inline cEditorSkin* cEditor::GetSkin()
	{
		return mpEditorSkin.get();
	}

	inline cEditorAnimWorld* cEditor::GetAnimWorld()
	{
		return mpEditorAnimWorld.get();
	}
#endif
}