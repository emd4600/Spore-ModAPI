#pragma once

#include <Spore\Internal.h>
#include <Spore\Resource\Database.h>
#include <Spore\Resource\DatabaseDirectoryFiles.h>
#include <Spore\Resource\ResourceObject.h>
#include <EASTL\string.h>

namespace Resource
{
	enum class PathID : uint32_t
	{
		/// Core Spore - Data
		Data = 0xa02149,
		/// Spore Galactic Adventures - SporebinEP1
		App = 0xa0214a,
		Debug = 0xa02150,
		/// Core Spore - Data/Locale
		Locale = 0x45962CC,
		/// Spore Galactic Adventures - Data/Config
		Config = 0xA0214F,
		/// My Spore Creations
		Creations = 0xA0214B,
		/// %APPDATA%/Spore
		AppData = 0xA02151,
		BaseData = 0x6CBED39,
		BaseDataLocale = 0x6CBED3A,
		/// %APPDATA%/Spore/Temp
		Temp = 0x60BA02F,
	};

	enum class SaveAreaID : uint32_t
	{
		/// My Spore Creations/Pictures
		Pictures = 0x11AC196,
		/// My Spore Creations/Movies
		Movies = 0x11AC197,
		/// My Spore Creations/AnimatedAvatars
		Animations = 0x11AC198,
		/// %APPDATA%/Spore/Games/Game0
		GamesGame0 = 0x4729A47,
		/// %APPDATA%/Spore/Preferences
		Preferences = 0x11AC192,
		/// %APPDATA%/Spore/EditorSaves.package
		Creatures = 0x11AC199,
		/// %APPDATA%/Spore/EditorSaves.package
		Buildings = 0x11AC19A,
		/// %APPDATA%/Spore/EditorSaves.package
		Vehicles = 0x11AC19B,
		/// %APPDATA%/Spore/EditorSaves.package
		Cells = 0x90368EA3,
		/// %APPDATA%/Spore/EditorSaves.package
		UFOs = 0x90368EA2,
		/// %APPDATA%/Spore/EditorSaves.package
		Plants = 0x90368EA0,
		/// %APPDATA%/Spore/EditorSaves.package
		Adventures = 0x86CA01C9,
		/// %APPDATA%/Spore/CityMusic
		CityMusic = 0x500EFC6,
		/// %APPDATA%/Spore/Pollination.package
		Cache = 0x11AC19C,
		/// %APPDATA%/Spore/Pollination.package
		Server = 0x11AC19D,
		/// %APPDATA%/Spore/Planets.package
		Planets = 0x31389B5,
		/// %APPDATA%/Spore/RigblockInfo.package
		RigblockInfo = 0x49A3D83,
		/// %APPDATA%/Spore/GraphicsCache.package
		GraphicsCache = 0x11AC1AC,
	};

	namespace Paths
	{
		const char16_t* GetDirFromID(PathID dirID);

		bool GetDirectory(PathID dirID, eastl::string16& dst);

		void RegisterDirectory(PathID dirID, const char16_t* path);

		/// Creates an empty temporary file.
		/// @param[out] dstPath Buffer where the destination path will be written.
		/// @param folderPath [Optional] Directory where the file is created, by default it uses the system temporary folder.
		/// @param filePrefix [Optional] Prefix for the name of the file, "temp" by default.
		/// @param fileExtension [Optional] Extension of the file, ".tmp" by default.
		/// @returns The length of the path that has been written to the `dstPath` buffer.
		int CreateTempFile(char16_t* dstPath, char16_t* folderPath = nullptr, char16_t* filePrefix = nullptr, char16_t* fileExtension = nullptr);

		/// Returns the path to the game's data directory. Typically, this is the Data folder in the directory where Core Spore is installed.
		const char16_t* GetDataDir();
		/// Returns the path to the game's app directory. Typically, this is the SporebinEP1 folder, containing SporeApp.exe, in the directory where Spore Galactic Adventures is installed.
		const char16_t* GetAppDir();
		/// Appears to return null. There may be specific circumstances where this returns a valid path to a directory.
		const char16_t* GetDebugDir();

		/// Returns the database being used to save data of a certain kind.
		/// A database can either be a `.package` file (DatabasePackedFile) or a plain folder.
		/// Generally, `EditorSaves.package` is returned for SaveAreaID::Creatures, SaveAreaID::Buildings,
		/// SaveAreaID::Vehicles, SaveAreaID::Cells, SaveAreaID::UFOs, SaveAreaID::Plants, SaveAreaID::Adventures
		/// @param areaID
		/// @returns
		Database* GetSaveArea(SaveAreaID areaID);

		/// Registers a database to be used to save specific types of data, such as saved games, creations, etc.
		/// @param areaID
		/// @param pDatabase
		/// @param unk
		void RegisterSaveArea(SaveAreaID areaID, Resource::Database* pDatabase, void* unk = nullptr);

		/// Creates a DatabaseDirectoryFiles database for use as a save area.
		/// The database path will be the one obtained through `basePath` plus `folderName`.
		/// @param basePath
		/// @param folderName
		/// @param[out] dst
		/// @param saveArea
		/// @returns True if the operation succeeded
		bool CreateSaveAreaDirectoryDatabase(PathID basePath, const char16_t* folderName, DatabaseDirectoryFilesPtr& dst, SaveAreaID saveArea);
	}

	namespace Addresses(Paths)
	{
		DeclareAddress(GetDirFromID);  // 0x6888A0 0x688650
		DeclareAddress(GetDirectory);  // 0x688A20 0x6887D0
		DeclareAddress(RegisterDirectory);  // 0x688DF0 0x688BA0
		DeclareAddress(GetSaveArea);
		DeclareAddress(RegisterSaveArea);
		DeclareAddress(CreateTempFile);  // 0x932AC0 0x932550
		DeclareAddress(CreateSaveAreaDirectoryDatabase);  // 0x6B2950 0x6B25B0
	}

	bool SaveNamedResource(ResourceObject* resource, const char16_t* fileName, Database* database);
}

namespace Addresses(Resource)
{
	DeclareAddress(SaveNamedResource);  // 0x6B4340 0x6B3FA0
}
