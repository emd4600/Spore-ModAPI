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

#include <Spore\App\IGameMode.h>

namespace App
{
	///
	/// A class that provides default implementation for all the methods in a IGameMode. 
	/// With this, one can create an IGameMode only implementing the necessary methods.
	/// It is recommended that if you implement the Initialize() method, you implement the Dispose() one as well.
	/// In the same way, OnEnter() should be paired with OnExit()
	///
	class DefaultGameMode : public IGameMode
	{
	public:
		DefaultGameMode();

		/* 00h */	virtual int AddRef() override;
		/* 04h */	virtual int Release() override;
		/* 08h */	virtual ~DefaultGameMode();
		/* 0Ch */	virtual bool func0Ch() override;
		/* 10h */	virtual bool Initialize(IGameModeManager* pManager) override;
		/* 14h */	virtual bool Dispose() override;
		/* 18h */	virtual bool OnEnter() override;
		/* 1Ch */	virtual void OnExit() override;
		/* 20h */	virtual void* func20h(int) override;
		/* 24h */	virtual bool OnKeyDown(int virtualKey, int modifiers) override;
		/* 28h */	virtual bool OnKeyUp(int virtualKey, int modifiers) override;
		/* 2Ch */	virtual bool OnMouseDown(int mouseState, float mouseX, float mouseY, int flags) override;
		/* 30h */	virtual bool OnMouseUp(int mouseState, float mouseX, float mouseY, int flags) override;
		/* 34h */	virtual bool OnMouseMove(float mouseX, float mouseY, int state) override;
		/* 38h */	virtual bool OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, int state) override;
		/* 3Ch */	virtual void Update(float fDelta1, float fDelta2) override;

	protected:
		int mnRefCount;
	};
}