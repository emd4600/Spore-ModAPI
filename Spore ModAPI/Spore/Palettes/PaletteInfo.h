#pragma once

#include <Spore\Object.h>
#include <Spore\Editors\EditorLimits.h>

#define PaletteInfoPtr eastl::intrusive_ptr<Palettes::PaletteInfo>

namespace Palettes
{
	class PaletteInfo
	{
	public:
		virtual ~PaletteInfo();
		virtual int AddRef();
		virtual int Release();

	private:
		/* 04h */	int mnRefCount;

	public:
		/* 08h */	IEditorLimitsPtr mpEditorLimits;
		/* 0Ch */	ObjectPtr field_C;
		/* 10h */	ObjectPtr field_10;
		/* 14h */	ObjectPtr field_14;
		/* 18h */	char16_t mCurrencyChar;
		/* 1Ch */	uint32_t mCameraPaletteID;
		/* 20h */	uint32_t mSaveExtension;
		/* 24h */	float field_24;  // -1.0f
		/* 28h */	float field_28;  // -1.0f
		/* 2Ch */	uint32_t mModelType;  // -1
		/* 30h */	bool field_30;  // true
		/* 31h */	bool field_31;
	};
	ASSERT_SIZE(PaletteInfo, 0x34);
}