#include "stdafx.h"
#include "AnimEditorMode.h"
#include "Debugging.h"
#include <Spore\Anim\IAnimManager.h>
#include <Spore\Anim\SPAnimation.h>

AnimEditorMode::AnimEditorMode()
	: mInput()
	, mpUI()
	, mpModelWorld()
	, mpLightingWorld()
	, mpEffectWorld()
	, mpAnimWorld()
	, mCreatures()
	, mCreatureKeys()
	, mNames()
	, mCurrentAnimID(0xFFFFFFFF)
	, mCurrentAnimMode()
	, mAnimIndices()
	, mClock(Clock::Mode::Seconds)
	, mLastCheckTime()
	, mPath()
	, mpBlocks()
{
	Initialize(nullptr);
}

AnimEditorMode::~AnimEditorMode()
{

}

// For internal use, do not touch this.
int AnimEditorMode::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not touch this.
int AnimEditorMode::Release()
{
	return DefaultRefCounted::Release();
}

// The use of this function is unknown.
bool AnimEditorMode::func0Ch()
{
	return false;
}

AnimEditorMode* sInstance;

bool AnimEditorMode::Initialize(App::IGameModeManager* pManager)
{
	sInstance = this;

	class Cheat 
		: public ArgScript::ICommand
	{
	public:
		void ParseLine(const ArgScript::Line& line) override
		{
			if (GameModeManager.GetActiveModeID() != MODE_ID) {
				GameModeManager.SetActiveMode(MODE_ID);
			}
			else {
				if (auto args = line.GetOption("remove", 1)) 
				{
					int index = mpFormatParser->ParseInt(args[0]);
					sInstance->RemoveCreature(index);
				}
				if (line.HasFlag("add"))
				{
					Sporepedia::ShopperRequest request(sInstance);
					request.shopperID = id("CreatureShopper");
					Sporepedia::ShopperRequest::Show(request);
				}
				size_t numArgs;
				if (auto args = line.GetOptionRange("play", &numArgs, 1, 2))
				{
					uint32_t animID = mpFormatParser->ParseUInt(args[0]);
					int mode = numArgs == 1 ? 0 : mpFormatParser->ParseInt(args[1]);

					sInstance->PlayAnimation(animID, mode);
				}
				else if (auto args = line.GetOptionRange("default", &numArgs, 0, 1))
				{
					int mode = numArgs == 0 ? 0 : mpFormatParser->ParseInt(args[0]);
					sInstance->PlayAnimation(ANIM_ID, mode);
				}
			}
		}

		const char* GetDescription(ArgScript::DescriptionMode mode) const override
		{
			return "Enters into anim editor";
		}
	};

	CheatManager.AddCheat("animEditor", new Cheat());
	
	return true;
}

bool AnimEditorMode::Dispose()
{
	CheatManager.RemoveCheat("animEditor");

	return true;
}

