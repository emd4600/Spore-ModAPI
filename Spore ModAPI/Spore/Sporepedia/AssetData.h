#pragma once

#include <Spore\App\PropertyList.h>
#include <Spore\Pollinator\cAssetMetadata.h>
#include <Spore\Sporepedia\OTDBParameters.h>
#include <Spore\Object.h>
#include <EASTL\fixed_vector.h>

namespace Sporepedia
{
	class IAssetData
	{
	public:
		static const uint32_t TYPE = 0x13D55DC8;

		IAssetData();

		/* 00h */	virtual ~IAssetData();
		/* 04h */	virtual void SetKey(const ResourceKey& key) = 0;
		/* 08h */	virtual void func08h() = 0;
		/* 0Ch */	virtual const char16_t* GetName() = 0;
		/* 10h */	virtual const char16_t* GetAuthorName() = 0;
		/* 14h */	virtual const char16_t* GetDescription() = 0;
		/* 18h */	virtual ResourceKey GetImageKey() = 0;
		/* 1Ch */	virtual ResourceKey GetBackgroundImageKey() = 0;
		/* 20h */	virtual void GetTags(eastl::string16& dst) = 0;
		/// Returns the asset subtype such as BuildingEntertainment, PlantSmall, VehicleMilitaryWater,...
		/* 24h */	virtual uint32_t GetAssetSubtype() = 0;
		/* 28h */	virtual int64_t GetTimeCreated() = 0;
		/// Returns true if it has a name or author name
		/* 2Ch */	virtual bool HasName() = 0;
		/* 30h */	virtual int func30h() = 0;
		/* 34h */	virtual int func34h() = 0;
		/* 38h */	virtual int func38h() = 0;
		/* 3Ch */	virtual float func3Ch() = 0;
		/* 40h */	virtual const ResourceKey& GetKey() = 0;
		/* 44h */	virtual void AsyncSetKey(const ResourceKey& key) = 0;
		/* 48h */	virtual bool func48h() = 0;
		/* 4Ch */	virtual void func4Ch() = 0;
		/* 50h */	virtual void LoadData() = 0;
		/* 54h */	virtual int64_t GetAuthorID() = 0;
		/* 58h */	virtual bool func58h() = 0;
		/* 5Ch */	virtual bool func5Ch() = 0;
		/* 60h */	virtual bool IsEditable() = 0;
		/* 64h */	virtual bool func64h() = 0;
		/* 68h */	virtual bool IsShareable() = 0;
		/* 6Ch */	virtual bool func6Ch() = 0;
		/* 70h */	virtual bool IsShared() = 0;
		/* 74h */	virtual bool IsPlayable() = 0;
		/* 78h */	virtual bool IsViewableLarge() = 0;
		/* 7Ch */	virtual bool func7Ch() = 0;
		/* 80h */	virtual bool func80h() = 0;
		/* 84h */	virtual bool func84h() = 0;
		/* 88h */	virtual int func88h() = 0;
		/* 8Ch */	virtual bool GetConsequenceTraits(eastl::vector<uint32_t>& dst) = 0;
		/* 90h */	virtual bool GetAssetID(uint64_t& dst) = 0;
		/* 94h */	virtual int64_t GetTimeDownloaded() = 0;
		/* 98h */	virtual void* func98h() = 0;
		/* 9Ch */	virtual int func9Ch() = 0;
		/* A0h */	virtual void SetKeyInternal(const ResourceKey& key, bool asyncLoad) = 0;
		/* A4h */	virtual void SetAssetMetadata(bool asyncLoad) = 0;
		/* A8h */	virtual bool funcA8h() = 0;
		/* ACh */	virtual void SetSummary(bool asyncLoad) = 0;
		/* B0h */	virtual void ProcessSummary(OTDB::ParameterResource* pSummary) = 0;
		/* B4h */	virtual void SetParameter(const OTDB::Parameter& parameter) = 0;

		/* 04h */	ResourceKey mKey;
	};

	class cSPAssetDataOTDB
		: public IAssetData
		, public Object
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x13D6B42B;

