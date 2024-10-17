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

#include <EASTL\string.h>
#include <EASTL\vector.h>
#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <Spore\ResourceKey.h>
#include <Spore\Transform.h>
#include <Spore\LocalizedString.h>

namespace App
{

	class PropertyList;

	enum class PropertyType : uint16_t
	{
		None = 0,
		Bool = 1,
		Int32 = 9,
		UInt32 = 0x0a,
		Float = 0x0d,
		String8 = 0x12,
		String16 = 0x13,
		Key = 0x20,
		Text = 0x22,
		Vector2 = 0x30,
		Vector3 = 0x31,
		ColorRGB = 0x32,
		Vector4 = 0x33,
		ColorRGBA = 0x34,
		Transform = 0x38,
		BBox = 0x39,
		// Unseen types
		Char = 0x0002,
		WChar = 0x0003,
		Int8 = 0x0005,
		UInt8 = 0x0006,
		Int16 = 0x0007,
		UInt16 = 0x0008,
		Int64 = 0x000B,
		UInt64 = 0x000C,
		Double = 0x000E,
		Ptr = 0x000F,
		// only this one is used in Spore code, but not in files
		Void = 0x0010,
		IUnknownRC = 0x0011,
		Flags = 0x0021,
		Matrix2 = 0x0035,
		Matrix3 = 0x0036,
		Matrix4 = 0x0037
	};


	using namespace Math;


	///
	/// Property is a class used to represent a property belonging to a PROP file. This class is widely used for configuring
	/// and storing game properties. The class PropertyList is used to group properties together, and represent a PROP file.
	///
	/// This class is not usually used directly; it provides, however, numerous static methods to easily get data from a PropertyList.
	/// For example, to get a property from a PROP file:
	/// ~~~~~~~~~~~~~~~{.cpp}
	/// PropertyList* propList = ...;  // get the PropertyList, probably from the PropManager class
	/// float modelScale = 1.0f;  // we can assign it a default value
	/// Property::GetFloat(propList, 0x00FBA611, modelScale);  // 0x00FBA611 is the propertyID of modelScale; you can find them in reg_property.txt (SporeMaster/SporeModder)
	/// // this returns a bool; if you don't assign default values, it might be a good idea to check it
	/// ~~~~~~~~~~~~~~~
	///
	/// Another use of this class is to assign values; this can be used to store saved game data, for example:
	/// ~~~~~~~~~~~~~~~{.cpp}
	/// // assuming the propertyID is just the hash of 'dnaAmount' (so it does not have an entry on reg_property.txt)
	/// propList->AddProperty(Hash::FNV("dnaAmount"), Property().SetValueInt32(80));
	/// ~~~~~~~~~~~~~~~
	///
	class Property
	{
	public:
		struct TextProperty
		{
			uint32_t tableID;
			uint32_t instanceID;
			char16_t buffer[256];
		};
	public:
		enum PropertyFlags
		{
			kPropertyFlagNotDirect = 0x10,
			kPropertyFlagArray = 0x30
		};

	public:
		Property();
		Property(const Property&);
		//TODO if flags & 4, does something special
		~Property();


		/// @name Methods for getting value pointers
		///@{

		///
		/// Returns a pointer to the int32_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		int32_t* GetValueInt32();

		///
		/// Returns a pointer to the float value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		float* GetValueFloat();

		///
		/// Returns a pointer to the bool value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		bool* GetValueBool();

		///
		/// Returns a pointer to the uint32_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		uint32_t* GetValueUInt32();

		///
		/// Returns a pointer to the Math::Vector2 value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		Vector2* GetValueVector2();

		///
		/// Returns a pointer to the Math::Vector3 value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		Vector3* GetValueVector3();

		///
		/// Returns a pointer to the Math::Vector4 value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		Vector4* GetValueVector4();

		///
		/// Returns a pointer to the Math::ColorRGB value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		ColorRGB* GetValueColorRGB();

		///
		/// Returns a pointer to the Math::ColorRGBA value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		ColorRGBA* GetValueColorRGBA();

		///
		/// Returns a pointer to the ResourceKey ('key') value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		ResourceKey* GetValueKey();

		///
		/// Returns a pointer to the EntityTransform ('transform') value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		Transform* GetValueTransform();

		///
		/// Returns a pointer to the LocalizedString ('text') value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		LocalizedString* GetValueText();

		///
		/// Returns a pointer to the BoundingBox ('bbox') value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		BoundingBox* GetValueBBox();

