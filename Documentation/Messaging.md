@page Messaging Messaging
@brief The messaging system is used to communicate different parts of the code

Spore implements a messaging system that is used to communicate between different parts of the code. There are two main concepts: **messages** and **listeners**.
A listener is a class that wants to react to a particular message. And messages are events, small pieces of information that are used to notify that something happened.

Why is this useful? Well, it can be used to correctly componentize code. For example, imagine you change your creature color. The %UI developer does not need to know
what the game should do when changing the color (play a sound? generate a texture? animate the creature?); instead, it just sends a message, something like "hey,
the play changed the color from this to this". Then, all the classes that have to react to such change (the editor, the creature baker,...) are listening to
that message, and will do whatever they need to do.

@section Messaging-Listeners Registering a listener

Listeners are classes that implement App::IMessageListener. You can use the *"ModAPI Message Listener"* item template to create a basic `IMessageListener` class.
As an example, we will directly extend `DefaultMessageListener`:

~~~~{.cpp}
class MyListener
	: public App::DefaultMessageListener
{
public:
	bool HandleMessage(uint32_t messageID, void* message) override;
};
~~~~

@note If your class implements more classes, using `DefaultMessageListener` might require you to provide extra implementation for `AddRef()` and `Release()`

The `HandleMessage()` method gets called whenever a message we are listening to is generated. `messageID` is the ID of that message (useful if our class is
listening to more than one) and `message` is extra information, which is optional and depends on the message itself. The return value is not used.

~~~~{.cpp}
bool MyListener::HandleMessage(uint32_t messageID, void* message) {
	if (messageID == App::OnModeEnterMessage::ID) 
	{
		// We can do this because we know this message type uses this as message data
		auto data = (App::OnModeEnterMessage*)message;
		
		App::ConsolePrintF("Entered mode with id 0x%x", data->GetModeID());
	}
	return false;
}
~~~~

Now you have to register the listener to that message ID. You can do it inside the `Initialize()` method of `dllmain`:
~~~~{.cpp}
MessageManager.AddListener(new MyListener(), App::OnModeEnterMessage::ID);
~~~~

Another example: a listener that prints to the console every time the player changes the creation color in the editor.
Download [dllmain.cpp here](messaging_example_1.cpp);

@section Messaging-Sending Sending a message

When a message is sent, all the listeners registered to that ID will be notified. Sending a message is very simple, 
you just have to use the [PostMSG()](@ref App::IMessageManager::PostMSG()) method: 

~~~~{.cpp}
// Send a message with id "MyMessageID" and 4.5 as data;
float r = 4.5f;
MessageManager.PostMSG(id("MyMessageID"), &r);
~~~~