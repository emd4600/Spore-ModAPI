#ifndef MODAPI_DLL_EXPORT
#include <Spore\App\Thumbnail_cImportExport.h>

namespace App
{
	auto_STATIC_METHOD_(Thumbnail_cImportExport, Thumbnail_cImportExport*, Get);

	auto_METHOD(Thumbnail_cImportExport, bool, GetFolderPath,
		Args(uint32_t creationType, string16& dst), Args(creationType, dst));
}
#endif