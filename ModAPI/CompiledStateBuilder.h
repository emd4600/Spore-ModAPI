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

#include "MaterialConfig.h"

namespace ModAPI
{
	class CompiledStateBuilder
	{
	public:
		CompiledStateBuilder();
		~CompiledStateBuilder();

		/*void WriteBool(bool value);
		void WriteChar(char value);
		void WriteShort(short value);
		void WriteInt(int value);
		void WriteFloat(float value);*/

		template <typename T>
		void Write(T value)
		{
			CheckBufferSize(sizeof(T));
			IncrementSize(sizeof(T));

			*(T*)(buffer + offset) = value;
			offset += sizeof(T);
		}

		void CopyBuffer(char* dst);

		int GetOffset();
		void SetOffset(int offset);

		int GetSize();

		static const int BUFFER_SIZE = 512;

	private:
		char* buffer;
		int offset;
		int size;
		int bufferSize;

		void CheckBufferSize(int extraSize);

		inline void IncrementSize(int extraSize)
		{
			if (offset == size)
			{
				size += extraSize;
			}
		}
	};
}