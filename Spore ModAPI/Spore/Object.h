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
#include <Spore\ResourceKey.h>
#include <EASTL\intrusive_ptr.h>

#include <cstddef>

#define OBJECT_CAST(c) if (type == c::TYPE) return (c*)this

using namespace eastl;

///
/// A default interface that provides a virtual destructor, it should only be used internally.
/// It is used in many manager implementations, but we don't know if it's a unique interface or one specific for each manager.
///
class IVirtual
{
public:
	virtual ~IVirtual() {};
};

///
/// This class represents a basic reference counted object. Reference counted objects can be used inside intrusive_ptr structures
/// in order to have automatic memory management. For example: intrusive_ptr\<Window\> mpWindow = new Window();
///
/// Internally, reference counted objects store a reference count. That value is increased every time AddRef() is called, 
/// and decreased every time Release() is called. When the reference count reaches 0, the object deletes itself.
/// Every AddRef() call must be paired with a Release() call; intrusive_ptr does that automatically.
///
/// However, intrusive pointers must be used carefully, since it could case problems on certain cases.
/// For example, class A has an intrusive_ptr\<B\> member. B has an intrusive_ptr\<A\> that points to the first object. This causes a 
/// recursive dependance that makes those objects never be deleted.
/// 
/// Additionally, this class contains a Cast method, that allows classes to implement
/// an efficient equivalent to dynamic_cast. You can use it directly, but it's recommended to use object_cast instead.
/// For example, to cast an IDrawable\* pDrawable; into a IImageDrawable\*:
/// ~~~~~~~~~~~~~~~~~~{.cpp}
/// // Cast an IDrawable* pDrawable into a IImageDrawable*
/// IImageDrawable* result = object_cast<IImageDrawable>(pDrawable);
/// // If it can be casted it will return nullptr; it's recommend it to always check
/// if (result) ...
/// ~~~~~~~~~~~~~~~~~~
///
/// Object is an interface; for a default implementation, check DefaultObject. 
/// Object can be considered an equivalent to COM objects.
///
/// You can use the "ModAPI Object" item template to create a basic Object class that supports casting.
///
class Object
{
public:

	static const uint32_t TYPE = 0xEE3F516E;

	virtual int AddRef() = 0;
	virtual int Release() = 0;

protected:
	virtual ~Object() {};

public:
	virtual void* Cast(uint32_t typeID) const = 0;
};


/// Dynamically casts one instance of an Object into another type. The type you are casting to
/// must have a static member called 'TYPE', but it does not need to be an Object. 
/// If the object cannot be casted to the given type, nullptr is returned.
/// Example usage:
/// ~~~~~~~~~~~~~~~~{.cpp}
/// cGameData* pCreature = GetCreature();
/// cModelObject* pModel = object_cast<cModelObject>(pCreature);
/// ~~~~~~~~~~~~~~~~
template <class Type, class CallerType>
inline Type* object_cast(const CallerType pObject)
{
	return (Type*) pObject->Cast(Type::TYPE);
}


///
/// A default implementation of the Object class.
///
class DefaultObject : public Object
{
public:
	DefaultObject();

	virtual int AddRef() override;
	virtual int Release() override;
	virtual void* Cast(uint32_t typeID) const override;

private:
	int mnRefCount = 0;
};

/// The default implementation of a reference counted class.
class DefaultRefCounted
{
public:
	DefaultRefCounted();

protected:
	virtual ~DefaultRefCounted() {};

public:
	virtual int AddRef();
	virtual int Release();
	virtual int GetReferenceCount();

protected:
	int mnRefCount = 0;
};

class MultithreadObject
{
public:
	MultithreadObject();

	virtual int AddRef();
	virtual int Release();

protected:
	int mnRefCount;
};

///////////////////////////////////
//// INTERNAL IMPLEMENENTATION ////
///////////////////////////////////

inline MultithreadObject::MultithreadObject()
	: mnRefCount(0)
{
}


inline DefaultObject::DefaultObject()
	: mnRefCount(0)
{

}

inline DefaultRefCounted::DefaultRefCounted()
	: mnRefCount(0)
{

}
