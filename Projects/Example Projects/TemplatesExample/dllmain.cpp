// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "MyCamera.h"
#include "MyCheat.h"
#include "MyGameMode.h"
#include "MyListener.h"
#include "MyObject.h"
#include "MyRenderable.h"
#include "MySimulatorObject.h"
#include "MySystem.h"
#include "MyWinProc.h"

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials

	// Here I'll show you how every thing is added. 
	// Keep in mind this is just an example, real applications might require to do it different.

	// This adds the camera to the camera system, but it doesn't change the current camera.
	// To actually use the camera, you have would have to use CameraManager.SetActiveCameraByID(id("MyCamera"))
	CameraManager.PutCamera(id("MyCamera"), new MyCamera(), u"MyCamera");

	// You can call this in the console typing 'mycheat'
	CheatManager.AddCheat("mycheat", new MyCheat());

	// This tells the game this game mode exists, but there is no way to enter it by default.
	// You can enter the game mode using GameModeManager.SetActiveMode(id("MyGameMode"))
	GameModeManager.AddGameMode(new MyGameMode(), id("MyGameMode"), "MyGameMode");

	// Adds the listener to react to the kMsgOnModeEnter message. This means the listener code will be called when 
	// the player changes the game mode
	MessageManager.AddListener(new MyListener(),  App::kMsgOnModeEnter);

	// The render system works with layers, each layer has a renderable assigned.
	// If you add the renderable to an already used layer, the previous one will disappear
	RenderManager.AddRenderable(new MyRenderable(), 38);

	// This allows you to create instances of the custom simulator object
	// WARNING: Games that contain a custom simulator object will require the mod to work, otherwise the game will crash on that save
	// Use it on your own risk.
	//
	// To create an instance of the object itself, you can do 
	// auto obj = simulator_new<MySimulatorObject>();
	ClassManager.AddFactory(new MySimulatorObjectFactory());

	// The system code will be executed when you are on a Simulator game mode (e.g. Creature stage, SPace stage, adventures,...)
	ModAPI::AddSimulatorStrategy(new MySystem(), MySystem::NOUN_ID);

	// Now the win proc will receive events on the main user interface
	// Usually you add win procs to the specific window you are interested (for example, to a button, to an editor panel,...)
	WindowManager.GetMainWindow()->AddWinProc(new MyWinProc());
}

void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

