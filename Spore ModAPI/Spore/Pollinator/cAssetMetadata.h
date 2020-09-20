#pragma once

#include <Spore\Internal.h>
#include <Spore\Resource\ResourceObject.h>
#include <Spore\Resource\IResourceManager.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

#define cAssetMetadataPtr intrusive_ptr<Pollinator::cAssetMetadata>

namespace Pollinator
{
	// documented from https://spore-community.github.io/docs/pollination/pollen_metadata.html#use-in-package-files
	/// The class representation of `.pollen_metadata` files, which represent the metadata (name, author, time created,...) of a creation.
	/// You can get a metadata object using Pollinator::GetMetadata()
	class cAssetMetadata
		: public Resource::ResourceObject
	{
	public:
		const static uint32_t TYPE = 0x30BDEE3;

		void* Cast(uint32_t type) const override;

		int64_t GetAssetID() const;
		int64_t GetParentAssetID() const;
		int64_t GetOriginalParentAssetID() const;

		const ResourceKey& GetAssetKey() const;
		const ResourceKey& GetParentAssetKey() const;

		int64_t GetTimeCreated();
		int64_t GetTimeDownloaded();

		string16 GetName() const;
		string16 GetDescription() const;
		string16 GetAuthor() const;
		int64_t GetAuthorID() const;
		const vector<string16>& GetAuthors() const;
		const vector<string16>& GetTags() const;

		const vector<uint32_t>& GetConsequenceTraits() const;

		bool IsShareable() const;
		bool IsLocalized() const;


		bool Set(const ResourceKey& assetKey, const char16_t* pName, const char16_t* pDescription, const char16_t* pTags, 
			const ResourceKey& parentAssetKey, bool isPollinated);

	public:
		/* 18h */	int64_t mAssetID;  // -1
		/* 20h */	ResourceKey mAssetKey;
		/* 2Ch */	ResourceKey mParentAssetKey;  // -1, -1, -1
		/* 38h */	int64_t mParentAssetID;  // -1
		/* 40h */	int64_t mOriginalParentAssetID;  // -1
		/* 48h */	int64_t mTimeCreated;
		/* 50h */	int64_t mTimeDownloaded;
		/* 58h */	string16 mAuthorName;
		/* 68h */	int64_t mAuthorID;
		/* 70h */	int mUseLocale;  // 0xFFFFFFFF if not localized, 1 if localized
		/* 74h */	bool mIsShareable;  // true
		/* 78h */	string16 mName;
		/* 88h */	string16 mDescription;
		/* 98h */	vector<string16> mAuthors;
		/* ACh */	vector<string16> mTags;
		/* C0h */	vector<uint32_t> mConsequenceTraits;
	};

	ASSERT_SIZE(cAssetMetadata, 0xD8);

	/// Used to get the metadata of a creation, if it exists. Example usage:
	/// ```cpp
	/// cAssetMetadataPtr metadata;
	/// if (Pollinator::GetMetadata(0x07ed7d9f, GroupIDs::BuildingModels, metadata)) {
	///		App::ConsolePrintF("%ls", metadata->GetName().c_str());
	/// }
	/// ```
	inline bool GetMetadata(uint32_t instanceID, uint32_t groupID, cAssetMetadataPtr& dst)
	{
		ResourceObjectPtr pResource;
		if (!ResourceManager.GetResource({ instanceID, Pollinator::cAssetMetadata::TYPE, groupID }, &pResource)) {
			return false;
		}
		dst = object_cast<cAssetMetadata>(pResource);
		return true;
	}

	inline string16 cAssetMetadata::GetName() const { return mName; }
	inline string16 cAssetMetadata::GetDescription() const { return mDescription; }
	inline string16 cAssetMetadata::GetAuthor() const { return mAuthorName; }
	inline int64_t cAssetMetadata::GetAuthorID() const { return mAuthorID; }
	inline const vector<string16>& cAssetMetadata::GetAuthors() const { return mAuthors; }
	inline const vector<string16>& cAssetMetadata::GetTags() const { return mTags; }

	inline const vector<uint32_t>& cAssetMetadata::GetConsequenceTraits() const { return mConsequenceTraits; }

	inline bool cAssetMetadata::IsShareable() const { return mIsShareable; }
	inline bool cAssetMetadata::IsLocalized() const { return mUseLocale == 1; }

	inline int64_t cAssetMetadata::GetAssetID() const { return mAssetID; }
	inline int64_t cAssetMetadata::GetParentAssetID() const { return mParentAssetID; }
	inline int64_t cAssetMetadata::GetOriginalParentAssetID() const { return mOriginalParentAssetID; }

	inline const ResourceKey& cAssetMetadata::GetAssetKey() const { return mAssetKey; }
	inline const ResourceKey& cAssetMetadata::GetParentAssetKey() const { return mParentAssetKey; }

	inline int64_t cAssetMetadata::GetTimeCreated() { return mTimeCreated; }
	inline int64_t cAssetMetadata::GetTimeDownloaded() { return mTimeDownloaded; }

	namespace Addresses(cAssetMetadata)
	{
		DeclareAddress(Set);
	}
}