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


#include <Spore\ArgScript\FormatParser.h>
#include <Spore\Internal.h>
#include <Spore\Object.h>

#include <EASTL\vector.h>

using namespace eastl;

namespace App
{

	///
	/// This manager is used to control the available cheats in the game, and the cheat console.
	/// It contains a map that assigns a keyword to an ArgScript::ICommand object, which parses the cheat and does the action.
	///
	class ICheatManager
	{
	public:
		enum
		{
			/// A message with no content sent when certain cheats are invoked.
			kMsgCheatInvoked = 0x4BEF1E3
		};

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~ICheatManager() {};

		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual bool Dispose() = 0;

		/* 14h */	virtual void func14h() = 0;

		///
		/// Adds a cheat to this manager. The cheat is just an ArgScript::ICommand object; the ArgScript::ICommand::ParseLine()
		/// function will be called when the cheat is invoked.
		/// @param pString The keyword that is used to invoke the cheat. This is case insensitive and it can't contain whitespaces.
		/// @param pParser The ArgScript::ICommand that represents this cheat.		
		/// @param bNotify [Optional] If true, a kMsgCheatInvoked message will be sent when the cheat is invoked.
		///
		/* 18h */	virtual void AddCheat(const char* pString, ArgScript::ICommand* pParser, bool bNotify = false) = 0;

		void AddCheat(const char* pKeyword, ArgScript::ParseLine_t pParseLine, ArgScript::GetDescription_t pGetDescription, bool bNotify = false);
		
		///
		/// Removes the cheat that is invoked with the given keyword from this manager. 
		/// @param pString The keyword used to invoke the cheat. This is case insensitive and it can't contain whitespaces.
		///
		/* 1Ch */	virtual void RemoveCheat(const char* pString) = 0;

		///
		/// Called every time a line is submitted to the console. 
		/// @param pString The text contents of the line.
		/// @returns Whether the line was correctly processed or not.
		///
		/* 20h */	virtual bool ProcessLine(const char* pString) = 0;

		/* 24h */	virtual int func24h() = 0;

		///
		/// Returns the ArgScript::ICommand that is operating behind the requested cheat.
		/// @param pKeyword The keyword used to invoke the cheat.
		///
		/* 28h */	virtual ArgScript::ICommand* GetCheat(const char* pKeyword) = 0;

		///
		/// Gets all the cheat keywords in this manager that match the given pattern. The pattern uses the character 
		/// '?' to allow any character, and '*' to allow any sequence of characters.
		/// @param pPattern The pattern keywords must match in order to be added to the vector.
		/// @param dst A const char* vector where the keywords will be added.
		/// @returns The number of keywords added.
		///
		/* 2Ch */	virtual size_t GetKeywords(const char* pPattern, vector<const char*> dst) = 0;

		/* 30h */	virtual void func30h(Object*) = 0;
		/* 34h */	virtual void func34h(Object*) = 0;

		///
		/// Returns the ArgScript::FormatParser instance that this manager is using.
		///
		/* 38h */	virtual ArgScript::FormatParser* GetArgScript() = 0;

		/* 3Ch */	virtual void func3Ch(int) = 0;
		/* 40h */	virtual void func40h(int) = 0;
		/* 44h */	virtual void func44h(int) = 0;
		/* 48h */	virtual bool func48h() = 0;
		/* 4Ch */	virtual void func4Ch(bool) = 0;


		///
		/// Returns the active cheat manager. Same as CheatManager().
		///
		static ICheatManager* Get();


	};

	///
	/// An utility method that returns the active console stream, and that can be used to print strings to the console.
	/// This is the equivalent to ICheatManager::Get()->GetArgScript()
	///
	inline ArgScript::FormatParser* GetConsoleStream()
	{
		return ICheatManager::Get()->GetArgScript();
	}

	///
	/// Returns the active cheat manager. Same as ICheatManager::Get().
	///
	inline ICheatManager* CheatManager()
	{
		return ICheatManager::Get();
	}

	template<typename... Args> inline void ConsolePrintF(const char* str, Args... args)
	{
		ArgScript::PrintF(GetConsoleStream(), str, args...);
	}

	/////////////////////////////////
//// INTERNAL IMPLEMENTATION ////
/////////////////////////////////

	namespace Addresses(ICheatManager)
	{
		DeclareAddress(Get);
	}
}
