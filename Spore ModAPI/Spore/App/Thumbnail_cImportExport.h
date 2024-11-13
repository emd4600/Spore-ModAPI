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
	struct PngEncoder {

		bool EncodePNG(IO::IStream* outputStream, int mode);

		/* 00h */	eastl::vector<int> field_0;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;  // not initialized
		/* 20h */	bool field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;  // -1
		/* 2Ch */	int field_2C;  // -1
		/* 30h */	int field_30;
		/* 34h */	int field_34;
		/* 38h */	int field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;  // 8
		/* 50h */	int field_50;
		/* 54h */	bool field_54;  // not initialized
		/* 55h */	bool field_55;
		/* 56h */	bool field_56;
		/* 58h */	eastl::vector<int8_t> mData;
		/* 6Ch */	int field_6C;
	};
	ASSERT_SIZE(PngEncoder, 0x70);

	struct ThumbnailDecodedMetadata
	{
		ThumbnailDecodedMetadata() = default;

		/* 00h */	int version;
		/* 04h */	uint32_t typeId;
		/* 08h */	uint32_t groupId;
		/* 10h */	uint64_t assetId;
		/* 18h */	uint64_t parentAssetId;
		/* 20h */	uint64_t timeCreated;
		/* 28h */	eastl::string16 authorName;
		/* 38h */	uint64_t authorId;
		/* 40h */	eastl::string16 name;
		/* 50h */	eastl::string16 description;
		/* 60h */	eastl::string16 tagsString;
		/* 70h */	eastl::vector<float> field_70;
		/* 84h */	uint32_t machineId;
		/* 88h */	uint32_t groupId2;
		/* 8Ch */	uint32_t instanceId;
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
		/// The path will end in a slash '/'
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

		/// Scans a disk directory, and tries to imports all PNG creations found there that were not already in the system.
		/// For each file path, it will check if it is aloready in mPngPathToKey (lowercase); if it isn't, it will
		/// call ImportPNG() on it, and add its entry to mPngPathToKey and mKeyToPngPath
		/// It uses `dstCount` to keep track of how many files have been loaded; it loads a maximum of 500
		/// @param directoryPath The path of the directory to scan
		/// @param[out] dstSkippedPaths A list of paths that were skipped because they were already in mPngPathToKey or too many files were loaded
		/// @param[out] dstCount The number of PNGs that were imported is added to this value
		/// @returns True if some PNG was loaded, false otherwise
		bool ImportDirectoryPNGs(const eastl::string16& directoryPath, eastl::hash_set<eastl::string16>& dstSkippedPaths, int& dstCount);

		static Thumbnail_cImportExport* Get();

	public:
		/// lowercase
		/* 04h */	eastl::hash_map<eastl::string16, ResourceKey> mPngPathToKey;
		/* 24h */	eastl::hash_map<ResourceKey, eastl::string16> mKeyToPngPath;
		/* 44h */	uint32_t mMachineId;  // not initialized
		/* 48h */	eastl::hash_map<int, int> field_48;
		/* 68h */	eastl::hash_map<int, int> field_68;
		/* 88h */	PngEncoder mPngEncoder;
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
		DeclareAddress(ImportDirectoryPNGs);  // 0x5FC900 0x5FCA80
	}

	namespace Addresses(PngEncoder)
	{
		DeclareAddress(EncodePNG);  // 0x68E660 0x68e190
	}
}