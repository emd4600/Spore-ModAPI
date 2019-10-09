#pragma once

#include <Spore\ResourceKey.h>
#include <EASTL\vector.h>

namespace Sporepedia
{
	///
	/// Extend this class to know when the user accepts an Sproepedia shopper request.
	/// You must override the `OnShopperAccept` method, which gets called when the user clicks the 
	/// Accept button in the Sporepedia. The method receives a the key of the selected creation.
	class IShopperListener
	{
	public:
		// it gets called on sub_64BFF0+139

		virtual void OnShopperAccept(const ResourceKey& selection) = 0;
	};
}