		///
		/// Returns a pointer to the eastl::string8 value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		eastl::string8* GetValueString8();

		///
		/// Returns a pointer to the eastl::string16 value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		eastl::string16* GetValueString16();

		// Unseen types:
		///
		/// Returns a pointer to the char value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		char* GetValueChar();

		///
		/// Returns a pointer to the char16_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		char16_t* GetValueWChar();

		///
		/// Returns a pointer to the int8_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		int8_t*	 GetValueInt8();

		///
		/// Returns a pointer to the uint8_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		uint8_t* GetValueUInt8();

		///
		/// Returns a pointer to the int16_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		int16_t* GetValueInt16();

		///
		/// Returns a pointer to the uint16_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		uint16_t* GetValueUInt16();

		///
		/// Returns a pointer to the int64_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		int64_t* GetValueInt64();

		///
		/// Returns a pointer to the uint64_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		uint64_t* GetValueUInt64();

		///
		/// Returns a pointer to the double value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		double* GetValueDouble();

		///
		/// Returns a pointer to the 'flags' value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		void** GetValueFlags();

		///
		/// Returns a pointer to the value(s) of this property, regardless of its type.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		void* GetValue();
		///@}

		/// @name Methods for setting values
		///@{

		///
		/// Sets the value of this property. This will reset the property, so it is like creating a new one.
		/// You must specify the type of the value, a pointer to the value or array of values, the sizeof() the value type,
		/// and the number of values.
		///
		/// This is only for internal usage or to create arrays; to assign single values, using methods like
		/// SetValueBool, SetValueInt32, etc is recommended.
		/// @param type
		/// @param flags
		/// @param pValue
		/// @param nValueSize
		/// @param nValueCount
		///
		bool Set(PropertyType type, int flags, void* pValue, size_t nValueSize, size_t nValueCount);

		///
		/// Sets the value of this Property to the given bool value.
		/// This will be a single-valued bool property.
		///
		/// @param value
		Property& SetValueBool(const bool& value);

		///
		/// Sets the value of this Property to the given int32_t value.
		/// This will be a single-valued int32 property.
		/// @param value
		///
		Property& SetValueInt32(const int32_t& value);

		///
		/// Sets the value of this Property to the given uint32_t value.
		/// This will be a single-valued uint32 property.
		/// @param value
		///
		Property& SetValueUInt32(const uint32_t& value);

		///
		/// Sets the value of this Property to the given float value.
		/// This will be a single-valued float property.
		/// @param value
		///
		Property& SetValueFloat(const float& value);

		///
		/// Sets the value of this Property to the given ResourceKey value.
		/// This will be a single-valued key property.
		/// @param value
		///
		Property& SetValueKey(const ResourceKey& value);

		///
		/// Sets the value of this Property to the given eastl::string8 value.
		/// This will be a single-valued eastl::string8 property.
		/// @param value
		///
		Property& SetValueString8(const eastl::string8& value);

		///
		/// Sets the value of this Property to the given eastl::string16 value.
		/// This will be a single-valued eastl::string16 property.
		/// @param value
		///
		Property& SetValueString16(const eastl::string16& value);

		///
		/// Sets the value of this Property to the given BoundingBox value.
		/// This will be a an array bbox property, with only one value.
		/// @param value
		///
		Property& SetValueBBox(const BoundingBox& value);

		///
		/// Sets the value of this Property to the given Math::Vector2 value.
		/// This will be a single-valued vector2 property.
		/// @param value
		///
		Property& SetValueVector2(const Vector2& value);

		///
		/// Sets the value of this Property to the given Math::Vector3 value.
		/// This will be a single-valued vector3 property.
		/// @param value
		///
		Property& SetValueVector3(const Vector3& value);

		///
		/// Sets the value of this Property to the given Math::Vector4 value.
		/// This will be a single-valued vector4 property.
		/// @param value
		///
		Property& SetValueVector4(const Vector4& value);

		///
		/// Sets the value of this Property to the given Math::ColorRGB value.
		/// This will be a single-valued colorRGB property.
		/// @param value
		///
		Property& SetValueColorRGB(const ColorRGB& value);

		///
		/// Sets the value of this Property to the given Math::ColorRGBA value.
		/// This will be a single-valued colorRGBA property.
		/// @param value
		///
		Property& SetValueColorRGBA(const ColorRGBA& value);


