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

#include <Spore\Object.h>
#include <Spore\MathUtils.h>

#include <Spore\Graphics\ModelAsset.h>
#include <Spore\Graphics\IModelWorld.h>

#include <Spore\Simulator\Serialization.h>

#include <EASTL\vector.h>
#include <EASTL\string.h>

#define cSpatialObjectPtr intrusive_ptr<Simulator::cSpatialObject>

namespace Simulator
{
	using namespace Math;

	/// A 3D model in the Simulator. This class is inherit by all classes that have a visual representation,
	/// and therefore need a position, orientation, and scale in 3D space. Models are identified by a 
	/// ResourceKey (using the SetModelKey() and GetModelKey() methods). The graphical model itself is 
	/// loaded in the SetModelWorld() method.
	class cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x1186577;  // 0x7BBC4FF as well?

		// loc_D315AE creature movement?

		/* 00h */	virtual void cSpatialObject_func00h(int);
		/* 04h */	virtual int cSpatialObject_func04h();
		/* 08h */	virtual int cSpatialObject_func08h();
		/* 0Ch */	virtual ~cSpatialObject();

		/// Sets this model as invisible in its IModelWorld and sets the model and model world to nullptr.
		/// It also resets all necessary parameters.
		/* 10h */	virtual void Reset();

		/* 14h */	virtual int Write(void* arg_0);
		/* 18h */	virtual int Read(void* arg_0);
		/* 1Ch */	virtual bool WriteToXML(XmlSerializer*);  // returns true
		/* 20h */	virtual bool cSpatialObject_func20h();  // returns true

		/* 24h */	virtual bool IsRolledOver();
		/* 28h */	virtual void SetIsRolledOver(bool bValue);
		/* 2Ch */	virtual const Vector3& GetPosition();
		/* 30h */	virtual const Quaternion& GetOrientation();
		/* 34h */	virtual float GetScale();
		/* 38h */	virtual void SetPosition(const Vector3& value);
		/* 3Ch */	virtual void SetOrientation(const Quaternion& value);
		/* 40h */	virtual void SetScale(float fValue);
		/// Changes the position and orientation of the object recalculating its physics.
		/// For example, it can be used to teleport creatures (using SetOffset() manually just moves them back to their original position)
		/// @param position
		/// @param orientation
		/* 44h */	virtual void Teleport(const Vector3& position, const Quaternion& orientation); 
		/* 48h */	virtual bool IsOnView();
		/* 4Ch */	virtual void SetIsOnView(bool bValue);
		/* 50h */	virtual bool IsSelected();
		/* 54h */	virtual void SetIsSelected(bool bValue);
		/* 58h */	virtual bool cSpatialObject_func58h();  // does nothing by default

		/// Returns the local Y axis of this spatial object
		/// @returns
		/* 5Ch */	virtual Vector3 GetDirection();

		/* 60h */	virtual Vector3 cSpatialObject_func60h();
		/* 64h */	virtual void SetLocalExtents(const BoundingBox& localExtents, float fScale);
		/* 68h */	virtual const BoundingBox& GetLocalExtents();
		/* 6Ch */	virtual int cSpatialObject_func6Ch(int);
		/* 70h */	virtual float GetBoundingRadius();
		/* 74h */	virtual float GetFootprintRadius();
		/* 78h */	virtual float GetMaxZ();
		// Something related with screen pos?
		/* 7Ch */	virtual Point& cSpatialObject_func7Ch(bool, Point& dst);
		// Both methods related with pinning the model to the planet
		/* 80h */	virtual void cSpatialObject_func80h();
		/* 84h */	virtual void cSpatialObject_func84h();
		/* 88h */	virtual bool HasModelChanged();
		/* 8Ch */	virtual void SetHasModelChanged(bool bValue);
		/* 90h */	virtual bool HasModel();
		/* 94h */	virtual void SetModelKey(const ResourceKey& modelKey);
		/* 98h */	virtual const ResourceKey& GetModelKey();
		/* 9Ch */	virtual bool cSpatialObject_func9Ch();
		/* A0h */	virtual void SetModelWorld(Graphics::IModelWorld* pModelWorld);
		/* A4h */	virtual void cSpatialObject_funcA4h();
		/* A8h */	virtual void SetModel(Graphics::Model* pModel, Graphics::IModelWorld* pModelWorld);
		/* ACh */	virtual Graphics::Model* GetModel();
		/* B0h */	virtual Graphics::IModelWorld* GetModelWorld();
		/* B4h */	virtual void cSpatialObject_funcB4h(string& dst);
		/* B8h */	virtual void* Cast(uint32_t type);
		/* BCh */	virtual int AddRef() = 0;
		/* C0h */	virtual int Release() = 0;

	public:

		/* 04h */	Vector3 mPosition;
		/* 10h */	Quaternion mOrientation;
		/* 20h */	BoundingBox mOriginalLocalExtents;
		/* 38h */	BoundingBox mLocalExtents;
		/* 50h */	uint32_t mFlags;   // kPickupEnabled = 0x200 belongs here, not in cInteractiveOrnament
		/* 54h */	uint32_t mMaterialType;
		/* 58h */	float field_58;  // material type?
		/* 5Ch */	float mBoundingRadius;
		/* 60h */	float mFootprintRadius;
		/* 64h */	float mScale;
		/* 68h */	float mDistanceFromCamera;
		/* 6Ch */	bool mbIsSelected;
		/* 6Dh */	bool mbIsRolledOver;
		/* 6Eh */	bool mbIsInvalid;
		/* 6Fh */	bool mbPickable;
		/* 70h */	bool mbIsTangible;
		/// If a model is fixed, it isn't affected by any kind of physics.
		/* 71h */	bool mbFixed;
		/* 72h */	bool mbIsBeingEdited;
		/* 73h */	bool mbModelChanged;
		/* 74h */	bool mbTransformDirty;
		/* 75h */	bool mbEnabled;
		/* 76h */	bool mbInView;
		/// True if the object is not floating on air
		/* 77h */	bool mbSupported;
		/* 78h */	bool mbIsGhost;
		/* 7Ch */	float field_7C;
		/* 80h */	float field_80;
		/* 84h */	float field_84;
		/* 88h */	float field_88;
		/* 8Ch */	float field_8C;
		/* 90h */	ResourceKey mModelKey;
		/* 9Ch */	intrusive_ptr<Graphics::Model> mpModel;
		/* A0h */	intrusive_ptr<Graphics::IModelWorld> mpModelWorld;
		/* A4h */	bool field_A4;
		/* A5h */	bool field_A5;
		/* A6h */	bool mbKeepPinnedToPlanet;
		/* A7h */	bool field_A7;
		/* A8h */	uint32_t field_A8;
		/* ACh */	int field_AC;
		/* B0h */	int field_B0;
		/* B4h */	float field_B4;
		/* B8h */	int field_B8;
		/* BCh */	int field_BC;
		/* C0h */	vector<int> field_C0;

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSpatialObject) == 0xD4, "sizeof(cSpatialObject) != D4h");
}


