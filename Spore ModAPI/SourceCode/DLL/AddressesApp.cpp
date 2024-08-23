#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\App\SPPropertyIDs.h>
#include <Spore\App\cArithmeticaResource.h>
#include <Spore\App\cCameraManager.h>
#include <Spore\App\cCheatManager.h>
#include <Spore\App\cCreatureModeStrategy.h>
#include <Spore\App\cCellModeStrategy.h>
#include <Spore\App\cGameModeManager.h>
#include <Spore\App\cMessageManager.h>
#include <Spore\App\ConfigManager.h>
#include <Spore\App\cPropManager.h>
#include <Spore\App\cViewer.h>
#include <Spore\App\DirectPropertyList.h>
#include <Spore\App\ICheatManager.h>
#include <Spore\App\IGameModeManager.h>
#include <Spore\App\IMessageManager.h>
#include <Spore\App\IPropManager.h>
#include <Spore\App\IClassManager.h>
#include <Spore\App\JobManager.h>
#include <Spore\App\cJob.h>
#include <Spore\App\cMouseCamera.h>
#include <Spore\App\IStateManager.h>
#include <Spore\App\Property.h>
#include <Spore\App\PropertyList.h>
#include <Spore\App\ScenarioMode.h>
#include <Spore\App\Thumbnail_cImportExport.h>
#include <Spore\App\cLocaleManager.h>
#include <Spore\App\AppData.h>
#include <Spore\App\IDGenerator.h>
#include <Spore\App\cSporeApp.h>
#include <Spore\App\Canvas.h>

namespace Addresses(App)
{
	DefineAddress(sAppCommandLine, SelectAddress(0x1601BA8, 0x15FD920));
#ifndef SDK_TO_GHIDRA
	DefineAddress(AppProperties_ptr, SelectAddress(0x1601BA0, 0x15FD918));
#else 
	DefineAddress(sAppProperties, SelectAddress(0x1601BA0, 0x15FD918));
#endif
}

namespace App
{
	namespace Addresses(cCameraManager)
	{
		DefineAddress(HandleMessage, SelectAddress(0x7C6D40, 0x7C66B0));
		DefineAddress(AddRef, SelectAddress(0xAE9150, 0xC6AB00));
		DefineAddress(Release, SelectAddress(0x5BF860, 0x7B87B0));
		DefineAddress(Initialize, SelectAddress(0x7C77E0, 0x7C7150));
		DefineAddress(Dispose, SelectAddress(0x7C7540, 0x7C6E50));
		DefineAddress(SetViewer, SelectAddress(0x7C6770, 0x7C61A0));
		DefineAddress(GetViewer, SelectAddress(0x7C6780, 0xA21090));
		DefineAddress(AddCameraType, SelectAddress(0x7C7620, 0x7C6F30));
		DefineAddress(PutCamera, SelectAddress(0x7C79A0, 0x7C7310));
		DefineAddress(ParseCameras, SelectAddress(0x7C72B0, 0x7C6C20));
		DefineAddress(Update, SelectAddress(0x7C6B00, 0x7C6440));
		DefineAddress(SetActiveCameraByKey, SelectAddress(0x7C6790, 0x7C61B0));
		DefineAddress(SetActiveCameraByID, SelectAddress(0x7C6DE0, 0x7C6750));
		DefineAddress(GetActiveCamera, SelectAddress(0x7C6820, 0x7C6240));
		DefineAddress(GetActiveCameraID, SelectAddress(0x7C67D0, 0x7C61F0));
		DefineAddress(GetCamera, SelectAddress(0x7C6E30, 0x7C67A0));
		DefineAddress(GetCameraID, SelectAddress(0x7C6C40, 0x7C6580));
		DefineAddress(GetCamerasCount, SelectAddress(0x7C6840, 0x7C6260));
		DefineAddress(GetCameraAt, SelectAddress(0x7C6850, 0x7C6270));
		DefineAddress(GetCameraIDAt, SelectAddress(0x7C6BE0, 0x7C6520));
		DefineAddress(SetActiveCamera, SelectAddress(0x7C6B80, 0x7C64C0));
		DefineAddress(GetActiveCameraIndex, SelectAddress(0xE464D0, 0x98F870));
		DefineAddress(RemoveCameras, SelectAddress(0x7C7640, 0x7C6F50));
	}

	namespace Addresses(cCheatManager)
	{
		DefineAddress(Initialize, SelectAddress(0x67EE90, 0x67ECC0));
		DefineAddress(Dispose, SelectAddress(0x67F630, 0x67F350));
		DefineAddress(func14h, SelectAddress(0x7E66D0, 0xC2E640));
		DefineAddress(AddCheat, SelectAddress(0x67FF40, 0x67FC10));
		DefineAddress(RemoveCheat, SelectAddress(0x67FCA0, 0x67F970));
		DefineAddress(ProcessLine, SelectAddress(0x67F150, 0x67EF80));
		DefineAddress(func24h, SelectAddress(0x67E580, 0x67E430));
		DefineAddress(GetCheat, SelectAddress(0x67F710, 0x67F430));
		DefineAddress(GetKeywords, SelectAddress(0x67FA00, 0x67F6D0));
		DefineAddress(func30h, SelectAddress(0x67F7E0, 0x67F500));
		DefineAddress(func34h, SelectAddress(0x67F860, 0x67F580));
		DefineAddress(GetArgScript, SelectAddress(0x113BA60, 0x113AE80));
		DefineAddress(func3Ch, SelectAddress(0x67E880, 0x67E6B0));
		DefineAddress(func40h, SelectAddress(0x67E8C0, 0x67E6F0));
		DefineAddress(func44h, SelectAddress(0x67E900, 0x67E730));
		DefineAddress(func48h, SelectAddress(0xABFB10, 0xABF790));
		DefineAddress(func4Ch, SelectAddress(0x67E200, 0x67E0A0));
	}