		///
		/// Sets the value of this Property to an array of bool values.
		/// This will be an array bool property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayBool(const bool* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of int32_t values.
		/// This will be an array int32 property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayInt32(const int32_t* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of uint32_t values.
		/// This will be an array uint32 property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayUInt32(const uint32_t* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of float values.
		/// This will be an array float property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayFloat(const float* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of ResourceKey values.
		/// This will be an array key property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayKey(const ResourceKey* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to the an array of eastl::string8 values.
		/// This will be an array eastl::string8 property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayString8(const eastl::string8* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of eastl::string16 values.
		/// This will be an array eastl::string16 property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayString16(const eastl::string16* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of BoundingBox values.
		/// This will be an array bbox property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayBBox(const BoundingBox* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of Transform values.
		/// This will be an array transform property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayTransform(const Transform* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of LocalizedString values.
		/// This will be an array text property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayText(const LocalizedString* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of Math::Vector2 values.
		/// This will be an array vector2 property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayVector2(const Vector2* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of Math::Vector3 values.
		/// This will be an array vector3 property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayVector3(const Vector3* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of Math::Vector4 values.
		/// This will be an array vector4 property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayVector4(const Vector4* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of Math::ColorRGB values.
		/// This will be an array colorRGB property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayColorRGB(const ColorRGB* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of Math::ColorRGBA values.
		/// This will be an array colorRGBA property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayColorRGBA(const ColorRGBA* pValues, size_t nValueCount);

		///@}


		/// @name Static methods for getting values
		///@{

		///
		/// Gets a single bool value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetBool(const PropertyList* pPropertyList, uint32_t propertyID, bool& dst);

		///
		/// Gets a single float value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetFloat(const PropertyList* pPropertyList, uint32_t propertyID, float& dst);

		///
		/// Gets a single int32_t value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetInt32(const PropertyList* pPropertyList, uint32_t propertyID, int32_t& dst);

		///
		/// Gets a single uint32_t value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetUInt32(const PropertyList* pPropertyList, uint32_t propertyID, uint32_t& dst);

		///
		/// Gets a single Math::Vector2 value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetVector2(const PropertyList* pPropertyList, uint32_t propertyID, Vector2& dst);

		///
		/// Gets a single Math::Vector3 value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetVector3(const PropertyList* pPropertyList, uint32_t propertyID, Vector3& dst);

		///
		/// Gets a single Meth::Vector4 value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetVector4(const PropertyList* pPropertyList, uint32_t propertyID, Vector4& dst);

		///
		/// Gets a single Meth::ColorRGB value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetColorRGB(const PropertyList* pPropertyList, uint32_t propertyID, ColorRGB& dst);

		///
		/// Gets a single Math::ColorRGBA value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetColorRGBA(const PropertyList* pPropertyList, uint32_t propertyID, ColorRGBA& dst);

		///
		/// Gets a single ResourceKey value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetKey(const PropertyList* pPropertyList, uint32_t propertyID, ResourceKey& dst);

		///
		/// Gets the instanceID of a single ResourceKey value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetKeyInstanceID(const PropertyList* pPropertyList, uint32_t propertyID, uint32_t& dst);

		///
		/// Gets the groupID of a single ResourceKey value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetKeyGroupID(const PropertyList* pPropertyList, uint32_t propertyID, uint32_t& dst);

		///
		/// Gets the typeID of a single ResourceKey value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetKeyTypeID(const PropertyList* pPropertyList, uint32_t propertyID, uint32_t& dst);

		///
		/// Gets a single LocalizedString ('text') value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetText(const PropertyList* pPropertyList, uint32_t propertyID, LocalizedString& dst);

		///
		/// Gets a single char* ('eastl::string8') value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// The value is a null-terminated char eastl::string.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetCString8(const PropertyList* pPropertyList, uint32_t propertyID, char*& dst);

		///
		/// Gets a single char16_t* ('eastl::string16') value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// The value is a null-terminated char16_t eastl::string.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetCString16(const PropertyList* pPropertyList, uint32_t propertyID, char16_t*& dst);

		///
		/// Gets a single eastl::string8 value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// This does the same as GetCString8, but wrapped inside an eastl::string8 class.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetString8(const PropertyList* pPropertyList, uint32_t propertyID, eastl::string& dst);

		///
		/// Gets a single eastl::string16 value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// This does the same as GetCString16, but wrapped inside an eastl::string16 class.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetString16(const PropertyList* pPropertyList, uint32_t propertyID, eastl::string16& dst);

