@page SimulatorBasic Interacting with the Simulator
@brief An overview of the most important Simulator functions

@tableofcontents

Before reading this tutorial, first read ["Introduction to the Simulator"](_simulator.html) tutorial. The code in this tutorial is
written assuming `using namespace Simulator;` is being used, for simplicity.

@section SimulatorBasic-Player Player data

~~~~{.cpp}
// Gives you the active star and planet

cStar* star = GetActiveStar();
cStarRecord* starRecord = GetActiveStarRecord();

cPlanet* planet = GetActivePlanet();
cPlanetRecord* planetRecord = GetActivePlanetRecord();


// Gives you the player empire and its political ID

cEmpire* empire = GetPlayerEmpire();
uint32_t politicalID = GetPlayerEmpireID();

// This can be used to know the current context: planet, solar system, galaxy

if (GetCurrentContext() == kSpaceContextGalaxy) {

}
else if (GetCurrentContext() == kSpaceContextPlanet) {

}

// Returns the avatar creature
cCreatureAnimal* avatar = GameNounManager.GetAvatar();
~~~~


@section SimulatorBasic-Stars Stars & Empires

In order to identify stars and planets, Spore uses the `StarIndex` and `PlanetIndex` types, which are just integers. Star indices are divided in sectors
(you can get the sector of a star index with `GetSectorIndex(starIndex)`). A planet index is composed with a star index, and then the index of the planet 
within that solar system (you can separate them with `GetStarRecordIndex(planetIndex)` and `GetPlanetIndex(planetIndex)`). Internally, planets and star systems
are stored as Simulator::cPlanetRecord and Simulator::cStarRecord.

~~~~{.cpp}
cStarRecord* star = StarManager.GetStarRecord(starIndex);
cPlanetRecord* planet = StarManager.GetPlanetRecord(planetIndex);
~~~~

You can access things like `star->mName`, `star->mPlanets`, `star->mEmpireID`, `planet->mPlantSpecies`, `planet->mWaterScore`,...
If you want to get the terraforming score of a planet, you can use `TerraformingManager.GetTScore(planet)`. You can also compute
the corresponding T-score for an atmosphere and temperature using `TerraformingManager.CalculateTScore(atmosphereScore, temperatureScore)`

The [StarManager](@ref Simulator::cStarManager) also has functions for many other things related with galaxies:

~~~~{.cpp}

cEmpire* empire = StarManager.GetEmpire(politicalID);

// The Grox
uint32_t politicalID = StarManager.GetGrobEmpireID();

// Where is the planet earth?
cStarRecord* star = StarManager.GetSol();

// If you are playing an adventure, this returns the star it is in
cStarRecord* star = StarManager.GetScenarioStar();
~~~~

The Simulator::cEmpire class has many useful attributes:

~~~~{.cpp}
cStarRecord* homeStar = empire->GetHomeStarRecord();

for (auto starRecord : empire->mStars) {

}

for (auto enemy : empire->mEnemies) {

}
for (auto ally : empire->mAllies) {

}

ResourceKey factory = empire->mCultureSet.GetCreation(kBuildingIndustry);

if (empire->mArchetype == kArchetypeEcologist) {

}
~~~~


@section SimulatorBasic-Relationships Relationships

The `RelationshipManager` manages the relationship between communities (tribes, cities, empires). You can do some basic actions:

 - **Check if two empires are at war:** `RelationshipManager.IsAtWar(empire1, empire2)`
 
 - **Apply a relationship:** The available relationships are at the Simulator::RelationshipEvents enum. You can use `ApplyRelationship` to
 apply a relationship effect between two communities (you need the *political ID* of the communities). The impact of that relationship depends on 
 settings to certain properties in `.prop` files.
 
~~~~{.cpp}
// The last parameter is the scale, how much is affected
RelationshipManager.ApplyRelationship(empire->GetPoliticalID(), causeEmpire->GetPoliticalID(), kRelationshipEventHostility, 0.3f);
~~~~


@section SimulatorBasic-Planets Planets

Given a 3D vector representing a position, there are multiple functions at `PlanetModel` related with planets. The position does not need to be at the surface,
it's just considered a direction from the center of the planet.

~~~~{.cpp}
Vector3 position = ...;

// Returns true if this position is inside or above the water mass in the planet
if (PlanetModel.IsInWater(position)) {

}

// Returns the terrain height at this position
float height = PlanetModel.GetHeightAt(position);

// Returns the city nearest to the position
cCity* city = PlanetModel.GetNearestCity(position);

