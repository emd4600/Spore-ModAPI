#include "stdafx.h"
#include "MyObject.h"

MyObject::MyObject()
{
}


MyObject::~MyObject()
{
}

// For internal use, do not modify.
int MyObject::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int MyObject::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* MyObject::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(MyObject);
	return nullptr;
}
