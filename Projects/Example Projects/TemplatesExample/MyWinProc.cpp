#include "stdafx.h"
#include "MyWinProc.h"

MyWinProc::MyWinProc()
{
}


MyWinProc::~MyWinProc()
{
}

// For internal use, do not modify.
int MyWinProc::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int MyWinProc::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* MyWinProc::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(MyWinProc);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int MyWinProc::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool MyWinProc::HandleUIMessage(IWindow* window, const Message& message)
{
	
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
