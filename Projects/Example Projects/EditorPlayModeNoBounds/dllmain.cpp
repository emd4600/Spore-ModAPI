// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
}

void Dispose()
{

}


// SetTargetPos() is called when you click at some point in the editor, making the creature walk there
member_detour(SetTargetPosition__detour, Editors::CreatureWalkController, void(const Vector3&, bool, bool))
{
	void detoured(const Vector3 & pos, bool applyNow, bool ignoreZ)
	{
		// Usually this method checks that pos.Length() < 5 (so that it is inside the circle), here we ignore it

		mRealTargetPosition = pos;
		mTargetPosition = pos;
		if (ignoreZ) mTargetPosition.z = 0.0f;

		if (applyNow) {
			original_function(this, pos, applyNow, ignoreZ);
		}
	}
};

Vector3 Vector2PointsMaxLength(const Vector3& p1, const Vector3& p2, float maxLength)
{
	Vector3 v = p2 - p1;
	if (maxLength * maxLength < v.SquaredLength()) {
		return p1 + v.Normalized() * maxLength;
	}
	else return p2;
}

// This is the tricky part. Update() is called every frame and it updates the creature position as it walks.
// It checks that it is not walking out of bounds at the middle of the function, which means we have to 
// replicate the whole function
member_detour(CreatureWalkUpdate__detour, Editors::CreatureWalkController, void(int))
{
	// Parameter is "delta time", how many milliseconds since last update
	void detoured(int dt_ms)
	{
		if (!mpAnimatedCreature || !mpModelWorld) return;

		// Conver the delta time to seconds
		float dt = dt_ms / 1000.0f;

		float var_74 = 1.0f;
		float speed = 1.0f;

		uint32_t animID;
		Anim::AnimIndex animIndex;
		if (mpAnimatedCreature->GetCurrentAnimation(&animID, nullptr, nullptr, &animIndex)
			&& !AnimManager.GetAnimGroup(animID)->allowLocomotion)
		{
			Vector3 dir = { 0.0f, -1.5f, 0.5f };
			mTargetLookAt = mpAnimatedCreature->mPosition + mpAnimatedCreature->mOrientation.ToMatrix() * dir;
			mCurrentLookAt = mTargetLookAt;
			var_74 = 0.0f;
			speed = 0.0f;
		}

		if (Anim::AnimatedCreature::IsIdleWalkLookatStart(animID))
		{
			float var_50;
			if (mpAnimatedCreature->func5Ch(animIndex, &var_74, &var_50))
			{
				speed = clamp(var_50 / var_74, 0.0f, 1.0f);
			}
			else {
				speed = 0.0f;
			}
		}
		else {
			speed = var_74;
		}

		mCurrentPosition = Vector2PointsMaxLength(mCurrentPosition, mTargetPosition,
			speed * mMovementSpeed * dt);
		// Here Spore would limit mCurrentPosition to a radius of 5

		mCurrentAngle = IncrementAngleTo(mCurrentAngle, mTargetAngle,
			speed * mRotateSpeed * dt);

		Vector3 targetLookAtDir = mTargetLookAt - mCurrentPosition;
		Vector3 v1 = targetLookAtDir;
		Vector3 currentLookAtDir = mCurrentLookAt - mCurrentPosition;
		if (targetLookAtDir != Vector3::ZERO) v1 = targetLookAtDir = targetLookAtDir.Normalized();
		if (currentLookAtDir != Vector3::ZERO) currentLookAtDir = currentLookAtDir.Normalized();

		// mCurrentLookAt decides where the creature head/eyes are looking to
		if (mSmoothLookAt) {
			float angle = IncrementAngleTo(
				Vector3::OrientedAngle(currentLookAtDir, Y_AXIS, Z_AXIS),
				Vector3::OrientedAngle(targetLookAtDir, Y_AXIS, Z_AXIS),
				5.0f * dt);
			mCurrentLookAt += { 10.0f * cosf(angle), 10.0f * sinf(angle), 0.0f };
		}
		else {
			mCurrentLookAt += 10.0f * Vector2PointsMaxLength(currentLookAtDir, targetLookAtDir, 2.0f * dt);
		}
		if (field_55) {
			v1.z = 0.0f;
			float angle = -Vector3::OrientedAngle(v1, -Y_AXIS, Z_AXIS);
			angle = CorrectAngleRange(CorrectAngleRange(mCurrentAngle) - CorrectAngleRange(angle));
			if (abs(angle) > PI / 4) {
				float rotAngle = mCurrentAngle - (angle < 0 ? -1 : 1) * PI / 4;
				mCurrentLookAt += Matrix3::FromAxisAngle(Z_AXIS, rotAngle) * mpAnimatedCreature->mPosition;
			}
		}

		mpAnimatedCreature->mPosition = mCurrentPosition;
		// Here we decide the orientation of the creature
		// Notice that this only rotates it around the Z axis, so the creature is always upwards (i.e. with gravity towards the plane).
		// With some more rotations you could actually change the gravity and make a spherical play mode...
		mpAnimatedCreature->mOrientation = Quaternion::FromRotation(Z_AXIS, mCurrentAngle);

		if (Anim::AnimatedCreature::IsIdleWalk(animID) &&
			((bool*)mpAnimatedCreature->p_cid)[0x2D4] &&
			!mSmoothLookAt)
		{
			Vector3 v = { mRealTargetPosition.x - mTargetPosition.x, mRealTargetPosition.y - mTargetPosition.y, 0.0f };
			if (v.Length() < 0.1f)
			{
				v = mpAnimatedCreature->mOrientation.ToMatrix() * v;
			}
			else {
				v = v.Normalized();
				static const float eps = 1e-8f;
				if (v.x < eps && v.y < eps && v.z < eps) {
					v = -Y_AXIS;
				}
			}

			mpAnimatedCreature->field_164 = lerp(mpAnimatedCreature->field_164, mCurrentPosition + 10.0f * v, 0.85f);
			if (abs(mpAnimatedCreature->field_164.z) > 0.000015258789) {
				mpAnimatedCreature->field_164.z = 0.0f;
			}
			mTargetLookAt = mpAnimatedCreature->field_164;
			mCurrentLookAt = mpAnimatedCreature->field_164;
		}
		else {
			mpAnimatedCreature->field_164 = mCurrentLookAt;
		}

		if (!field_54) {
			Vector3 point = { mpAnimatedCreature->mPosition.x, mpAnimatedCreature->mPosition.y, 500.0f };
			Graphics::FilterSettings settings;
			settings.flags = 0;
			settings.collisionMode = (Graphics::CollisionMode)4;
			settings.requiredGroupFlags |= 1LL << ModelManager.GetGroupFlag((uint32_t)Graphics::ModelGroups::TestEnv);

			// We are doing a raycast from the creature XY position vertically down, to check where the ground is
			// raycastedModel is the model that collided with that "ray", so it should be the ground model
			// "intersection" will be the point where the "ray" hit the ground, so it's Z coordinate is the height of the terrain
			// at the creature position.
			Vector3 intersection;
			auto raycastedModel = mpModelWorld->FindFirstModelAlongLine(
				point, point - Vector3(0, 0, 1000.0f), nullptr, &intersection, nullptr, settings);

			SporeDebugPrint("intersection: %f, %f, %f", intersection.x, intersection.y, intersection.z);

			if (raycastedModel)
			{
				if (field_7C > 0) {
					field_7C -= dt;
				}
				else {
					mpAnimatedCreature->mPosition.z = field_74 + intersection.z;
					if (field_78 > field_74) {
						field_74 += field_80 * dt;
						if (field_74 > field_78) {
							field_74 = field_78;
						}
					}
					else if (field_74 > field_78) {
						field_74 -= field_80 * dt;
						if (field_74 < field_78) {
							field_74 = field_78;
						}
					}
				}
			}
		}
	}
};


void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	
	CreatureWalkUpdate__detour::attach(GetAddress(Editors::CreatureWalkController, Update));
	SetTargetPosition__detour::attach(GetAddress(Editors::CreatureWalkController, SetTargetPosition));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

