This mod adds a color wheel to the editor, which lets you select the precise color you want instead of relying on preset colors. You can 
[download it here](https://sporemodder.wordpress.com/infinite-colors-enhanced-color-picker/).

![](https://i.imgur.com/X8XjsKK.png)

The first step in this mod was designing the chooser UI in the SPUI Editor, with [SporeModder FX](https://emd4600.github.io/SporeModder-FX/). To
every important window we assigned it a unique `ControlID`, so that it can be used from the code.

The `ColorWheelSwatchUI` class is an extension of a `Palettes::ColorSwatchUI` object and it's used to control the created SPUI. It basically stores the 
color as **HSV** (hue, saturation, value) instead of the usual red, green, blue, and uses UI messages to change that color. In the color wheel, the 
distance from the center is the *saturation*, the angle is the *hue*, and the bar below the wheel represents the *value*.

Knowing how to change the color required some reverse engineering; you will see that the method that does it directly calls addresses in code that 
haven't been exposed by the SDK yet. When the player releases the mouse the mod sends a `ColorChangedMessage` so that the editor adds undo/redo actions.

To add the button that displays the color wheel we've had to detour the `ColorPickerUI::Load` method. Unfortunately we cannot call the original implementation,
as we need the rest of buttons to be slightly smaller to fit the new button. So what you see is a copy of the Spore code that generates those buttons.
The code that detects when that button is pressed and decides to show the wheel is also copied from what Spore does with the other buttons.