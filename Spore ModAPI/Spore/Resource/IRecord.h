#pragma once

#include <Spore\Resource\ThreadedObject.h>
#include <Spore\IO\IStream.h>
#include <Spore\ResourceKey.h>

#define IRecordPtr eastl::intrusive_ptr<Resource::IRecord>

namespace Resource
{
	class Database;

	/// Represents a file in a Database; records are identified by a ResourceKey (which specifies group, instance and type IDs),
	/// and have an underlying IO::IStream that is used to read/write data.
	class IRecord
		: public ThreadedObject
	{
	public:
		/// Gets the ResourceKey name that identifies this record.
		/// @returns
		/* 10h */	virtual const ResourceKey& GetKey() = 0;
		
		/// Sets the ResourceKey name that identifies this record.
		/// @param key
		/* 14h */	virtual void SetKey(const ResourceKey& key) = 0;

		/// Returns the IStream used to access this record data.
		/// @returns 
		/* 18h */	virtual IO::IStream* GetStream() = 0;

		/// Returns the database that this record belongs to.
		/// @returns
		/* 1Ch */	virtual Database* GetDatabase() = 0;

		/// Opens this record, allowing its data to be used.
		/// @returns
		/* 20h */	virtual bool RecordOpen() = 0;

		/// Closes this record, forbidding any use of its data.
		/// @returns
		/* 24h */	virtual bool RecordClose() = 0;
	};
}