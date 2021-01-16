#pragma once

#include <Spore\BasicIncludes.h>

#define MyListenerPtr intrusive_ptr<MyListener>

class MyListener 
	: public App::IMessageListener
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("MyListener");

	MyListener();
	~MyListener();

	int AddRef() override;
	int Release() override;
	
	// This is the function you have to implement, called when a message you registered to is sent.
	bool HandleMessage(uint32_t messageID, void* message) override;
};