		///
		/// Gets an array of bool values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayBool(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, bool*& dst);

		///
		/// Gets an array of int32_t values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayInt32(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, int*& dst);

		///
		/// Gets an array of uint32_t values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayUInt32(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, unsigned int*& dst);

		///
		/// Gets an array of float values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayFloat(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, float*& dst);

		///
		/// Gets an array of Math::Vector2 values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayVector2(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, Vector2*& dst);

		///
		/// Gets an array of Math::Vector3 values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayVector3(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, Vector3*& dst);

		///
		/// Gets an array of Math::Vector4 values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayVector4(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, Vector4*& dst);

		///
		/// Gets an array of Math::ColorRGB values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayColorRGB(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, ColorRGB*& dst);

		///
		/// Gets an array of ResourceKey values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayKey(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, ResourceKey*& dst);

		///
		/// Gets an array of char* ('eastl::string8') values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayString8(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, eastl::string8*& dst);

		///
		/// Gets an array of 'eastl::string16' values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayString16(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, eastl::string16*& dst);

		///
		/// Gets an array of EntityTransform values from a property with the propertyID specified in the given list.
		/// This type of property can only exist on array properties.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayTransform(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, Transform*& dst);


		///
		/// Gets an array of bool values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayBool(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<bool>& dst);

		///
		/// Gets an array of int32_t values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayInt32(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<int>& dst);

		///
		/// Gets an array of uint32_t values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayUInt32(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<uint32_t>& dst);

		///
		/// Gets an array of float values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayFloat(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<float>& dst);

		///
		/// Gets an array of Math::Vector2 values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayVector2(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<Vector2>& dst);

		///
		/// Gets an array of Math::Vector3 values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayVector3(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<Vector3>& dst);

		///
		/// Gets an array of Math::Vector4 values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayVector4(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<Vector4>& dst);

		///
		/// Gets an array of Math::ColorRGB values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayColorRGB(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<ColorRGB>& dst);

		///
		/// Gets an array of ResourceKey values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayKey(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<ResourceKey>& dst);

		///
		/// Gets an array of char* ('eastl::string8') values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayString8(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<eastl::string>& dst);

		///
		/// Gets an array of 'eastl::string16' values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayString16(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<eastl::string16>& dst);

		///
		/// Gets an array of EntityTransform values from a property with the propertyID specified in the given list.
		/// This type of property can only exist on array properties.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The vector where a copy of the values will be stored
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayTransform(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<Transform>& dst);



		///@}

	protected:
		void Clear(bool arg_0);

	protected:
		union UNNAMED(PropertyValues)
		{

			bool		mValueBool;
			int8_t		mValueInt8;
			uint8_t		mValueUInt8;
			int16_t		mValueInt16;
			uint16_t	mValueUInt16;
			int32_t		mValueInt32;
			uint32_t	mValueUInt32;
			// We can't add these ones; it adds unnecessary padding at the end of the class
			//int64_t		mValueInt64;
			//uint64_t		mValue;
			//double			mValue;
			float		mValueFloat;
			struct UNNAMED(PropertyResourceKey) { ResourceKey mValueKey; };
			struct UNNAMED(PropertyVector2) { Vector2	mValueVector2; };
			struct UNNAMED(PropertyVector3){ Vector3	mValueVector3; };
			struct UNNAMED(PropertyVector4) { Vector4	mValueVector4; };
			struct UNNAMED(PropertyColorRGB) { ColorRGB	mValueColorRGB; };
			struct UNNAMED(PropertyColorRGBA) { ColorRGBA	mValueColorRGBA; };

			struct UNNAMED(PropertyString8) { eastl::string8	mValueString8; };
			struct UNNAMED(PropertyString16) { eastl::string16	mValueString16; };

			struct UNNAMED(PropertyArray)
			{
				void* mpData;
				size_t mnItemSize;
				size_t mnItemCount;
			};
		};

	public:
		/* 10h */	short			mnFlags;
		/* 12h */	PropertyType	mnType;
	};
	ASSERT_SIZE(Property, 0x14);

