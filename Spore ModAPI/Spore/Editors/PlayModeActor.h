#pragma once

#include <Spore\Object.h>
#include <Spore\Editors\CreatureWalkController.h>
#include <EASTL\vector.h>

namespace Editors
{
	class PlayModeActor
		: public DefaultRefCounted
	{
	public:
		class WalkAction : public DefaultRefCounted {
		public:
			/* 08h */	Vector3 dstPosition;
			/* 14h */	int field_14;  // not initialized
			/* 18h */	int field_18;  // not initialized
			/* 1Ch */	int field_1C;  // not initialized
			/* 20h */	float field_20;
			/* 24h */	float field_24;
			/* 28h */	bool field_28;
			/* 29h */	bool field_29;
			/* 2Ah */	bool field_2A;
			/* 2Bh */	bool field_2B;
		};

		void AddWalkAction(WalkAction* action, bool = false);

		static WalkAction* CreateWalkAction(const Vector3& position, float = 1.0f, bool = false, float = 0.5f);

		/* 08h */	AnimatedCreaturePtr mpCreature;
		/* 0Ch */	int field_0C;
		/* 10h */	CreatureWalkControllerPtr mpWalkController;
		/* 14h */	int field_14;  // not initialized
		/* 18h */	intrusive_ptr<DefaultRefCounted> field_18;
		/* 1Ch */	int mActorID;  // -1
		/* 20h */	float field_20;
		/* 24h */	bool field_24;
		/* 28h */	float field_28;
		/* 2Ch */	int field_2C;  // not initialized
		/* 30h */	int field_30;  // not initialized
		/* 34h */	float field_34;
		/* 38h */	intrusive_ptr<DefaultRefCounted> field_38;
		/* 3Ch */	vector<intrusive_ptr<WalkAction>> mWalkActions;
	};
	ASSERT_SIZE(PlayModeActor, 0x50);
	ASSERT_SIZE(PlayModeActor::WalkAction, 0x2C);

	namespace Addresses(PlayModeActor)
	{
		DeclareAddress(AddWalkAction);
	}
}