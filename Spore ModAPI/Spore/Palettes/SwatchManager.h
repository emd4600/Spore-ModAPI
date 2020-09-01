#pragma once

#include <Spore\Palettes\ItemViewer.h>

#define SwatchManager (*Palettes::cSwatchManager::Get())

namespace Palettes
{
	class cSwatchManager
	{
	public:
		void SetUnloadTime(ItemViewer* pViewer, float time = 1e12f);

		ItemViewer* AddViewer(ItemViewer* pViewer = nullptr);

		static cSwatchManager* Get();
	};

	namespace Addresses(cSwatchManager)
	{
		DeclareAddress(Get);
		DeclareAddress(SetUnloadTime);
		DeclareAddress(AddViewer);
	}
}