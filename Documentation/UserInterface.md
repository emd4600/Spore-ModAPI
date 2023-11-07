@page UserInterface User Interface
@brief How to load user interface elements to Spore and react to them

@tableofcontents

In this tutorial we will explain the basic operations you need to know to create and react to user interface in Spore.
The user interface system is called UTFWin, and everything you need is inside that namespace.
For simplicity, we will assume through all this tutorial that `using namespace UTFWin;` is being used, so we don't have to write `UTFWin::` all the time.

First of all, we must discuss the two main elements in the Spore user interface: `IWindow` and `IWinProc`.
 - Windows are elements that occupy a region of the screen. Images, text fields, buttons, sliders... they all implement `IWindow`.
 - Window procedures are used to give functionality to windows. They don't have a visual representation.
 
The windows are grouped creating a hierarchy: a window can have multiple children windows. A window can only have one parent window: the window that doesn't have any
parent is called the *root* window. For example, in the editor, the palette is a children of the root window; each of the pages is a children of the palette; 
each of the parts is a children of the page, etc. Windows are identified with a `controlID`, it's like their name.

Windows can also have multiple window procedures. Procudres do not form a hierarchy: they do not have children nor parents, and the same procedure can be added
to multiple windows. For example, the `EditorUI` class is a procedure (it implements `IWinProc`) and it's added to all the buttons in the editor.

