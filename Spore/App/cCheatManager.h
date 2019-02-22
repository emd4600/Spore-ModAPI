/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
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

#pragma once

#include <Spore\App\ICheatManager.h>
#include <Spore\ArgScript\FormatParser.h>
#include <Spore\ArgScript\IParser.h>
#include <Spore\Object.h>

#include <EASTL\map.h>
#include <EASTL\set.h>
#include <EASTL\string.h>


namespace App
{
	using namespace eastl;
	using namespace ArgScript;

	///
	/// The implementation of ICheatManager; this should only be used for extending and detouring. 
	///
	class cCheatManager : public ICheatManager, public IVirtual
	{
		cCheatManager();
		virtual ~cCheatManager() {};

		// Overrides

		virtual int AddRef() override;
		virtual int Release() override;

		virtual bool Initialize() override;
		virtual bool Dispose() override;
		virtual void func14h() override;
		virtual void AddCheat(const char* pString, ArgScript::ICommand* parser, bool bNotify) override;
		virtual void RemoveCheat(const char* pString) override;
		virtual bool ProcessLine(const char* pString) override;
		virtual int func24h() override;
		virtual ArgScript::ICommand* GetCheat(const char* pKeyword) override;
		virtual size_t GetKeywords(const char* pPattern, vector<const char*> dst) override;
		virtual void func30h(Object*) override;
		virtual void func34h(Object*) override;
		virtual ArgScript::FormatParser* GetArgScript() override;
		virtual void func3Ch(int) override;
		virtual void func40h(int) override;
		virtual void func44h(int) override;
		virtual bool func48h() override;
		virtual void func4Ch(bool) override;


	protected:

		typedef map<string, intrusive_ptr<ArgScript::IParser>> CheatMap_t;

	protected:
		/* 08h */	int mnRefCount;
		/* 0Ch */	CheatMap_t mCheats;
		/* 28h */	set<string> mNotifyCheats;
		/* 44h */	ArgScript::FormatParser* mpArgScript;
		/* 48h */	set<intrusive_ptr<Object>> field_48;  // UIs?
		/* 64h */	bool field_68;  // true
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cCheatManager) == 0x68, "sizeof(cCheatManager) != 68h");

	namespace InternalAddressList(cCheatManager)
	{
		DefineAddress(Initialize, GetAddress(0x67EE90, 0x67ECC0, 0x67ECC0));
		DefineAddress(Dispose, GetAddress(0x67F630, 0x67F350, 0x67F350));
		DefineAddress(func14h, GetAddress(0x7E66D0, 0xC2E620, 0xC2E640));
		DefineAddress(AddCheat, GetAddress(0x67FF40, 0x67FC10, 0x67FC10));
		DefineAddress(RemoveCheat, GetAddress(0x67FCA0, 0x67F970, 0x67F970));
		DefineAddress(ProcessLine, GetAddress(0x67F150, 0x67EF80, 0x67EF80));
		DefineAddress(func24h, GetAddress(0x67E580, 0x67E430, 0x67E430));
		DefineAddress(GetCheat, GetAddress(0x67F710, 0x67F430, 0x67F430));
		DefineAddress(GetKeywords, GetAddress(0x67FA00, 0x67F6D0, 0x67F6D0));
		DefineAddress(func30h, GetAddress(0x67F7E0, 0x67F500, 0x67F500));
		DefineAddress(func34h, GetAddress(0x67F860, 0x67F580, 0x67F580));
		DefineAddress(GetArgScript, GetAddress(0x113BA60, 0x113AE90, 0x113AE80));
		DefineAddress(func3Ch, GetAddress(0x67E880, 0x67E6B0, 0x67E6B0));
		DefineAddress(func40h, GetAddress(0x67E8C0, 0x67E6F0, 0x67E6F0));
		DefineAddress(func44h, GetAddress(0x67E900, 0x67E730, 0x67E730));
		DefineAddress(func48h, GetAddress(0xABFB10, 0xABF750, 0xABF790));
		DefineAddress(func4Ch, GetAddress(0x67E200, 0x67E0A0, 0x67E0A0));
	}
}