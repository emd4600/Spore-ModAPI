#pragma once

#include <Spore\Internal.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Resource\ResourceObject.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\RenderWare\Raster.h>
#include <EASTL\hash_map.h>
#include <EASTL\string.h>

#define ThumbnailImportExport (*App::Thumbnail_cImportExport::Get())

namespace App
{
	/// A class related with the .PNG files of creations.
	///
	/// It can be used to get the path to the My Spore Creations folder:
	/// ~~~~~~~~{.cpp}
	/// eastl::string16 path;
	/// ThumbnailImportExport.GetFolderPath(TypeIDs::crt, path);
	/// // Now path is something like 'C:\Users\...\My Documents\My Spore Creations\Creatures'
	/// ~~~~~~~~
	/// 
	/// You can also use it to save a Resource::ResourceObject into a `.png` with Thumbnail_cImportExport::SavePNG()
	class Thumbnail_cImportExport
		: public IUnmanagedMessageListener
	{
	public:
		/// Gets the filepath of the folder where the .PNGs of the creation type are stored.
		/// @param creationType One of the types in TypeIDs, such as 'crt', 'bld',...
		/// @param[out] dst The eastl::string where the path will be written.
		bool GetFolderPath(uint32_t creationType, eastl::string16& dst);

		/// Used to obtain a path from a locale file, by default `0x19F76D11.locale`, similar to the one that would
		/// return GetFolderPath()
		bool FolderPathFromLocale(uint32_t instanceID, eastl::string16& dst, uint32_t tableID = 0xFFFFFFFF);

		/// Encodes the given resource into a `.png` image and saves it, both in the given package and in the
		/// "My Spore Creations" in the user Documents folder. 
		/// 
		/// In the package, the image will be saved using the same ResourceKey as the resource, but with a TypeIDs::png type.
		/// The function expects a TypeIDs::pollen_metadata file to exist in that same folder, which will be used to write the 
		/// metadata (name, description, author, etc) of the creation.
		/// 
		/// @param pResource The resource object to encode inside the PNG. It will be encoded using the appropriate Resource::IResourceFactory
		/// @param pImage The raster that is written as the image
		/// @param pDBPF The DBPF taht contains the pollen metadata, and where the PNG will be saved
		/// @param forceReplace [Optional] If false (by default), if the `.png` already exists in the folder, it will try writing variants like `(1)`, `(2)`,...
		/// @param disableSteganography [Optional] If false (by default), the data in the `.png` will be stored in a special way meant to save space.
		/// @returns `true` on success, `false` if something failed.
		bool SavePNG(Resource::ResourceObject* pResource, RenderWare::Raster* pImage, Resource::DBPF* pDBPF, 
			bool forceReplace = false, bool disableSteganography = false);

		static Thumbnail_cImportExport* Get();

		// Not finished yet, but it's not important
	private:
		/* 04h */	eastl::hash_map<int, int> field_04;
		/* 24h */	eastl::hash_map<int, int> field_24;
		/* 44h */	int field_44;  // not initialized
		/* 48h */	eastl::hash_map<int, int> field_48;
		/* 68h */	eastl::hash_map<int, int> field_68;

		// other fields are eastl::string16 with the creation paths
	};

	namespace Addresses(Thumbnail_cImportExport)
	{
		DeclareAddress(Get);
		DeclareAddress(GetFolderPath);
		DeclareAddress(FolderPathFromLocale);
		DeclareAddress(SavePNG);
	}
}