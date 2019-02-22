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

#include <EASTL\functional.h>

#define static_detour(ClassName, FunctionName, decl) static_detour<decl>(); \
 typedef static_detour<decl>::original_pointer ClassName##_##FunctionName##_original

#define detour(ClassName, FunctionName, decl) detour<ClassName, decl>(); \
 typedef detour<ClassName, decl>::original_pointer FunctionName##_original

namespace ModAPI
{
	template<typename T>
	class static_detour;

	template<typename T, typename U>
	class detour;

	template <typename _original_pointer, typename _detoured_pointer>
	class detour_base
	{
	public:
		typedef _original_pointer original_pointer;
		typedef _detoured_pointer detoured_pointer;

		inline void assign(detoured_pointer pNewFunction)
		{
			pDetouredFunction = pNewFunction;
		}

	protected:
		original_pointer pOriginalFunction;
		detoured_pointer pDetouredFunction;
	};

	template<typename Result, typename ... Arguments>
	class static_detour<Result(Arguments...)>
	{
	public:
		typedef Result(*original_pointer)(Arguments...);
		typedef Result(*detoured_pointer)(original_pointer, Arguments...);

		inline Result operator()(Arguments... args)
		{
			return pOriginalFunction(args);
		}

		inline void assign(detoured_pointer pNewFunction)
		{
			pDetouredFunction = pNewFunction;
		}

	protected:
		original_pointer pOriginalFunction;
		detoured_pointer pDetouredFunction;
	};

	template<typename ThisType, typename Result, typename ... Arguments>
	class detour<ThisType, Result(Arguments...)>
	{
	public:
		typedef Result(__thiscall*original_pointer)(ThisType*, Arguments...);
		typedef Result(__fastcall*detoured_pointer)(ThisType*, int, original_pointer, Arguments...);

		inline Result operator()(ThisType* pObject, Arguments... args)
		{
			return pOriginalFunction(pObject, args);
		}

		inline void assign(detoured_pointer pNewFunction)
		{
			pDetouredFunction = pNewFunction;
		}

	protected:
		original_pointer pOriginalFunction;
		detoured_pointer pDetouredFunction;
	};
}