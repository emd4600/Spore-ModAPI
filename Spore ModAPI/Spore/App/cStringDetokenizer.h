#pragma once

#include <Spore\App\ITokenTranslator.h>
#include <Spore\LocalizedString.h>
#include <EASTL\vector.h>

namespace App
{
	/// The class responsible for translating text tokens, which are special characters in locale files.
	/// In locale files, tokens are surrounded with `~` characters, and get replaced in-game with a text
	/// provided by an App::ITokenTranslator class.
	class cStringDetokenizer
		: public ITokenTranslator
	{
	public:
		/* 18h */	virtual void func18h();
		/* 1Ch */	virtual void AddTranslator(ITokenTranslator* pTranslator);
		/* 20h */	virtual void RemoveTranslator(ITokenTranslator* pTranslator);
		/* 24h */	virtual bool HasTokens(const char16_t* pStr) const;
		/* 28h */	virtual bool func28h(int, string16& dst);
		/* 2Ch */	virtual bool ProcessString(const char16_t* pStr, string16& dst);
		/* 30h */	virtual bool func30h(LocalizedString*, 
			pair<uint32_t, string16>* pTokensBegin, pair<uint32_t, string16>* pTokensEnd);
		/* 34h */	virtual void func34h(const char16_t* pStr, int index);
		/* 38h */	virtual bool ProcessStringEx(const char16_t* pStr, string16& dst,
			pair<uint32_t, string16>* pTokensBegin = nullptr, pair<uint32_t, string16>* pTokensEnd = nullptr);
		/* 3Ch */	virtual bool FindTokenTranslation(const char16_t* pToken, string16& dst) const;

	protected:
		/* 08h */	vector<ITokenTranslatorPtr> mTranslators;
		/* 1Ch */	string16 field_1C[4];
	};
	ASSERT_SIZE(cStringDetokenizer, 0x5C);
}