/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModCreatorKit.
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

#include <Spore\App\IGameMode.h>
#include <Spore\Effects.h>
#include <Spore\Clock.h>
#include <EASTL\string.h>

using namespace eastl;
using namespace Swarm;

class EffectEditorMode 
	: public App::IGameMode
	, public DefaultRefCounted
{
public:
	static const uint32_t kWorldID = id("EffectEditor");

	EffectEditorMode();

	int AddRef() override;
	int Release() override;
	~EffectEditorMode();

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

	// The function to attach the mode to the game mode manager.
	static void AddGameMode();

private:
	void CreateEffect();
	void UpdateFileTime();
	
protected:
	intrusive_ptr<IEffectWorld> mpEffectWorld;
	intrusive_ptr<IEffect> mpEffect;

	Clock mClock;
	ULARGE_INTEGER mnLastCheckTime;
	string16 mpPath;
};
