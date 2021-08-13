// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

class SpaceToolCheat
	: public ArgScript::ICommand
{
public:
	// We add a constructor to initialize the maps
	SpaceToolCheat() 
		: mNamesMap()
		, mDescriptionsMap()
	{
	}

	void ParseLine(const ArgScript::Line& line) override {
		// First, ensure we are in space stage
		if (!Simulator::IsSpaceGame()) {
			App::ConsolePrintF("You must be on Space Stage to use this cheat.");
			return;
		}

		// We initialize the names and descriptions of the tools, only once
		if (mNamesMap.empty()) {
			vector<ResourceKey> keys;
			// This gives us the keys of all the files in the spacetools~ folder.
			ResourceManager.GetFileKeys(keys, &StandardFileFilter(ResourceKey::kWildcardID, GroupIDs::SpaceTools, ResourceKey::kWildcardID));

			for (auto& key : keys) {
				cSpaceToolDataPtr tool;
				if (ToolManager.LoadTool(key, tool)) {
					// There are some tools that are not for players. Those don't have description.
					// So we check that the files define spaceToolDescription and spaceToolDetailDescription properties
					// Also, ensure it has spaceToolPanelKey, which is only there for player tools
					if (tool->mpPropList->HasProperty(0x3068D95D) && 
						tool->mpPropList->HasProperty(0x04CAD19B) &&
						tool->mpPropList->HasProperty(0xA6A37FC4))
					{
						mNamesMap[key.instanceID] = tool->mDescription.GetText();
						mDescriptionsMap[key.instanceID] = tool->mDetailDescription.GetText();
					}
				}
			}
		}

		size_t numArgs;
		auto args = line.GetArgumentsRange(&numArgs, 0, 2);

		if (numArgs == 0) {
			for (auto& entry : mNamesMap) {
				App::ConsolePrintF("\"%ls\": %ls", entry.second.c_str(), mDescriptionsMap[entry.first].c_str());
			}
			return;
		}

		// string16::CtorConvert() is used to convert an 8-bit string (args) to a string16
		string16 searchText = string16(string16::CtorConvert(), args[0]); 

		vector<uint32_t> results;

		// Search in the names
		for (auto& entry : mNamesMap) {
			if (containsCaseInsensitive(entry.second, searchText)) {
				results.push_back(entry.first);
			}
		}
		// Search in the descriptions
		for (auto& entry : mDescriptionsMap) {
			if (containsCaseInsensitive(entry.second, searchText)) {
				results.push_back(entry.first);
			}
		}

		if (results.size() > 1) {
			if (line.HasFlag("all")) {
				// We must add all the results to the player inventory
				int ammo = 1;
				if (numArgs == 2) {
					ammo = mpFormatParser->ParseInt(args[1]);
				}
				App::ConsolePrintF("Added %d units of the following tools:", ammo);
				for (auto toolID : results) {
					cSpaceToolDataPtr tool;
					if (ToolManager.LoadTool(ResourceKey(toolID, TypeIDs::prop, GroupIDs::SpaceTools), tool)) {
						tool->mCurrentAmmoCount = ammo;
						SimulatorSpaceGame.GetPlayerInventory()->AddItem(tool.get());
						App::ConsolePrintF("\"%ls\": %ls", mNamesMap[toolID].c_str(), mDescriptionsMap[toolID].c_str());
					}
				}
			}
			else {
				// Inconclusive search, show all the results
				App::ConsolePrintF("There was more than one result; please choose one of these tools, or search again with '-all' to get all of them.");
				for (auto toolID : results) {
					App::ConsolePrintF("\"%ls\": %ls", mNamesMap[toolID].c_str(), mDescriptionsMap[toolID].c_str());
				}
			}
		}
		else if (results.size() == 1) {
			// Just add the single result of the search
			cSpaceToolDataPtr tool;
			if (ToolManager.LoadTool(ResourceKey(results[0], TypeIDs::prop, GroupIDs::SpaceTools), tool)) {
				int ammo = 1;
				if (numArgs == 2) {
					ammo = mpFormatParser->ParseInt(args[1]);
					tool->mCurrentAmmoCount = ammo;
				}
				SimulatorSpaceGame.GetPlayerInventory()->AddItem(tool.get());
				App::ConsolePrintF("Added %d units of \"%ls\".", ammo, mNamesMap[results[0]].c_str());
			}
		}
		else {
			App::ConsolePrintF("No tool matches the given text. Try searching something else.");
		}
	}

	const char* GetDescription(ArgScript::DescriptionMode mode) const override {
		if (mode == ArgScript::DescriptionMode::Basic) {
			return "Adds a space tool to your spaceship.";
		}
		else {
			return "addspacetool \"<text>\" (<ammo>)\n" 
				"Adds a space tool to your spaceship.\n"
				"'text' is used to search among the tools names and descriptions;\n"
				"If only one is found, it is added; if more than one is found, it shows you all of them so you can choose.\n"
				"When there is more than one result, you can add all of them with '-all'. For example:\n"
				"   addspacetool \"atmosphere\" -all\n"
				"adds all the tools related with the atmosphere.\n"
				"The second parameter is optional, it sets a specific amount of ammo.\n"
				"Invoke it with no parameters (just 'addspacetool') to see a list of all available tools.";
		}
	}

private:
	// We save the names of the tools here, we will only load them once
	// Associates a space tool id to its name
	map<uint32_t, string16> mNamesMap;
	map<uint32_t, string16> mDescriptionsMap;

	// Returns true if 'container' contains 'contained', case insensitive
	static bool containsCaseInsensitive(const string16& container, const string16& contained) {
		auto searchResult = eastl::search(container.begin(), container.end(), contained.begin(), contained.end(),
			[](char16_t a, char16_t b) {
			return eastl::CharToUpper(a) == eastl::CharToUpper(b);
		});
		return searchResult != container.end();
	}	
};

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials

	CheatManager.AddCheat("addspacetool", new SpaceToolCheat());
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

