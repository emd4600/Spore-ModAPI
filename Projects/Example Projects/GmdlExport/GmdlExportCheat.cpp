#include "stdafx.h"
#include "GmdlExportCheat.h"

#include <d3dx9tex.h>

GmdlExportCheat::GmdlExportCheat()
{
}


GmdlExportCheat::~GmdlExportCheat()
{
}

// The initialization function that adds the cheat to the game.
void GmdlExportCheat::AddCheat() {
	CheatManager.AddCheat("gmdlExport", new GmdlExportCheat());
}


void GmdlExportCheat::ParseLine(const ArgScript::Line& line)
{
	// When the command is executed, we just have to show the Sporepedia
	// We want the Sporepedia to notify this class when the user chooses the creation
	Sporepedia::ShopperRequest request(this);
	Sporepedia::ShopperRequest::Show(request);
}

const char* GmdlExportCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Exports the model and textures of a creation so you can use it in Blender.";
	}
	else {
		return "Exports the model and textures of a creation so you can use it in Blender.\n"
			"The creation files will be saved in the creation type folder inside 'My Documents\\My Spore Creations'.\n"
			"The textures are exported in TGA format. You can import the creation by using the SporeModder Blender Addons:\n"
			"https://github.com/emd4600/SporeModder-Blender-Addons#features \n"
			"\n"
			"You can execute this command from anywhere; when executed, the Sporepedia will be shown to select the creation.\n"
			"The creation needs to be baked, so you have to preview it in the Sporepedia before exporting it.\n"
			"\n"
			"Only Cells, Creatures, Plants, Buildings, Vehicles & UFOs can be exported."
			"\n"
			"When exported, the following files might be generated (instead of 'creation', the creation name):\n"
			" - creation.gmdl: The model itself, use the Blender addons to import it.\n"
			" - creation__diffuse.gmdl: The main texture, which has the color of the creation.\n"
			" - creation__normal.gmdl: A normal map, which is used to create little details.\n"
			" - creation__specular.gmdl: Specular map, which defines how light affects the creation.\n"
			" - creation__colorMap.gmdl: Only for buildings, vehicles and UFOs, its usage is unknown.\n";
	}
}

