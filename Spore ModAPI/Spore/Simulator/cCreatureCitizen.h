#pragma once

#include <Spore\Simulator\cCreatureBase.h>

#define cCreatureCitizenPtr intrusive_ptr<Simulator::cCreatureCitizen>

namespace Simulator
{
	class cCreatureCitizen
		: public cCreatureBase
	{
	public:
		static const uint32_t TYPE = 0x4F176642;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		//TODO
	};
}