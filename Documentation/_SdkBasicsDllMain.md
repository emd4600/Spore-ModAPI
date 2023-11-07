@page Sdk-Basics-DllMain ModAPI SDK Basics: The main file, dllmain
@brief A basic guide of the `dllmain.cpp` file of %ModAPI projects

When you create a new %ModAPI project, you have some default files, something like this:

![](0R8WiYE.png)

`readme.txt`, `targetver.h`, `stdafx.h` and `stfafx.cpp` are internal files that you don't need to modify. The other one, `dllmain.cpp`, is the main file of our mod,
so we are going to explain everyhing you need to know about it in this tutorial.

If you open the file, you will notice it has 4 methods. `DllMain` is the method that gets executed when our `.dll` gets loaded into the game;
however the project template has already filled it with the code it needs so you will probably never have to touch it. The other three methods are more important; they all have 
comments (which you can just remove) that explain what you can do there, still, we are going to explain them now:

@section Sdk-Basics-DllMain-Initialize Initialize

Probably the most important method, this gets executed when Spore has finished initializing. This happens before the start movie is shown to the player.
Here is where you are going to add most new things: new cheats, new space tools, new game modes, new simulator classes,... . 
You can also change materials, read `.prop` files, print to the console,...

An example of a basic `Initialize` method:
~~~~{.cpp}
void Initialize()
{
	TestCheat::AddCheat();
	SpaceDestroyCheat::AddCheat();
	FortniteGameMode::AddGameMode();
}
~~~~

@section Sdk-Basics-DllMain-Dispose Dispose

The opposite of initialize: this method is executed when the game is closed. Generally you don't need to do anything here, as Spore takes care of msotly everything.
Taht is, if you add a cheat in the `Initialize` method, you don't need to remove it here, because Spore removes it automatically. Most times you can leave this function empty.

@section Sdk-Basics-DllMain-AttachDetours AttachDetours

If your mod uses detouring (a method for redirecting Spore code), this is the place to add them. For more information about detours, [check the tutorial](_detouring.html).

~~~~{.cpp}
void AttachDetours()
{
	cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}
~~~~