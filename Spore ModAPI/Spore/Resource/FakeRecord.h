#pragma once

#include <Spore\Resource\IRecord.h>

#define FakeRecordPtr eastl::intrusive_ptr<Resource::FakeRecord>

namespace Resource
{
	class FakeRecord 
		: public IRecord
	{
	public:
		FakeRecord(Database* database, IO::IStream* stream, const ResourceKey& key,
			bool closeStreamOnClose, bool deleteStreamOnClose);

		virtual const ResourceKey& GetKey() override;
		virtual void SetKey(const ResourceKey& key) override;
		virtual IO::IStream* GetStream() override;
		virtual Database* GetDatabase() override;
		virtual bool RecordOpen() override;
		virtual bool RecordClose() override;

	public:
		/* 08h */	Database* mDatabase;
		/* 0Ch */	IO::IStream* mStream;
		/* 10h */	ResourceKey mKey;
		/* 1Ch */	bool mCloseStreamOnClose;
		/* 1Dh */	bool mDeleteStreamOnClose;
		/* 20h */	int field_20;
	};
	ASSERT_SIZE(FakeRecord, 0x24);

	namespace Addresses(FakeRecord) {
		DeclareAddress(_ctor);  // 0x8E2940 0x8E2650
	}
}