#include "stdafx.h"
#include "MyGameMode.h"

MyGameMode::MyGameMode()
{
	
}

MyGameMode::~MyGameMode()
{

}

// For internal use, do not touch this.
int MyGameMode::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not touch this.
int MyGameMode::Release()
{
	return DefaultRefCounted::Release();
}

// The use of this function is unknown.
bool MyGameMode::func0Ch()
{
	return false;
}

bool MyGameMode::Initialize(App::IGameModeManager* pManager)
{
	// Called when on game startup. Here you should create all your model/effect worlds, etc.
	
	return true;
}

bool MyGameMode::Dispose()
{
	// Called when the game exits. Here you should dispose all your model/effect worlds,
	// ensure all objects are released, etc
	
	return true;
}

bool MyGameMode::OnEnter()
{
	// Called when the game mode is entered. Here you should load your effects and models,
	// load the UI, add custom renderers, etc.
	
	// Return false if there was any error.
	return true;
}

void MyGameMode::OnExit()
{
	// Called when the game mode is exited. Here you should kill all effects and models, 
	// stop any renderers, unload the UI, etc.
}

// The use of this function is unknown.
void* MyGameMode::func20h(int) 
{
	return nullptr;
}


//// INPUT LISTENERS ////

// Called when a keyboard key button is pressed.
bool MyGameMode::OnKeyDown(int virtualKey, KeyModifiers modifiers)
{
	mInput.OnKeyDown(virtualKey, modifiers);
	
	// Return true if the keyboard event has been handled in this method.
	return false;
}

// Called when a keyboard key button is released.
bool MyGameMode::OnKeyUp(int virtualKey, KeyModifiers modifiers)
{
	mInput.OnKeyUp(virtualKey, modifiers);
	
	// Return true if the keyboard event has been handled in this method.
	return false;
}

// Called when a mouse button is pressed (this includes the mouse wheel button).
bool MyGameMode::OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseDown(mouseButton, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when a mouse button is released (this includes the mouse wheel button).
bool MyGameMode::OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseUp(mouseButton, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when the mouse is moved.
bool MyGameMode::OnMouseMove(float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseMove(mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when the mouse wheel is scrolled. 
// This method is not called when the mouse wheel is pressed.
bool MyGameMode::OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseWheel(wheelDelta, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}


//// UPDATE FUNCTION ////

void MyGameMode::Update(float delta1, float delta2)
{
	// Called on every frame.
	// delta1 and delta2 are the ellapsed time in seconds since the last call,
	// the difference between both is not known.
}
