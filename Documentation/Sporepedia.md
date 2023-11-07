@page Sporepedia Interacting with the Sporepedia
@brief How to show the %Sporepedia to the player

Sometimes we need the player to select a creation from the Sporepedia. This is done with **shopper requests**: they use a configuration file
in the `AssetBrowserConfig` folder to know what text to show to the player, what possible creation types it can select, etc

We can prompt a Sporepedia shopper request by using the Sporepedia::ShopperRequest class. To react when the player selects the creation and 
clicks the *Accept* button, we will need to create a class that extends Sporepedia::IShopperListener class. 

~~~~{.cpp}
class MyListener
	: public Sporepedia::IShopperListener
{
public:
	void OnShopperAccept(const ResourceKey& selection) override;
};
~~~~

The `OnShopperAccept()` method will be called when the user choses a creation and clicks the *Accept* button. The parameter it receives
is the key code that identifies the creation. The folder and type depend on the creation (for example, for creatures the type is `crt`,
for buildings it's `bld`, etc). You can get information about the creation by using the Pollinator::GetMetadata() method:

~~~~{.cpp}
void OnShopperAccept(const ResourceKey& selection)
{
	auto metadata = Pollinator::GetMetadata(selection.instanceID, selection.groupID);
	App::ConsolePrintF("You selected the creation %ls", metadata->GetName().c_str());
}
~~~~

Now, to show the Sporepedia, at some point in your code (for example, on a cheat, or when the user clicks a button) you will have to execute this:
~~~~{.cpp}
// 'listener' is an instance of a class that implements IShopperListener,
// for example the MyListener we showed before

Sporepedia::ShopperRequest request(listener);
request.shopperID = id("MilitaryAirShopper");
~~~~

You use `SetShopperID()` to tell which shopper configuration you use. The value is the ID of a `.prop` file in the `AssetBrowserConfig` folder.
If no shopper ID is used, by default it uses `GlobalTemplate` which shows all types of creations. Another interesting method is 
[`request.SetSelection()`](@ref Sporepedia::ShopperRequest::SetSelection()), which allows you to show an already-selected creation to the player.

Usually `IShopperListener` is not implemented alone; usually it's part of a bigger class. For example, you can make a cheat that is also a shopper listener:
~~~~{.cpp}
class MyListener
	: public ArgScript::ICommand
	, public Sporepedia::IShopperListener
{
public:
	...
};
~~~~

As an example of a mod that uses this, check the [source code of `GmdlExport`](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/GmdlExport).
This mod adds a cheat that shows the Sporepedia.