#pragma once

namespace Editors
{
	class INameableEntity
	{
	public:
		/* 00h */	virtual void SetName(const char16_t* pString) = 0;
		/* 04h */	virtual const char16_t* GetName() = 0;

		/* 08h */	virtual void SetDescription(const char16_t* pString) = 0;
		/* 0Ch */	virtual const char16_t* GetDescription() = 0;

		/* 10h */	virtual void SetTags(const char16_t* pString) {};
		/* 14h */	virtual const char16_t* GetTags() {
			return nullptr;
		};
	};
}