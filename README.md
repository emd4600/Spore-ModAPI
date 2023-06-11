# Spore ModAPI SDK

This GitHub page hosts the Spore ModAPI development kit, used to create Spore mods with C++. 
To use those mods, you need the [ModAPI Launcher and Installers](http://davoonline.com/sporemodder/rob55rod/ModAPI/Public/).

The **Spore ModAPI SDK** allows you to create C++ mods for Spore. These mods are compiled into `.dll` files,
that can then be used by the **[ModAPI Launcher Kit](http://davoonline.com/sporemodder/rob55rod/ModAPI/Public/index.html)** to inject them into Spore.

The documentation of the SDK is available here: https://emd4600.github.io/Spore-ModAPI/

Instructions about download, installation and updating can be found [in this tutorial](https://emd4600.github.io/Spore-ModAPI/_installation.html).

The source code can be found in this GitHub repository. If you want to see the SDK in action, check the [list of open source mods](https://github.com/emd4600/SporeModder-FX/wiki/List-of-open-source-mods).
This project also includes the source code of some example mods made with the ModAPI SDK:
 - [ModCreatorKit](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/ModCreatorKit#modcreatorkit)
 - [GmdlExport](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/GmdlExport)
 - [EditorPlayModeNoBounds](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/EditorPlayModeNoBounds)
 - [SpaceToolCheat](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/SpaceToolCheat)

To compile the core DLLs (unless you want to develop the SDK itself, you don't need to do this):
 1. Open the Visual Studio Command Prompt
 2. Navigate to the SDK root directory.
 3. Execute `msbuild "Spore ModAPI" -t:BuildDlls -p:BuildVer=177 -p:Config=Release` (changing the version and config accordingly)

## Working with Ghidra

If you want to extend the SDK, or just want to investigate Spore's source code, you can use the free program [Ghidra](https://ghidra-sre.org/) to do so. The SDK includes a plugin and some files, that can be used to add all the known data from the SDK into Ghidra. These are prepared to work with Ghidra's function decompiler, making reverse engineering much easier:

![](https://i.imgur.com/pCE2zPL.png)

To use them:
 1. Open your project in Ghidra.
 2. If you hadn't done it yet, analyze the executable (this finds all functions).
 3. Open `Windows > Script Manager`.
 4. On the top bar of the new window, click on the `Manage Script Directories` ![](https://i.imgur.com/McdNx46.png)
 5. On the popup window, click on the `+` button and search the `Spore ModAPI SDK/SDKtoGhidra/GhidraScript` folder in your SDK installation.
 6. Close that popup and go back to the script manager, find the `ImportSporeSDK.java` script (it's in the `Data` category).
 7. Execute it: it will ask for a file, select the `Spore ModAPI SDK/SDKtoGhidra/SporeGhidra_march2017.xml` (or `SporeGhidra_disk.xml` if you use a disk Spore installation).
 8. Wait for it to complete; in the console, you can see all the functions and data types that have been added.

Keep in mind that Ghidra's decompiler is only an approximation, and it will not produce code that is directly executable on the SDK. There are several differences to keep in mind, among others:
 - Ghidra data types have no inheritance, so the decompiler isn't aware of superclass/subclass relationships.
 - Ghidra does not understand virtual functions. When calling a virtual function, Ghidra first grabs the function pointer from the virtual function table, and then executes it.
 - Ghidra does not understand `intrusive_ptr`s, which means the code it generates makes calls to `AddRef()` and `Release()` (which you never see in the SDK).

### Generating Ghidra files (only for SDK maintainers)

If you are extending the SDK and need to update the Ghidra files, you need to install Python 3.9 (at least) and the library `libclang`, then run `extract.py`.