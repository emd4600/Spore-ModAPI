#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\App\CommandLine.h>
#include <Spore\App\Canvas.h>
#include <Spore\App\PropertyList.h>
#include <Spore\Object.h>
#include <EASTL\string.h>

#define AppSystem (*App::IAppSystem::Get())
#define IAppSystemPtr eastl::intrusive_ptr<App::IAppSystem>

namespace App
{
	class IAppSystem
	{
	public:
		/// Only available after IAppSystem::Init()
		static IAppSystem* Get();

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~IAppSystem() = 0;
		/* 0Ch */	virtual void SetUserDirNames(const char16_t* mySporeCreationsFolderName, const char16_t* appDataSporeFolderName) = 0;
		/* 10h */	virtual bool PreInit(CommandLine* commandLine, const char16_t* ddfListPath) = 0;
		/* 14h */	virtual bool Init(CommandLine* commandLine) = 0;
		/* 18h */	virtual bool InitPlugins(CommandLine* commandLine) = 0;
		/* 1Ch */	virtual bool Configure(CommandLine* commandLine) = 0;
		/* 20h */	virtual bool InitGraphics(CommandLine* commandLine) = 0;
		/* 24h */	virtual bool PreShutdown() = 0;
		/* 28h */	virtual bool Shutdown() = 0;
		/* 2Ch */	virtual int Pause() = 0;
		/* 30h */	virtual int Unpause() = 0;
		/* 34h */	virtual bool IsPaused() = 0;
		/* 38h */	virtual void SetTimeScale(float scale) = 0;
		/* 3Ch */	virtual void SetFixedStepping(int) = 0;
		/* 40h */	virtual void BoostBackgroundJobs(bool) = 0;
		/* 44h */	virtual bool IsBoostEnabled() = 0;
		/// Does nothing
		/* 48h */	virtual int GetPerfWarnings() = 0;
		/* 4Ch */	virtual bool Demo() = 0;
		/// Does nothing
		/* 50h */	virtual bool func50h() = 0;
		/// Does nothing
		/* 54h */	virtual bool func54h() = 0;
		/// Does nothing
		/* 58h */	virtual bool func58h() = 0;
		/* 5Ch */	virtual void OpenURL(const char16_t*) = 0;
		/* 60h */	virtual void func60h() = 0;  // DeactivateApp() ?
		/* 64h */	virtual void func64h() = 0;  // ToggleFullscreen() ?
		/* 68h */	virtual void func68h() = 0;  // ToggleDisplay() ?
		/* 6Ch */	virtual void HookWindows() = 0;
		/* 70h */	virtual void UnhookWindows() = 0;
		/* 74h */	virtual void SetEffectCollectionIDs(uint32_t* instanceIDs, uint32_t* groupIDs) = 0;
		/* 78h */	virtual void Update(int deltaTimeMS) = 0;
		/* 7Ch */	virtual void func7Ch() = 0;
		/* 80h */	virtual void PostUpdate() = 0;
		/* 84h */	virtual void func84h(int) = 0;
		/* 88h */	virtual int func88h() = 0;
		/// Does nothing
		/* 8Ch */	virtual void func8Ch() = 0;
	};

