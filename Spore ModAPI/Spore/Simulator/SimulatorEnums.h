#pragma once

#include <stdint.h>

namespace Simulator
{
	/// All the noun IDs used to identify Simulator game data classes in the game files.
	/// These IDs can be passed to the cGameNounManager to create instances of these classes,
	/// even if the class itself isn't in the SDK yet.
	enum GameNounIDs
	{
		kGameData = 0x17F243B,
		kCheatObject = 0x2A37E35,
		kMissionFetch = 0x2AFD284,
		kMissionHappinessEvent = 0x4F3BDE9,
		kMissionMakeAlly = 0x4F77499,
		kRaidPlunderEvent = 0x397BFF3,
		kRaidEvent = 0x3960C0E,
		kMissionColonize = 0x2BA2A0E,
		kMissionEradicate = 0x2F99994,
		kMissionExplore = 0x32A12F1,
		kMissionWar = 0x330FC49,
		kMissionScan = 0x347092D,
		kMissionTerraform = 0x35988F4,
		kMissionTrade = 0x2ADEDFF,
		kMissionTradeRoute = 0x447092D,
		kMissionMultiDelivery = 0x35ED8F6,
		kMissionBiosphere = 0x437444B,
		kGenericPressureEvent = 0x317AFCC,
		kMissionMultiStep = 0x4222283,
		kMissionBalance = 0x347092E,
		kMissionFindAliens = 0x347092F,
		kMissionFlight101 = 0x4222284,
		kMissionUseTool = 0x2ADEDEE,
		kMissionStory201 = 0x4222285,
		kMissionChangeArchetype = 0x4622285,
		kMissionTrackBadge = 0x4633285,
		kMissionAdventure = 0x46332A5,
		kPlayer = 0x2C21781,
		kMilitaryAttackCityOrder = 0x2E9AE6C,
		kCulturalConvertCityOrder = 0x3DF2CC5,
		kGameTerrainCursor = 0x18C40BC,
		kBuildingCityHall = 0x18EA1EB,
		kBuildingIndustry = 0x18EA2CC,
		kBuildingHouse = 0x18EB106,
		kBuildingEntertainment = 0x1A56ABA,
		kBuildingScenario = 0x70703B3,
		kTurret = 0x436F342,
		kCelestialBody = 0x38CFB6B,
		kGameBundle = 0x18C431C,
		kCulturalTarget = 0x3D5C325,
		kCity = 0x18C43E8,
		kGameBundleGroundContainer = 0x1906183,
		kVehicle = 0x18C6DE8,
		kVehicleGroupOrder = 0x2E98AB7,
		kCityWalls = 0x18C7C97,
		kCityTerritory = 0x244FB08,
		kPlaceholderColonyEditorCursorAttachment = 0x2C5C93A,
		kPlanetaryArtifact = 0x2DD8C42,
		kToolObject = 0x4E3FAB5,
		kCivilization = 0x18C816A,
		kCreatureAnimal = 0x18EB45E,
		kCreatureCitizen = 0x18EB4B7,
		kObstacle = 0x3ED8573,
		kGamePlant = 0x18C84A9,
		kFruit = 0x2C9CC91,
		kFruitGroup = 0x2E96892,
		kNest = 0x52AA6122,
		kHerd = 0x1BE418E,
		kEgg = 0x2A034CD,
		kInteractiveOrnament = 0x3A2511E,
		kGameplayMarker = 0x36BE27E,
		kOrnament = 0x18C88E4,
		kAnimalTrap = 0x61494BE,
		kTotemPole = 0x55CF865,
		kTribeFoodMat = 0x629BAFE,
		kRock = 0x2A8FB3F,
		kCommodityNode = 0x403DF5C,
		kMovableDestructibleOrnament = 0x283DDB1,
		kSolarHitSphere = 0x32F9778,
		kHitSphere = 0x2E72CAE,
		kInterCityRoad = 0x2B8A4E7,
		kTribe = 0x18C6D19,
		kTribeTool = 0x18C8F0C,
		kSpear = 0x24270C9,
		kArtilleryProjectile = 0x18C9380,
		kFlakProjectile = 0x240E3BF,
		kDefaultToolProjectile = 0x24270C5,
		kDeepSpaceProjectile = 0x24270C7,
		kSpaceDefenseMissile = 0x244D3C8,
		kDefaultBeamProjectile = 0x24630D7,
		kDefaultAoEArea = 0x4167186,
		kCulturalProjectile = 0x4F76F0D,
		kResourceProjectile = 0x5776A2C,
		kICBM = 0x49CEC61,
		kSoundLoopObject = 0x18EB641,
		kRotationRing = 0x2EE8CE8,
		kRotationBall = 0x7292112,
		kMorphHandle = 0x7A30A12,
		kTargetMorphHandle = 0x76F6E64,
		kArrowMorphHandle = 0x771AD6F,
		kSimpleRotationRing = 0x7A81829,
		kSimpleRotationBall = 0x7ABDD91,
		kPlanet = 0x3275728,
		kVisiblePlanet = 0x44462A6,
		kStar = 0x355C93A,
		kSolarSystem = 0x38CF94C,
		kSimPlanetLowLOD = 0x3572E72,
		kEmpire = 0x18EB9D2,
		kSpaceInventory = 0x21FFA3F,
		kPlayerInventory = 0x2265FDC,
		kGameDataUFO = 0x18EBADC,
		kTribeHut = 0x1E4DAAE,
		kTribePlanner = 0x3098AF98,
		kCreatureSpeciesMission = 0x1406A572,
		kCreatureTutorialMission = 0x34066DBA,
		kTribeToTribeMission = 0x5436411A,
		kFindMission = 0x14D9597F,
		kNanoDrone = 0x6EF0F11,
		kPlaceableSound = 0x74E0069,
		kPlaceableEffect = 0x7B38BA7
	};

