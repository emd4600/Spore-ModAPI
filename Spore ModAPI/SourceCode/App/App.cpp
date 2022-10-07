#ifndef MODAPI_DLL_EXPORT
#include <Spore\App\Thumbnail_cImportExport.h>
#include <Spore\App\AppData.h>
#include <Spore\App\ResourceKeyGenerator.h>

namespace App
{
	auto_STATIC_METHOD_(Thumbnail_cImportExport, Thumbnail_cImportExport*, Get);

	auto_METHOD(Thumbnail_cImportExport, bool, GetFolderPath,
		Args(uint32_t creationType, string16& dst), Args(creationType, dst));

	auto_METHOD(Thumbnail_cImportExport, bool, FolderPathFromLocale,
		Args(uint32_t instanceID, string16& dst, uint32_t tableID), Args(instanceID, dst, tableID));

	auto_METHOD(Thumbnail_cImportExport, bool, SavePNG,
		Args(Resource::ResourceObject* pResource, RenderWare::Raster* pImage, Resource::DBPF* pDBPF,
			bool forceReplace, bool disableSteganography),
		Args(pResource, pImage, pDBPF, forceReplace, disableSteganography));


	auto_STATIC_METHOD(AppData, Resource::DBPF*, GetPackageForSaveDirectory, Args(uint32_t arg), Args(arg));
	auto_STATIC_METHOD_VOID(AppData, SetPackageForSaveDirectory, 
		Args(uint32_t arg, Resource::DBPF* package, bool b), Args(arg, package, b));


	auto_STATIC_METHOD_(cResourceKeyGenerator, cResourceKeyGenerator*, Get);
}
#endif