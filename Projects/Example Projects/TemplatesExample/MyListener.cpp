#include "stdafx.h"
#include "MyListener.h"

MyListener::MyListener()
{
}


MyListener::~MyListener()
{
}

// For internal use, do not modify.
int MyListener::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int MyListener::Release()
{
	return DefaultRefCounted::Release();
}


// The method that receives the message. The first thing you should do is checking what ID sent this message...
bool MyListener::HandleMessage(uint32_t messageID, void* message)
{
	// Return true if the message has been handled. Other listeners will receive the message regardless of the return value.
	return true;
}
