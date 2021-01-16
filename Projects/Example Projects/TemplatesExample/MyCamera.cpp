#include "stdafx.h"
#include "MyCamera.h"

MyCamera::MyCamera()
{
	
}

MyCamera::~MyCamera()
{

}

// For internal use, do not touch this.
int MyCamera::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not touch this.
int MyCamera::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* MyCamera::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(ICamera);
	CLASS_CAST(MyCamera);
	return nullptr;
}


bool MyCamera::OnAttach(App::ICameraManager* pManager) {
	return true;
}

bool MyCamera::OnDeattach() {
	return true;
}

void MyCamera::OnEnter() {

}

void MyCamera::OnExit() {

}

/// UPDATE FUNCTION ///
void MyCamera::Update(int deltaTime, App::cViewer* pViewer) {
	// Called every frame.
	// delta1 is the ellapsed time in milliseconds since the last call
}

void MyCamera::func24h(bool arg) {
	if (!arg) mInput.Reset();
}


//// INPUT LISTENERS ////

// Called when a keyboard key button is pressed.
bool MyCamera::OnKeyDown(int virtualKey, KeyModifiers modifiers)
{
	mInput.OnKeyDown(virtualKey, modifiers);
	
	// Return true if the keyboard event has been handled in this method.
	return false;
}

// Called when a keyboard key button is released.
bool MyCamera::OnKeyUp(int virtualKey, KeyModifiers modifiers)
{
	mInput.OnKeyUp(virtualKey, modifiers);
	
	// Return true if the keyboard event has been handled in this method.
	return false;
}

// Called when a mouse button is pressed (this includes the mouse wheel button).
bool MyCamera::OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseDown(mouseButton, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when a mouse button is released (this includes the mouse wheel button).
bool MyCamera::OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseUp(mouseButton, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when the mouse is moved.
bool MyCamera::OnMouseMove(float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseMove(mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when the mouse wheel is scrolled. 
// This method is not called when the mouse wheel is pressed.
bool MyCamera::OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseWheel(wheelDelta, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}


bool MyCamera::func40h(int) {
	return false;
}
bool MyCamera::func44h(int) {
	return false;
}
bool MyCamera::func48h(int) {
	return false;
}

App::PropertyList* MyCamera::GetPropertyList() {
	return nullptr;
}

void MyCamera::Initialize() {
		
}

void MyCamera::func54h(Vector3& dst) {
	dst = { 0, 0, 0 };
}
