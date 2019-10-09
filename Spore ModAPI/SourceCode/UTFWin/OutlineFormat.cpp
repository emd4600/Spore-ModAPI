/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\UTFWin\OutlineFormat.h>

namespace UTFWin
{
	void OutlineFormat::SetStrength(int strength)
	{
		this->strength = strength;

		switch (strength)
		{
		case 1:
			smoothness = 0.0004f;
			saturation = 0.25f;
			break;

		case 2:
			smoothness = 0.0003f;
			saturation = 0.5f;
			break;

		case 3:
			smoothness = 0.0002f;
			saturation = 0.75f;
			break;

		case 4:
			smoothness = 0.0001f;
			saturation = 1.0f;
			break;

		case 5:
			smoothness = 0.0f;
			saturation = 1.25f;
			break;

		case 6:
			smoothness = 0.0f;
			saturation = 1.5f;
			break;

		case 7:
			smoothness = 0.0f;
			saturation = 1.85f;
			break;

		case 8:
			smoothness = 0.0f;
			saturation = 2.35f;
			break;

		case 9:
			smoothness = 0.0f;
			saturation = 3.15f;
			break;
		}
	}

	void OutlineFormat::SetSize(int size)
	{
		this->size = size;

		switch (size)
		{
		case 1:
			this->sizeX = 1.0f;
			this->sizeY = 1.0f;
			break;

		case 2:
			this->sizeX = 2.0f;
			this->sizeY = 2.0f;
			break;

		case 3:
			this->sizeX = 3.0f;
			this->sizeY = 3.0f;
			break;

		case 4:
			this->sizeX = 4.0f;
			this->sizeY = 4.0f;
			break;

		case 5:
			this->sizeX = 5.0f;
			this->sizeY = 5.0f;
			break;

		case 6:
			this->sizeX = 6.0f;
			this->sizeY = 6.0f;
			break;

		case 7:
			this->sizeX = 7.0f;
			this->sizeY = 7.0f;
			break;

		case 8:
			this->sizeX = 8.0f;
			this->sizeY = 8.0f;
			break;

		case 9:
			this->sizeX = 9.0f;
			this->sizeY = 9.0f;
			break;
		}
	}
}