#pragma once

#include <Spore\Resource\ResourceObject.h>
#include <Spore\MathUtils.h>

#define cCellResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellResource>
#define cAdvectResourcePtr eastl::intrusive_ptr<Simulator::Cell::cAdvectResource>
#define cCellBackgroundMapResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellBackgroundMapResource>>
#define cCellCellResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellCellResource>>
#define cCellEffectMapResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellEffectMapResource>>
#define cCellGlobalsResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellGlobalsResource>>
#define cCellLookAlgorithmResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellLookAlgorithmResource>>
#define cCellLookTableResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellLookTableResource>>
#define cCellLootTableResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellLootTableResource>>
#define cCellPopulateResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellPopulateResource>>
#define cCellPowersResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellPowersResource>>
#define cCellRandomCreatureResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellRandomCreatureResource>>
#define cCellStructureResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellStructureResource>>
#define cCellWorldResourcePtr eastl::intrusive_ptr<Simulator::Cell::cCellDataReference<Simulator::Cell::cCellWorldResource>>

namespace Simulator
{
	namespace Cell
	{
		struct CellSerializerField
		{
			/* 00h */	const char* mpName;
			/* 04h */	uint32_t mID;
			/* 08h */	int field_8;  // some offset? If it's -1, it's the end of the CellSerializer fields
			/* 0Ch */	int field_C;
			/* 10h */	int field_10;  // pointer to a CellSerializer? Sometimes it's also just a number
			/* 14h */	int field_14;  // some type? 4 is pointer
			/* 18h */	int field_18;
			/* 1Ch */	int field_1C;  // default value?
			/* 20h */	int field_20;
			/* 24h */	int field_24;
		};
		ASSERT_SIZE(CellSerializerField, 0x28);

		struct CellSerializer
		{
			/* 00h */	const char* mpName;
			/* 04h */	CellSerializerField* mpFields;
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	int field_10;
			/* 14h */	int field_14;
			/* 18h */	int field_18;
			/* 1Ch */	int field_1C;
			/* 20h */	int field_20;
			/* 24h */	int field_24;
		};
		ASSERT_SIZE(CellSerializer, 0x28);

		class cCellResource
			: public Resource::ResourceObject
		{
		public:
			static const uint32_t TYPE = 0x116D51E;

		public:
			/* 14h */	void* mpData;
			/* 18h */	int mDataSize;
			/* 1Ch */	CellSerializer* mDataSerializer;
		};
		ASSERT_SIZE(cCellResource, 0x20);


		struct cCellDataReference_
		{
			/* 00h */	uint32_t mInstanceID;
			/* 04h */	CellSerializer* mpSerializer;
			/* 08h */	cCellResourcePtr mpResource;
			/* 0Ch */	int mCounter;

			void AddRef();
			void Release();

			static cCellDataReference_* Create(uint32_t instanceID, CellSerializer* serializer);
		};
		ASSERT_SIZE(cCellDataReference_, 0x10);

		namespace Addresses(cCellDataReference_) 
		{
			DeclareAddress(Create);  // 0xE829B0 0xE82420
		}

		template <typename T> struct cCellDataReference 
			: public cCellDataReference_
		{
			static cCellDataReference<T>* Create(uint32_t instanceID) {
				return (cCellDataReference<T>*)cCellDataReference_::Create(instanceID, T::Serializer());
			}
		};

		enum class CellStageScale : int
		{
			None = -1,
			_0 = 0,
			_1 = 1,
			_2 = 2,
			_4 = 3,
			_10 = 4,
			_20 = 5,
			_40 = 6,
			_100 = 7,
			_200 = 8,
			_400 = 9,
			_1K = 10,
			_2K = 11,
			_4K = 12,
			_10K = 13,
			_20K = 14,
			_40K = 15,
			_100K = 16,
			_200K = 17,
			_400K = 18,
			_1M = 19
		};

		struct cCellPowersResource
		{
			typedef cCellDataReference<cCellPowersResource> Reference;
			static const uint32_t TYPE = 0x754BE343;
			static CellSerializer* Serializer();

