#pragma once

#include <Spore\MathUtils.h>
#include <Spore\Anim\AnimatedCreature.h>
#include <Spore\Graphics\IModelWorld.h>

#define EditorCreatureControllerPtr eastl::intrusive_ptr<Editors::EditorCreatureController>

namespace Editors
{
	class EditorCreatureController
	{
	public:
		EditorCreatureController();
		virtual ~EditorCreatureController() {};

		int AddRef();
		int Release();

		Anim::AnimatedCreature* GetAnimatedCreature() const;
		void SetAnimatedCreature(Anim::AnimatedCreature* pCreature);

		Graphics::IModelWorld* GetGroundModelWorld() const;
		void SetGroundModelWorld(Graphics::IModelWorld* modelWorld);

		void Update(int dt);

		// third arg is ignore z?
		void SetTargetPosition(const Vector3& position, bool applyNow=false, bool ignoreZ = false);
		void SetTargetAngle(float angle, bool applyNow = false);

		Vector3 GetCurrentPosition() const;
		float GetCurrentAngle() const;

	public:
		/* 04h */	int mnRefCount;
		/* 08h */	AnimatedCreaturePtr mpAnimatedCreature;
		/* 0Ch */	Graphics::IModelWorld* mpModelWorld;
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	uint32_t mCurrentAnimID;
		/* 20h */	Math::Vector3 mRealTargetPosition;
		/* 2Ch */	Math::Vector3 mTargetPosition;
		/* 38h */	Math::Vector3 mCurrentPosition;
		/* 44h */	float mTargetAngle;
		/* 48h */	float mCurrentAngle;
		/* 4Ch */	float mMovementSpeed;  // 2.5
		/* 50h */	float mRotateSpeed;  // pi, angle speed?
		/* 54h */	bool field_54;
		/* 55h */	bool field_55;
		/* 58h */	Math::Vector3 mTargetLookAt;  // creature position?
		/* 64h */	Math::Vector3 mCurrentLookAt;
		/* 70h */	bool field_70;  // true
		/* 74h */	float field_74;
		/* 78h */	float field_78;
		/* 7Ch */	float field_7C;
		/* 80h */	float field_80;  // 0.5
		/* 84h */	bool mSmoothLookAt;
	};
	ASSERT_SIZE(EditorCreatureController, 0x88);

	namespace Addresses(EditorCreatureController)
	{
		DeclareAddress(Update);
		DeclareAddress(SetTargetPosition);
	}
	namespace Addresses(CreatureWalkController)
	{
		DeclareAddress(Update);
		DeclareAddress(SetTargetPosition);
	}
}
