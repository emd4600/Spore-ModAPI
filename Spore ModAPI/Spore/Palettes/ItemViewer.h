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
		/* 1Ch */	virtual void func1Ch();
		/* 20h */	virtual void func20h();  // sets model visible

		/* 24h */	virtual void Load(const ResourceKey& fileName);
		/* 28h */	virtual void SetName(const ResourceKey& fileName);

		/* 2Ch */	virtual void func2Ch();
		/* 30h */	virtual void func30h();
		/* 34h */	virtual void func34h();
		/* 38h */	virtual void func38h();
		/* 3Ch */	virtual void func3Ch();
		/* 40h */	virtual void func40h();
		/* 44h */	virtual void func44h();
		/* 48h */	virtual void func48h();
		/* 4Ch */	virtual void func4Ch();
		/* 50h */	virtual void func50h();
		/* 54h */	virtual void func54h();
		/* 58h */	virtual void func58h();
		/* 5Ch */	virtual void func5Ch();
		/* 60h */	virtual void func60h();
		/* 64h */	virtual void func64h();
		/* 68h */	virtual void RotateModel();

		// 44h OnMouseEnter

	public:
		// probably should be protected, but then it's not as useful..
		void InitializeViewerCamera();

	public:
		/* 10h */	bool field_10;
		/* 14h */	intrusive_ptr<UI::cSPUILayeredObject> mpLayeredObject;
		/* 18h */	vector<int> field_18;
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
		/* 38h */	int field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	ResourceKey mFileName;
		/* 58h */	int field_58;  // not initialized
		/* 5Ch */	intrusive_ptr<IWindow> mpWindow;
		/* 60h */	intrusive_ptr<IWindow> field_60;
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
		/* D0h */	const wchar_t* field_D0;  // "ui_material_blink"
		/* D4h */	const wchar_t* field_D4;  // "ui_material_blink"
		/* D8h */	float field_D8;
		/* DCh */	float field_DC;
		/* E0h */	int field_E0;  // -1
		/* E4h */	const wchar_t* field_E4;  // "ui_material_blink"
		/* E8h */	bool field_E8;  // true
		/* E9h */	bool field_E9;  // true
		/* EAh */	bool field_EA;
		/* EBh */	bool field_EB;
		/* ECh */	bool field_EC;
		/* F0h */	int field_F0;
		/* F4h */	int field_F4;  // 2
		/* F8h */	int field_F80;
		/* FCh */	bool field_FC;  // true
		/* FDh */	bool field_FD;
		/* 100h */	uint32_t field_100;  // 0x71FA7D3F ('drag')
		/* 104h */	vector<int> field_104;
		/* 118h */	intrusive_ptr<Graphics::Model> mpModel;
		/* 11Ch */	vector<intrusive_ptr<Graphics::Model>> field_11C;
		/* 130h */	vector<Transform> field_130;
		/* 144h */	int field_144;
		/* 148h */	vector<int> field_148;
		/* 15Ch */	float field_15C;
		/* 160h */	bool mbViewerInitialized;
		/* 161h */	bool field_161;
		/* 162h */	bool field_162;
		/// If this viewer is for a creation, whether the creation is already baked or not.
		/* 163h */	bool mbCreationIsBaked;
		/* 164h */	bool field_164;
		/* 165h */	bool field_165;
		/* 166h */	bool field_166;
		/* 167h */	bool field_167; 
		/* 168h */	bool field_168;  // not initialized
		/* 169h */	bool field_169;
		/* 16Ah */	bool mbRotationEnabled;
		/* 16Bh */	bool field_16B;
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
		DeclareAddress(InitializeViewerCamera, SelectAddress(0x5F3B50,, 0x5F3D80));
	}
}
