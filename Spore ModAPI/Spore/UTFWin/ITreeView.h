#pragma once

#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\TreeNode.h>

namespace UTFWin
{
	class ITreeView : public UTFWinObject
	{
	public:
		static const uint32_t TYPE = 0xB02AECEC;

		enum ColorIndices
		{
			kColorText = 0,
			kColorBackground = 1,
			kColorDisabledText = 2,
			kColorDisabledBackground = 3,
			kColorSelectedText = 4,
			kColorSelectedBackground = 5,
			kColorHighlightedText = 6,
			kColorHighlightedBackground = 7,
			kColorConnectorLines = 8,

		};

		enum Params
		{
			kParamIndentWidth = 0,
			kParamLineWidth = 1,
			kParamLineIndent = 2,
			kParamIconSpacing = 3
		};

		/* 10h */	virtual IWindow* ToWindow() = 0;

		///
		/// Gets the color used for the specific component.
		/// @param index The component, in the ITreeView::kColor... values
		///
		/* 14h */	virtual Color GetColor(int index) const = 0;

		///
		/// Sets the color used for the specific component.
		/// @param index The component, in the ITreeView::kColor... values
		/// @param color The new color value.
		///
		/* 18h */	virtual void SetColor(int index, Color color) = 0;

		///
		/// Gets the width of the borders.
		///
		/* 1Ch */	virtual const Math::Rectangle& GetBorderWidth() const = 0;

		///
		/// Sets the width of the borders.
		/// @param value A Rectangle with the new borders width.
		///
		/* 20h */	virtual void SetBorderWidth(const Math::Rectangle& value) = 0;

		///
		/// Sets the value of the specified tree view flag. The flag must be one of the ITreeView::kFlag... values.
		/// @param flag The flag to set, one of the ITreeView::kFlag... values.
		/// @param value The new bool value of that flag.
		///
		/* 24h */	virtual void SetTreeViewFlag(int flag, bool value) = 0;

		///
		/// Gets the value of the tree view flags, which are the ITreeView::kFlag... values.
		///
		/* 28h */	virtual bool GetTreeViewFlags() const = 0;

		///
		/// Sets the height of individual rows.
		/// @param value The new row height.
		/// 
		/* 2Ch */	virtual void SetItemHeight(size_t value) = 0;

		///
		/// Gets the height of individual rows.
		///
		/* 30h */	virtual size_t GetItemHeight() const = 0;

		///
		/// Chagnes the value of the specified parameter, which can be one of the following:
		/// ITreeView::kParamIdentWidth, ITreeView::kParamLineWidth, ITreeView::kParamLineIndent and ITreeView::kParamIconSpacing
		/// @param paramIndex The parameter to change.
		/// @param value The new value of the parameter.
		///
		/* 34h */	virtual void SetParameter(int paramIndex, size_t value) = 0;

		///
		/// Gets the value of the specified parameter, which can be one of the following:
		/// ITreeView::kParamIdentWidth, ITreeView::kParamLineWidth, ITreeView::kParamLineIndent and ITreeView::kParamIconSpacing
		/// @param paramIndex The parameter whose value will be returned.
		///
		/* 38h */	virtual size_t GetParameter(int paramIndex) = 0;

		///
		/// Sets the icon that is drawn by default on each item.
		/// @param pIconDrawable The IDrawable that will render the icon.
		/// 
		/* 3Ch */	virtual void SetDefaultIcon(IDrawable* pIconDrawable) = 0;

		///
		/// Gets the icon that is drawn by default on each item.
		/// 
		/* 40h */	virtual IDrawable* GetDefaultIcon() const = 0;

		///
		/// Sets the IDrawable of the expander button that is rendered before every icon.
		/// @param pExpanderDrawable The IDrawable that will render the icon (usually a TreeExpanderDrawable)
		/// 
		/* 44h */	virtual void SetExpanderDrawable(IDrawable* pExpanderDrawable) = 0;

		///
		/// Gets the IDrawable of the expander button that is rendered before every icon.
		/// 
		/* 48h */	virtual IDrawable* GetExpanderDrawable() const = 0;


		/* 4Ch */	virtual TreeNode& GetRootNode() = 0;
	};
}