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
#include <Spore\Editors\PlayModeAnimations.h>
#include <Spore\Editors\PlayModeActor.h>
#include <Spore\Editors\PlayModeBackgrounds.h>

//TODO vftable 10h OnMouseClick sub_62A810

namespace Editors
{
	//PLACEHOLDER complete this
	class EditorPlayMode : public DefaultRefCounted
	{
	public:
		// sub_62C570 Update

		// sub_639D70 walks?

		/* 10h */	virtual bool OnMouseDown(int mouseButton, float mouseX, float mouseY, int flags);
		/* 14h */	virtual bool OnMouseUp(int mouseButton, float mouseX, float mouseY, int flags);
		/* 18h */	virtual bool OnMouseMove(float mouseX, float mouseY, int state);
		/* 1Ch */	virtual bool OnKeyDown(int virtualKey, int modifiers);
		/* 20h */	virtual bool OnKeyUp(int virtualKey, int modifiers);
		// one function more, related with UI

	public:
		/* 08h */	char padding_08[0x7C - 0x8];
		/* 7Ch */	PlayModeActor** mpMainActor;  // at 10h, AnimatedCreatureController
		/* 80h */	char padding_80[0x3588 - 0x80];
		/* 3588h */	PlayModeAnimations mAnimations;
		/* 3618h */	PlayModeBackgrounds mBackgrounds;
		//TODO 3614h is Editor
		//TODO 36D0h mNumAdditionalActors
	};
}