#pragma once

#include <Spore\Palettes\PaletteMain.h>

#define PaletteIteratorPtr eastl::intrusive_ptr<Palettes::PaletteIterator>

namespace Palettes
{
	/// Used to iterate through the items of an editors palette.
	/// ```cpp
	/// PaletteIteratorPtr iterator = new Palettes::PaletteIterator();
	/// iterator->Init(palette);
	/// auto item = iterator->Start();
	/// while (item) {
	///		// Do something with item...
	///		item = iterator->Next();
	/// }
	/// ```
	class PaletteIterator
		: public DefaultRefCounted
		, public Object
	{
	public:
		static const uint32_t TYPE = 0x42D4548;

		void Init(PaletteMain* palette);

		bool HasNext();

		PaletteItem* Start(uint32_t* dstCategoryID = nullptr, int* dstColumn = nullptr, int* dstRow = nullptr, int* dstPageIndex = nullptr);

		/// Gets the next element in the iterator. Will find the first next palette item that is not null.
		/// Returns null if it reaches the end of the palette.
		/// @param[out] dstCategoryID
		/// @param[out] dstColumn
		/// @param[out] dstRow
		/// @param[out] dstPageIndex
		/// @returns The next palette item, or null if the end was reached
		PaletteItem* Next(uint32_t* dstCategoryID = nullptr, int* dstColumn = nullptr, int* dstRow = nullptr, int* dstPageIndex = nullptr);

	public:
		/* 0Ch */	PaletteMainPtr mpPalette;
		/* 10h */	int mCategoryIndex;
		/* 14h */	int mSubCategoryIndex;
		/* 18h */	int mPageIndex;
		/* 1Ch */	int mItemIndex;
	};
	ASSERT_SIZE(PaletteIterator, 0x20);

	namespace Addresses(PaletteIterator)
	{
		DeclareAddress(Init);  // 0x5C7C80 0x5C7CB0
		DeclareAddress(HasNext);  // 0x5C7CD0 0x5C7D00
		DeclareAddress(Start);  // 0x5C7F40 0x5C7F70
		DeclareAddress(Next);  // 0x5C7EE0 0x5C7F10
	}
}