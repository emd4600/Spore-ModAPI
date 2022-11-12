#pragma once

#include <Spore\Anim\IAnimWorld.h>
#include <Spore\Anim\TLSA.h>
#include <Spore\Resource\Database.h>

#define AnimManager (*Anim::IAnimManager::Get())

namespace Anim
{
	class IAnimManager
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual ~IAnimManager() = 0;
		/* 0Ch */	virtual bool Initialize(int) = 0;
		/* 10h */	virtual bool Dispose() = 0;
		/* 14h */	virtual void Update(int) = 0;
		/* 18h */	virtual float func18h() = 0;
		/* 1Ch */	virtual void func1Ch(float) = 0;
		/* 20h */	virtual IAnimWorld* CreateWorld(const char16_t* name) = 0;
		/* 24h */	virtual bool func24h(int, int, int) = 0;
		/* 28h */	virtual void ClearAnimationCache() = 0;
		// calls func30h for all animations in the animID group
		// used to preload animations
		/* 2Ch */	virtual void func2Ch(uint32_t animID, int* pOnlyIndex = nullptr) = 0;
		// Adds animation to list of pending to load
		/* 30h */	virtual void RequestAnimation(uint32_t animResourceID) = 0;
		/* 34h */	virtual void func34h(int) = 0;
		/* 38h */	virtual void LoadPendingAnimations() = 0;  // reads .animation
		/* 3Ch */	virtual bool SetDefaultFillerAnimation(uint32_t animID) = 0;
		/* 40h */	virtual TlsaAnimGroup* GetAnimGroup(uint32_t animID) = 0;
		/* 44h */	virtual void LoadRequiredAnimations(uint32_t animID) = 0;  // reads .animation
		/* 48h */	virtual int func48h() = 0;
		/* 4Ch */	virtual int func4Ch() = 0;
		/* 50h */	virtual bool SaveTlsa(Resource::Database* database) = 0;
		/* 54h */	virtual bool SavePctp(Resource::Database* database) = 0;
		/* 58h */	virtual bool SaveGait(Resource::Database* database) = 0;
		/* 58h */	virtual bool SaveAnimation(Resource::Database* database, int) = 0;
		/* 5Ch */	virtual int func5Ch(int, int) = 0;

		static IAnimManager* Get();
	};

	namespace Addresses(IAnimManager) {
		DeclareAddress(Get);
	}
}