// Returns the planet surface position that is aligned with the given position
Vector3 pos = PlanetModel.ToSurface(position);

// Returns the quaternion orientation that orients an object in this direction
Vector3 direction = {0, 0, 1};
Quaternion orientation = PlanetModel.GetOrientation(position, direction);


// Generally returns -9.8, but adventures can use a different gravity
float gravity = PlanetModel.GetGravity();

// Returns the position at the planet that the mouse cursor is aiming at
// This can collide with certain objects like airplanes, creatures, cyty walls, but for example not rocks
Vector3 pos = GameViewManager.GetWorldMousePosition();
~~~~

If you have a Simulator::cCity object, you can get the position of the city using `city->GetWallsPosition()`.

@section SimulatorBasic-Tools Space tools & inventory

The [space tools tutorial](_space_tools.html) shows you how to add new space tools. Apart from that, there are many useful functions related with
space tools and the space inventory. You can get the [space inventory](Simulator::cSpaceInventory) with `SimulatorSpaceGame.GetPlayerInventory()`.
That class has methods to see if there's a certain item, add and remove items, etc. For example, if we want to add a planet buster weapon to our
inventory:

~~~~{.cpp}
cSpaceToolDataPtr tool;
ToolManager.LoadTool({id("PlanetBusterBomb"), 0, 0}, tool)

auto inventory = SimulatorSpaceGame.GetPlayerInventory();
inventory->AddItem(tool.get());

// You can also add ammo to the tool
tool->AddAmmo(10);
~~~~


@section SimulatorBasic-Modes Game modes

Calling `SimGameModeManager.GetActiveModeID()` returns the ID of the current mode, which you can compare to the IDs at the GameModeIDs enum.
There are also functions that do that for you: `IsSpaceGame()`, `IsScenarioMode()`,...

You can get the difficulty tunning `.prop` of the active mode and difficulty by calling `GameModeManager.GetActiveDifficultyTuning()`. 


@section SimulatorBasic-Loading Loading creatures, vehicles and models

Some simulator objects, such as creatures and vehicles, have specialized functions that must be used when creating them.

To create a creature, first you must get its species, then use Simulator::cCreatreAnimal::Create() to create a new instance of that species.
You must also give it the initial position.

~~~~{.cpp}
auto species = SpeciesManager.GetSpeciesProfile({ 0x066B8241, TypeIDs::crt, GroupIDs::CreatureModels });
cCreatureAnimalPtr creature = cCreatureAnimal::Create({ 500.0, 0, 0 }, species);
~~~~

You can create a vehicle with `simulator_new`, like most other %Simulator classes. You will have to call the `Load()` method to load a model
and tell which kind of vehicle it is:

~~~~{.cpp}
cVehiclePtr vehicle = simulator_new<cVehicle>();
vehicle->Load(kVehicleLand, kVehicleMilitary, { 0x19A3A9AC, TypeIDs::vcl, GroupIDs::VehicleModels });

// If you are on civ/space stage, you can spawn a vehicle that belongs to a city
// The last argument is whether you are on space stage
cVehiclePtr vehicle = city->SpawnVehicle(kVehicleMilitary, kVehicleLand, { 0x19A3A9AC, TypeIDs::vcl, GroupIDs::VehicleModels }, false);
~~~~

For other types of spatial objects, you can just use `SetModelKey()`:

~~~~{.cpp}
cGameDataPtr rock = GameNounManager.CreateInstance(kRock);
object_cast<cSpatialObject>(rock)->SetModelKey({ id("EP1_sg_rare_fossils_04"), TypeIDs::prop, GroupIDs::CivicObjects });
~~~~

@subsection SimulatorBasic-Loading-Moving Moving & Animating

You can move a vehicle to a position using `MoveTo()`:

~~~~{.cpp}
Vector3 dst = ...;
vehicle->MoveTo(dst);
~~~~

For creatures, you can use `WalkTo()`. It takes an additional integer (`speedState`) and a 3D vector, their usage is unknown.

~~~~{.cpp}
Vector3 dst = ...;
vehicle->WalkTo(0, dst, {0, 0, 1});
~~~~

Creatures also have a function to play an animation. For more information about how to find animation IDs, check this 
[Spore animations tutorial](https://github.com/emd4600/SporeModder-FX/wiki/How-to:-use-Spore-animations):

~~~~{.cpp}
// 0x04FFA018 is the animation where the creature tells a joke
creature->PlayAnimation(0x04FFA018);
~~~~
