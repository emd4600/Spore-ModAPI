#pragma once

#include <Spore\App\CommandLine.h>
#include <Spore\App\cAppSystem.h>
#include <Spore\App\IClassManager.h>
#include <Spore\UTFWin\IWindow.h>

namespace App
{
	class cSporeApp
		: public App::IUnmanagedMessageListener
		, public DefaultRefCounted
	{
	public:
		/// The main function executed on the game, creates the cSporeApp and runs Init(), Run(), and Shutdown().
		/// @param commandLine
		/// @returns
		static int EAMain(CommandLine* commandLine);

		bool Init(CommandLine* commandLine);
		/// The main game loop.
		void Run();
		bool Shutdown();

	public:
		/* 0Ch */	bool mHasInitialized;
		/* 0Dh */	bool mIsRunning;
		// These three are related with time
		/* 10h */	uint64_t field_10;
		/* 18h */	float field_18;
		/* 1Ch */	float field_1C;
		/* 20h */	IAppSystemPtr mpAppSystem;
		/* 24h */	IClassManager* mpClassManager;
		/* 28h */	IWindowPtr mpMainWindow;
		/* 2Ch */	int field_2C;
		/* 30h */	int mpMovieSystem;
		/* 34h */	int field_34;
		/* 38h */	int mpTerrainSystem;
		/* 3Ch */	int mpSimulatorSystem;
		/* 40h */	int mResult;
	};
	ASSERT_SIZE(cSporeApp, 0x48);

	namespace Addresses(cSporeApp)
	{
		DeclareAddress(EAMain);  // 0xF48C10 0xF48810
		DeclareAddress(Init);  // 0xF48230 0xF47E90
		DeclareAddress(Run);  // 0xF47810 0xF47420
		DeclareAddress(Shutdown);  // 0xF47950 0xF475A0
	}
}