// We process the GMDL file to find the IDs of the textures
// There's more information about the GMDL format in https://github.com/emd4600/SporeModder-Blender-Addons/blob/master/gmdl_importer.py
void GetTextureNames(IO::IStream* stream, map<int, ResourceKey>& textures)
{
	int version, count, meshCount;
	IO::ReadInt32(stream, &version, 1, IO::kEndianLittle);
	IO::ReadInt32(stream, &count, 1, IO::kEndianBig);
	stream->SetPosition(count * 12, IO::kPositionTypeCurrent);

	IO::ReadInt32(stream, &meshCount, 1, IO::kEndianLittle);

	stream->SetPosition(28, IO::kPositionTypeCurrent);

	IO::ReadInt32(stream, &count, 1, IO::kEndianLittle);
	for (int i = 0; i < count; ++i)
	{  // TriangleBuffer
		stream->SetPosition(12, IO::kPositionTypeCurrent);
		int bufferSize;
		IO::ReadInt32(stream, &bufferSize, 1, IO::kEndianLittle);
		stream->SetPosition(bufferSize, IO::kPositionTypeCurrent);
	}

	IO::ReadInt32(stream, &count, 1, IO::kEndianLittle);
	for (int i = 0; i < count; ++i)
	{  // VertexFormat
		int elementCount;
		IO::ReadInt32(stream, &elementCount, 1, IO::kEndianLittle);
		stream->SetPosition(12 * elementCount, IO::kPositionTypeCurrent);
	}

	IO::ReadInt32(stream, &count, 1, IO::kEndianLittle);
	for (int i = 0; i < count; ++i)
	{  // VertexBuffer
		stream->SetPosition(8, IO::kPositionTypeCurrent);
		int bufferSize;
		IO::ReadInt32(stream, &bufferSize, 1, IO::kEndianLittle);
		stream->SetPosition(bufferSize, IO::kPositionTypeCurrent);
	}

	stream->SetPosition(meshCount * 12, IO::kPositionTypeCurrent);
	int pos = stream->GetPosition();

	IO::ReadInt32(stream, &count, 1, IO::kEndianLittle);
	if (count != 0) {
		App::ConsolePrintF("Warning: Special model, cannot extract textures.");
	}

	IO::ReadInt32(stream, &count, 1, IO::kEndianLittle);
	for (int i = 0; i < count; ++i)
	{  // Materials
		int flags;
		IO::ReadInt32(stream, &flags, 1, IO::kEndianBig);
		if (flags == 0) continue;

		int dataCount;
		IO::ReadInt32(stream, &dataCount, 1, IO::kEndianLittle);
		for (int j = 0; j < dataCount; ++j) {
			int shData;
			IO::ReadInt32(stream, &shData, 1, IO::kEndianLittle);

			if (shData == 0x20D) {
				int textureCount, samplerIndex;
				IO::ReadInt32(stream, &textureCount, 1, IO::kEndianLittle);
				for (int t = 0; t < textureCount; ++t) 
				{
					IO::ReadInt32(stream, &samplerIndex, 1, IO::kEndianLittle);
					stream->SetPosition(12, IO::kPositionTypeCurrent);

					ResourceKey textureName;
					textureName.typeID = TypeIDs::raster;
					IO::ReadUInt32(stream, &textureName.instanceID, 1, IO::kEndianLittle);
					IO::ReadUInt32(stream, &textureName.groupID, 1, IO::kEndianLittle);
					textures[samplerIndex] = textureName;
				}
			}
			else {
				stream->SetPosition(Graphics::Renderer::GetShaderDataSize(shData), IO::kPositionTypeCurrent);
			}
		}
	}
}

