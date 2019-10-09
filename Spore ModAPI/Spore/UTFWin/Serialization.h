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

#include <Spore\UTFWin\LayoutReader.h>

#include <EASTL\vector.h>

using namespace eastl;

namespace UTFWin
{
	struct ComponentSerialization;
	struct StructSerialization;
	class Serializer;

	typedef bool(*StructSerializerGetter)(Serializer& dst, void* arg_4, ComponentSerialization& serialization);

	typedef bool(*Getter)(void* arg_0, void* arg_4, ComponentSerialization& serialization);
	typedef bool(*Setter)(void* arg_0, void* arg_4, ComponentSerialization& serialization);
	typedef bool(*SerializerGetter)(Serializer& dst, void* arg_4, ComponentSerialization& serialization);

	struct PropertyMethods
	{
		Getter mGetter;
		Setter mSetter;
		SerializerGetter mSerializerGetter;
	};

	struct SerializedProperty
	{
		 
		enum
		{
			kTypeParent = 1,
			kTypeBool = 2,
			kTypeUInt8 = 3,
			kTypeUInt16 = 4,
			kTypeUInt32 = 5,
			kTypeUInt64 = 6,
			kTypeInt8 = 7,
			kTypeInt16 = 8,
			kTypeInt32 = 9,
			kTypeInt64 = 10,
			kTypeFloat = 11,

			kTypeDim = 15,
			kTypeVec4 = 16,
			kTypeVec2 = 17,
			kTypeText = 18,
			kTypePointer = 19,
			kTypeStruct = 20,

			kFlagArray = 0x8000
		};

		int field_0;
		union
		{
			PropertyMethods* mpMethods;
			StructSerialization* mpStructSerialization;
		};
		uint32_t mnProxyID;
		uint16_t mnType;
		size_t mnOffset;
		size_t mnCount;
	};

	struct StructSerialization
	{
		int field_0;
		int field_4;
		StructSerializerGetter mGetter;
	};

	struct ComponentSerialization
	{
		ComponentSerialization(uint16_t nType, uint32_t nProxyID, size_t nObjectSize, SerializedProperty* pProperties, size_t nPropertiesCount);

		uint16_t mnType;
		uint32_t mnProxyID;
		size_t mnObjectSize;
		SerializedProperty* mpProperties;
		size_t mnPropertiesCount;
		// 3 methods?
	};

	class Serializer
	{
	public:
		const ComponentSerialization* mpSerialization;
		void* mpObject;
		size_t mnCount;
		uint32_t mnProxyID;
	};

	class SerializationService
	{
	public:
		SerializationService();
		virtual ~SerializationService() {};

		/* 04h */	virtual void func04h(int) = 0;
		/* 08h */	virtual void func08h(int) = 0;
		/* 0Ch */	virtual void func0Ch() = 0;
		/* 10h */	virtual LayoutReader* GetReader(uint32_t nType) = 0;
		/* 14h */	virtual void func18h(int, int) = 0;
		/* 18h */	virtual int Read(IO::IStream* pStream, int arg_8, int arg_C) = 0;

	protected:
		/* 04h */	vector<intrusive_ptr<Object>> field_04;
		/* 18h */	vector<int> field_18;
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
	};

	static_assert(sizeof(SerializationService) == 0x34, "sizeof(SerializationService) != 34h");
}