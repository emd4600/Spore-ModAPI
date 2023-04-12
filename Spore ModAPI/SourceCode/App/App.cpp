#ifndef MODAPI_DLL_EXPORT
#include <Spore\App\Thumbnail_cImportExport.h>
#include <Spore\App\AppData.h>
#include <Spore\App\IDGenerator.h>
#include <Spore\App\cCreatureModeStrategy.h>

namespace App
{
	auto_STATIC_METHOD_(Thumbnail_cImportExport, Thumbnail_cImportExport*, Get);

	auto_METHOD(Thumbnail_cImportExport, bool, GetFolderPath,
		Args(uint32_t creationType, eastl::string16& dst), Args(creationType, dst));

	auto_METHOD(Thumbnail_cImportExport, bool, FolderPathFromLocale,
		Args(uint32_t instanceID, eastl::string16& dst, uint32_t tableID), Args(instanceID, dst, tableID));

	auto_METHOD(Thumbnail_cImportExport, bool, SavePNG,
		Args(Resource::ResourceObject* pResource, RenderWare::Raster* pImage, Resource::Database* pDBPF,
			bool forceReplace, bool disableSteganography),
		Args(pResource, pImage, pDBPF, forceReplace, disableSteganography));



	auto_STATIC_METHOD_(cIDGenerator, cIDGenerator*, Get);

	auto_STATIC_METHOD_(cCreatureModeStrategy, cCreatureModeStrategy*, Get);
}
#endif