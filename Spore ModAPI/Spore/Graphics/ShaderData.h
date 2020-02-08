#pragma once

#include <Spore\MathUtils.h>

namespace Graphics
{
	struct ShadowMapInfo
	{
		Math::Vector4 mRangeAndStrength; 
		Math::Vector4 mShadowDir;
		Math::Vector4 mNestInfo;
	};
}