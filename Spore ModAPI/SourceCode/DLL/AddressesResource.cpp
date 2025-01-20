#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Resource\cResourceManager.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\DatabaseDirectoryFiles.h>
#include <Spore\Resource\IKeyFilter.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\PFIndexModifiable.h>
#include <Spore\Resource\PFRecordRead.h>
#include <Spore\Resource\PFRecordWrite.h>
#include <Spore\Resource\FakeRecord.h>
#include <Spore\Resource\Paths.h>

namespace Resource
{
	namespace Addresses(cResourceManager)
	{
		DefineAddress(GetResource, SelectAddress(0x8DF7E0, 0x8DF700)); 
		DefineAddress(ReleaseResources, SelectAddress(0x8E1CC0, 0x8E19D0));
		DefineAddress(NeedsToRelease, SelectAddress(0x8DE6D0, 0x8DE530));
		DefineAddress(func10h, SelectAddress(0x8DF810, 0x8DF730));
		DefineAddress(GetAsyncResource, SelectAddress(0x8DF810, 0x8DF730));
		DefineAddress(GetCachedResource, SelectAddress(0x8DE730, 0x8DE590));
		DefineAddress(func18h, SelectAddress(0x8DFB50, 0x8DFA70));
		DefineAddress(ReadResource, SelectAddress(0x8DFCF0, 0x8DFC10));
		DefineAddress(WriteResource, SelectAddress(0x8DEE90, 0x8DEDA0));
		DefineAddress(SetTypeRemap, SelectAddress(0x8E1EF0, 0x8E1C00));
		DefineAddress(GetTypeRemap, SelectAddress(0x8E0E70, 0x8E0B90));
		DefineAddress(GetGeneralTypeID, SelectAddress(0x8DFD20, 0x8DFC40));
		DefineAddress(GetRealFileKey, SelectAddress(0x8DFD60, 0x8DFC80));
		DefineAddress(func34h, SelectAddress(0x8E0F00, 0x8E0C20));
		DefineAddress(GetFileKeys, SelectAddress(0x8E0FF0, 0x8E0D00));
		DefineAddress(func3Ch, SelectAddress(0x8E11D0, 0x8E0EE0));
		DefineAddress(func40h, SelectAddress(0x8E0A50, 0x8E0770));
		DefineAddress(SetResourceFactory, SelectAddress(0x8E2010, 0x8E1D20));
		DefineAddress(GetResourceFactory, SelectAddress(0x8DFED0, 0x8DFDF0));
		DefineAddress(GetResourceFactories, SelectAddress(0x8E03D0, 0x8E0200));
		DefineAddress(AddDBPF, SelectAddress(0x8E12F0, 0x8E1000));
		DefineAddress(GetPriority, SelectAddress(0x8DE780, 0x8DE5E0));
		DefineAddress(GetDBPF, SelectAddress(0x8DE7C0, 0x8DE620));
		DefineAddress(GetAllDBPFs, SelectAddress(0x8E0550, 0x8E0380));
		DefineAddress(func60h, SelectAddress(0x8DEFB0, 0x8DEEC0));
		DefineAddress(func64h, SelectAddress(0x8E2310, 0x8E2020));
		DefineAddress(GetResourceCache, SelectAddress(0x8DE810, 0x8DE670));
		DefineAddress(func6Ch, SelectAddress(0x8DE860, 0x8DE6C0));
		DefineAddress(func70h, SelectAddress(0x8DE8B0, 0x8DE710));
		DefineAddress(GetResourceCaches, SelectAddress(0x8E05E0, 0x8E0410));
		DefineAddress(AddFileName, SelectAddress(0x8DE6E0, 0x8DE540));
		DefineAddress(GetFileName, SelectAddress(0x8E0660, 0x8E0490));
		DefineAddress(SetFileName, SelectAddress(0x8E1A40, 0x8E1750));
		DefineAddress(RemoveFileName, SelectAddress(0x8E1AA0, 0x8E17B0));
		DefineAddress(GetTypeID, SelectAddress(0x8DFF50, 0x8DFE70));
		DefineAddress(GetExtension, SelectAddress(0x8E0010, 0x8DFF30));
		DefineAddress(AddExtensionMapping, SelectAddress(0x8E1B20, 0x8E1830));
		DefineAddress(RemoveExtensionMapping, SelectAddress(0x8E1BD0, 0x8E18E0));

