#pragma once

#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Object.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

namespace Graphics
{
	class cRenderTargetManager
		: public IRenderTargetManager
		, public App::IMessageListener
		, public DefaultRefCounted
	{
	public:
		struct EntryRegion
		{
			/* 00h */	Math::IntRectangle rect;
			/* 10h */	int field_10;  // -1
			/* 14h */	int field_14;  // -1
			/* 18h */	int field_18;  // -1
			/* 1Ch */	bool field_1C;
		};
		ASSERT_SIZE(EntryRegion, 0x20);

		struct Entry {
			/* 00h */	vector<EntryRegion> mRegions;
			/* 14h */	vector<int> field_14;
			/* 28h */	D3DFORMAT format;
			/* 2Ch */	int width;
			/* 30h */	int height;
			/* 34h */	int field_34;  // use count? enabled?
			/* 38h */	Texture* pTexture;
		};
		ASSERT_SIZE(Entry, 0x3C);

		/* 10h */	bool mbInitialized;
		/* 14h */	int field_14;
		/* 18h */	vector<Entry> mEntries;
	};

	static_assert(sizeof(cRenderTargetManager) == 0x2C, "sizeof(cRenderTargetManager) != 2Ch");
}