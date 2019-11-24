#ifndef MODAPI_DLL_EXPORT
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

#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\TreeNode.h>
#include <Spore\UTFWin\IButton.h>
#include <Spore\UTFWin\ITextEdit.h>
#include <SourceCode\Utility.h>

namespace UTFWin
{

	int DefaultDrawable::AddRef()
	{
		return ++mnRefCount;
	}

	int DefaultDrawable::Release()
	{
		if (--mnRefCount == 0)
		{
			delete this;
		}
		return mnRefCount;
	}

	void* DefaultDrawable::Cast(uint32_t type) const
	{
		if (type == IDrawable::TYPE || type == Object::TYPE)
		{
			return (IDrawable*) this;
		}
		else
		{
			return nullptr;
		}
	}


	void DefaultDrawable::Paint(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params)
	{

	}

	bool DefaultDrawable::IsColliding(const Math::Rectangle& area, const Math::Point& point, RenderParams& params)
	{
		return true;
	}

	bool DefaultDrawable::GetDimensions(Dimensions& dst, int state, int index)
	{
		return false;
	}

	bool DefaultDrawable::UseCollision(uint32_t type, bool& dst)
	{
		return false;
	}


	//// TreeNode ////

	DEFAULT_REFCOUNT(TreeNode);

	auto_METHOD_VIRTUAL_VOID(TreeNode, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(TreeNode, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(TreeNode, TreeNode, func18h, Args(int arg_0, int arg_4), Args(arg_0, arg_4));
	auto_METHOD_VIRTUAL_VOID_(TreeNode, TreeNode, func1Ch);
	auto_METHOD_VIRTUAL_VOID_(TreeNode, TreeNode, func20h);
	auto_METHOD_VIRTUAL_(TreeNode, TreeNode, bool, func24h);
	auto_METHOD_VIRTUAL_(TreeNode, TreeNode, bool, func28h);
	auto_METHOD_VIRTUAL_(TreeNode, TreeNode, bool, func2Ch);
	auto_METHOD_VIRTUAL_VOID(TreeNode, TreeNode, func30h, Args(int arg_0), Args(arg_0));
	auto_METHOD_VIRTUAL_VOID(TreeNode, TreeNode, func34h, Args(int arg_0, int arg_4), Args(arg_0, arg_4));



	void* TreeNode::Cast(uint32_t type) const  
	{
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == TreeNode::TYPE)
		{
			return (TreeNode*) this;
		}
		else
		{
			return nullptr;
		}
	}

	TreeNode::TreeNode(WinTreeView* pView)
		: mpTreeView(pView)
		, mpParent(nullptr)
		, mChildren()
		, field_24()
		, mnNodeFlags(2)
		, mTextStyleID(0)
		, field_30()
		, mCaption()
		, mNodeID(0)
		, mpIcon(nullptr)
		, field_4C(nullptr)
	{
	}

	void TreeNode::Update()
	{
		TreeNode* pNode = this;

		while (pNode != nullptr)
		{
			pNode->field_24 = 1;
			if (pNode->mnNodeFlags & 2)
			{
				for (TreeNode& pChild : pNode->mChildren)
				{
					pNode->field_24 += pChild.field_24;
				}
			}

			pNode = pNode->mpParent;
		}
	}

	IButton* IButton::Create()
	{
		IWindow* pWindow = ((IWindow*(__stdcall*)(void*, void*)) (GetAddress(IButton, Create)))(nullptr, nullptr);
		return object_cast<IButton>(pWindow);
	}

	ITextEdit* ITextEdit::Create()
	{
		IWindow* pWindow = ((IWindow*(__stdcall*)(void*, void*)) (GetAddress(ITextEdit, Create)))(nullptr, nullptr);
		return object_cast<ITextEdit>(pWindow);
	}
}
#endif
