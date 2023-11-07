@page Cheats The cheat console
@brief How to print text to the console and add new cheats

If you want to see an example of real mods that add new cheats, check the [`GmdlExport`](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/GmdlExport)
and the [`ModCreatorKit`](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/ModCreatorKit)

@section Cheats-Console Printing to the console

You can print text to the console using the App::ConsolePrintF() method. It works like the [C++ printf](http://www.cplusplus.com/reference/cstdio/printf/) method.

~~~~{.cpp}
App::ConsolePrintF("Hello World!");
~~~~

You can use "format specifiers" to print the value of variables. For example, `%d` can be used to print integers, and `%f` to print floats:

~~~~{.cpp}
App::ConsolePrintF("Integer: %d     Float: %f", 10, 4.5f);
~~~~

That prints `Integer: 10     Float: 4.5`

@section Cheats-Creating Adding a new cheat

Cheats use the ArgScript scripting language, which is the same used in many Spore files (such as `.prop.prop_t`). You have more info in the 
[SporeModderFX wiki](https://github.com/emd4600/SporeModder-FX/wiki/ArgScript).

To create a new cheat we have to create a class that parses an ArgScript command. You can use the *"ModAPI Cheat* item template to create one. It
basically creates a class like this:

~~~~{.cpp}
using namespace ArgScript;

class MyCheat 
	: public ICommand
{
public:
	void ParseLine(const Line& line) override;
	const char* GetDescription(DescriptionMode mode) const override;
};
~~~~

The simplest method is `GetDescription()`; there you just have to return a description of your cheat, that is showed when executing the `help` command.
Depending on the `mode` parameter you can return a more complex description which is shown when executing `help mycheat`.

~~~~{.cpp}
const char* MyCheat::GetDescription(DescriptionMode mode) const {
	if (mode == DescriptionMode::Basic) {
		return "This is a basic description";
	} else {
		return "MyCheat: does something like this.\n"
				"   You can include line breaks.\n"
	}
}
~~~~

`ParseLine()` is the method called when the player executes the cheat. The `line` parameter has information about the arguments and options that the player wrote.

You can add the cheat in your `Initialize()` method. Cheat names are case-insensitive:
~~~~{.cpp}
CheatManager.AddCheat("myCheat", new MyCheat());
~~~~

@section Cheats-Processing Processing the cheat line

Let's see an example of how to process arguments and options typed by the player in the cheat; this is done by calling functions on the `line` parameter.
Check the ArgScript::Line documentation. The main functions you must know are `GetArguments()` and `GetOption()`, which return a list of strings.
For example, if I have the line `mycheat 3 water -option (0.3, 0, 1.0)`:
 - `line.GetArguments(2)` will return a list with "3", "water".
 - `line.GetOption("option", 1)` will return a list with "(0.3, 0, 1.0)".
 
The numeric argument in those functions is how many arguments were expected; this means that if the player had only typed one argument, the first function
would have raised an exception, that is shown to the user in the console. The returned list contains strings, but you can convert those elements to integers,
floats, colors,... with the `mpFormatParser` member:

~~~~{.cpp}
void MyCheat::ParseLine(const Line& line)
{
	auto args = line.GetArguments(2);
	int val = mpFormatParser->ParseInt(args[0]);
	// In the above example, val = 3 and args[1] = "water"

	args = line.GetOption("option", 1);
	ColorRGB color = mpFormatParser->ParseColorRGB(args[0]);
}
~~~~

@section Cheats-Examples

@subsection Example 1: Planet Buster cheat

This cheat gives you a planet buster bomb, only if you are in the space stage. Optionally, the player can write
an argument which will be the number of bombs received. Fopr more information about Simulator, check the
["Interacting with the Simulator"](_simulator_basic.html) tutorial.

~~~~{.cpp}
// This is in dllmain.cpp

using namespace ArgScript;

class PlanetBusterCheat 
	: public ICommand
{
public:
	void ParseLine(const Line& line) {
		if (IsSpaceGame()) {
			cSpaceToolDataPtr tool;
			ToolManager.LoadTool({id("PlanetBusterBomb"), 0, 0}, tool);
			
			size_t numArgs;
			auto args = line.GetArgumentsRange(&numArgs, 0, 1);
			if (numArgs == 1) {
				tool->mCurrentAmmoCount = mpFormatParser->ParseInt(args[0]);
			}
			
			auto inventory = SimulatorSpaceGame.GetPlayerInventory();
			inventory->AddItem(tool.get());
		}
	}
	
	const char* GetDescription(DescriptionMode mode) const {
		return "Call the cheat. Drop the bomb. BOOM!";
	}
};

void Initialize() {
	CheatManager.AddCheat("planetBuster", new PlanetBusterCheat());
}
~~~~
