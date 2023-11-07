@page EnteringEditor How to enter into the editor
@brief How to use an EditorRequest to access an editor.

@tableofcontents

@section Includes Required includes

 - `<Spore\Creations.h>`
 
@section EnteringEditor_Implementation Implementation

You can access an editor by using the Editors::EditorRequest class. You must create it using `new`, and it's better if you save it in an `intrusive_ptr`.

When you create a new instance of this class, you have to set the `editorID` field to the ID of the editor you want to go to. The ID has 
to be the name of an editor configuration file in the `editor_setup~` folder, such as `CreatureEditorExtraLarge`, `BuildingHouse`, etc

There are some additional properties that control features available in the editor. Configurating them is optional:
 - `sporepediaCanSwitch`: If true, the button to enter the Sporepedia and edit another creation is enabled. By default, *false*
 - `disableNameEdit`: If true, it won't be possible to edit the name of the creation. By default, *false*
 - `allowSporepedia`: If true, the button to enter the Sporepedia will be enabled. By default, *false*
 - `hasSaveButton`: If true, there will be a button to save the creation. By default, *false*
 - `hasCreateNewButton`: If true, there will be a button to create a new creation. By default, *false*
 - `hasExitButton`: If true, there will be a button to exit the editor. By default, *false*
 - `hasPublishButton`: If true, there will be a button to publish and share the creation. By default, *false*
 - `hasCancelButton`: If true, there will be a cancel button. By default, *true*
 
One you have configured the request, you can submit it using EditorRequest::Submit(). If you are in a Simulator game mode, you should use
`GameModeManager.SubmitEditorRequest()`.

@section EnteringEditor_Examples Examples

@subsection EnteringEditor_Example1 Enter into the creature editor
~~~~{.cpp}
EditorRequestPtr request = new EditorRequest();
request->editorID = id("CreatureEditorExtraLarge");
request->allowSporepedia = true;
request->hasSaveButton = true;

EditorRequest::Submit(request.get());
~~~~