	namespace Addresses(cGameModeManager)
	{
		DefineAddress(HandleMessage, SelectAddress(0x7D86A0, 0x7D8240));

		DefineAddress(AddRef, SelectAddress(0xCF91C0, 0x671F20));
		DefineAddress(Release, SelectAddress(0xD57BB0, 0xAE0620));

		DefineAddress(Initialize, SelectAddress(0x7D8580, 0x7D8120));
		DefineAddress(Dispose, SelectAddress(0x7D9640, 0x7D91E0));
		DefineAddress(func14h, SelectAddress(0x7D8710, 0x7D82B0));
		DefineAddress(InitializeModes, SelectAddress(0x7D8750, 0x7D82F0));
		DefineAddress(ClearActiveMode, SelectAddress(0x7D8990, 0x7D8530));
		DefineAddress(AddGameMode, SelectAddress(0x7D9780, 0x7D9320));
		DefineAddress(RemoveGameMode, SelectAddress(0x7D9510, 0x7D90B0));
		DefineAddress(SetActiveMode, SelectAddress(0x7D9150, 0x7D8CF0));
		DefineAddress(GetActiveMode, SelectAddress(0x7D87E0, 0x7D8380));
		DefineAddress(GetGameMode, SelectAddress(0x7D8790, 0x7D8330));
		DefineAddress(GetModeIDAt, SelectAddress(0x7D8930, 0x7D84D0));
		DefineAddress(GetActiveModeID, SelectAddress(0x7D8820, 0x7D83C0));
		DefineAddress(GetModeCount, SelectAddress(0x7D8860, 0x7D8400));
		DefineAddress(SetActiveModeAt, SelectAddress(0x7D91A0, 0x7D8D40));
		DefineAddress(GetGameModeAt, SelectAddress(0x7D88F0, 0x7D8490));
		DefineAddress(func48h, SelectAddress(0x108DD90, 0x111CD70));
		DefineAddress(SetActiveModeByName, SelectAddress(0x7D8880, 0x7D8420));
		DefineAddress(GetCameraManager, SelectAddress(0xB18420, 0x967D90));
		DefineAddress(SetViewer, SelectAddress(0x7D8970, 0x7D8510));
		DefineAddress(GetViewer, SelectAddress(0x804E60, 0x5AADB0));
	}

	namespace Addresses(cMessageManager)
	{
		DefineAddress(Initialize, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(Dispose, SelectAddress(0x885780, 0x884BD0));
		DefineAddress(GetOption, SelectAddress(0x884370, 0x883970));
		DefineAddress(SetOption, SelectAddress(0x884400, 0x883A00));
		DefineAddress(PostMSG, SelectAddress(0x885F10, 0x8854A0));
		DefineAddress(func18h, SelectAddress(0x8863F0, 0x885980));
		DefineAddress(func1Ch, SelectAddress(0x886490, 0x885A20));
		DefineAddress(AddListener, SelectAddress(0x8844D0, 0x883AD0));
		DefineAddress(AddUnmanagedListener, SelectAddress(0x884490, 0x883A90));
		DefineAddress(AddHandler, SelectAddress(0x884520, 0x883B20));
		DefineAddress(RemoveListener, SelectAddress(0x884590, 0x883B90));
		DefineAddress(RemoveHandler, SelectAddress(0x884590, 0x883B90));
		DefineAddress(func34h, SelectAddress(0x884C30, 0x8841F0));
		DefineAddress(func38h, SelectAddress(0x8853A0, 0x8847F0));
		DefineAddress(func3Ch, SelectAddress(0x98F7F0, 0x98F4D0));
		DefineAddress(UseMutex, SelectAddress(0x8845A0, 0x883BA0));
		DefineAddress(AddEntry, SelectAddress(0x885920, 0x884D70));
		DefineAddress(RemoveEntry, SelectAddress(0x885270, 0x8846C0));

		DefineAddress(MessageSend, SelectAddress(0x885F10, 0x8854A0));
		DefineAddress(MessagePost, SelectAddress(0x8863F0, 0x885980));
		DefineAddress(MessagePostFunction, SelectAddress(0x886490, 0x885A20));
		DefineAddress(ProcessQueue, SelectAddress(0x884C30, 0x8841F0));
		DefineAddress(ProcessQueue2, SelectAddress(0x8853A0, 0x8847F0));
		DefineAddress(GetMessageQueue, SelectAddress(0x98F7F0, 0x98F4D0));
		DefineAddress(Lock, SelectAddress(0x8845A0, 0x883BA0));
	}

	namespace Addresses(cPropManager)
	{
		DefineAddress(HandleMessage, SelectAddress(0x6A5A30, 0x6A58D0));

