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

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IWinProc.h>

namespace UTFWin
{
	template<typename Pointer, typename Reference>
	class ChildrenIterator
	{
	public:
		intrusive_list_node* mpNode;

	public:
		ChildrenIterator(intrusive_list_node* pWindow);

		Pointer operator*() const;
		Pointer operator->() const;

		ChildrenIterator& operator++();

		ChildrenIterator operator++(int);

		ChildrenIterator& operator--();

		ChildrenIterator operator--(int);

		bool operator!=(ChildrenIterator &i2) const;
		bool operator!=(const ChildrenIterator &i2) const;
	};

	template<typename Pointer, typename Reference>
	inline ChildrenIterator<Pointer, Reference>::ChildrenIterator(intrusive_list_node* pNode)
		: mpNode(pNode)
	{
	}

	template<typename Pointer, typename Reference>
	inline Pointer ChildrenIterator<Pointer, Reference>::operator*() const
	{
		return (Pointer) mpNode;
	}
	template<typename Pointer, typename Reference>
	inline Pointer ChildrenIterator<Pointer, Reference>::operator->() const
	{
		return (Pointer) mpNode;
	}

	template<typename Pointer, typename Reference>
	inline ChildrenIterator<Pointer, Reference>& ChildrenIterator<Pointer, Reference>::operator++()
	{
		mpNode = mpNode->mpNext;
		return *this;
	}

	template<typename Pointer, typename Reference>
	inline ChildrenIterator<Pointer, Reference> ChildrenIterator<Pointer, Reference>::operator++(int)
	{
		ChildrenIterator<Pointer, Reference> tmp = *this;
		tmp.mpNode = mpNode->mpNext;
		return tmp;
	}

	template<typename Pointer, typename Reference>
	inline ChildrenIterator<Pointer, Reference>& ChildrenIterator<Pointer, Reference>::operator--()
	{
		mpNode = mpNode->mpPrev;
		return *this;
	}

	template<typename Pointer, typename Reference>
	inline ChildrenIterator<Pointer, Reference> ChildrenIterator<Pointer, Reference>::operator--(int)
	{
		ChildrenIterator<Pointer, Reference> tmp = *this;
		tmp.mpNode = mpNode->mpPrev;
		return tmp;
	}

	template<typename Pointer, typename Reference>
	bool ChildrenIterator<Pointer, Reference>::operator!=(ChildrenIterator &i2) const
	{
		return mpNode != i2.mpNode;
	}

	template<typename Pointer, typename Reference>
	bool ChildrenIterator<Pointer, Reference>::operator!=(const ChildrenIterator &i2) const
	{
		return mpNode != i2.mpNode;
	}


	class WindowChildren
	{
	public:
		//typedef typename IWindowList_t::iterator iterator;
		//typedef typename IWindowList_t::const_iterator const_iterator;

		typedef typename ChildrenIterator<IWindow*, IWindow&> iterator;
		typedef typename ChildrenIterator<const IWindow*, const IWindow&> const_iterator;

		IWindow* mpParentWindow;

		WindowChildren(IWindow* pWindow);

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;
	};

	inline WindowChildren::WindowChildren(IWindow* pWindow)
		: mpParentWindow(pWindow)
	{
	}


	inline WindowChildren::iterator WindowChildren::begin() 
	{ 
		uint32_t ptr = (uint32_t)mpParentWindow->GetChildrenBegin().mpNode;
		return iterator(mpParentWindow->GetChildrenBegin().mpNode);
	}
	inline WindowChildren::const_iterator WindowChildren::begin() const 
	{ 
		return const_iterator(mpParentWindow->GetChildrenBegin().mpNode);
	}
	inline WindowChildren::const_iterator WindowChildren::cbegin() const 
	{ 
		return const_iterator(mpParentWindow->GetChildrenBegin().mpNode);
	}
	inline WindowChildren::iterator WindowChildren::end() 
	{ 
		return iterator(mpParentWindow->GetChildrenEnd().mpNode);
	}
	inline WindowChildren::const_iterator WindowChildren::end() const 
	{ 
		return const_iterator(mpParentWindow->GetChildrenEnd().mpNode);
	}
	inline WindowChildren::const_iterator WindowChildren::cend() const 
	{ 
		return const_iterator(mpParentWindow->GetChildrenEnd().mpNode);
	}



