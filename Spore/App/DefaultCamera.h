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

#include <Spore\App\ICamera.h>

namespace App
{
	///
	/// Defines a default implementation of ICamera. This can be used to create a new camera only giving implementations for the methods needed.
	///

	class DefaultCamera : public ICamera
	{
	public:
		DefaultCamera();

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t typeID) const override;

		/* 10h */	virtual bool OnAttach(ICameraManager* pManager) override { return false; };
		/* 14h */	virtual bool OnDeattach() override { return false; };
		/* 18h */	virtual void OnEnter() override {};
		/* 1Ch */	virtual void OnExit() override {};
		/* 20h */	virtual void Update(int nDeltaTime, Viewer* pViewer) override {};
		/* 24h */	virtual void func24h(bool) override {};
		/* 28h */	virtual bool OnKeyDown(int virtualKey, int modifiers) override { return false; };
		/* 2Ch */	virtual bool OnKeyUp(int virtualKey, int modifiers) override { return false; };
		/* 30h */	virtual bool OnMouseDown(int mouseState, float mouseX, float mouseY, int flags) override { return false; };
		/* 34h */	virtual bool OnMouseUp(int mouseState, float mouseX, float mouseY, int flags) override { return false; };
		/* 38h */	virtual bool OnMouseMove(float mouseX, float mouseY, int state) override { return false; };
		/* 3Ch */	virtual bool OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, int state) override { return false; };
		/* 40h */	virtual bool func40h(int) override { return false; };
		/* 44h */	virtual bool func44h(int) override { return false; };
		/* 48h */	virtual bool func48h(int) override { return false; };
		/* 4Ch */	virtual PropertyList* GetPropertyList() override { return nullptr; };
		/* 50h */	virtual void Initialize() override {};
		/* 54h */	virtual void func54h(Vector3& dst) override;

	protected:
		int mnRefCount;
	};
}