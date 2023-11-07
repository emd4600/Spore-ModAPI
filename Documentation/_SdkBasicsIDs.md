@page Sdk-Basics-IDs ModAPI SDK Basics: IDs & Hashes
@brief How Spore identifies files, folders, properties,...

@section Sdk-Basics-IDs-Hex Hexadecimal Numbers

We are used to count see numbers like 15, 3540, 285,... . What all these numbers have in common is that they use the **decimal base**: when we count to ten, we add another digit.
However, this is not the only way to represent a number; there's one way used a lot in computers, **hexadecimal**.

Hexadecimal is similar to the decimal base we are used to, but instead of adding digits when we count up to 10, we do it with 16. 
In base 10 we only have 10 different digits (0, 1, 2, 3, 4, 5, 6, 7, 8, 9); in base 16, we have 16: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F

This means that 7 is the same value, whether in base 10 or 16. But B, in base 16, means 11; C means 12, F means 15, etc

In the decimal base, when we move one digit, we multiply it by ten: 2 is two, but 20 is two times 10.
In hexadecimal we do the same, but multiplying by 16: 2 is two, but 20 is two times 16, that is, 32.

In C++, when we want to write a hexadecimal number, we prefix it with `0x`. For example, to write 24 in hexadecimal we can do `int number = 0x18;`

@section Sdk-Basics-IDs-IDs Hashes

An ID is an 8-digit hexadecimal number that Spore uses instead of names to identify many things (files, properties,...), they are sometimes referred as **hashes**.
It's possible to get the hash corresponding to a name, but not the other way around. Hashes are case-insensitive (i.e. `asd` and `ASD` have the same hash).

Even though they are just integers, IDs are represented in the %ModAPI SDK with the type `uint32_t`. You can get the hash of a name by using the `id()` function. 
For example, `id("ModAPI")` gives you `0x30B264D5`. [SporeModder FX](https://emd4600.github.io/SporeModder-FX/) also has a feature to calculate hashes. 

![](PB1deAP.png)

@section Sdk-Basics-IDs-ResourceKey Resource Keys

In Spore, files are identified with 3 IDs: the *group* (that is, the folder name), the *instance* (the file name), and the *type* (the extension). 
These three IDs are called a ResourceKey, and it's one of the mot common structures in the SDK. In Spore files, resource keys are written 
like `group!instance.type`. In the code, you have multiple ways of declaring a ResourceKey:

~~~~{.cpp}
// Imagine we want to make CivicObjects!EP1_Barrel.prop
// The type ID for prop is 0x00B1B104
// When declaring a resource key, the order is instance, type, group

ResourceKey key = ResourceKey(id("EP1_Barrel"), 0x00B1B104, id("CivicObjects"));

ResourceKey key = { id("EP1_Barrel"), 0x00B1B104, id("CivicObjects") };

ResourceKey key;
key.instanceID = id("EP1_Barrel");
key.typeID = 0x00B1B104;
key.groupID = id("CivicObjects");
~~~~

The most common type IDs are in the enum TypeIDs; similarly, the most common group IDs are in the enum GroupIDs. So
the previous key could be written as `ResourceKey key = { id("EP1_Barrel"), TypeIDs::prop, GroupIDs::CivicObjects };`