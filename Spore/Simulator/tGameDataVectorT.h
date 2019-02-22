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

	template <class T>
	class tGameDataVectorT
	{
	public:
		typedef intrusive_ptr<T> PtrT;

		bool field_0;
		vector<intrusive_ptr<T>> data;

		intrusive_ptr<T>& operator[] (const int index);
		const intrusive_ptr<T>& operator[] (const int index) const;

		inline size_t size() const {
			return data.size();
		};

		inline bool empty() const {
			return data.empty();
		};

		inline typename vector<PtrT>::iterator begin() { return data.begin(); };
		inline typename vector<PtrT>::const_iterator begin() const { return data.begin(); };
		inline typename vector<PtrT>::const_iterator cbegin() const { return data.cbegin(); };
		inline typename vector<PtrT>::iterator end() { return data.end(); };
		inline typename vector<PtrT>::const_iterator end() const { return data.end(); };
		inline typename vector<PtrT>::const_iterator cend() const { return data.cend(); };
	};

	template <class T>
	inline intrusive_ptr<T>& tGameDataVectorT<T>::operator[] (const int index) {
		return data[index];
	}

	template <class T>
	inline const intrusive_ptr<T>& tGameDataVectorT<T>::operator[] (const int index) const {
		return data[index];
	}
}