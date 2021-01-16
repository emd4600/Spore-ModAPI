#include "stdafx.h"
#include "MyCheat.h"

MyCheat::MyCheat()
{
}


MyCheat::~MyCheat()
{
}


void MyCheat::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* MyCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "MyCheat: Elaborate description of what this cheat does.";
	}
}