In Spore, layouts come in `.spui` (**Sp** ore **U** ser **I** nterface) files. You can view and edit them using [SporeModder FX](https://emd4600.github.io/SporeModder-FX/).

The `EnhancedColorPicker` is an example of a mod that uses the %UTFWin module, you can see the [source code in GitHub](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/EnhancedColorPicker).

@section UserInterface-Loading Loading SPUI layouts

`.spui` layouts are represented in the code by the [UILayout](@ref UTFWin::UILayout). In order to load a SPUI file, you must declare an instance of that class
(that is, without using `new`); generally that is stored inside a class, but it's not necessary. Then, use the
[LoadByID()](@ref UTFWin::UILayout::LoadByID()), [LoadByName()](@ref UTFWin::UILayout::LoadByName()) or [Load()](@ref UTFWin::UILayout::Load()) methods. 

~~~~{.cpp}
// By name: it uses a unicode string, so you have to prefix it with 'u'
UILayout layout;
layout.LoadByName(u"EditorSharedUI");

// By id:
UILayout layout;
layout.LoadByID(0xF0F17503);
~~~~

By default, when a layout is loaded it's added to the main window of the game. Very often that's not what you will want, so you can
change it by calling `SetParentWindow()`:
~~~~{.cpp}
UILayout layout;
layout.LoadByName(u"EditorSharedUI");

// 'window' is an IWindow*
layout.SetParentWindow(window);
~~~~

@section UserInterface-Windows Main operations with windows
@subsection UserInterface-Windows-Get Getting windows

The main window of the game can be accessed with the `WindowManager`:
~~~~{.cpp}
// returns an IWindow*
auto window = WindowManager.GetMainWindow();
~~~~

As was mentioned before, windows can be identified with a `controlID`. Not all windows have an ID, as you don't always need to access a window. You can get
the `IWindow*` object with a certain ID by calling the `FindWindowByID()` method, which can be called both in `UILayout` and in `IWindow`s:

~~~~{.cpp}
UILayout layout;
layout.LoadByName(u"EditorSharedUI");

// get the window with ID 0xd04562fa
auto window = layout.FindWindowByID(0xd04562fa);
~~~~

@subsection UserInterface-Windows-Add Creating and adding windows

Since `IWindow` is an abstract interface, you cannot create new instances of it directly. Instead, you have to instatiate one of the implementations (standard window,
button, etc). For now, the %ModAPI SDK only supports the `Window` class. You can use the `AddWindow()` and `RemoveWindow()` methods of `IWindow` to change the hierarchy:
~~~~{.cpp}
auto window = new Window();
window->SetControlID(id("MyPanel"));
window->SetFillColor(Color::RED);
window->SetArea({ 50, 50, 250, 250 });

WindowManager.GetMainWindow()->AddWindow(window);
~~~~

When you use `AddWindow()`, the window gets removed from its previous parent, if any.

If you want to store a pointer to a window in a class, it's recommended to use an intrusive pointer (`IWindowPtr`)

@subsection UserInterface-Windows-Flags Visible, enabled: flags and state

Certain properties in a window are controlled by its **flags**: a number where every bit means one thing. The two main flags control visibility and whether the button 
is enabled or disabled: `kWinFlagVisible` and `kWinFlagEnabled`. You can get the flags with `GetFlags()`, then use the bitwise AND operation to check them:
~~~~{.cpp}
if (window->GetFlags() & kWinFlagEnabled) {
	// This code only gets executed if the window is enabled
}
~~~~

You can use `SetFlag()` to change the value of one of the flags:
~~~~{.cpp}
// Hide the window
window->SetFlag(kWinFlagVisible, false);
~~~~

The state of a window are also flags, but control whether the player is hovering the window, clicking it, etc. Not all window types support it:
~~~~{.cpp}
// Is the player hovering the button?
if (button->GetState() & kStateHover) {

}
~~~~

@subsection UserInterface-Windows-Hierarchy Working with the window hierarchy

 - As explained before, all windows (except root ones) have a parent window, which you can get by calling `GetParent()`.
 - You can use `AddWindow()` to add new children windows, `RemoveWindow()` to remove children windows.
 - `window1->IsAncestorOf(window2)` will tell you if `window2` is a children of `window1`. This works recursively, meaning that this is checked for all
 children of `window1` as well.
 - Use `BringToFront(window)` to ensure that the children window `window` is displayed in front of all other children. Similarly, `SendToBack(window)` will
 make it display below all other children.
 - It's possible to iterate through all children of a window:
~~~~{.cpp}
for (auto child : window->children()) {

}
~~~~
 - If you want to destroy a window, as well as all it's children:
~~~~{.cpp}
window->GetParent()->DisposeWindowFamily(window);
~~~~

@section UserInterface-Layouts Window area and layouts

Windows occupy a region of the screen. Regarding to this we can differentiate two different values: the `area` and the `realArea`.
Both this properties are defined by a `Rectangle`, which is four float values: X & Y coordinates of the top-left corner, X & Y coordinates of the
bottom-right corner.
 - The `realArea` is the real coordinates.
 - The `area` is relative to the parent, and it can be altered by window procedures.
 
Therefore, the `area` are only used as parameters; if you want to know the real position and size of a window, you have to use `GetRealArea()`.
There exists a special type of window procedures that are designed to change their area depending on their parent; those procedures are called **layouts**.
Layouts use the `area` property and the parent of a window to adapt and change the `realArea`. Why is that useful? Let's see it with a quick example:
imagine you want a window in the center of the screen. What coordinates is that, (400, 300)? You cannot know, because it depends on the resolution. Layouts
allow you to do this easily. There are two layout classes:
 - [SimpleLayout](@ref UTFWin::SimpleLayout): It makes the `area` coordinates be relative to the parent real area. It does so with a proeprty called `anchor` 
(similar to other %UI designers) which defines the sides of the parent the window is attached to.
 - [ProportionalLayout](@ref UTFWin::ProportionalLayout): Similar to the SimpleLayout, but this one uses proportions.
 
Let's see it with examples. We want to create a window that is *80x50* in size (widht 80 and height 50) and is always attached to the bottom right corner of its
parent. We can do it with a SimpleLayout:
~~~~{.cpp}
auto window = new Window();
window->SetFillColor(Color::RED);

// With this, the 'area' of our window will be relative to the bottom right of its parent
window->AddWinProc(new SimpleLayout(kAnchorBottom | kAnchorRight));

// Since now the 'area' origin of coordinates starts at the bottom right, we have to use
// negative coordinates to move it inside our parent
window->SetArea({ -80, -50, 0, 0 });

WindowManager.GetMainWindow()->AddWindow(window);
~~~~

Another example: we want to create a window that is *200x100*  in size and is always centered in the screen. We can do it with the ProportionalLayout:
~~~~{.cpp}
auto window = new Window();
window->SetFillColor(Color::RED);

// Each of this values means that the left side starts at 50% of the parent width, 
// the top side starts at 50% of parent height, etc
window->AddWinProc(new ProportionalLayout(0.5f, 0.5f, 0.5f, 0.5f));

window->SetArea({ -100, -50, 100, 50 });

WindowManager.GetMainWindow()->AddWindow(window);
~~~~

Try adding these codes inside a cheat and play with it a little.

Windows have some extra methods to modify the area: `SetLocation()`, `SetSize()`. There are also equivalents that set these properties after the 
layouts have been applied: `SetLayoutArea()`, `SetLayoutLocation()`, `SetLayoutSize()`.


@section UserInterface-Drawables Drawables

Windows have two basic parameters that control its appearance: the *fill* and the *shade* colors. The *fill* color is rendered in the background, 
filling all the area of the window. The *shade* color is a tint that changes how all the window is rendered.

Additionally, windows can use drawables to render more advanced things. Classes that implement UTFWin::IDrawable can be added to a window with `SetDrawable()`;
a single window can have only one drawable. Also keep in mind that not all drawables are valid for all windows; you cannot add a `SliderDrawable` to a button.

`IDrawable`s can also be inherited in order to create new drawables. For example, the game minimap is a modified drawable that renders an image generated in the code.

@subsection UserInterface-Drawables-Image Image Drawables

The most common drawable is the `ImageDrawable`, which just renders an image into the window. Even though you can configurate the drawable itself, 
there's also a method that creates the window, loads the image and creates the drawable all in one:
~~~~{.cpp}
// The window will be added to 'parentWindow'
// It's {instance, type, group}
auto window = IImageDrawable::AddImageWindow({ id("cultural_turret"), TypeIDs::png, 0x65928944 }, 0, 0, parentWindow);
~~~~

@section UserInterface-Events Procedures: reacting to events

One of the most common uses of the %UTFWin module is reacting to %UI events. User interface events are caleld **messages**, and are represented by the
UTFWin::Message class; there are messages for everything that can happen in the %UI: mouse and keyboard input, clicking buttons, displaying elements, editing text,...

**Window procedures** (`IWinProc`) are classes that are used to react to events in windows. To implement your own window procedure you have to create a new class
that inherits `IWinProc`, and override its two main methods:
~~~~{.cpp}
class MyListener 
	: public IWinProc
{
public:
    int GetEventFlags() const override; 
    bool HandleUIMessage(IWindow* window, const Message& message) override;
};
~~~~

You can also create a basic window procedure using the *"ModAPI Window Procedure"* item template.

Now, what code goes in each of those two methods? `GetEventFlags()` must return a combination of flags that tells which kind of events this window procedure is
listening to. The available flags are documented at UTFWin::EventFlags.
~~~~{.cpp}
int MyListener::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}
~~~~

