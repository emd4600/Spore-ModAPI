#pragma once

#include <Spore\BasicIncludes.h>

#define MySystemPtr intrusive_ptr<MySystem>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new MySystem(), MySystem::NOUN_ID);
///

class MySystem
	: public Simulator::cStrategy
{
public:
	static const uint32_t TYPE = id("TemplatesExample::MySystem");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	bool WriteToXML(Simulator::XmlSerializer*) override;
	void Update(int deltaTime, int deltaGameTime) override;

	//
	// You can add more methods here
	//

	static Simulator::Attribute ATTRIBUTES[];

private:
	//
	// You can add members here
	//
};