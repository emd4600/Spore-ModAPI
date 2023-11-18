
#ifndef MODAPI_DLL_EXPORT
#include <Spore\App\Thumbnail_cImportExport.h>
#include <Spore\App\AppData.h>
#include <Spore\App\IDGenerator.h>
#include <Spore\App\cCreatureModeStrategy.h>
#include <Spore\App\cSporeApp.h>
#include <Spore\App\cArithmeticaResource.h>
#include <Spore\App\ConfigManager.h>
#include <Spore\App\IStateManager.h>
#endif
#include <Spore\App\CommandLine.h>

namespace App
{
#ifndef MODAPI_DLL_EXPORT
	auto_STATIC_METHOD_(Thumbnail_cImportExport, Thumbnail_cImportExport*, Get);

	auto_METHOD(Thumbnail_cImportExport, bool, GetFolderPath,
		Args(uint32_t creationType, eastl::string16& dst), Args(creationType, dst));

	auto_METHOD(Thumbnail_cImportExport, bool, FolderPathFromLocale,
		Args(uint32_t instanceID, eastl::string16& dst, uint32_t tableID), Args(instanceID, dst, tableID));

	auto_METHOD(Thumbnail_cImportExport, bool, SavePNG,
		Args(Resource::ResourceObject* pResource, RenderWare::Raster* pImage, Resource::Database* pDBPF,
			bool forceReplace, bool disableSteganography),
		Args(pResource, pImage, pDBPF, forceReplace, disableSteganography));

	auto_METHOD(Thumbnail_cImportExport, bool, ImportPNG,
		Args(const char16_t* path, ResourceKey& key), Args(path, key));


	auto_STATIC_METHOD_(cIDGenerator, cIDGenerator*, Get);

	auto_STATIC_METHOD_(cCreatureModeStrategy, cCreatureModeStrategy*, Get);

	auto_STATIC_METHOD_(IAppSystem, IAppSystem*, Get);

	auto_STATIC_METHOD(cSporeApp, int, EAMain, Args(CommandLine* commandLine), Args(commandLine));
	auto_STATIC_METHOD(cSporeApp, bool, Init, Args(CommandLine* commandLine), Args(commandLine));
	auto_STATIC_METHOD_VOID_(cSporeApp, Run);
	auto_STATIC_METHOD_(cSporeApp, bool, Shutdown);

	auto_STATIC_METHOD_(Canvas, Canvas*, Get);

	//// cArithmeticaResource ////

	auto_STATIC_METHOD(cArithmeticaResource, bool, Load,
		Args(uint32_t a, uint32_t b, cArithmeticaResource& c), Args(a, b, c));

	auto_METHOD_VOID(cArithmeticaResource, ComputeFunction, Args(const char* a), Args(a));

	auto_METHOD_VOID_(cArithmeticaResource, ComputeAll);

	auto_METHOD(cArithmeticaResource, float, GetValue, Args(const char* a), Args(a));

	auto_METHOD_VOID(cArithmeticaResource, SetValue, Args(const char* a, float b), Args(a, b));

	cArithmeticaResource::cArithmeticaResource()
		: CachedResourceObject()
		, mVariableNames()
		, mOperators()
		, mState()
		, mFunctions()
	{
	}

	cArithmeticaResource::~cArithmeticaResource()
	{
	}

	void cArithmeticaResource::func14h() {
	}

	//// ConfigManager ////

	auto_STATIC_METHOD_(IConfigManager, IConfigManager*, Get);

	PropertyList* GetPreferences()
	{
		return *(PropertyList**)GetAddress(App, sPreferencesPropList);
	}

	//// StateManager ////

	auto_STATIC_METHOD_(IStateManager, IStateManager*, Get);

#endif


	auto_METHOD(CommandLine, eastl::string16&, Get, Args(int i), Args(i));

	auto_METHOD(CommandLine, int, FindSwitch,
		Args(const char16_t* a1, bool a2, eastl::string16* a3, int a4),
		Args(a1, a2, a3, a4));

	CommandLine* GetAppCommandLine() {
		return *(CommandLine**)GetAddress(App, sAppCommandLine);
	}
}