		DefineAddress(GetType, SelectAddress(0x1065680, 0xE310C0));
		DefineAddress(CreateResource, SelectAddress(0x6A3580, 0x6A3330));
		DefineAddress(AsyncAccess, SelectAddress(0x4BB8E0, 0x4BC5B0));
		DefineAddress(Read, SelectAddress(0x6AB2B0, 0x6AB150));
		DefineAddress(Write, SelectAddress(0x6AA2C0, 0x6AA160));
		DefineAddress(GetSupportedTypes, SelectAddress(0x6A3650, 0x6A3400));
		DefineAddress(IsValid, SelectAddress(0x4CBDE0, 0x7F9CA0));

		DefineAddress(AddRef, SelectAddress(0x947080, 0x7685A0));
		DefineAddress(Release, SelectAddress(0x57CB00, 0x67D9F0));
		DefineAddress(func08h, SelectAddress(0x6A3550, 0x6A3300));
		DefineAddress(Initialize, SelectAddress(0x6A9CF0, 0x6A9B90));
		DefineAddress(PreloadPropertyLists, SelectAddress(0x6A7FD0, 0x6A7E70));
		DefineAddress(Dispose, SelectAddress(0x6AA950, 0x6AA7F0));
		DefineAddress(GetPropertyID, SelectAddress(0x6A6100, 0x6A5FA0));
		DefineAddress(GetPropertyName, SelectAddress(0x6A5B00, 0x6A59A0));
		DefineAddress(func20h, SelectAddress(0x6A6160, 0x6A6000));
		DefineAddress(GetPropertyGroupName, SelectAddress(0x6A5B40, 0x6A59E0));
		DefineAddress(HasPropertyList, SelectAddress(0x6A4400, 0x6A4270));
		DefineAddress(GetPropertyList, SelectAddress(0x6A6240, 0x6A60E0));
		DefineAddress(GetGlobalPropertyList, SelectAddress(0x6A3560, 0x6A3310));
		DefineAddress(SetPropertyList, SelectAddress(0x6A6350, 0x6A61F0));
		DefineAddress(func38h, SelectAddress(0x6A5B80, 0x6A5A20));
		DefineAddress(func3Ch, SelectAddress(0x6A5D10, 0x6A5BB0));
		DefineAddress(func40h, SelectAddress(0x6A5C20, 0x6A5AC0));
		DefineAddress(func44h, SelectAddress(0x6A4490, 0x6A4300));
		DefineAddress(GetAllListIDs, SelectAddress(0x6AAAA0, 0x6AA940));
		DefineAddress(func4Ch, SelectAddress(0x6AA260, 0x6AA100));
		DefineAddress(GetPropertyDefinition, SelectAddress(0x6A3F70, 0x6A3D60));
		DefineAddress(GetPropertyGroupsCount, SelectAddress(0x6A3C30, 0x6A39B0));
		DefineAddress(GetPropertyGroupIDAt, SelectAddress(0x6A3C60, 0x6A39E0));


		DefineAddress(GetFactoryType, SelectAddress(0x1065680, 0xE310C0));
		DefineAddress(CreateResourceAsync, SelectAddress(0x4BB8E0, 0x4BC5B0));
		DefineAddress(ReadResource, SelectAddress(0x6AB2B0, 0x6AB150));
		DefineAddress(WriteResource, SelectAddress(0x6AA2C0, 0x6AA160));
		DefineAddress(CanConvert, SelectAddress(0x4CBDE0, 0x7F9CA0));

		DefineAddress(SetDevMode, SelectAddress(0x6A3550, 0x6A3300));
		DefineAddress(GetIDFromName, SelectAddress(0x6A6100, 0x6A5FA0));
		DefineAddress(GetNameFromID, SelectAddress(0x6A5B00, 0x6A59A0));
		DefineAddress(GetPropertyGroupIDFromName, SelectAddress(0x6A6160, 0x6A6000));
		DefineAddress(GetNameFromPropertyGroupID, SelectAddress(0x6A5B40, 0x6A59E0));
		DefineAddress(AddPropertyList, SelectAddress(0x6A6350, 0x6A61F0));
		DefineAddress(RemovePropertyList, SelectAddress(0x6A5B80, 0x6A5A20));
		DefineAddress(RemovePropertyLists, SelectAddress(0x6A5D10, 0x6A5BB0));
		DefineAddress(RemovePropertyLists2, SelectAddress(0x6A5C20, 0x6A5AC0));
		DefineAddress(AreAnyPropertyListsReferenced, SelectAddress(0x6A4490, 0x6A4300));
		DefineAddress(GetPropertyListIDs, SelectAddress(0x6AAAA0, 0x6AA940));
	}

