@page Models Models
@brief How to display models

Everything related to models is in the Graphics namespace.

@section Models-World Creating a model world

In Spore, models are organized in **model worlds**. A model world is not affected by models on other worlds; each model world can have multiple "lighting worlds"
which control how the moedls are illuminated.

Creating a new model world is very easy, you just need to assign it an ID. For example, if you wanted to create your own game mode, you would need
your own model world. You will also have to add it to the rendering queue.

~~~~{.cpp}
IModelWorldPtr world = ModelManager.CreateWorld(id("MyWorld"));
world->SetVisible(true);

RenderManager.AddRenderable(world->ToRenderable(), Graphics::kRenderQueueMain);
~~~~

@note On certain occasions you might want to have multiple model worlds, and decide how to render them manually. In that case, you don't need to
add the world to the render queue.

@section Models-Adding Adding new models

In order for a model to be displayed, it needs to be inside a model world. If you are modifying an existing mode (say, for example, the editors) 
you will probably have access to an exsting model world; if you don't, create one. In order to load a model you have to reference it's `.prop` file:

~~~~{.cpp}
// In this example, we use the background model world of the editor
auto world = Editor.mpBackgroundModelWorld;
ModelPtr model = world->LoadModel(id("ep1_altarreligious"), GroupIDs::CivicObjects);
world->UpdateModel(model.get());
~~~~

@section Models-Transforming Transforming models

By default, models are visible. You can change that:

~~~~{.cpp}
// 'false' -> invisible, 'true' -> visible
world->SetModelVisibility(model.get(), false);
~~~~

With what you learned before, the models will always spawn at the same position. Obviously, this is not what we want. The model class
has a method called `SetTransform()` that allows us to move, scale and rotate the model. This takes a Transform object; for more information on how
it works, check the [math tutorial](_math.html).

~~~~{.cpp}
// This set the scale of the model to 0.5 (so it will be half the original size)
// and moves it one unit up. As you can see, transformations can be concatenated
model->SetTransform(Transform().SetScale(0.5f).SetOffset(0, 0, 1.0f));
~~~~