		DefineAddress(Dispose, SelectAddress(0x8E1CC0, 0x8E19D0));
		DefineAddress(Initialize, SelectAddress(0x8DE6D0, 0x8DE530));
		DefineAddress(GetResourceAsync, SelectAddress(0x8DF810, 0x8DF730));
		DefineAddress(GetLoadedResource, SelectAddress(0x8DE730, 0x8DE590));
		DefineAddress(ReloadResource, SelectAddress(0x8DFB50, 0x8DFA70));
		DefineAddress(GetPrivateResource, SelectAddress(0x8DFCF0, 0x8DFC10));
		DefineAddress(SetTypeMapping, SelectAddress(0x8E1EF0, 0x8E1C00));
		DefineAddress(GetRecordTypesFromResourceType, SelectAddress(0x8E0E70, 0x8E0B90));
		DefineAddress(GetTypeMapping, SelectAddress(0x8DFD20, 0x8DFC40));
		DefineAddress(FindRecord, SelectAddress(0x8DFD60, 0x8DFC80));
		DefineAddress(GetResourceKeyList, SelectAddress(0x8E0F00, 0x8E0C20));
		DefineAddress(GetRecordKeyList, SelectAddress(0x8E0FF0, 0x8E0D00));
		DefineAddress(GetRecordKeyList2, SelectAddress(0x8E11D0, 0x8E0EE0));
		DefineAddress(RegisterChangeNotification, SelectAddress(0x8E0A50, 0x8E0770));
		DefineAddress(RegisterFactory, SelectAddress(0x8E2010, 0x8E1D20));
		DefineAddress(FindFactory, SelectAddress(0x8DFED0, 0x8DFDF0));
		DefineAddress(GetFactoryList, SelectAddress(0x8E03D0, 0x8E0200));
		DefineAddress(RegisterDatabase, SelectAddress(0x8E12F0, 0x8E1000));
		DefineAddress(IsDatabaseRegistered, SelectAddress(0x8DE780, 0x8DE5E0));
		DefineAddress(FindDatabase, SelectAddress(0x8DE7C0, 0x8DE620));
		DefineAddress(GetDatabaseList, SelectAddress(0x8E0550, 0x8E0380));
		DefineAddress(DoDatabaseChanged, SelectAddress(0x8DEFB0, 0x8DEEC0));
		DefineAddress(RegisterCache, SelectAddress(0x8E2310, 0x8E2020));
		DefineAddress(FindCache, SelectAddress(0x8DE810, 0x8DE670));
		DefineAddress(CacheResource, SelectAddress(0x8DE860, 0x8DE6C0));
		DefineAddress(FlushCache, SelectAddress(0x8DE8B0, 0x8DE710));
		DefineAddress(GetCacheList, SelectAddress(0x8E05E0, 0x8E0410));
		DefineAddress(GetKeyFromName, SelectAddress(0x8DE6E0, 0x8DE540));
		DefineAddress(GetNameFromKey, SelectAddress(0x8E0660, 0x8E0490));
		DefineAddress(SetKeyName, SelectAddress(0x8E1A40, 0x8E1750));
		DefineAddress(ForgetKeyName, SelectAddress(0x8E1AA0, 0x8E17B0));
		DefineAddress(GetTypeFromTypename, SelectAddress(0x8DFF50, 0x8DFE70));
		DefineAddress(GetTypenameFromType, SelectAddress(0x8E0010, 0x8DFF30));
		DefineAddress(SetTypename, SelectAddress(0x8E1B20, 0x8E1830));
		DefineAddress(ResetTypename, SelectAddress(0x8E1BD0, 0x8E18E0));
	}

