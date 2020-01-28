#pragma once

#include <Spore\Internal.h>
#include <Spore\Resource\ResourceObject.h>
#include <Spore\Resource\IResourceManager.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

#define cAssetMetadataPtr intrusive_ptr<Pollinator::cAssetMetadata>

namespace Pollinator
{
	class cAssetMetadata
		: public Resource::ResourceObject
	{
	public:
		const static uint32_t TYPE = 0x30BDEE3;

		string16 GetName() const;
		string16 GetDescription() const;
		string16 GetAuthor() const;

	public:
		/* 18h */	int field_18;  // -1
		/* 1Ch */	int field_1C;  // -1
		/* 20h */	ResourceKey field_20;
		/* 2Ch */	ResourceKey field_2C;  // -1, -1, -1
		/* 38h */	int64_t field_38;  // -1
		/* 40h */	int64_t field_40;  // -1
		/* 48h */	int64_t field_48;
		/* 50h */	int64_t field_50;
		/* 58h */	string16 mAuthorName;
		/* 68h */	ResourceKey field_68;  // -1, -1, -1
		/* 74h */	bool field_74;  // true
		/* 78h */	string16 mName;
		/* 88h */	string16 mDescription;
		/* 98h */	vector<string16> mAuthors;
		/* ACh */	vector<string16> mTags;
		/* C0h */	vector<int> field_C0;
	};

	ASSERT_SIZE(cAssetMetadata, 0xD8);

	inline cAssetMetadata* GetMetadata(uint32_t instanceID, uint32_t groupID)
	{
		Resource::ResourceObject* pResource;
		if (!ResourceManager.GetResource({ instanceID, Pollinator::cAssetMetadata::TYPE, groupID }, &pResource)) {
			return nullptr;
		}
		return (cAssetMetadata*)pResource;
	}

	inline string16 cAssetMetadata::GetName() const { return mName; }
	inline string16 cAssetMetadata::GetDescription() const { return mDescription; }
	inline string16 cAssetMetadata::GetAuthor() const { return mAuthorName; }
}