	namespace Addresses(cViewer)
	{
		DefineAddress(SetViewTransform, SelectAddress(0x7C53A0, 0x7C4DD0));
		DefineAddress(GetViewTransform, SelectAddress(0x7C4790, 0x7C41C0));
		DefineAddress(Initialize, SelectAddress(0x7C5470, 0x7C4EA0));
		DefineAddress(ClearScene, SelectAddress(0x7C42F0, 0x7C3D20));
		DefineAddress(LoadTransformations, SelectAddress(0x7C5650, 0x7C5080));
		DefineAddress(SetBackgroundColor, SelectAddress(0x7C42C0, 0x7C3CF0));
		DefineAddress(GetNearPlane, SelectAddress(0x7C4330, 0x7C3D60));
		DefineAddress(GetFarPlane, SelectAddress(0x7C4340, 0x7C3D70));
		DefineAddress(SetNearPlane, SelectAddress(0x7C5240, 0x7C4C70));
		DefineAddress(SetFarPlane, SelectAddress(0x7C5260, 0x7C4C90));
		DefineAddress(SetAspectRatio, SelectAddress(0x7C51F0, 0x7C4C20));
		DefineAddress(SetCameraMaterialLODs, SelectAddress(0x7C43A0, 0x7C3DD0));
		DefineAddress(GetCameraMaterialLODs, SelectAddress(0x7C4B80, 0x7C45B0));
		DefineAddress(SetRenderType, SelectAddress(0x7C4380, 0x7C3DB0));
		DefineAddress(GetCameraToMouse, SelectAddress(0x7C4FA0, 0x7C49D0));
		DefineAddress(GetCameraToPoint, SelectAddress(0x7C4DD0, 0x7C4800));
		DefineAddress(SetViewWindow, SelectAddress(0x7C51A0, 0x7C4BD0));
		DefineAddress(SetViewOffset, SelectAddress(0x7C5170, 0x7C4BA0));
		DefineAddress(SetViewport, SelectAddress(0x7C5100, 0x7C4B30));
		DefineAddress(SetPerspectiveProjection, SelectAddress(0x7C5A50, 0x7C5480));
		DefineAddress(SetParallelProjection, SelectAddress(0x7C5AC0, 0x7C54F0));
		DefineAddress(Dispose, SelectAddress(0x7C4240, 0x7C3C70));
		DefineAddress(BeginUpdate, SelectAddress(0x7C5650, 0x7C5080));
		DefineAddress(EndUpdate, SelectAddress(0x7C42B0, 0x7C3CE0));
	}

	namespace Addresses(DirectPropertyList)
	{
		DefineAddress(SetProperty, SelectAddress(0x6A3310, 0x6A30C0));
		DefineAddress(RemoveProperty, SelectAddress(0x6A3140, 0x6A2EF0));
		DefineAddress(HasProperty, SelectAddress(0x6A2A20, 0x6A27D0));
		DefineAddress(GetPropertyAlt, SelectAddress(0x6A20A0, 0x6A1E50));
		DefineAddress(GetProperty, SelectAddress(0x6A2B10, 0x6A28C0));
		DefineAddress(GetPropertyObject, SelectAddress(0x6A2A50, 0x6A2800));
		DefineAddress(CopyFrom, SelectAddress(0x6A2D20, 0x6A2AD0));
		DefineAddress(AddPropertiesFrom, SelectAddress(0x6A1850, 0x6A1600));
		DefineAddress(CopyAllPropertiesFrom, SelectAddress(0x6A1720, 0x6A14D0));
		DefineAddress(AddAllPropertiesFrom, SelectAddress(0x6A1760, 0x6A1510));
		DefineAddress(Read, SelectAddress(0x6A33C0, 0x6A3170));
		DefineAddress(Write, SelectAddress(0x6A1890, 0x6A1640));
		DefineAddress(GetPropertyIDs, SelectAddress(0x6A33D0, 0x6A3180));
		DefineAddress(Clear, SelectAddress(0x6A2D70, 0x6A2B20));

		DefineAddress(SetBool, SelectAddress(0x6A1A30, 0x6A17E0));
		DefineAddress(SetInt, SelectAddress(0x6A1AD0, 0x6A1880));
		DefineAddress(SetFloat, SelectAddress(0x6A1B60, 0x6A1910));
	}

	namespace Addresses(ICheatManager)
	{
		DefineAddress(Get, SelectAddress(0x67DF40, 0x67DDE0));
	}

	namespace Addresses(IClassManager)
	{
		DefineAddress(Get, SelectAddress(0x9205E0, 0x920320));
	}

	namespace Addresses(IGameModeManager)
	{
		DefineAddress(Get, SelectAddress(0x67DE30, 0x67DCD0));
	}

	namespace Addresses(IMessageManager)
	{
		DefineAddress(Get, SelectAddress(0x67DDE0, 0x67DC80));
	}

	namespace Addresses(IPropManager)
	{
		DefineAddress(Get, SelectAddress(0x67DF50, 0x67DDF0));
	}

	/*namespace Addresses(IStateManager) 
	{
		DefineAddress(Get, SelectAddress(0x67DE40, 0x67DCE0));
	}*/

	namespace Addresses(Property)
	{
		DefineAddress(GetValueInt32, SelectAddress(0x41ECF0, 0x41E950));
		DefineAddress(GetValueFloat, SelectAddress(0x41EDD0, 0x41EA30));
		DefineAddress(GetValueBool, SelectAddress(0x41EC80, 0x41E8E0));
		DefineAddress(GetValueUInt32, SelectAddress(0x41ED60, 0x41E9C0));
		DefineAddress(GetValueVector2, SelectAddress(0x6A11C0, 0x6A0F70));
		DefineAddress(GetValueVector3, SelectAddress(0xCCE1D0, 0xCCEA90));
		DefineAddress(GetValueVector4, SelectAddress(0x6A11F0, 0x6A0FA0));
		DefineAddress(GetValueColorRGB, SelectAddress(0x6A1220, 0x6A0FD0));
		DefineAddress(GetValueColorRGBA, SelectAddress(0x6A1250, 0x6A1000));
		DefineAddress(GetValueKey, SelectAddress(0x6A1280, 0x6A1030));
		DefineAddress(GetValueTransform, SelectAddress(0x6A12B0, 0x6A1060));
		DefineAddress(GetValueText, SelectAddress(0x6A12E0, 0x6A1090));
		DefineAddress(GetValueBBox, SelectAddress(0x6A3B10, 0x5F23A0));
		DefineAddress(GetValueString8, SelectAddress(0x60ED10, 0x60EF10));
		DefineAddress(GetValueString16, SelectAddress(0x68A740, 0x68A4E0));

