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
#include <Spore\Simulator\Serialization.h>

#define ISimulatorSerializablePtr eastl::intrusive_ptr<Simulator::ISimulatorSerializable>

namespace Simulator
{
	class ISimulatorSerializable
		: public Object
	{
	public:
		static const uint32_t TYPE = 0x179C807;

		virtual ~ISimulatorSerializable() {}

		/* 10h */	virtual bool Write(ISerializerStream* stream) = 0;
		/* 14h */	virtual bool Read(ISerializerStream* stream) = 0;
		/* 18h */	virtual bool ISimulatorSerializable_func18h() = 0;
		/* 1Ch */	virtual bool WriteToXML(XmlSerializer*) = 0;
		/* 20h */	virtual uint32_t GetNounID() const = 0;
	};

	// Used by cEmpire
	class ISimulatorSerializableRefCounted
		: public ISimulatorSerializable
		, public RefCountTemplate
	{
	};
}