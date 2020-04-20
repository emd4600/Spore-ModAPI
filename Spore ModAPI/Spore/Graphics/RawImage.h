#pragma once

namespace Graphics
{
	class IRawImage
	{
	public:
		/* 00h */	virtual int func00h() = 0;  // returns 0Ch
		/* 04h */	virtual void GetData(int& dstWidth, int& dstHeight, void*& dstData) = 0;  // returns 04h, 08h, and 10h
		/* 08h */	virtual int AddRef() = 0;
		/* 0Ch */	virtual int Release() = 0;
	};


}