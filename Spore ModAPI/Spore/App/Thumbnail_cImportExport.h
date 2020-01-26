#pragma once

#include <Spore\Internal.h>
#include <Spore\App\IMessageListener.h>
#include <EASTL\hash_map.h>
#include <EASTL\string.h>
namespace App
{
	/// A class related with the .PNG files of creations.
	///
	/// It can be used to get the path to the My Spore Creations folder:
	/// ~~~~~~~~{.cpp}
	/// string16 path;
	/// App::Thumbnail_cImportExport::Get()->GetFolderPath(TypeIDs::crt, path);
	/// // Now path is something like 'C:\Users\...\My Documents\My Spore Creations\Creatures'
	/// ~~~~~~~~
	class Thumbnail_cImportExport
		: public IUnmanagedMessageListener
	{
	public:
		/// Gets the filepath of the folder where the .PNGs of the creation type are stored.
		/// @param creationType One of the types in TypeIDs, such as 'crt', 'bld',...
		/// @param[out] dst The string where the path will be written.
		bool GetFolderPath(uint32_t creationType, string16& dst);

		static Thumbnail_cImportExport* Get();

		// Not finished yet, but it's no important
	private:
		/* 04h */	hash_map<int, int> field_04;
		/* 24h */	hash_map<int, int> field_24;
		/* 44h */	int field_44;  // not initialized
		/* 48h */	hash_map<int, int> field_48;
		/* 68h */	hash_map<int, int> field_68;
	};

	namespace Addresses(Thumbnail_cImportExport)
	{
		DeclareAddress(Get);
		DeclareAddress(GetFolderPath);
	}
}