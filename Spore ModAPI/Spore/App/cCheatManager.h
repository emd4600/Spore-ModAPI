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
	///
	/// The implementation of ICheatManager; this should only be used for extending and detouring. 
	///
	class cCheatManager 
		: public ICheatManager
		, public IVirtual
	{
	public:
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
		virtual size_t GetKeywords(const char* pPattern, eastl::vector<const char*> dst) override;
		virtual void func30h(Object*) override;
		virtual void func34h(Object*) override;
		virtual ArgScript::FormatParser* GetArgScript() override;
		virtual void func3Ch(int) override;
		virtual void func40h(int) override;
		virtual void func44h(int) override;
		virtual bool func48h() override;
		virtual void func4Ch(bool) override;


	public:
		typedef eastl::map<eastl::string, eastl::intrusive_ptr<ArgScript::IParser>> CheatMap_t;

		/* 08h */	int mnRefCount;
		/* 0Ch */	CheatMap_t mCheats;
		/* 28h */	eastl::set<eastl::string> mNotifyCheats;
		/* 44h */	ArgScript::FormatParser* mpArgScript;
		/* 48h */	eastl::set<ObjectPtr> field_48;  // UIs?
		/* 64h */	bool field_68;  // true
	};
	ASSERT_SIZE(cCheatManager, 0x68);

	namespace Addresses(cCheatManager)
	{
		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(func14h);
		DeclareAddress(AddCheat);
		DeclareAddress(RemoveCheat);
		DeclareAddress(ProcessLine);
		DeclareAddress(func24h);
		DeclareAddress(GetCheat);
		DeclareAddress(GetKeywords);
		DeclareAddress(func30h);
		DeclareAddress(func34h);
		DeclareAddress(GetArgScript);
		DeclareAddress(func3Ch);
		DeclareAddress(func40h);
		DeclareAddress(func44h);
		DeclareAddress(func48h);
		DeclareAddress(func4Ch);
	}
}