#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Swarm\IEffectWorld.h>
#include <Spore\App\PropertyList.h>
#include <EASTL\map.h>

#define SpaceGfx (*Simulator::cSpaceGfx::Get())

namespace Simulator
{
	class cSpaceGfx
		: public cStrategy
	{
	public:
		static cSpaceGfx* Get();

		void InitializeInternal();
		void DisposeInternal();

		/// Returns the scale in which planets, moons, gas giants and stars are displayed in the 
		static float GetObjectScale(SpaceGfxObjectType type, float tValue, bool isFromPlanet);

	public:
		/// The effect that shows the stars in the galaxy. `sg_galaxy`, uses `mpGalaxyEffectWorld`.
		/* 1Ch */	IEffectPtr mpGalaxyEffect;
		/// Shows extra lonely stars outside the galaxy, only visible when zooming out the galaxy. `0x5C830352`, uses mpGalaxyEffectWorld
		/* 20h */	IEffectPtr field_20;
		/// Gloom effect that makes the galaxy brighter, only visible when zooming out the galaxy. `sg_galaxy_screen`, uses mpGalaxyEffectWorld
		/* 24h */	IEffectPtr mpGalaxyScreenEffect;
		/// The blue-ish image with the shape of the galaxy. `sg_galaxy_ambience`, uses mpGalaxyEffectWorld
		/* 28h */	IEffectPtr mpGalaxyAmbienceEffect;
		/// `0xC467B744`, uses mpGalaxyEffectWorld
		/* 2Ch */	IEffectPtr field_2C;
		/// `0x840CEA6`, uses field_94
		/* 30h */	IEffectPtr field_30;
		/// `0x45846142`, uses field_94
		/* 34h */	IEffectPtr field_34;
		/* 38h */	int field_38;
		/* 3Ch */	map<int, int> field_3C;
		/* 58h */	int field_58;  // not initialized
		/* 5Ch */	int field_5C;  // not initialized
		/// `0x4CAB5702`, uses field_94
		/* 60h */	IEffectPtr field_60;
		/// Some gloom around the sun? `0x4E7A261F`, uses field_94
		/* 64h */	IEffectPtr field_64;
		/// Some gloom around the sun? `0xC150010A`, uses field_94
		/* 68h */	IEffectPtr field_68;
		/// `solar_system_skybox`, uses field_94
		/* 6Ch */	IEffectPtr mpSolarSystemSkybox;
		/// Some gloom around the sun? `0xF1F7D4DC`, uses field_94
		/* 70h */	IEffectPtr field_70;
		/// `0xBF4763D8`, uses field_94
		/* 74h */	IEffectPtr field_74;
		/// "star dust" particles floating around, `0xA0C77D6F`, uses field_94
		/* 78h */	IEffectPtr field_78;
		/// Static stars in the sky (that don't move), `0x3EAC08A`, uses field_A4
		/* 7Ch */	IEffectPtr field_7C;
		/// Galaxies and some dust in the background, `0x3EAF98C`, uses field_A4
		/* 80h */	IEffectPtr field_80;
		/// Moving stars in the sky, `0x3EBF4AE`, uses field_9C
		/* 84h */	IEffectPtr field_84;
		/// Galaxies and some dust in the background, less bright than field_80, `0x3EBF4B5`, uses field_9C
		/* 88h */	IEffectPtr field_88;
		/* 8Ch */	ObjectPtr field_8C;
		/* 90h */	ObjectPtr field_90;
		/// ID `0x17F40C7`
		/* 94h */	IEffectWorldPtr field_94;
		/// ID `0x17F40C8`, only unsuspended in solar system view
		/* 98h */	IEffectWorldPtr mpSolarSystemEffectWorld;
		/// ID `0x26F8FCB`, used for planet atmosphere?
		/* 9Ch */	IEffectWorldPtr field_9C;
		// sub_6EEF90
		/* A0h */	ObjectPtr field_A0;
		/// ID `0x284E479`
		/* A4h */	IEffectWorldPtr field_A4;
		// sub_6EEF90
		/* A8h */	ObjectPtr field_A8;
		/// ID `0x17F40C9`, only unsuspended in galaxy view
		/* ACh */	IEffectWorldPtr mpGalaxyEffectWorld;
		/// ID `0x67247E6`
		/* B0h */	IEffectWorldPtr field_B0;
		// sub_6EEF90
		/* B4h */	ObjectPtr field_B4;
		/* B8h */	ObjectPtr field_B8;
		/* BCh */	int field_BC;
		/* C0h */	ObjectPtr field_C0;
		/* C4h */	ObjectPtr field_C4;
		/* C8h */	char padding_C8[0x100 - 0xC8];  //TODO cGameEditDisplayStrategy?? seems to be parent of display strategies?
		/* 100h */	bool mInitialized;
		/* 104h */	Vector3 field_104;  // not initialized
		/* 110h */	Vector3 field_110;  // not initialized
		/* 11Ch */	Vector3 field_11C;  // not initialized
		/* 128h */	int field_128;  // not initialized
		/* 12Ch */	unsigned int mGalaxyDustEffectLerpMS;  // not initialized
		/* 130h */	Vector3 mGalaxyMaxZoomDustColor;  // not initialized
		/// `gametuning~!SpaceGalaxyEffect.prop`
		/* 13Ch */	PropertyListPtr mpSpaceGalaxyEffectPropList;
	};
	ASSERT_SIZE(cSpaceGfx, 0x140);

	namespace Addresses(cSpaceGfx)
	{
		DeclareAddress(Get);  // 0xB3D3D0 0xB3D570
		DeclareAddress(InitializeInternal);  // 0x10367E0  0x1035910
		DeclareAddress(DisposeInternal);  // 0x1038190  0x10372C0
	}
}