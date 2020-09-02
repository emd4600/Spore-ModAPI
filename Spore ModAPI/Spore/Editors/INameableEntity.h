#pragma once

namespace Editors
{
	class INameableEntity
	{
	public:
		virtual void SetName(const char16_t* pString) = 0;
		virtual const char16_t* GetName() = 0;

		virtual void SetDescription(const char16_t* pString) = 0;
		virtual const char16_t* GetDescription() = 0;

		virtual void SetTags(const char16_t* pString) {};
		virtual const char16_t* GetTags() {
			return nullptr;
		};
	};
}