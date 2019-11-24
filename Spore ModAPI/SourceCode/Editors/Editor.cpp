#ifndef MODAPI_DLL_EXPORT
#include <Spore\Editors\Editor.h>
#include <Spore\Editors\EditorModel.h>

namespace Editors
{
	auto_METHOD(Editor, bool, sub_581F70, Args(EditorRigblock* part, void* activeHandle, int value), Args(part, activeHandle, value));

	auto_METHOD_const_(EditorModel, string16&, GetCreationName);
	auto_METHOD_VOID(EditorModel, SetColor, Args(int index, struct ColorRGB color), Args(index, color));
}
#endif
