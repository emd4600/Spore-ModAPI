#include <Spore\Anim\IAnimManager.h>
#include <Spore\Anim\AnimatedCreature.h>

namespace Anim
{
	auto_STATIC_METHOD_(IAnimManager, IAnimManager*, Get);


	int AnimatedCreature::AddRef() {
		return ++mnRefCount;
	}

	int AnimatedCreature::Release() {
		--mnRefCount;
		if (mnRefCount == 0) {
			mnRefCount = 1;
			if (p_cid != 0 && mpAnimWorld) {
				mpAnimWorld->DestroyCreature(this);
			}
			delete this;
			return 0;
		}
		return mnRefCount;
	}

	bool AnimatedCreature::IsIdleWalkLookatStart(uint32_t animID)
	{
		// idle_walk_lookat_start
		// csa_idle_walk_lookat_start
		// epic_idle_walk_lookat_start
		switch (animID) {
		case 0x04866D8E:
		case 0x0452B634:
		case 0x05CB2176:
			return true;
		}
		return false;
	}

	bool AnimatedCreature::IsIdleWalkStop(uint32_t animID)
	{
		// idle_walk_lookat_stop
		// idle_walkstop_01
		// idle_walkstop_02
		// idle_walkstop_03
		// epic_idle_walkstop_01
		// epic_idle_walkstop_02
		// epic_idle_walkstop_03
		// csa_idle_walk_lookat_stop
		// csa_idle_walkstop_01
		// csa_idle_walkstop_02
		// csa_idle_walkstop_03
		switch (animID)
		{
		case 0x04866DB9:
		case 0x04866DC3:
		case 0x04866DCB:
		case 0x04866DD4:
		case 0x05CB21AE:
		case 0x05CB21AF:
		case 0x05CB21B0:
		case 0x0452B651:
		case 0x04482911:
		case 0x04482918:
		case 0x0448291F:
			return true;
		}
		return false;
	}

	bool AnimatedCreature::IsIdleWalk(uint32_t animID)
	{
		if (IsIdleWalkLookatStart(animID) || IsIdleWalkStop(animID)) return true;
		// idle_walk_lookat_loop
		// csa_idle_walk_lookat_loop
		// epic_idle_walk_lookat_loop
		// csa_idle_walk_looklt
		// csa_idle_walk_lookrt
		switch (animID) {
		case 0x04866DAB:
		case 0x0452B64A:
		case 0x05CB2177:
		case 0x044828E9:
		case 0x04482906:
			return true;
		}
		return false;
	}
}