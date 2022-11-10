#pragma once

#include <Spore\Resource\Database.h>
#include <Spore\FixedPoolAllocator.h>
#include <Spore\IO\IStream.h>
#include <Spore\Mutex.h>
#include <EASTL\string.h>
#include <EASTL\list.h>
#include <EASTL\map.h>

#define DatabaseDirectoryFilesPtr eastl::intrusive_ptr<Resource::DatabaseDirectoryFiles>

namespace Resource
{
	class IResourceManager;

	typedef bool(*FileNameToKeyConverter_t)(const char16_t*, const char16_t*, const char16_t*, ResourceKey&);

	class DatabaseDirectoryFiles
		: public Database
	{
	public:
		static const uint32_t DATABASE_TYPE = 0x34728492;

		static const uint32_t TYPE = 0x226A1DE;

		EAIOZoneObject_AMBIGOUS_DECLARATION;

		DatabaseDirectoryFiles(const char16_t* location, ICoreAllocator* allocator = nullptr);
		virtual ~DatabaseDirectoryFiles();

		virtual void* Cast(uint32_t type) const override;

		/* 04h */	virtual bool Initialize() override;
		/* 08h */	virtual bool Dispose() override;
		/* 0Ch */	virtual uint32_t GetDatabaseType() const override;
		/* 10h */	virtual int GetRefCount() const override;
		/* 14h */	virtual void Lock(bool lock) override;
		/* 18h */	virtual bool Open(IO::AccessFlags desiredAccess = IO::AccessFlags::Read, IO::CD createDisposition = IO::CD::Default, bool arg_8 = false) override;
		/* 1Ch */	virtual bool Close() override;
		/* 20h */	virtual IO::AccessFlags GetAccessFlags() const override;
		/* 24h */	virtual bool Flush() override;
		/* 28h */	virtual const char16_t* GetLocation() const override;
		/* 2Ch */	virtual bool SetLocation(const char16_t* path) override;
		/* 30h */	virtual size_t GetKeyList(eastl::vector<ResourceKey>& dstVector, IResourceFilter* filter = nullptr) override;
		/* 34h */	virtual bool OpenRecord(
			const ResourceKey& name,
			IRecord** ppDst,
			IO::AccessFlags desiredAccess = IO::AccessFlags::Read, 
			IO::CD createDisposition = IO::CD::Default,
			bool arg_10 = true,
			RecordInfo* pDstInfo = nullptr) override;
		/* 38h */	virtual int GetOpenCount(const ResourceKey& key) override;
		/* 3Ch */	virtual bool CloseRecord(IRecord* pRecord) override;
		/* 40h */	virtual bool DeleteRecord(const ResourceKey& name) override;
		/* 44h */	virtual bool Attach(bool, IResourceManager* pResourceMan, bool) override;
		/* 48h */	virtual ICoreAllocator* GetAllocator() const override;

		/* 4Ch */	virtual bool AddExtensionMapping(const char16_t* extension, uint32_t typeID);
		/* 50h */	virtual void SetFileNameToKeyConverter(FileNameToKeyConverter_t callback);
		/* 54h */	virtual int UpdateRecordData(const char16_t*, eastl::vector<ResourceKey>& keys, int);
		/* 58h */	virtual int UpdateRecordData2(eastl::vector<ResourceKey>& keys);
		/* 5Ch */	virtual uint32_t GetTypeFromTypename(const char16_t* typeName);
		/* 60h */	virtual const char16_t* GetTypenameFromType(uint32_t typeID);
		/* 64h */	virtual bool GetFileNameFromKey(const ResourceKey& key, char16_t* dst);
		/* 68h */	virtual bool GetKeyFromFileName(const char16_t* fileName, ResourceKey& dst);
		/* 6Ch */	virtual uint32_t GetDefaultGroupId();
		/* 70h */	virtual void SetDefaultGroupId(uint32_t groupID);

	public:
		struct DDFRecordListData
		{
			/* 00h */	eastl::string16 field_0;
			/* 10h */	uint64_t mTime;
			/* 18h */	eastl::list<IRecordPtr> field_18;  // DDFRecordPtr
		};
		ASSERT_SIZE(DDFRecordListData, 0x28);

		/* 0Ch */	bool mIsInitialized;
		/* 10h */	ICoreAllocator* mpAllocator;
		/* 14h */	bool field_14;
		/* 15h */	bool field_15;
		/* 18h */	IO::AccessFlags mAccessFlags;
		/* 1Ch */	eastl::string16 mLocation;
		/* 2Ch */	FixedPoolAllocator mExtensionMapAllocator;
		/* 4Ch */	FixedPoolAllocator mRecordListDataMapAllocator;
		/* 6Ch */	eastl::map<eastl::string16, uint32_t, eastl::less<eastl::string16>, FixedPoolAllocatorAdapter> mExtensionMap;
		/* 8Ch */	eastl::map<ResourceKey, int, eastl::less<ResourceKey>, FixedPoolAllocatorAdapter> mRecordListDataMap;  // actually the type is DDFRecordListData
		/* ACh */	uint32_t mDefaultGroupID;
		/* B0h */	IResourceManager* mpResourceManager;
		/* B4h */	FileNameToKeyConverter_t mFileNameToKeyConverter;
		/* B8h */	int field_B8[0x20];
		/* 138h */	Mutex mMutex;
	};
	ASSERT_SIZE(DatabaseDirectoryFiles, 0x168);

