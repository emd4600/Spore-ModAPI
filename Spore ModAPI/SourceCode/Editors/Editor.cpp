#ifndef MODAPI_DLL_EXPORT
#include <Spore\Editors\Editor.h>
#include <Spore\Editors\EditorModel.h>
#include <Spore\Editors\TuningSpine.h>

namespace Editors
{
	auto_METHOD(cEditor, bool, sub_581F70, Args(EditorRigblock* part, void* activeHandle, int value), Args(part, activeHandle, value));

	auto_METHOD_VOID(cEditor, SetEditorModel, Args(EditorModel* pEditorModel), Args(pEditorModel));
	auto_METHOD_VOID(cEditor, CommitEditHistory, Args(bool p, EditorStateEditHistory* pStateHistory), Args(p, pStateHistory));
	auto_METHOD_VOID(cEditor, Undo, Args(bool a, bool b), Args(a, b));
	auto_METHOD_VOID_(cEditor, Redo);

	auto_METHOD_VOID_(EditorModel, Dispose);
	auto_METHOD_const_(EditorModel, eastl::string16&, GetCreationName);
	auto_METHOD_VOID(EditorModel, SetColor, Args(int index, struct ColorRGB color), Args(index, color));
	auto_METHOD_VOID(EditorModel, Load, Args(cEditorResource* pResource), Args(pResource));
	auto_METHOD_VOID(EditorModel, Save, Args(cEditorResource* pResource), Args(pResource));

	auto_STATIC_METHOD_(cTuningSpine, cTuningSpine*, Get);


	int IEditorLimits::AddRef() {
		++mnRefCount;
		return mnRefCount;
	}

	int IEditorLimits::Release() {
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}


	auto_METHOD_VIRTUAL_VOID(EditorModel, INameableEntity, SetName, Args(const char16_t* pString), Args(pString));
	auto_METHOD_VIRTUAL_VOID(EditorModel, INameableEntity, SetDescription, Args(const char16_t* pString), Args(pString));

	const char16_t* EditorModel::GetName() {
		return mName.c_str();
	}

	const char16_t* EditorModel::GetDescription() {
		return mDescription.c_str();
	}

	void EditorModel::SetTags(const char16_t* pString) {}
	const char16_t* EditorModel::GetTags() { return nullptr; }

	EditorModel::EditorModel()
		: mnRefCount(0)
		, mKey()
		, mParts()
		, field_2C()
		, field_30()
		, field_34()
		, field_38()
		, field_3C()
		, field_40(-2.0f)
		, field_44(2.0f)
		, field_48()
		, field_4C()
		, field_4D()
		, field_4E(true)
		, field_4F()
		, field_50()
		, field_51()
		, mTranslationOptions()
		, mModelType()
		, mName()
		, mDescription()
		, mAcceptedName()
		, mSkinEffectIDs()
		, mSkinEffectSeeds{1234, 1234, 1234}
		, mColors {ColorRGB(1.0f, 1.0f, 1.0f), ColorRGB(1.0f, 1.0f, 1.0f), ColorRGB(1.0f, 1.0f, 1.0f)}
		, field_C8()
	{
	}

	EditorModel::~EditorModel()
	{
		Dispose();

		// field_30 is a pointer, but I don't know what kind so we manually Release it
		if (field_30 != 0) {
			int* pointer = (int*)field_30;
			pointer[1]--;
			if (pointer[1] == 0) {
				pointer[1] = 1;
				delete ((IVirtual*)pointer);
			}
		}
	}

	cEditorResource::cEditorResource()
		: mBlocks()
		, mProperties {}
		, padding_5C {}
	{
	}

	cEditorResource::~cEditorResource()
	{}

}
#endif
