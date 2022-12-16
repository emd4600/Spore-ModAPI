#pragma once

#include <Spore\Internal.h>
#include <EASTL\bitset.h>
#include <EASTL\internal\thread_support.h>

struct GeneralAllocator
{
	struct Chunk
	{
		/* 00h */	size_t mchunk_prev_size;
		/* 04h */	size_t mchunk_size;  // with some flags?
		///* 08h */	void* data_ptr;
		/* 08h */	Chunk* bck;
		/* 0Ch */	Chunk* fwd;
	};

	struct SkipListChunk : Chunk
	{
	};

	struct allocator_mutex : eastl::Internal::mutex
	{
		/* 18h */	int lock_count;
	};
	ASSERT_SIZE(allocator_mutex, 0x1C);

	typedef bool(*MallocFailureFunction_t)(GeneralAllocator*, unsigned int, unsigned int, int);

	static const int NUM_FAST_BINS = 8;  // ?
	static const int NUM_BINS = 128;  // ?
	static const int MIN_SIZE = 0x10;
	static const int BIN_MAP_SIZE = 4;
	static const int INUSE_FLAG = 1;

	static GeneralAllocator* Get();

	int GetFastBinIndexFromChunkSize(unsigned int chunkSize);
	int GetSmallBinIndexFromChunkSize(unsigned int chunkSize);
	int GetLargeBinIndexFromChunkSize(unsigned int chunkSize);

	bool GetFastBinChunksExist();

	SkipListChunk* GetBin(int index);
	SkipListChunk* GetUnsortedBin();
	SkipListChunk* GetNextBin(SkipListChunk* bin);
	Chunk* GetFirstChunkInBin(SkipListChunk* bin);
	Chunk* GetLastChunkInBin(SkipListChunk* bin);

	bool ChunkMatchesLowHigh(bool, Chunk* chunk, int offset);

	void* GetDataPtrFromChunkPtr(Chunk* chunk);

	unsigned int GetChunkSize(Chunk* chunk);
	void SetChunkSize(Chunk* chunk, unsigned int size);
	void SetNextChunkPrevSize(Chunk* chunk, unsigned int size);

	Chunk* GetChunkAtOffset(Chunk* chunk, unsigned int offset);

	bool GetPrevChunkIsInUse(Chunk* chunk);

	bool GetChunkIsLargeBin(Chunk* chunk);

	bool SizeIsWithinSmallBinRange(int size);

	void SetChunkInUseOffset(Chunk* chunk, unsigned int offset);

	void LinkChunk(Chunk* chunk, Chunk* bck, Chunk* fwd);
	void UnlinkChunk(Chunk* chunk);

	void SplitChunkTail(Chunk* victim, unsigned int requestedSize, bool isSmallBin);

	void AdjustTopChunk(Chunk* chunk, unsigned int size);
	void AdjustHighFence();

	unsigned int GetBinBitmapWordFromBinIndex(unsigned int index);
	unsigned int GetBinBitmapBitFromBinIndex(unsigned int index);

	/* 00h */	int field_0;
	/* 04h */	unsigned int max_fastbin_size;
	/* 08h */	Chunk* fastbins[NUM_FAST_BINS];
	/* 28h */	Chunk* field_28;
	/* 2Ch */	Chunk* field_2C;
	/* 30h */	Chunk* bins[NUM_BINS * 2/* - 2*/];
	///* 430h */	eastl::bitset<128> binmap;  //TODO how many?
	/* 430h */	unsigned int binmap[4];
	/* 440h */	Chunk* top;
	/* 444h */	Chunk* last_remainder;
	/* 448h */	int field_448;
	/* 44Ch */	int field_44C;
	/* 450h */	int field_450;
	/* 454h */	int field_454;
	/* 458h */	int field_458;
	/* 45Ch */	int field_45C;
	/* 460h */	int field_460;
	/* 464h */	int field_464;
	/* 468h */	Chunk* field_468;
	/* 46Ch */	bool field_46C;
	/* 46Dh */	bool field_46D;
	/* 470h */	int field_470;
	/* 474h */	char padding_474[0x488 - 0x474];
	/* 488h */	int field_488;
	/* 48Ch */	int field_48C;
	/* 490h */	int field_490;
	/* 494h */	unsigned int field_494;
	/* 498h */	int field_498;
	/* 49Ch */	int field_49C;
	/* 4A0h */	int field_4A0;
	/* 4A4h */	int field_4A4;
	/* 4A8h */	int field_4A8;
	/* 4ACh */	MallocFailureFunction_t malloc_failure_function;
	/* 4B0h */	int field_4B0;
	/* 4B4h */	int field_4B4;
	/* 4B8h */	char field_4B8[0x4E4 - 0x4B8];
	/* 4E4h */	allocator_mutex* field_4E4;

	// /* 4C0h */	callback for OutputDebugString
};
ASSERT_SIZE(GeneralAllocator, 0x4E8);  //TODO