	namespace Addresses(DatabasePackedFile)
	{
		DefineAddress(GetType, SelectAddress(0x8D9B60, 0x8D97A0));
		DefineAddress(GetReferenceCount, SelectAddress(0x69D630, 0x69D3F0));
		DefineAddress(UseIndexMutex, SelectAddress(0x8D88C0, 0x8D84F0));
		DefineAddress(Load, SelectAddress(0x8D90A0, 0x8D8CA0));
		DefineAddress(Save, SelectAddress(0x8D9FF0, 0x8D9CD0));
		DefineAddress(GetAccessFlags, SelectAddress(0x8D88F0, 0xFF02D0));
		DefineAddress(Write, SelectAddress(0x8DB150, 0x8DAEC0));
		DefineAddress(GetPath, SelectAddress(0xAE92B0, 0xA42700));
		DefineAddress(SetPath, SelectAddress(0x8DA000, 0x8D9CE0));
		DefineAddress(GetFiles, SelectAddress(0x8D8DF0, 0x8D8A30));
		DefineAddress(GetFile, SelectAddress(0x8DA980, 0x8DA6F0));
		DefineAddress(func38h, SelectAddress(0x8D9C40, 0x8D9880));
		DefineAddress(func3Ch, SelectAddress(0x8DA050, 0x8D9D30));
		DefineAddress(RemoveFile, SelectAddress(0x8D9290, 0x8D8E90));
		DefineAddress(SetResourceManager, SelectAddress(0x8D8C80, 0x8D88C0));
		DefineAddress(GetAllocator, SelectAddress(0x6BD860, 0x7F55C0));
		DefineAddress(GetStream, SelectAddress(0x8D8D90, 0x8D89D0));
		DefineAddress(SetStream, SelectAddress(0x8D8DA0, 0x8D89E0));
		DefineAddress(CreatePFRecordRead, SelectAddress(0x8D89E0, 0x8D8600));
		DefineAddress(CreatePFRecordReadCopy, SelectAddress(0x8D89A0, 0x8D85C0));
		DefineAddress(CreatePFRecordWriteData, SelectAddress(0x8D8950, 0x8D8570));
		DefineAddress(CreatePFRecordWrite, SelectAddress(0x8D8900, 0x8D8520));
		DefineAddress(Read, SelectAddress(0x8D8A20, 0x8D8640));
		DefineAddress(ReadHeader, SelectAddress(0x8D9370, 0x8D8F70));
		DefineAddress(Reset, SelectAddress(0x8D9540, 0x8D9140));
		DefineAddress(IsReadyForWrite, SelectAddress(0x8D9600, 0x8D9200));
		DefineAddress(IsValidHeader, SelectAddress(0x8D94B0, 0x8D90B0));
		DefineAddress(ReadIndex, SelectAddress(0x8DAD00, 0x8DAA70));
		DefineAddress(WriteIndex, SelectAddress(0x8D9CD0, 0x8D9910));
		DefineAddress(StreamCanContainFileData, SelectAddress(0x8D9720, 0x8D9320));
		DefineAddress(CreatePFIndexModifiable, SelectAddress(0x8D8A60, 0x8D8680));
		DefineAddress(ReleaseObject, SelectAddress(0x6BC5B0, 0x8D86B0));
		DefineAddress(RenovateIndex, SelectAddress(0x8D8A90, 0x8D86D0));
		DefineAddress(func90h, SelectAddress(0x8D9E50, 0x8D9A90));
		DefineAddress(ReadBytes, SelectAddress(0x8D8FB0, 0x8D8BF0));
		DefineAddress(ReadData, SelectAddress(0x8D9770, 0x6BCA80));

