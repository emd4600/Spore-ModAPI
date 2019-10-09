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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>

namespace Simulator
{
	class cGameTerrainCursor
		: public cGameData
		, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x14A4EDC;
		static const uint32_t NOUN_ID = 0x18C40BC;

		typedef vector<intrusive_ptr<cSpatialObject>> SpatialObjects;

		using Object::Cast;
		using Object::AddRef;
		using Object::Release;

		/* 54h */	virtual cGameData* ToSpatialObject();
		/* 58h */	virtual void SetObjects(SpatialObjects* pVector);
		/* 5Ch */	virtual void func5Ch_(int);
		/* 60h */	virtual void func60h_(int, int);
		/* 64h */	virtual void func64h_();
		/// Returns the amount of values in the objects vector.
		/* 68h */	virtual int GetObjectsCount();
		/// Returns how many objects of the specified type are in the objects vector.
		/// @param type The object TYPE field.
		/* 6Ch */	virtual int GetObjectTypeCount(uint32_t type);
		/* 70h */	virtual int GetSelectedObjectCount();
		/* 74h */	virtual int UpdateSelectedObjectCount();
		/* 78h */	virtual int UpdateSelectedObjects();
		/* 7Ch */	virtual int func7Ch_(int, int);
		/* 80h */	virtual void func80h_(int, int);
		/* 84h */	virtual void SetAnchor(const Vector3& position);
		/* 88h */	virtual const Vector3& GetAnchor();
		/* 8Ch */	virtual void SetDiagonal1(const Vector3& position);
		/* 90h */	virtual const Vector3& GetDiagonal1();
		/* 94h */	virtual void SetDiagonal2(const Vector3& position);
		/* 98h */	virtual const Vector3& GetDiagonal2();
		/* 9Ch */	virtual int func9Ch_(int, int);
		/* A0h */	virtual void funcA0h(int, int);
		/* A4h */	virtual void ResetAnchors();
		/* A8h */	virtual bool IsAnchorValid();
		/* ACh */	virtual void SetRadius(float value);
		/* B0h */	virtual void SetAlpha(float value);
		/* B4h */	virtual float GetAlpha();
		/* B8h */	virtual void SetIsVisible(bool value);
		/* BCh */	virtual bool IsVisible();
		/* C0h */	virtual void SetAnchorValid(bool value);
		/* C4h */	virtual bool IsAnchorValid_();
		/* C8h */	virtual void funcC8h_();
		/* CCh */	virtual void SetIsFactoryObject(bool value);
		/* D0h */	virtual void funcD0h_(cSpatialObject*);
		/* D4h */	virtual cSpatialObject* funcD4h_();
		/* D8h */	virtual void SetIsRectangleSelect(bool value);
		/* DCh */	virtual bool IsRectangleSelect();
		/* E0h */	virtual void funcE0h_(bool);
		/* E4h */	virtual bool funcE4h_();

		static cGameTerrainCursor* GetTerrainCursor();

	public:
		/* 108h */	Vector3 mPosition;
		/* 114h */	Vector3 mAnchorPosition;
		/* 120h */	Vector3 mDiagonalPosition1;
		/* 12Ch */	Vector3 mDiagonalPosition2;
		/* 138h */	Quaternion mOrientation;
		/* 148h */	float mRadius;
		/* 14Ch */	float mAlpha;
		/* 150h */	bool mbRectangleSelect;  // true
		/* 154h */	int field_154;
		/* 158h */	bool field_158;
		/* 159h */	bool mbIsVisible;
		/* 15Ah */	bool mbIsFactoryObject;  // true
		/* 15Ch */	int mSelectedObjectCount;
		/* 160h */	bool mbAnchorValid;
		/* 164h */	SpatialObjects* mpObjects;
		/* 168h */	intrusive_ptr<cSpatialObject> field_168;
	};

	namespace Addresses(cGameTerrainCursor)
	{
		DeclareAddress(GetTerrainCursor, SelectAddress(0xB30BE0, NO_ADDRESS, 0xB30EB0));
	}
}