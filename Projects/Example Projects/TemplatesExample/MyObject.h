#pragma once

#include <Spore\BasicIncludes.h>

#define MyObjectPtr intrusive_ptr<MyObject>

class MyObject 
	: public Object
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("MyObject");
	
	MyObject();
	~MyObject();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
