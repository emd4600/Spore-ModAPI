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

#include <EASTL\vector.h>
#include <EASTL\intrusive_ptr.h>
#include <Spore\Object.h>

namespace Simulator
{
	class cGameData;

#ifndef SDK_TO_GHIDRA
	template <class T>
	class tGameDataVectorT
	{
	public:
		typedef eastl::intrusive_ptr<T> PtrT;

		tGameDataVectorT();

		bool needsUpdate;
		eastl::vector<eastl::intrusive_ptr<T>> data;

		eastl::intrusive_ptr<T>& operator[] (const int index);
		const eastl::intrusive_ptr<T>& operator[] (const int index) const;

		inline size_t size() const {
			return data.size();
		};

		inline bool empty() const {
			return data.empty();
		};

		inline typename eastl::vector<PtrT>::iterator begin() { return data.begin(); };
		inline typename eastl::vector<PtrT>::const_iterator begin() const { return data.begin(); };
		inline typename eastl::vector<PtrT>::const_iterator cbegin() const { return data.cbegin(); };
		inline typename eastl::vector<PtrT>::iterator end() { return data.end(); };
		inline typename eastl::vector<PtrT>::const_iterator end() const { return data.end(); };
		inline typename eastl::vector<PtrT>::const_iterator cend() const { return data.cend(); };
	};

	template <class T>
	inline tGameDataVectorT<T>::tGameDataVectorT()
		: needsUpdate(true)
		, data()
	{}

	template <class T>
	inline eastl::intrusive_ptr<T>& tGameDataVectorT<T>::operator[] (const int index) {
		return data[index];
	}

	template <class T>
	inline const eastl::intrusive_ptr<T>& tGameDataVectorT<T>::operator[] (const int index) const {
		return data[index];
	}
#else
	// The original class has nested template parameters, it is too complex for our script to handle
	template <class T>
	class tGameDataVectorT
	{
	public:
		bool needsUpdate;
		eastl::intrusive_ptr<T>* mpBegin;
		eastl::intrusive_ptr<T>* mpEnd;
		eastl::intrusive_ptr<T>* mpCapacity;
		int mGarbage;
		eastl::allocator mAllocator;
	};
#endif
}