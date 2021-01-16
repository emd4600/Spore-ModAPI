#pragma once

#include <Spore\BasicIncludes.h>

#define MyGameModePtr intrusive_ptr<MyGameMode>

class MyGameMode 
	: public App::IGameMode
	, public DefaultRefCounted
{
public:
	MyGameMode();

	int AddRef() override;
	int Release() override;
	~MyGameMode();

	bool func0Ch() override;
	bool Initialize(App::IGameModeManager* pManager) override;
	bool Dispose() override;
	bool OnEnter() override;
	void OnExit() override;
	void* func20h(int) override;

	bool OnKeyDown(int virtualKey, KeyModifiers modifiers) override;
	bool OnKeyUp(int virtualKey, KeyModifiers modifiers) override;
	bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
	bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
	bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState) override;
	bool OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState) override;
	void Update(float delta1, float delta2) override;
	
protected:
	GameInput mInput;
};
