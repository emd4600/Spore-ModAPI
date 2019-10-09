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
#include <Spore\App\MessageListenerData.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\SubSystem\ISimulatorUIGraphic.h>
#include <EASTL\list.h>

namespace Simulator
{
	class cSimulatorSystem
		: public App::IMessageListener
		, public IVirtual
	{
	public:
		/* 10h */	virtual bool Initialize();
		/* 14h */	virtual bool Dispose();
		/* 18h */	virtual bool InitializeSubSystems();
		/* 1Ch */	virtual bool DisposeSubSystems();
		/* 20h */	virtual int func20h(uint32_t);
		/* 24h */	virtual void InitializeGameModes();
		/* 28h */	virtual void func28h(int);
		/* 2Ch */	virtual void Update(int milliseconds);

		/// Calls UpdateUIGraphics(), updates all the UI updatable elements.
		/// Also calls Update() on all the system strategies.
		/* 30h */	virtual void PostUpdate(int milliseconds);  // also update?

		/// Calls update on all the updatable UI elements registered in the system.
		/// Also updates the game terrain cursor.
		/* 34h */	virtual void UpdateUIGraphics(int milliseconds);  // does something with game terrain cursor
		// the boolean is irrelevant
		/* 38h */	virtual void AddUpdatableUIGraphic(ISimulatorUIGraphic*, bool=true);  // add updatable UI
		/* 3Ch */	virtual bool ContainsUpdatableUIGraphic(ISimulatorUIGraphic*);
		/* 40h */	virtual bool RemoveUpdatableUIGraphic(ISimulatorUIGraphic*);
		/* 44h */	virtual void ClearUpdatableUIGraphics();
		/* 48h */	virtual bool Write(int);
		/* 4Ch */	virtual bool Read(int);
		/* 50h */	virtual bool func50h();
		/* 54h */	virtual bool func54h();
		/* 58h */	virtual bool func58h();
			
	protected:
		/* 08h */	int mnRefCount;
		/* 0Ch */	bool field_0C;  // notInEditor?
		/* 0Dh */	bool field_0D;
		/* 0Eh */	bool field_0E;
		/* 10h */	float field_10;
		/* 14h */	float field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		// list of UIs that can be updated?
		// for example, city rollover, only appears when mouse over city
		/* 20h */	list<intrusive_ptr<ISimulatorUIGraphic>> field_20;
		/* 2Ch */	bool field_2C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
		/* 38h */	int field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	App::MessageListenerData mMessageData;
		/* 5Ch */	vector<intrusive_ptr<cStrategy>> mSubSystems;

	public:
		static cSimulatorSystem* Get();
	};

	inline cSimulatorSystem* SimulatorSystem() {
		return cSimulatorSystem::Get();
	}

	/// Initializes certain Simulator systems so that most things can be used without being in a star or planet.
	/// This method does:
	/// - Uses the StarManager temporary star with a temporary planet on it, and sets those as the current
	/// star/planet in SpacePlayerData.
	/// - Calls the PrepareSimulator() method in GameViewManager so that the simulator objects are displayed
	/// on the screen.
	void InitializeWithoutPlanet();

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSimulatorSystem) == 0x70, "sizeof(cSimulatorSystem) != 70h");

	namespace Addresses(cSimulatorSystem)
	{
		DeclareAddress(Get, SelectAddress(0xB3D190, NO_ADDRESS, 0xB3D330));
	}
}