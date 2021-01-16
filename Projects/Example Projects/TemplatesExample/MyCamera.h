#pragma once

#include <Spore\BasicIncludes.h>

#define MyCameraPtr intrusive_ptr<MyCamera>

class MyCamera 
	: public App::ICamera
	, public DefaultRefCounted
{
public:
	MyCamera();

	int AddRef() override;
	int Release() override;
	~MyCamera();
	void* Cast(uint32_t type) const override;

	bool OnAttach(App::ICameraManager* pManager) override;
	bool OnDeattach() override;
	void OnEnter() override;
	void OnExit() override;
	void Update(int deltaTime, App::cViewer* pViewer) override;

	void func24h(bool) override;

	bool OnKeyDown(int virtualKey, KeyModifiers modifiers) override;
	bool OnKeyUp(int virtualKey, KeyModifiers modifiers) override;
	bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
	bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
	bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState) override;
	bool OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState) override;
	
	bool func40h(int) override;
	bool func44h(int) override;
	bool func48h(int) override;

	App::PropertyList* GetPropertyList() override;
	void Initialize() override;
	void func54h(Vector3& dst) override;
	
protected:
	GameInput mInput;
};

