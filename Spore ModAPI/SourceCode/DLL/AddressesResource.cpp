#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Resource\cResourceManager.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\PFIndexModifiable.h>
#include <Spore\Resource\PFRecordRead.h>
#include <Spore\Resource\PFRecordWrite.h>

namespace Resource
{
	namespace Addresses(cResourceManager)
	{
		DefineAddress(NeedsToRelease, SelectAddress(0x8DE6D0, 0x8DE520, 0x8DE530));
		DefineAddress(ReleaseResources, SelectAddress(0x8E1CC0, 0x8E19C0, 0x8E19D0));
		DefineAddress(GetResource, SelectAddress(0x8DF7E0, 0x8DF6F0, 0x8DF700));
		DefineAddress(func10h, SelectAddress(0x8DF810, 0x8DF720, 0x8DF730));
		const uintptr_t GetAsyncResource = func10h;
		DefineAddress(GetCachedResource, SelectAddress(0x8DE730, 0x8DE580, 0x8DE590));
		DefineAddress(func18h, SelectAddress(0x8DFB50, 0x8DFA60, 0x8DFA70));
		DefineAddress(ReadResource, SelectAddress(0x8DFCF0, 0x8DFC00, 0x8DFC10));
		DefineAddress(WriteResource, SelectAddress(0x8DEE90, 0x8DED90, 0x8DEDA0));
		DefineAddress(SetTypeRemap, SelectAddress(0x8E1EF0, 0x8E1BF0, 0x8E1C00));
		DefineAddress(GetTypeRemap, SelectAddress(0x8E0E70, 0x8E0B80, 0x8E0B90));
		DefineAddress(GetGeneralTypeID, SelectAddress(0x8DFD20, 0x8DFC30, 0x8DFC40));
		DefineAddress(GetRealFileKey, SelectAddress(0x8DFD60, 0x8DFC70, 0x8DFC80));
		DefineAddress(func34h, SelectAddress(0x8E0F00, 0x8E0C10, 0x8E0C20));
		DefineAddress(GetFileKeys, SelectAddress(0x8E0FF0, 0x8E0CF0, 0x8E0D00));
		DefineAddress(func3Ch, SelectAddress(0x8E11D0, 0x8E0ED0, 0x8E0EE0));
		DefineAddress(func40h, SelectAddress(0x8E0A50, 0x8E0760, 0x8E0770));
		DefineAddress(SetResourceFactory, SelectAddress(0x8E2010, 0x8E1D10, 0x8E1D20));
		DefineAddress(GetResourceFactory, SelectAddress(0x8DFED0, 0x8DFDE0, 0x8DFDF0));
		DefineAddress(GetResourceFactories, SelectAddress(0x8E03D0, 0x8E01F0, 0x8E0200));
		DefineAddress(AddDBPF, SelectAddress(0x8E12F0, 0x8E0FF0, 0x8E1000));
		DefineAddress(GetPriority, SelectAddress(0x8DE780, 0x8DE5D0, 0x8DE5E0));
		DefineAddress(GetDBPF, SelectAddress(0x8DE7C0, 0x8DE610, 0x8DE620));
		DefineAddress(GetAllDBPFs, SelectAddress(0x8E0550, 0x8E0370, 0x8E0380));
		DefineAddress(func60h, SelectAddress(0x8DEFB0, 0x8DEEB0, 0x8DEEC0));
		DefineAddress(func64h, SelectAddress(0x8E2310, 0x8E2010, 0x8E2020));
		DefineAddress(GetResourceCache, SelectAddress(0x8DE810, 0x8DE660, 0x8DE670));
		DefineAddress(func6Ch, SelectAddress(0x8DE860, 0x8DE6B0, 0x8DE6C0));
		DefineAddress(func70h, SelectAddress(0x8DE8B0, 0x8DE700, 0x8DE710));
		DefineAddress(GetResourceCaches, SelectAddress(0x8E05E0, 0x8E0400, 0x8E0410));
		DefineAddress(AddFileName, SelectAddress(0x8DE6E0, 0x8DE530, 0x8DE540));
		DefineAddress(GetFileName, SelectAddress(0x8E0660, 0x8E0480, 0x8E0490));
		DefineAddress(SetFileName, SelectAddress(0x8E1A40, 0x8E1740, 0x8E1750));
		DefineAddress(RemoveFileName, SelectAddress(0x8E1AA0, 0x8E17A0, 0x8E17B0));
		DefineAddress(GetTypeID, SelectAddress(0x8DFF50, 0x8DFE60, 0x8DFE70));
		DefineAddress(GetExtension, SelectAddress(0x8E0010, 0x8DFF20, 0x8DFF30));
		DefineAddress(AddExtensionMapping, SelectAddress(0x8E1B20, 0x8E1820, 0x8E1830));
		DefineAddress(RemoveExtensionMapping, SelectAddress(0x8E1BD0, 0x8E18D0, 0x8E18E0));
	}

