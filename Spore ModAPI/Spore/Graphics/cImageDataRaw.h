#pragma once

#include <Spore\Resource\ResourceObject.h>

#define cImageDataPtr eastl::intrusive_ptr<Graphics::cImageData>
#define cImageDataRawPtr eastl::intrusive_ptr<Graphics::cImageDataRaw>

namespace Graphics
{
	class cImageData
	{
	public:
		/* 00h */	virtual int GetType();
		/* 04h */	virtual void GetData(int& dstWidth, int& dstHeight, int8_t*& dstData);
		/* 08h */	virtual int AddRef();
		/* 0Ch */	virtual int Release();

	public:
		/* 04h */	int mWidth;
		/* 08h */	int mHeight;
		/* 0Ch */	int mType;  // -1
		/* 10h */	int8_t* mpData;
	};
	ASSERT_SIZE(cImageData, 0x14);

	class cImageDataRaw
		: public Resource::SpecialResourceObject
		, public cImageData
	{
	};
	ASSERT_SIZE(cImageDataRaw, 0x2C);
}