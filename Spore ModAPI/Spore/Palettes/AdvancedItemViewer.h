#pragma once

#include <Spore\Palettes\ItemViewer.h>
#include <Spore\Palettes\PaletteItem.h>
#include <Spore\Palettes\PaletteInfo.h>
#include <Spore\Clock.h>

#define AdvancedItemViewerPtr eastl::intrusive_ptr<Palettes::AdvancedItemViewer>

namespace Palettes
{
	class AdvancedItemViewer
		: public ItemViewer
	{
	public:
		static const uint32_t TYPE = 0x3349C94;

		struct Message
		{
			inline static const Message& Get(const UTFWin::Message& msg) {
				return *(Message*)&msg.Mouse;
			}

			struct Data {
				/* 00h */	int padding_0[7];
				/* 1Ch */	ItemViewer* pViewer;
			};

			/* 0Ch */	int field_C;
			/* 10h */	int field_10;
			/* 14h */	int field_14;
			/* 18h */	Data pData;
		};

		AdvancedItemViewer();

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		void SetAutoRotate(bool enabled);
		void SetZoom(float zoom);

		void Initialize(const ResourceKey& nameKey, UTFWin::IWindow* pWindow, UTFWin::IWindow* pParentWindow,
			uint32_t messageID, PaletteItem* pItem, PaletteInfo* pPaletteInfo, bool);

		/* 1Ch */	virtual void Unload() override;
		/* 20h */	virtual void Update(int time) override;
		/* 24h */	virtual void Load(const ResourceKey& fileName) override;
		/* 28h */	virtual void SetName(const ResourceKey& fileName) override;
		/* 2Ch */	virtual void func2Ch(bool) override;
		/* 30h */	virtual bool func30h() const override;
		/* 34h */	virtual UTFWin::IWindow* GetWindow() const override;
		/* 38h */	virtual void Set3dPreview(bool enabled) override;
		/* 3Ch */	virtual Anim::AnimatedCreature* GetAnimatedCreature() const override;
		/* 40h */	virtual void func40h() override;
		/* 44h */	virtual bool func44h() override;
		/* 48h */	virtual void func48h() override;
		/* 4Ch */	virtual void func4Ch() override;
		/* 50h */	virtual void func50h() override;
		/* 54h */	virtual void func54h(int) override;
		/* 58h */	virtual float func58h() override;
		/* 5Ch */	virtual bool IsOutside() override;
		/* 60h */	virtual void OnOutside() override;
		/* 64h */	virtual void func64h() override;
		/* 68h */	virtual void RotateModel() override;

		/* 6Ch */	virtual bool func6Ch();
		/* 70h */	virtual void func70h();
		/* 74h */	virtual int func74h();
		/* 78h */	virtual void func78h(int);
		/* 7Ch */	virtual void func7Ch();

		virtual int GetEventFlags() const override;
		virtual bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;
		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

		/* 17Ch */	DefaultRefCountedPtr field_17C;
		/* 180h */	PaletteItemPtr mpItem;
		/* 184h */	bool field_184;
		/* 188h */	float field_188;  // 1.0
		/* 18Ch */	ObjectPtr field_18C;
		/* 190h */	int field_190;
		/* 194h */	ObjectPtr field_194;
		/* 198h */	bool field_198;  // true
		/* 199h */	bool field_199;  // not initialized
		/* 19Ah */	bool field_19A;
		/* 1A0h */	Clock field_1A0;
		/* 1B8h */	ObjectPtr field_1B8;
		/* 1BCh */	ObjectPtr field_1BC;
		/* 1C0h */	int field_1C0;  // not initialized
		/* 1C4h */	int field_1C4;  // not initialized;
	};
	ASSERT_SIZE(AdvancedItemViewer, 0x1C8);

	namespace Addresses(AdvancedItemViewer)
	{
		DeclareAddress(SetAutoRotate);
		DeclareAddress(SetZoom);

		DeclareAddress(HandleUIMessage);
		DeclareAddress(Unload);
		DeclareAddress(Update);
		DeclareAddress(Load);
		DeclareAddress(SetName);
		DeclareAddress(func40h);
		DeclareAddress(func44h);
		DeclareAddress(func48h);
		DeclareAddress(func4Ch);
		DeclareAddress(func50h);
		DeclareAddress(func54h);
		DeclareAddress(func58h);
		DeclareAddress(IsOutside);
		DeclareAddress(OnOutside);
		DeclareAddress(func64h);
		DeclareAddress(RotateModel);
		DeclareAddress(func6Ch);
		DeclareAddress(func70h);
		DeclareAddress(func74h);
		DeclareAddress(func78h);
		DeclareAddress(HandleMessage);

		DeclareAddress(Initialize);
	}
}
