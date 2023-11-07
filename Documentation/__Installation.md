@page Installation Installing the %ModAPI SDK
@brief How to install Visual Studio, the %ModAPI SDK, and how to receive updates

@tableofcontents

@section Installation-Installing Installation

@subsection Installation-Installing-VS Visual Studio

You need to download **Visual Studio 2019 Community**, which is the free version. [You can download it here](https://visualstudio.microsoft.com/vs/)
After the installation, the **Visual Studio Installer** will open, allowing you to choose what features you want. For the %ModAPI SDK, you need to check
the following:
 - **Desktop development with C++**. When you select this option, on the panel on the right there are some other options you can check. Ensure the **MSVC v142**
 and **Windows 10 SDK** options are checked.
 - Optionally, you can also install **Game development with C++**. If you want to do mods related with graphics, you will need this to interact with DirectX.
 
![](installer.png)
 
Once you have all that selected, click on `Modify` and wait until it's installed.

@subsection Installation-Installing-Launcher ModAPI Launcher Kit

In order to use the %ModAPI SDK and the mods you generate with it, you will need the **%ModAPI Launcher Kit**, which [you can download here](http://davoonline.com/sporemodder/rob55rod/%ModAPI/Public/index.html).
From now on, you should launch Spore through the launcher.

@subsection Installation-Installing-SDK ModAPI SDK

Open Visual Studio. You will see four big buttons, click on the first one: **Clone or check out code**. In the new panel you have to fill two things:
 - *Repository location*: Paste this link there: `https://github.com/emd4600/Spore-ModAPI.git`
 - *Local path*: This is the folder in your computer where the %ModAPI SDK will be saved.
 
Once you fill those two fields, click on `Clone` and wait until the project finishes downloading.

When it's finished, find the menu bar at the top and go to `Extensions -> Manage Extensions`. 
A dialog will open; in the search bar, type `spore`. You will see the **Spore %ModAPI SDK Templates**
item appear, select it and click on `Download`. When it finishes installing, you will need to restart Visual Studio.

![](extension.png)

@note If Visual Studio gives you problem installing the extension, [you can download it manually](https://marketplace.visualstudio.com/items?itemName=emd.modapisdk).

@section Installation-Creating Creating new projects

Now you can create a %ModAPI project clicking the `Create a new project` button in the splash screen or using the menu`File -> New.. -> Project`. 
In the dialog that appears, type *spore* in the search bar. Select the **Spore %ModAPI Project** and click on `Next`.

![](project_template.png)

Now you can give your project whatever name you want. In the `Location` field, click the `...` button to find the folder where your project will be stored.
You can save it wherever you want, but we recommend you to save it in the `Projects` folder of the %ModAPI SDK folder.

![](new_project.png)

Now a small dialog will appear asking you the paths to the launcher kit and to the SDK. They should already be filled, but if one of them is blank you will have
to find that path. Click `Accept` and your project will be created. When the project finishes creating, the **Solution Explorer** will appear:

![](solution_explorer.png)

As you can see, your "solution" (which is a collection of projects) shows two projects: the one you created and the **Spore %ModAPI** one. That last project is 
part of the SDK and is shared between all your projects, it's there so you can see its files and update the SDK.

By default, your mod project does nothing and only contains one file, `dllmain.cpp`. That is going to be the main file of your mod, check 
[the `dllmain.cpp` tutorial](__sdk-_basics-_dll_main.html).

You can compile your project by clicking `F7` or the menu button `Build -> Build Solution`. The `.dll`s will be packed to the location you chose for the 
%ModAPI launcher kit, which means that you can test them directly. You can open the game through the launcher by just pressing `Ctrl + F5` or the menu 
button `Debug -> Start without debugging`.

@subsection Installation-Creating-Items Item templates

The extension you installed before also contains **item templates**, which let you easily create the basic files related to the %ModAPI SDK. To add one,
right click on the folder where `dllmain.cpp` is (it has the name of your project) and click `Add -> New Item..`. A dialog will open, and there you will 
see the multiple item templates that you can use.

![](item_templates.png)

@section Installation-Updating Updating the SDK

To update the SDK you have to use the **Team Explorer** window in Visual Studio. If it's not showing, click on the menu `View -> Team Explorer`. 
There, click on the `Sync` button. 

![](sync.png)
![](fetch.png)

The important one is `Incomming Commits`. If you click on `Fetch`, it will check if there have been any updates; if you click on `Pull` it will download them into
your copy of the SDK.

Keep in mind that you should also update the %ModAPI Launcher Kit in order to use all the new features in the SDK.