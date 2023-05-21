#ifndef MODAPI_DLL_EXPORT
#include <Spore\Editors\EditorPlayMode.h>
#include <Spore\Editors\PlayModeActor.h>

namespace Editors
{
	auto_METHOD_VOID(PlayModeActor, AddWalkAction, Args(PlayModeActor::WalkAction* action, bool arg2), Args(action, arg2));

	PlayModeActor::WalkAction* PlayModeActor::CreateWalkAction(const Vector3& position, float arg_4, bool arg_8, float arg_C)
	{
		auto action = new PlayModeActor::WalkAction();
		action->dstPosition = position;
		action->field_20 = arg_4;
		action->field_24 = arg_C;
		action->field_28 = arg_8;
		action->field_29 = false;
		action->field_2A = false;
		action->field_2B = false;
		return action;
	}

	auto_METHOD_VOID(EditorCreatureController, Update, Args(int dt), Args(dt));
	auto_METHOD_VOID(EditorCreatureController, SetTargetPosition, Args(const Vector3& a1, bool a2, bool a3), Args(a1, a2, a3));

	EditorCreatureController::EditorCreatureController()
		: mnRefCount()
		, mpAnimatedCreature()
		, mpModelWorld()
		, field_10()
		, field_14()
		, field_18()
		, mCurrentAnimID()
		, mRealTargetPosition()
		, mTargetPosition()
		, mCurrentPosition()
		, mTargetAngle()
		, mCurrentAngle()
		, mMovementSpeed(2.5f)
		, mRotateSpeed(Math::PI)
		, field_54()
		, field_55()
		, mTargetLookAt()
		, mCurrentLookAt()
		, field_70(true)
		, field_74()
		, field_78()
		, field_7C()
		, field_80(0.5f)
		, mSmoothLookAt()
	{
	}

	int EditorCreatureController::AddRef()
	{
		++mnRefCount;
		return mnRefCount;
	}
	int EditorCreatureController::Release()
	{
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}

	void EditorCreatureController::SetTargetAngle(float angle, bool applyNow)
	{
		mTargetAngle = angle;
		if (applyNow)
		{
			mCurrentAngle = angle;
			mpAnimatedCreature->mOrientation = Quaternion::FromRotation(Z_AXIS, angle);
		}
	}

	Anim::AnimatedCreature* EditorCreatureController::GetAnimatedCreature() const
	{
		return mpAnimatedCreature.get();
	}
	void EditorCreatureController::SetAnimatedCreature(Anim::AnimatedCreature* pCreature)
	{
		mpAnimatedCreature = pCreature;
	}

	Graphics::IModelWorld* EditorCreatureController::GetGroundModelWorld() const
	{
		return mpModelWorld;
	}
	void EditorCreatureController::SetGroundModelWorld(Graphics::IModelWorld* modelWorld)
	{
		mpModelWorld = modelWorld;
	}

	Vector3 EditorCreatureController::GetCurrentPosition() const {
		return mCurrentPosition;
	}
	float EditorCreatureController::GetCurrentAngle() const {
		return mCurrentAngle;
	}


	//// PlayModeBackgrounds ////

	auto_METHOD_VOID_(PlayModeBackgrounds, SwitchBackground);

	auto_METHOD_VOID_(PlayModeBackgrounds, DisableBackground);

	auto_METHOD_VOID(PlayModeBackgrounds, Load,
		Args(PlayModeUI* a1, uint32_t a2, uint32_t a3, Graphics::ILightingWorld* a4, int8_t a5),
		Args(a1, a2, a3, a4, a5));

	auto_METHOD_VOID(PlayModeBackgrounds, LoadBackgroudFiles,
		Args(int8_t backgroundSet), Args(backgroundSet));

	auto_METHOD(PlayModeBackgrounds, bool, HandleUIButton,
		Args(uint32_t controlID), Args(controlID));

	auto_METHOD_VOID(PlayModeBackgrounds, ToggleBackgroundButtonHighlights,
		Args(uint32_t backgroundButtonID), Args(backgroundButtonID));

	auto_METHOD_VOID_(PlayModeBackgrounds, UpdatePageNumbers);

	auto_METHOD_VOID_(PlayModeBackgrounds, UpdateBackgroundButtons);

	auto_METHOD_(PlayModeBackgrounds, bool, IsBlackBackground);


	//// PlayModeUI ////

	auto_METHOD_VIRTUAL(PlayModeUI, UTFWin::IWinProc, bool, HandleUIMessage,
		Args(UTFWin::IWindow* pWindow, const UTFWin::Message& message),
		Args(pWindow, message));

	auto_METHOD(PlayModeUI, UTFWin::IWindow*, FindWindowByID,
		Args(uint32_t controlID), Args(controlID));

	auto_METHOD_VOID(PlayModeUI, SetWindowVisible,
		Args(uint32_t controlID, bool visible), Args(controlID, visible));


	//// EditorPlayMode ////

	auto_METHOD_VOID(EditorPlayMode, Load,
		Args(cEditor* editor, int8_t playModeBackgroundSet), Args(editor, playModeBackgroundSet));

	auto_METHOD_VOID_(EditorPlayMode, Dispose);

	auto_METHOD_(EditorPlayMode, uint32_t, GetNextEnvironmentReactionAnimID);

	auto_METHOD_VOID(EditorPlayMode, sub_628CC0, Args(bool a), Args(a));
}
#endif