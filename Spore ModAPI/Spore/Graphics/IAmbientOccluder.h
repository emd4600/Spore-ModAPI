#pragma once

namespace Graphics
{
	class IAmbientOccluder
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual void func08h() = 0;
		/* 0Ch */	virtual void func0Ch(int, int, int) = 0;
		/* 10h */	virtual bool func10h() = 0;
		/* 14h */	virtual bool func14h(int, int) = 0;
		/* 18h */	virtual bool func18h() = 0;
		/* 1Ch */	virtual int func1Ch() = 0;
		/* 20h */	virtual bool func20h(int, int) = 0;
	};
}