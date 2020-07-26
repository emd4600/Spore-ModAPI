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

	auto_METHOD_VOID(CreatureWalkController, Update, Args(int dt), Args(dt));
	auto_METHOD_VOID(CreatureWalkController, SetTargetPosition, Args(const Vector3& a1, bool a2, bool a3), Args(a1, a2, a3));

	CreatureWalkController::CreatureWalkController()
		: mnRefCount()
		, mpAnimatedCreature()
		, mpModelWorld()
		, field_10()
		, field_14()
		, field_18()
		, field_1C()
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

	int CreatureWalkController::AddRef()
	{
		++mnRefCount;
		return mnRefCount;
	}
	int CreatureWalkController::Release()
	{
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}

	void CreatureWalkController::SetTargetAngle(float angle, bool applyNow)
	{
		mTargetAngle = angle;
		if (applyNow)
		{
			mCurrentAngle = angle;
			mpAnimatedCreature->mOrientation = Quaternion::FromRotation(Z_AXIS, angle);
		}
	}

	Anim::AnimatedCreature* CreatureWalkController::GetAnimatedCreature() const
	{
		return mpAnimatedCreature.get();
	}
	void CreatureWalkController::SetAnimatedCreature(Anim::AnimatedCreature* pCreature)
	{
		mpAnimatedCreature = pCreature;
	}

	Graphics::IModelWorld* CreatureWalkController::GetGroundModelWorld() const
	{
		return mpModelWorld;
	}
	void CreatureWalkController::SetGroundModelWorld(Graphics::IModelWorld* modelWorld)
	{
		mpModelWorld = modelWorld;
	}

	Vector3 CreatureWalkController::GetCurrentPosition() const {
		return mCurrentPosition;
	}
	float CreatureWalkController::GetCurrentAngle() const {
		return mCurrentAngle;
	}
}
#endif