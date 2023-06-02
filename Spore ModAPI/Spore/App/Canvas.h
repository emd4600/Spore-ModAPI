#pragma once

#include <Spore\App\IMessageManager.h>
#include <Spore\Internal.h>
#include <EASTL\string.h>

namespace App
{
	class Canvas
	{
	public:
		static Canvas* Get();

		/* 00h */	virtual ~Canvas();
		/* 04h */	virtual bool Init();
		/* 08h */	virtual bool Shutdown();
		/* 0Ch */	virtual bool func0Ch();
		/* 10h */	virtual void func10h(bool);
		/* 14h */	virtual void Update();
		/* 18h */	virtual void Clear();
		/* 1Ch */	virtual int GetStyle();
		/* 20h */	virtual void SetStyle(int style);
		/* 24h */	virtual int GetOptions();
		/* 28h */	virtual void SetOptions(int options);
		/* 2Ch */	virtual const char16_t* GetCaption();
		/* 30h */	virtual void SetCaption(const char16_t* caption);
		/* 34h */	virtual void GetPosition(int& x, int& y);
		/* 38h */	virtual void SetPosition(int x, int y);
		/* 3Ch */	virtual void GetClientArea(tagRECT& dstRect);
		/* 40h */	virtual void SetClientArea(struct tagRECT rect);
		/* 44h */	virtual bool IsActive();
		/* 48h */	virtual void SetActive(bool active);
		/* 4Ch */	virtual bool IsVisible();
		/* 50h */	virtual void SetVisible(bool visible);
		/* 54h */	virtual bool IsFullscreen();
		/* 58h */	virtual void SetFullscreen(bool fullscreen, int width, int height);
		/* 5Ch */	virtual bool IsMinimized();
		/* 60h */	virtual bool IsMaximized();
		/* 64h */	virtual IMessageManager* GetMessageServer();
		/* 68h */	virtual void SetMessageServer(IMessageManager*);
		/* 6Ch */	virtual void func6Ch(int);
		/* 70h */	virtual void func70h(int, int);
		/* 74h */	virtual bool HasSystemCursor();
		/* 78h */	virtual void SetSystemCursorVisible(bool visible);
		/* 7Ch */	virtual void func7Ch(int, int);
		/* 80h */	virtual void func80h(int);
		/// Called every frame by cAppSystem::Run()
		/* 84h */	virtual bool Tick();
		/* 88h */	virtual int func88h();
		/* 8Ch */	virtual void func8Ch(int);
		/* 90h */	virtual int func90h();
		/* 94h */	virtual HWND GetWindow();
		/* 98h */	virtual ATOM GetCanvasClass();
		/* 9Ch */	virtual HMONITOR GetMonitor();

	public:
		/* 04h */	int field_4;  // 0xF
		/* 08h */	int mOptions;  // 0x2A
		/* 0Ch */	bool mIsFullscreen;
		/* 0Dh */	bool field_D;
		/* 0Eh */	bool field_E;
		/* 0Fh */	bool field_F;
		/* 10h */	bool field_10;
		/* 11h */	bool field_11;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	bool field_1C;
		/* 20h */	int field_20;
		/* 24h */	eastl::string16 mCaption;
		/* 34h */	int field_34;
		/* 38h */	int field_38;
		/* 3Ch */	tagRECT field_3C;
		/* 4Ch */	bool field_4C;  // true
		/* 4Dh */	bool field_4D;
		/* 4Eh */	bool field_4E;
		/* 4Fh */	bool field_4F;
		/* 50h */	int field_50;  // 2000
		/* 54h */	HKL mKeyboardLayout;
		/* 58h */	int mDefaultAnsiCodeForLocale;
		/* 5Ch */	IMessageManager* mpMessageServer;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	int field_68;
		/* 6Ch */	bool field_6C;
		/* 6Dh */	bool field_6D;
		/* 6Eh */	bool field_6E;
		/* 70h */	ATOM mCanvasClass;
		/* 74h */	HWND mWindow;
		/* 78h */	int field_78;
		/* 7Ch */	HCURSOR mCursor;
		/* 80h */	HBRUSH mBrush;
		/* 84h */	int field_84;  // 0xC80000
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
	};
	ASSERT_SIZE(Canvas, 0x98);

	namespace Addresses(Canvas)
	{
		DeclareAddress(Get);  // 0x67DE10 0x67DCB0
		DeclareAddress(Init);  // 0x84A3F0 0x849BF0
		DeclareAddress(Shutdown);  // 0x848900 0x848100
		DeclareAddress(func0Ch);  // 0xA134D0 0xA13540
		DeclareAddress(func10h);  // 0x848240 0x847A40
		DeclareAddress(Update);  // 0x848290 0x847A90
		DeclareAddress(Clear);  // 0x8482C0 0x847AC0
		DeclareAddress(GetStyle);  // 0x985FB0 0xFCC1D0
		DeclareAddress(SetStyle);  // 0x84A600 0x849E00
		DeclareAddress(GetOptions);  // 0x923C40 0x93B630
		DeclareAddress(SetOptions);  // 0x848310 0x847B10
		DeclareAddress(GetCaption);  // 0x804E30 0xFF3480
		DeclareAddress(SetCaption);  // 0x84A710 0x849ED0
		DeclareAddress(GetPosition);  // 0x8489E0 0x8481E0
		DeclareAddress(SetPosition);  // 0x848A00 0x848200
		DeclareAddress(GetClientArea);  // 0x848A70 0x848270
		DeclareAddress(SetClientArea);  // 0x8497B0 0x848FB0
		DeclareAddress(IsActive);  // 0x848340 0x847B40
		DeclareAddress(SetActive);  // 0x848360 0x847B60
		DeclareAddress(IsVisible);  // 0x848380 0x847B80
		DeclareAddress(SetVisible);  // 0x8483A0 0x847BA0
		DeclareAddress(IsFullscreen);  // 0x69D4C0 0xAB2FF0
		DeclareAddress(SetFullscreen);  // 0x8498C0 0x8490C0
		DeclareAddress(IsMinimized);  // 0x8483C0 0x847BC0
		DeclareAddress(IsMaximized);  // 0x8483E0 0x847BE0
		DeclareAddress(GetMessageServer);  // 0xA36470 0xC871D0
		DeclareAddress(SetMessageServer);  // 0xA168B0 0xA169B0
		DeclareAddress(func6Ch);  // 0x8487A0 0xB18CB0
		DeclareAddress(func70h);  // 0x8487B0 0x847FA0
		DeclareAddress(HasSystemCursor);  // 0xA37650 0xB1FB30
		DeclareAddress(SetSystemCursorVisible);  // 0x8487D0 0x847FC0
		DeclareAddress(func7Ch);  // 0x8487F0 0x847FF0
		DeclareAddress(func80h);  // 0x848820 0x848020
		DeclareAddress(Tick);  // 0x848AF0 0x8482F0
		DeclareAddress(func88h);  // 0x84A890 0x84A050
		DeclareAddress(func8Ch);  // 0x848400 0x847C00
		DeclareAddress(func90h);  // 0x95FE80 0x1030E20
		DeclareAddress(GetWindow);  // 0xF681A0 0xF67D40
		DeclareAddress(GetCanvasClass);  // 0x848410 0x847C10
		DeclareAddress(GetMonitor);  // 0x848420 0x847C20
	}
}