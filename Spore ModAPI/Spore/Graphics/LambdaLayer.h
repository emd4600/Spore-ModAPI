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

#include <Spore\Graphics\ILayer.h>
#include <EASTL\functional.h>

namespace Graphics
{
	class LambdaLayer
		: public ILayer
	{
	public:
		typedef void(*Render_t)(int, int, App::cViewer**, RenderStatistics&);

		LambdaLayer(Render_t);

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void DrawLayer(int, int, App::cViewer**, RenderStatistics&) override;

	protected:
		int mnRefCount;
		Render_t mFunction;
	};
}
