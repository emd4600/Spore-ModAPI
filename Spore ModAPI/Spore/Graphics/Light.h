#pragma once

#include <Spore\MathUtils.h>

namespace Graphics
{
	struct Light
	{
		enum class Type : int {

		};

		/* 00h */	Type type;
		/* 04h */	float radius;
		/* 08h */	float invRadius;
		/* 0Ch */	float innerConeAngle;
		/* 10h */	Math::ColorRGB color;
		/* 1Ch */	float outerConeAngle;
		/* 20h */	Math::Vector3 direction;
		/* 2Ch */	Math::Vector3 position;  // this might be at 30h
	};
}