		cSPAssetDataOTDB();
		~cSPAssetDataOTDB();

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual void SetKey(const ResourceKey& key) override;
		virtual void func08h() override;
		virtual const char16_t* GetName() override;
		virtual const char16_t* GetAuthorName() override;
		virtual const char16_t* GetDescription() override;
		virtual ResourceKey GetImageKey() override;
		virtual ResourceKey GetBackgroundImageKey() override;
		virtual void GetTags(eastl::string16& dst) override;
		virtual uint32_t GetAssetSubtype() override;
		virtual int64_t GetTimeCreated() override;
		virtual bool HasName() override;
		virtual int func30h() override;
		virtual int func34h() override;
		virtual int func38h() override;
		virtual float func3Ch() override;
		virtual const ResourceKey& GetKey() override;
		virtual void AsyncSetKey(const ResourceKey& key) override;
		virtual bool func48h() override;
		virtual void func4Ch() override;
		virtual void LoadData() override;
		virtual int64_t GetAuthorID() override;
		virtual bool func58h() override;
		virtual bool func5Ch() override;
		virtual bool IsEditable() override;
		virtual bool func64h() override;
		virtual bool IsShareable() override;
		virtual bool func6Ch() override;
		virtual bool IsShared() override;
		virtual bool IsPlayable() override;
		virtual bool IsViewableLarge() override;
		virtual bool func7Ch() override;
		virtual bool func80h() override;
		virtual bool func84h() override;
		virtual int func88h() override;
		virtual bool GetConsequenceTraits(eastl::vector<uint32_t>& dst) override;
		virtual bool GetAssetID(uint64_t& dst) override;
		virtual int64_t GetTimeDownloaded() override;
		virtual void* func98h() override;
		virtual int func9Ch() override;
		virtual void SetKeyInternal(const ResourceKey& key, bool asyncLoad) override;
		virtual void SetAssetMetadata(bool asyncLoad) override;
		virtual bool funcA8h() override;
		virtual void SetSummary(bool asyncLoad) override;
		virtual void ProcessSummary(OTDB::ParameterResource* pSummary) override;
		virtual void SetParameter(const OTDB::Parameter& parameter) override;

	public:
		/* 1Ch */	cAssetMetadataPtr mpMetadata;
		/* 20h */	PropertyListPtr field_20;
		/* 24h */	bool mIsPlayable;
		/* 25h */	bool mIsViewableLarge;
		/* 26h */	bool mIsEditable;
		/* 28h */	uint32_t mSubtype;
		/* 2Ch */	int field_2C;  // 2
		/* 30h */	float field_30;  // not initialized
		/* 34h */	float field_34;  // not initialized
		/* 38h */	float field_38;  // not initialized
		/* 3Ch */	ObjectPtr field_3C;
		/* 40h */	eastl::fixed_vector<int, 5> field_40;
		/* 6Ch */	int field_6C;
		/* 70h */	IAsyncRequestPtr mpAsyncMetadata;
		/* 74h */	IAsyncRequestPtr mpAsyncSummary;
	};
	ASSERT_SIZE(cSPAssetDataOTDB, 0x78);

	namespace Addresses(cSPAssetDataOTDB)
	{
		DeclareAddress(SetKey);

		DeclareAddress(GetName);
		DeclareAddress(GetAuthorName);
		DeclareAddress(GetDescription);
		DeclareAddress(GetImageKey);
		DeclareAddress(GetBackgroundImageKey);
		DeclareAddress(GetTags);

		DeclareAddress(GetTimeCreated);
		DeclareAddress(HasName);


		DeclareAddress(func38h);
		DeclareAddress(func3Ch);

		DeclareAddress(AsyncSetKey);
		DeclareAddress(func48h);
		DeclareAddress(func4Ch);
		DeclareAddress(LoadData);
		DeclareAddress(GetAuthorID);

		DeclareAddress(IsEditable);
		DeclareAddress(func64h);
		DeclareAddress(IsShareable);

		DeclareAddress(IsShared);


		DeclareAddress(func7Ch);
		DeclareAddress(func80h);

		DeclareAddress(GetConsequenceTraits);
		DeclareAddress(GetAssetID);
		DeclareAddress(GetTimeDownloaded);

		DeclareAddress(func9Ch);
		DeclareAddress(SetKeyInternal);
		DeclareAddress(SetAssetMetadata);
		DeclareAddress(funcA8h);
		DeclareAddress(SetSummary);
		DeclareAddress(ProcessSummary);
		DeclareAddress(SetParameter);
	}
}