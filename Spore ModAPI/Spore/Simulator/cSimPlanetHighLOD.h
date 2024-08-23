#pragma once

#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\MathUtils.h>
#include <EASTL\fixed_list.h>

#define cSimPlanetHighLODPtr eastl::intrusive_ptr<Simulator::cSimPlanetHighLOD>

namespace Simulator
{
	class cSimPlanetHighLOD
		: public cGonzagoSimulator
	{
	public:
		static const uint32_t TYPE = 0xF04D0722;

		/// Completely destroys a city in this planet, removing all the walls and buildings and showing a fire effect.
		/// You can optionally specifiy the empire ID of who destroyed the city, which will apply bad relations with the aggressed community.
		/// @param pCity The city to be destroyed.
		/// @param aggressorEmpireID Optional, ID of the empire who attacked the city.
		void DestroyCity(cCity* pCity, uint32_t agressorEmpireID = -1);

	public:
		struct UnkClass
		{
			char field_0[16];
		};
		ASSERT_SIZE(UnkClass, 0x10);

		/* 10h */	int field_10;  // 1
		/* 14h */	bool field_14;
		/* 18h */	ObjectPtr field_18;
		/* 1Ch */	ObjectPtr field_1C;
		/* 20h */	int mSimulationStepTime;
		/* 24h */	int mColonyUpdateStepTime;  // not initialized
		/* 28h */	DefaultRefCountedPtr field_28;
		/* 2Ch */	ObjectPtr field_2C;
		/* 30h */	ObjectPtr field_30;
		/* 34h */   eastl::sp_fixed_list<UnkClass, 10> field_34;
		/* 158h */	bool field_158;
		/* 15Ch */	Math::Vector3 field_15C;  // X_AXIS
		/* 168h */	int field_168;  // not initialized
		/* 16Ch */	int field_16C;  // not initialized
		/* 170h */	cGonzagoTimer field_170;
		/* 190h */	int field_190;  // not initialized
		/* 194h */	int field_194;  // not initialized
		/* 198h */	int field_198;  // not initialized
		/* 19Ch */	eastl::vector<int> field_19C;
		/* 1B0h */	DefaultRefCountedPtr field_1B0;
		/* 1B4h */	bool field_1B4;
		/* 1B8h */	int field_1B8;
		/* 1BCh */	ObjectPtr field_1BC;
		/* 1C0h */	eastl::map<int, ObjectPtr> field_1C0;
		/* 1DCh	*/	ObjectPtr field_1DC;
		/* 1E0h */	bool field_1E0;
		/* 1E4h */	void* field_1E4;
	};
	ASSERT_SIZE(cSimPlanetHighLOD, 0x1E8);

	namespace Addresses(cSimPlanetHighLOD)
	{
		DeclareAddress(DestroyCity);
	}
}