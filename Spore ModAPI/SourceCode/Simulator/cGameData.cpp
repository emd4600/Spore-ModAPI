#ifndef MODAPI_DLL_EXPORT
#include <Spore\Simulator\cGameData.h>

namespace Simulator
{
	//auto_METHOD_VIRTUAL(cGameData, cGameData, bool, Write, Args(ISerializerStream* stream), Args(stream));
	auto_METHOD_VIRTUAL(cGameData, cGameData, bool, Read, Args(ISerializerStream* stream), Args(stream));
	auto_METHOD_VIRTUAL_(cGameData, cGameData, bool, func18h);
	auto_METHOD_VIRTUAL(cGameData, cGameData, bool, WriteToXML, Args(int arg_0), Args(arg_0));
	auto_METHOD_VIRTUAL(cGameData, cGameData, bool, SetDefinitionID, Args(int arg_0), Args(arg_0));
	auto_METHOD_VIRTUAL_VOID(cGameData, cGameData, SetGameDataOwner, Args(cGameData* pOwner), Args(pOwner));
	auto_METHOD_VIRTUAL_(cGameData, cGameData, bool, IsDestroyed);
	
	auto_METHOD_VIRTUAL_VOID(cGameData, cGameData, SetGameDataOwner2, Args(cGameData* pOwner), Args(pOwner));

	auto_METHOD_VIRTUAL(cGameData, cGameData, bool, func3Ch, Args(int arg_0), Args(arg_0));

	auto_METHOD_VIRTUAL_VOID_(cGameData, cGameData, RemoveOwner);
	
	auto_METHOD_VIRTUAL(cGameData, cGameData, int, WriteAsText, Args(int arg_0), Args(arg_0));

	cGameData* cGameData::GetGameDataOwner() {
		return mpGameDataOwner.get();
	}

	void cGameData::SetPoliticalID(uint32_t id) {
		mPoliticalID = id;
	}

	uint32_t cGameData::GetPoliticalID() {
		return mPoliticalID;
	}

	bool cGameData::func40h() {
		return true;
	}

	int cGameData::AddRef() {
		return DefaultRefCounted::AddRef();
	}
	int cGameData::Release() {
		return DefaultRefCounted::Release();
	}

	void* cGameData::Cast(uint32_t type) const {
		CLASS_CAST(ISimulatorSerializable);
		CLASS_CAST(Object);
		CLASS_CAST(cGameData);
		return nullptr;
	}

	cGameData::cGameData()
		: field_14()
		, field_18()
		, field_1C(0xFFFFFFFF)
		, field_20()
		, mbIsDestroyed()
		, mID(0xFFFFFFFF)
		, mDefinitionID()
		, mpGameDataOwner()
		, mPoliticalID(0xFFFFFFFF)
	{}
}
#endif