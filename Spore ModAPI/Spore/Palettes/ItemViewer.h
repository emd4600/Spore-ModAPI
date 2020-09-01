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
#include <Spore\Graphics\ModelAsset.h>
#include <Spore\UI\cSPUILayeredObject.h>
#include <Spore\Anim\AnimatedCreature.h>

#define ItemViewerPtr eastl::intrusive_ptr<Palettes::ItemViewer>

namespace Palettes
{
	using namespace eastl;
	using namespace UTFWin;

	class ItemViewer 
		: public IWinProc
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

		/* 2Ch */	virtual void func2Ch(bool) = 0;
		/* 30h */	virtual bool func30h() const = 0;
		/* 34h */	virtual IWindow* GetWindow() const = 0;
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
		/* 18h */	vector<ModelPtr> field_18;
		/* 2Ch */	AnimatedCreaturePtr field_2C;
		/* 30h */	ObjectPtr field_30;
		/* 34h */	ObjectPtr field_34;
		/* 38h */	ObjectPtr field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	ResourceKey mFileName;
		/* 58h */	int field_58;  // not initialized
		/* 5Ch */	IWindowPtr mpWindow;
		/* 60h */	IWindowPtr field_60;
		/* 64h */	float mZoom;  // 1
		/* 68h */	float mRotation;  // 0
		/* 6Ch */	float field_6C;  // 0
		/* 70h */	float mFinalZoom;  // 1
		/* 74h */	char _padding_74[0x20];
		/* 94h */	float field_94;  // 1
		/* 98h */	Math::Matrix3 field_98;
		/* BCh */	bool field_BC;
		/* C0h */	float field_C0;
		/* C4h */	float field_C4;
		/* C8h */	int field_C8;  // -1
		/* CCh */	int field_CC;  // -1
		/* D0h */	const char16_t* field_D0;  // "ui_material_blink"
		/* D4h */	const char16_t* field_D4;  // "ui_material_blink"
		/* D8h */	float field_D8;
		/* DCh */	float field_DC;
		/* E0h */	int field_E0;  // -1
		/* E4h */	const char16_t* field_E4;  // "ui_material_blink"
		/* E8h */	bool field_E8;  // true
		/* E9h */	bool field_E9;
		/* EAh */	bool field_EA;  // true
		/* EBh */	bool field_EB;
		/* ECh */	bool field_EC;
		/* F0h */	AnimatedCreaturePtr mpCreature;
		/* F4h */	int field_F4;  // 2
		/* F8h */	int field_F8;
		/* FCh */	bool field_FC;  // true
		/* FDh */	bool field_FD;
		/* 100h */	uint32_t field_100;  // 0x71FA7D3F ('drag')
		/* 104h */	vector<ModelPtr> field_104;
		/* 118h */	ModelPtr mpModel;
		/* 11Ch */	vector<ModelPtr> field_11C;
		/* 130h */	vector<Transform> field_130;
		/* 144h */	ObjectPtr field_144;
		/* 148h */	vector<int> field_148;
		/* 15Ch */	float field_15C;
		/* 160h */	bool mbViewerInitialized;
		/* 161h */	bool field_161;
		/* 162h */	bool field_162;
		/// If this viewer is for a creation, whether the creation is already baked or not.
		/* 163h */	bool mbCreationIsBaked;
		/* 164h */	bool field_164;
		/* 165h */	bool field_165;  // true
		/* 166h */	bool field_166;  // true
		/* 167h */	bool field_167; 
		/* 168h */	bool field_168;  // not initialized
		/* 169h */	bool field_169;
		/* 16Ah */	bool field_16A;  // true  // mbRotationEnabled ?
		/* 16Bh */	bool mShowTooltip;  // true
		/// If true, no background image will be set in the preview.
		/* 16Ch */	bool mbOmitBackground;
		/* 170h */	int field_170;  // not initialized
		/* 174h */	uint32_t mThumbnailCameraID;
		/* 178h */	int field_178;  // index?
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(ItemViewer) == 0x17C, "sizeof(ItemViewer) != 17Ch");

	namespace Addresses(ItemViewer)
	{
		DeclareAddress(InitializeViewerCamera);

		DeclareAddress(UnkUnload1);
		DeclareAddress(UnkUnload2);

		DeclareAddress(Unload);
	}
}