	enum class SpaceContext : int
	{
		None = -1,
		Planet = 0,
		SolarSystem = 1,
		Galaxy = 2
	};

	/// Technology level of a planet.
	enum class TechLevel : int
	{
		None = 0,
		Creature = 1,
		Tribe = 2,
		City = 3,
		Civilization = 4,
		Empire = 5,
	};

	/// Type of a planet, used in Simulator::cPlanetRecord.
	enum class PlanetType : int
	{
		None = -1,
		AsteroidBelt = 0,
		GasGiant = 1,
		T0 = 2,
		T1 = 3,
		T2 = 4,
		T3 = 5,
		Unset = 6
	};

	/// The type of a star in a galaxy (which includes black holes, binary stars, 
	/// proto-planetary disks, and the galactic core), used in Simulator::cStarRecord.
	enum class StarType : int
	{
		None = 0,
		/// The galactic core
		GalacticCore = 1,
		/// Black holes
		BlackHole = 2,
		/// Proto-planetary disks
		ProtoPlanetary = 3,
		/// Yellow stars
		StarG = 4,
		/// Blue stars
		StarO = 5,
		/// Red stars
		StarM = 6,
		/// Binary O-O (blue-blue) star system
		BinaryOO = 7,
		/// Binary O-M (blue-red) star system
		BinaryOM = 8,
		/// Binary O-G (blue-yellow) star system
		BinaryOG = 9,
		/// Binary G-G (yellow-yellow) star system
		BinaryGG = 10,
		/// Binary G-M (yellow-red) star system
		BinaryGM = 11,
		/// Binary M-M (red-red) star system
		BinaryMM = 12
	};

	/// Used by Simulator::cCelestialBody.
	enum class cCelestialBodyType : int
	{
		None = -1,
		Star = 0,
		/// Uses effect `0x3D6F8D8`
		Comet = 2
	};

	/// Used by function cPlanetRecord::GetPerihelion()
	enum class MoonPerihelionType : int
	{
		/// The returned value is the parent perihelion minus the moon perihelion
		DifferenceWithParent = 0,
		/// The returned value is the parent perihelion
		Parent = 1,
		/// The returned value is the parent perihelion plus the moon perihelion
		SumWithParent = 2,
		/// The returned value is the moon perihelion within its orbit, so relative to the parent planet
		RelativeToParent = 3,
	};

