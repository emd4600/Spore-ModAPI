#pragma once

#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\intrusive_ptr.h>

#define FileDropMessagePtr eastl::intrusive_ptr<App::FileDropMessage>

namespace App
{
	class FileDropMessage
	{
	public:
		static const uint32_t ID = 0x24CE123;

		virtual ~FileDropMessage() = 0;
		virtual int AddRef() = 0;
		virtual int Release() = 0;

	public:
		/* 04h */	eastl::vector<eastl::string16> files;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
	};
}