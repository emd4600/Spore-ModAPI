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

#include <Spore\UTFWin\UTFWinObject.h>
#include <Spore\UTFWin\Serialization.h>

#define ILayoutElementPtr eastl::intrusive_ptr<UTFWin::ILayoutElement>

namespace UTFWin
{
	enum class AlignmentH
	{
		Left = 1,
		Right = 2,
		Center = 3
	};

	enum class AlignmentV
	{
		Top = 1,
		Bottom = 2,
		Middle = 3
	};

	enum class FontAlignmentH
	{
		Default = 0,
		Left = 1,
		Right = 2,
		Center = 3
	};

	enum class FontAlignmentV
	{
		Default = 0,
		Top = 1,
		Bottom = 2,
		Middle = 3
	};

	enum class Orientation
	{
		Horizontal = 1,
		Vertical = 2
	};

	enum class ButtonTypes
	{
		Standard = 1,
		Toggle = 2,
		Radio = 3
	};

	enum class StateIndices : uint32_t
	{
		Normal = 0,
		Disabled = 1,
		Highlighted = 2,
		Active = 3,
		CheckedNormal = 4,
		CheckedDisabled = 5,
		CheckedHighlighted = 6,
		CheckedActive = 7
	};

	///
	/// This class represents an element that is part of a user interfaces. All ILayoutElement classes are able to implement a
	/// Serializer, allowing it to be saved and loaded from SPUI files.
	///
	class ILayoutElement : public UTFWinObject
	{
	public:
		virtual void SetSerializer(Serializer& dst) = 0;

		///
		/// Returns the ID that identifies this type of element in a SPUI file.
		///
		virtual uint32_t GetProxyID() const = 0;

		static const uint32_t TYPE = 0xEEC58382;

		enum
		{
			kLeft = 0,
			kTop = 1,
			kRight = 2,
			kBottom = 3
		};

	};

	///
	/// A default implementation of ILayoutElement.
	///
	class DefaultLayoutElement : public ILayoutElement
	{
	public:

		DefaultLayoutElement();

		virtual int AddRef();
		virtual int Release();

	protected:
		int mnRefCount;
	};
}