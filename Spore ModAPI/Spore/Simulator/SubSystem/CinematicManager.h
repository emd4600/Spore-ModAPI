#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\ArgScript\ICommand.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\MathUtils.h>

/// Accesses the current instance of Simulator::cCinematicManager
#define CinematicManager (*Simulator::cCinematicManager::Get())

namespace Simulator
{
	class CinematicActionUnkBase
	{
	public:
		virtual ~CinematicActionUnkBase() = 0;
		virtual int AddRef() = 0;
		virtual int Release() = 0;
	};

	typedef bool(*CinematicActionFunction_t)(Object* actionData, bool);

	class CinematicAction
		: public RefCountTemplate
		, public CinematicActionUnkBase
	{
	public:
		virtual ~CinematicAction() {}
		virtual int AddRef() override;
		virtual int Release() override;

		static CinematicActionFunction_t GetStartVignetteFunction();

	public:
		/// For instance, CinematicVignetteAction
		/* 0Ch */	ObjectPtr mActionData;
		/* 10h */	CinematicActionFunction_t mFunction;
	};
	ASSERT_SIZE(CinematicAction, 0x14);

	namespace Addresses(CinematicAction) {
		DeclareAddress(StartVignetteFunction_ptr);  // 0xAD3D50 0xAD3EF0
	}


	class cCinematicManager
		: public App::IMessageListener
		, public cStrategy
	{
	public:
		static cCinematicManager* Get();

		/* 10h */	virtual void AddCommand(const char* commandName, ArgScript::ICommand* command);

		void PlayCinematic(const char* cinematicName, int arg0, int arg1, int arg2, int arg3, int arg4);

	public:
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	int field_2C;
		/* 30h */	char padding_30[0x3c8 - 0x30];
	};
	ASSERT_SIZE(cCinematicManager, 0x3C8);
	
	namespace Addresses(cCinematicManager) {
		DeclareAddress(Get);  // 0xB3D430 0xB3D5D0
		DeclareAddress(PlayCinematic);  // 0xAE0480 0xAE08B0
	}



	class CinematicVignetteActionData
		: public Object
		, public DefaultRefCounted
	{
	public:
		enum class PositionType
		{
			None = 0,
			Unk1 = 1,
			Effect = 2,
			ActorNest = 3,
			ActorHut = 4,
			ActorTribe = 5,
			ActorCity = 6,
			Object = 7,
			Actor = 8,
			NearestWater = 9,
			NearestLand = 10
		};

		enum class OffsetMultiplier {
			/// Uses the foot radius of the actor as an offset multiplier
			FootprintRadius = 0,
			/// Uses the max width of the target object as an offset multiplier
			TargetWidth = 1,
			/// Uses the height of the target object as an offset multiplier
			TargetHeight = 2,
			None = 3,
		};

		static const uint32_t TYPE = 0x55113D6;

		CinematicVignetteActionData();
		virtual ~CinematicVignetteActionData() {}

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

	public:
		/// Actor name
		/* 0Ch */	uint32_t mActorId;
		/// Vignette identifier
		/* 10h */	uint32_t mVignetteId;
		/// Vignette identifier
		/* 14h */	ResourceKey mVignetteKey;
		/// Relative position (if no options specified, then relative to the actor)
		/* 20h */	Math::Vector3 mPosition;
		/* 2Ch */	Math::Vector3 mFacingOffset;
		/// If not None, relative to a position
		/* 38h */	PositionType mRelativePosType;  // Unk1
		/* 3Ch */	uint32_t mRelativePosId;
		/// If not None, face a position with an optional offset mFacingOffset
		/* 40h */	PositionType mFacingType;  // None
		/* 44h */	uint32_t mFacingId;
		/// state does not wait for routing to finish
		/* 48h */	bool mNoWait;
		/* 4Ch */	OffsetMultiplier mOffsetMultiplier;  // None
		/* 50h */	uint32_t field_50;  // -1
	};
	ASSERT_SIZE(CinematicVignetteActionData, 0x54);
}