The `GmdlExport` mod adds a new cheat that extracts the GMDL model and textures of Spore creations (creatures, buildings, vehicles, flora).
You can see it in action [in the tutorial](https://github.com/emd4600/SporeModder-FX/wiki/How-to-import-creations-into-Blender).

The implementation of the mod is very simple. It just requires a cheat, `GmdlExportCheat.h`/`.cpp`. This cheat also inherits from
`Sporepedia::IShopperListener`, [to show the Sporepedia](http://davoonline.com/sporemodder/emd4600/SporeModAPI/_sporepedia.html).

Once the player selects a creation, it just checks if it's a valid type and if the `.gmdl` model exists.
Extracting the GMDL is easy, as you just need to copy all the contents. Check the 
[Resources & IO tutorial](http://davoonline.com/sporemodder/emd4600/SporeModAPI/_resources.html).

Extracting the textures is the complicated part. First, the mod reads the `.gmdl` file contents (ignoring most of it) until it arrives to the
material data, which contains the `ResourceKey`s of the textures the model uses, as well as their sampler indices (i.e. whether they are diffuse, normal maps,...).
The reading function is based in the [SporeModder Blender Addons implementation](https://github.com/emd4600/SporeModder-Blender-Addons/blob/master/gmdl_importer.py),
which in turn was made by reverse engineerng how Spore reads GMDL files.

Once we have the texture keys, it's not enough, as Spore saves the textures in `.raster` format. We use the `TextureManager` to load them into 
`RenderWare::Raster` objects (which is how Spore represents textures in the code); finally, we save them into a `.png` by accessing the DirectX data
and using the `D3DXSaveTextureToFile()` function; for this reason, the project must link an additional DirectX library.

Spore uses the alpha channel of the normal map to store the specular map. That is quite inconvenient to use, so we give the `normalSpec` texture special
treatment: we split it in two.