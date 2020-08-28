#include "stdafx.h"
#include "PackageCheat.h"

PackageCheat::PackageCheat()
{
}


PackageCheat::~PackageCheat()
{
}

void PrintPackages() {
	Resource::IResourceManager::DBPFList packages;
	int count = ResourceManager.GetAllDBPFs(packages);
	App::ConsolePrintF("----- %d packages:", count);
	for (auto dbpf : packages) {
		App::ConsolePrintF("ls", dbpf->GetPath());
	}
	App::ConsolePrintF("-----");
}

//PLACEHOLDER TODO
bool ParseKey(string name, ResourceKey& dst) {
	auto dotIndex = name.find('.');
	if (dotIndex != string::npos) {
		dst.typeID = ResourceManager.GetTypeID(string16(string16::CtorConvert(), name.substr(dotIndex + 1)).c_str());
		
	} else {
		dotIndex = name.size();
	}
	string split = name.substr(0, dotIndex);

	return true;
}

void PackageCheat::ParseLine(const ArgScript::Line& line)
{
	if (auto args = line.GetOption("file", 1)) {
		if (line.HasFlag("list")) PrintPackages();

		ResourceKey name;
		if (!ResourceKey::Parse(name, string16(string16::CtorConvert(), args[0]).c_str())) {
			App::ConsolePrintF("Incorrect file name");
			return;
		}
		auto dbpf = ResourceManager.GetDBPF(name);
		if (dbpf) {
			App::ConsolePrintF("File found in: %ls", dbpf->GetPath());
		}
		else {
			App::ConsolePrintF("File not found.");
		}
	} 
	else {
		PrintPackages();
	}
}

const char* PackageCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Prints all .package files. Using -file, you can check the package where a certain file is stored.";
}
