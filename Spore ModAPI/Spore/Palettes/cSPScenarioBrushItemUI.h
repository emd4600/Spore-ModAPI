#pragma once

#include <Spore\Palettes\IItemFrameUI.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\UTFWin\UILayout.h>

namespace Palettes
{
	class cSPScenarioBrushItemUI
		: public DefaultItemFrameUI
		, public App::IMessageListener
	{
	public:
		/* 24h */	IWindowPtr mpItemsPanel;
		/* 28h */	UILayoutPtr mpLayout;
		/* 2Ch */	DefaultRefCountedPtr field_2C;
		/* 30h */	ResourceKey mToolGenericEffectID;
		/* 3Ch */	ResourceKey mToolPreviewEffect;
		/* 48h */	ResourceKey mMarkerModelID;
		/* 54h */	uint32_t mBrushCategory;
		/* 58h */	Vector2 mBrushIntensityRange;  // 0.0, 1.0
		/* 60h */	Vector2 mBrushSizeRange;  // 0.0, 1.0
		/* 68h */	bool mIsTerraformModel;  // uses terraformModelID instead of toolGenericEffectID
		/* 69h */	bool mIsValidComplexity;  // true
		/* 6Ah */	bool mIsDragging;
		/* 6Ch */	float mBrushIntensityDefault;  // 0.5
		/* 70h */	float mBrushSizeDefault;  // 0.5
		/* 74h */	float mBrushComplexity;  // 1.0
	};
}