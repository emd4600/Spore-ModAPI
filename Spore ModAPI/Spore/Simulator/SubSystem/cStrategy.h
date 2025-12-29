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
#include <Spore\Simulator\SubSystem\cSavedGameHeader.h>

#define ISimulatorStrategyPtr eastl::intrusive_ptr<Simulator::ISimulatorStrategy>
#define cStrategyPtr eastl::intrusive_ptr<Simulator::cStrategy>

namespace Simulator
{
	class ISimulatorStrategy
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual void Initialize() = 0;
		/* 0Ch */	virtual void Dispose() = 0;
		/* 10h */	virtual const char* GetName() const = 0;
		/* 14h */	virtual void OnModeExited(uint32_t previousModeID, uint32_t newModeID) = 0;
		/* 18h */	virtual void OnModeEntered(uint32_t previousModeID, uint32_t newModeID) = 0;
		/* 1Ch */	virtual uint32_t GetLastGameMode() const = 0;
		/* 20h */	virtual uint32_t GetCurrentGameMode() const = 0;
		/* 24h */	virtual bool func24h(uint32_t) = 0;
		/* 28h */	virtual bool Write(ISerializerStream*) = 0;
		/* 2Ch */	virtual bool Read(ISerializerStream*) = 0;
		/* 30h */	virtual void OnLoad(const cSavedGameHeader& savedGame) = 0;
		/* 34h */	virtual bool WriteToXML(XmlSerializer*) = 0;
		/* 38h */	virtual void Update(int deltaTime, int deltaGameTime) = 0;
		// Called just before the game mode update function finishes
		/* 3Ch */	virtual void PostUpdate(int deltaTime, int deltaGameTime) = 0;
		/* 40h */	virtual void func40h(uint32_t) = 0;
		/* 44h */	virtual void func44h(uint32_t) = 0;
		/* 48h */	virtual void func48h() = 0;
		/* 4Ch */	virtual void func4Ch() = 0;
	};

	class cStrategy
		: public ISimulatorStrategy
		, public IVirtual
	{
	public:
		cStrategy();
		virtual ~cStrategy();

		int AddRef() override;
		int Release() override;

		void OnModeExited(uint32_t previousModeID, uint32_t newModeID) override;
		void OnModeEntered(uint32_t previousModeID, uint32_t newModeID) override;
		uint32_t GetLastGameMode() const override;
		uint32_t GetCurrentGameMode() const override;
		bool func24h(uint32_t) override;

		void OnLoad(const cSavedGameHeader& savedGame) override;

		void Update(int deltaTime, int deltaGameTime) override;
		void PostUpdate(int deltaTime, int deltaGameTime) override;
		void func40h(uint32_t) override;
		void func44h(uint32_t) override;
		void func48h() override;
		void func4Ch() override;

	public:
		/* 08h */	int mnRefCount;
		// NOTE: These 2 mode values can sometimes appear swapped when changing modes.
		/* 0Ch */	uint32_t mLastGameMode;  // -1
		/* 10h */	uint32_t mCurrentGameMode;  // -1
		/* 14h */	uint32_t field_14;  // -1
		/* 18h */	int field_18;
	};
	ASSERT_SIZE(cStrategy, 0x1C);
}