inline int GeneralAllocator::GetFastBinIndexFromChunkSize(unsigned int chunkSize)
{
	return chunkSize >> 3;
}

inline int GeneralAllocator::GetSmallBinIndexFromChunkSize(unsigned int chunkSize)
{
	return chunkSize >> 3;
}

inline int GeneralAllocator::GetLargeBinIndexFromChunkSize(unsigned int chunkSize)
{
	if ((chunkSize >> 6) <= 0x20) return (chunkSize >> 6) + 0x38;
	if ((chunkSize >> 9) <= 0x14) return (chunkSize >> 9) + 0x5B;
	if ((chunkSize >> 12) <= 0xA) return (chunkSize >> 12) + 0x6E;
	if ((chunkSize >> 15) <= 0x4) return (chunkSize >> 15) + 0x77;
	if ((chunkSize >> 18) <= 0x2) return (chunkSize >> 18) + 0x7C;
	return 0x7E;
}

inline unsigned int GeneralAllocator::GetChunkSize(Chunk* chunk)
{
	return chunk->mchunk_size & 0x7FFFFFF8;
}

inline void GeneralAllocator::SetChunkSize(Chunk* chunk, unsigned int size)
{
	chunk->mchunk_size = size;
}
inline void GeneralAllocator::SetNextChunkPrevSize(Chunk* chunk, unsigned int size)
{
	GetChunkAtOffset(chunk, size)->mchunk_prev_size = size;
}

inline GeneralAllocator::Chunk* GeneralAllocator::GetChunkAtOffset(Chunk* chunk, unsigned int offset)
{
	return (Chunk * )((unsigned int)chunk + offset);
}

inline bool GeneralAllocator::GetPrevChunkIsInUse(Chunk* chunk)
{
	return chunk->mchunk_size & 1;
}

inline bool GeneralAllocator::GetChunkIsLargeBin(Chunk* chunk)
{
	return chunk->mchunk_size & 0x80000000;
}

inline void* GeneralAllocator::GetDataPtrFromChunkPtr(Chunk* chunk)
{
	return (void*)((int)chunk + 8);
}

inline bool GeneralAllocator::SizeIsWithinSmallBinRange(int size)
{
	return size < 0x200;
}

inline GeneralAllocator::SkipListChunk* GeneralAllocator::GetBin(int index)
{
	return (SkipListChunk*)((int)&field_28 + index * 8);
}

inline GeneralAllocator::SkipListChunk* GeneralAllocator::GetUnsortedBin()
{
	return GetBin(1);
}

inline GeneralAllocator::SkipListChunk* GeneralAllocator::GetNextBin(SkipListChunk* bin)
{
	return (GeneralAllocator::SkipListChunk*)((int)bin + 8);
}

inline GeneralAllocator::Chunk* GeneralAllocator::GetFirstChunkInBin(SkipListChunk* bin)
{
	return bin->fwd;
}
inline GeneralAllocator::Chunk* GeneralAllocator::GetLastChunkInBin(SkipListChunk* bin)
{
	return bin->bck;
}

inline bool GeneralAllocator::ChunkMatchesLowHigh(bool param1, Chunk* chunk, int offset)
{
	if (!field_468) return true;
	return param1 ? (int)field_468 <= (int)chunk + offset : (int)chunk < (int)field_468;
}

inline void GeneralAllocator::SetChunkInUseOffset(Chunk* chunk, unsigned int offset)
{
	GetChunkAtOffset(chunk, offset)->mchunk_size |= 1;
}

inline void GeneralAllocator::LinkChunk(Chunk* chunk, Chunk* bck, Chunk* fwd)
{
	chunk->bck = bck;
	chunk->fwd = fwd;
	bck->fwd = chunk;
	fwd->bck = chunk;
}

inline void GeneralAllocator::UnlinkChunk(Chunk* chunk)
{
	chunk->bck->fwd = chunk->fwd;
	chunk->fwd->bck = chunk->bck;
}

inline bool GeneralAllocator::GetFastBinChunksExist()
{
	return max_fastbin_size & 1;
}

inline void GeneralAllocator::SplitChunkTail(Chunk* victim, unsigned int requestedSize, bool isSmallBin)
{
	UnlinkChunk(victim);
	unsigned int size = GetChunkSize(victim);
	unsigned int remainderSize = size - requestedSize;
	if (remainderSize < MIN_SIZE)
	{
		SetChunkInUseOffset(victim, size);
	}
	else
	{
		auto unsortedBin = GetUnsortedBin();
		auto remainder = GetChunkAtOffset(victim, size);
		LinkChunk(remainder, unsortedBin, unsortedBin->fwd);
		if (isSmallBin) last_remainder = remainder;
		SetChunkSize(victim, requestedSize | INUSE_FLAG);
		SetChunkSize(remainder, remainderSize | INUSE_FLAG);
		SetNextChunkPrevSize(remainder, remainderSize);
	}
}