	/// Reads an extension mapping `.prop` file from the `0x1C7AC81` folder, and adds those type names to
	/// the given database; the instance ID is usually also `0x1C7AC81`.
	/// @param instanceID
	/// @param database
	void ReadExtensionMappingsFromPropFile(uint32_t instanceID, DatabaseDirectoryFiles* database);


	namespace Addresses(DatabaseDirectoryFiles)
	{
		//DeclareAddress(Initialize);  // 0x6BC1D0 0x6BBDC0
		DeclareAddress(Dispose);  // 0x8D63E0 0x8D60D0
		//DeclareAddress(GetDatabaseType);
		DeclareAddress(GetRefCount);
		DeclareAddress(Lock);  // 0x8D6440 0x8D6130
		DeclareAddress(Open);  // 0x8D6640 0x8D6330
		DeclareAddress(Close);  // 0x8D79E0 0x8D7640
		//DeclareAddress(GetAccessFlags);
		DeclareAddress(Flush);  // 0x8D6AD0 0x8D6760
		//DeclareAddress(GetLocation);
		DeclareAddress(SetLocation);  // 0x8D6D40 0x8D69A0
		DeclareAddress(GetKeyList);  // 0x8D7210 0x8D6E70
		DeclareAddress(OpenRecord);  // 0x8D83A0 0x8D7FD0
		DeclareAddress(GetOpenCount);  // 0x8D6B60 0x8D67F0
		DeclareAddress(CloseRecord);  // 0x8D6D90 0x8D69F0
		DeclareAddress(DeleteRecord);  // 0x8D7A40 0x8D76A0
		DeclareAddress(Attach);  // 0x8D6950 0x8D6640
		//DeclareAddress(GetAllocator);
		DeclareAddress(AddExtensionMapping);  // 0x8D7330 0x8D6F90
		//DeclareAddress(SetFileNameToKeyConverter);
		DeclareAddress(UpdateRecordData);  // 0x8D8160 0x8D7DB0
		DeclareAddress(UpdateRecordData2);  // 0x8D8050 0x8D7CA0
		DeclareAddress(GetTypeFromTypename);  // 0x8D6840 0x8D6530
		DeclareAddress(GetTypenameFromType);  // 0x8D68F0 0x8D65E0
		DeclareAddress(GetFileNameFromKey);  // 0x8D6BD0 0x8D6860
		DeclareAddress(GetKeyFromFileName);  // 0x8D6500 0x8D61F0
		//DeclareAddress(GetDefaultGroupId);
		//DeclareAddress(SetDefaultGroupId);
	}
}

namespace Addresses(Resource)
{
	DeclareAddress(ReadExtensionMappingsFromPropFile);  // 0x6B2440 0x6B20A0
}