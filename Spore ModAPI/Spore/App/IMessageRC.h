#pragma once

namespace App
{
	class IMessageRC
	{
	public:
		virtual ~IMessageRC() {};
		virtual int AddRef() = 0;
		virtual int Release() = 0;
	};
}