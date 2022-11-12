#pragma once

#include <Spore\Internal.h>

namespace Resource
{
	///
	/// A structure that contains the metadata of a file stored in a database, such as the offset in the package file and the size.
	///
	struct RecordInfo
	{
		/// The offset, in bytes, of the file data inside the package file.
		/* 00h */	size_t chunkOffset;
		/// The size, in bytes, that this file occupies inside the package file.
		/* 04h */	size_t compressedSize;
		/// The size, in bytes, that this file occupies in memory, once uncompressed.
		/* 08h */	size_t memorySize;
		/// 0 -> no compression, -1 -> compressed
		/* 0Ch */	short flags;  // 0xFFFF for compressed
		/// Whether this item has been saved and written into the package.
		/* 0Eh */	bool isSaved;
	};
	ASSERT_SIZE(RecordInfo, 0x10);
}