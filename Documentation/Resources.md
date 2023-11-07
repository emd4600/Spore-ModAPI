@page Resources Resources & Input/Output
@brief How to access file data from `.package` files

The main functionalities to access resources of the game is in the %Resource package. Therefore, in this tutorial, we will assume 
`using namespace Resource;` is being used to avoid typing `Resource::` all the time.

If you want to see a mod that uses the Resources module, check [the GmdlExport mod](https://github.com/emd4600/Spore-ModAPI/tree/master/Projects/Example%20Projects/GmdlExport).

@section Resources-Opening Opening a resource

To access a resource, first you need to know its ResourceKey. Once you have it, you can access the resource by using the 
`ResourceManager`:

~~~~{.cpp}
ResourceObjectPtr object;
if (ResourceManager.GetResource(key, &object)) {

}
~~~~

The real type of `object` will be a class that extends `ResourceObject`, and it depends on the file type: it could be a `PropertyList`, a `GmdlAsset`,...
The files are converted to resources by using an `IResourceFactory`; if you make your own file type, you can create a resource factory that reads it.

@section Resources-Files Getting the file data

Sometimes it's not convenient to get the processed resource: sometimes you will want to directly access the raw data, just as it's written in 
the `.package` file. The resource manager allows you to get the [Database](@ref Resource::Database) (the class that represents either a `.package` or a plain folder like `Games/Game0`) 
for a certain file. You can then open the file either for read or write access by using an `IRecord`.

~~~~{.cpp}
// Remember keys are { instance, type, group }
ResourceKey key = { id("TestFile"), TypeIDs::prop, 0x405010BB };

if (auto package = ResourceManager.GetDatabase(key))
{
    // If the file does not exist, GetDatabase returns nullptr so this code is not executed
	
    Resource::IRecord* record;
	// By default it's opened for read
    if (pDBPF->GetFile(key, &record))
    {
        // Do something with the IPFRecord
    }
}
~~~~

@section Resources-IO Using IO to read/write

If you call `record->GetStream()` on an `IPFRecord`, it will return the underlying IO::IStream object that can be used to read/write from the file.
That class can be used to read/write batches of bytes directly. The IO namespace provides other methods to read/write specific types of data,
such as IO::ReadInt32(), IO::ReadLine(), IO::WriteUInt16,...

@subsection Resources-IO-Disk Accessing a disk file

It's also possible to read/write a file directly from the user disk. Instead of usnig an `IPFRecord`, you can create
a `FileStream` directly. After creating it, you must call `Open()` with the permissions you need. After you are done, don't forget to call `Close()`:

~~~~{.cpp}
FileStreamPtr stream = new IO::FileStream(u"C:\\Users\\Eric\\Desktop\\test.raw");
stream->Open(IO::kAccessFlagReadWrite, IO::kCDCreateAlways);

for (int i = 0; i < 14; ++i) {
	IO::WriteInt32(stream, &i);
}

stream->Close();
~~~~

Another useful stream class is `MemoryStream`, which keeps the file data entirely in memory.