			/* 00h */	int teleportCost;
			/* 04h */	float teleportRange;
		};
		ASSERT_SIZE(cCellPowersResource, 0x8);

		struct cCellRandomCreatureResource
		{
			typedef cCellDataReference<cCellRandomCreatureResource> Reference;
			static const uint32_t TYPE = 0xF9C3D770;
			static CellSerializer* Serializer();

			struct cRandomCreatureEntry
			{
				enum class Type : int {
					Creature = 0,
					Pollinated = 1
				};

				/* 00h */	Type type;
				/* 04h */	uint32_t creatureID;
				/* 08h */	float weight;
				/* 0Ch */	int speedMin;
				/* 10h */	int speedMax;
				/* 14h */	int dangerMin;
				/* 18h */	int dangerMax;
			};
			ASSERT_SIZE(cRandomCreatureEntry, 28);

			/* 00h */	int numEntries;
			/* 04h */	cRandomCreatureEntry* entries;
		};
		ASSERT_SIZE(cCellRandomCreatureResource, 8);

		struct cCellStructureResource
		{
			typedef cCellDataReference<cCellStructureResource> Reference;
			static const uint32_t TYPE = 0x4B9EF6DC;
			static CellSerializer* Serializer();

			struct cSPAttachment
			{
				enum class Type : int {
					Model = 0,
					Effect = 1,
					Structure = 2,
					Creature = 3,
					RandomCreature = 4,
					PlayerCreature = 5,
					Debug = 6
				};

				/* 00h */	int bone;
				/* 04h */	Type type;
				/* 08h */	cCellDataReference<cCellStructureResource>* structure;
				/* 0Ch */	cCellDataReference<cCellRandomCreatureResource>* randomCreature;
				/* 10h */	int effectID;
				/* 14h */	int levelMin;
				/* 18h */	int levelMax;
				/* 1Ch */	Math::ColorRGB color;
			};
			ASSERT_SIZE(cSPAttachment, 0x28);

			/* 00h */	uint32_t onDeath;
			/* 04h */	uint32_t onDeathSmall;
			/* 08h */	uint32_t onDeathLarge;
			/* 0Ch */	uint32_t onHatch;
			/* 10h */	uint32_t onStartHatch;
			/* 14h */	cSPAttachment* attachments;
			/* 18h */	int numAttachments;
		};
		ASSERT_SIZE(cCellStructureResource, 0x1C);

		struct cCellCellResource;
		struct cCellPopulateResource
		{
			typedef cCellDataReference<cCellPopulateResource> Reference;
			static const uint32_t TYPE = 0xDA141C1B;
			static CellSerializer* Serializer();

			struct cMarker
			{
				enum class Type : int
				{
					Distribute = 0,
					Cluster = 1,
					Plant = 2,
					Encounter = 3
				};
				enum class PlantType : int
				{
					Type1 = 0,
					Type2 = 1,
					Type3 = 2,
					Type4 = 3,
					Type5 = 4,
					Type6 = 5,
				};

				/* 00h */	int field_0;
				/* 04h */	int field_4;
				/* 08h */	int field_8;
				/* 0Ch */	float zOffset;
				/* 10h */	float zOffsetMax;
				/* 14h */	int field_14;
				/* 18h */	cCellDataReference<cCellCellResource>* distributeCell;
				/* 1Ch */	cCellDataReference<cCellCellResource>* clusterCell;
				/* 20h */	cCellDataReference<cCellPopulateResource>* encounterPopulate;
				/* 24h */	PlantType plantType;
				/* 28h */	Type type;
				/* 2Ch */	float count;
				/* 30h */	float count_easy;
				/* 34h */	float count_med;
				/* 38h */	float count_hard;
				/* 3Ch */	int size;
				/* 40h */	int parts;
				/* 44h */	int linear;
				/* 48h */	int encounterScale;
			};
			ASSERT_SIZE(cMarker, 0x4C);

			/* 00h */	CellStageScale scale;
			/* 04h */	uint32_t maskTexture;
			/* 08h */	int numMarkers;
			/* 0Ch */	cMarker* markers;
		};
		ASSERT_SIZE(cCellPopulateResource, 0x10);

