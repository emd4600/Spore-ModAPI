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

#include <EASTL\vector.h>
#include <Spore\MathUtils.h>
#include <Spore\Object.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Graphics\Model.h>
#include <Spore\UI\cSPUILayeredObject.h>
#include <Spore\Anim\AnimatedCreature.h>

#define ItemViewerPtr eastl::intrusive_ptr<Palettes::ItemViewer>

namespace Palettes
{
	enum class TriggerBehaviors : uint32_t
	{
		None = 0x2CA33BDB,
		Drag = 0x71FA7D3,
		Click = 0x5E71AB9B,
	};

	class ItemViewer 
		: public UTFWin::IWinProc
		, public DefaultRefCounted
		, public App::IUnmanagedMessageListener
	{
	public:
		static const uint32_t TYPE = 0x31E56741;

		ItemViewer();
		~ItemViewer();

		using Object::AddRef;
		using Object::Release;

		/* 1Ch */	virtual void Unload();
		/* 20h */	virtual void Update(int time) = 0;  // sets model visible

		/* 24h */	virtual void Load(const ResourceKey& fileName) = 0;
		/* 28h */	virtual void SetName(const ResourceKey& fileName) = 0;

		/* 2Ch */	virtual void SetShowModelOnHover(bool enabled) = 0;
		/* 30h */	virtual bool GetShowModelOnHover() const = 0;
		/* 34h */	virtual UTFWin::IWindow* GetWindow() const = 0;
		/* 38h */	virtual void Set3dPreview(bool enabled) = 0;
		/* 3Ch */	virtual Anim::AnimatedCreature* GetAnimatedCreature() const = 0;  //PLACEHOLDER GetAnimatedCreature()
		/* 40h */	virtual void func40h() = 0;
		/* 44h */	virtual bool func44h() = 0;
		/* 48h */	virtual void func48h() = 0;
		/* 4Ch */	virtual void func4Ch() = 0;
		/* 50h */	virtual void func50h() = 0;
		/* 54h */	virtual void func54h(int) = 0;
		/* 58h */	virtual float func58h() = 0;
		/* 5Ch */	virtual bool IsOutside() = 0;
		/* 60h */	virtual void OnOutside() = 0;
		/* 64h */	virtual void func64h() = 0;
		/* 68h */	virtual void RotateModel() = 0;

		// 44h OnMouseEnter

	public:
		// probably should be protected, but then it's not as useful..
		void InitializeViewerCamera();

	public:
		/* 10h */	bool field_10;
		/* 14h */	cSPUILayeredObjectPtr mpLayeredObject;
		/* 18h */	eastl::vector<ModelPtr> field_18;
		/* 2Ch */	AnimatedCreaturePtr field_2C;
		/* 30h */	ObjectPtr field_30;
		/* 34h */	ObjectPtr field_34;
		/* 38h */	ObjectPtr field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	uint32_t mInstanceID; // Item instanceID
		/* 44h */	uint32_t mTypeID; // Item typeID
		/* 48h */	uint32_t mGroupID; // Item groupID
		/* 4Ch */	ResourceKey mFileName; // Item Key
		/* 58h */	uint32_t mTypeIDUnk1;  // not initialized, usually set to 'prop' hash
		/* 5Ch */	IWindowPtr mpWindow;
		/* 60h */	IWindowPtr mpWindowUnk1; // Same as above?
		/* 64h */	float mZoom;  // 1
		/* 68h */	float mRotation;  // 0
		/* 6Ch */	float mInitialRotation;  // 0
		/* 70h */	float mFinalZoom;  // 1 // Desired zoom
		/* 74h */	char _padding_74[0x20];
		/* 94h */	float mInitialZoom;  // 1 
		/* 98h */	Math::Matrix3 field_98; // Something to do with model transforms
		/* BCh */	bool field_BC;
		/* C0h */	float field_C0;
		/* C4h */	float field_C4;
		/* C8h */	int field_C8;  // -1
		/* CCh */	int field_CC;  // -1
		/* D0h */	const char16_t* mUIMaterialUnk1;  // "ui_material_blink"
		/* D4h */	const char16_t* mUIMaterialUnk2;  // "ui_material_blink"
		/* D8h */	float field_D8;
		/* DCh */	float field_DC;
		/* E0h */	int field_E0;  // -1
		/* E4h */	const char16_t* mUIMaterialUnk3;  // "ui_material_blink"
		/* E8h */	bool field_E8;  // true
		/* E9h */	bool field_E9;
		/* EAh */	bool mb3DPreviewEnabled;  // true // If set to false, model will not show when hovered
		/* EBh */	bool field_EB;
		/* ECh */	bool field_EC;
		/* F0h */	AnimatedCreaturePtr mpCreature;
		/* F4h */	int field_F4;  // 2
		/* F8h */	int field_F8;
		/* FCh */	bool field_FC;  // true
		/* FDh */	bool field_FD;
		/* 100h */	TriggerBehaviors mTriggerBehavior;  // TriggerBehaviors::Drag
		/* 104h */	eastl::vector<ModelPtr> field_104;
		/* 118h */	ModelPtr mpModel;
		/* 11Ch */	eastl::vector<ModelPtr> field_11C;
		/* 130h */	eastl::vector<Transform> field_130;
		/* 144h */	ObjectPtr field_144;
		/* 148h */	eastl::vector<int> field_148;
		/* 15Ch */	float field_15C;
		/* 160h */	bool mbViewerInitialized;
		/* 161h */	bool field_161;
		/* 162h */	bool field_162;
		/// If this viewer is for a creation, whether the creation is already baked or not.
		/* 163h */	bool mbCreationIsBaked;
		/* 164h */	bool field_164;
		/* 165h */	bool field_165;  // true
		/* 166h */	bool mbShowModelOnHover;  // true
		/* 167h */	bool field_167; 
		/* 168h */	bool field_168;  // not initialized
		/* 169h */	bool field_169;
		/* 16Ah */	bool mbRotationEnabled;  // true
		/* 16Bh */	bool mShowTooltip;  // true
		/// If true, no background image will be set in the preview.
		/* 16Ch */	bool mbOmitBackground;
		/* 170h */	int field_170;  // not initialized
		/* 174h */	uint32_t mThumbnailCameraID;
		/* 178h */	int field_178;  // index?
	};
	ASSERT_SIZE(ItemViewer, 0x17C);

	namespace Addresses(ItemViewer)
	{
		DeclareAddress(InitializeViewerCamera);

		DeclareAddress(UnkUnload1);
		DeclareAddress(UnkUnload2);

		DeclareAddress(Unload);
	}
}
