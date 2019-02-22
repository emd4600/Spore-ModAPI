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

#include <Spore\App\Property.h>
#include <Spore\IO\IStream.h>
#include <Spore\Resource\ResourceObject.h>
#include <EASTL\vector_map.h>
#include <EASTL\vector.h>


using namespace eastl;
using namespace Resource;

namespace App
{

	///
	/// PropertyList: A class that contains multiple properties. This is the representation of a .prop file.
	///
	/// PropertyLists store properties as a map, where an uint32_t (the property ID) is the key, and a Property is the value.
	/// The contents of a Property class vary depending on the property type and flags; therefore, it is recommended that, for
	/// retrieveing values from a property list, you use the static methods defined in the Property class, which are adapted
	/// to get specific types of values.
	///
	/// PropertyLists can have a parent; in that case, properties are also searched recursively in the parents. 
	///
	/// PropertyList inherits from ResourceObject, and therefore, is uniquely identified using a ResourceKey. 
	/// Use the class PropertyManager to get specific lists.
	///
	class PropertyList : public SpecialResourceObject
	{

	public:
		typedef vector_map<uint32_t, Property> PropertyMap;
		typedef intrusive_ptr<PropertyList> Pointer;

		PropertyList();
		virtual ~PropertyList() {};

		///
		/// Sets the value of the property with the given ID to the specified value.
		/// If no property with that ID exists in this list, a new one will be created and added to the list.
		/// This does not affect the parent PropertyList; this way you are ensured that the value modified will only 
		/// affect the current list.
		/// @param propertyID The ID of the property to add.
		/// @param pValue The value of the property, stored inside a Property object of the appropiate type.
		///
		/* 14h */	virtual void SetProperty(uint32_t propertyID, const Property* pValue);

		///
		/// Removes this propertyID and its value from the list.
		/// This does not affect the parent PropertyList.
		/// @param propertyID The ID of the property to remove.
		/// @returns true if the property was removed, false if it did not exist.
		///
		/* 18h */	virtual int RemoveProperty(uint32_t propertyID);

		///
		/// Tells whether a property with this propertyID is contained inside this list, or inside any of its parents.
		/// This funciton will be called recursively on the PropertyList's parents until the property is found (which returns true)
		/// or no parents are left to check (which returns false).
		/// @param propertyID The ID of the property to check whether it exists.
		///
		/* 1Ch */	virtual bool HasProperty(uint32_t propertyID) const;

		///
		/// This does the same as GetProperty(uint32_t, Property*&). It is rarely used.
		///
		/* 20h */	virtual bool GetPropertyAlt(uint32_t propertyID, Property*& result) const;

		///
		/// Gets the pointer to a Property with the given propertyID and assigns it to the parameter 'result'.
		/// If no property with that ID is found, the function will return false and 'result' will remain unmodified.
		/// This function will be called recursively on the PropertyList's parents until the property is found (which returns true)
		/// or no parents are left to check (which returns false).
		/// @param[in] propertyID The ID of the property to find.
		/// @param[out] result The destination that will be assigned with the pointer to the found property (if any).
		/// @returns true if the property was found, false otherwise.
		///
		/* 24h */	virtual bool GetProperty(uint32_t propertyID, Property*& result) const;

		///
		/// Gets the pointer to a Property with the given propertyID. This always returns a value:
		/// either the found property, or a default property object.
		/// However, using this method is not recommended, since there is no way to know if the returned property is the default one or not.
		/// Therefore, this method should only be used in cases where the value of the property does not really matter.
		/// This function will be called recursively on the PropertyList's parents until the property is found (which returns true)
		/// or no parents are left to check (which returns false).
		/// @param propertyID The ID of the property to get.
		///
		/* 28h */	virtual Property* GetPropertyObject(uint32_t propertyID) const;  // always returns something

		///
		/// Copies the properties and parent from pOther. After calling this method, this object will be identical to pOther
		/// (except for the ResourceKey name); that is, it will have the same properties and the same parent.
		/// @param pOther The PropertyList whose properties will be copied.
		///
		/* 2Ch */	virtual void CopyFrom(const PropertyList* pOther);

		///
		/// Copies all the properties from pOther to this property list.
		/// The existing properties will not be deleted; their values might get overrided if they are contained in pOther, however.
		/// @param pOther The PropertyList whose properties will be copied.
		///
		/* 30h */	virtual void AddPropertiesFrom(const PropertyList* pOther);