	/// Used by Simulator::cCommEvent.
	enum class cCommEventType : int
	{
		None = -1,
		Space = 0,
		Civ = 1
	};

	/// Used by Simulator::cEmpire
	enum Archetypes
	{
		kArchetypeWarrior = 0,
		kArchetypeTrader = 1,
		kArchetypeScientist = 2,
		kArchetypeShaman = 3,
		kArchetypeBard = 4,
		kArchetypeZealot = 5,
		kArchetypeDiplomat = 6,
		kArchetypeEcologist = 7,
		kArchetypeGrob = 8,
		kArchetypePlayerWarrior = 9,
		kArchetypePlayerTrader = 10,
		kArchetypePlayerScientist = 11,
		kArchetypePlayerShaman = 12,
		kArchetypePlayerBard = 13,
		kArchetypePlayerZealot = 14,
		kArchetypePlayerDiplomat = 15,
		kArchetypePlayerEcologist = 16,
		kArchetypePlayerWanderer = 17,
		kArchetypePlayerKnight = 18,
	};

	/// Used by Simulator::cEmpire
	enum EmpireTrait
	{
		kEmpireTraitNone = 0,
		kEmpireTraitStingy = 1,
		kEmpireTraitGenerous = 2,
		kEmpireTraitAccidentProne = 3,
	};

	/// Used by Simulator::cInteractableObject
	enum OrnamentType
	{
		kOrnamentFlower = 1,
		kOrnamentBone = 2,
		kOrnamentStick = 3
	};

	/// The different states in which a mission can be (accepted, rejected, failed, etc).
	/// Used by Simulator::cMission.
	enum class MissionState : int
	{
		/// When the mission hasn't been accepted yet, and player is in the initial conversation
		Unaccepted = 0,
		/// The mission has been finished (not necessarily completed). After this, the mission is destroyed.
		Finished = 1,
		/// The player just accepted the mission, but it hasn't started yet.
		/// It calls cMission::OnMissionAccept() and immediately transitions to MissionState::Active
		Accepted = 2,
		/// The mission is currently active. While the mission is in this state, it receives calls to Update()
		Active = 3,
		/// The player has successfully completed the mission. It calls cMission::OnMissionCompleted() and immediately 
		/// transitions to MissionState::Finished, or to MissionState::StepCompleted if this is a sub-mission of a bigger mission.
		Completed = 5,
		/// The player has failed the mission.
		/// It calls cMission::OnMissionFailed() and immediately transitions to MissionState::Finished
		Failed = 6,
		/// The mission has been aborted. 
		/// It calls cMission::OnMissionAbort() and immediately transitions to MissionState::Finished
		Aborted = 7,
		/// The mission has been rejected. 
		/// It calls cMission::OnMissionReject() and immediately transitions to MissionState::Finished
		Rejected = 8,
		/// When this mission is only a step of a bigger mission, and the step gets completed
		StepCompleted = 9
	};

	/// Types of star landmarks to be searched in some missions. Used by Simulator::cStarClue.
	enum class LandmarkStarType : int
	{
		Here = 0,
		Star = 1,
		Wormhole = 2,
		BigStar = 3,
		RedStar = 4,
		ProtoPlanetaryStar = 5,
		GalacticCore = 6
	};

	/// Types of planet landmarks to be searched in some missions. Used by Simulator::cPlanetClue.
	enum class LandmarkPlanetType : int
	{
		AsteroidBelt = 0,
		GasGiant = 1,
		T0 = 2,
		T1 = 3,
		T2 = 4,
		T3 = 5
	};
	
	/// Used by Simulator::cPlanet
	enum class PlanetRepresentationMode : int
	{
		/// `mpVisiblePlanet` is set to invisible, `mpSolarHitSphere` is disabled
		Nothing = 0,
		/// `mpVisiblePlanet` is set to visible, `mpSolarHitSphere` is enabled
		VisiblePlanetAndHitSphere = 1,
		/// `mpVisiblePlanet` is set to visible, `mpSolarHitSphere` is disabled
		OnlyVisiblePlanet = 2,
		/// `mpVisiblePlanet` is set to invisible, `mpSolarHitSphere` is enabled
		OnlyHitSphere = 3,
	};

