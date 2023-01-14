#pragma once

namespace UTFWin
{
	/// The cursor IDs that are always available. There are more cursors on the game, but their ID
	/// and whether they are loaded depend on the current context of the game.
	namespace BasicCursorIDs
	{
		enum Cursors
		{
			/// STD_None
			StdNone = 0x1001,

			/// STD_Center
			StdCenter = 0x1005,

			/// STD_IBeam
			StdIBeam = 0x1004,

			/// cursor_link
			Link = 0x1006,

			/// STD_Help
			StdHelp = 0x1007,

			/// STD_SizeNS
			StdSizeNS = 0x1008,

			/// STD_SizeWE
			StdSizeWE = 0x1009,

			/// STD_SizeNWSE
			StdSizeNWSE = 0x100A,

			/// STD_SizeNESW
			StdSizeNESW = 0x100B,

			/// STD_SizeAll
			StdSizeAll = 0x100C,

			/// cursor-dragselect
			DragSelect = 0x100D,

			/// cursor-default
			Default = 0x1002,

			/// cursor-default-debug
			DefaultCursor = 0x1011,

			/// cursor-wait
			Wait = 0x1003,

			/// cursor-active-wait
			ActiveWait = 0x1024,

			/// cursor-magicwand
			MagicWand = 0x100E,

			/// cursor-paint
			Paint = 0x100F,

			/// cursor-eyedropper
			EyeDropper = 0x1010,

			/// cursor-default-alpha01
			DefaultAlpha01 = 0x1012,
			
			/// cursor-default-alpha02
			DefaultAlpha02 = 0x1013,

			/// cursor-default-alpha03
			DefaultAlpha03 = 0x1014,

			/// cursor-default-alpha04
			DefaultAlpha04 = 0x1015,

			/// cursor-default-alpha05
			DefaultAlpha05 = 0x1016,

			/// cursor-default-alpha06
			DefaultAlpha06 = 0x1017,

			/// cursor-default-alpha07
			DefaultAlpha07 = 0x1018,

			/// cursor-default-alpha08
			DefaultAlpha08 = 0x1019,

			/// cursor-default-alpha09
			DefaultAlpha09 = 0x101A,

			/// STD_Center-alpha01
			StdCenterAlpha01 = 0x101B,

			/// STD_Center-alpha02
			StdCenterAlpha02 = 0x101C,

			/// STD_Center-alpha03
			StdCenterAlpha03 = 0x101D,

			/// STD_Center-alpha04
			StdCenterAlpha04 = 0x101E,

			/// STD_Center-alpha05
			StdCenterAlpha05 = 0x101F,

			/// STD_Center-alpha06
			StdCenterAlpha06 = 0x1020,

			/// STD_Center-alpha07
			StdCenterAlpha07 = 0x1021,

			/// STD_Center-alpha08
			StdCenterAlpha08 = 0x1022,

			/// STD_Center-alpha09
			StdCenterAlpha09 = 0x1023,
		};
	}
}