	namespace Addresses(DatabasePackedFile)
	{
		DefineAddress(GetType, SelectAddress(0x8D9B60, 0x8D9790, 0x8D97A0));
		DefineAddress(GetReferenceCount, SelectAddress(0x69D630, 0x69D3F0, 0x69D3F0));
		DefineAddress(UseIndexMutex, SelectAddress(0x8D88C0, 0x8D84E0, 0x8D84F0));
		DefineAddress(Load, SelectAddress(0x8D90A0, 0x8D8C90, 0x8D8CA0));
		DefineAddress(Save, SelectAddress(0x8D9FF0, 0x8D9CC0, 0x8D9CD0));
		DefineAddress(GetAccessFlags, SelectAddress(0x8D88F0, 0xFF02D0, 0xFF02D0));
		DefineAddress(Write, SelectAddress(0x8DB150, 0x8DAEB0, 0x8DAEC0));
		DefineAddress(GetPath, SelectAddress(0xAE92B0, 0xA426C0, 0xA42700));
		DefineAddress(SetPath, SelectAddress(0x8DA000, 0x8D9CD0, 0x8D9CE0));
		DefineAddress(GetFiles, SelectAddress(0x8D8DF0, 0x8D8A20, 0x8D8A30));
		DefineAddress(GetFile, SelectAddress(0x8DA980, 0x8DA6E0, 0x8DA6F0));
		DefineAddress(func38h, SelectAddress(0x8D9C40, 0x8D9870, 0x8D9880));
		DefineAddress(func3Ch, SelectAddress(0x8DA050, 0x8D9D20, 0x8D9D30));
		DefineAddress(RemoveFile, SelectAddress(0x8D9290, 0x8D8E80, 0x8D8E90));
		DefineAddress(SetResourceManager, SelectAddress(0x8D8C80, 0x8D88B0, 0x8D88C0));
		DefineAddress(GetAllocator, SelectAddress(0x6BD860, 0x7F5550, 0x7F55C0));
		DefineAddress(GetStream, SelectAddress(0x8D8D90, 0x8D89C0, 0x8D89D0));
		DefineAddress(SetStream, SelectAddress(0x8D8DA0, 0x8D89D0, 0x8D89E0));

		DefineAddress(CreatePFRecordRead, SelectAddress(0x8D89E0, 0x8D85F0, 0x8D8600));
		DefineAddress(CreatePFRecordReadCopy, SelectAddress(0x8D89A0, 0x8D85B0, 0x8D85C0));
		DefineAddress(CreatePFRecordWriteData, SelectAddress(0x8D8950, 0x8D8560, 0x8D8570));
		DefineAddress(CreatePFRecordWrite, SelectAddress(0x8D8900, 0x8D8510, 0x8D8520));
		DefineAddress(Read, SelectAddress(0x8D8A20, 0x8D8630, 0x8D8640));
		DefineAddress(ReadHeader, SelectAddress(0x8D9370, 0x8D8F60, 0x8D8F70));
		DefineAddress(Reset, SelectAddress(0x8D9540, 0x8D9130, 0x8D9140));
		DefineAddress(IsReadyForWrite, SelectAddress(0x8D9600, 0x8D91F0, 0x8D9200));
		DefineAddress(IsValidHeader, SelectAddress(0x8D94B0, 0x8D90A0, 0x8D90B0));
		DefineAddress(ReadIndex, SelectAddress(0x8DAD00, 0x8DAA60, 0x8DAA70));
		DefineAddress(WriteIndex, SelectAddress(0x8D9CD0, 0x8D9900, 0x8D9910));
		DefineAddress(StreamCanContainFileData, SelectAddress(0x8D9720, 0x8D9310, 0x8D9320));
		DefineAddress(CreatePFIndexModifiable, SelectAddress(0x8D8A60, 0x8D8670, 0x8D8680));
		DefineAddress(ReleaseObject, SelectAddress(0x6BC5B0, 0x8D86A0, 0x8D86B0));
		DefineAddress(RenovateIndex, SelectAddress(0x8D8A90, 0x8D86C0, 0x8D86D0));
		DefineAddress(func90h, SelectAddress(0x8D9E50, 0x8D9A80, 0x8D9A90));


