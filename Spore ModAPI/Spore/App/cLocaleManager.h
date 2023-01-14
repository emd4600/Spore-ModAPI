#pragma once

#include <Spore\App\cStringDetokenizer.h>
#include <Spore\Resource\ResourceObject.h>

#define LocaleManager (*App::cLocaleManager::Get())

namespace App
{
	class cLocaleManager
		: public DefaultRefCounted
	{
	public:
		/* 10h */	virtual bool SetLanguage(const eastl::string16& languageCode);
		/* 14h */	virtual const eastl::string16& GetActiveLanguage() const;
		/* 18h */	virtual bool SetLanguageByName(const eastl::string16& languageName);
		/* 1Ch */	virtual const char16_t* GetActiveLanguageName() const;
		/* 20h */	virtual cStringDetokenizer* GetStringDetokenizer();
		/* 24h */	virtual bool func24h(const ResourceKey& key, Resource::ResourceObject** ppDst) const;

		static cLocaleManager* Get();
	};

	namespace Addresses(cLocaleManager)
	{
		DeclareAddress(Get);
	}
}