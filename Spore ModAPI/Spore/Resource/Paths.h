#pragma once

#include <Spore\Internal.h>
#include <Spore\Resource\Database.h>
#include <EASTL\string.h>

namespace Resource
{
	enum class PathID : uint32_t
	{
		Data = 0xa02149,
		App = 0xa0214a,
		Debug = 0xa02150,
		Locale = 0x45962CC,
		Config = 0xA0214F,
		Creations = 0xA0214B,
		AppData = 0xA02151,
		BaseData = 0x6CBED39,
		BaseDataLocale = 0x6CBED3A,
		Temp = 0x60BA02F,
	};

	enum class SaveAreaID : uint32_t
	{
		Pictures = 0x11AC196,
		Movies = 0x11AC197,
		Animations = 0x11AC198,
		GamesGame0 = 0x4729A47,
		Preferences = 0x11AC192,
		Creatures = 0x11AC199,
		Buildings = 0x11AC19A,
		Vehicles = 0x11AC19B,
		Cells = 0x90368EA3,
		UFOs = 0x90368EA2,
		Plants = 0x90368EA0,
		Adventures = 0x86CA01C9,
		CityMusic = 0x500EFC6,
		Cache = 0x11AC19C,
		Server = 0x11AC19D,
		Planets = 0x31389B5,
		RigblockInfo = 0x49A3D83,
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

		const char16_t* GetDataDir();
		const char16_t* GetAppDir();
		const char16_t* GetDebugDir();

		/// Returns the database being used to save data of a certain kind.
		/// A database can either be a `.package` file (DatabasePackedFile) or a plain folder.
		/// Generally, `EditorSaves.package` is returned for SaveAreaID::Creatures, SaveAreaID::Buildings,
		/// SaveAreaID::Vehicles, SaveAreaID::Cells, SaveAreaID::UFOs, SaveAreaID::Plants, SaveAreaID::Adventures
		/// @param areaID
		/// @returns
		Database* GetSaveArea(SaveAreaID areaID);

		void RegisterSaveArea(SaveAreaID areaID, Resource::Database* pDatabase, void* = nullptr);
	}

	namespace Addresses(Paths)
	{
		DeclareAddress(GetDirFromID);  // 0x6888A0 0x688650
		DeclareAddress(GetDirectory);  // 0x688A20 0x6887D0
		DeclareAddress(RegisterDirectory);  // 0x688DF0 0x688BA0
		DeclareAddress(GetSaveArea);
		DeclareAddress(RegisterSaveArea);
		DeclareAddress(CreateTempFile);  // 0x932AC0 0x932550
	}
}