		struct cCellWorldResource
		{
			typedef cCellDataReference<cCellWorldResource> Reference;
			static const uint32_t TYPE = 0x9B8E862F;
			static CellSerializer* Serializer();

			struct cLevelEntry
			{
				/* 00h */	cCellDataReference<cCellPopulateResource>* populate;
				/* 04h */	bool startTile;
				/* 08h */	CellStageScale playerSize;
			};
			ASSERT_SIZE(cLevelEntry, 12);

			struct cAdvectEntry
			{
				/* 00h */	CellStageScale field_0;
				/* 04h */	CellStageScale playerSize;
				/* 08h */	int strength;
				/* 0Ch */	int variance;
				/* 10h */	int period;
				/* 14h */	uint32_t advectID;
			};
			ASSERT_SIZE(cAdvectEntry, 24);

			/* 00h */	int numPopulate;
			/* 04h */	cLevelEntry* populate;
			/* 08h */	int numAdvect;
			/* 0Ch */	cAdvectEntry* advect;
		};
		ASSERT_SIZE(cCellWorldResource, 0x10);

		struct cCellLootTableResource;

		struct cCellCellResource
		{
			typedef cCellDataReference<cCellCellResource> Reference;
			static const uint32_t TYPE = 0xDFAD9F51;
			static CellSerializer* Serializer();

			struct cAIData
			{
				enum class Type : int
				{
					None = -1,
					Player = 0,
					Straight = 0x1002,
					SlowSeek = 0x1003,
					Orbit = 0x1004,
					Chomp = 0x1005,
					Eater = 0x1006,
					Parasite = 0x1007,
					Caterpillar = 0x1008,
					Sleeper = 0x1009,
					Waterballoon = 0x100A,
					Mosquito = 0x100B,
					Dragon = 0x100C,
					Poolball = 0x100D,
					Leak = 0x100E,
					Parts = 0x1001
				};
				enum class MovementStyle : int
				{
					Default = 0,
					Flagella = 1,
					Cillia = 2,
					Jet = 4,
					TurnInPlace = 8,
					FlagellaCillia = 3,
					FlagellaJet = 5,
					CilliaJet = 6,
					FlagellaCilliaJet = 7
				};
				enum class FoodType : int
				{
					Null = -1,
					None = 0,
					Liquid = 3,
					Rock = 1,
					Solid = 2,
					Air = 4
				};

				/* 00h */	Type type;
				/* 04h */	float awarenessRadius;
				/* 08h */	float awarenessRadiusFood;
				/* 0Ch */	float awarenessRadiusPredator;
				/* 10h */	MovementStyle movementStyle;
				/* 14h */	bool flocking;
				/* 18h */	float speed;
				/* 1Ch */	float chaseSpeed;
				/* 20h */	float wanderSpeed;
				/* 24h */	float fleeSpeed;
				/* 28h */	float fearsNearbyDamageRadius;
				/* 2Ch */	float fearsNearbyDeathRadius;
				/* 30h */	float fearsNearbyDamageTime;
				/* 34h */	float fearsNearbyDeathTime;
				/* 38h */	float protectRadius;
				/* 3Ch */	float protectTime;
				/* 40h */	float turnFactor;
				/* 44h */	bool axialMovement;
				/* 48h */	float spawnTime;
				/* 4Ch */	float spawnRestTime;
				/* 50h */	cCellDataReference<cCellLootTableResource>* spawnOutput;
				/* 54h */	float arcLength;
				/* 58h */	float arcLengthSecondary;
				/* 5Ch */	int numArcs;
				/* 60h */	cCellCellResource* keyTransformation;
				/* 64h */	cCellCellResource* keyProjectile;
				/* 68h */	FoodType food;
				/* 6Ch */	int growCount;
				/* 70h */	int digestionCount;
				/* 74h */	float digestionTime;
				/* 78h */	cCellDataReference<cCellLootTableResource>* digestionOutput;
				/* 7Ch */	float fleeTime;
				/* 80h */	float fleeRestTime;
				/* 84h */	float chaseTime;
				/* 88h */	float chaseRestTime;
				/* 8Ch */	bool chasesDamage;
				/* 8Dh */	bool fearsMouths;
				/* 8Eh */	bool fearsWeapons;
				/* 8Fh */	bool fearsElectric;
				/* 90h */	bool fearsPoison;
				/* 91h */	bool fearsDamage;
				/* 92h */	bool ignoresFood;
				/* 94h */	float awakeTime;
				/* 98h */	float sleepTime;
				/* 9Ch */	int growAmount;
				/* A0h */	float hatchDuration;
				/* A4h */	float poisonRecharge;
				/* A8h */	float electricRecharge;
				/* ACh */	float electricRechargeVsSmall;
				/* B0h */	float electricDischarge;
			};
			ASSERT_SIZE(cAIData, 0xB4);