		DefineAddress(ReadBytes, SelectAddress(0x8D8FB0, 0x8D8BE0, 0x8D8BF0));
		DefineAddress(ReadData, SelectAddress(0x8D9770, 0x6BCA80, 0x6BCA80));
	}

	namespace Addresses(StandardFileFilter) 
	{
		DefineAddress(IsValid, SelectAddress(0x404F10, 0x404F10, 0x404F10));
	}

	namespace Addresses(IResourceManager)
	{
		DefineAddress(Get, SelectAddress(0x8DE650, 0x8DE4A0, 0x8DE4B0));
	}

	namespace Addresses(PFIndexModifiable)
	{
		DefineAddress(func04h, SelectAddress(0xA37650, 0xB1FB00, 0xB1FB30));
		DefineAddress(IsEmpty, SelectAddress(0x8DBCE0, 0x6BF430, 0x6BF430));
		DefineAddress(GetFileCount, SelectAddress(0xA654F0, 0x8E8220, 0x8E8230));
		DefineAddress(Reset, SelectAddress(0x8DBCF0, 0x8DBA90, 0x8DBAA0));
		DefineAddress(GetTotalDiskSize, SelectAddress(0x8DB570, 0x8DB2B0, 0x8DB2C0));
		DefineAddress(GetDataEnd, SelectAddress(0x8DB510, 0x8DB250, 0x8DB260));
		DefineAddress(GetFiles, SelectAddress(0x8DC250, 0x8DBFF0, 0x8DC000));
		DefineAddress(GetAllFiles, SelectAddress(0x8DC310, 0x8DC0B0, 0x8DC0C0));
		DefineAddress(func24h, SelectAddress(0x8DC810, 0x8DC5B0, 0x8DC5C0));
		DefineAddress(GetFileInfo, SelectAddress(0x8DBD70, 0x8DBB10, 0x8DBB20));
		DefineAddress(PutFileInfo, SelectAddress(0x8DC410, 0x8DC1B0, 0x8DC1C0));
		DefineAddress(RemoveFile, SelectAddress(0x8DBDB0, 0x8DBB50, 0x8DBB60));
		DefineAddress(Read, SelectAddress(0x8DBF10, 0x8DBCB0, 0x8DBCC0));
		DefineAddress(Write, SelectAddress(0x8DB5C0, 0x8DB300, 0x8DB310));
		DefineAddress(SetIsSaved, SelectAddress(0x8DB800, 0x8DB540, 0x8DB550));
		DefineAddress(CheckFilesInRange, SelectAddress(0x8DB850, 0x8DB590, 0x8DB5A0));
		DefineAddress(CheckFilesInSizeRange, SelectAddress(0x8DB8E0, 0x8DB620, 0x8DB630));
	}

	namespace Addresses(PFRecordRead)
	{
		DefineAddress(GetName, SelectAddress(0x6C07B0, 0x8DCA90, 0x8DCAA0));
		DefineAddress(SetName, SelectAddress(0x8DCCC0, 0x6B4250, 0x6B4250));
		DefineAddress(GetStream, SelectAddress(0x6C07C0, 0x8DC640, 0x8DC650));
		DefineAddress(GetParentDBPF, SelectAddress(0xFC8510, 0x6C0230, 0x6C0230));
		DefineAddress(Open, SelectAddress(0x8DCFD0, 0x6C0810, 0x8DCD60));
		DefineAddress(Close, SelectAddress(0x8DCFF0, 0x6C0830, 0x8DCD80));
		DefineAddress(func28h, SelectAddress(0x8DCF80, 0x6C07C0, 0x8DCD10));

