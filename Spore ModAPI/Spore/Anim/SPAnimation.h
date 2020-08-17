#pragma once

#include <cstdint>
#include <EASTL\intrusive_ptr.h>

#define SPAnimationPtr eastl::intrusive_ptr<Anim::SPAnimation>

namespace Anim
{
	struct SPAnimation;

	struct SPAnimationChannel
	{
		/* 00h */	uint32_t magic;  // 'CHAN'
		/* 04h */	SPAnimation* pAnimation;
		/* 08h */	char name[0x80];
		/* 88h */	
	};

	struct SPAnimation
	{
		int AddRef();
		int Release();

		/* 00h */	uint32_t magic;  // 'ANIM'
		/* 04h */	int fileSize;
		/* 08h */	int version;
		/* 0Ch */	char path[256];
		/* 10Ch */	int field_10C;
		/* 110h */	uint32_t id;
		/* 114h */	int mnRefCount;
		/* 118h */	int field_118;
		/* 11Ch */	float frameLength;  // 1/30
		/* 120h */	float length;
		/* 124h */	char padding_124[0x13C - 0x124];
		/* 13Ch */	int vfxCount;
		/* 140h */	void* pVFX;
		/* 144h */	int channelCount;
		/* 148h */	SPAnimationChannel** pChannels;
	};

	inline int SPAnimation::AddRef() {
		++mnRefCount;
		return mnRefCount;
	}

	inline int SPAnimation::Release() {
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}
}