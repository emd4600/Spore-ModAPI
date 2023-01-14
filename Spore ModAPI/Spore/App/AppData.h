#pragma once

#include <Spore\Resource\DatabasePackedFile.h>

namespace App
{
	// kept here for backwards compatibility
	namespace Addresses(AppData)
	{
		DeclareAddress(GetPackageForSaveDirectory);
		DeclareAddress(SetPackageForSaveDirectory);
	}
}