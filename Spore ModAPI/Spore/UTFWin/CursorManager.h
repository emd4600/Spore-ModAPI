#pragma once

#include <Spore\Resource\IResourceFactory.h>
#include <Spore\UTFWin\Cursors.h>

#define CursorManager (*UTFWin::cCursorManager::Get())

namespace UTFWin
{
	class cCursorManager
		: public Resource::IResourceFactory
	{
	public:

		/// Loads a cursor and assigns it to the given ID.
		bool Load(uint32_t id, const char16_t* fileName, bool loadFromFile = true, int xHotspot = 0, int yHotspot = 0);

		uint32_t GetActiveCursor() const;
		bool SetActiveCursor(uint32_t id);

		/// Changes whether the native cursor is visible or not.
		/// @param visible
		void ShowCursor(bool visible);

		/// Selects the given controlID in the `DropCursorIcons.spui` layout to be used in the ShowDropCursorIcon() function.
		/// @param controlID
		bool UseDropCursorIcon(uint32_t controlID);

		/// Toggles the visibility of the drop cursor icon selected by UseDropCursorIcon()
		/// @param visible
		void ShowDropCursorIcon(bool visible);

		static cCursorManager* Get();
	};

	namespace Addresses(cCursorManager)
	{
		DeclareAddress(Get);

		DeclareAddress(Load);
		DeclareAddress(GetActiveCursor);
		DeclareAddress(SetActiveCursor);
		DeclareAddress(ShowCursor);
		DeclareAddress(UseDropCursorIcon);
		DeclareAddress(ShowDropCursorIcon);
	}
}