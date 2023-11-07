@page Sdk-Basics-Strings ModAPI SDK Basics: Strings
@brief How strings and text are used in the %ModAPI

In the %ModAPI SDK there are multiple ways to represent text: C-strings, C++ strings, and localized text.
Generally, you will use the C++ strings, and localized text if you need your text to accept translations. The use of C-strings is not recommended,
but many calls in Spore use it so it's good to know what it is.

@section Sdk-Basics-Strings-Unicode ASCII vs Unicode

Usually, the strings we use in C++ are encoded in ASCII. This means that each character is just one byte, and the possible characters are quite limited.
You have all the characters you need to write in English plus some extras, but not much more.

When other languages come into play, ASCII is not enough. Instead, you cna use the Unicode encoding: two bytes per character, can represent everything that you need,
from Russian to Chinese to plain English.

To distinguish between ASCII and Unicode, we add a *16* to the type (because its 16 bits): instead of `char`, `char16_t`; instead of `string`, `string16`.
When writing string literals, you have to add a `u` prefix to use Unicode:
~~~~{.cpp}
// C-style strings
const char* text = "This is ASCII";
const char16_t* text = u"This is Unicode";

// C++ style strings
string text = "This is ASCII";
string16 text = u"This is Unicode";
~~~~

When printing formatted strings (`printf`, `App::ConsolePrintF`, etc), `%%s` is the format specifier for ASCII and `%%ls` for Unicode.

@section Sdk-Basics-Strings-C-strings C-Strings

C-strings are the most basic representation of strings, they are just a pointer to an array of characters, like `char*`.

~~~~{.cpp}
const char* text = "This is ASCII";
const char16_t* text = u"This is Unicode";
~~~~

They are set as `const` because the text inside must not be modified.

It is possible to access particular characters by using `[]`. To calculate the length of the string, use the method `strlen()`.

@section Sdk-Basics-Strings-Cpp-strings C++ Strings

This will be how you use strings more frequently, with the types `string` (ASCII) and `string16` (Unicode).
~~~~{.cpp}
string text = "This is ASCII";
string16 text = u"This is Unicode";
~~~~

You can concatenate strings with `+`.
~~~~{.cpp}
string text = "This is ASCII";
string text2 = "My text: " + text; 
~~~~

You can access particular characters by using `[]`. Calling `text.size()` will return the length of the string. You can also use *for each* loops to get every character in the string:
~~~~{.cpp}
string text = "random text";
for (int i = 0; i < text.size(); ++i) {
	App::ConsolePrintF("Character %d: %c", text[i]);
}

// This does the same:
for (char c : text) {
	App::ConsolePrintF("Character %d: %c", c);
}
~~~~

When using a C++ string in a `printf`-like operation, you have to call `.c_str()`:
~~~~{.cpp}
string16 text = u"This is Unicode";
App::ConsolePrintF("Printing a unicode string: %ls", text.c_str());
~~~~

It is also possible to save the result of a printf inside a string:
~~~~{.cpp}
string result = "";
result.sprintf("%d - %d", 6, 23);
~~~~

@section Sdk-Basics-Strings-Localized Localized Strings

In Spore and the %ModAPI SDK, it is possible to use strings that depend on the current language of the game. THis is done with the LocalizedString class.
These strings are identified with a *table ID* and an *instance ID*. The table ID is the name of a `.locale` file inside the `locale~` folder; the instance ID is a hexadecimal
number that identifies a string within that file. 

You can specify the table and instance IDs either when creating the LocalizedString or by calling the `SetText()` method. Call `GetText()` to get the translated text (it's Unicode):
~~~~{.cpp}
LocalizedString text(id("ScenarioMode"), 0x07D91073);
string16 translation = text.GetText();
~~~~