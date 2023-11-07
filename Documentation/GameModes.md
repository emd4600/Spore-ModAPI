@page GameModes Game Modes & Cameras
@brief How to create new game modes and cameras

At every moment in the game, there is one game mode active. It's a mode with its own controls, camera, and update function (a function that gets called every time).
For example, the *Editor*, the *Galaxy Game Entry*, the *Adventure Editor*,... each one is a game mode.

@section GameModes-Create Creating new game modes

Game modes implement the App::IGameMode class. The easiest way to create a new one is by using the *ModAPI Game Mode* item template. The main methods in a 
game mode are:
 - `OnEnter()`: Called when the game mode is entered. Here you should do things like loading the models, the user interface,...
 - `OnExit()`: Called when the game mode is exited. Here you should do things like unloading the models, the user interface,...
 - `Update()`: Called once every frame, this is where msot of the code goes. 
 
There are many methods that get called with user interaction: `OnMouseDown`, `OnKeyUp`, etc. If you used the item template, they have a default implementation
that just records these interactions on a `GameInput` object. You can then check what buttons are pressed or where the mouse is in the `Update()` method.

~~~~{.cpp}
void MyGameMode::Update(float delta1, float delta2)
{
	if (mInput.IsMouseDown(kMouseButtonLeft) && mInput.mouseState.IsShiftDown) {
		...
	}
}
~~~~

You can add the new game mode to the `GameModeManager` using the `AddGameMode` method. You must do it in the `Initialize()` method of `dllmain`.

~~~~{.cpp}
GameModeManager.AddGameMode(new MyGameMode(), id("MyGameMode"), "MyGameMode");
~~~~

If you want an example of a mod that adds a new game mode, check the *Effect Editor* in the [`ModCreatorKit`](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/ModCreatorKit)

@section GameModes-Active Changing the active mode

There can only be one active mode at once. When the active mode is changed, the old one is notified, so the user does not have to worry about 
the transition and whatever mode was active before. You need to know the ID of the mode to set it active, there's a list in the GameModeIDs enum.

~~~~{.cpp}
GameModeManager.SetActiveMode(id("MyGameMode"));
~~~~

@section GameModes-Camera Changing the active camera

Similar to game modes, there can only be one active camera at a time. Cameras have their own controls (mouse and keyboard). 
Cameras are defined in `.prop` files in the `camera_properties~` folder. When the game mode is activated, you should set which 
camera you want to use (otherwise, the previous one would be used): 

~~~~{.cpp}
bool MyGameMode::OnEnter()
{
    CameraManager.SetActiveCameraByID(id("EditorCameraCreatureUI"));
    ...
}
~~~~

@section GameModes-CustomCamera Creating a custom camera

The available cameras in the game might not be enough for you. If you want to control directly how the camera works 
(the mouse/keyboard input, the functionality of the camera) you must create a new camera type. Cameras implement the App::ICamera interface;
you can create a new one by using the *ModAPI Camera* item template. You will see the available methods in cameras are very similar to those
in game modes. You can then add the camera to the list of available cameras in your `Initialize()` method.

~~~~{.cpp}
CameraManager.PutCamera(0x8f645234, new MyCamera());
// Now you can set the camera as active using the 0x8f645234 ID
~~~~

It's also possible to create a generic camera type that can be used by multiple files in `camera_properties~`. This allows to create variations of the same
camera type without having to create multiple classes. In order to do that, you have to create a function, the "camera factory": the function receives 
a `.prop` file as parameter; you must create an isntance of your camera and read its properties from the prop list.

~~~~{.cpp}
App::ICamera* MyCameraFactory(App::PropertyList* propList)
{
    auto camera = new MyCamera();
	
    // You should create a 'ReadProp' method in your camera that reads the prop list
    camera->ReadProp(propList);
	
    return camera;
}
~~~~

