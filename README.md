This GitHub page hosts the Spore ModAPI development kit, used to create Spore mods with C++. 
To use those mods, you need the [ModAPI Launcher and Installers](http://davoonline.com/sporemodder/rob55rod/ModAPI/Public/).

The **Spore ModAPI SDK** allows you to create C++ mods for Spore. These mods are compiled into `.dll` files,
that can then be used by the **[ModAPI Launcher Kit](http://davoonline.com/sporemodder/rob55rod/ModAPI/Public/index.html)** to inject them into Spore.

The documentation of the SDK is available here: https://emd4600.github.io/Spore-ModAPI/

Instructions about download, installation and updating can be found [in this tutorial](https://emd4600.github.io/Spore-ModAPI/_installation.html).

The source code can be found in this GitHub repository. It also includes the source code
of 3 real mods made with the ModAPI SDK:
 - [EnhancedColorPicker](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/EnhancedColorPicker)
 - [GmdlExport](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/GmdlExport)
 - [ModCreatorKit](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/ModCreatorKit)

To compile the core DLLs (unless you want to develop the SDK itself, you don't need to do this):
 1. Open the Visual Studio Command Prompt
 2. Navigate to the SDK root directory.
 3. Execute `msbuild "Spore ModAPI" -t:BuildDlls -p:BuildVer=177 -p:Config=Release` (changing the version and config accordingly)
