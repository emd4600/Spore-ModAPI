#pragma once

#include <Spore\App\CommandLine.h>
#include <Spore\App\PropertyList.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>
#include <EASTL\vector_map.h>

#define IConfigManagerPtr eastl::intrusive_ptr<App::IConfigManager>
#define ConfigManager (*App::IConfigManager::Get())

namespace App
{
	class IConfigManager
	{
	public:
		enum Messages
		{
			kMsgOptionApplied = 0xF62ADE
		};

		static IConfigManager* Get();

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~IConfigManager() = 0;
		/* 0Ch */	virtual bool Init(CommandLine* commandLine, bool) = 0;
		/* 10h */	virtual bool Shutdown() = 0;
		/* 14h */	virtual void Update() = 0;
		/* 18h */	virtual void SetScriptPath(const char* path) = 0;
		/* 1Ch */	virtual void SetScriptKey(uint32_t instanceID, uint32_t groupID) = 0;
		/* 20h */	virtual void SetInfoAlerts(bool) = 0;
		/* 24h */	virtual void SetErrorAlerts(bool) = 0;
		/* 28h */	virtual bool Configure() = 0;
		/* 2Ch */	virtual void SetOption(uint32_t optionID, int value) = 0;
		/* 30h */	virtual int GetOption(uint32_t optionID) = 0;
		/* 34h */	virtual int GetOptionDefault(uint32_t optionID) = 0;
		/* 38h */	virtual void GetOptionIDs(eastl::vector<uint32_t>& dst) = 0;
		/* 3Ch */	virtual bool SavePreferences() = 0;
		/* 40h */	virtual void ResetToDefaults() = 0;
		/* 44h */	virtual int GetNumScreenResolutions() = 0;
		/* 48h */	virtual bool GetScreenResolutionInfo(int optionIndex, int& dstScreenWidth, int& dstScreenHeight, int& dstRefreshRate) = 0;
		/* 4Ch */	virtual bool GetConfigString(int index, eastl::string& dst) = 0;
		/* 50h */	virtual void SaveOptionSetup(const char* path) = 0;
	};

	namespace Addresses(IConfigManager)
	{
		DeclareAddress(Get);  // 0x67DE50 0x67DCF0
	}

	class cConfigScriptState
	{
	public:
		struct cOption
		{
			/* 00h */	uint32_t mID;
			/* 04h */	int mDefaultValue;
			/* 08h */	int mValue;
			/* 0Ch */	eastl::fixed_vector<PropertyListPtr, 4> mPossibleValues;
			/* 34h */	eastl::fixed_vector<eastl::vector_map<uint32_t, PropertyListPtr>, 4> field_34;
		};
		ASSERT_SIZE(cOption, 0xAC);

		/* 00h */	uint32_t field_0;  // 0x21566AA
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	bool field_C;
		/* 0Dh */	bool field_D;
		/* 10h */	eastl::string field_10;
		/* 20h */	eastl::string field_20;
		/* 30h */	eastl::string field_30;
		/* 40h */	bool field_40;
		/* 41h */	bool field_41;
		/* 42h */	bool mInfoAlerts;
		/* 43h */	bool field_43;  // true
		/* 44h */	eastl::vector<cOption> mOptions;
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;
		/* 60h */	eastl::vector<eastl::string> mConfigStrings;
		/* 74h */	eastl::vector<int> field_74;
	};
	ASSERT_SIZE(cConfigScriptState, 0x88);

	class cConfigManager
		: public IConfigManager
		, public RefCountTemplate
	{
	public:
		/* 0Ch */	ObjectPtr mpFileParser;
		/* 10h */	ObjectPtr mpScriptParser;
		/* 14h */	ResourceKey mScriptKey;
		/* 20h */	cConfigScriptState mConfigScriptState;
		/* A8h */	int field_A8;  // -1
		/* ACh */	bool mIsSafeMode;
		/* ADh */	bool mShowConfigAlerts;
		/* B0h */	PropertyListPtr mpAppPropList;
	};
	ASSERT_SIZE(cConfigManager, 0xB4);

	/// Returns the preferences property list, which is stored in `AppData/Spore/Preferences/Preferences.prop`
	/// @returns
	PropertyList* GetPreferences();

#ifdef SDK_TO_GHIDRA
	PropertyList* sPreferencesPropList;
#endif
}

namespace Addresses(App)
{
	DeclareAddress(sPreferencesPropList);  // 0x1601BA4 0x15FD91C
}