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
		, mParent(nullptr)
		, mnOperationsDone(0)
	{

	}

	auto_METHOD_VOID(PropertyList, SetProperty, PARAMS(uint32_t propertyID, const Property* pValue), PARAMS(propertyID, pValue));
	auto_METHOD(PropertyList, int, RemoveProperty, PARAMS(uint32_t propertyID), PARAMS(propertyID));
	auto_METHOD_const(PropertyList, bool, HasProperty, PARAMS(uint32_t propertyID), PARAMS(propertyID));
	auto_METHOD_const(PropertyList, bool, GetPropertyAlt, PARAMS(uint32_t propertyID, Property*& result), PARAMS(propertyID, result));
	auto_METHOD_const(PropertyList, bool, GetProperty, PARAMS(uint32_t propertyID, Property*& result), PARAMS(propertyID, result));
	auto_METHOD_const(PropertyList, Property*, GetPropertyObject, PARAMS(uint32_t propertyID), PARAMS(propertyID));
	auto_METHOD_VOID(PropertyList, CopyFrom, PARAMS(const PropertyList* pOther), PARAMS(pOther));
	auto_METHOD_VOID(PropertyList, AddPropertiesFrom, PARAMS(const PropertyList* pOther), PARAMS(pOther));
	auto_METHOD_VOID(PropertyList, CopyAllPropertiesFrom, PARAMS(const PropertyList* pOther), PARAMS(pOther));
	auto_METHOD_VOID(PropertyList, AddAllPropertiesFrom, PARAMS(const PropertyList* pOther), PARAMS(pOther));
	auto_METHOD(PropertyList, bool, Read, PARAMS(IO::IStream* pInputStream), PARAMS(pInputStream));
	auto_METHOD_const(PropertyList, bool, Write, PARAMS(IO::IStream* pOutputStream), PARAMS(pOutputStream));
	auto_METHOD_VOID_const(PropertyList, GetPropertyIDs, PARAMS(vector<uint32_t>& dst), PARAMS(dst));
	auto_METHOD_VOID_(PropertyList, Clear);

	auto_METHOD_VOID(PropertyList, SetParent, PARAMS(PropertyList* pParent), PARAMS(pParent));



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


	auto_METHOD_VOID(DirectPropertyList, SetBool, PARAMS(uint32_t propertyID, bool value), PARAMS(propertyID, value));
	auto_METHOD_VOID(DirectPropertyList, SetInt, PARAMS(uint32_t propertyID, int value), PARAMS(propertyID, value));
	auto_METHOD_VOID(DirectPropertyList, SetFloat, PARAMS(uint32_t propertyID, float value), PARAMS(propertyID, value));

	auto_METHOD_VOID(DirectPropertyList, SetProperty, PARAMS(uint32_t propertyID, const Property* pValue), PARAMS(propertyID, pValue));
	auto_METHOD(DirectPropertyList, int, RemoveProperty, PARAMS(uint32_t propertyID), PARAMS(propertyID));
	auto_METHOD_const(DirectPropertyList, bool, HasProperty, PARAMS(uint32_t propertyID), PARAMS(propertyID));
	auto_METHOD_const(DirectPropertyList, bool, GetPropertyAlt, PARAMS(uint32_t propertyID, Property*& result), PARAMS(propertyID, result));
	auto_METHOD_const(DirectPropertyList, bool, GetProperty, PARAMS(uint32_t propertyID, Property*& result), PARAMS(propertyID, result));
	auto_METHOD_const(DirectPropertyList, Property*, GetPropertyObject, PARAMS(uint32_t propertyID), PARAMS(propertyID));
	auto_METHOD_VOID(DirectPropertyList, CopyFrom, PARAMS(const PropertyList* pOther), PARAMS(pOther));
	auto_METHOD_VOID(DirectPropertyList, AddPropertiesFrom, PARAMS(const PropertyList* pOther), PARAMS(pOther));
	auto_METHOD_VOID(DirectPropertyList, CopyAllPropertiesFrom, PARAMS(const PropertyList* pOther), PARAMS(pOther));
	auto_METHOD_VOID(DirectPropertyList, AddAllPropertiesFrom, PARAMS(const PropertyList* pOther), PARAMS(pOther));
	auto_METHOD(DirectPropertyList, bool, Read, PARAMS(IO::IStream* pInputStream), PARAMS(pInputStream));
	auto_METHOD_const(DirectPropertyList, bool, Write, PARAMS(IO::IStream* pOutputStream), PARAMS(pOutputStream));
	auto_METHOD_VOID_const(DirectPropertyList, GetPropertyIDs, PARAMS(vector<uint32_t>& dst), PARAMS(dst));
	auto_METHOD_VOID_(DirectPropertyList, Clear);
}