	namespace Addresses(Property)
	{
		DeclareAddress(GetValueInt32);
		DeclareAddress(GetValueFloat);
		DeclareAddress(GetValueBool);
		DeclareAddress(GetValueUInt32);
		DeclareAddress(GetValueVector2);
		DeclareAddress(GetValueVector3);
		DeclareAddress(GetValueVector4);
		DeclareAddress(GetValueColorRGB);
		DeclareAddress(GetValueColorRGBA);
		DeclareAddress(GetValueKey);
		DeclareAddress(GetValueTransform);
		DeclareAddress(GetValueText);
		DeclareAddress(GetValueBBox);
		DeclareAddress(GetValueString8);
		DeclareAddress(GetValueString16);

		DeclareAddress(GetValueChar);
		DeclareAddress(GetValueWChar);
		DeclareAddress(GetValueInt8);
		DeclareAddress(GetValueUInt8);
		DeclareAddress(GetValueInt16);
		DeclareAddress(GetValueUInt16);
		DeclareAddress(GetValueInt64);
		DeclareAddress(GetValueUInt64);
		DeclareAddress(GetValueDouble);
		DeclareAddress(GetValueFlags);
		DeclareAddress(GetValue);


		DeclareAddress(Set);
		DeclareAddress(SetValueInt32);
		DeclareAddress(SetValueUInt32);
		DeclareAddress(SetValueKey);
		DeclareAddress(SetValueString8);
		DeclareAddress(SetValueString16);
		DeclareAddress(SetValueFloat);
		DeclareAddress(SetValueBool);
		DeclareAddress(SetValueBBox);
		DeclareAddress(SetValueVector2);
		DeclareAddress(SetValueVector3);
		DeclareAddress(SetValueVector4);
		DeclareAddress(SetValueColorRGB);
		DeclareAddress(SetValueColorRGBA);


		DeclareAddress(GetBool);
		DeclareAddress(GetFloat);
		DeclareAddress(GetInt32);
		DeclareAddress(GetUInt32);
		DeclareAddress(GetVector2);
		DeclareAddress(GetVector3);
		DeclareAddress(GetVector4);
		DeclareAddress(GetColorRGB);
		DeclareAddress(GetColorRGBA);
		DeclareAddress(GetKey);
		DeclareAddress(GetKeyInstanceID);
		DeclareAddress(GetKeyGroupID);
		DeclareAddress(GetKeyTypeID);
		DeclareAddress(GetText);
		DeclareAddress(GetCString8);
		DeclareAddress(GetCString16);
		DeclareAddress(GetString8);
		DeclareAddress(GetString16);

		DeclareAddress(GetArrayBool);
		DeclareAddress(GetArrayInt32);
		DeclareAddress(GetArrayUInt32);
		DeclareAddress(GetArrayFloat);
		DeclareAddress(GetArrayVector2);
		DeclareAddress(GetArrayVector3);
		DeclareAddress(GetArrayVector4);
		DeclareAddress(GetArrayColorRGB);
		DeclareAddress(GetArrayKey);
		DeclareAddress(GetArrayString8);
		DeclareAddress(GetArrayString16);
		DeclareAddress(GetArrayTransform);

		DeclareAddress(Clear);
	}

	inline Property::Property()
		: mnFlags(0)
		, mnType(PropertyType::None)
	{
	}

	inline Property::~Property()
	{
		if (mnFlags & 4)
		{
			Clear(false);
		}
	}

#ifndef SDK_TO_GHIDRA

	inline auto_METHOD_VOID(Property, Clear, Args(bool arg_0), Args(arg_0));

	inline auto_METHOD_(Property, int32_t*, GetValueInt32);
	inline auto_METHOD_(Property, float*, GetValueFloat);
	inline auto_METHOD_(Property, bool*, GetValueBool);
	inline auto_METHOD_(Property, uint32_t*, GetValueUInt32);
	inline auto_METHOD_(Property, Vector2*, GetValueVector2);
	inline auto_METHOD_(Property, Vector3*, GetValueVector3);
	inline auto_METHOD_(Property, Vector4*, GetValueVector4);
	inline auto_METHOD_(Property, ColorRGB*, GetValueColorRGB);
	inline auto_METHOD_(Property, ColorRGBA*, GetValueColorRGBA);
	inline auto_METHOD_(Property, ResourceKey*, GetValueKey);
	inline auto_METHOD_(Property, Transform*, GetValueTransform);
	inline auto_METHOD_(Property, LocalizedString*, GetValueText);
	inline auto_METHOD_(Property, BoundingBox*, GetValueBBox);
	inline auto_METHOD_(Property, eastl::string8*, GetValueString8);
	inline auto_METHOD_(Property, eastl::string16*, GetValueString16);

