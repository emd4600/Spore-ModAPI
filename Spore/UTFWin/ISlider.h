#pragma once

#include <Spore\UTFWin\SliderDrawable.h>

namespace UTFWin
{
	class ISlider 
		: public UTFWinObject
	{
	public:
		/* 10h */	virtual IWindow* ToWindow() = 0;
		/// Set orientation of the slider
		/* 14h */	virtual void SetOrientation(Orientation value) = 0;
		/// Get orientation of the slider
		/* 18h */	virtual Orientation GetOrientation() = 0;
		/// Set current value
		/* 1Ch */	virtual void SetValue(int value, int arg_4) = 0;
		/// Get current value
		/* 20h */	virtual int GetValue() = 0;
		/// Set minimum value of the slider
		/* 24h */	virtual void SetMinValue(int value, int arg_4) = 0;
		/// Get minimum value of the slider
		/* 28h */	virtual int GetMinValue() = 0;
		/// Set maximum value of the slider
		/* 2Ch */	virtual void SetMaxValue(int value, int arg_4) = 0;
		/// Get maximum value of the slider
		/* 30h */	virtual int GetMaxValue() = 0;
		/// Set object to render slider appearance
		/* 34h */	virtual void SetSliderDrawable(ISliderDrawable* drawable) = 0;
		/// Get object to render slider appearance
		/* 38h */	virtual ISliderDrawable* GetSliderDrawable() = 0;

		static const uint32_t TYPE = 0xF00A8A0;
	};
}