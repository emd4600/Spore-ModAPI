#pragma once

#include <Spore\Internal.h>
#include <EASTL\vector.h>

#define HintManager (*UI::cHintManager::Get())

namespace UI
{
	class cHintManager
	{
	public:
		void ShowHint(uint32_t hintID);

		static cHintManager* Get();

	protected:
		/* 0Ch */	eastl::vector<int> field_C;
		/* 20h */	eastl::vector<int> field_20;
		/* 34h */	float field_34;
		/* 38h */	float field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	float field_40;
		/* 44h */	float field_44;
		/* 48h */	int field_48;  // 3
		/* 4Ch */	int field_4C;
		/* 50h */	float field_50;
	};

	namespace Addresses(cHintManager) {
		DeclareAddress(Get);
		DeclareAddress(ShowHint);
	}
}