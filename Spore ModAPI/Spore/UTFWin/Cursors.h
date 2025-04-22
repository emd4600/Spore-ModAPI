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

			///-------------------
			/// Simulator Cursors
			///------------------- 

			/// cursor-no-opt
			NoOptions = 0x3a204b0,

			// cursor-object-translate
			Pan = 0x600cd69,
			
			/// cursor-grab_open
			GrabOpen = 0x648fbf1,

			/// cursor-ban-mode
			BanMode = 0x5ecbdffd,


			///-------------------
			/// CRG Cursors
			///-------------------
			
			/// cur_ClaimNest
			ClaimNest = 0x7542cdb5,

			/// cursor_skeleton2
			UnlockSkeleton = 0x342d221f,

			/// cursor-eat-fruit
			EatFruit = 0xb14ab7b6,

			/// cursor-eat-omni
			EatOmni = 0x3febe52,

			/// cursor-eat-carcass
			EatCarn = 0x514ab7b7,

			/// cursor-mate
			Mate = 0x314ab7b1,

			/// cursor-target-creature
			TargetCreature = 0xf36a0c84,

			/// cursor_atk
			Attack = 0xb14ab7b9,

			/// cursor_social
			Socialize = 0x525ff7d,

			/// cursor_friend
			Friend = 0x755c4eb5,

			/// cursor-crg-pickup
			Pickup = 0x3b360dc,

			/// cursor-crg-putdown
			Putdown = 0x3b360df,

			/// cursor-crg-throw
			Throw = 0x3b360e4,


			///-------------------
			/// TRG Cursors
			///-------------------

			/// cursor-dance
			Dance = 0x3febe3d,

			/// cursor-trg-domesticate
			Domesticate = 0xe382f00e,

			/// cursor-steal
			Steal = 0x3febe42,

			/// cursor_repair
			Repair = 0x525ff0f,

			/// cursor-crg-give-grn
			Gift = 0x8b875bdc,

			/// cursor-crg-give-grn-no
			GiftDeny = 0xf59ce677,

			/// cursor-fish
			Fish = 0x3febe3f,

			/// cursor-gather
			Gather = 0x3febe40,

			/// cursor_pickup-maracas
			PickupMaracas = 0x63fe8d4,

			/// cursor_pickup-horn
			PickupHorn = 0x63fe8d5,

			/// cursor_pickup-didgeridoo
			PickupDidgeridoo = 0x63fe8d6,

			/// cursor_pickup-axe
			PickupAxe = 0x63fe8d7,

			/// cursor_pickup-spear
			PickupSpear = 0x63fe8d8,

			/// cursor_pickup-torch
			PickupTorch = 0x63fe8d9,

			/// cursor-trg-tool-pickup-fish
			PickupFishing = 0x3febe37,

			/// cursor-trg-tool-pickup-gather
			PickupGather = 0x3febe38,

			/// cursor_pickup-heal
			PickupHealing = 0x3febe3b,


			///-------------------
			/// CVG Cursors
			///-------------------

			/// cursor-claim-spicemine
			ClaimSpice = 0x5d53800,

			/// cursor_goodie-hut
			QuestionHut = 0x56e3a22,


			///-------------------
			/// SPG Cursors
			///------------------- 

			/// cursor-spg-sculpting-norm
			SpgSculpting = 0x682102e,

			/// cursor-spg-social-norm
			SpgSocial = 0x6821016,

			/// cursor-spg-sculpting-norm
			SpgSculpt = 0x682102e,

			/// cursor-spg-travel-norm
			SpgScan = 0x6821022,

			/// cursor-spg-travel-on
			SpgScanActive = 0x6821024,

			/// cursor-spg-abduct-norm
			SpgAbduct = 0x682103e,
			
			/// cursor-spg-abduct-on
			SpgAbductActive = 0x6821040,
			
			/// cursor-spg-color-norm
			SpgColor = 0x6821026,
			
			/// cursor-spg-color-on
			SpgColorActive = 0x6821029,
			
			/// cursor-spg-colonize-norm
			SpgColonize = 0x6821032,

			/// cursor-spg-atmospheric-norm
			SpgAtmosphere = 0x6821042,


			///-------------------
			/// EP1 Cursors
			///-------------------

			/// cursor-object-scale
			ObjectScale = 0xe84563d4,

			/// cursor-translate-XY
			TranslateXY = 0xf728e452,
			
			/// cursor-translate-Z
			TranslateZ = 0x7391920b,
			
		};
	}
}