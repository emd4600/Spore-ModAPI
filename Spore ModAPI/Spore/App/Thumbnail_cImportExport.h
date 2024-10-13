#pragma once

#include <Spore\Internal.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Resource\ResourceObject.h>
#include <Spore\Resource\Database.h>
#include <Spore\RenderWare\Raster.h>
#include <EASTL\hash_map.h>
#include <EASTL\hash_set.h>
#include <EASTL\string.h>

#define ThumbnailImportExport (*App::Thumbnail_cImportExport::Get())

namespace App
{
	struct ThumbnailDecodedMetadata
	{
		ThumbnailDecodedMetadata() = default;

		/* 00h */	int version;
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	uint64_t assetId;
		/* 18h */	uint64_t parentAssetId;
		/* 20h */	uint64_t timeCreated;
		/* 28h */	eastl::string16 authorName;
		/* 38h */	uint64_t authorId;
		/* 40h */	eastl::string16 name;
		/* 50h */	eastl::string16 description;
		/* 60h */	eastl::string16 tagsString;
		/* 70h */	eastl::vector<float> field_70;
		/* 84h */	int field_84;
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
	};
	ASSERT_SIZE(ThumbnailDecodedMetadata, 0x90);

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
		/// @param database The Database that contains the pollen metadata, and where the PNG will be saved
		/// @param forceReplace [Optional] If false (by default), if the `.png` already exists in the folder, it will try writing variants like `(1)`, `(2)`,...
		/// @param disableSteganography [Optional] If false (by default), the data in the `.png` will be stored in a special way meant to save space.
		/// @returns `true` on success, `false` if something failed.
		bool SavePNG(Resource::ResourceObject* pResource, RenderWare::Raster* pImage, Resource::Database* database, 
			bool forceReplace = false, bool disableSteganography = false);

		/// Reads the PNG file from the given file path, and adds the creation found within to the Sporepedia if it hasn't been added yet. 
		/// 
		/// @param path The full path to the file being read.
		/// @param key Resource key to the creation being read.
		/// @returns 'true' on success, 'false' if something failed.
		bool ImportPNG(const char16_t* path, ResourceKey& key);

		/// Extracts information from a PNG file. It extracts both the metadata, and the data encoded within the image.
		/// @param[out] dstMetadata 
		/// @param[out] dstDataStream
		/// @returns true on success, false if something failed
		bool DecodePNG(IO::IStream* stream, ThumbnailDecodedMetadata& dstMetadata, IStreamPtr& dstDataStream);

		/// Saves the file paths information that keeps track of which PNGs have been loaded.
		/// It saves it in file `0x473C3E6!0x473C3E6.0x473C3E6` of Resource::SaveAreaID::Server (`Pollination.package`)
		/// @returns true on success, false if something failed
		bool SaveFilePaths();

		static Thumbnail_cImportExport* Get();

	public:
		/* 04h */	eastl::hash_set<eastl::string16> mLoadedPNGs;
		/* 24h */	eastl::hash_map<ResourceKey, eastl::string16> mPNGPathMap;
		/* 44h */	int field_44;  // not initialized
		/* 48h */	eastl::hash_map<int, int> field_48;
		/* 68h */	eastl::hash_map<int, int> field_68;
		/* 88h */	char padding_88[0xF8 - 0x88];
		/* F8h */	int field_F8;
		/* FCh */	int field_FC;
		/* 100h */	int field_100;
		/* 104h */	eastl::string16 mCellsPath;
		/* 114h */	eastl::string16 mCreaturesPath;
		/* 124h */	eastl::string16 mBuildingsPath;
		/* 134h */	eastl::string16 mPlantsPath;
		/* 144h */	eastl::string16 mVehiclesPath;
		/* 154h */	eastl::string16 mUFOsPath;
		/* 164h */	eastl::string16 mCityMusicPath;
		/* 174h */	eastl::string16 mScenariosPath;
		/* 184h */	int field_184;
	};
	ASSERT_SIZE(Thumbnail_cImportExport, 0x188);

	namespace Addresses(Thumbnail_cImportExport)
	{
		DeclareAddress(Get);
		DeclareAddress(GetFolderPath);
		DeclareAddress(FolderPathFromLocale);
		DeclareAddress(SavePNG);
		DeclareAddress(ImportPNG);
		DeclareAddress(DecodePNG);  // 0x5FBA10 0x5FBB90
		DeclareAddress(SaveFilePaths);  // 0x5F89C0 0x5F8B60
	}
}