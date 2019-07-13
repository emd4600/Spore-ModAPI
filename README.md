This GitHub page hosts the Spore ModAPI development kit, used to create Spore mods with C++. 
To use those mods, you need the [ModAPI Launcher and Installers](http://davoonline.com/sporemodder/rob55rod/ModAPI/Public/).
The documentation of the SDK is available here: http://davoonline.com/sporemodder/emd4600/SporeModAPI/index.html

# Pre-requisites
To use the SDK, you need to have installed:
 - The Windows 10 SDK (you might need to use different versions if you don’t have Windows 10): https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk
 - Visual Studio 2017. You can download the free version here: https://visualstudio.microsoft.com/vs/community/

# Setting up the SDK

Download the `Spore.ModAPI.Development.Kit.2.4.0.zip` file provided in the [latest release](https://github.com/Emd4600/Spore-ModAPI/releases/latest). Unzip it to whatever directory you want, which will become your workspace for ModAPI mods.

Inside the folder you will find a file called `Spore ModAPI Templates.vsix`. If you have installed Visual Studio correctly, you will be able to execute the file. Once the installer is open, press *Install*.

Finally, open Visual Studio. Go to *Tools -> Code Snippets Manager…* . In the dialog that opens, ensure that the Language: field is set to *Visual C++*. Press the button *Add…* and find the folder called *ModAPISnippets*, which is inside the ModAPI tools folder we unzipped before.

## If you had already installed previous versions
For those that installed older versions of the ModAPI Development Kit, we need to take an extra step to get this working. If this is the first time you install it, you can skip this step.
1. Open Visual Studio. Go to *Tools -> Extensions and Updates…* . There, find the item called *Spore ModAPI Templates* and uninstall it.
2. Go to the directory `%APPDATA%\Microsoft\VisualStudio`. There you will see multiple folders, it’s recommended that you do these steps for all of them. Inside each of these folders, you go to ProjectTemplatesCache\Visual C++ Project. If you see a folder called `Spore ModAPI Template.zip`, delete it.

Now you can install the tempates as explained before.

# Creating a project

Go to *File -> New -> Project…* . A dialog will open; under the tab Visual C++, select the template called Spore ModAPI Template. Now in the bottom part of the dialog there are two fields you must modify:
- `Name`: Insert the name of your mod; do not to use whitespaces. 
- `Location`: Where your mod files will be saved. Use the button *Browse…* to navigate to the *Projects* folder inside the ModAPI directory you unzipped before.

Now, there is one more thing you might need to do. Open the project configuration, ensure the **Configuration** box is set to `All Configurations` like shown in the picture below. Now, in the General categories, there are two settings you must pay attention to.
 - `Windows SDK Version`: Ensure this setting is set to the latest SDK version.
 - `Platform Toolset`: Ensure this setting is set to **Visual Studio 2017** (not necessarily v141)

![VS Project Configuration](https://sporemodder.files.wordpress.com/2018/10/b9lhk9y2.png?w=1024)


Once you have created a new project, you must select the version you are going to compile the `.dll` for (`Debug - Disk`, `Debug - Patched Steam`, etc). 
 - `Disk`: For CD versions and pirated copies.
 - `Steam Patched`: For Steam, GoG and Origin versions.
 - `Steam`: For older versions, this one is deprecated and must not be used.