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
	namespace Components
	{
		class IEffectComponent
		{
		public:
			IEffectComponent();
			IEffectComponent(const IEffectComponent& other);
			virtual ~IEffectComponent() {};

			void AddRef();
			void Release();


		protected:
			int mnRefCount;
		};

		typedef IEffectComponent IEffectDescription;

		inline IEffectComponent::IEffectComponent()
			: mnRefCount(0)
		{

		}

		// We do nothing here; we don't want to copy the ref count!
		inline IEffectComponent::IEffectComponent(const IEffectComponent& other)
			: mnRefCount(0)
		{

		}

		inline void IEffectComponent::AddRef()
		{
			mnRefCount++;
		}
		inline void IEffectComponent::Release()
		{
			if (mnRefCount-- == 0)
			{
				delete this;
			}
		}
	}

}