@page Swarm-Effects Swarm: The effects system
@brief How to spawn effects

For effects such as particles, decals, etc Spore uses a custom engine called %Swarm. Everything related to effects is in the Swarm namespace.

Effects are a collection of components with different attributes, e.g. spawn 10 red particles here, move a model in this direction,...
You can create your own effects (or discover how existing ones are made) with SporeModderFX, more information here: https://github.com/emd4600/SporeModder-FX/wiki

Effects are uniquely identified with an ID. But keep in mind that this ID is only used to identify the structure of the effect itself: you can have multiple instances
of the same effect at the same time.

@section Swarm-Effects-Spawning Spawning effects

The basic operation that can be done with %Swarm is spawning an instance of an effect, and that is done with the [EffectsManager](@ref Swarm::IEffectsManager).
First you have to declare an intrusive pointer to the Swarm::IEffect class, which is where the effect will be stored. Then you call
the `CreateVisualEffect()` method with the ID of the effect. This method returns `true` if the effect was sucessfully created; it's good practice to check
it before doing anything with it to avoid crashes:
~~~~{.cpp}
IVisualEffectPtr effect;
if (EffectsManager.CreateVisualEffect(id("SG_ufo_scan_HitGround"), 0, effect)) {
	// This will only be executed if the effect existed and a new instance was created
}
~~~~

Now, with just this the effect will not show yet. You have to call `Start()` to make it show; similarly, you can kill it anytime by calling `Stop()`.
~~~~{.cpp}
IVisualEffectPtr effect;
if (EffectsManager.CreateVisualEffect(id("SG_ufo_scan_HitGround"), 0, effect)) {
	effect.Start();
}
~~~~

@section Swarm-Effects-Transform Transforming the effects

With what you learned before, the effects will always spawn at the same position. Obviously, this is not what we want. The effect class
has a method called `SetSourceTransform()` that allows us to move, scale and rotate the effect. This takes a Transform object; for more information on how
it works, check the [math tutorial](_math.html).

~~~~{.cpp}
// This set the scale of the effect to 0.5 (so it will be half the original size)
// and moves it one unit up. As you can see, transformations can be concatenated
effect->SetSourceTransform(Transform().SetScale(0.5f).SetOffset(0, 0, 1.0f));
~~~~

Another important property of effects is the **seed**. A seed is a special number used to generate random numbers. Many effects, in order to look variated,
often depend on random numbers to make multiple instances of the same effect look different. By fixing a seed, you will always make it look the same.
~~~~{.cpp}
// Seed is just an integer number
effect->SetSeed(8721947);
~~~~


@section Swarm-Effects-Examples Examples

@subsection Swarm-Effects-Examples-1 Example 1: Spawning effects at random positions

In this example we will spawn multiple instances of `SG_gasGiant_01~` (which corresponds to ID `0x03F54A4F`). Actually, we will make it more interesting:
there are 12 different gas giant effects, and their IDs can be accessed by just adding to that first ID. We will create one instance of each gas giant and place
it in a random position (in a radius of 7 units) using Math::randf()

~~~~{.cpp}
for (int i = 0; i < 12; ++i) {
	IVisualEffectPtr effect;
	if (EffectsManager.CreateVisualEffect(0x03F54A4F + i, 0, effect)) {
		// X and Y can go negative, but we will only use positive Z so it doesn't go below the ground
		effect->SetSourceTransform(Transform()
			.SetOffset(Math::randf(-7, 7), Math::randf(-7, 7), Math::randf(0, 7))
			.SetScale(0.08f));
		effect->Start();
	}
}
~~~~

Try putting this code inside a custom cheat and execute it in the creature editor. This will be the result:
![](effects_example_1.png)

You can download the [`dllmain.cpp` source code here](effects_example_1.cpp).