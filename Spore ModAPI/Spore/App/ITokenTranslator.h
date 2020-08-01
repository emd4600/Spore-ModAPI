#pragma once

#include <Spore\Object.h>
#include <EASTL\string.h>

#define ITokenTranslatorPtr eastl::intrusive_ptr<App::ITokenTranslator>

namespace App
{
	class ITokenTranslator
		: public DefaultRefCounted
	{
	public:
		virtual bool TranslateToken(const char16_t* pToken, string16& dst) = 0;
		virtual void func14h(int) {};
	};
}