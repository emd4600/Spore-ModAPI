#include <Spore\Internal.h>
#include <Spore\Sporepedia\ShopperRequest.h>

namespace Sporepedia
{
	auto_STATIC_METHOD_VOID(ShopperRequest, Show, Args(ShopperRequest& request), Args(request));

	ShopperRequest::ShopperRequest(IShopperListener* listener)
		: shopperID(0x578C04FA)
		, gameModeID()
		, field_8()
		, field_C()
		, field_10()
		, field_11()
		, field_12()
		, field_13(true)
		, field_14()
		, currentSelection()
		, field_24(true)
		, field_28()
		, field_2C()
		, field_30(0xAD0E52)
		, field_34(1)
		, pListener(listener)
		, field_3C()
		, pEditorRequest(nullptr)
		, field_44()
	{
	}
}