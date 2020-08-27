#pragma once

#include <Spore\Palettes\ItemViewer.h>
#include <Spore\Palettes\PaletteItem.h>
#include <Spore\Clock.h>

#define AdvancedItemViewerPtr eastl::intrusive_ptr<Palettes::AdvancedItemViewer>

namespace Palettes
{
	class AdvancedItemViewer
		: public ItemViewer
	{
	public:
		static const uint32_t TYPE = 0x3349C94;

		void SetAutoRotate(bool enabled);
		void SetZoom(float zoom);

		/* 17Ch */	ObjectPtr field_17C;
		/* 180h */	PaletteItemPtr mpItem;
		/* 184h */	bool field_184;
		/* 188h */	float mZoom;  // 1.0
		/* 18Ch */	ObjectPtr field_18C;
		/* 190h */	int field_190;
		/* 194h */	ObjectPtr field_194;
		/* 198h */	bool field_198;  // true
		/* 199h */	bool field_199;  // not initialized
		/* 19Ah */	bool field_19A;
		/* 1A0h */	Clock field_1A0;
		/* 1B8h */	ObjectPtr field_1B8;
		/* 1BCh */	ObjectPtr field_1BC;
		/* 1C0h */	int field_1C0;  // not initialized
		/* 1C4h */	int field_1C4;  // not initialized
	};
	ASSERT_SIZE(AdvancedItemViewer, 0x1C8);

	namespace Addresses(AdvancedItemViewer)
	{
		DeclareAddress(SetAutoRotate);
		DeclareAddress(SetZoom);
	}
}
