#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>
#include <Spore\App\IMessageRC.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>

namespace Skinner
{
	class cSkinPainterJobExtractTexture
		/* 00h */	: public App::IUnmanagedMessageListener
		/* 04h */	, public App::IMessageRC
		/* 08h */	, public cSkinPainterJob
	{
	public:
		/* 18h */	uint32_t mInstanceID;
		/* 1Ch */	uint32_t mGroupID;
		/* 20h */	RenderWare::Raster* field_20;
		/* 24h */	int field_24;
		/* 28h */	bool field_28;
		/* 29h */	bool field_29;
		/* 2Ah */	bool field_2A;
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
		/* 34h */	App::MessageListenerData mMessageListenerData;
	};
	ASSERT_SIZE(cSkinPainterJobExtractTexture, 0x48);
}