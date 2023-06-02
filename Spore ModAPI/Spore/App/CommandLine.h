#pragma once

#include <Spore\Internal.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>

namespace App
{
	class CommandLine
	{
	public:
		virtual ~CommandLine();

		eastl::string16& Get(int index);

		int FindSwitch(const char16_t* name, bool caseSensitive = false, eastl::string16* dst = nullptr, int firstIndex = 0);

		/// All the separated arguments of the command line, including the program name
		/* 04h */	eastl::vector<eastl::string16> mSplits;
		/* 18h */	eastl::string16 field_18;
		/* 28h */	eastl::string16 field_28;
	};
	ASSERT_SIZE(CommandLine, 0x38);

	namespace Addresses(CommandLine)
	{
		DeclareAddress(FindSwitch);  // 0x92B6C0 0x92B570
		DeclareAddress(Get);  // 0x92B570 0x92B420
	}

	/// Returns the command line that was used to execute this app.
	/// Only available after the start of cAppSystem::PreInit().
	/// @returns
	CommandLine* GetAppCommandLine();
}

namespace Addresses(App)
{
	DeclareAddress(sAppCommandLine);  // 0x1601BA8 0x15FD920
}