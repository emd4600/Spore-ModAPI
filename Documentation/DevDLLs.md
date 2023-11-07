@page DevDLLs Compiling ModAPI core DLLs
@brief How to use the latest, non-released %ModAPI features

Mods made with the %ModAPI SDK only work using a specialized launcher; among other reasons, that's because
%ModAPI mods require an additional set of DLLs that are responsible for communicating your mod with the Spore code. 
Those are called the **core %ModAPI DLLs**.

Often, some of the new features added in the SDK require a new version of those core DLLs. Those features 
cannot be used in public mods until the launcher itself updates its core DLLs (because otherwise, players won't
be able to play the mod); but you, as a developer, can try them out.

In this tutorial, we'll show you how to compile the core DLLs so you can test new features. Keep in mind
that you cannot release mods you create with these new features until the %ModAPI Launcher Kit updates its core DLLs as well.

@section DevDLLs-Compiling Compiling the core DLLs

In order to compile a development version of the core DLLs:
1. Open the project `[Spore %ModAPI SDK folder]\Spore %ModAPI\Spore ModAPI.vcxproj`
2. In Visual Studio, open the file `SourceCode\stdafx.h`. There, you will have to edit the 
value of the `#define EXECUTABLE_TYPE` line: set it to 0 if you have a disk version of Spore, 2 otherwise.
3. Set the compile configuration (below the menu bar) to `Debug DLL`. Now compile the project.
4. If there are no errors, the files will be at `[Spore %ModAPI SDK folder]\dll\Debug`. Copy the files `SporeModAPI.dll` and `SporeModAPI.lib`
to `[Spore %ModAPI Launcher Kit]\coreLibs\`; make a backup copy of the files there before, so you can always restore them.
5. If you have a disk version of Spore, replace `SporeModAPI.disk.dll` (remember to backup first!) with the newly generated `SporeModAPI.dll`; 
otherwise, do the same but to the `SporeModAPI.march2017.dll` file.