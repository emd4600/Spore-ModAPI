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

namespace Swarm
{
	enum AppFlags
	{
		/* 00h */	kAppFlagDeepWater,
		/* 01h */	kAppFlagShallowWater,
		/* 02h */	kAppFlagLowerAtmosphere,
		/* 03h */	kAppFlagUpperAtmosphere,
		/* 04h */	kAppFlagEnglish,
		/* 05h */	kAppFlagPlanetHasWater,
		/* 06h */	kAppFlagCinematics,
		/* 07h */	kAppFlagCellGameMode,
		/* 08h */	kAppFlagCreatureGameMode,
		/* 09h */	kAppFlagTribeGameMode,
		/* 0Ah */	kAppFlagGGEMode,
		/* 0Bh */	kAppFlagCivGameMode,
		/* 0Ch */	kAppFlagSpaceGameMode,
		/* 0Dh */	kAppFlagAtmoLow,
		/* 0Eh */	kAppFlagAtmoMed,
		/* 0Fh */	kAppFlagAtmoHigh,
		/* 10h */	kAppFlagEditorMode,
		/* 11h */	kAppFlagSpaceGameOutOfUFO,
		/* 12h */	kAppFlagSpaceGameGalaxyMode,
		/* 13h */	kAppFlagSpaceGameSolarMode,
		/* 14h */	kAppFlagSpaceGamePlanetMode,
		/* 15h */	kAppFlagIsNight,
		/* 16h */	kAppFlagIsRaining,
		/* 17h */	kAppFlagWeatherIce,
		/* 18h */	kAppFlagWeatherCold,
		/* 19h */	kAppFlagWeatherWarm,
		/* 1Ah */	kAppFlagWeatherHot,
		/* 1Bh */	kAppFlagWeatherLava
	};
}