bool AnimEditorMode::OnEnter()
{
	mpModelWorld = ModelManager.CreateWorld(MODE_ID);
	mpLightingWorld = LightingManager.CreateLightingWorld(MODE_ID);
	mpEffectWorld = EffectsManager.CreateWorld(MODE_ID);
	EffectsManager.SetDefaultWorld(mpEffectWorld.get());
	mpAnimWorld = AnimManager.CreateWorld(u"AnimEditorMode");

	mpAnimWorld->SetEffectWorld(mpEffectWorld.get());
	mpAnimWorld->SetModelWorld(mpModelWorld.get());

	mpLightingWorld->SetLightingState(id("CreatureEditor"));
	mpModelWorld->SetLightingWorld(mpLightingWorld.get(), 0, false);
	mpModelWorld->SetActive(true);

	Renderer.RegisterLayer(mpModelWorld->AsLayer(), 8);
	Renderer.RegisterLayer(mpAnimWorld.get(), 9);

	CameraManager.SetActiveCameraByID(id("EffectEditorCamera"));

	// Add one creature by default
	AddCreature({ 0x67cd060, TypeIDs::crt, GroupIDs::CreatureModels });
	
	// Disabled blocks because the load transform crashes the game for unexplainable reasons
	/*mpBlocks = new AnimEditorBlocks();
	mpBlocks->GenerateMesh(mCreatures[0]->p_cid);*/

	DebugInformation* pDebugInformation = nullptr;
	Resource::Database* pDBPF = nullptr;
	ResourceKey name = { id("_SporeModder_AnimEditor"), TypeIDs::animation, GroupIDs::Global };

	pDBPF = ResourceManager.FindDatabase(name);

	if (!Debugging::Get()->GetDebugInformation(pDBPF, &pDebugInformation)
		|| !pDebugInformation->GetFilePath(name, &mPath))
	{
		mPath = u"";
	}

	UpdateFileTime();
	App::ConsolePrintF("%ls", mPath.c_str());

	Renderer.RegisterLayer(this, 10);

	/*mpUI = new AnimEditorUI();
	mpUI->Load();*/

	PlayAnimation(ANIM_ID, 0);

	return true;
}

void AnimEditorMode::OnExit()
{
	mCreatures.clear();

	if (mpAnimWorld) {
		mpAnimWorld->Dispose();
		mpAnimWorld = nullptr;
	}
	if (mpEffectWorld) {
		EffectsManager.RemoveWorld(MODE_ID);
		mpEffectWorld = nullptr;
	}
	if (mpModelWorld) {
		ModelManager.DisposeWorld(MODE_ID);
		mpModelWorld = nullptr;
	}
	if (mpLightingWorld) {
		LightingManager.RemoveLightingWorld(MODE_ID);
		mpLightingWorld = nullptr;
	}
}

// The use of this function is unknown.
void* AnimEditorMode::func20h(int) 
{
	return nullptr;
}


//// INPUT LISTENERS ////

// Called when a keyboard key button is pressed.
bool AnimEditorMode::OnKeyDown(int virtualKey, KeyModifiers modifiers)
{
	mInput.OnKeyDown(virtualKey, modifiers);
	
	// Return true if the keyboard event has been handled in this method.
	return false;
}

// Called when a keyboard key button is released.
bool AnimEditorMode::OnKeyUp(int virtualKey, KeyModifiers modifiers)
{
	mInput.OnKeyUp(virtualKey, modifiers);
	
	// Return true if the keyboard event has been handled in this method.
	return false;
}

