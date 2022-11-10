#pragma once

#include <Spore\Graphics\IModelWorld.h>
#include <EASTL\intrusive_list.h>

namespace Simulator
{
	class cGameData;

	class IGameDataView 
		: public eastl::intrusive_list_node
	{
	public:
		/* 00h */	virtual ~IGameDataView() = 0;

		/* 04h */	virtual void Update(int deltaTime, int deltaGameTime) = 0;

		/// Creates an game data view instance for the given object.
		/// This should only be called on the master instance (which is cGameViewManager responsability).
		/// @param pObject
		/* 08h */	virtual IGameDataView* Create(cGameData* pObject) = 0;

		/* 0Ch */	virtual cGameData* func0Ch() = 0;
		/* 10h */	virtual void func10h(bool) = 0;
		/* 14h */	virtual bool func14h() = 0;
		/* 18h */	virtual void SetVisible(bool visible) = 0;
		/* 1Ch */	virtual bool IsVisible() = 0;
		/* 20h */	virtual cGameData* func20h() = 0;

		/// Sets the object, and if the object has a model it sets the
		/// object as the model's owner.
		/// @param pObject
		/* 24h */	virtual void SetObject(cGameData* pObject) = 0;

		/* 28h */	virtual void func28h(Object* pObject, Graphics::IModelWorld* pModelWorld, const ResourceKey& modelKey, const ColorRGB& arg_C) = 0;
		/* 2Ch */	virtual Graphics::Model* GetModel() = 0;
		/* 30h */	virtual void SetModel(Graphics::Model* pModel, Graphics::IModelWorld* pModelWorld) = 0;
	};
	ASSERT_SIZE(IGameDataView, 0xC);
}