void GmdlExportCheat::OnShopperAccept(const ResourceKey& selection)
{
	// Ensure we can export this type of creation, and then get the My Spore Creations folder.
	string16 creationFolder;
	auto type = selection.typeID;
	if ((type != TypeIDs::cll && type != TypeIDs::crt && type != TypeIDs::bld && type != TypeIDs::vcl && 
		type != TypeIDs::ufo && type != TypeIDs::flr) ||
		!App::Thumbnail_cImportExport::Get()->GetFolderPath(type, creationFolder)) 
	{
		App::ConsolePrintF("Error: Only cells, creatures, buildings, vehicles, UFOs and plants can be exported.");
		return;
	}

	// Get the .prop file that defines the creation
	App::PropertyList::Pointer propList;
	if (!PropManager.GetPropertyList(selection.instanceID, selection.groupID, propList))
	{
		App::ConsolePrintF("Error: The creation is not baked. Preview it in the Sporepedia before exporting it.");
		return;
	}

	// The property 'modelMeshLOD0' (0x00F9EFBB) contains the key to the high-res GMDL file
	ResourceKey gmdlName;
	App::Property::GetKey(propList.get(), 0x00F9EFBB, gmdlName);

	// Now we need to get the .gmdl
	// To get the raw contents of a file, first we need to get the .package and then the file
	Resource::IPFRecord* pRecord;
	auto dbpf = ResourceManager.GetDBPF(gmdlName);
	if (!dbpf || !dbpf->GetFile(gmdlName, &pRecord)) {
		App::ConsolePrintF("Error: The creation is not baked. Preview it in the Sporepedia before exporting it.");
		return;
	}

	// Get the creation name
	auto metadata = Pollinator::GetMetadata(selection.instanceID, selection.groupID);
	if (!metadata) {
		App::ConsolePrintF("Error: Could not get creation name.");
		return;
	}
	string16 creationName = metadata->GetName();
	
	// The GMDL file contains the keys of the textures it uses.
	// We'll find the texture name and the sampler index, as that tells us what it is for (e.g. diffuse, normal,...)
	map<int, ResourceKey> textureIDs;
	GetTextureNames(pRecord->GetStream(), textureIDs);

	// Read the raw contents of the GMDL and save them to a file
	pRecord->GetStream()->SetPosition(0);
	auto size = pRecord->GetStream()->GetSize();
	char* buffer = new char[size];
	pRecord->GetStream()->Read(buffer, size);
	pRecord->Close();

	string16 path;
	path.sprintf(u"%ls%ls.gmdl", creationFolder.c_str(), creationName.c_str());
	intrusive_ptr<IO::FileStream> outputStream = new IO::FileStream(path.c_str());
	outputStream->Open(IO::kAccessFlagReadWrite, IO::kCDCreateAlways);
	outputStream->Write(buffer, size);
	outputStream->Close();
	delete[] buffer;

	// Now, extract the textures
	// Spore sues the .raster format, so we wil use DirectX to convert them to .tga
	for (auto textureID : textureIDs) {
		auto texture = TextureManager.GetTexture(textureID.second, Graphics::ITextureManager::kForceLoad);
		auto raster = texture->GetRaster();
		string16 textureEnding;
		bool splitNSpec = false;

		// Use the sampler index to know the type of texture we are dealing with
		if (type == TypeIDs::cll || type == TypeIDs::crt || type == TypeIDs::flr) {
			if (textureID.first == 0) textureEnding = u"__diffuse";
			else {
				textureEnding = u"__normal";
				splitNSpec = true;
			}
		}
		else if (type == TypeIDs::vcl || type == TypeIDs::bld) {
			if (textureID.first == 0) textureEnding = u"__diffuse";
			else if (textureID.first == 1) textureEnding = u"__colorMap";
			else {
				textureEnding = u"__normal";
				splitNSpec = true;
			}
		}
		else {
			textureEnding.sprintf(u"__%d", textureID.first);
		}

		path.sprintf(u"%ls%ls%ls.tga", creationFolder.c_str(), creationName.c_str(), textureEnding.c_str());
		D3DXSaveTextureToFile((wchar_t*)path.c_str(), D3DXIMAGE_FILEFORMAT::D3DXIFF_TGA, raster->pTexture, nullptr);
			
		// Spore saves the specular map as the alpha channel of the normal map, we want to separate it
		// The following is pure DirectX, we create another texture and write the alpha channel of the normal map into it.
		if (splitNSpec) {
			D3DLOCKED_RECT sourceLockedRect, dstLockedRect;
			raster->pTexture->LockRect(0, &sourceLockedRect, NULL, 0);
				
			IDirect3DTexture9* specTexture;
			if (Graphics::Renderer::GetDevice()->CreateTexture(raster->width, raster->height, 1, 0,
				D3DFORMAT::D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &specTexture, NULL) != D3D_OK)
			{
				App::ConsolePrintF("Warning: The specular texture could not be separated.");
				return;
			}
			specTexture->LockRect(0, &dstLockedRect, NULL, 0);

			for (int i = 0; i < raster->width; ++i) {
				for (int j = 0; j < raster->height; ++j) {
					int alpha = ((unsigned int*)sourceLockedRect.pBits)[j* raster->width + i] >> 24;
					((unsigned int*)dstLockedRect.pBits)[j * raster->width + i] = 0xFF000000 | alpha << 16 | alpha << 8 | alpha;
				}
			}

			raster->pTexture->UnlockRect(0);
			specTexture->UnlockRect(0);

			path.sprintf(u"%ls%ls__specular.tga", creationFolder.c_str(), creationName.c_str(), textureEnding.c_str());
			D3DXSaveTextureToFile((wchar_t*)path.c_str(), D3DXIMAGE_FILEFORMAT::D3DXIFF_TGA, specTexture, nullptr);
		}
	}

	// Done, everything completed successfully!
	App::ConsolePrintF("Successfully exported to %ls%ls.gmdl", creationFolder.c_str(), creationName.c_str());
}