	/// Used by Simulator::cSpaceInventoryItem
	enum class SpaceInventoryItemType
	{
		/// Plants 
		Plant = 0,
		/// Non-sentient animals
		NonSentientAnimal = 1,
		/// Space tools in `spacetools~` (`0x30608F0B`) group
		Tool = 2,
		CargoSlot = 3,
		/// Objects in `spacetrading~` (`0x34D97FA`, GroupIDs::SpaceTrading_) group
		TradingObject = 4,
		/// Objects in `multiDelivery_mision_objects~` (`0x037D494E`) group
		MultiDeliveryObject = 5,
		/// Sentient animals (citizens)
		Sentient = 6,
		Unk7 = 7,
		/// cObjectInstanceInventoryItem
		ObjectInstance = 8
	};

	/// Different kinds of surfaces where a tool can hit, usde by Simulator::cSpaceToolData.
	enum SpaceToolHit
	{
		kHitCombatant = 0,
		kHitGround = 1,
		kHitWater = 2,
		kHitAir = 3
	};

	/// Different kinds of targets that a tool can shoot at, usde by Simulator::cSpaceToolData.
	enum SpaceToolTarget
	{
		/* shr 0 */	kTargetAnimal = 1,
		/* shr 1 */	kTargetA13ABC9F = 2,
		/* shr 2 */	kTargetUFO = 4,
		/* shr 3 */	kTargetVehicle = 8,
		/* shr 4 */	kTargetTurret = 0x10,
		/* shr 5 */	kTargetCity = 0x20,
		/* shr 6 */	kTargetBuilding = 0x40,
		/* shr 7 */	kTargetWorld = 0x80,
		/* shr 8 */	kTargetAir = 0x100,
		/* shr 9 */	kTargetA6663355 = 0x200,
		/* shr 10 */	//4BF0FA5A = 0x400
	};

	/// Different types of actions that a tribe can carry, used by Simulator::cTribePlanner.
	enum class TribePlanType : int
	{
		/// In tribe archetype, property `RaidPlans`
		Raid = 1,
		/// In tribe archetype, property `GiftPlans`
		Gift = 2,
		/// In tribe archetype, property `HuntPlans`
		Hunt = 3,
		/// In tribe archetype, property `GatherPlans`
		Gather = 4,
		/// In tribe archetype, property `FishPlans`
		Fish = 5,
		/// In tribe archetype, property `MatePlans`
		Mate = 6,
		/// In tribe archetype, property `CheatMemberPlans`
		CheatMember = 7,
		/// In tribe archetype, property `BuyToolsPlans`
		BuyTools = 8,
		/// In tribe archetype, property `IdlePlans`
		Idle = 9,
		/// In tribe archetype, property `StealFoodPlans`
		StealFood = 10
	};

	/// Properties of relationships between communities (tribes, civilizations, empires)
	enum RelationshipEvents
	{
		kRelationshipEventCompliment = 0x0526E4E5,
		kRelationshipEventTrade = 0x0526E4EE,
		kRelationshipEventGift = 0x0526E4F2,
		kRelationshipEventBuyCityOver = 0x0526E4F5,
		kRelationshipEventJoinedAlliance = 0x0526E4F8,
		kRelationshipEventBribeNode = 0x0526E4FB,
		kRelationshipEventInsult = 0x0526E4FE,
		kRelationshipEventHostility = 0x0526E501,
		kRelationshipEventReligion = 0x0526E504,
		kRelationshipEventBuyCityUnder = 0x0526E50A,
		kRelationshipEventDemandRejected = 0x0526E50E,
		kRelationshipEventDeclaredWar = 0x0526E512,
		kRelationshipEventUsedNuclearWeapon = 0x05776D99,
		kRelationshipEventBrokeDeal = 0x05ADB0AA,
		kRelationshipEventFoughtEnemy = 0x05DA8036,