			struct cLocalizedString
			{
				/* 00h */	char16_t text[80];
				/* 04h */	uint32_t localeInstanceID;
			};
			ASSERT_SIZE(cLocalizedString, 164);

			struct cEatData
			{
				/* 00h */	int foodValue;
				/* 04h */	int hpValue;
				/* 08h */	bool bomb;
				/* 0Ch */	bool poisonNova;
			};
			ASSERT_SIZE(cEatData, 12);

			enum class CellType : int
			{
				None = 0,
				Liquid = 3,
				Rock = 1,
				Solid = 2,
				Air = 4,
				Poison = 5,
				Nanite = 7,
				Unlock = 6
			};
			enum class Sound : int
			{
				None = 0,
				Plant = 2,
				Rock = 3,
				Creature = 1,
				Bubble = 4
			};
			enum class Density : int
			{
				None = 0,
				Air = 2,
				Liquid = 1,
				Solid = 3,
				Rock = 4
			};
			enum class UnlockType : int
			{
				None = 0,
				Body = 12,

				Mandible = 2,
				Filter = 3,
				Proboscis = 4,

				Chemical = 5,
				Electric = 6,
				Spike = 7,

				Cilia = 8,
				Flagella = 9,
				Jet = 10
			};

			/* 00h */	cCellDataReference<cCellStructureResource>* structure;
			/* 04h */	cLocalizedString name;
			/* A8h */	int hp;
			/* ACh */	bool fixedOrientation;
			/* B0h */	int flags;
			/* B4h */	CellType cellType;
			/* B8h */	UnlockType unlockType;
			/* BCh */	Density density;
			/* C0h */	Sound sound;
			/* C4h */	cCellDataReference<cCellCellResource>* break_;
			/* C8h */	cCellDataReference<cCellLootTableResource>* pieces;
			/* CCh */	cCellDataReference<cCellCellResource>* leak;
			/* D0h */	cCellDataReference<cCellCellResource>* expel;
			/* D4h */	cCellDataReference<cCellLootTableResource>* explosionTable;
			/* D8h */	cCellDataReference<cCellLootTableResource>* loot;
			/* DCh */	cCellDataReference<cCellCellResource>* poison;
			/* E0h */	cAIData ai;
			/* 194h */	cAIData ai_hard;
			/* 248h */	cAIData ai_easy;
			/* 2FCh */	int friendGroup;
			/* 300h */	bool wontAttackPlayer;
			/* 301h */	bool wontAttackPlayerWhenSmall;
			/* 304h */	float size[2];
			/* 30Ch */	cEatData eat;
			/* 318h */	bool triggersEscapeMission;
		};
		ASSERT_SIZE(cCellCellResource, 0x31C);

		struct cCellLootTableResource
		{
			typedef cCellDataReference<cCellLootTableResource> Reference;
			static const uint32_t TYPE = 0xD92AF091;
			static CellSerializer* Serializer();

			struct cLootTableEntry
			{
				enum class Type : int
				{
					Nothing = 0,
					Cell = 1,
					Table = 2
				};

				/* 00h */	Type type;
				/* 04h */	cCellDataReference<cCellCellResource>* cell;
				/* 08h */	cCellDataReference<cCellLootTableResource>* table;
				/* 0Ch */	float weight;
				/* 10h */	int count;
				/* 14h */	int countDelta;
				/* 18h */	int levelOffset;
			};
			ASSERT_SIZE(cLootTableEntry, 28);

