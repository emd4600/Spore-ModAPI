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
	struct SerializedProperty;
	struct Serializer;

	/// Structure used to define access methods for special property types.
	struct PropertyMethods
	{
		typedef bool(*Getter)(void* arg_0, void*, const ComponentSerialization& serialization);
		typedef bool(*Setter)(void* arg_0, void*, const ComponentSerialization& serialization);
		typedef bool(*SerializerGetter)(Serializer& dst, const Serializer& parentSerializer, const SerializedProperty* prop);

		Getter getter;
		Setter setter;
		SerializerGetter serializerGetter;
	};

	struct StructSerialization
	{
		typedef bool(*StructSerializerGetter)(Serializer& dst, const Serializer& parentSerializer, const ComponentSerialization& serialization);

		int field_0;
		int field_4;
		StructSerializerGetter mGetter;
	};

	/// The possible property types used in SPUI serialization.
	enum SerializedTypes
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

	/// Defines how a member of a class is stored in an SPUI.
	struct SerializedProperty
	{


		int field_0;
		union
		{
			PropertyMethods* pMethods;
			StructSerialization* pStructSerialization;
		};
		/// An ID used to uniquely identify this property.
		uint32_t proxyID;
		/// The type of property, 
		uint16_t type;
		/// The offset of the variable inside the class. Can be obtained using `offsetof(class, member)`.
		size_t offset;
		/// If it's an array, how many elements the property has; otherwise, 1.
		size_t count;
	};

	/// A structure that defines how a class is stored in an SPUI.
	struct ComponentSerialization
	{
		typedef bool(*UnkMethod1)(void*);
		typedef bool(*UnkMethod2)();
		typedef void(*OnSerializationFinished)(void*);

		ComponentSerialization(uint16_t type, uint32_t proxyID, size_t objectSize, SerializedProperty* properties, size_t propertiesCount);

		/// The type of component, one in UTFWin::SerializedTypes; usually `kTypePointer`.
		uint16_t type;
		/// The proxy ID used to identify the component type.
		uint32_t proxyID;
		/// The `sizeof()` of the class to be serialized
		size_t objectSize;
		/// A pointer to the properties of the class
		SerializedProperty* pProperties;
		/// How many properties there are in `pProperties`
		size_t propertiesCount;

		UnkMethod1 field_14;
		UnkMethod2 field_18;  // always returns true?
		/// Optional method called after the serialization has been finished. The parameter is the object.
		OnSerializationFinished onSerializationFinished;
	};

	/// A structure that defines how an object must be read in an SPUI.
	struct Serializer
	{
		/// A pointer to the structure that defines the serialization for the element.
		const ComponentSerialization* pSerialization;
		/// The element to be serialized
		void* pObject;
		/// How many components the element has (1 if it's not an array)
		size_t count;
		/// The proxy ID used to identify the element type. It's the same used in the class factory.
		uint32_t proxyID;
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