		DefineAddress(GetValueChar, SelectAddress(0x6A3930, 0x6A36E0));
		DefineAddress(GetValueWChar, SelectAddress(0x6A3960, 0x6A3710));
		DefineAddress(GetValueInt8, SelectAddress(0x6A3990, 0x6A3740));
		DefineAddress(GetValueUInt8, SelectAddress(0x6A39C0, 0x6A3770));
		DefineAddress(GetValueInt16, SelectAddress(0x6A39F0, 0x6A37A0));
		DefineAddress(GetValueUInt16, SelectAddress(0x6A2E20, 0x6A37D0));
		DefineAddress(GetValueInt64, SelectAddress(0x6A3A50, 0x6A3800));
		DefineAddress(GetValueUInt64, SelectAddress(0x6A3A80, 0x6A3830));
		DefineAddress(GetValueDouble, SelectAddress(0x6A3AB0, 0x6A3860));
		DefineAddress(GetValueFlags, SelectAddress(0x6A3AE0, 0x6A3890));
		DefineAddress(GetValue, SelectAddress(0x447140, 0x4474C0));


		DefineAddress(Set, SelectAddress(0x93E250, 0x93DCF0));
		DefineAddress(SetValueInt32, SelectAddress(0x422E10, 0x422EB0));
		DefineAddress(SetValueUInt32, SelectAddress(0x428400, 0x428010));
		DefineAddress(SetValueKey, SelectAddress(0x422EA0, 0x422F40));
		DefineAddress(SetValueString8, SelectAddress(0x4B59E0, 0x4B62F0));
		DefineAddress(SetValueString16, SelectAddress(0x427E60, 0x427A10));
		DefineAddress(SetValueFloat, SelectAddress(0x428490, 0x4280A0));
		DefineAddress(SetValueBool, SelectAddress(0x422D80, 0x422E20));
		DefineAddress(SetValueBBox, SelectAddress(0x4781B0, 0x478800));
		DefineAddress(SetValueVector2, SelectAddress(0x6A3760, 0x6A3510));
		DefineAddress(SetValueVector3, SelectAddress(0x6A37C0, 0x6A3570));
		DefineAddress(SetValueVector4, SelectAddress(0x6A3830, 0x6A35E0));
		DefineAddress(SetValueColorRGB, SelectAddress(0x6A3860, 0x6A3610));
		DefineAddress(SetValueColorRGBA, SelectAddress(0x6A38D0, 0x6A3680));


		DefineAddress(GetBool, SelectAddress(0x407140, 0x407190));
		DefineAddress(GetFloat, SelectAddress(0x40CE70, 0x40CF10));
		DefineAddress(GetInt32, SelectAddress(0x410290, 0x410330));
		DefineAddress(GetUInt32, SelectAddress(0x4AF0A0, 0x4AF730));
		DefineAddress(GetVector2, SelectAddress(0x6A1310, 0x6A10C0));
		DefineAddress(GetVector3, SelectAddress(0x6A1360, 0x6A1110));
		DefineAddress(GetVector4, SelectAddress(0x6A13B0, 0x6A1160));
		DefineAddress(GetColorRGB, SelectAddress(0x6A1400, 0x6A11B0));
		DefineAddress(GetColorRGBA, SelectAddress(0x6A1450, 0x6A1200));
		DefineAddress(GetKey, SelectAddress(0x6A14A0, 0x6A1250));
		DefineAddress(GetKeyInstanceID, SelectAddress(0x6A14F0, 0x6A12A0));
		DefineAddress(GetKeyGroupID, SelectAddress(0x6A1530, 0x6A12E0));
		DefineAddress(GetKeyTypeID, SelectAddress(0x6A1570, 0x6A1320));
		DefineAddress(GetText, SelectAddress(0x6A15B0, 0x6A1360));
		DefineAddress(GetCString8, SelectAddress(0x6A16A0, 0x6A1450));
		DefineAddress(GetCString16, SelectAddress(0x6A16E0, 0x6A1490));
		DefineAddress(GetString8, SelectAddress(0x6A1600, 0x6A13B0));
		DefineAddress(GetString16, SelectAddress(0x6A1650, 0x6A1400));

		DefineAddress(GetArrayBool, SelectAddress(0x6A09B0, 0x6A0760));
		DefineAddress(GetArrayInt32, SelectAddress(0x6A0A20, 0x6A07D0));
		DefineAddress(GetArrayUInt32, SelectAddress(0x6A0A90, 0x6A0840));
		DefineAddress(GetArrayFloat, SelectAddress(0x6A0B00, 0x6A08B0));
		DefineAddress(GetArrayVector2, SelectAddress(0x6A0B70, 0x6A0920));
		DefineAddress(GetArrayVector3, SelectAddress(0x6A0BE0, 0x6A0990));
		DefineAddress(GetArrayVector4, SelectAddress(0x6A0C50, 0x6A0A00));
		DefineAddress(GetArrayColorRGB, SelectAddress(0x6A0CC0, 0x6A0A70));
		DefineAddress(GetArrayKey, SelectAddress(0x6A0D30, 0x6A0AE0));
		DefineAddress(GetArrayString8, SelectAddress(0x6A0DA0, 0x6A0B50));
		DefineAddress(GetArrayString16, SelectAddress(0x6A0E10, 0x6A0BC0));
		DefineAddress(GetArrayTransform, SelectAddress(0x6A0E80, 0x6A0C30));

