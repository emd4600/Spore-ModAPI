@page Simulator Introduction to the Simulator
@brief How to iterate %Simulator objects and create new instances

The Simulator is the gameplay engine in Spore. In this tutorial we will show you the basic interactions you can do with it.

Objects in the Simulator are called **nouns**; this is the equivalent to *entities* in other game engines like Unity. The basic noun class
is [cGameData](@ref Simulator::cGameData), and then there are more specific nouns that extend it (e.g. `cCreatureAnimal`, `cVehicle`, etc). Each noun class
is identified with an ID, for example `cCreatureAnimal::NOUN_ID`.

Then there are some component classes, which are used to give certain attribute sto nouns. For example, nouns can extend `cSpatialObject` to have a 
3D representation, or `cCombatant` to have health points, etc 

For simplicity, we will assume through all this tutorial that `using namespace Simulator;` is being used, so we don't have to write `Simulator::` all the time.

@section Simulator-Iterating Iterating Simulator objects

Very often you will need a way to access to all %Simulator objects of a certain type: do something to all creatures, remove all vehicles,...
You can do that with the `GetData()` method:

~~~~{.cpp}
auto vehicles = GetData<cVehicle>();
for (auto vehicle : vehicles) {
	// vehicle is a cVehicle*
}
~~~~

Sometimes we will want to get the objects of a type that the %ModAPI SDK does not support yet. In that case, we have to use the noun ID directly, and
`cGameData` as thet type. You have a full list of noun IDs at Simulator::GameNounIDs. Still, you can use object casting to get useful information:
~~~~{.cpp}
for (auto egg : GetData<cGameData>(kEgg)) {
	// Eggs have 3d representation, so we can try casting
	if (auto eggModel = object_cast<cSpatialObject>(egg)) 
	{
		float dist = (GameNounManager.GetAvatar()->GetPosition() - eggModel->GetPosition()).Length();
		App::ConsolePrintF("You have an egg at %f meters!", dist);
	}
}
~~~~

You can also get all the instances of base classes like `cSpatialObject`, `cCombatant`, `cLocomotiveObject`,... using `GetDataByCast()`. All objects
that can be casted to that class will be returned:
~~~~{.cpp}
auto models = GetDataByCast<cSpatialObject>();
for (auto model : models) {
	// model is a cSpatialObject*
}
~~~~

@section Simulator-Creating Creating new instances

When creating new instances of %Simulator objects you cannot use `new`. Instead, do it like this:

~~~~{.cpp}
auto object = simulator_new<cInteractiveOrnament>();
~~~~

@note If you want to save a pointer to an object in a class member, you should use an intrusive pointer (for example `cInteractiveOrnamentPtr`)

If you need to create an object whose class is not in the SDK yet, you can create it using the `GameNounManager` directly. It will return a
`cGameData*`, but you can cast it to do whatever you need.

~~~~{.cpp}
auto herd = GameNounManager.CreateInstance(kRock);
if (auto herdModel = object_cast<cSpatialObject>(herd)) 
{
	herdModel->SetModelKey({ id("EP1_Barrel"), TypeIDs::prop, GroupIDs::CivicObjects });
}
~~~~

@section Simulator-Examples Examples

@subsection Simulator-Examples-1 Example 1: Make all airplanes fly towards the closest city to the player

~~~~{.cpp}
auto city = PlanetModel.GetNearestCity(GameNounManager.GetAvatar()->GetPosition());
if (city) {
    for (auto vehicle : GetData<cVehicle>()) {
        if (vehicle->GetLocomotion() == kLocomotionAir) {
            vehicle->MoveTo(city->GetWallsPosition());
        }
    }
}
~~~~

@subsection Simulator-Examples-2 Example 2: Kill all entities with health points (except avatar)

~~~~{.cpp}
for (auto combatant : GetDataByCast<cCombatant>()) {
	// To compare two pointers, we must ensure they are the same type
	if (object_cast<cCreatureAnimal>(combatant) != GameNounManager.GetAvatar()) {
		combatant->SetHealthPoints(0);
	}
}
~~~~