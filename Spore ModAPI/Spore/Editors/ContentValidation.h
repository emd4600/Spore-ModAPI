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
		DeclareAddress(IllegalCharacters_ptr);
		DeclareAddress(ValidationEditableTests_ptr);
	}

	inline eastl::string16& ContentValidation::IllegalCharacters() {
		return *(eastl::string16*)GetAddress(ContentValidation, IllegalCharacters_ptr);
	}
	inline ContentValidation& ContentValidation::ValidationEditableTests() {
		return *(ContentValidation*)GetAddress(ContentValidation, ValidationEditableTests_ptr);
	}
}