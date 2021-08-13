#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include "SpaceToolIconOverride.h"
#include <Spore\CommonIDs.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\ImageDrawable.h>
#include <Spore/App/ICheatManager.h>

// Keys already found in ufotools~ folder
const uint32_t kIllegalIconIDs[] = {
	0x0376BCCB, 0x0413CDCC, 0x0693541D, 0x093E2784, 0x09408000, 0x0B253979,
	0x0B634E74, 0x0BBF8B7F, 0x0E46B215, 0x0E46B216, 0x0E46B217, 0x13303157,
	0x1585FFDA, 0x16405742, 0x166EF53B, 0x17C14197, 0x193DF54C, 0x193DF54D,
	0x193DF54E, 0x1D4969C4, 0x1DB66826, 0x1FE4D405, 0x24BB5AFA, 0x27375339,
	0x316D79BE, 0x31E8CD4B, 0x33A79E9E, 0x3827A7DD, 0x3AAD7A25, 0x3AD6E6DE,
	0x425E08A8, 0x43C721AB, 0x470F6AFF, 0x49546DC7, 0x4A9165C1, 0x4AD21FAC,
	0x4C9E121B, 0x4CB7785A, 0x4EAC24E0, 0x4FA02F92, 0x4FB5974E, 0x50F605A9,
	0x5305735C, 0x555AAE55, 0x55BD6B48, 0x5A5B9CF4, 0x5B617A60, 0x5B682F89,
	0x5B682F8A, 0x5B682F8B, 0x5CEF21ED, 0x5EA00CC5, 0x5FB05326, 0x61DD37F7,
	0x66E86527, 0x699E2CD3, 0x6A84358D, 0x6C5F78FF, 0x6EC30DFC, 0x71B594FE,
	0x746F294F, 0x75844E51, 0x777B4B4B, 0x7D7B9F2E, 0x80C291EC, 0x813F6FE0,
	0x818C1D26, 0x826502EA, 0x826502EB, 0x826502EC, 0x826502ED, 0x826502EF,
	0x8347BDAA, 0x8397B3E5, 0x85F72315, 0x88192C2B, 0x8841A300, 0x8841A301,
	0x8841A304, 0x8841A306, 0x8841A307, 0x89824FB1, 0x8AC8A228, 0x8AC8A22A,
	0x8AC8A22B, 0x8AC8A22D, 0x8AF687AB, 0x8D9C0D48, 0x91764839, 0x98ADACAB,
	0x9E323298, 0x9E323299, 0x9E32329A, 0xA4567740, 0xA690DC79, 0xAEB8DDC0,
	0xB3413E4D, 0xB4C8CF26, 0xB862B6A2, 0xB88BAE81, 0xB88BAE82, 0xB88BAE83,
	0xB9FB9DB4, 0xC19CCD88, 0xC58C1950, 0xC77D4838, 0xCB2CF8E8, 0xCF8FA5E3,
	0xD2F186F7, 0xD4050F90, 0xD4055DBD, 0xD4055DBF, 0xD5F08274, 0xD5F08276,
	0xD5F08277, 0xD9F39498, 0xD9F3949A, 0xD9F3949B, 0xD9F3949C, 0xD9F3949D,
	0xDA55CF56, 0xDCD91F31, 0xDD4101FC, 0xDECC0005, 0xE337ABD6, 0xE5F742F6,
	0xE62B3858, 0xE660D395, 0xE660D396, 0xE660D397, 0xE6D8B938, 0xF0739A82,
	0xF3C4A0B1, 0xF5CB2A3E, 0xF6DBAACA, 0xF8A7810F, 0xF91FF6EF, 0xFB3D4BA5,
	0xFB3D4BA6, 0xFB3D4BA7, 0xFB6BDBE9, 0xFDE1BB35, 0xFE64427D, 0xFF8DD834,
};

bool IsIllegalID(uint32_t id)
{
	for (uint32_t illegalToolImageID : kIllegalIconIDs) {
		if (id == illegalToolImageID) {
			return true;
		}
	}

	return false;
}

eastl::vector<ResourceKey> moddedIconKeyCache = {};

void ReadModdedPNGs()
{
	eastl::vector<ResourceKey> toolIconKeys;

	ResourceManager.GetFileKeys(toolIconKeys,
		&Resource::StandardFileFilter(
			ResourceKey::kWildcardID,
			0x3064CB38, // ufotools~
			TypeIDs::png,
			ResourceKey::kWildcardID
		)
	);

	for (const ResourceKey& toolIconKey : toolIconKeys) {
		if (!IsIllegalID(toolIconKey.instanceID)) {
			moddedIconKeyCache.push_back(toolIconKey);
		}
	}
}

void InjectIconWindows(UTFWin::IWindow* window)
{
	if (moddedIconKeyCache.size() == 0) { // Don't read it multiple times.
		ReadModdedPNGs();
	}

	for (const ResourceKey& toolIconKey : moddedIconKeyCache) {
		UTFWin::IWindow* iconWindow = UTFWin::IImageDrawable::AddImageWindow(
			{ toolIconKey.instanceID, TypeIDs::png, toolIconKey.groupID },
			0, 0, window);

		iconWindow->SetControlID(toolIconKey.instanceID);
		iconWindow->SetFillColor(Color(255, 255, 255, 0));
		iconWindow->SetArea({ 0, 0, 300, 300 });
		iconWindow->SetFlag(UTFWin::kWinFlagVisible, false);
	}
}

member_detour(LoadSPUI_detour, UTFWin::UILayout, bool(const ResourceKey&, bool, uint32_t)) {
	bool detoured(const ResourceKey & resourceKey, bool unkBool, uint32_t unkParams) {
		bool result = original_function(this, resourceKey, unkBool, unkParams);
		if (resourceKey.instanceID == 0x46fed9c8) { // Only modify layout with all base game icons
			UTFWin::UILayout* layout = this;
			UTFWin::IWindow* firstIcon = layout->FindWindowByID(0xC19CCD88); // First icon from spui. Should be the fastest to access.
			InjectIconWindows(firstIcon); // Icons should be destroyed with window hierarchy
		}

		return result;
	}
};

long SpaceToolIconOverride::AttachDetour() {
	long result = 0;
	result |= LoadSPUI_detour::attach(GetAddress(UTFWin::UILayout, Load));
	return result;
}

#endif