			/* 00h */	cLootTableEntry* entries;
			/* 04h */	int numEntries;
			/* 08h */	float minRadius;
			/* 0Ch */	float maxRadius;
			/* 10h */	float initialAlpha;
			/* 14h */	float expelForce;
			/* 18h */	int effect;
			/* 1Ch */	bool mustHavePart;
			/* 20h */	float delay;
		};
		ASSERT_SIZE(cCellLootTableResource, 0x24);

		struct cCellLookTableResource
		{
			typedef cCellDataReference<cCellLookTableResource> Reference;
			static const uint32_t TYPE = 0x8C042499;
			static CellSerializer* Serializer();

			struct cLookTableEntry
			{
				enum class Type : int
				{
					Up = 0,
					Forward = 1,
					Left = 2,
					Right = 3,
					PursueTarget = 4,
					FleeTarget = 5,
					Object = 6,
					Food = 7,
					Predator = 8,
					Destination = 9,
					Cursor = 10,
					Player = 11,
				};

				/* 00h */	Type type;
				/* 04h */	float value;
			};
			ASSERT_SIZE(cLookTableEntry, 8);

			/* 00h */	cLookTableEntry* entries;
			/* 04h */	int numEntries;
		};
		ASSERT_SIZE(cCellLookTableResource, 8);

		struct cCellLookAlgorithmResource
		{
			typedef cCellDataReference<cCellLookAlgorithmResource> Reference;
			static const uint32_t TYPE = 0xDBA35AE2;
			static CellSerializer* Serializer();

			struct cLookAlgorithmEntry
			{
				enum class Type : int
				{
					Player = 0,
					NPC = 1,
					Epic = 2
				};
				enum class Action : int
				{
					Other = -1,
					Idle = 0,
					Moving = 0x12,
					Scared = 0x15,
					MoveScared = 0x13,
					Mad = 0x16,
					MoveMad = 0x14
				};

				/* 00h */	Type type;
				/* 04h */	Action action;
				/* 08h */	cCellDataReference<cCellLookTableResource>* player;
				/* 0Ch */	cCellDataReference<cCellLookTableResource>* npc;
				/* 10h */	cCellDataReference<cCellLookTableResource>* epic;
			};
			ASSERT_SIZE(cLookAlgorithmEntry, 20);

			/* 00h */	cLookAlgorithmEntry* entries;
			/* 04h */	int numEntries;
		};
		ASSERT_SIZE(cCellLookAlgorithmResource, 8);

		struct cCellEffectMapResource
		{
			typedef cCellDataReference<cCellEffectMapResource> Reference;
			static const uint32_t TYPE = 0x433FB70C;
			static CellSerializer* Serializer();

			struct cEffectMapEntry
			{
				enum class Type : int
				{
					Foreground = 0,
					Background = 1,
					Tracer = 2,
					TracerBackground = 3,
					Skybox = 4,
					TileBackground = 5
				};

				/* 00h */	uint32_t effectID;
				/* 04h */	Type type;
				/* 08h */	float field_8;
				/* 0Ch */	float field_C;
				/* 10h */	float field_10;
				/* 14h */	float field_14;
				/* 18h */	int field_18;
			};
			ASSERT_SIZE(cEffectMapEntry, 28);

			/* 00h */	int numEntries;
			/* 04h */	cEffectMapEntry* entries;
		};
		ASSERT_SIZE(cCellEffectMapResource, 8);

		struct cCellBackgroundMapResource
		{
			typedef cCellDataReference<cCellBackgroundMapResource> Reference;
			static const uint32_t TYPE = 0x612B3191;
			static CellSerializer* Serializer();

			struct cBackgroundMapEntry
			{
				/* 00h */	Math::ColorRGB color;
				/* 0Ch */	float field_C;
			};
			ASSERT_SIZE(cBackgroundMapEntry, 0x10);

			/* 00h */	int numEntries;
			/* 04h */	cBackgroundMapEntry* entries;
		};
		ASSERT_SIZE(cCellBackgroundMapResource, 8);