Then, in your `Initialize()` method you can add this camera factory to the camera manager so it gets recognized:
~~~~{.cpp}
CameraManager.AddCameraType(0x00DF8567, MyCameraFactory);
~~~~

If a camera `.prop` file uses `uint32 cameraType 0x00DF8567`, it will be using your new camera.


@section GameModes-Examples Examples
@subsection GameModes-Examples-1 Example 1: Pivot camera

In this example, we will make a camera that orbits around a pivot point, controlled with the mouse. This is like the camera used in the Galaxy game entry.

First, create a new camera class using the *ModAPI Camera* template (I'll call my class `PivotCamera`). Now, open the created `.h`, since we are going
to add some members to our class. We will add them after the `GameInput mInput` variable, which is at the end of the class. I'll add the following members:
 - `Point mLastMouse`: we will use this to control how much the player has moved the mouse.
 - `float mRotateSpeed`: this will control how much the camera moves when the player moves the mouse. In the example we will never change this value,
 but you can make it variable if you want (for example, let the player control the speed with buttons)
 - `Vector3 mTarget`: where the camera is looking at. In the example, we will use the origin of coordinates (*0, 0, 0*) but you can change it (for example,
 the position of the avatar creature...)
 - `float mDistance`: how much zoom the camera has, this will be controled with the mouse wheel.
 - `float mAngleX` and `float mAngleY`: these two fields are used to orbit the camera around the target point, and will be controlled with the mouse movement. 
 These angles will be in radians. Techincally, these are the *longitude* and *latitude* angles.
 
We end up with something like this:

```cpp
protected:
	GameInput mInput;
	Point mLastMouse;
	Vector3 mTarget;
	float mRotateSpeed;
	float mDistance;
	float mAngleX;
	float mAngleY;
```

That is all we have to do in the header file, now open the `.cpp`. The first thing you must always do is initialize your class members in the constructor:

```cpp
PivotCamera::PivotCamera()
	: mInput()
	, mDistance(4.0f)
	, mLongitude(0)
	, mLatitude(0)
	, mTarget(0, 0, 0)
	, mRotateSpeed(PI)
{
}
``` 

The class has many methods, but we only need to change two of them. First, we will make the zoom functionality, in the `OnMouseWheel` method. 
The `wheelDelta` parameter tells how much the player has scrolled the mouse
wheel, and it's usually a multiple of 120; depending on this value and some factor (the "zoom speed") we will change the distance:

```cpp
bool PivotCamera::OnMouseWheel(int wheelDelta, float mouseX, float mouseY, MouseState mouseState)
{
	mInput.OnMouseWheel(wheelDelta, mouseX, mouseY, mouseState);

	mDistance -= wheelDelta / (120*3.0f);
	
	return false;
}
```

And now, let's go to the important method, where the camera logic happens, `Update()`. This method gets called every frame: the `deltaTime` parameter 
tells us how many milliseconds have passed since the last frame, and `pViewer` is the object where we have to put our camera transformations.

The first thing we will do is some configuration for the camera, setting the *near plane* and *far plane*. The near plane tells the minimum distance at 
which you can see things, and far plane is the maximum distance at which you can see things. For example, I'll set them to *0.01* and *1000*:

```cpp
pViewer->SetFarPlane(0.01f);
pViewer->SetNearPlane(1000f);
```

Now we will process the mouse input, using the `mInput` variable. We only want the camera to move if the user was pressing the left mouse button, 
so we will make an *if* with the condition `mInput.IsMouseDown(MouseButton::kMouseButtonLeft)`. Inside the if, we have to calculate how much the mouse
has moved since the last time the method was called; for that, we will use the `mLastMouse` variable.

```cpp
if (mInput.IsMouseDown(MouseButton::kMouseButtonLeft)) {
	Point deltaMouse = mInput.mousePosition - mLastMouse;
	mLastMouse = mInput.mousePosition;
}
```

Now, we will change `mAngleX` and `mAngleY` depending on the `deltaMouse` *x* and *y* coordinates. We will also divide the change with the screen size,
this way it doesn't depend on your resolution:

```cpp
mAngleX -= deltaMouse.x * mRotateSpeed / pViewer->GetViewport().Width;
mAngleY += deltaMouse.y * mRotateSpeed / pViewer->GetViewport().Height;
```

With just this code, the player would be able to "loop" the camera through the north and south polle, and we don't want that. That is why we will limit
the Y angle between *pi/2*  (90º in radians) and *-pi/2* (-90º in radians). Actually, we will limit the angle a little bit before that, because exactly at the 
poles the method that calculates the camera direction doens't work correctly. After all this, the if looks like this:

```cpp
if (mInput.IsMouseDown(MouseButton::kMouseButtonLeft)) {
	Point deltaMouse = mInput.mousePosition - mLastMouse;
	mLastMouse = mInput.mousePosition;

	mAngleX -= deltaMouse.x * mRotateSpeed / pViewer->GetViewport().Width;
	mAngleY += deltaMouse.y * mRotateSpeed / pViewer->GetViewport().Height;

	mAngleY = max(min(mAngleY, PI*0.95f / 2.0f), -PI*0.95f / 2.0f);
}
```

Now, we must calculate the position of our camera. We can do this using [spherical coordinates](https://en.wikipedia.org/wiki/Spherical_coordinate_system#Cartesian_coordinates):

```cpp
// Spherical coordinates
float colatitude = PI / 2.0f - mAngleY;
Vector3 position = {
	mDistance * cosf(mAngleX) * sinf(colatitude),
	mDistance * sinf(mAngleX) * sinf(colatitude),
	mDistance * cosf(colatitude)
};
```

Finally, we submit our camera transformations using the `SetCameraTransform()` method, which takes a [`Transform`](_math.html#Math-Transform) object. To create the correct
transformation, we will use the Matrix3::LookAt() method. 
The final `Update()` method looks like this:

```cpp
void PivotCamera::Update(int deltaTime, App::cViewer* pViewer) 
{
	pViewer->SetFarPlane(0.01f);
	pViewer->SetNearPlane(1000f);

	if (mInput.IsMouseDown(MouseButton::kMouseButtonLeft)) {
		Point deltaMouse = mInput.mousePosition - mLastMouse;
		mLastMouse = mInput.mousePosition;

		mAngleX -= deltaMouse.x * mRotateSpeed / pViewer->GetViewport().Width;
		mAngleY += deltaMouse.y * mRotateSpeed / pViewer->GetViewport().Height;

		mAngleY = max(min(mAngleY, PI*0.95f / 2.0f), -PI*0.95f / 2.0f);
	}

	// Spherical coordinates
	float colatitude = Math::PI / 2.0f - mAngleY;
	Vector3 position = {
		mDistance * cosf(mAngleX) * sinf(colatitude),
		mDistance * sinf(mAngleX) * sinf(colatitude),
		mDistance * cosf(colatitude)
	};

	pViewer->SetCameraTransform(Transform().SetOffset(position).SetRotation(Matrix3::LookAt(position, mTarget)));
}
```

Now, in order to use the camera, we have to add it in `dllmain.cpp`. First, import our file using `#include "PivotCamera.h"` at the top of your file 
(after the rest of includes). Now, before the `Initialize()` method, we will create our own method that receives a property list and returns our camera:

```cpp
App::ICamera* PivotCameraFactory(App::PropertyList* propList)
{
    auto camera = new PivotCamera();
    return camera;
}
```

The camera can be used by `.prop` files, and you can read their properties there if you need to. Now, in the initialize method, we will add it to the camera
manager, assigning it an ID:

```cpp
void Initialize() {
	CameraManager.AddCameraType(id("PivotCamera"), &PivotCameraFactory);
}
```

And with this, it's finished! You can use your camera by adding the `uint32 cameraType hash(PivotCamera)` property to a file in `camera_properties~`.