#pragma once

#include <Spore\MathUtils.h>

namespace Simulator
{
	/// Settings of the orbit of a planet or celestial body in a solar system.
	/// These are all mathematical properties to define an elliptical orbit.
	/// `mPlaneNormal` describes the plane of rotation, whereas 
	/// `mEccentricty` and `mPerihelion` describe the ellipse in that plane.
	/// 
	/// This class saves all its parameters except `mCache`. `mCache` is precalculated from the 
	/// other parameters when the data is loaded, so if you change one of the parameters you
	/// have to calculate the cache again using Precalculate().
	class cEllipticalOrbit
	{
	public:
		struct OrbitCache
		{
			/// The `a` parameter of an ellipse, also known as semi-major axis, 
			/// `length(mPerihelion) / (1 - mEccentricity)`
			/* 00h */	float mSemiMajorAxis;
			/// `mSemiMajorAxis * mSemiMajorAxis`
			/* 04h */	float mSemiMajorAxisSquared;
			/// The `b` parameter of an ellipse, also known as semi-minor axis, 
			/// `sqrt(mSemiMajorAxisSquared - mFociSquared)`
			/* 08h */	float mSemiMinorAxis;
			/// `mSemiMinorAxis * mSemiMinorAxis`
			/* 0Ch */	float mSemiMinorAxisSquared;
			/// The `c` parameter of an ellipse, `mSemiMajorAxis * mEccentricity`
			/* 10h */	float mFoci;
			/// `mFoci * mFoci`
			/* 14h */	float mFociSquared;
			/// `mEccentricity * mEccentricity`
			/* 18h */	float mEccentricitySquared;
			/// `(a^2 + b^2) * pi / 2`
			/* 1Ch */	float field_1C;
			/// `mPerihelion / length(mPerihelion)`
			/* 20h */	Math::Vector3 mPerihelionNormalized;
			/// `crossProduct(mPlaneNormal, mPerihelion)`
			/* 2Ch */	Math::Vector3 mDescendingNode;
			/// Focus closest to the perihelion, the object orbits around this. `mFoci * mPerihelionNormalized`
			/* 38h */	Math::Vector3 mFocus;
		};

		/// If true, the orbit is null (so there is no orbit at all)
		/* 00h */	bool mbNullOrbit;  // true
		/// Normal vector of the plane in which the planet orbits. The planet never leaves that plane.
		/* 04h */	Math::Vector3 mPlaneNormal;
		/// Eccentricity of the ellipse of the orbit; 0.0 is a circular orbit.
		/* 10h */	float mEccentricity;
		/// Point of the orbit in which the planet is closest to the star. Also known as periapsis.
		/* 14h */	Math::Vector3 mPerihelion;
		/// Time it takes, in real seconds, to complete one orbit (i.e. how long an astronomical year is)
		/* 20h */	float mPeriod;
		/* 24h */	OrbitCache mCache;

		/// Calculates all the valeus in `mCache` using the rest of parameters in this class.
		/// This must be called every time a parameter is changed.
		void Precalculate();
	};
	ASSERT_SIZE(cEllipticalOrbit::OrbitCache, 0x44);
	ASSERT_SIZE(cEllipticalOrbit, 0x68);

	namespace Addresses(cEllipticalOrbit)
	{
		DeclareAddress(Precalculate);  // 0xFE8C10
	}
}