inline void GeneralAllocator::AdjustTopChunk(Chunk* chunk, unsigned int size)
{
	chunk->bck = chunk;
	chunk->fwd = chunk;
	SetChunkSize(chunk, size | INUSE_FLAG);
	SetNextChunkPrevSize(chunk, size);
	if (!field_46C)
	{
		AdjustHighFence();
	}
}
inline void GeneralAllocator::AdjustHighFence()
{
	unsigned int size = (top->mchunk_size >> 1) & 0x3FFFFFFC;
	field_468 = (Chunk*)((unsigned int)top + size);
}

inline unsigned int GeneralAllocator::GetBinBitmapWordFromBinIndex(unsigned int index)
{
	return index >> 5;
}
inline unsigned int GeneralAllocator::GetBinBitmapBitFromBinIndex(unsigned int index)
{
	return 1 << (index & 0x1F);
}


/*
   malloc_chunk details:
	(The following includes lightly edited explanations by Colin Plumb.)
	Chunks of memory are maintained using a `boundary tag' method as
	described in e.g., Knuth or Standish.  (See the paper by Paul
	Wilson ftp://ftp.cs.utexas.edu/pub/garbage/allocsrv.ps for a
	survey of such techniques.)  Sizes of free chunks are stored both
	in the front of each chunk and at the end.  This makes
	consolidating fragmented chunks into bigger chunks very fast.  The
	size fields also hold bits representing whether chunks are free or
	in use.
	An allocated chunk looks like this:
	chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             Size of previous chunk, if unallocated (P clear)  |
		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             Size of chunk, in bytes                     |A|M|P|
	  mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             User data starts here...                          .
		.                                                               .
		.             (malloc_usable_size() bytes)                      .
		.                                                               |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             (size of chunk, but used for application data)    |
		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             Size of next chunk, in bytes                |A|0|1|
		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	Where "chunk" is the front of the chunk for the purpose of most of
	the malloc code, but "mem" is the pointer that is returned to the
	user.  "Nextchunk" is the beginning of the next contiguous chunk.
	Chunks always begin on even word boundaries, so the mem portion
	(which is returned to the user) is also on an even word boundary, and
	thus at least double-word aligned.
	Free chunks are stored in circular doubly-linked lists, and look like this:
	chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             Size of previous chunk, if unallocated (P clear)  |
		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	`head:' |             Size of chunk, in bytes                     |A|0|P|
	  mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             Forward pointer to next chunk in list             |
		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             Back pointer to previous chunk in list            |
		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             Unused space (may be 0 bytes long)                .
		.                                                               .
		.                                                               |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	`foot:' |             Size of chunk, in bytes                           |
		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		|             Size of next chunk, in bytes                |A|0|0|
		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	The P (PREV_INUSE) bit, stored in the unused low-order bit of the
	chunk size (which is always a multiple of two words), is an in-use
	bit for the *previous* chunk.  If that bit is *clear*, then the
	word before the current chunk size contains the previous chunk
	size, and can be used to find the front of the previous chunk.
	The very first chunk allocated always has this bit set,
	preventing access to non-existent (or non-owned) memory. If
	prev_inuse is set for any given chunk, then you CANNOT determine
	the size of the previous chunk, and might even get a memory
	addressing fault when trying to do so.
	The A (NON_MAIN_ARENA) bit is cleared for chunks on the initial,
	main arena, described by the main_arena variable.  When additional
	threads are spawned, each thread receives its own arena (up to a
	configurable limit, after which arenas are reused for multiple
	threads), and the chunks in these arenas have the A bit set.  To
	find the arena for a chunk on such a non-main arena, heap_for_ptr
	performs a bit mask operation and indirection through the ar_ptr
	member of the per-heap header heap_info (see arena.c).
	Note that the `foot' of the current chunk is actually represented
	as the prev_size of the NEXT chunk. This makes it easier to
	deal with alignments etc but can be very confusing when trying
	to extend or adapt this code.
	The three exceptions to all this are:
	 1. The special chunk `top' doesn't bother using the
	trailing size field since there is no next contiguous chunk
	that would have to index off it. After initialization, `top'
	is forced to always exist.  If it would become less than
	MINSIZE bytes long, it is replenished.
	 2. Chunks allocated via mmap, which have the second-lowest-order
	bit M (IS_MMAPPED) set in their size fields.  Because they are
	allocated one-by-one, each must contain its own trailing size
	field.  If the M bit is set, the other bits are ignored
	(because mmapped chunks are neither in an arena, nor adjacent
	to a freed chunk).  The M bit is also used for chunks which
	originally came from a dumped heap via malloc_set_state in
	hooks.c.
	 3. Chunks in fastbins are treated as allocated chunks from the
	point of view of the chunk allocator.  They are consolidated
	with their neighbors only in bulk, in malloc_consolidate.
*/