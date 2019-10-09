#pragma once

#include <Spore\App\StandardMessage.h>
#include <Spore\MathUtils.h>

namespace Editors
{
	// not public inheritance, so user can't access the fields
	///
	/// A message sent every time the user changes the color of the creation in the editor.
	class ColorChangedMessage : App::StandardMessage
	{
	public:
		static const uint32_t ID = 0x90E08F60;

		using App::StandardMessage::id;

		inline ColorChangedMessage(Math::Color color, Object* object, uint32_t regionFilter, bool isDefaultColor, int colorIndex)
		{
			params[0].uint32 = color.value;
			SetObject(1, object);
			params[2].uint32 = regionFilter;
			params[3].boolean = isDefaultColor;
			params[4].int32 = colorIndex;
		}

		/// Returns the color selected by the user.
		inline Math::Color GetColor() {
			return params[0].uint32;
		}

		inline Object* GetColorChooserObject() {
			return params[1].object;
		}

		/// In block painting, the instance ID of a file that defines which region is painted in partial styles;
		/// The file is assumed to be in the folder with group ID 0x406A6F00.
		/// In skinpaints, this is the skinpaint index (0 -> base, 1 -> coat, 2 -> detail).
		inline uint32_t GetRegionFilter() {
			return params[2].uint32;
		}

		inline bool IsDefaultColor() {
			return params[3].boolean;
		}

		inline int GetColorIndex() {
			return params[4].int32;
		}
	};

}