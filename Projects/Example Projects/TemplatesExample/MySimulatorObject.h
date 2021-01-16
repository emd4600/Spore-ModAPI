#pragma once

#include <Spore\BasicIncludes.h>

#define MySimulatorObjectPtr intrusive_ptr<MySimulatorObject>

///
/// In your dllmain Initialize method, add the factory like this:
/// ClassManager.AddFactory(new MySimulatorObjectFactory());
///
/// Then you will be able to create instances of this class by doing:
/// auto obj = simulator_new<MySimulatorObject>();

class MySimulatorObject
	: public Simulator::cGameData
{
public:
	static const uint32_t TYPE = id("TemplatesExample::MySimulatorObject");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	uint32_t GetCastID() const override;
	uint32_t GetNounID() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;

	//
	// You can add more methods here
	//

	static Simulator::Attribute ATTRIBUTES[];

private:
	//
	// You can add members here
	//
};

class MySimulatorObjectFactory
	: public App::ISPClassFactory
{
public:
	size_t GetTypes(uint32_t* pDstTypes, size_t count) const override;
	Object* Create(uint32_t type, ICoreAllocator* pAllocator) override;
	const char* GetName(uint32_t type) const override;
};

