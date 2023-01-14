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

#include <Spore\Internal.h>
#include <Spore\App\PropertyList.h>

#define DirectPropertyListPtr eastl::intrusive_ptr<App::DirectPropertyList>

namespace App
{

	///
	/// A special kind of PropertyList that allows to have fast-access bool/int/float properties, apart from normal properties.
	///
	class DirectPropertyList : public PropertyList
	{
	public:

		DirectPropertyList(size_t nFastAccessCount);
		~DirectPropertyList();

		///
		/// Gets a fast-acesss bool property from this DirectPropertyList. 
		/// You MUST only use this for fast-access properties (those specified in SPPropertyIDs); trying to get other
		/// properties using this method will result in undefined behaviour. 
		/// To get non-fast-access properties from this list, use the static methods provided in the Property class.
		///
		bool GetDirectBool(uint32_t propertyID);

		///
		/// Gets a fast-acesss int property from this DirectPropertyList. 
		/// You MUST only use this for fast-access properties (those specified in SPPropertyIDs); trying to get other
		/// properties using this method will result in undefined behaviour. 
		/// To get non-fast-access properties from this list, use the static methods provided in the Property class.
		///
		int GetDirectInt(uint32_t propertyID);

		///
		/// Gets a fast-acesss float property from this DirectPropertyList. 
		/// You MUST only use this for fast-access properties (those specified in SPPropertyIDs); trying to get other
		/// properties using this method will result in undefined behaviour. 
		/// To get non-fast-access properties from this list, use the static methods provided in the Property class.
		///
		float GetDirectFloat(uint32_t propertyID);

		///
		/// Assigns the given bool value to the specified propertyID.
		/// The property will be stored as fast-access if propertyID is contained in SPPropertyIDs.
		///
		void SetBool(uint32_t propertyID, bool value);

		///
		/// Assigns the given int value to the specified propertyID.
		/// The property will be stored as fast-access if propertyID is contained in SPPropertyIDs.
		///
		void SetInt(uint32_t propertyID, int value);

		///
		/// Assigns the given float value to the specified propertyID.
		/// The property will be stored as fast-access if propertyID is contained in SPPropertyIDs.
		///
		void SetFloat(uint32_t propertyID, float value);


		// Overrided methods

		/* 14h */	virtual void SetProperty(uint32_t propertyID, const Property* pValue) override;
		/* 18h */	virtual int RemoveProperty(uint32_t propertyID) override;
		/* 1Ch */	virtual bool HasProperty(uint32_t propertyID) const override;
		/* 20h */	virtual bool GetPropertyAlt(uint32_t propertyID, Property*& result) const override;
		/* 24h */	virtual bool GetProperty(uint32_t propertyID, Property*& result) const override;
		/* 28h */	virtual Property* GetPropertyObject(uint32_t propertyID) const override;
		/* 2Ch */	virtual void CopyFrom(const PropertyList* pOther) override;
		/* 30h */	virtual void AddPropertiesFrom(const PropertyList* pOther) override;
		/* 34h */	virtual void CopyAllPropertiesFrom(const PropertyList* pOther) override;
		/* 38h */	virtual void AddAllPropertiesFrom(const PropertyList* pOther) override;
		/* 3Ch */	virtual bool Read(IO::IStream* pInputStream) override;
		/* 40h */	virtual bool Write(IO::IStream* pOutputStream) const override;
		/* 44h */	virtual void GetPropertyIDs(eastl::vector<uint32_t>& dst) const override;
		/* 48h */	virtual void Clear() override;

	protected:
		union DirectValue
		{
			bool mBoolValue;
			int mIntValue;
			float mFloatValue;
		};

	public:
		/* 38h */	size_t			mnFastAccessCount;
		/* 3Ch */	DirectValue*	mpValues;

	protected:
		/* 40h */	Property		mTemporaryProperty;

	};
	ASSERT_SIZE(DirectPropertyList, 0x54);

	namespace Addresses(DirectPropertyList)
	{
		DeclareAddress(SetProperty);
		DeclareAddress(RemoveProperty);
		DeclareAddress(HasProperty);
		DeclareAddress(GetPropertyAlt);
		DeclareAddress(GetProperty);
		DeclareAddress(GetPropertyObject);
		DeclareAddress(CopyFrom);
		DeclareAddress(AddPropertiesFrom);
		DeclareAddress(CopyAllPropertiesFrom);
		DeclareAddress(AddAllPropertiesFrom);
		DeclareAddress(Read);
		DeclareAddress(Write);
		DeclareAddress(GetPropertyIDs);
		DeclareAddress(Clear);

		DeclareAddress(SetBool);
		DeclareAddress(SetInt);
		DeclareAddress(SetFloat);
	}


	inline bool DirectPropertyList::GetDirectBool(uint32_t propertyID)
	{
		return mpValues[propertyID].mBoolValue;
	}

	inline int DirectPropertyList::GetDirectInt(uint32_t propertyID)
	{
		return mpValues[propertyID].mIntValue;
	}

	inline float DirectPropertyList::GetDirectFloat(uint32_t propertyID)
	{
		return mpValues[propertyID].mFloatValue;
	}

}