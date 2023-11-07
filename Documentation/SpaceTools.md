@page SpaceTools Creating space tools
@brief How to add custom functionality to space tools

Adding new space tools has been possible for a very long time; however, they must be based in existing tools. The %ModAPI SDK allows you to create
new **tool strategies**, which let you use custom code for your custom space tools.

In order to create a tool strategy, you have to extend the `cToolStrategy` class or any of its subclasses. You should choose the one that gets closer to
the type of tool you want to do (for example, if it has a projectile, use `cDefaultProjectileWeapon`). Here's a list of all available classes:

 - Simulator::cAbductToolStrategy
 - Simulator::cArtilleryWeaponStrategy
 - Simulator::cCropCirclesToolStrategy
 - Simulator::cDefaultAoETool
 - Simulator::cDefaultBeamTool
 - Simulator::cDefaultProjectileWeapon
 - Simulator::cDeepSpaceProjectileToolStrategy
 - Simulator::cDragInputProjectileToolStrategy
 - Simulator::cDropCargoToolStrategy
 - Simulator::cEnergyRepairToolStrategy
 - Simulator::cGenesisDeviceToolStrategy
 - Simulator::cGetOutOfUFOToolStrategy
 - Simulator::cGlobalMindEraseToolStrategy
 - Simulator::cMindEraseToolStrategy
 - Simulator::cPlaceColonyToolStrategy
 - Simulator::cPlaceObjectToolStrategy
 - Simulator::cRallyCallToolStrategy
 - Simulator::cRepairAOEToolStrategy
 - Simulator::cRepairToolStrategy
 - Simulator::cScanToolStrategy
 - Simulator::cToggleToolStrategy
 - Simulator::cToolStrategy
 - Simulator::cTurretDefenseMissileWeapon
 - Simulator::cTurretFlakWeapon
 
There are many methods that you can override which define the logic of the space tool. It's recommended to first call the default implementation, and then
do whatever you need. Check the methods documentation at the Simulator::cToolStrategy page. The most important methods are:

 - `OnSelect()`: called when the user clicks on the tool button to select it.
 - `OnDeselect()`: called when the user clicks on the tool button again to unselect it.
 - `WhileAiming()`: called when the player has the tool selected and is aiming at the planet.
 - `Update()`: called every game loop if the tool is visible, that is, if the panel that contains it is selected or if the tool is selected.
 - `SelectedUpdate()`: unlike Update, it's not executed if the game is paused.
 - `OnMouseDown()`: called when the player clicks down the left mouse button with the tool selected.
 - `OnMouseUp()`: called when the player releases the left mouse button with the tool selected.
 - `OnHit()`: called when the moue hits an objective
 - `WhileAiming()`: called every game update while the player is aiming with the tool selected.
 - `WhileFiring()`: called every game update while the player is firing with the tool selected.
 
All these methods receive a Simulator::cSpaceToolData object that has the data processed from the tool `.prop` file in `spacetools~`. Keep in mind that
the strategy class can be shared by multiple tools; you should not store any members in your strategy class.

You can add the strategy to the tool manager in the `Initialize()` method in `dllmain`. You have to assign it an ID.

~~~~{.cpp}
ToolManager.AddStrategy(new CustomToolStrategy(), id("CustomToolStrategy"));
~~~~

To use it in a space tool, add this in the `.prop` file in `spacetools~`:
~~~~{.cpp}
key spaceToolStrategy hash(CustomToolStrategy)
~~~~