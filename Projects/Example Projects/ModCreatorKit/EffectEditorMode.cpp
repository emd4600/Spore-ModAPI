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
#include "stdafx.h"
#include "EffectEditorMode.h"
#include "DebugInformation.h"
#include "Debugging.h"

#include <Spore\Resources.h>
#include <Spore\App\IGameModeManager.h>
#include <Spore\Hash.h>

EffectEditorMode::EffectEditorMode()
	: mpEffect(nullptr)
	, mClock(Clock::Mode::Seconds)
	, mnLastCheckTime()
	, mpPath()
	, mpEffectWorld(nullptr)
{
	
}

EffectEditorMode::~EffectEditorMode()
{

}

int EffectEditorMode::AddRef() {
	return DefaultRefCounted::AddRef();
}
int EffectEditorMode::Release() {
	return DefaultRefCounted::Release();
}

// The use of this function is unknown.
bool EffectEditorMode::func0Ch()
{
	return false;
}

bool EffectEditorMode::Initialize(App::IGameModeManager*)
{
	return true;
}

bool EffectEditorMode::Dispose()
{
	SwarmManager.RemoveWorld(kWorldID);
	return true;
}

void EffectEditorMode::CreateEffect()
{
	if (mpEffect) mpEffect->Stop(1);

	// We want it to stop and start inmediately, so we will really kill all particles
	SwarmManager.GetActiveWorld()->SetState(Swarm::kStateShutdown);
	SwarmManager.GetActiveWorld()->SetState(Swarm::kStateActive);

	if (SwarmManager.CreateEffect(id("_effect_editor"), 0, mpEffect)) {
		// This will only be executed if the effect existed and a new instance was created
		mpEffect->Start(1);
	}

	// Stop and start the clock again
	mClock.Reset();
	mClock.Start();
}

void EffectEditorMode::UpdateFileTime()
{
	if (!mpPath.empty()) {
		HANDLE handle = CreateFile((wchar_t*)mpPath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		FILETIME lastWriteTime;
		if (GetFileTime(handle, NULL, NULL, &lastWriteTime))
		{
			mnLastCheckTime.LowPart = lastWriteTime.dwLowDateTime;
			mnLastCheckTime.HighPart = lastWriteTime.dwHighDateTime;
		}

		CloseHandle(handle);
	}
}

bool EffectEditorMode::OnEnter()
{
	// Get the handle of the main.effdir file

	mpEffectWorld = SwarmManager.CreateWorld(kWorldID);

	SwarmManager.SetActiveWorld(mpEffectWorld.get());

	DebugInformation* pDebugInformation = nullptr;
	Resource::DBPF* pDBPF = nullptr;
	ResourceKey name = { id("main"), TypeIDs::effdir, id("_SporeModder_EffectEditor") };
	string16 path;

	pDBPF = ResourceManager.GetDBPF(name);

	if (Debugging::Get()->GetDebugInformation(pDBPF, &pDebugInformation)
		&& pDebugInformation->GetFilePath(name, &path))
	{
		mpPath = path.c_str();
	}
	else
	{
		mpPath = u"";
	}

	// Load camera and effect
	CameraManager.SetActiveCameraByID(id("EffectEditorCamera"));
	CameraManager.GetViewer()->SetBackgroundColor(ColorRGBA(0.7f, 0.7f, 0.7f, 1.0f));

	CreateEffect();
	
	return true;
}

void EffectEditorMode::OnExit()
{
	SwarmManager.RemoveWorld(kWorldID);
}

// The use of this function is unknown.
void* EffectEditorMode::func20h(int) 
{
	return nullptr;
}


//// INPUT LISTENERS ////

bool EffectEditorMode::OnKeyDown(int virtualKey, KeyModifiers modifiers)
{
	return false;
}

bool EffectEditorMode::OnKeyUp(int virtualKey, KeyModifiers modifiers)
{
	return false;
}

bool EffectEditorMode::OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)
{
	return false;
}

bool EffectEditorMode::OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)
{
	return false;
}

bool EffectEditorMode::OnMouseMove(float mouseX, float mouseY, MouseState mouseState)
{
	return false;
}

bool EffectEditorMode::OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState)
{
	return false;
}

//// UPDATE FUNCTION ////

void EffectEditorMode::Update(float delta1, float delta2)
{
	// Update every second
	if (mClock.GetElapsed() >= 1.0f)
	{
		ULARGE_INTEGER oldTime = mnLastCheckTime;
		UpdateFileTime();

		if (mnLastCheckTime.QuadPart > oldTime.QuadPart) {
			CreateEffect();
		}
	}
}


//// INITIALIZATION FUNCTION ////

// The initialization function that adds this game mode to the game mode manager.
void EffectEditorMode::AddGameMode()
{
	GameModeManager.AddGameMode(new EffectEditorMode(), id("EffectEditorMode"), "EffectEditorMode");
}