		DefineAddress(Clear, SelectAddress(0x93E0A0, 0x93DAF0));
	}

	namespace Addresses(PropertyList)
	{
		DefineAddress(SetProperty, SelectAddress(0x6A3070, 0x6A2E20));
		DefineAddress(RemoveProperty, SelectAddress(0x6A3140, 0x6A2EF0));
		DefineAddress(HasProperty, SelectAddress(0x6A26C0, 0x6A2470));
		DefineAddress(GetPropertyAlt, SelectAddress(0x6A2030, 0x6A1DE0));
		DefineAddress(GetProperty, SelectAddress(0x6A2780, 0x6A2530));
		DefineAddress(GetPropertyObject, SelectAddress(0x6A2720, 0x6A24D0));
		DefineAddress(CopyFrom, SelectAddress(0x6A2C90, 0x6A2A40));
		DefineAddress(AddPropertiesFrom, SelectAddress(0x6A3160, 0x6A2F10));
		DefineAddress(CopyAllPropertiesFrom, SelectAddress(0x6A1720, 0x6A14D0));
		DefineAddress(AddAllPropertiesFrom, SelectAddress(0x6A1760, 0x6A1510));
		DefineAddress(Read, SelectAddress(0x6A31B0, 0x6A2F60));
		DefineAddress(Write, SelectAddress(0x6A1790, 0x6A1540));
		DefineAddress(GetPropertyIDs, SelectAddress(0x6A32C0, 0x6A3070));
		DefineAddress(Clear, SelectAddress(0x6A2CD0, 0x6A2A80));

		DefineAddress(SetParent, SelectAddress(0x6A1960, 0x6A1710));
	}

	// We keed it for backwards compatibility
	namespace ScenarioMode_addresses
	{
		DefineAddress(ptr, SelectAddress(0x16CBD24, 0x16C7AA4));
	}

	namespace Addresses(cScenarioMode)
	{
		DefineAddress(ptr, SelectAddress(0x16CBD24, 0x16C7AA4));
	}

	namespace Addresses(Thumbnail_cImportExport)
	{
		DefineAddress(Get, SelectAddress(0x5F7750, 0x5F79C0));
		DefineAddress(GetFolderPath, SelectAddress(0x5F9140, 0x5F92C0));
		DefineAddress(FolderPathFromLocale, SelectAddress(0x5F9220, 0x5F93A0));
		DefineAddress(SavePNG, SelectAddress(0x5FA7E0, 0x5FA960));
		DefineAddress(ImportPNG, SelectAddress(0x5FC240, 0x5FC3C0));
	}

	namespace Addresses(cLocaleManager)
	{
		DefineAddress(Get, SelectAddress(0x67DF60, 0x67DE00));
	}

	namespace Addresses(AppData)
	{
		DefineAddress(GetPackageForSaveDirectory, SelectAddress(0x6B22C0, 0x6B1F20));
		DefineAddress(SetPackageForSaveDirectory, SelectAddress(0x6B3A90, 0x6B36F0));
	}

	namespace Addresses(cResourceKeyGenerator)
	{
		DefineAddress(Get, SelectAddress(0x67DF80, 0x67DE20));
	}

	namespace Addresses(cIDGenerator)
	{
		DefineAddress(Get, SelectAddress(0x67DF80, 0x67DE20));
	}

	namespace Addresses(IJobManager)
	{
		DefineAddress(Get, SelectAddress(0x68F980, 0x68F490));
	}

	namespace Addresses(cJob)
	{
		DefineAddress(AddRef, SelectAddress(0x68FE20, 0x68F910));
		DefineAddress(Release, SelectAddress(0x690540, 0x6900E0));
		DefineAddress(AddDependency, SelectAddress(0x6915D0, 0x691340));
		DefineAddress(AddWeakDependency, SelectAddress(0x691610, 0x691380));
		DefineAddress(Wait, SelectAddress(0x692900, 0x692670));
		DefineAddress(Cancel, SelectAddress(0x692650, 0x6923C0));
		DefineAddress(Resume, SelectAddress(0x690DD0, 0x690970));
		DefineAddress(Continuation, SelectAddress(0x68FE80, 0x68F9B0));
		DefineAddress(GetStatus, SelectAddress(0x68FE40, 0x68F930));
	}

	namespace Addresses(cCreatureModeStrategy)
	{
		DefineAddress(Get, SelectAddress(0xD37C40, 0xD38840));
		DefineAddress(ExecuteAction, SelectAddress(0xD38770, 0xD39360));
	}

