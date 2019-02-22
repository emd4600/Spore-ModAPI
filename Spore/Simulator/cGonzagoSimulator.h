/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#pragma once

#include <Spore\Object.h>
#include <Spore\Simulator\ISimulatorSerializable.h>

namespace Simulator
{
	class cGonzagoSimulator
		: public DefaultRefCounted
		, public ISimulatorSerializable
	{
	public:
		/* 10h */	virtual void func10h(int, int);
		/* 14h */	virtual char16_t* GetName(int);
		/* 18h */	virtual void func18h(int);

	protected:
		/* 0Ch */	bool field_0C;
		/* 0Dh */	bool field_0D;
		/* 0Eh */	bool field_0E;
	};
}