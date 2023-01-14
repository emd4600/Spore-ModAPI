#pragma once

#include <Spore\Anim\AnimatedCreature.h>
#include <Spore\BasicIncludes.h>
#include "AnimEditorBlocks.h"
#include "AnimEditorUI.h"

#define AnimEditorModePtr intrusive_ptr<AnimEditorMode>

class AnimEditorMode 
	: public App::IGameMode
	, public Sporepedia::IShopperListener
	, public Graphics::ILayer
	, public DefaultRefCounted
{
public:
	static const uint32_t MODE_ID = id("AnimEditorMode");
	static const uint32_t ANIM_ID = id("_anim_editor");

	AnimEditorMode();

	int AddRef() override;
	int Release() override;
	~AnimEditorMode();

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


	void OnShopperAccept(const ResourceKey& selection) override;

	void DrawLayer(int flags, int layerIndex, App::cViewer**, Graphics::RenderStatistics&) override;


	void AddCreature(const ResourceKey& key);
	void ReloadCreature(int index);
	void RemoveCreature(int index);
	void PlayAnimation(uint32_t animID, int mode);
	
protected:
	void UpdateFileTime();

	GameInput mInput;
	AnimEditorUIPtr mpUI;

	IModelWorldPtr mpModelWorld;
	ILightingWorldPtr mpLightingWorld;
	IEffectsWorldPtr mpEffectWorld;
	IAnimWorldPtr mpAnimWorld;
	vector<AnimatedCreaturePtr> mCreatures;
	vector<string16> mNames;
	vector<ResourceKey> mCreatureKeys;
	vector<Anim::AnimIndex> mAnimIndices;
	uint32_t mCurrentAnimID;
	int mCurrentAnimMode;

	AnimEditorBlocksPtr mpBlocks;

	Clock mClock;
	ULARGE_INTEGER mLastCheckTime;
	string16 mPath;
};