The other method is the important one. `HandleUIMessage()` is called every time a message is received in a window that has this procedure added.
The return value is important: it's whether the message has been handled or not. This means that if the method returns `true`, no other window will
receive this message.

~~~~{.cpp}
bool MyListener::HandleUIMessage(IWindow* window, const Message& message)
{
    // by default, just return false since we didn't handle the message
    return false;
}
~~~~

The `window` parameter is the window that is calling this procedure, but not necessarily the window where the event was generated. This is because the same procedure
can be added to multiple windows. You can get the window that generated the event with `message.source`. You can also use the method `IsType()` to know the type of
message. The `message` parameter contains information related to the event, but not all data is always valid; it depends in the event type. For example, you can 
only use `message.Key` if the message was a key pressed, key released, etc.

For example, this code will print something to the console if a button with the ID "ExitButton" was clicked:
~~~~{.cpp}
bool MyListener::HandleUIMessage(IWindow* pWindow, const Message& message)
{
    if (message.IsType(kMsgButtonClick)) {
        if (message.source->GetControlID() == id("ExitButton"))
        {
			App::ConsolePrintF("You pressed the exit button");
            // We did handled the message, return true
            return true;
        }
    }
    // By default, just return false since we didn't handle the message
    return false;
}
~~~~

In addition to window procedures, there are the UTFWin::InteractiveWinProc and UTFWin::InteractiveWindow classes. These classes extend `IWinProc` and `IWindow` 
respectively and define methods that allow to easily handle messages. Instead of handling everything in a big `HandleUIMessage()` method, in these classes you
can extend the method that listens to the type of event you want, for example `OnMouseClick()`.

@subsection UserInterface-Events-Sending Sending events

It is possible to programatically generate an event. This can be used, for example, to make the game believe certain button was clicked.

~~~~{.cpp}
Message message;
message.source = window;  // Which window generated this event?
message.eventType = kMsgMouseDown;  // What type of event is it?
// Now we want to set the specific parameters (i.e. the position that was clicked,...).
message.Mouse.mouseState = kMouseLeftButtonDown;
message.Mouse.mouseX = 50;
message.Mouse.mouseY = 276;

// Now just send the message
window->SendMsg(message);
~~~~