#pragma once

#include <Spore\Object.h>
#include <Spore\MathUtils.h>
#include <Spore\Graphics\ModelAsset.h>

#define EditorBaseHandlePtr eastl::intrusive_ptr<Editors::EditorBaseHandle>

namespace Editors
{
	class EditorRigblock;

	enum class EditorHandleState : int
	{
		/// User is moving the handle
		Active = 0,
		/// Rigblock is not selected, usually handle is invisible
		Unselected = 1,
		/// Mouse is hovering over the handle
		Rollover = 2,
		/// Rigblock is selected but user is not interacting with handle
		Default = 3
	};

	class EditorBaseHandle
		: public Object
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x50A1FE5;

		/* 10h */	virtual uint32_t GetTypeID();
		/* 14h */	virtual void func14h();
		// also used to unload
		/* 18h */	virtual void Load(EditorRigblock* pRigblock, bool load, uint32_t modelID, uint32_t overdrawModelID);
		/* 1Ch */	virtual void Dispose();
		/// Sets the scale (scaling the model and overdraw model), which gets multiplied by `mDefaultScale`
		/// @param scale
		/* 20h */	virtual void SetScale(float scale);
		/* 24h */	virtual Math::Vector3 GetPosition();
		/* 28h */	virtual void func28h(int, bool);
		/* 2Ch */	virtual void func2Ch();
		/* 30h */	virtual void func30h(int, bool);
		/* 34h */	virtual ResourceKey GetTuningFile();
		/* 38h */	virtual float GetAlpha(EditorHandleState state);
		/* 3Ch */	virtual float GetOverdrawAlpha(EditorHandleState state);
		/* 40h */	virtual Math::ColorRGB GetColor(EditorHandleState state);
		/* 44h */	virtual Math::ColorRGB GetOverdrawColor(EditorHandleState state);
		/* 48h */	virtual float GetDefaultScale();

	public:
		/* 0Ch */	PropertyListPtr mpPropList;
		/* 10h */	EditorRigblock* mpRigblock;
		/* 14h */	ModelPtr mpModel;
		/* 18h */	ModelPtr mpOverdrawModel;
		/* 1Ch */	int field_1C;  // not initialized, maybe state?
		/* 20h */	float mFadeInTime;
		/* 24h */	float mFadeOutTime;
		/* 28h */	float mAnimateInTime;
		/* 2Ch */	float mAnimateOutTime;
		/* 30h */	ResourceKey mDefaultModel;
		/* 3Ch */	ResourceKey mDefaultOverdrawModel;
		/* 48h */	bool mHasOverdraw;
		/* 4Ch */	float mDefaultScale;
	};
}