		kRelationshipEventSpaceMissionComplete = 0x0526E519,
		kRelationshipEventSpaceMissionFailed = 0x0526E51C,
		kRelationshipEventSpaceMissionRejected = 0x0526E51D,
		kRelationshipEventSpaceMissionAborted = 0x0526E51E,
		kRelationshipEventSpaceGiveGift = 0x0526E51F,
		kRelationshipEventSpaceBreakAlliance = 0x0526E521,
		kRelationshipEventSpaceCreateAlliance = 0x0526E524,
		kRelationshipEventSpaceTradeComplete = 0x0526E527,
		kRelationshipEventSpaceTradeDeclined = 0x0526E52A,
		kRelationshipEventSpaceCityPanicked = 0x0526E52D,
		kRelationshipEventSpaceTerraformWorsened = 0x0526E531,
		kRelationshipEventSpaceTerraformImproved = 0x0526E535,
		kRelationshipEventSpaceTerraformExtinction = 0x0526E537,
		kRelationshipEventSpaceDestroyBuilding = 0x0526E53C,
		kRelationshipEventSpaceDestroyAllyUFO = 0x0526E542,
		kRelationshipEventSpaceBadToolUse = 0x0526E545,
		kRelationshipEventSpaceGoodToolUse = 0x0526E56A,
		kRelationshipEventSpaceFloodCity = 0x0526E5CF,
		kRelationshipEventSpaceAbductCitizen = 0x0526E5D4,
		kRelationshipEventSpaceStealCommodity = 0x0526E5D8,
		kRelationshipEventSpaceCheatGood = 0x0526E5DC,
		kRelationshipEventSpaceCheatBad = 0x0526E5F3,
		kRelationshipEventSpaceNewEmpireAndCTMGOwner = 0x0526E5F4,
		kRelationshipEventSpaceUpliftedCiv = 0x055165F5,
		kRelationshipEventSpaceBadSystemPurchaseOffer = 0x05590199,
		kRelationshipEventSpaceGoodSystemPurchaseOffer = 0x055901B3,
		kRelationshipEventSpaceBeNice = 0x0577909A,
		kRelationshipEventSpaceBeNasty = 0x0577909B,
		kRelationshipEventSpacePushedTooFar = 0x057B4514,
		kRelationshipEventSpaceCapturedASystem = 0x057B9100,
		kRelationshipEventSpaceWasAtWar = 0x057E4FE3,
		kRelationshipEventSpaceEmbassyBonus = 0x0580E23B,
		kRelationshipEventSpaceDestroyUFO = 0x0591F833,
		kRelationshipEventSpaceWitholdTribute = 0x0594AFFF,
		kRelationshipEventSpaceAcceptGift = 0x0594B017,
		kRelationshipEventSpaceMissionStarted = 0x05B6CE81,
		kRelationshipEventSpaceCommunicatedNice = 0x05B6CF09,
		kRelationshipEventSpacePersonalityNice = 0x05B6FCC9,
		kRelationshipEventSpacePersonalityMean = 0x05B6FCD4,
		kRelationshipEventSpaceAvoidedContact = 0x05B942D0,
		kRelationshipEventSpaceCommunicatedMean = 0x05F62736,
		kRelationshipEventSpaceStartedWar = 0x05F8A1AD,
		kRelationshipEventSpaceArchetypeNice = 0x05FF85B2,
		kRelationshipEventSpaceArchetypeMean = 0x05FF85B3,
		kRelationshipEventSpaceArchetypeMods = 0x05FF85B4,
		kRelationshipEventSpaceSuperPower = 0x0601DF2A,
		kRelationshipEventSpaceTradeRouteSpice = 0x0667AF08,
		kRelationshipEventSpaceAlliedWithGrob = 0x068B2938,
		kRelationshipEventSpaceCommittedAtrocity = 0x068B2971,

		kRelationshipEventTribeAttack = 0x0530CF00,
		kRelationshipEventTribeKill = 0x0530CF01,
		kRelationshipEventTribeRaid = 0x0530CF02,
		kRelationshipEventTribeStealBaby = 0x0530CF03,
		kRelationshipEventTribeAttackToolOrHut = 0x0530CF04,
		kRelationshipEventTribeDestroyTool = 0x0530CF05,
		kRelationshipEventTribeGift = 0x0530CF06,
		kRelationshipEventTribeSocial = 0x0530CF07,
		kRelationshipEventTribeRecruit = 0x0530CF08,
		kRelationshipEventTribeConvert = 0x0530CF09,
		kRelationshipEventTribeCheatGood = 0x0530CF0A,
		kRelationshipEventTribeCheatBad = 0x0530CF0B,
		kRelationshipEventTribeSocialPower = 0x54EAB4B3
	};