		DefineAddress(GetType, SelectAddress(0x8DC8A0, 0x6C0240, 0x8DC670));
		DefineAddress(GetAccessFlags, SelectAddress(0x8DCCF0, 0x8DC670, 0x8DC680));
		DefineAddress(GetState, SelectAddress(0x1065680, 0xE31100, 0xE310C0));
		// DefineAddress(REMOVE_THIS_Close, SelectAddress(0x6C07D0, 0x8DC650, 0x8DC660));
		DefineAddress(GetSize, SelectAddress(0x113BA60, 0xBB9C20, 0x113AE80));
		DefineAddress(SetSize, SelectAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(GetPosition, SelectAddress(0x8DC8B0, 0x6C0250, 0x8DC690));
		DefineAddress(SetPosition, SelectAddress(0x8DD030, 0x6C0870, 0x8DCDC0));
		DefineAddress(GetAvailable, SelectAddress(0x8DC8F0, 0x6C0290, 0x8DC6D0));
		DefineAddress(Read, SelectAddress(0x8DD0F0, 0x6C0930, 0x8DCE80));
		DefineAddress(Flush, SelectAddress(0xA37650, 0xB1FB00, 0xB1FB30));
		DefineAddress(Write, SelectAddress(0x951320, 0x950E00, 0x950E00));


		DefineAddress(ReadData, SelectAddress(0x8DCA40, 0x6C03F0, 0x8DC820));
	}

	namespace Addresses(PFRecordWrite)
	{
		DefineAddress(GetName, SelectAddress(0x6C07B0, 0x8DCA90, 0x8DCAA0));
		DefineAddress(SetName, SelectAddress(0x8DCCC0, 0x6B4250, 0x6B4250));
		DefineAddress(GetStream, SelectAddress(0x6C07C0, 0x8DC640, 0x8DC650));
		DefineAddress(GetParentDBPF, SelectAddress(0xFC8510, 0x6C0230, 0x6C0230));
		DefineAddress(Open, SelectAddress(0x8DD170, 0x8DCF50, 0x8DCF60));
		DefineAddress(Close, SelectAddress(0x6C0F80, 0x6C09B0, 0x6C09B0));
		DefineAddress(func28h, SelectAddress(0x6C0F20, 0x8DCEF0, 0x8DCF00));

		DefineAddress(GetType, SelectAddress(0x8DCCE0, 0x6C04C0, 0x8DCAB0));
		DefineAddress(GetAccessFlags, SelectAddress(0x8DCCF0, 0x8DC670, 0x8DC680));
		DefineAddress(GetState, SelectAddress(0x1065680, 0xE31100, 0xE310C0));
		// DefineAddress(REMOVE_THIS_Close, SelectAddress(0x66AD60, 0xB1E3E0, 0xB1E410));
		DefineAddress(GetSize, SelectAddress(0x8DCD00, 0x8DCAB0, 0x8DCAC0));
		DefineAddress(SetSize, SelectAddress(0x6C0A70, 0x8DCAE0, 0x8DCAF0));
		DefineAddress(GetPosition, SelectAddress(0x8DCD30, 0x6C04D0, 0x6C04D0));
		DefineAddress(SetPosition, SelectAddress(0x6C0AB0, 0x8DCB20, 0x8DCB30));
		DefineAddress(GetAvailable, SelectAddress(0x8DCD70, 0x8DCB60, 0x8DCB70));
		DefineAddress(Read, SelectAddress(0x8DCDA0, 0x6C0510, 0x6C0510));
		DefineAddress(Flush, SelectAddress(0x8DCDE0, 0x6C0550, 0x6C0550));
		DefineAddress(Write, SelectAddress(0x6C0AF0, 0x6C0580, 0x6C0580));
	}
}
#endif
