@page Properties Properties & .prop files
@brief How to read and write .prop files, the most common Spore file format.

@note This tutorial assumes you have read the *C++ Basics* tutorials.

If you ever look to the Spore files in a `.package`, you will see most of them are `.prop` files. These are very simple files that assign
values to properties. An example of `.prop` file:

~~~~
bool modelAdventureCameraAlphas true
key modelLOD0 DI_WrapTotem.rw4
~~~~

You have more information about this format in the [Spore modding wiki](https://github.com/emd4600/SporeModder-FX/wiki/Property-Lists-(.prop)).

@tableofcontents

@section Properties_Includes Required includes

 - `<Spore\Properties.h>`
 
@section Properties_Getting Getting a property list

A `.prop` file is represented by an object of the App::PropertyList class. To read a `.prop` file, you use the 
[GetPropertyList()](@ref App::IPropManager::GetPropertyList) of the [PropManager](@ref App::IPropManager). The method takes the instance and group IDs,
and an `intrusive_ptr` that will store the property list. For example, to get the `ConsequenceTraits!clg_meat.prop` file:

~~~~{.cpp}
PropertyListPtr propList;
PropManager.GetPropertyList(id("clg_meat"), id("ConsequenceTraits"), propList);
~~~~

The method returns `true` if the file was read successfully, false otherwise. If it returned `true`, now `propList` will contain the data of the file.

@section Properties_Reading Reading properties from a list

The App::Property class provides many static methods to get the value of a property.

To get a single value, you must use the `GetX()` methods, where X is the type of property. First you have to declare the variable where 
the value will be stored, and then call the method giving the property list, the ID of the property, and the variable. 
The method requires a raw pointer (`*`) instead of an `intrusive_ptr`, so we use `.get()` on the property list to get it. For example:

~~~~{.cpp}
float scale;
App::Property::GetFloat(propList.get(), 0x00FBA611, scale);  // modelScale

ResourceKey modelName;
App::Property::GetKey(propList.get(), 0x00F9EFBB, modelName);  // modelMeshLOD0
~~~~

The method returns `true` if the propery was found and of the type requested, so the value should only be used if it returned `true`.

Some properties come in arrays, that is, a single property may have multiple values. You can access them with `GetArrayX()`, which will provide you
with a pointer to the values and the count of how many values there are.

~~~~{.cpp}
ResourceKey* names;
int count;
App::Property::GetArrayKey(propList.get(), 0x02A907B5, count, names);  // modelEffect
// Now you can access them like names[0], names[1], ...
~~~~

@note Usually it is not possible to use `id()` to get the ID of a property. [SporeModder FX](https://emd4600.github.io/SporeModder-FX/) can be used to get it.

@section Properties_AppProperties Using AppProperties

%App properties are special properties that can be accessed with very good performance, and therefore are used frequently in the code. They are the properties defined in the `AppProperties.trigger` file, and are configured in the `Config\ConfigManager.txt` files of the player.
The IDs of the properties that can use the fast access are defined at App::SPPropertyIDs, and they are accessed by using the 
`GetDirectInt()`, `GetDirectFloat()`, `GetDirectBool()` methods on the `AppProperties` object:

~~~~{.cpp}
if (AppProperties.GetDirectBool(App::SPPropertyIDs::kWireframe)) {
	// ...
}
~~~~

@section Properties_Adding Adding properties to a list

Even though it is less common, it is also possible to add new properties or change the values of existing ones. This is used to store information;
for example, Spore generates a property list for each creation.

Creating a new property list is very simple, you just need to call `new`. You can then assign a name and folder with the `PropManager`:

~~~~{.cpp}
PropertyListPtr propList = new App::PropertyList();
PropManager.SetPropertyList(propList.get(), id("listName"), id("listFolder"));
~~~~

To assign properties, you have to use the `SetProperty()` method combined with the `SetValueX()` or `SetArrayX()` methods of the Property class:

~~~~{.cpp}
propList->SetProperty(id("dnaAmount"), &Property().SetValueInt32(80));

float values[3] = {30.4, 40, 10.941};
propList->SetProperty(id("scales"), &Property().SetArrayFloat(values, 3));
~~~~
