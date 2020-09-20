#pragma once

#include <Spore\Resource\DatabasePackedFile.h>

namespace App
{
	namespace AppData
	{
		Resource::DBPF* GetPackageForSaveDirectory(uint32_t directoryID);

		void SetPackageForSaveDirectory(uint32_t directoryID, Resource::DBPF* pPackage, bool = false);
	}

	namespace Addresses(AppData)
	{
		DeclareAddress(GetPackageForSaveDirectory);
		DeclareAddress(SetPackageForSaveDirectory);
	}
}