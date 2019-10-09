#pragma once

#error "Not yet implemented"
// PLACEHOLDER

namespace Simulator
{
	class cCivilization
	{
		/* 30h */	uint32_t mPolticalID;

		/* 6Ch */	cCultureSet mCultureSet;

		/* 98h */	float mMoney;

		/* 4Ch */	virtual uint32_t GetPoliticalID() const;

		// 0xBF16F0 float GetVehicleCost(VehiclePurpose speciality) const;
		// 0xBEEC50 float GetMoney() const;
	};
}