// Called when a mouse button is pressed (this includes the mouse wheel button).
bool AnimEditorMode::OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseDown(mouseButton, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when a mouse button is released (this includes the mouse wheel button).
bool AnimEditorMode::OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseUp(mouseButton, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when the mouse is moved.
bool AnimEditorMode::OnMouseMove(float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseMove(mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}

// Called when the mouse wheel is scrolled. 
// This method is not called when the mouse wheel is pressed.
bool AnimEditorMode::OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseWheel(wheelDelta, mouseX, mouseY, mouseState);
	
	// Return true if the mouse event has been handled in this method.
	return false;
}


//// UPDATE FUNCTION ////

void AnimEditorMode::Update(float dt, float delta2)
{
	if (mpAnimWorld) {
		mpAnimWorld->Update(dt);
	}

	// Update every second
	if (mCurrentAnimID == ANIM_ID && mClock.GetElapsed() >= 1.0f)
	{
		ULARGE_INTEGER oldTime = mLastCheckTime;
		UpdateFileTime();

		if (mLastCheckTime.QuadPart > oldTime.QuadPart) {
			PlayAnimation(ANIM_ID, mCurrentAnimMode);
		}
	}
}

void AnimEditorMode::DrawLayer(int flags, int layerIndex, App::cViewer** pViewers, Graphics::RenderStatistics&)
{
	/*if (mpBlocks) {
		CameraManager.GetViewer()->LoadTransformations();
		mpBlocks->Render();
	}*/
}


void AnimEditorMode::OnShopperAccept(const ResourceKey& selection)
{
	AddCreature(selection);
	PlayAnimation(ANIM_ID, 0);
}

const static Vector3 kCreatureSeparation = { 2.5f, 0.0f, 0.0f };

void AnimEditorMode::AddCreature(const ResourceKey& selection)
{
	App::ConsolePrintF("Adding creature 0x%x ! 0x%x", selection.groupID, selection.instanceID);

	if (auto creature = mpAnimWorld->LoadCreature(selection))
	{
		Vector3 position = { 0.0f, 0.0f, 0.0f };
		if (!mCreatures.empty()) {
			position = mCreatures[mCreatures.size() - 1]->mPosition + kCreatureSeparation;
		}

		creature->mPosition = position;
		mCreatures.push_back(creature);
		mCreatureKeys.push_back(selection);
		mAnimIndices.push_back(-1);
		mpModelWorld->StallUntilLoaded(creature->GetModel());
		mpModelWorld->SetInWorld(creature->GetModel(), true);

		int index = mCreatures.size() - 1;

		string16 name = u"";
		cAssetMetadataPtr metadata;
		if (Pollinator::GetMetadata(selection.instanceID, selection.groupID, metadata)) {
			name = metadata->GetName();
		}
		mNames.push_back(name);
		App::ConsolePrintF("Added creature %ls to index %d", name.c_str(), index);
	}
	else {
		App::ConsolePrintF("Error: creature doesn't exist");
	}
}


void AnimEditorMode::RemoveCreature(int index)
{
	if (index >= (int)mCreatures.size() || index < 0) {
		App::ConsolePrintF("Cannot remove creature %d, invalid index", index);
	}
	else {
		mpAnimWorld->DestroyCreature(mCreatures[index].get());
		mCreatures.erase(mCreatures.begin() + index);
		mAnimIndices.erase(mAnimIndices.begin() + index);
		mCreatureKeys.erase(mCreatureKeys.begin() + index);

		App::ConsolePrintF("Removed creature %s", mNames[index].c_str());
		mNames.erase(mNames.begin() + index);

		// Move existing creatures
		for (unsigned int i = index; i < mCreatures.size(); ++i) {
			mCreatures[i]->mPosition -= kCreatureSeparation;
		}
	}
}

void AnimEditorMode::PlayAnimation(uint32_t animID, int mode)
{
	AnimManager.ClearAnimationCache();

	AnimManager.LoadRequiredAnimations(animID);

	mCurrentAnimID = animID;
	mCurrentAnimMode = mode;

	for (unsigned int i = 0; i < mCreatures.size(); ++i)
	{
		// Stop previous animation
		if (mAnimIndices[i] != -1)
		{
			mCreatures[i]->SetLoop(mAnimIndices[i], false);
			mCreatures[i]->SetLoopTimes(mAnimIndices[i], 0.0f);
		}

		auto animIndex = mCreatures[i]->LoadAnimation(animID);
		mCreatures[i]->SetAnimationMode(animIndex, mode);
		mCreatures[i]->StartAnimation(animIndex);

		mCreatures[i]->SetLoop(animIndex, true);
		mCreatures[i]->SetLoopTimes(animIndex, -1.0f);

		mAnimIndices[i] = animIndex;
	}

	// Stop and start the clock again
	mClock.Reset();
	mClock.Start();
}

void AnimEditorMode::UpdateFileTime()
{
	if (!mPath.empty()) {
		HANDLE handle = CreateFile((wchar_t*)mPath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		FILETIME lastWriteTime;
		if (GetFileTime(handle, NULL, NULL, &lastWriteTime))
		{
			mLastCheckTime.LowPart = lastWriteTime.dwLowDateTime;
			mLastCheckTime.HighPart = lastWriteTime.dwHighDateTime;
		}

		CloseHandle(handle);
	}
}