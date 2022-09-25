#pragma once

#include <Spore\Editors\EditorLimits.h>

#define cScenarioDataEconomyPtr eastl::intrusive_ptr<Simulator::cScenarioDataEconomy>
#define cScenarioTerraformEconomyPtr eastl::intrusive_ptr<Simulator::cScenarioTerraformEconomy>

namespace Simulator
{
	class cScenarioDataEconomy
		: public Editors::IEditorLimits
	{
	public:
		/* 1Ch */	virtual void func1Ch(int index, int value);

	public:
		/* 08h */	int mValues[8];
		/* 28h */	int field_28;
		/* 2Ch */	uint32_t field_2C;
	};
	ASSERT_SIZE(cScenarioDataEconomy, 0x30);

	class cScenarioTerraformMode;

	class cScenarioTerraformEconomy
		: public Editors::IEditorLimits
	{
	public:
		/* 08h */	cScenarioTerraformMode* mpTerraformMode;
	};
	ASSERT_SIZE(cScenarioTerraformEconomy, 0xC);
}