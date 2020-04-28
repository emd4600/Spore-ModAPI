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

		static cCursorManager* Get();
	};

	namespace Addresses(cCursorManager)
	{
		DeclareAddress(Get);

		DeclareAddress(Load);
		DeclareAddress(GetActiveCursor);
		DeclareAddress(SetActiveCursor);
	}
}