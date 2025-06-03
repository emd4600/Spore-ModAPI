/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModCreatorKit.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#include "stdafx.h"
#include "Cheats.h"

#include "ContextCheat.h"
#include "AddressCheat.h"
#include "AnimLogCheat.h"
#include "EffectLogCheat.h"
#include "SFXLogCheat.h"
#include "PackageCheat.h"
#include "PrintCursorCheat.h"
#include "UILogCheat.h"
#include "UIInspectCheat.h"
#include "PlaySoundCheat.h"

#include <Spore\App\ICheatManager.h>
#include <Spore\Editors\BakeManager.h>
#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\Swarm\IEffectsManager.h>

template <typename T> void AddDebugCheat(const char* name, int size, int address) {
	void* data = new char[size];
	CALL(address, void, Args(void*, T*), Args(data, T::Get()));
	CheatManager.AddCheat(name, (ArgScript::ICommand*)data);
}

void AddDebugCheat_(const char* name, int size, int address) {
	void* data = new char[size];
	CALL(address, void, Args(void*), Args(data));
	CheatManager.AddCheat(name, (ArgScript::ICommand*)data);
}

void AddCheats()
{
	CheatManager.AddCheat("devContext", new ContextCheat());
	CheatManager.AddCheat("devAnimLog", new AnimLogCheat());
	CheatManager.AddCheat("devSFXLog", new SFXLogCheat());
	CheatManager.AddCheat("devEffectLog", new EffectLogCheat());
	CheatManager.AddCheat("devPackage", new PackageCheat());
	CheatManager.AddCheat("devLogUI", new UILogCheat());
	CheatManager.AddCheat("devInspectUI", new UIInspectCheat());
	CheatManager.AddCheat("devPrintCursor", new PrintCursorCheat());
	CheatManager.AddCheat("devPlaySound", new PlaySoundCheat());

	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x1498444, 0x1493E5C)), "devRaid");
	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x149845C, 0x1493E74)), "devSpace");
	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x1498474, 0x1493E8C)), "devBadge");
	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x149848C, 0x1493EA4)), "devMission");
	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x14984BC, 0x1493ED4)), "devAri");

	AddDebugCheat<Editors::IBakeManager>(
		"devBake", 0xF0, Address(ModAPI::ChooseAddress(0x4044D0, 0x404500)));

	AddDebugCheat<Graphics::IRenderTargetManager>(
		"devRTT", 0xDC, Address(ModAPI::ChooseAddress(0x76F4B0, 0x76EAD0)));

	// Requires access to state manager
	//AddDebugCheat<void*>("debugState", 0xE0, Address(ModAPI::ChooseAddress(0x7E5360, 0x7E4F40)));

	AddDebugCheat_("devApp", 0xE8, Address(ModAPI::ChooseAddress(0x7EA7D0, 0x7EA3C0)));

	AddDebugCheat<Swarm::IEffectsManager>(
		"devEffects", 0x100, Address(ModAPI::ChooseAddress(0xA74070, 0xA73C10)));

	AddDebugCheat<Swarm::IEffectsManager>(
		"devEffect", 0x1A4, Address(ModAPI::ChooseAddress(0xA742F0, 0xA73EA0)));

	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x1499558, 0x1494F70)), "devTerraform");
	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x14648AC, 0x1460514)), "devViewMgr");
	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x146A29C, 0x1465EF4)), "devStarMgr");
	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x147CC5C, 0x147889C)), "devGtn");
	AddressCheat::AddCheat(Address(ModAPI::ChooseAddress(0x13F7690, 0x13F4678)), "devOTDB");

	// Special cheat: is also an IUnmanagedMessageListener, so we need to replace two vftables
	auto pollenCheat = new int[6];
	pollenCheat[0] = Address(ModAPI::ChooseAddress(0x13FF02C, 0x13FB894));
	pollenCheat[1] = 0;
	pollenCheat[2] = 0;
	pollenCheat[4] = Address(ModAPI::ChooseAddress(0x13FF024, 0x13FB88C));
	pollenCheat[5] = 0;
	CheatManager.AddCheat("devPollen", (ArgScript::ICommand*)pollenCheat);
}