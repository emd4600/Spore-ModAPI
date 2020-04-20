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
			if (field_17C != 0 && mpAnimWorld) {
				mpAnimWorld->DestroyCreature(this);
			}
			delete this;
			return 0;
		}
		return mnRefCount;
	}
}