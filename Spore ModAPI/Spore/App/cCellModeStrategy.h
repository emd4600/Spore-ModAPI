#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\App\IGameMode.h>
#include <Spore\CommonIDs.h>

#define cCellModeStrategyPtr eastl::intrusive_ptr<App::cCellModeStrategy>
// The pointer variable is never saved, but it can be retrieved in the GameModeManager
//#define CellModeStrategy (*App::cCellModeStrategy::Get())

namespace App
{
	class cCellModeStrategy
		: public App::IGameMode
		, public App::IUnmanagedMessageListener
	{
	public:
		static const uint32_t MODE_ID = GameModeIDs::kGameCell;

		/* 00h */	virtual int AddRef() override;
		/* 04h */	virtual int Release() override;

		/* 0Ch */	virtual bool func0Ch() override;
		/* 10h */	virtual bool Initialize(App::IGameModeManager* pManager) override;
		/* 14h */	virtual bool Dispose() override;
		/* 18h */	virtual bool OnEnter() override;
		/* 1Ch */	virtual void OnExit() override;
		/* 20h */	virtual void* func20h(int) override;
		/* 24h */	virtual bool OnKeyDown(int virtualKey, KeyModifiers modifiers) override;
		/* 28h */	virtual bool OnKeyUp(int virtualKey, KeyModifiers modifiers) override;
		/* 2Ch */	virtual bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
		/* 30h */	virtual bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
		/* 34h */	virtual bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState) override;
		/* 38h */	virtual bool OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, MouseState mouseState) override;
		/* 3Ch */	virtual void Update(float fDelta1, float fDelta2) override;

		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

	public:
		/* 08h */	bool mbEnableLoadingCards;  // not initialized
		/* 09h */	bool field_09;
		/* 0Ah */	bool field_0A;
	};
	ASSERT_SIZE(cCellModeStrategy, 0xC);

	namespace Addresses(cCellModeStrategy)
	{
		DeclareAddress(AddRef);
		DeclareAddress(Release);
		DeclareAddress(func0Ch);
		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(OnEnter);
		DeclareAddress(OnExit);
		DeclareAddress(func20h);
		DeclareAddress(OnKeyDown);
		DeclareAddress(OnKeyUp);
		DeclareAddress(OnMouseDown);
		DeclareAddress(OnMouseUp);
		DeclareAddress(OnMouseMove);
		DeclareAddress(OnMouseWheel);
		DeclareAddress(Update);

		DeclareAddress(HandleMessage);
	}
}

// Keep these addresses original name, for backwards compatibility
namespace Simulator
{
	namespace Cell
	{
		namespace Addresses(GameModeCell)
		{
			DeclareAddress(AddRef);
			DeclareAddress(Release);
			DeclareAddress(func0Ch);
			DeclareAddress(Initialize);
			DeclareAddress(Dispose);
			DeclareAddress(OnEnter);
			DeclareAddress(OnExit);
			DeclareAddress(func20h);
			DeclareAddress(OnKeyDown);
			DeclareAddress(OnKeyUp);
			DeclareAddress(OnMouseDown);
			DeclareAddress(OnMouseUp);
			DeclareAddress(OnMouseMove);
			DeclareAddress(OnMouseWheel);
			DeclareAddress(Update);

			DeclareAddress(HandleMessage);
		}
	}
}
