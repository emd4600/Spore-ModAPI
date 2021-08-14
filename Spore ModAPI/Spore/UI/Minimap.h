#pragma once

#include <Spore\UTFWin\Window.h>
#include <Spore\App\IMessageListener.h>

#define MinimapPtr eastl::intrusive_ptr<UI::Minimap>

namespace UI
{
	//TODO
	class Minimap
		/* 00h */	: public UTFWin::Window
		/* 20Ch */	, public DefaultRefCounted
		/* 214h */	, public App::IMessageListener
	{
	public:
		/* 218h */	Math::ColorRGB field_218;  // white
		/* 224h */	int field_224;
		/* 228h */	int field_228;
		/* 22Ch */	int field_22C;
		/* 230h */	int field_230;
		/* 234h */	int field_234;
		/* 238h */	bool field_238;
		/* 239h */	bool field_239;  // arg_14
		/* 23Ch */	int field_23C;
		/* 240h */	int field_240;  // arg_4
		/* 244h */	ObjectPtr field_244;
		/* 248h */	ObjectPtr field_248;
		/* 24Ch */	ObjectPtr field_24C;
		/* 250h */	ObjectPtr field_250;
		/* 254h */	ObjectPtr field_254;
		/* 258h */	DefaultRefCountedPtr field_258;
		/* 260h	*/	Clock field_260;
		/* 278h */	float field_278;  // 10000.0
		/* 27Ch */	int field_27C;
		/* 280h */	char padding_280[0x980 - 0x280];
		/* 980h */	ObjectPtr field_980;
		/* 984h */	ObjectPtr field_984;
		/* 988h */	ObjectPtr field_988;
		/* 98Ch */	ObjectPtr field_98C;
		/* 990h */	float field_990;
		/* 994h */	float field_994;
		/* 998h */	float field_998;
		/* 99Ch */	float field_99C;
		/* 9A0h */	float field_9A0;
	};
	ASSERT_SIZE(Minimap, 0x9A8);
}