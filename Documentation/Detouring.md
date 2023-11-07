@page Detouring Detouring
@brief How to redirect Spore methods

@section Detouring Detouring

One of the most promising features in the %ModAPI SDK is the ability of changing the code of certain Spore methods, known as **detouring**. If you
detour a method, your code will be executed when Spore tries to execute that method. This is actually the core of how %ModAPI mods work: internally,
the `Initialize()` method is called by a detour.

One thing you must keep in mind is that you can only detour a method if you know its *address*, which is where the function is located inside *SporeApp.exe*.
You can get the address of a method by using `GetAddress(class, function)`; if it gives you an error, then you cannot detour that function.

How detouring is done depends on two things:
 - Is the function `static`?
 - If it's not static, is it `virtual`?
 
@note Functions inside namespaces are also considered static, as they don't belong to a class.

If the function is static, you must use `static_detour`; if it's not static, you must use `virtual_detour` if it's virtual or `member_detour` if it's not.
In order to do a detour, you must know the function *declaration*: the return type and the parameter types. For example, for `float myfunc(int a)` the declaration
is `float(int)`; for `void myfunc(const Vector3&, int)` it's `void(const Vector3&, int)`. When you are creating a detour, you are actually creating a class, so 
you must give it a name.

 - `static_detour(name, declaration)`
 - `member_detour(name, className, declaration)`: `className` is the name of the class that defines the function. For example, to detour 
 Simulator::cCreatureBase::PlayAnimation() you have to use `Simulator::cCreatureBase`.
 - `virtual_detour(name, className, virtualClass, declaration)`: `virtualClass` is the name of the base class that first defined the function,
 whereas `className` is the name of the class that implements it and you are detouring. For example: UTFWin::Window::SetDrawable(), `className` would be
 `UTFWin::Window` (because that's the implementation we want to detour) but `virtualClass` will be `UTFWin::IWindow`, since that's where `SetDrawable()` was declared.
 
After that, you open the "class" with `{ };` and inside you declare the function with the same return type and parameters, and name `detoured`. For example,
to edtour Graphics::Renderer::SetModelMatrix():

```cpp
// SetModelMatrix__detour will be the name of the detour class
static_detour(SetModelMatrix__detour, void()) {
	void detoured(D3DMATRIX* value)  {

	}
};
```

@note Like with classes, don't forget the semicolon `;` after the `}`

@subsection Detouring-Original Calling the original function

Inside the detoured function you can call `original_function()` to call the original implementation. If the detoured function is not static, you will
also have to pass as the first parameter the object you want to call the function on (usually `this`).

```
static_detour(SetModelMatrix__detour, void()) {
	void detoured(D3DMATRIX* value)  {
		original_function(value);
	}
};

member_detour(PaletteLoad__detour, Palettes::PaletteUI, 
	void(Palettes::PaletteMain*, UTFWin::IWindow*, bool, void*)) 
{
	void detoured(Palettes::PaletteMain* pPalette, UTFWin::IWindow* pWindow, 
					bool arg3, void* arg4) 
	{
		// Just call the original on this object
		original_function(this, pPalette, pWindow, arg3, arg4);
	}	  
};
```

@subsection Detouring-Applying Applying the detour

Once you have the detour class, you have to tell the %ModAPI what method (or more exactly, what address) you are going to redirect. You do that in the
`AttachDetours()` method of `dllmain.cpp`, by calling the static function `attach()` of the detour class. You have to pass it the address, which you can 
get with `GetAddress()` as explained before.

```cpp
void AttachDetours()
{
    SetModelMatrix__detour::attach(GetAddress(Graphics::Renderer, SetModelMatrix));
	
	PaletteLoad__detour::attach(GetAddress(Palettes::PaletteUI, Load));
}
```

@section Detouring-Examples Examples

@subsection Detouring-Examples-1 Example 1: Removing the hologram

App::cViewer::SetRenderType() decides what kind of rendering is done. We don't know what most values do, except for two: `0` is the "standard" rendering,
and `15` is the rendering used by the *hologram scout*. If we detour that function so that every time Spore tries to use rendering mode 15 we use 0 instead,
the hologram scout will look like a normal creature instead of an hologram.

As you can see in the declaration, it returns void and gets an integer and a bool parameter, so the declaration will be like `void(int, bool)`. It is not
static and it is not virtual, so we need to use `member_detour`.

```cpp
member_detour(SetRenderType__detour, App::cViewer, void(int, bool)) {
	void detoured(int renderType, bool arg2) {
		if (renderType == 15) renderType = 0;
		original_function(this, renderType, arg2);
	}
};

void AttachDetours()
{
    SetRenderType__detour::attach(GetAddress(cViewer, SetRenderType));
}
```


