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
		kNone = 0,
		kBool = 1,
		kInt32 = 9,
		kUInt32 = 0x0a,
		kFloat = 0x0d,
		kString8 = 0x12,
		kString16 = 0x13,
		kKey = 0x20,
		kText = 0x22,
		kVector2 = 0x30,
		kVector3 = 0x31,
		kColorRGB = 0x32,
		kVector4 = 0x33,
		kColorRGBA = 0x34,
		kTransform = 0x38,
		kBBox = 0x39,
		// Unseen types
		kChar = 0x0002,
		kWChar = 0x0003,
		kInt8 = 0x0005,
		kUInt8 = 0x0006,
		kInt16 = 0x0007,
		kUInt16 = 0x0008,
		kInt64 = 0x000B,
		kUInt64 = 0x000C,
		kDouble = 0x000E,
		kPtr = 0x000F,
		// only this one is used in Spore code, but not in files
		kVoid = 0x0010,
		kIUnknownRC = 0x0011,
		kFlags = 0x0021,
		kMatrix2 = 0x0035,
		kMatrix3 = 0x0036,
		kMatrix4 = 0x0037
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
		enum PropertyFlags
		{
			kPropertyFlagNotDirect = 0x10,
			kPropertyFlagArray = 0x30
		};

	public:
		Property();
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
		/// Returns a pointer to the wchar_t value(s) of this property.
		/// If the property is not of the specified type, a pointer to a default value will be returned.
		///
		wchar_t* GetValueWChar();

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
		/// This will be a single-valued string8 property.
		/// @param value
		///
		Property& SetValueString8(const eastl::string8& value);

		///
		/// Sets the value of this Property to the given eastl::string16 value.
		/// This will be a single-valued string16 property.
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
		/// This will be an array string8 property of 'nValueCount' values.
		/// @param pValues The array with the values.
		/// @param nValueCount How many values the array has.
		///
		Property& SetArrayString8(const eastl::string8* pValues, size_t nValueCount);

		///
		/// Sets the value of this Property to an array of eastl::string16 values.
		/// This will be an array string16 property of 'nValueCount' values.
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
		/// Gets a single char* ('string8') value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// The value is a null-terminated char string.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetCString8(const PropertyList* pPropertyList, uint32_t propertyID, char*& dst);

		///
		/// Gets a single wchar_t* ('string16') value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// The value is a null-terminated wchar_t string.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetCString16(const PropertyList* pPropertyList, uint32_t propertyID, wchar_t*& dst);

		///
		/// Gets a single string8 value from a property with the propertyID specified in the given list.
		/// If it is an array property, it will return the first value in the array.
		/// This does the same as GetCString8, but wrapped inside an eastl::string8 class.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dst The destination value that will be assigned with the value found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetString8(const PropertyList* pPropertyList, uint32_t propertyID, eastl::string& dst);

		///
		/// Gets a single string16 value from a property with the propertyID specified in the given list.
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
		/// Gets an array of char* ('string8') values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// The values are null-terminated char strings.
		/// @param[in] pPropertyList The PropertyList where this property will be searched.
		/// @param[in] propertyID The unique identifier of the property to find.
		/// @param[out] dstCount The destination size_t that will be assigned with the number of values found.
		/// @param[out] dst The destination pointer that will be assigned with the array of values found, if any.
		/// @returns True if a property of the required type and propertyID was found, false otherwise.
		///
		static bool GetArrayString8(const PropertyList* pPropertyList, uint32_t propertyID, size_t& dstCount, eastl::string8*& dst);

		///
		/// Gets an array of wchar_t* ('string16') values from a property with the propertyID specified in the given list.
		/// If it is not an array property, a pointer to the single value will be returned.
		/// The values are null-terminated wchar_t strings.
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

		///@}

	protected:
		void Clear(bool arg_0);

	protected:
		union
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
			struct { ResourceKey mValueKey; };
			struct { Vector2	mValueVector2; };
			struct { Vector3	mValueVector3; };
			struct { Vector4	mValueVector4; };
			struct { ColorRGB	mValueColorRGB; };
			struct { ColorRGBA	mValueColorRGBA; };

			struct { eastl::string8	mValueString8; };
			struct { eastl::string16	mValueString16; };

			struct
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

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(Property) == 0x14, "sizeof(Property) != 14h");

	namespace InternalAddressList(Property)
	{
		DefineAddress(GetValueInt32, GetAddress(0x41ECF0, 0x41E950, 0x41E950));
		DefineAddress(GetValueFloat, GetAddress(0x41EDD0, 0x41EA30, 0x41EA30));
		DefineAddress(GetValueBool, GetAddress(0x41EC80, 0x41E8E0, 0x41E8E0));
		DefineAddress(GetValueUInt32, GetAddress(0x41ED60, 0x41E9C0, 0x41E9C0));
		DefineAddress(GetValueVector2, GetAddress(0x6A11C0, 0x6A0F70, 0x6A0F70));
		DefineAddress(GetValueVector3, GetAddress(0xCCE1D0, 0xCCEA40, 0xCCEA90));
		DefineAddress(GetValueVector4, GetAddress(0x6A11F0, 0x6A0FA0, 0x6A0FA0));
		DefineAddress(GetValueColorRGB, GetAddress(0x6A1220, 0x6A0FD0, 0x6A0FD0));
		DefineAddress(GetValueColorRGBA, GetAddress(0x6A1250, 0x6A1000, 0x6A1000));
		DefineAddress(GetValueKey, GetAddress(0x6A1280, 0x6A1030, 0x6A1030));
		DefineAddress(GetValueTransform, GetAddress(0x6A12B0, 0x6A1060, 0x6A1060));
		DefineAddress(GetValueText, GetAddress(0x6A12E0, 0x6A1090, 0x6A1090));
		DefineAddress(GetValueBBox, GetAddress(0x6A3B10, 0x5F23A0, 0x5F23A0));
		DefineAddress(GetValueString8, GetAddress(0x60ED10, 0x60EF30, 0x60EF10));
		DefineAddress(GetValueString16, GetAddress(0x68A740, 0x68A4E0, 0x68A4E0));

		DefineAddress(GetValueChar, GetAddress(0x6A3930, 0x6A36E0, 0x6A36E0));
		DefineAddress(GetValueWChar, GetAddress(0x6A3960, 0x6A3710, 0x6A3710));
		DefineAddress(GetValueInt8, GetAddress(0x6A3990, 0x6A3740, 0x6A3740));
		DefineAddress(GetValueUInt8, GetAddress(0x6A39C0, 0x6A3770, 0x6A3770));
		DefineAddress(GetValueInt16, GetAddress(0x6A39F0, 0x6A37A0, 0x6A37A0));
		DefineAddress(GetValueUInt16, GetAddress(0x6A2E20, 0x6A37D0, 0x6A37D0));
		DefineAddress(GetValueInt64, GetAddress(0x6A3A50, 0x6A3800, 0x6A3800));
		DefineAddress(GetValueUInt64, GetAddress(0x6A3A80, 0x6A3830, 0x6A3830));
		DefineAddress(GetValueDouble, GetAddress(0x6A3AB0, 0x6A3860, 0x6A3860));
		DefineAddress(GetValueFlags, GetAddress(0x6A3AE0, 0x6A3890, 0x6A3890));
		DefineAddress(GetValue, GetAddress(0x447140, 0x4474C0, 0x4474C0));


		DefineAddress(Set, GetAddress(0x93E250, 0x93DCF0, 0x93DCF0));
		DefineAddress(SetValueInt32, GetAddress(0x422E10, 0x422EB0, 0x422EB0));
		DefineAddress(SetValueUInt32, GetAddress(0x428400, 0x428010, 0x428010));
		DefineAddress(SetValueKey, GetAddress(0x422EA0, 0x422F40, 0x422F40));
		DefineAddress(SetValueString8, GetAddress(0x4B59E0, 0x4B62F0, 0x4B62F0));
		DefineAddress(SetValueString16, GetAddress(0x427E60, 0x427A10, 0x427A10));
		DefineAddress(SetValueFloat, GetAddress(0x428490, 0x4280A0, 0x4280A0));
		DefineAddress(SetValueBool, GetAddress(0x422D80, 0x422E20, 0x422E20));
		DefineAddress(SetValueBBox, GetAddress(0x4781B0, 0x478800, 0x478800));
		DefineAddress(SetValueVector2, GetAddress(0x6A3760, 0x6A3510, 0x6A3510));
		DefineAddress(SetValueVector3, GetAddress(0x6A37C0, 0x6A3570, 0x6A3570));
		DefineAddress(SetValueVector4, GetAddress(0x6A3830, 0x6A35E0, 0x6A35E0));
		DefineAddress(SetValueColorRGB, GetAddress(0x6A3860, 0x6A3610, 0x6A3610));
		DefineAddress(SetValueColorRGBA, GetAddress(0x6A38D0, 0x6A3680, 0x6A3680));


		DefineAddress(GetBool, GetAddress(0x407140, 0x407190, 0x407190));
		DefineAddress(GetFloat, GetAddress(0x40CE70, 0x40CF10, 0x40CF10));
		DefineAddress(GetInt32, GetAddress(0x410290, 0x410330, 0x410330));
		DefineAddress(GetUInt32, GetAddress(0x4AF0A0, 0x4AF730, 0x4AF730));
		DefineAddress(GetVector2, GetAddress(0x6A1310, 0x6A10C0, 0x6A10C0));
		DefineAddress(GetVector3, GetAddress(0x6A1360, 0x6A1110, 0x6A1110));
		DefineAddress(GetVector4, GetAddress(0x6A13B0, 0x6A1160, 0x6A1160));
		DefineAddress(GetColorRGB, GetAddress(0x6A1400, 0x6A11B0, 0x6A11B0));
		DefineAddress(GetColorRGBA, GetAddress(0x6A1450, 0x6A1200, 0x6A1200));
		DefineAddress(GetKey, GetAddress(0x6A14A0, 0x6A1250, 0x6A1250));
		DefineAddress(GetKeyInstanceID, GetAddress(0x6A14F0, 0x6A12A0, 0x6A12A0));
		DefineAddress(GetKeyGroupID, GetAddress(0x6A1530, 0x6A12E0, 0x6A12E0));
		DefineAddress(GetKeyTypeID, GetAddress(0x6A1570, 0x6A1320, 0x6A1320));
		DefineAddress(GetText, GetAddress(0x6A15B0, 0x6A1360, 0x6A1360));
		DefineAddress(GetCString8, GetAddress(0x6A16A0, 0x6A1450, 0x6A1450));
		DefineAddress(GetCString16, GetAddress(0x6A16E0, 0x6A1490, 0x6A1490));
		DefineAddress(GetString8, GetAddress(0x6A1600, 0x6A13B0, 0x6A13B0));
		DefineAddress(GetString16, GetAddress(0x6A1650, 0x6A1400, 0x6A1400));

		DefineAddress(GetArrayBool, GetAddress(0x6A09B0, 0x6A0760, 0x6A0760));
		DefineAddress(GetArrayInt32, GetAddress(0x6A0A20, 0x6A07D0, 0x6A07D0));
		DefineAddress(GetArrayUInt32, GetAddress(0x6A0A90, 0x6A0840, 0x6A0840));
		DefineAddress(GetArrayFloat, GetAddress(0x6A0B00, 0x6A08B0, 0x6A08B0));
		DefineAddress(GetArrayVector2, GetAddress(0x6A0B70, 0x6A0920, 0x6A0920));
		DefineAddress(GetArrayVector3, GetAddress(0x6A0BE0, 0x6A0990, 0x6A0990));
		DefineAddress(GetArrayVector4, GetAddress(0x6A0C50, 0x6A0A00, 0x6A0A00));
		DefineAddress(GetArrayColorRGB, GetAddress(0x6A0CC0, 0x6A0A70, 0x6A0A70));
		DefineAddress(GetArrayKey, GetAddress(0x6A0D30, 0x6A0AE0, 0x6A0AE0));
		DefineAddress(GetArrayString8, GetAddress(0x6A0DA0, 0x6A0B50, 0x6A0B50));
		DefineAddress(GetArrayString16, GetAddress(0x6A0E10, 0x6A0BC0, 0x6A0BC0));
		DefineAddress(GetArrayTransform, GetAddress(0x6A0E80, 0x6A0C30, 0x6A0C30));

		DefineAddress(Clear, GetAddress(0x93E0A0, 0x93DAF0, 0x93DAF0));
	}

	inline Property::Property()
		: mnFlags(0)
		, mnType(PropertyType::kNone)
	{
	}

	inline Property::~Property()
	{
		if (mnFlags & 4)
		{
			Clear(false);
		}
	}

	inline auto_METHOD_VOID(Property, Clear, PARAMS(bool arg_0), PARAMS(arg_0));

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
	inline auto_METHOD_(Property, wchar_t*, GetValueWChar);
	inline auto_METHOD_(Property, int8_t*, GetValueInt8);
	inline auto_METHOD_(Property, uint8_t*, GetValueUInt8);
	inline auto_METHOD_(Property, int16_t*, GetValueInt16);
	inline auto_METHOD_(Property, uint16_t*, GetValueUInt16);
	inline auto_METHOD_(Property, int64_t*, GetValueInt64);
	inline auto_METHOD_(Property, uint64_t*, GetValueUInt64);
	inline auto_METHOD_(Property, double*, GetValueDouble);
	inline auto_METHOD_(Property, void**, GetValueFlags);

	inline auto_METHOD_(Property, void*, GetValue);


	inline auto_METHOD(Property, bool, Set, PARAMS(PropertyType type, int flags, void* pValue, size_t nValueSize, size_t nValueCount), PARAMS(type, flags, pValue, nValueSize, nValueCount));
	inline auto_METHOD(Property, Property&, SetValueInt32, PARAMS(const int32_t& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueUInt32, PARAMS(const uint32_t& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueKey, PARAMS(const ResourceKey& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueString8, PARAMS(const eastl::string8& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueString16, PARAMS(const eastl::string16& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueFloat, PARAMS(const float& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueBool, PARAMS(const bool& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueBBox, PARAMS(const BoundingBox& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueVector2, PARAMS(const Vector2& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueVector3, PARAMS(const Vector3& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueVector4, PARAMS(const Vector4& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueColorRGB, PARAMS(const ColorRGB& value), PARAMS(value));
	inline auto_METHOD(Property, Property&, SetValueColorRGBA, PARAMS(const ColorRGBA& value), PARAMS(value));


	inline auto_STATIC_METHOD(Property, bool, GetBool, PARAMS(const PropertyList* prop, uint32_t propertyID, bool& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetFloat, PARAMS(const PropertyList* prop, uint32_t propertyID, float& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetInt32, PARAMS(const PropertyList* prop, uint32_t propertyID, int32_t& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetUInt32, PARAMS(const PropertyList* prop, uint32_t propertyID, uint32_t& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetVector2, PARAMS(const PropertyList* prop, uint32_t propertyID, Vector2& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetVector3, PARAMS(const PropertyList* prop, uint32_t propertyID, Vector3& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetVector4, PARAMS(const PropertyList* prop, uint32_t propertyID, Vector4& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetColorRGB, PARAMS(const PropertyList* prop, uint32_t propertyID, ColorRGB& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetColorRGBA, PARAMS(const PropertyList* prop, uint32_t propertyID, ColorRGBA& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetKey, PARAMS(const PropertyList* prop, uint32_t propertyID, ResourceKey& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetKeyInstanceID, PARAMS(const PropertyList* prop, uint32_t propertyID, uint32_t& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetKeyGroupID, PARAMS(const PropertyList* prop, uint32_t propertyID, uint32_t& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetKeyTypeID, PARAMS(const PropertyList* prop, uint32_t propertyID, uint32_t& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetText, PARAMS(const PropertyList* prop, uint32_t propertyID, LocalizedString& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetCString8, PARAMS(const PropertyList* prop, uint32_t propertyID, char*& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetCString16, PARAMS(const PropertyList* prop, uint32_t propertyID, wchar_t*& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetString8, PARAMS(const PropertyList* prop, uint32_t propertyID, eastl::string& dst), PARAMS(prop, propertyID, dst));
	inline auto_STATIC_METHOD(Property, bool, GetString16, PARAMS(const PropertyList* prop, uint32_t propertyID, eastl::string16& dst), PARAMS(prop, propertyID, dst));

	inline auto_STATIC_METHOD(Property, bool, GetArrayBool, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, bool*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayInt32, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, int32_t*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayUInt32, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, uint32_t*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayFloat, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, float*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayVector2, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, Vector2*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayVector3, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, Vector3*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayVector4, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, Vector4*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayColorRGB, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, ColorRGB*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayKey, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, ResourceKey*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayString8, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, eastl::string8*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayString16, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, eastl::string16*& dst), PARAMS(prop, propertyID, dstCount, dst));
	inline auto_STATIC_METHOD(Property, bool, GetArrayTransform, PARAMS(const PropertyList* prop, uint32_t propertyID, size_t& dstCount, Transform*& dst), PARAMS(prop, propertyID, dstCount, dst));
	//TODO Bounding boxes?


	inline Property& Property::SetArrayBool(const bool* pValues, size_t nValueCount) {
		Set(PropertyType::kBool, kPropertyFlagArray, (void*) pValues, sizeof(bool), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayInt32(const int32_t* pValues, size_t nValueCount) {
		Set(PropertyType::kInt32, kPropertyFlagArray, (void*)pValues, sizeof(int32_t), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayUInt32(const uint32_t* pValues, size_t nValueCount) {
		Set(PropertyType::kUInt32, kPropertyFlagArray, (void*)pValues, sizeof(uint32_t), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayFloat(const float* pValues, size_t nValueCount) {
		Set(PropertyType::kFloat, kPropertyFlagArray, (void*)pValues, sizeof(float), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayKey(const ResourceKey* pValues, size_t nValueCount) {
		Set(PropertyType::kKey, kPropertyFlagArray, (void*)pValues, sizeof(ResourceKey), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayString8(const eastl::string8* pValues, size_t nValueCount) {
		Set(PropertyType::kString8, kPropertyFlagArray, (void*)pValues, sizeof(eastl::string8), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayString16(const eastl::string16* pValues, size_t nValueCount) {
		Set(PropertyType::kString16, kPropertyFlagArray, (void*)pValues, sizeof(eastl::string16), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayBBox(const BoundingBox* pValues, size_t nValueCount) {
		Set(PropertyType::kBBox, kPropertyFlagArray, (void*)pValues, sizeof(BoundingBox), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayTransform(const Transform* pValues, size_t nValueCount) {
		Set(PropertyType::kTransform, kPropertyFlagArray, (void*)pValues, sizeof(Transform), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayText(const LocalizedString* pValues, size_t nValueCount) {
		Set(PropertyType::kText, kPropertyFlagArray, (void*)pValues, sizeof(LocalizedString), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayVector2(const Vector2* pValues, size_t nValueCount) {
		Set(PropertyType::kVector2, kPropertyFlagArray, (void*)pValues, sizeof(Vector2), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayVector3(const Vector3* pValues, size_t nValueCount) {
		Set(PropertyType::kVector3, kPropertyFlagArray, (void*)pValues, sizeof(Vector3), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayVector4(const Vector4* pValues, size_t nValueCount) {
		Set(PropertyType::kVector4, kPropertyFlagArray, (void*)pValues, sizeof(Vector4), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayColorRGB(const ColorRGB* pValues, size_t nValueCount) {
		Set(PropertyType::kColorRGB, kPropertyFlagArray, (void*)pValues, sizeof(ColorRGB), nValueCount);
		return *this;
	}
	inline Property& Property::SetArrayColorRGBA(const ColorRGBA* pValues, size_t nValueCount) {
		Set(PropertyType::kColorRGBA, kPropertyFlagArray, (void*)pValues, sizeof(ColorRGBA), nValueCount);
		return *this;
	}
}