		struct cCellGlobalsResource
		{
			typedef cCellDataReference<cCellGlobalsResource> Reference;
			static const uint32_t TYPE = 0x2A3CE5B7;
			static CellSerializer* Serializer();

			enum class GameMode : int
			{
				_0 = 0,
				_1 = 1,
				_2 = 2
			};
			enum class ControlMethod : int
			{
				_0 = 0,
				_1 = 1,
				_2 = 2
			};
			enum class EditorMethod : int
			{
				_0 = 0,
				_1 = 1
			};
			enum class TutorialMethod : int
			{
				_0 = 0,
				_1 = 1,
				_2 = 2
			};
			enum class EndingMethod : int
			{
				_0 = 0,
				_1 = 1
			};
			enum class EyeMethod : int
			{
				_0 = 0,
				/// The game considers a cell blind if it has less than 3 eyes
				_1 = 1
			};

			/* 00h */	GameMode gameMode;
			/* 04h */	cCellDataReference<cCellWorldResource>* world_1;
			/* 08h */	cCellDataReference<cCellWorldResource>* world_2;
			/* 0Ch */	cCellDataReference<cCellWorldResource>* world_3;
			/* 10h */	cCellDataReference<cCellWorldResource>* world_4;
			/* 14h */	cCellDataReference<cCellWorldResource>* world_5;
			/* 18h */	cCellDataReference<cCellWorldResource>* worldBackground_1;
			/* 1Ch */	cCellDataReference<cCellWorldResource>* worldBackground_2;
			/* 20h */	cCellDataReference<cCellWorldResource>* worldBackground_3;
			/* 24h */	cCellDataReference<cCellWorldResource>* worldBackground_4;
			/* 28h */	cCellDataReference<cCellWorldResource>* worldBackground_5;
			/* 2Ch */	cCellDataReference<cCellWorldResource>* worldRandom;
			/* 30h */	cCellDataReference<cCellWorldResource>* worldRandomBg;
			/* 34h */	cCellDataReference<cCellCellResource>* startCell;
			/* 38h */	uint32_t startingCellKey;
			/* 3Ch */	cCellDataReference<cCellEffectMapResource>* effectMapEntry;
			/* 40h */	cCellDataReference<cCellBackgroundMapResource>* backgroundMapEntry;
			/* 44h */	float flowMultiplier;
			/* 48h */	float npcSpeedMultiplier;
			/* 4Ch */	float npcTurnSpeedMultiplier_Jet;
			/* 50h */	float npcTurnSpeedMultiplier_Flagella;
			/* 54h */	float npcTurnSpeedMultiplier_Cilia;
			/* 58h */	float densityRock;
			/* 5Ch */	float densitySolid;
			/* 60h */	float densityLiquid;
			/* 64h */	float densityAir;
			/* 68h */	float backgroundDistance;
			/* 6Ch */	float minDragCollisionSpeed;
			/* 70h */	float minImpactCollisionSpeed;
			/* 74h */	float ciliaSpeedAsJet;
			/* 78h */	float flagellaSpeedAsJet;
			/* 7Ch */	float flagellaSpeedAsCilia;
			/* 80h */	float ciliaSpeedAsFlagella;
			/* 84h */	cCellDataReference<cCellLookAlgorithmResource>* keyLookAlgorithm;
			/* 88h */	float beachDistance;
			/* 8Ch */	float finishLineDistance;
			/* 90h */	float noPartSpeed;
			/* 94h */	float flagellaRampMinFactor;
			/* 98h */	float flagellaRampTime;
			/* 9Ch */	float flagellaRampResetAngle;
			/* A0h */	float flagellaTurnSpeedRampStart;
			/* A4h */	float flagellaTurnSpeedRampEnd;
			/* A8h */	float flagellaTurnSpeedMin;
			/* ACh */	float flagellaTurnSpeedMax;
			/* B0h */	float ciliaTurnSpeed;
			/* B4h */	float jetTurnSpeed;
			/* B8h */	float startLevelNoCreatureRadius;
			/* BCh */	float startLevelNoAnythingRadius;
			/* C0h */	int numHighLOD_FG;
			/* C4h */	int numHighLOD_BG;
			/* C8h */	float percentAnimalFood;
			/* CCh */	float percentPlantFood;
			/* D0h */	int field_208;
			/* D4h */	ControlMethod controlMethod;
			/* D8h */	EditorMethod editorMethod;
			/* DCh */	TutorialMethod tutorialMethod;
			/* E0h */	EndingMethod endingMethod;
			/* E4h */	EyeMethod eyeMethod;
			/* E8h */	float timeToGoldyCinematic;
			/* ECh */	float missionTime;
			/* F0h */	float missionResetTime;
			/* F4h */	float escapeMinDistance;
			/* F8h */	float escapeMaxDistance;
			/* FCh */	float escapeDelayMedium;
			/* 100h */	float escapeTimerHard;
			/* 104h */	float nonAnimatingCiliaMovementFactor;
			/* 108h */	float nonAnimatingJetMovementFactor;
			/* 10Ch */	float mateTriggerDistance;
			/* 110h */	float mateSpawnDistance;
		};
		ASSERT_SIZE(cCellGlobalsResource, 0x114);


