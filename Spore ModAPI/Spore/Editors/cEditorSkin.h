#pragma once

#include <Spore\Editors\EditorModel.h>
#include <Spore\Editors\cEditorSkinMesh.h>
#include <Spore\Graphics\IModelWorld.h>

#define cEditorSkinPtr eastl::intrusive_ptr<Editors::cEditorSkin>

namespace Editors
{
	class cEditor;

	class cEditorSkin
		: public Object
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0xCFEB4C03;
		// ctor sub_4C2460

		cEditorSkinMesh* GetMesh(int hq = 1);

		/// Returns whether the skinpaint has finished generating.
		/// @returns
		bool HasFinishedPainting();

		bool PaintSkin(EditorModel* editorModel);

	public:

		/* 0Ch */	cEditor* mpEditor;
		/* 10h */	EditorModel* mpEditorModel;
		/* 14h */	Graphics::IModelWorld* mpModelWorld;
		/// 0xEFEB80EC!0xFEB8102.gmdl
		/* 18h */	cEditorSkinMesh* mpMesh;
		/// 0xEFEB80EC!0xCFF37532.gmdl
		/* 1Ch */	cEditorSkinMesh* mpMeshHQ;
		/* 20h */	char padding_20[0x48 - 0x20];
		/* 48h */	eastl::vector<int> field_48;
		/* 4Ch */	int field_4C;
		/* 60h */	uint32_t mMaterialID;
		/// Group ID 0x40602900, Type ID raster
		/* 64h */	ResourceKey mTextureKey;
		/* 70h */	TexturePtr field_70;
		/* 74h */	TexturePtr field_74;
		/* 78h */	float mSkinResolutionHQ;
		/* 7Ch */	float mSkinResolutionRealtime;
		/* 80h */	float mSkinResolutionHQ2;
		/* 84h */	int field_84;
	};
	ASSERT_SIZE(cEditorSkin, 0x88);

	namespace Addresses(cEditorSkin)
	{
		DeclareAddress(GetMesh);  // 0x4C4280 0x4C4A50
		DeclareAddress(HasFinishedPainting);  // 0x4C5170 0x4C5920
		DeclareAddress(PaintSkin);  // 0x4C4AA0 0x4C5270
	}
}