		DefineAddress(GetDatabaseType, SelectAddress(0x8D9B60, 0x8D97A0));
		DefineAddress(GetRefCount, SelectAddress(0x69D630, 0x69D3F0));
		DefineAddress(Lock, SelectAddress(0x8D88C0, 0x8D84F0));
		DefineAddress(Open, SelectAddress(0x8D90A0, 0x8D8CA0));
		DefineAddress(Close, SelectAddress(0x8D9FF0, 0x8D9CD0));
		DefineAddress(Flush, SelectAddress(0x8DB150, 0x8DAEC0));
		DefineAddress(GetLocation, SelectAddress(0xAE92B0, 0xA42700));
		DefineAddress(SetLocation, SelectAddress(0x8DA000, 0x8D9CE0));
		DefineAddress(GetKeyList, SelectAddress(0x8D8DF0, 0x8D8A30));
		DefineAddress(OpenRecord, SelectAddress(0x8DA980, 0x8DA6F0));
		DefineAddress(GetOpenCount, SelectAddress(0x8D9C40, 0x8D9880));
		DefineAddress(CloseRecord, SelectAddress(0x8DA050, 0x8D9D30));
		DefineAddress(DeleteRecord, SelectAddress(0x8D9290, 0x8D8E90));
		DefineAddress(Attach, SelectAddress(0x8D8C80, 0x8D88C0));
		DefineAddress(CreateRecordRead, SelectAddress(0x8D89E0, 0x8D8600));
		DefineAddress(CreateRecordReadCopy, SelectAddress(0x8D89A0, 0x8D85C0));
		DefineAddress(CreateRecordWriteData, SelectAddress(0x8D8950, 0x8D8570));
		DefineAddress(CreateRecordWrite, SelectAddress(0x8D8900, 0x8D8520));
		DefineAddress(ReadHeaders, SelectAddress(0x8D8A20, 0x8D8640));
		DefineAddress(ReadHeaderRecord, SelectAddress(0x8D9370, 0x8D8F70));
		DefineAddress(WriteEmptyHeaderRecord, SelectAddress(0x8D9540, 0x8D9140));
		DefineAddress(WriteHeaderRecord, SelectAddress(0x8D9600, 0x8D9200));
		DefineAddress(VerifyHeaderRecordIntegrity, SelectAddress(0x8D94B0, 0x8D90B0));
		DefineAddress(ReadIndexRecord, SelectAddress(0x8DAD00, 0x8DAA70));
		DefineAddress(WriteIndexRecord, SelectAddress(0x8D9CD0, 0x8D9910));
		DefineAddress(VerifyIndexRecordIntegrity, SelectAddress(0x8D9720, 0x8D9320));
		DefineAddress(CreateIndex, SelectAddress(0x8D8A60, 0x8D8680));
		DefineAddress(DestroyIndex, SelectAddress(0x6BC5B0, 0x8D86B0));
		DefineAddress(MakeIndexModifiable, SelectAddress(0x8D8A90, 0x8D86D0));
		DefineAddress(InitializeHoleTable, SelectAddress(0x8D9E50, 0x8D9A90));
	}

	namespace Addresses(StandardFileFilter) 
	{
		DefineAddress(IsValid, SelectAddress(0x404F10, 0x404F10));
	}

	namespace Addresses(IResourceManager)
	{
		DefineAddress(Get, SelectAddress(0x8DE650, 0x8DE4B0));
	}

	namespace Addresses(PFIndexModifiable)
	{
		DefineAddress(func04h, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(IsEmpty, SelectAddress(0x8DBCE0, 0x6BF430));
		DefineAddress(GetFileCount, SelectAddress(0xA654F0, 0x8E8230));
		DefineAddress(Reset, SelectAddress(0x8DBCF0, 0x8DBAA0));
		DefineAddress(GetTotalDiskSize, SelectAddress(0x8DB570, 0x8DB2C0));
		DefineAddress(GetDataEnd, SelectAddress(0x8DB510, 0x8DB260));
		DefineAddress(GetFiles, SelectAddress(0x8DC250, 0x8DC000));
		DefineAddress(GetAllFiles, SelectAddress(0x8DC310, 0x8DC0C0));
		DefineAddress(func24h, SelectAddress(0x8DC810, 0x8DC5C0));
		DefineAddress(GetFileInfo, SelectAddress(0x8DBD70, 0x8DBB20));
		DefineAddress(PutFileInfo, SelectAddress(0x8DC410, 0x8DC1C0));
		DefineAddress(RemoveFile, SelectAddress(0x8DBDB0, 0x8DBB60));
		DefineAddress(Read, SelectAddress(0x8DBF10, 0x8DBCC0));
		DefineAddress(Write, SelectAddress(0x8DB5C0, 0x8DB310));
		DefineAddress(SetIsSaved, SelectAddress(0x8DB800, 0x8DB550));
		DefineAddress(CheckFilesInRange, SelectAddress(0x8DB850, 0x8DB5A0));
		DefineAddress(CheckFilesInSizeRange, SelectAddress(0x8DB8E0, 0x8DB630));
	}