	/// Possible genres of an adventure, used by Simulator::cScenarioModeData
	enum class ScenarioGenre : uint32_t
	{
		ScenarioUnset = 0x20790816,
		ScenarioPlanet = 0x24720859,
		ScenarioGenreTemplate = 0x27818FE6,
		ScenarioGenreAttack = 0x287ADCDC,
		ScenarioGenreDefend = 0xC34C5E14,
		ScenarioGenreSocialize = 0xFB734CD1,
		ScenarioGenreExplore = 0x37FD4E0D,
		ScenarioGenreQuest = 0xC422519E,
		ScenarioGenreStory = 0xB4707F8F,
		ScenarioGenreCollect = 0x25A6EA6E,
		ScenarioGenrePuzzle = 0xE27DDAD4
	};

	enum class ScenarioPowerupType : int
	{
		MedKit = 1,
		EnergyKit = 2,
		SpeedBoost = 3,
		DamageBoost = 4,
		ArmorBoost = 5,
		Mine = 6,
		JumpPad = 7,
		Teleporter = 8,
		Spawner = 9,
		Bomb = 10,
		Gate = 11,
		KeyCard = 12,
		Grenade = 13,

		Destructible = 15,  // also used by explosive barrel
	};

	enum class ScenarioObjectType : uint32_t
	{
		ScenarioUndefined = 0x867A9EE9,
		ScenarioBuilding = 0xB10E526F,
		ScenarioCreature = 0xE34E8A60,
		ScenarioVehicle = 0x5B3D1D0D,
		ScenarioUfo = 0xD37C1045,
		ScenarioFixedObject = 0x6031C03A,
		ScenarioFixedObjectEffect = 0x7998CE71,
		ScenarioFixedObjectGameplay = 0xCF56099A,
		ScenarioFixedObjectAudio = 0xE137FF08,
		ScenarioFixedObjectCommodityNode = 0xC7FDCB1E
	};

	enum class ScenarioGfxOverrideType : int
	{
		/// No override
		Invisible = 0,
		/// Use the default model, no override
		Normal = 1,
		/// Use a custom asset specified by the player
		Disguised = 2,
	};

	enum class ScenarioGoalType : int
	{
		None = 0,
		MoveTo = 1,
		TalkTo = 2,
		Kill = 3,
		Befriend = 4,
		AllyWith = 5,
		Bring = 6,
		Collect = 7,
		Hold = 8,
		Give = 9,
		Block = 10,
		Defend = 11,
	};

	///  The different states in which an adventure can be while being played (beginning, active, completed, failed etc).
	///  Used by Simulator::cScenarioPlayMode.
	enum class ScenarioPlayModeState : int
	{
		/// When beginning adventure from the editor, it will skip the opening cinematic to immediately begin the adventure.
		EditorStart = 0,
		/// When the opening cinematic is running.
		OpeningCinematic = 1,
		/// When loading the adventure from quick play or (presumably) space stage. Opening cinematic will run.
		MissionStart = 2,
		/// The adventure is currently active.
		Active = 3,
		/// When the adventure is completed successfully, the victory cinematic will play and Spore points will be rewarded (if eligible). 
		/// If applicable, the player captain will act joyful and perhaps dance in the results screen as Spore points are rewarded to them.
		Completed = 5,
		/// If the adventure wasn't successfully cleared, the failure or death cinematic will play, depending on the type of failure. 
		/// Spore points will not be rewarded, and if applicable, the player captain will appear sad in the results screen.
		Failed = 6

	};
	/// Possible motive (health & hunger) states for a creature; what is considered "low" and "critical" depends on the `MotiveTuning` settings
	enum class CreatureMotive : int
	{
		None = 0,
		Default = 1,
		LowHunger = 2,
		CriticalHealthAndHunger = 3,
		LowHealth = 4,
		CriticalHealth = 5
	};

