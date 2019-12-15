#pragma once

#include <Spore\Cheats.h>
#include <Spore\Creations.h>

// Our cheat class also extends IShopperListener so it can react when the user selects the creation in the Sporepedia
class GmdlExportCheat
	: public ArgScript::ICommand
	, public Sporepedia::IShopperListener
{
public:
	GmdlExportCheat();
	~GmdlExportCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

	// Overrided from IShopperListener. This will get called when the user selects a creation in the Sporepedia.
	void OnShopperAccept(const ResourceKey& selection) override;
	
	// Call this in the dllmain Initialize function.
	static void AddCheat();
};