		///
		/// Copies all the properties from pOther. The existing properties will be removed.
		/// The properties will be copied recursively from every pOther parent, so you will end up with a similar result
		/// to void AddAllPropertiesFrom(PropertyList* pOther); the difference is that the existing properties will be removed.
		/// This PropertyList's parent will be set to null; this way is ensured that this object will end up having only the same
		/// properties as pOther and its parents.
		/// @param pOther The PropertyList whose properties will be copied.
		///
		/* 34h */	virtual void CopyAllPropertiesFrom(const PropertyList* pOther);

		///
		/// Similar to void CopyPropertiesFrom(PropertyList* pOther), but this copies all the properties from pOther parents as well.
		/// This method will be called recursively on pOther's parents until no parents are left, and then the properties from pOther will
		/// be copied. This ensure that pOther properties have priority over their parents'.
		/// @param pOther The PropertyList whose properties will be copied.
		///
		/* 38h */	virtual void AddAllPropertiesFrom(const PropertyList* pOther);

		///
		/// Fills this PropertyList with the information contained in the given IO::IStream, according to the PROP file format.
		/// If there's any error while reading the file, the operation will be interrupted, and no more properties will be read.
		/// @param pInputStream The IStream where the data will be read from.
		/// @returns true if everything could be successfully read, false otherwise.
		///
		/* 3Ch */	virtual bool Read(IO::IStream* pInputStream);

		///
		/// Writes this PropertyList into the given IO::IStream, according to the PROP file format. 
		/// If there's any error while writing the file, the operation will be interrupted, and no more properties will be written.
		/// @param pOutputStream The IStream where the data will be written.
		/// @returns true if everything could be successfully written, false otherwise.
		///
		/* 40h */	virtual bool Write(IO::IStream* pOutputStream) const;

		///
		/// Fills the given vector with all the property IDs contained in this PropertyList.
		/// This does not include the properties contained in the parent.
		/// @param[Out] dst A uint32_t vector where the IDs will be put.
		///
		/* 44h */	virtual void GetPropertyIDs(vector<uint32_t>& dst) const;

		///
		/// Removes all the properties from this PropertyList.
		///
		/* 48h */	virtual void Clear();


		///
		/// Changes the parent of this list. The 'parent' property will be changed accordingly.
		///
		void SetParent(PropertyList* pParent);

		enum
		{
			/// The default typeID used by .prop files.
			kPropTypeID = 0x00B1B104
		};

	protected:
		/* 18h */	PropertyMap				mProperties;
		/* 30h */	PropertyList::Pointer	mParent;
		/* 34h */	int						mnOperationsDone;  // I don't really know why this is used, but the add, remove, copy etc operations increase this
	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(PropertyList) == 0x38, "sizeof(PropertyList) must be 38h");

	namespace InternalAddressList(PropertyList)
	{
		DefineAddress(SetProperty, GetAddress(0x6A3070, 0x6A2E20, 0x6A2E20));
		DefineAddress(RemoveProperty, GetAddress(0x6A3140, 0x6A2EF0, 0x6A2EF0));
		DefineAddress(HasProperty, GetAddress(0x6A26C0, 0x6A2470, 0x6A2470));
		DefineAddress(GetPropertyAlt, GetAddress(0x6A2030, 0x6A1DE0, 0x6A1DE0));
		DefineAddress(GetProperty, GetAddress(0x6A2780, 0x6A2530, 0x6A2530));
		DefineAddress(GetPropertyObject, GetAddress(0x6A2720, 0x6A24D0, 0x6A24D0));
		DefineAddress(CopyFrom, GetAddress(0x6A2C90, 0x6A2A40, 0x6A2A40));
		DefineAddress(AddPropertiesFrom, GetAddress(0x6A3160, 0x6A2F10, 0x6A2F10));
		DefineAddress(CopyAllPropertiesFrom, GetAddress(0x6A1720, 0x6A14D0, 0x6A14D0));
		DefineAddress(AddAllPropertiesFrom, GetAddress(0x6A1760, 0x6A1510, 0x6A1510));
		DefineAddress(Read, GetAddress(0x6A31B0, 0x6A2F60, 0x6A2F60));
		DefineAddress(Write, GetAddress(0x6A1790, 0x6A1540, 0x6A1540));
		DefineAddress(GetPropertyIDs, GetAddress(0x6A32C0, 0x6A3070, 0x6A3070));
		DefineAddress(Clear, GetAddress(0x6A2CD0, 0x6A2A80, 0x6A2A80));

		DefineAddress(SetParent, GetAddress(0x6A1960, 0x6A1710, 0x6A1710));
	}
}