	/// Possible types of interactable objects, used by cInteractableObject
	enum class InteractableObjectType : int
	{
		None = 0,
		Flower = 1,
		Bone = 2,
		Stick = 3,
		Fruit = 4,
		Rock = 5,
		Unk6 = 6,
		FixedScenarioObject = 7,
	};

	/// Used by cBadgeManager, ounts how many events of a certain kind have happened, used to know when to give a badge
	enum class BadgeManagerEvent : int
	{
		ReqPlanetsColonized = 0,
		ReqAlliancesFormed = 1,
		ReqStarsExplored = 2,
		ReqPlanetsTerraformed = 3,
		ReqEmpiresMet = 4,
		ReqWarsStarted = 5,
		Unk6 = 6,
		ReqFetchMissionsComplete = 7,
		ReqEradicateMissionsComplete = 8,
		ReqEcoDisasterMissionsComplete = 9,
		ReqFoodWebsComplete = 0xA,
		ReqRaresCollected = 0xB,
		ReqBadgePointsEarned = 0xC,
		ReqTradesComplete = 0xD,
		ReqMissionsComplete = 0xE,
		ReqGrobDefeated = 0xF,
		ReqGrobAllied = 0x10,
		Flight101Complete = 0x11,
		FriendsDefended = 0x12,
		CivsPromoted = 0x13,
		CreaturesPromoted = 0x14,
		Sightseer = 0x15,
		FlightsMade = 0x16,
		AestheticTools = 0x17,
		StorybooksVisited = 0x18,
		TradeRoutes = 0x19,
		SystemsPurchased = 0x1A,
		PlanetsConquered = 0x1B,
		ToolsPurchased = 0x1C,
		Joker = 0x1D,
		ReqArchetypeSwitches = 0x1E,
	};

	/// Types of names that can be generated with cSpaceNames
	enum class SpaceNamesType : uint32_t
	{
		kPlanet = 0x07E1310A,
		kBuilding = 0x03DEE114,
		kVehicle = 0xBA1FD5AC,
		kBlackHole = 0xDEB2D943,
		kTribe = 0x055EA490,
		kCreature = 0x51AA76BB,
		kCity = 0x58F4C251,
		kStar = 0x7CAB064C
	};

	enum class SpaceGfxObjectType : int
	{
		Planet = 0,
		Moon = 1,
		GasGiant = 2,
		Star = 3
	};

	enum class PlanetTemperatureType : int
	{
		/// Temperature score is between 0.4 and 0.6
		Normal = 1,
		/// Temperature score is lower than 0.1
		VeryCold = 2,
		/// Temperature score is between 0.1 and 0.4
		Cold = 3,
		/// Temperature score is higher than 0.85
		VeryHot = 4,
		/// Temperature score is between 0.6 and 0.85
		Hot = 5,
	};

	enum class SolarSystemOrbitTemperature
	{
		/// Hot orbit, close to the sun
		Hot = 0,
		/// Normal orbit, neither too close nor too far to the sun
		Normal = 1,
		/// Cold orbit, far from the sun
		Cold = 2,
	};

	enum class UfoType
	{
		Player = 0,
		UberTurret = 1,
		Raider = 2,
		Unk3 = 3,
		Bomber = 4,
		/// Only has weapon 'abduct'
		Unk5 = 5,
		Defender = 6,
		Unk7 = 7,
		Unk8 = 8,
		Unk9 = 9,
		Unk10 = 10,
		Unk11 = 10,
	};

	enum TribeToolType
	{
		kTribeToolTypeNone = 0,
		kTribeToolTypeAttack1 = 1,
		kTribeToolTypeAttack2 = 2,
		kTribeToolTypeAttack3 = 3,
		kTribeToolTypeSocial1 = 4,
		kTribeToolTypeSocial2 = 5,
		kTribeToolTypeSocial3 = 6,
		kTribeToolTypeGather = 7,
		kTribeToolTypeFish = 8,
		kTribeToolTypeHeal = 9,
		kTribeToolTypeFirepit = 10,
		kTribeToolTypeChieftain = 11,
	};

