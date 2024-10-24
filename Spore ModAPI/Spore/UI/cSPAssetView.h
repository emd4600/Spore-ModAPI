#pragma once

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\Sporepedia\AssetData.h>

#define cSPAssetViewPtr eastl::intrusive_ptr<UI::cSPAssetView>

namespace UI
{
	class cSPAssetView
		: public UTFWin::IWinProc
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x73CC339E;

		cSPAssetView();

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t) const override;
		virtual int GetEventFlags() const override;
		virtual bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

		/* 1Ch */	virtual void Load(UTFWin::IWindow* window, Sporepedia::IAssetData* assetData, bool, bool);
		/* 20h */	virtual void func20h();
		/* 24h */	virtual void func24h(int, int);
		/* 28h */	virtual void SetVisible(bool visible);

		bool sub_6590A0();

	public:
		/* 0Ch */	char padding_C[0x108 - 0xC];
	};
	ASSERT_SIZE(cSPAssetView, 0x108);

	namespace Addresses(cSPAssetView) {
		DeclareAddress(_ctor);  // 0x657DA0 0x657F30
		DeclareAddress(sub_6590A0);  // 0x6590A0 0x659230
	}
}