	// Unseen types:
	inline auto_METHOD_(Property, char*, GetValueChar);
	inline auto_METHOD_(Property, char16_t*, GetValueWChar);
	inline auto_METHOD_(Property, int8_t*, GetValueInt8);
	inline auto_METHOD_(Property, uint8_t*, GetValueUInt8);
	inline auto_METHOD_(Property, int16_t*, GetValueInt16);
	inline auto_METHOD_(Property, uint16_t*, GetValueUInt16);
	inline auto_METHOD_(Property, int64_t*, GetValueInt64);
	inline auto_METHOD_(Property, uint64_t*, GetValueUInt64);
	inline auto_METHOD_(Property, double*, GetValueDouble);
	inline auto_METHOD_(Property, void**, GetValueFlags);

	inline auto_METHOD_(Property, void*, GetValue);


	inline auto_METHOD(Property, bool, Set, Args(PropertyType type, int flags, void* pValue, size_t nValueSize, size_t nValueCount), Args(type, flags, pValue, nValueSize, nValueCount));
	inline auto_METHOD(Property, Property&, SetValueInt32, Args(const int32_t& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueUInt32, Args(const uint32_t& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueKey, Args(const ResourceKey& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueString8, Args(const eastl::string8& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueString16, Args(const eastl::string16& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueFloat, Args(const float& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueBool, Args(const bool& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueBBox, Args(const BoundingBox& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueVector2, Args(const Vector2& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueVector3, Args(const Vector3& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueVector4, Args(const Vector4& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueColorRGB, Args(const ColorRGB& value), Args(value));
	inline auto_METHOD(Property, Property&, SetValueColorRGBA, Args(const ColorRGBA& value), Args(value));


	inline auto_STATIC_METHOD(Property, bool, GetBool, Args(const PropertyList* prop, uint32_t propertyID, bool& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetFloat, Args(const PropertyList* prop, uint32_t propertyID, float& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetInt32, Args(const PropertyList* prop, uint32_t propertyID, int32_t& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetUInt32, Args(const PropertyList* prop, uint32_t propertyID, uint32_t& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetVector2, Args(const PropertyList* prop, uint32_t propertyID, Vector2& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetVector3, Args(const PropertyList* prop, uint32_t propertyID, Vector3& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetVector4, Args(const PropertyList* prop, uint32_t propertyID, Vector4& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetColorRGB, Args(const PropertyList* prop, uint32_t propertyID, ColorRGB& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetColorRGBA, Args(const PropertyList* prop, uint32_t propertyID, ColorRGBA& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetKey, Args(const PropertyList* prop, uint32_t propertyID, ResourceKey& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetKeyInstanceID, Args(const PropertyList* prop, uint32_t propertyID, uint32_t& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetKeyGroupID, Args(const PropertyList* prop, uint32_t propertyID, uint32_t& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetKeyTypeID, Args(const PropertyList* prop, uint32_t propertyID, uint32_t& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetText, Args(const PropertyList* prop, uint32_t propertyID, LocalizedString& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetCString8, Args(const PropertyList* prop, uint32_t propertyID, char*& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetCString16, Args(const PropertyList* prop, uint32_t propertyID, char16_t*& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetString8, Args(const PropertyList* prop, uint32_t propertyID, eastl::string& dst), Args(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetString16, Args(const PropertyList* prop, uint32_t propertyID, eastl::string16& dst), Args(prop, propertyID, dst));

	inline auto_STATIC_METHOD(Property, bool, GetArrayBool, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, bool*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayInt32, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, int32_t*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayUInt32, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, uint32_t*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayFloat, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, float*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayVector2, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, Vector2*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayVector3, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, Vector3*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayVector4, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, Vector4*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayColorRGB, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, ColorRGB*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayKey, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, ResourceKey*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayString8, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, eastl::string8*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayString16, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, eastl::string16*& dst), Args(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayTransform, Args(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, Transform*& dst), Args(prop, propertyID, dstCount, dst));
	//TODO Bounding boxes?


	inline Property& Property::SetArrayBool(const bool* pValues, size_t nValueCount) {
		Set(PropertyType::Bool, kPropertyFlagArray, (void*) pValues, sizeof(bool), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayInt32(const int32_t* pValues, size_t nValueCount) {
		Set(PropertyType::Int32, kPropertyFlagArray, (void*)pValues, sizeof(int32_t), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayUInt32(const uint32_t* pValues, size_t nValueCount) {
		Set(PropertyType::UInt32, kPropertyFlagArray, (void*)pValues, sizeof(uint32_t), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayFloat(const float* pValues, size_t nValueCount) {
		Set(PropertyType::Float, kPropertyFlagArray, (void*)pValues, sizeof(float), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayKey(const ResourceKey* pValues, size_t nValueCount) {
		Set(PropertyType::Key, kPropertyFlagArray, (void*)pValues, sizeof(ResourceKey), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayString8(const eastl::string8* pValues, size_t nValueCount) {
		Set(PropertyType::String8, kPropertyFlagArray, (void*)pValues, sizeof(eastl::string8), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayString16(const eastl::string16* pValues, size_t nValueCount) {
		Set(PropertyType::String16, kPropertyFlagArray, (void*)pValues, sizeof(eastl::string16), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayBBox(const BoundingBox* pValues, size_t nValueCount) {
		Set(PropertyType::BBox, kPropertyFlagArray, (void*)pValues, sizeof(BoundingBox), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayTransform(const Transform* pValues, size_t nValueCount) {
		Set(PropertyType::Transform, kPropertyFlagArray, (void*)pValues, sizeof(Transform), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayText(const LocalizedString* pValues, size_t nValueCount) {
		Set(PropertyType::Text, kPropertyFlagArray, (void*)pValues, sizeof(LocalizedString), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayVector2(const Vector2* pValues, size_t nValueCount) {
		Set(PropertyType::Vector2, kPropertyFlagArray, (void*)pValues, sizeof(Vector2), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayVector3(const Vector3* pValues, size_t nValueCount) {
		Set(PropertyType::Vector3, kPropertyFlagArray, (void*)pValues, sizeof(Vector3), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayVector4(const Vector4* pValues, size_t nValueCount) {
		Set(PropertyType::Vector4, kPropertyFlagArray, (void*)pValues, sizeof(Vector4), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayColorRGB(const ColorRGB* pValues, size_t nValueCount) {
		Set(PropertyType::ColorRGB, kPropertyFlagArray, (void*)pValues, sizeof(ColorRGB), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayColorRGBA(const ColorRGBA* pValues, size_t nValueCount) {
		Set(PropertyType::ColorRGBA, kPropertyFlagArray, (void*)pValues, sizeof(ColorRGBA), nValueCount);
		return *this;
	}


	inline bool Property::GetArrayBool(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<bool>& dst) {
		bool* data;
		size_t count;
		if (GetArrayBool(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<bool>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayInt32(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<int>& dst) {
		int* data;
		size_t count;
		if (GetArrayInt32(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<int>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayUInt32(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<uint32_t>& dst) {
		uint32_t* data;
		size_t count;
		if (GetArrayUInt32(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<uint32_t>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayFloat(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<float>& dst) {
		float* data;
		size_t count;
		if (GetArrayFloat(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<float>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayVector2(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<Vector2>& dst) {
		Vector2* data;
		size_t count;
		if (GetArrayVector2(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<Vector2>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayVector3(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<Vector3>& dst) {
		Vector3* data;
		size_t count;
		if (GetArrayVector3(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<Vector3>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayVector4(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<Vector4>& dst) {
		Vector4* data;
		size_t count;
		if (GetArrayVector4(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<Vector4>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayColorRGB(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<ColorRGB>& dst) {
		ColorRGB* data;
		size_t count;
		if (GetArrayColorRGB(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<ColorRGB>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayKey(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<ResourceKey>& dst) {
		ResourceKey* data;
		size_t count;
		if (GetArrayKey(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<ResourceKey>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayString8(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<eastl::string>& dst) {
		eastl::string* data;
		size_t count;
		if (GetArrayString8(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<eastl::string>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayString16(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<eastl::string16>& dst) {
		eastl::string16* data;
		size_t count;
		if (GetArrayString16(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<eastl::string16>(data, data + count);
			return true;
		}
		return false;
	}

	inline bool Property::GetArrayTransform(const PropertyList* pPropertyList, uint32_t propertyID, eastl::vector<Transform>& dst) {
		Transform* data;
		size_t count;
		if (GetArrayTransform(pPropertyList, propertyID, count, data)) {
			dst = eastl::vector<Transform>(data, data + count);
			return true;
		}
		return false;
	}

#endif
}