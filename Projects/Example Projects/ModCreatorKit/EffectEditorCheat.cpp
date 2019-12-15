/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModCreatorKit.
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
#include "stdafx.h"
#include "EffectEditorCheat.h"

#include <Spore\App\ICheatManager.h>
#include <Spore\GameModes.h>


EffectEditorCheat::EffectEditorCheat()
{
}


EffectEditorCheat::~EffectEditorCheat()
{
}

void EffectEditorCheat::AddCheat()
{
	CheatManager.AddCheat("effectEditor", new EffectEditorCheat());
}


void EffectEditorCheat::ParseLine(const ArgScript::Line& line)
{
	GameModeManager.SetActiveModeByName("EffectEditorMode");
}

const char* EffectEditorCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Enters into an effect viewer that is connected in real time with SporeModderFX";
}
