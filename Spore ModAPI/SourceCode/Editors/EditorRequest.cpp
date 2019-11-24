#ifndef MODAPI_DLL_EXPORT
#include <Spore\Editors\EditorRequest.h>
#include <Spore\App\IGameModeManager.h>

namespace Editors
{
	EditorRequest::EditorRequest()
		: mRefCount()
		, editorID(-1)
		, creationKey()
		, activeModeID(App::GameModeManager()->GetActiveModeID())
		, field_20()
		, editableTests()
		, sporepediaCanSwitch()
		, disableNameEdit()
		, allowSporepedia()
		, hasSaveButton()
		, hasCreateNewButton()
		, hasExitButton(true)
		, hasPublishButton()
		, hasCancelButton(true)
		, field_3C()
		, field_3D(true)
		, field_40()
		, field_50()
		, field_60()
		, field_64()
		, field_65()
		, field_66()
		, field_68()
		, field_6C()
		, field_6D(true)
		, field_6E(true)
		, field_6F()
		, field_70()
		, field_84()
		, field_88()
		, field_8C()
		, field_90()
		, field_94(nullptr)
		, next(nullptr)
	{
	}

	EditorRequest::~EditorRequest() {}

	int EditorRequest::AddRef() {
		++mRefCount;
		return mRefCount;
	}

	int EditorRequest::Release() {
		--mRefCount;
		if (!mRefCount) delete this;
		return mRefCount;
	}

	auto_STATIC_METHOD(EditorRequest, bool, Submit, Args(EditorRequest* request), Args(request));
}
#endif
