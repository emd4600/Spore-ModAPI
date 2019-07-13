#pragma once

#include <cstdint>
#include <Spore\Internal.h>
#include <EASTL\string.h>

namespace Editors
{
	struct ContentValidation {
		int32_t flags[4];

		static eastl::string16& IllegalCharacters();
		static ContentValidation& ValidationEditableTests();
	};

	namespace Addresses(ContentValidation) {
		DeclareAddress(IllegalCharacters_ptr, SelectAddress(0x15DEA54, , 0x15DA7C4));
		DeclareAddress(ValidationEditableTests_ptr, SelectAddress(0x15DEA04, , 0x15DA7D4));
	}

	inline eastl::string16& ContentValidation::IllegalCharacters() {
		return *(eastl::string16*)GetAddress(ContentValidation, IllegalCharacters_ptr);
	}
	inline ContentValidation& ContentValidation::ValidationEditableTests() {
		return *(ContentValidation*)GetAddress(ContentValidation, ValidationEditableTests_ptr);
	}
}