	enum TribeToolClass
	{
		kTribeToolClassNone = 0,
		kTribeToolClassAttack = 1,
		kTribeToolClassSocial = 2,
		kTribeToolClassOther = 3,
	};

	enum TribeBundleType
	{
		kTribeBundleTypeFruit = 1,
		kTribeBundleTypeMeat = 2,
		kTribeBundleTypeFish = 3,
	};

	enum TribeInputAction
	{
		//TODO there are more

		kTribeInputActionToolAttack1 = 19,
		kTribeInputActionToolAttack2 = 20,
		kTribeInputActionToolAttack3 = 21,
		kTribeInputActionToolSocial1 = 22,
		kTribeInputActionToolSocial2 = 23,
		kTribeInputActionToolSocial3 = 24,
		kTribeInputActionToolHeal = 25,
		kTribeInputActionToolFirepit = 26,
	};

	enum CitizenAction
	{
		//TODO there are more
		kCitizenActionEat = 0,
		kCitizenActionFish = 1,
		kCitizenActionGather = 2,
		kCitizenActionGrabTool = 3,

		kCitizenActionHeal = 5,

		kCitizenActionAttack = 7,
		kCitizenActionRaid1 = 8,
		kCitizenActionGift1 = 9,
		kCitizenActionHunt = 10,
		kCitizenActionMate = 11,
		kCitizenActionParty = 12,
		kCitizenActionCollectEgg = 13,
		kCitizenActionBundle = 14,

		kCitizenActionRaid2 = 15,

		kCitizenActionFeedWild = 20,
		kCitizenActionGift2 = 21,

		kCitizenActionRepair = 24,
		kCitizenActionTame = 25,
		kCitizenActionRecruit = 26,
		kCitizenActionGatherMeat = 27,
	};

	enum HandheldItem
	{
		kHandheldItemNone = 0,
		/// trg_hunting_tool1
		kHandheldItemTrgHuntingTool1 = 1,
		/// trg_hunting_tool2
		kHandheldItemTrgHuntingTool1 = 2,
		/// trg_hunting_tool3
		kHandheldItemTrgHuntingTool1 = 3,
		/// trg_fishing_tool and related
		kHandheldItemTrgFishingTool = 4,
		/// Either trg_eating_fish or trg_fishing_tool1_fish, etc
		kHandheldItemTrgFish = 5,
		/// Either trg_eating_seaweed or trg_fishing_tool1_seaweed, etc
		kHandheldItemTrgFish = 6,
		/// trg_eating_fruit
		kHandheldItemTrgEatingFruit = 7,
		/// trg_eating_seaweed or trg_eating_fish
		kHandheldItemTrgEatingSeaweedOrFish = 8,
		/// trg_eating_meat
		kHandheldItemTrgEatingMeat = 9,
		/// trg_eating_seaweed
		kHandheldItemTrgEatingSeaweed = 10,
		/// city_protest_sign_hunger
		kHandheldItemCityProtestSignHunger = 11,
		/// trg_recruit_staff
		kHandheldItemTrgRecruitStaff = 12,
		/// trg_social_maraca
		kHandheldItemTrgSocialMaraca = 13,
		/// trg_social_horn
		kHandheldItemTrgSocialHorn = 14,
		/// trg_social_didgeridoo
		kHandheldItemTrgSocialDidgeridoo = 15,
		/// trg_gathering_treesmacker
		kHandheldItemTrgGatheringTreeSmacker = 16,
		/// trg_chieftain_staff
		kHandheldItemTrgChieftainStaff = 17,
		/// trg_healing_staff
		kHandheldItemTrgHealingStaff = 18,
		/// trg_repair_mallet
		kHandheldItemTrgRepairMallet = 19,
		/// trg_water_bucket
		kHandheldItemTrgWaterBucket = 20,
		/// 0xA8F747AE, some tribal horn
		kHandheldItemUnk21 = 21,
		/// trg_firebomb
		kHandheldItemTrgFireBomb = 22,
		/// trg_eating_egg
		kHandheldItemTrgEatingEgg = 23,
	};
}