	//// WIN PROCEDURES ////

	template<typename Pointer, typename Reference>
	class ProcIterator
	{
	public:
		const IWindow* mpParentWindow;
		Pointer mpProc;

	public:
		ProcIterator(const IWindow* pParentWindow);
		ProcIterator(const IWindow* pParentWindow, Pointer pProcedure);

		Pointer operator*() const;
		Pointer operator->() const;

		ProcIterator& operator++();

		ProcIterator operator++(int);

		bool operator!=(ProcIterator &i2) const;
		bool operator!=(const ProcIterator &i2) const;
	};

	template<typename Pointer, typename Reference>
	inline ProcIterator<Pointer, Reference>::ProcIterator(const IWindow* pParentWindow)
		: mpParentWindow(pParentWindow)
		, mpProc(nullptr)
	{
	}
	template<typename Pointer, typename Reference>
	inline ProcIterator<Pointer, Reference>::ProcIterator(const IWindow* pParentWindow, Pointer pProcedure)
		: mpParentWindow(pParentWindow)
		, mpProc(pProcedure)
	{
	}

	template<typename Pointer, typename Reference>
	inline Pointer ProcIterator<Pointer, Reference>::operator*() const
	{
		return mpProc;
	}
	template<typename Pointer, typename Reference>
	inline Pointer ProcIterator<Pointer, Reference>::operator->() const
	{
		return mpProc;
	}

	template<typename Pointer, typename Reference>
	inline ProcIterator<Pointer, Reference>& ProcIterator<Pointer, Reference>::operator++()
	{
		return ProcIterator(mpParentWindow, mpParentWindow->GetNextWinProc(mpProc));
	}

	template<typename Pointer, typename Reference>
	inline ProcIterator<Pointer, Reference> ProcIterator<Pointer, Reference>::operator++(int)
	{
		return ProcIterator(mpParentWindow, mpParentWindow->GetNextWinProc(mpProc));
	}

	template<typename Pointer, typename Reference>
	inline bool ProcIterator<Pointer, Reference>::operator!=(ProcIterator &i2) const
	{
		return mpParentWindow != i2.mpParentWindow || mpProc != i2.mpProc;
	}

	template<typename Pointer, typename Reference>
	inline bool ProcIterator<Pointer, Reference>::operator!=(const ProcIterator &i2) const
	{
		return mpParentWindow != i2.mpParentWindow || mpProc != i2.mpProc;
	}


	class WindowProcedures
	{
	public:
		typedef typename ProcIterator<IWinProc*, IWinProc&> iterator;
		typedef typename ProcIterator<const IWinProc*, const IWinProc&> const_iterator;

		const IWindow* mpParentWindow;

		WindowProcedures(const IWindow* pWindow);

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;
	};

	inline WindowProcedures::WindowProcedures(const IWindow* pWindow)
		: mpParentWindow(pWindow)
	{
	}


	inline WindowProcedures::iterator WindowProcedures::begin()
	{
		return iterator(mpParentWindow, mpParentWindow->GetNextWinProc(nullptr));
	}
	inline WindowProcedures::const_iterator WindowProcedures::begin() const
	{
		return const_iterator(mpParentWindow, mpParentWindow->GetNextWinProc(nullptr));
	}
	inline WindowProcedures::const_iterator WindowProcedures::cbegin() const
	{
		return const_iterator(mpParentWindow, mpParentWindow->GetNextWinProc(nullptr));
	}
	inline WindowProcedures::iterator WindowProcedures::end()
	{
		return iterator(mpParentWindow, nullptr);
	}
	inline WindowProcedures::const_iterator WindowProcedures::end() const
	{
		return const_iterator(mpParentWindow, nullptr);
	}
	inline WindowProcedures::const_iterator WindowProcedures::cend() const
	{
		return const_iterator(mpParentWindow, nullptr);
	}
}