	namespace Addresses(PFRecordRead)
	{
		DefineAddress(GetName, SelectAddress(0x6C07B0, 0x8DCAA0));
		DefineAddress(SetName, SelectAddress(0x8DCCC0, 0x6B4250));
		DefineAddress(GetStream, SelectAddress(0x6C07C0, 0x8DC650));
		DefineAddress(GetParentDBPF, SelectAddress(0xFC8510, 0x6C0230));
		DefineAddress(Open, SelectAddress(0x8DCFD0, 0x8DCD60));
		DefineAddress(Close, SelectAddress(0x8DCFF0, 0x8DCD80));
		DefineAddress(func28h, SelectAddress(0x8DCF80, 0x8DCD10));

		DefineAddress(GetType, SelectAddress(0x8DC8A0, 0x8DC670));
		DefineAddress(GetAccessFlags, SelectAddress(0x8DCCF0, 0x8DC680));
		DefineAddress(GetState, SelectAddress(0x1065680, 0xE310C0));
		// DefineAddress(REMOVE_THIS_Close, SelectAddress(0x6C07D0, 0x8DC660));
		DefineAddress(GetSize, SelectAddress(0x113BA60, 0x113AE80));
		DefineAddress(SetSize, SelectAddress(0x101B0F0, 0xDDE930));
		DefineAddress(GetPosition, SelectAddress(0x8DC8B0, 0x8DC690));
		DefineAddress(SetPosition, SelectAddress(0x8DD030, 0x8DCDC0));
		DefineAddress(GetAvailable, SelectAddress(0x8DC8F0, 0x8DC6D0));
		DefineAddress(Read, SelectAddress(0x8DD0F0, 0x8DCE80));
		DefineAddress(Flush, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(Write, SelectAddress(0x951320, 0x950E00));


		DefineAddress(ReadData, SelectAddress(0x8DCA40, 0x8DC820));


		DefineAddress(GetKey, SelectAddress(0x6C07B0, 0x8DCAA0));
		DefineAddress(SetKey, SelectAddress(0x8DCCC0, 0x6B4250));
		DefineAddress(GetDatabase, SelectAddress(0xFC8510, 0x6C0230));
		DefineAddress(RecordOpen, SelectAddress(0x8DCFD0, 0x8DCD60));
		DefineAddress(RecordClose, SelectAddress(0x8DCFF0, 0x8DCD80));
		DefineAddress(DoPostClose, SelectAddress(0x8DCF80, 0x8DCD10));
	}

	namespace Addresses(PFRecordWrite)
	{
		DefineAddress(GetName, SelectAddress(0x6C07B0, 0x8DCAA0));
		DefineAddress(SetName, SelectAddress(0x8DCCC0, 0x6B4250));
		DefineAddress(GetStream, SelectAddress(0x6C07C0, 0x8DC650));
		DefineAddress(GetParentDBPF, SelectAddress(0xFC8510, 0x6C0230));
		DefineAddress(Open, SelectAddress(0x8DD170, 0x8DCF60));
		DefineAddress(Close, SelectAddress(0x6C0F80, 0x6C09B0));
		DefineAddress(func28h, SelectAddress(0x6C0F20, 0x8DCF00));

		DefineAddress(GetType, SelectAddress(0x8DCCE0, 0x8DCAB0));
		DefineAddress(GetAccessFlags, SelectAddress(0x8DCCF0, 0x8DC680));
		DefineAddress(GetState, SelectAddress(0x1065680, 0xE310C0));
		// DefineAddress(REMOVE_THIS_Close, SelectAddress(0x66AD60, 0xB1E410));
		DefineAddress(GetSize, SelectAddress(0x8DCD00, 0x8DCAC0));
		DefineAddress(SetSize, SelectAddress(0x6C0A70, 0x8DCAF0));
		DefineAddress(GetPosition, SelectAddress(0x8DCD30, 0x6C04D0));
		DefineAddress(SetPosition, SelectAddress(0x6C0AB0, 0x8DCB30));
		DefineAddress(GetAvailable, SelectAddress(0x8DCD70, 0x8DCB70));
		DefineAddress(Read, SelectAddress(0x8DCDA0, 0x6C0510));
		DefineAddress(Flush, SelectAddress(0x8DCDE0, 0x6C0550));
		DefineAddress(Write, SelectAddress(0x6C0AF0, 0x6C0580));