	class cAppSystem
		: public IAppSystem
		, public App::IMessageListener
		, public RefCountTemplate
	{
	public:
		static cAppSystem* Create();

		virtual void SetUserDirNames(const char16_t* mySporeCreationsFolderName, const char16_t* appDataSporeFolderName) override;
		virtual bool PreInit(CommandLine* commandLine, const char16_t* ddfListPath) override;
		virtual bool Init(CommandLine* commandLine) override;
		virtual bool InitPlugins(CommandLine* commandLine) override;
		virtual bool Configure(CommandLine* commandLine) override;
		virtual bool InitGraphics(CommandLine* commandLine) override;
		virtual bool PreShutdown() override;
		virtual bool Shutdown() override;
		virtual int Pause() override;
		virtual int Unpause() override;
		virtual bool IsPaused() override;
		virtual void SetTimeScale(float scale) override;
		virtual void SetFixedStepping(int) override;
		virtual void BoostBackgroundJobs(bool) override;
		virtual bool IsBoostEnabled() override;
		virtual int GetPerfWarnings() override;
		virtual bool Demo() override;
		virtual void OpenURL(const char16_t*) override;
		virtual void func60h() override;  // DeactivateApp() ?
		virtual void func64h() override;  // ToggleFullscreen() ?
		virtual void func68h() override;  // ToggleDisplay() ?
		virtual void HookWindows() override;
		virtual void UnhookWindows() override;
		virtual void SetEffectCollectionIDs(uint32_t* instanceIDs, uint32_t* groupIDs) override;
		virtual void Update(int deltaTimeMS) override;
		virtual void func7Ch() override;
		virtual void PostUpdate() override;
		virtual void func84h(int) override;
		virtual int func88h() override;

	public:
		/* 10h */	Canvas* mpCanvas;
		// 1Ch is cResourceManager, 24h is cLocaleManager, 28h is cResourceKeyGenerator, 3Ch is IConfigManager, 40h is cJobManager, CCh is PropertyListPtr mpPreferencesPropList
		/* 14h */	char padding_14[0x124];
		/* 138h */	eastl::string16 mMySporeCreationsFolderName;
		/* 148h */	eastl::string16 mAppDataSporeFolderName;
		// 164h is time scale
		/* 158h */	char padding_158[0x1F0 - 0x158];
	};
	ASSERT_SIZE(cAppSystem, 0x1F0);

	namespace Addresses(IAppSystem)
	{
		DeclareAddress(Get);  // 0x67DE20 0x67DCC0
	}

	namespace Addresses(cAppSystem)
	{
		DeclareAddress(Create);  // 0x7E8E10 0x7E8A00
		DeclareAddress(SetUserDirNames);  // 0x7E98B0 0x7E94A0
		DeclareAddress(PreInit);  // 0x7E9050 0x7E8C40
		DeclareAddress(Init);  // 0x7E6C60 0x7E6850
		DeclareAddress(InitPlugins);  // 0x7E97E0 0x7E93D0
		DeclareAddress(Configure);  // 0x7E7840 0x7E7430
		DeclareAddress(InitGraphics);  // 0x7EAF50 0x7EAAE0
		DeclareAddress(PreShutdown);  // 0x7E6940 0x7E6520
		DeclareAddress(Shutdown);  // 0x7E9930 0x7E9520
		DeclareAddress(Pause);  // 0x7E6340 0x7E5F20
		DeclareAddress(Unpause);  // 0x7E6350 0x7E5F30
		DeclareAddress(IsPaused);  // 0x7E6360 0x7E5F40
		DeclareAddress(SetTimeScale);  // 0x7E6370 0x7E5F50
		DeclareAddress(SetFixedStepping);  // 0x7E6390 0x7E5F70
		DeclareAddress(BoostBackgroundJobs);  // 0x7E6AA0 0x7E6680
		DeclareAddress(IsBoostEnabled);  // 0x7E6B00 0x7E66E0
		DeclareAddress(Demo);  // 0xB2FA20 0x7E6120
		DeclareAddress(OpenURL);  // 0x7EA1E0 0x7E9DD0
		DeclareAddress(func60h);  // 0x7E63A0 0x7E5F80
		DeclareAddress(func64h);  // 0x7E63D0 0x7E5FB0
		DeclareAddress(func68h);  // 0x7E6400 0x7E5FE0
		DeclareAddress(HookWindows);  // 0x7E64A0 0x7E6080
		DeclareAddress(UnhookWindows);  // 0x7E64F0 0x7E60D0
		DeclareAddress(SetEffectCollectionIDs);  // 0x7E6520 0x7E6100
		DeclareAddress(Update);  // 0x7EA290 0x7E9E80
		DeclareAddress(func7Ch);  // 0x7E6540 0x7E6130
		DeclareAddress(PostUpdate);  // 0x7E6550 0x7E6140
		DeclareAddress(func84h);  // 0x7E6B20 0x7E6700
		DeclareAddress(func88h);  // 0xA6C9F0 0xA6C940
	}
}