		class cAdvectResource
			: public Resource::CachedResourceObject
		{
		public:
			/// A 128x128 map of vectors
			/* 18h */	Math::Vector3* mVectors;
			/* 1Ch */	int mDataSize;
		};
		ASSERT_SIZE(cAdvectResource, 0x20);


		cCellGlobalsResource* GetGlobalsData();

#ifdef SDK_TO_GHIDRA
		CellSerializer* sSerializer__lootTable;
		CellSerializer* sSerializer__cell;
		CellSerializer* sSerializer__populate;
		CellSerializer* sSerializer__world;
		CellSerializer* sSerializer__look_table;
		CellSerializer* sSerializer__random_creature;
		CellSerializer* sSerializer__look_algorithm;
		CellSerializer* sSerializer__backgroundMap;
		CellSerializer* sSerializer__effectMap;
		CellSerializer* sSerializer__powers;
		CellSerializer* sSerializer__globals;
		CellSerializer* sSerializer__structure;
#endif
	}

	namespace Addresses(Cell)
	{
		DeclareAddress(GetData);  // 0xE4D2A0 0xE4CBF0
		DeclareAddress(GetGlobalsData);  // 0xE4D4A0 0xE4CE20
		DeclareAddress(sSerializer__lootTable);  // 0x16B52A0 0x16B1020
		DeclareAddress(sSerializer__cell);  // 0x16B1730 0x16AD4B0
		DeclareAddress(sSerializer__populate);  // 0x16B4D00 0x16B0A80
		DeclareAddress(sSerializer__world);  // 0x16B1650 0x16AD3D0
		DeclareAddress(sSerializer__look_table);  // 0x16B1624 0x16AD3A4
		DeclareAddress(sSerializer__random_creature);  // 0x16B16A8 0x16AD428
		DeclareAddress(sSerializer__look_algorithm);  // 0x16B52F8 0x16B1078
		DeclareAddress(sSerializer__backgroundMap);  // 0x16B52CC 0x16B104C
		DeclareAddress(sSerializer__effectMap);  // 0x16B5000 0x16B0D80
		DeclareAddress(sSerializer__powers);  // 0x16B4E64 0x16B0BE4
		DeclareAddress(sSerializer__globals);  // 0x16B4DDC 0x16B0B5C
		DeclareAddress(sSerializer__structure);  // 0x16B16D4 0x16AD454
	}

	namespace Cell
	{
#ifndef SDK_TO_GHIDRA
		/// Loads the data of a cell file reference, or returns the existing cached file.
		/// @param reference
		/// @param dst
		template <typename T>
		T* GetData(cCellDataReference_* reference, eastl::intrusive_ptr<cCellDataReference<T>>& dst) {
			return STATIC_CALL(GetAddress(Cell, GetData), T*, 
				Args(cCellDataReference_*, eastl::intrusive_ptr<cCellDataReference<T>>&),
				Args(reference, dst));
		}
#else
		void* GetData(cCellDataReference_* reference, eastl::intrusive_ptr<cCellDataReference_>& dst);
#endif
	}
}