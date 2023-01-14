#ifndef MODAPI_DLL_EXPORT
#include <Spore\Sporepedia\ObjectTemplateDB.h>
#include <Spore\Sporepedia\AssetData.h>
#include <Spore\Sporepedia\AssetViewManager.h>

namespace Sporepedia
{
	namespace OTDB
	{
		auto_STATIC_METHOD_(cObjectTemplateDB, cObjectTemplateDB*, Get);
	}

	auto_STATIC_METHOD_(cAssetViewManager, cAssetViewManager*, Get);

	auto_METHOD_VOID(class_B8, SetAssetDataFactory, Args(uint32_t typeID, AssetDataFactory factory),
		Args(typeID, factory));


	IAssetData::IAssetData()
		: mKey() {}

	IAssetData::~IAssetData() {}

	cSPAssetDataOTDB::cSPAssetDataOTDB()
		: mpMetadata()
		, field_20()
		, mIsPlayable()
		, mIsViewableLarge()
		, mIsEditable()
		, mSubtype()
		, field_2C(2)
		, field_3C()
		, field_40()
		, field_6C()
		, mpAsyncMetadata()
		, mpAsyncSummary()
	{
	}

	cSPAssetDataOTDB::~cSPAssetDataOTDB()
	{
	}

	int cSPAssetDataOTDB::AddRef() {
		return DefaultRefCounted::AddRef();
	}
	int cSPAssetDataOTDB::Release() {
		return DefaultRefCounted::Release();
	}
	void* cSPAssetDataOTDB::Cast(uint32_t type) const {
		CLASS_CAST(Object);
		CLASS_CAST(IAssetData);
		CLASS_CAST(cSPAssetDataOTDB);
		return nullptr;
	}


	auto_METHOD_VIRTUAL_VOID(cSPAssetDataOTDB, IAssetData, SetKey, Args(const ResourceKey& key), Args(key));

	void cSPAssetDataOTDB::func08h() {}

	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, const char16_t*, GetName);
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, const char16_t*, GetAuthorName);
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, const char16_t*, GetDescription);
	RedirectVirtualMethod_noargs_structret(cSPAssetDataOTDB, IAssetData, GetImageKey, ResourceKey);
	RedirectVirtualMethod_noargs_structret(cSPAssetDataOTDB, IAssetData, GetBackgroundImageKey, ResourceKey);
	auto_METHOD_VIRTUAL_VOID(cSPAssetDataOTDB, IAssetData, GetTags, Args(eastl::string16& dst), Args(dst));

	uint32_t cSPAssetDataOTDB::GetAssetSubtype() {
		return mSubtype;
	}
	
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, int64_t, GetTimeCreated);
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, HasName);

	int cSPAssetDataOTDB::func30h() {
		return 0;
	}
	int cSPAssetDataOTDB::func34h() {
		return 0;
	}
	
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, int, func38h);
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, float, func3Ch);

	const ResourceKey& cSPAssetDataOTDB::GetKey() {
		return mKey;
	}

	auto_METHOD_VIRTUAL_VOID(cSPAssetDataOTDB, IAssetData, AsyncSetKey, Args(const ResourceKey& key), Args(key));
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, func48h);
	auto_METHOD_VIRTUAL_VOID_(cSPAssetDataOTDB, IAssetData, func4Ch);
	auto_METHOD_VIRTUAL_VOID_(cSPAssetDataOTDB, IAssetData, LoadData);
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, int64_t, GetAuthorID);

	bool cSPAssetDataOTDB::func58h() {
		return false;
	}
	bool cSPAssetDataOTDB::func5Ch() {
		return true;
	}

	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, IsEditable);
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, func64h);
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, IsShareable);

	bool cSPAssetDataOTDB::func6Ch() {
		return true;
	}
	
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, IsShared);

	bool cSPAssetDataOTDB::IsPlayable() {
		return mIsPlayable;
	}
	bool cSPAssetDataOTDB::IsViewableLarge() {
		return mIsViewableLarge;
	}

	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, func7Ch);
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, func80h);

	bool cSPAssetDataOTDB::func84h() {
		return false;
	}
	int cSPAssetDataOTDB::func88h() {
		return field_6C;
	}

	auto_METHOD_VIRTUAL(cSPAssetDataOTDB, IAssetData, bool, GetConsequenceTraits, Args(eastl::vector<uint32_t>& dst), Args(dst));
	auto_METHOD_VIRTUAL(cSPAssetDataOTDB, IAssetData, bool, GetAssetID, Args(uint64_t& dst), Args(dst));
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, int64_t, GetTimeDownloaded);

	void* cSPAssetDataOTDB::func98h() {
		return &field_2C;
	}
	
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, int, func9Ch);
	auto_METHOD_VIRTUAL_VOID(cSPAssetDataOTDB, IAssetData, SetKeyInternal, Args(const ResourceKey& key, bool asyncLoad), Args(key, asyncLoad));
	auto_METHOD_VIRTUAL_VOID(cSPAssetDataOTDB, IAssetData, SetAssetMetadata, Args(bool asyncLoad), Args(asyncLoad));
	auto_METHOD_VIRTUAL_(cSPAssetDataOTDB, IAssetData, bool, funcA8h);
	auto_METHOD_VIRTUAL_VOID(cSPAssetDataOTDB, IAssetData, SetSummary, Args(bool asyncLoad), Args(asyncLoad));
	auto_METHOD_VIRTUAL_VOID(cSPAssetDataOTDB, IAssetData, ProcessSummary, Args(OTDB::ParameterResource* pSummary), Args(pSummary));
	auto_METHOD_VIRTUAL_VOID(cSPAssetDataOTDB, IAssetData, SetParameter, Args(const OTDB::Parameter& parameter), Args(parameter));
}
#endif