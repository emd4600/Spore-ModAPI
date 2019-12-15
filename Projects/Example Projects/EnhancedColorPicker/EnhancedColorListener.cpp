#include "stdafx.h"
#include "EnhancedColorListener.h"
#include <Spore\Editors\EditorMessages.h>

EnhancedColorListener::EnhancedColorListener(Object* colorChooser)
	: mpColorChooser(colorChooser)
{
}


EnhancedColorListener::~EnhancedColorListener()
{
}

bool EnhancedColorListener::HandleMessage(uint32_t messageID, void* message)
{
	if (messageID != Editors::ColorChangedMessage::ID) return false;

	auto& msg = *(Editors::ColorChangedMessage*)message;
	if (msg.GetColorChooserObject() != mpColorChooser.get()) return false;

	if (Editor.field_150 &&
		CALL(Address(ModAPI::ChooseAddress(0x4C4280, 0x4C4A50)), void*, Args(Object*, int), Args(Editor.field_150.get(), 1)) &&
		Editor.mpEditorModel)
	{
		int index = msg.GetRegionFilter();
		if (index == -1) {
			index = 0;
		}
		if (index >= 0 && index < 2)
		{
			Editor.mpEditorModel->SetColor(index, ColorRGB(msg.GetColor()));
			Editor.field_4B2 = true;

			// sub_4C4AA0
			CALL(Address(ModAPI::ChooseAddress(0x4C4AA0, 0x4C5270)), void,
				Args(Object*, Editors::EditorModel*),
				Args(Editor.field_150.get(), Editor.mpEditorModel));
		}
	}

	return true;
}