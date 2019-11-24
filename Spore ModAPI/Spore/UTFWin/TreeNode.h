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

#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\IDrawable.h>

#include <EASTL\string.h>
#include <EASTL\intrusive_list.h>

namespace UTFWin
{
	class WinTreeView;

	class ITreeNode
	{
	public:
		virtual ~ITreeNode() {};

	protected:
		int mnRefCount;
	};

	class TreeNode : public ILayoutElement, public ITreeNode, public intrusive_list_node
	{
	public:
		static const uint32_t TYPE = 0xD02AFC2B;

		TreeNode(WinTreeView* pTreeView);
		virtual ~TreeNode() {};

		/* 18h */	virtual void func18h(int, int);
		/* 1Ch */	virtual void func1Ch();
		/* 20h */	virtual void func20h();
		/* 24h */	virtual bool func24h();
		/* 28h */	virtual bool func28h();
		/* 2Ch */	virtual bool func2Ch();
		/* 30h */	virtual void func30h(int);
		/* 34h */	virtual void func34h(int, int);

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		// My own addition; without these we cannot work with treeviews!

		const wchar_t* GetCaption() const;
		void SetCaption(const wchar_t* pCaption);

		IDrawable* GetIcon() const;
		void SetIcon(IDrawable* pIconDrawable);

		void AddNode(TreeNode* pNode);
		void RemoveNode(TreeNode* pNode);

		void Update();  // ?

	protected:
		/* 14h */	WinTreeView* mpTreeView;
		/* 18h */	TreeNode* mpParent;
		/* 1Ch */	intrusive_list<TreeNode> mChildren;
		/* 24h */	int field_24;
		/* 28h */	int mnNodeFlags;  // 2
		/* 2Ch */	uint32_t mTextStyleID;
		/* 30h */	int field_30;
		/* 34h */	wstring mCaption;
		/* 44h */	uint32_t mNodeID;
		/* 48h */	intrusive_ptr<IDrawable> mpIcon;
		/* 4Ch */	intrusive_ptr<Object> field_4C;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(TreeNode) == 0x50, "sizeof(TreeNode) != 50h");

	namespace Addresses(TreeNode)
	{
		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);
		DeclareAddress(func18h);
		DeclareAddress(func1Ch);
		DeclareAddress(func20h);
		DeclareAddress(func24h);
		DeclareAddress(func28h);
		DeclareAddress(func2Ch);
		DeclareAddress(func30h);
		DeclareAddress(func34h);

	}

	inline const wchar_t* TreeNode::GetCaption() const
	{
		return mCaption.c_str();
	}
	inline void TreeNode::SetCaption(const wchar_t* pCaption)
	{
		mCaption = pCaption;
	}


	inline IDrawable* TreeNode::GetIcon() const
	{
		return mpIcon.get();
	}
	inline void TreeNode::SetIcon(IDrawable* pIconDrawable)
	{
		mpIcon = pIconDrawable;
	}


	inline void TreeNode::AddNode(TreeNode* pNode)
	{
		mChildren.push_back(*pNode);
		pNode->mpParent = this;


		pNode->Update();
		Update();
	}

	inline void TreeNode::RemoveNode(TreeNode* pNode)
	{
		mChildren.remove(*pNode);
		pNode->mpParent = nullptr;
		
		pNode->Update();
		Update();
	}
}