		DefineAddress(GetKey, SelectAddress(0x6C07B0, 0x8DCAA0));
		DefineAddress(SetKey, SelectAddress(0x8DCCC0, 0x6B4250));
		DefineAddress(GetDatabase, SelectAddress(0xFC8510, 0x6C0230));
		DefineAddress(RecordOpen, SelectAddress(0x8DD170, 0x8DCF60));
		DefineAddress(RecordClose, SelectAddress(0x6C0F80, 0x6C09B0));
		DefineAddress(DoPostClose, SelectAddress(0x6C0F20, 0x8DCF00));
	}

	namespace Addresses(Paths)
	{
		DefineAddress(GetDirFromID, SelectAddress(0x6888A0, 0x688650));
		DefineAddress(GetDirectory, SelectAddress(0x688A20, 0x6887D0));
		DefineAddress(RegisterDirectory, SelectAddress(0x688DF0, 0x688BA0));
		DefineAddress(GetSaveArea, SelectAddress(0x6B22C0, 0x6B1F20));
		DefineAddress(RegisterSaveArea, SelectAddress(0x6B3A90, 0x6B36F0));
		DefineAddress(CreateTempFile, SelectAddress(0x932AC0, 0x932550));
		DefineAddress(CreateSaveAreaDirectoryDatabase, SelectAddress(0x6B2950, 0x6B25B0));
	};

	namespace Addresses(DatabaseDirectoryFiles)
	{
		//DefineAddress(Initialize, SelectAddress(0x6BC1D0, 0x6BBDC0));
		DefineAddress(Dispose, SelectAddress(0x8D63E0, 0x8D60D0));
		//DefineAddress(GetDatabaseType);
		DefineAddress(GetRefCount, SelectAddress(0x69D630, 0x69D3F0));
		DefineAddress(Lock, SelectAddress(0x8D6440, 0x8D6130));
		DefineAddress(Open, SelectAddress(0x8D6640, 0x8D6330));
		DefineAddress(Close, SelectAddress(0x8D79E0, 0x8D7640));
		//DefineAddress(GetAccessFlags);
		DefineAddress(Flush, SelectAddress(0x8D6AD0, 0x8D6760));
		//DefineAddress(GetLocation);
		DefineAddress(SetLocation, SelectAddress(0x8D6D40, 0x8D69A0));
		DefineAddress(GetKeyList, SelectAddress(0x8D7210, 0x8D6E70));
		DefineAddress(OpenRecord, SelectAddress(0x8D83A0, 0x8D7FD0));
		DefineAddress(GetOpenCount, SelectAddress(0x8D6B60, 0x8D67F0));
		DefineAddress(CloseRecord, SelectAddress(0x8D6D90, 0x8D69F0));
		DefineAddress(DeleteRecord, SelectAddress(0x8D7A40, 0x8D76A0));
		DefineAddress(Attach, SelectAddress(0x8D6950, 0x8D6640));
		//DefineAddress(GetAllocator);
		DefineAddress(AddExtensionMapping, SelectAddress(0x8D7330, 0x8D6F90));
		//DefineAddress(SetFileNameToKeyConverter);
		DefineAddress(UpdateRecordData, SelectAddress(0x8D8160, 0x8D7DB0));
		DefineAddress(UpdateRecordData2, SelectAddress(0x8D8050, 0x8D7CA0));
		DefineAddress(GetTypeFromTypename, SelectAddress(0x8D6840, 0x8D6530));
		DefineAddress(GetTypenameFromType, SelectAddress(0x8D68F0, 0x8D65E0));
		DefineAddress(GetFileNameFromKey, SelectAddress(0x8D6BD0, 0x8D6860));
		DefineAddress(GetKeyFromFileName, SelectAddress(0x8D6500, 0x8D61F0));
		//DefineAddress(GetDefaultGroupId);
		//DefineAddress(SetDefaultGroupId);
	}

	namespace Addresses(FakeRecord) {
		DefineAddress(_ctor, SelectAddress(0x8E2940, 0x8E2650));
	}
}

namespace Addresses(Resource)
{
	DefineAddress(ReadExtensionMappingsFromPropFile, SelectAddress(0x6B2440, 0x6B20A0));
	DefineAddress(SaveNamedResource, SelectAddress(0x6B4340, 0x6B3FA0));
}

#endif