	namespace Addresses(cCellModeStrategy)
	{
		DefineAddress(AddRef, SelectAddress(0x1098140, 0xDD3CA0));
		DefineAddress(Release, SelectAddress(0xE1CF40, 0x1154790));
		DefineAddress(func0Ch, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(Initialize, SelectAddress(0xE82280, 0xE81CF0));
		DefineAddress(Dispose, SelectAddress(0xE824C0, 0xE81F30));
		DefineAddress(OnEnter, SelectAddress(0xE55950, 0xE552F0));
		DefineAddress(OnExit, SelectAddress(0xE80190, 0xE7FC00));
		DefineAddress(func20h, SelectAddress(0xE515F0, 0xE50FE0));
		DefineAddress(OnKeyDown, SelectAddress(0xE81E80, 0xE818F0));
		DefineAddress(OnKeyUp, SelectAddress(0xE51600, 0xE50FF0));
		DefineAddress(OnMouseDown, SelectAddress(0xE6CDE0, 0xE6C860));
		DefineAddress(OnMouseUp, SelectAddress(0xE5C6F0, 0xE5C0F0));
		DefineAddress(OnMouseMove, SelectAddress(0xE51620, 0xE51010));
		DefineAddress(OnMouseWheel, SelectAddress(0xE7DBC0, 0xE7D660));
		DefineAddress(Update, SelectAddress(0xE80F10, 0xE80980));

		DefineAddress(HandleMessage, SelectAddress(0xE5CB90, 0xE62700));
	}

	namespace Addresses(cMouseCamera)
	{
		DefineAddress(Update, SelectAddress(0x7DAF30, 0x7DAAB0));
		DefineAddress(OnKeyDown, SelectAddress(0x7D9890, 0x7D9410));
		DefineAddress(OnMouseDown, SelectAddress(0x7DA110, 0x7D9C90));
		DefineAddress(OnMouseUp, SelectAddress(0x7F5AC0, 0x5A9C70));
		DefineAddress(OnMouseMove, SelectAddress(0x7DAD40, 0x7DA8C0));
		DefineAddress(OnMouseWheel, SelectAddress(0x7DAE50, 0x7DA9D0));
		DefineAddress(Initialize, SelectAddress(0x7D99A0, 0x7D9520));
		DefineAddress(func54h, SelectAddress(0x7D9970, 0x7D94F0));
		DefineAddress(HandleMessage, SelectAddress(0x7DA180, 0x7D9D00));
		DefineAddress(CalculateViewTransform, SelectAddress(0x7DAB30, 0x7DA6B0));
	}

	namespace Addresses(IAppSystem)
	{
		DefineAddress(Get, SelectAddress(0x67DE20, 0x67DCC0));
	}

	namespace Addresses(cAppSystem)
	{
		DefineAddress(Create, SelectAddress(0x7E8E10, 0x7E8A00));
		DefineAddress(SetUserDirNames, SelectAddress(0x7E98B0, 0x7E94A0));
		DefineAddress(PreInit, SelectAddress(0x7E9050, 0x7E8C40));
		DefineAddress(Init, SelectAddress(0x7E6C60, 0x7E6850));
		DefineAddress(InitPlugins, SelectAddress(0x7E97E0, 0x7E93D0));
		DefineAddress(Configure, SelectAddress(0x7E7840, 0x7E7430));
		DefineAddress(InitGraphics, SelectAddress(0x7EAF50, 0x7EAAE0));
		DefineAddress(PreShutdown, SelectAddress(0x7E6940, 0x7E6520));
		DefineAddress(Shutdown, SelectAddress(0x7E9930, 0x7E9520));
		DefineAddress(Pause, SelectAddress(0x7E6340, 0x7E5F20));
		DefineAddress(Unpause, SelectAddress(0x7E6350, 0x7E5F30));
		DefineAddress(IsPaused, SelectAddress(0x7E6360, 0x7E5F40));
		DefineAddress(SetTimeScale, SelectAddress(0x7E6370, 0x7E5F50));
		DefineAddress(SetFixedStepping, SelectAddress(0x7E6390, 0x7E5F70));
		DefineAddress(BoostBackgroundJobs, SelectAddress(0x7E6AA0, 0x7E6680));
		DefineAddress(IsBoostEnabled, SelectAddress(0x7E6B00, 0x7E66E0));
		DefineAddress(Demo, SelectAddress(0xB2FA20, 0x7E6120));
		DefineAddress(OpenURL, SelectAddress(0x7EA1E0, 0x7E9DD0));
		DefineAddress(func60h, SelectAddress(0x7E63A0, 0x7E5F80));
		DefineAddress(func64h, SelectAddress(0x7E63D0, 0x7E5FB0));
		DefineAddress(func68h, SelectAddress(0x7E6400, 0x7E5FE0));
		DefineAddress(HookWindows, SelectAddress(0x7E64A0, 0x7E6080));
		DefineAddress(UnhookWindows, SelectAddress(0x7E64F0, 0x7E60D0));
		DefineAddress(SetEffectCollectionIDs, SelectAddress(0x7E6520, 0x7E6100));
		DefineAddress(Update, SelectAddress(0x7EA290, 0x7E9E80));
		DefineAddress(func7Ch, SelectAddress(0x7E6540, 0x7E6130));
		DefineAddress(PostUpdate, SelectAddress(0x7E6550, 0x7E6140));
		DefineAddress(func84h, SelectAddress(0x7E6B20, 0x7E6700));
		DefineAddress(func88h, SelectAddress(0xA6C9F0, 0xA6C940));
	}

