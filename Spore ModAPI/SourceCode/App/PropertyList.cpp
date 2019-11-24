#ifndef MODAPI_DLL_EXPORT
/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\App\PropertyList.h>
#include <Spore\App\DirectPropertyList.h>

namespace App
{
	PropertyList::PropertyList()
		: mProperties()
		, mpParent(nullptr)
		, mnOperationsDone(0)
	{

	}

	auto_METHOD_VOID(PropertyList, SetProperty, Args(uint32_t propertyID, const Property* pValue), Args(propertyID, pValue));
	auto_METHOD(PropertyList, int, RemoveProperty, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_const(PropertyList, bool, HasProperty, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_const(PropertyList, bool, GetPropertyAlt, Args(uint32_t propertyID, Property*& result), Args(propertyID, result));
	auto_METHOD_const(PropertyList, bool, GetProperty, Args(uint32_t propertyID, Property*& result), Args(propertyID, result));
	auto_METHOD_const(PropertyList, Property*, GetPropertyObject, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_VOID(PropertyList, CopyFrom, Args(const PropertyList* pOther), Args(pOther));
	auto_METHOD_VOID(PropertyList, AddPropertiesFrom, Args(const PropertyList* pOther), Args(pOther));
	auto_METHOD_VOID(PropertyList, CopyAllPropertiesFrom, Args(const PropertyList* pOther), Args(pOther));
	auto_METHOD_VOID(PropertyList, AddAllPropertiesFrom, Args(const PropertyList* pOther), Args(pOther));
	auto_METHOD(PropertyList, bool, Read, Args(IO::IStream* pInputStream), Args(pInputStream));
	auto_METHOD_const(PropertyList, bool, Write, Args(IO::IStream* pOutputStream), Args(pOutputStream));
	auto_METHOD_VOID_const(PropertyList, GetPropertyIDs, Args(vector<uint32_t>& dst), Args(dst));
	auto_METHOD_VOID_(PropertyList, Clear);

	auto_METHOD_VOID(PropertyList, SetParent, Args(PropertyList* pParent), Args(pParent));



	DirectPropertyList::DirectPropertyList(size_t nFastAccessCount)
		: mTemporaryProperty()
		, mnFastAccessCount(nFastAccessCount)
	{
		mpValues = new DirectValue[nFastAccessCount];
		memset(mpValues, 0, sizeof(DirectValue) * nFastAccessCount);
	}
	DirectPropertyList::~DirectPropertyList()
	{
		delete mpValues;
	}


	auto_METHOD_VOID(DirectPropertyList, SetBool, Args(uint32_t propertyID, bool value), Args(propertyID, value));
	auto_METHOD_VOID(DirectPropertyList, SetInt, Args(uint32_t propertyID, int value), Args(propertyID, value));
	auto_METHOD_VOID(DirectPropertyList, SetFloat, Args(uint32_t propertyID, float value), Args(propertyID, value));

	auto_METHOD_VOID(DirectPropertyList, SetProperty, Args(uint32_t propertyID, const Property* pValue), Args(propertyID, pValue));
	auto_METHOD(DirectPropertyList, int, RemoveProperty, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_const(DirectPropertyList, bool, HasProperty, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_const(DirectPropertyList, bool, GetPropertyAlt, Args(uint32_t propertyID, Property*& result), Args(propertyID, result));
	auto_METHOD_const(DirectPropertyList, bool, GetProperty, Args(uint32_t propertyID, Property*& result), Args(propertyID, result));
	auto_METHOD_const(DirectPropertyList, Property*, GetPropertyObject, Args(uint32_t propertyID), Args(propertyID));
	auto_METHOD_VOID(DirectPropertyList, CopyFrom, Args(const PropertyList* pOther), Args(pOther));
	auto_METHOD_VOID(DirectPropertyList, AddPropertiesFrom, Args(const PropertyList* pOther), Args(pOther));
	auto_METHOD_VOID(DirectPropertyList, CopyAllPropertiesFrom, Args(const PropertyList* pOther), Args(pOther));
	auto_METHOD_VOID(DirectPropertyList, AddAllPropertiesFrom, Args(const PropertyList* pOther), Args(pOther));
	auto_METHOD(DirectPropertyList, bool, Read, Args(IO::IStream* pInputStream), Args(pInputStream));
	auto_METHOD_const(DirectPropertyList, bool, Write, Args(IO::IStream* pOutputStream), Args(pOutputStream));
	auto_METHOD_VOID_const(DirectPropertyList, GetPropertyIDs, Args(vector<uint32_t>& dst), Args(dst));
	auto_METHOD_VOID_(DirectPropertyList, Clear);
}
#endif
