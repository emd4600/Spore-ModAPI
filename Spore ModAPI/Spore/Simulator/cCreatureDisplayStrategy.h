#pragma once

#include <Spore\Simulator\cBaseDisplayStrategy.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\UI\GlobalUI.h>
#include <Spore\Swarm\IVisualEffect.h>

#define cCreatureDisplayStrategyPtr eastl::intrusive_ptr<Simulator::cCreatureDisplayStrategy>

namespace Simulator
{
	class cCreatureDisplayStrategy
		/* 00h */	: public cBaseDisplayStrategy
		/* 38h */	, public UTFWin::IWinProc
		/* 3Ch */	, public App::IMessageListener
		/* 40h */	, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x107B7140;

	public:
		/* 48h */	ObjectPtr field_48;
		/* 4Ch */	ObjectPtr field_4C;
		/* 50h */	int field_50;  // not initialized
		/* 54h */	bool field_54;  // not initialized
		/* 55h */	bool field_55;  // true
		/* 58h */	UI::GlobalUI* mpGlobalUI;
		/* 5Ch */	int mpPosseUI;  //TODO UI::Posse*
		/* 60h */	ObjectPtr mpUISocialRainbow;  // TODO cUISocialRainbow*
		/* 68h */	cGonzagoTimer field_68;
		/* 88h */	cGonzagoTimer field_88;
		//TODO this is actually a structure, UI::CreatureTimerBar
		/* A8h */	bool field_A8;  // true
		/* ACh */	int field_AC;
		/* B0h */	char padding_B0[0xE0 - 0xB0];
		/* E0h */	cGonzagoTimer field_E0;
		/* 100h */	cGonzagoTimer field_100;
		/* 120h */	ObjectPtr field_120;
		/* 124h */	int field_124;
		/* 128h */	int field_128;
		/* 12Ch */	int field_12C[10];
		/* 158h */	cGonzagoTimer field_158;
		/* 178h */	float field_178;
		/* 17Ch */	float field_17C;
		/* 180h */	float field_180;
		/* 184h */	float field_184;  // true
		/// Effect 0x36099ACF
		/* 188h */	IVisualEffectPtr field_188;
		/// Effect 0xAAA2AC3C
		/* 18Ch */	IVisualEffectPtr field_18C;
		/* 190h */	char field_190[0x320 - 0x190];
	};
	ASSERT_SIZE(cCreatureDisplayStrategy, 0x320);
}