	namespace Addresses(cSporeApp)
	{
		DefineAddress(EAMain, SelectAddress(0xF48C10, 0xF48810));
		DefineAddress(Init, SelectAddress(0xF48230, 0xF47E90));
		DefineAddress(Run, SelectAddress(0xF47810, 0xF47420));
		DefineAddress(Shutdown, SelectAddress(0xF47950, 0xF475A0));
	}

	namespace Addresses(CommandLine)
	{
		DefineAddress(FindSwitch, SelectAddress(0x92B6C0, 0x92B570));
		DefineAddress(Get, SelectAddress(0x92B570, 0x92B420));
	}

	namespace Addresses(Canvas)
	{
		DefineAddress(Get, SelectAddress(0x67DE10, 0x67DCB0));
		DefineAddress(Init, SelectAddress(0x84A3F0, 0x849BF0));
		DefineAddress(Shutdown, SelectAddress(0x848900, 0x848100));
		DefineAddress(func0Ch, SelectAddress(0xA134D0, 0xA13540));
		DefineAddress(func10h, SelectAddress(0x848240, 0x847A40));
		DefineAddress(Update, SelectAddress(0x848290, 0x847A90));
		DefineAddress(Clear, SelectAddress(0x8482C0, 0x847AC0));
		DefineAddress(GetStyle, SelectAddress(0x985FB0, 0xFCC1D0));
		DefineAddress(SetStyle, SelectAddress(0x84A600, 0x849E00));
		DefineAddress(GetOptions, SelectAddress(0x923C40, 0x93B630));
		DefineAddress(SetOptions, SelectAddress(0x848310, 0x847B10));
		DefineAddress(GetCaption, SelectAddress(0x804E30, 0xFF3480));
		DefineAddress(SetCaption, SelectAddress(0x84A710, 0x849ED0));
		DefineAddress(GetPosition, SelectAddress(0x8489E0, 0x8481E0));
		DefineAddress(SetPosition, SelectAddress(0x848A00, 0x848200));
		DefineAddress(GetClientArea, SelectAddress(0x848A70, 0x848270));
		DefineAddress(SetClientArea, SelectAddress(0x8497B0, 0x848FB0));
		DefineAddress(IsActive, SelectAddress(0x848340, 0x847B40));
		DefineAddress(SetActive, SelectAddress(0x848360, 0x847B60));
		DefineAddress(IsVisible, SelectAddress(0x848380, 0x847B80));
		DefineAddress(SetVisible, SelectAddress(0x8483A0, 0x847BA0));
		DefineAddress(IsFullscreen, SelectAddress(0x69D4C0, 0xAB2FF0));
		DefineAddress(SetFullscreen, SelectAddress(0x8498C0, 0x8490C0));
		DefineAddress(IsMinimized, SelectAddress(0x8483C0, 0x847BC0));
		DefineAddress(IsMaximized, SelectAddress(0x8483E0, 0x847BE0));
		DefineAddress(GetMessageServer, SelectAddress(0xA36470, 0xC871D0));
		DefineAddress(SetMessageServer, SelectAddress(0xA168B0, 0xA169B0));
		DefineAddress(func6Ch, SelectAddress(0x8487A0, 0xB18CB0));
		DefineAddress(func70h, SelectAddress(0x8487B0, 0x847FA0));
		DefineAddress(HasSystemCursor, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(SetSystemCursorVisible, SelectAddress(0x8487D0, 0x847FC0));
		DefineAddress(func7Ch, SelectAddress(0x8487F0, 0x847FF0));
		DefineAddress(func80h, SelectAddress(0x848820, 0x848020));
		DefineAddress(Tick, SelectAddress(0x848AF0, 0x8482F0));
		DefineAddress(func88h, SelectAddress(0x84A890, 0x84A050));
		DefineAddress(func8Ch, SelectAddress(0x848400, 0x847C00));
		DefineAddress(func90h, SelectAddress(0x95FE80, 0x1030E20));
		DefineAddress(GetWindow, SelectAddress(0xF681A0, 0xF67D40));
		DefineAddress(GetCanvasClass, SelectAddress(0x848410, 0x847C10));
		DefineAddress(GetMonitor, SelectAddress(0x848420, 0x847C20));
	}

	namespace Addresses(cArithmeticaResource)
	{
		DefineAddress(Load, SelectAddress(0x7F2810, 0x7F2300));
		DefineAddress(ComputeFunction, SelectAddress(0x7F26A0, 0x7F2190));
		DefineAddress(ComputeAll, SelectAddress(0x7F2AD0, 0x7F25C0));
		DefineAddress(GetValue, SelectAddress(0x7F2B60, 0x7F2650));
		DefineAddress(SetValue, SelectAddress(0x7F2B90, 0x7F2680));
	}

	namespace Addresses(IConfigManager)
	{
		DefineAddress(Get, SelectAddress(0x67DE50, 0x67DCF0));
	}

	namespace Addresses(IStateManager) {
		DefineAddress(Get, SelectAddress(0x67DE40, 0x67DCE0));
	}
}

namespace Addresses(App)
{
	DefineAddress(sPreferencesPropList, SelectAddress(0x1601BA4, 0x15FD91C));
#ifdef SDK_TO_GHIDRA
	DefineAddress(sScenarioMode, SelectAddress(0x16CBD24, 0x16C7AA4));
	DefineAddress(sCreatureModeStrategy, SelectAddress(0x16A2514, 0x169E294));
#endif
}

#endif
