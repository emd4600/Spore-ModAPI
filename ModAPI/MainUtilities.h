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

#include <Windows.h>

namespace ModAPI
{
	class UIEventListener;
	enum UIEventContext;

	class ShaderConstantsManager;

	class ModAPIUtils
	{
	public:
		typedef void(*InitFunction)();

		static void AddInitFunction(InitFunction function);

		static void AddUIEventListener(UIEventListener* listener, UIEventContext context);

		static ShaderConstantsManager* GetShaderConstantsManager();

		ModAPIUtils();

		static void InitModAPI();


	private:
		static ModAPIUtils* Utils;

	private:

		HMODULE hModAPIDLL;

		FARPROC pAddInitFunction;
		FARPROC pAddInitUIEventListener;
		FARPROC pGetShaderConstantsManager;
	};
	// For convenience, take it out of the class
	inline void AddInitFunction(ModAPIUtils::InitFunction function)
	{
		ModAPIUtils::AddInitFunction(function);
	}
}