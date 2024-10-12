#pragma once

#include <Spore\Simulator\cCommunity.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cGameBundleContainer.h>
#include <Spore\Simulator\cIdentityColorable.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\Simulator\cTribeHut.h>
#include <Spore\Simulator\cTribePlanner.h>
#include <Spore\Simulator\cTribeTool.h>
#include <Spore\Simulator\cTribeFoodMat.h>
#include <Spore\Simulator\cTotemPole.h>
#include <Spore\Simulator\cCommunityLayout.h>
#include <Spore\Simulator\cOrnament.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\array.h>
#include <EASTL\deque.h>

#define cTribePtr eastl::intrusive_ptr<Simulator::cTribe>

namespace Simulator
{
	struct cFishHotSpot
	{
		/* 00h */	Math::Vector3 mPos;
		/* 0Ch */	float mCurrentFood;
		/* 10h */	float mMaxFood;
		/* 14h */	float mResupplyRate;
		/* 18h */	eastl::array<int, 3> mCubeIndex;
		/* 24h */	cHitSpherePtr mpFishingHitSphere;
		/* 28h */	cOrnamentPtr mpFishingHotSpot;
		/* 30h */	uint64_t mStartTime;
		/* 38h */	bool mbActive;
		/* 39h */	bool mbReplenishing;
	};
	ASSERT_SIZE(cFishHotSpot, 0x40);

	struct cFishHotSpotUnk {
		/* 00h */	char padding_0[0x1C];
		/* 1Ch */	cFishHotSpot mData;
	};
	ASSERT_SIZE(cFishHotSpotUnk, 0x60);

	eastl::vector<cFishHotSpotUnk>& GetTribeFishHotSpots();

	cGonzagoTimer& GetTribeFishTimer();

	uint64_t GetTribeFishEndTime();
	void SetTribeFishEndTime(uint64_t);


	/// A tribe from the tribe stage.
	class cTribe
		/* 00h */	: public cCommunity
		/* 120h */	, public cSpatialObject
		/* 1F4h */	, public cBehaviorList
		/* 20Ch */	, public cGameBundleContainer
		/* 230h */	, public cIdentityColorable
	{
	public:
		static const uint32_t TYPE = 0x4F396A66;
		static const uint32_t NOUN_ID = 0x18C6D19;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Generates the tribe food mat and tribe members
		/* 8Ch */	virtual void SpawnTribe(const Math::Vector3& position, int numMembers, int, bool);
		/// Returns the vector with the members of the tribe
		/* 90h */	virtual eastl::vector<cCreatureCitizenPtr>& GetTribeMembers();
		/// Returns a vector of all selectable members of the tribe
		/* 94h */	virtual eastl::vector<cSpatialObjectPtr>& GetSelectableMembers();
		/* 98h */	virtual cCreatureCitizen* SpawnMember(int);
		/// Removes a member of the tribe. index seems to cause issues if not 0.
		/* 9Ch */	virtual void func9Ch(int index, bool);
		/// Calls func9Ch() with second parameter true
		/* A0h */	virtual void funcA0h(int index);
		/* A4h */	virtual int GetTotalFood();
		/* A8h */	virtual void funcA8h();
		/* ACh */	virtual cTribeHut* GetHut();
		/* B0h */	virtual cTribeHut* funcB0h();
		/* B4h */	virtual cTribeTool* CreateTool(int toolType);
		// Destroys a bunch of things
		/* B8h */	virtual void RemoveTool(cTribeTool* tribeTool);
		/* BCh */	virtual eastl::vector<cTribeToolPtr>& GetTools();
		/* C0h */	virtual eastl::vector<cTribeToolPtr>& funcC0h();

		/// Checks the mTools vector and returns the first tool that has the given tool type,
		/// or nullptr if no tool was found.
		/// @param toolType
		/// @returns
		cTribeTool* GetToolByType(int toolType);

		void UpdateFoodVisuals(float amount);

	public:
		/* 260h */	cTribeFoodMatPtr mpFoodMat;
		/* 264h */	bool mbMotiveCheatOn;
		/* 268h */	float mRSquareSize;  // 10.0
		/* 26Ch */	int field_26C;  // -1
		/* 270h */	cGonzagoTimer mVignetteTimer;
		/* 290h */	cTribePlannerPtr mpTribePlanner;
		/* 294h */	eastl::vector<int> field_294;
		/* 2A8h */	eastl::vector<int> field_2A8;
		/* 2BCh */	int field_2BC;
		/* 2C0h */	float mEggPenFoodValue;
		/* 2C4h */	float mInitialRelationship; // does not seem to change from 0
		/* 2C8h */	float mChieftainRespawnTimer;
		/* 2CCh */	float mGiftRelationshipDecayTimer;
		/* 2D0h */	ObjectPtr field_2D0;
		/* 2D4h */	ObjectPtr field_2D4;
		/* 2D8h */	int field_2D8; 
		/* 2DCh */	int field_2DC;  // not initialized
		/* 2E0h */	int field_2E0;  // not initialized
		/* 2E4h */	int field_2E4;  // not initialized
		/* 2E8h */	int field_2E8;  // not initialized
		/* 2ECh */	int field_2EC;  // not initialized
		/* 2F0h */	int field_2F0;  // not initialized
		/* 2F4h */	int field_2F4;  // not initialized
		/* 2F8h */	int field_2F8;  // not initialized
		/* 2FCh */	int field_2FC;  // not initialized
		/* 300h */	bool mbCheckedForWater;
		/* 301h */	bool mbCheckedForForests;
		/// Coordinates in the planet of the source of water closest to the tribe.
		/* 304h */	Vector3 mClosestWater;
		/// Distance from tribe to `mClosestWater`
		/* 310h */	float mClosestWaterDistance;
		/* 314h */	eastl::vector<Vector3> mClosestForests;
		/* 328h */	int field_328;  // not initialized
		/* 32Ch */	int mUpgradeLevel; // may be a uint32 or have errors?
		/* 330h */	float mZoningRadius;  // 30.0
		/* 334h */	bool mbRoboTribe;
		/* 338h */	int mRoboPopulationCount;
		/* 33Ch */	bool mbVisualized;
		/* 340h */	eastl::vector<cCreatureCitizenPtr> mTribeMembers;
		/* 354h */	eastl::vector<cSpatialObjectPtr> mSelectableMembers;
		/* 368h */	cTribeHutPtr mpHut;
		/* 36Ch */	eastl::vector<cTribeToolPtr> mTools;
		/* 380h */	eastl::vector<cTribeToolPtr> mSocialTools;
		/* 394h */	eastl::hash_map<int, cCommunityLayout> field_394;
		/* 3B4h */	cCommunityLayout mTribeLayout;
		/* 418h */	eastl::fixed_vector<int, 45> field_418;
		/* 4E4h */	eastl::hash_map<int, eastl::deque<ObjectPtr>> field_4E4;
		/* 504h */	int field_504;  // not initialized
		/* 508h */	int field_508;  // not initialized
		/* 50Ch */	int field_50C;  // not initialized
		/* 510h */	cGonzagoTimer mPopulationTimer;
		/* 530h */	cGonzagoTimer mTimer;
		/* 550h */	int mTribeArchetype;  //TODO
		/* 554h */	bool field_554;
		/* 555h */	bool field_555;
		/* 556h */	bool mbMembersFlee; // if true, creatures run away in fear and die
		/* 557h */	bool mGoodyPopped;
		/* 558h */	char _padding_558[0x1310];
		/* 1868h */	int field_1868;
		/* 186Ch */	int field_186C;
		/* 1870h */	int field_1870;
		/* 1874h */	int field_1874;  // -1
		/* 1878h */	bool field_1878;
		/* 1879h */	bool field_1879;
		/* 187Ch */	int field_187C;  // not initialized
		/* 1880h */	int field_1880;
		/* 1884h */	int field_1884;
		/* 1888h */	int field_1888;
		/* 188Ch */	int field_188C;  // -1
		/* 1890h */	bool field_1890;
		/* 1891h */	bool field_1891;
		/* 1894h */	int field_1894;  // not initialized
		/* 1898h */	int field_1898;
		/* 189Ch */	int field_189C;
		/* 18A0h */	int field_18A0;
		/* 18A4h */	int field_18A4;  // -1
		/* 18A8h */	bool field_18A8;
		/* 18A9h */	bool field_18A9;
		/* 18ACh */	uint32_t field_18AC;  // not initialized
		/* 18B0h */	int field_18B0;
		/* 18B4h */	int field_18B4;
		/* 18B8h */	int field_18B8;
		/* 18BCh */	int field_18BC;  // -1
		/* 18C0h */	bool field_18C0;
		/* 18C1h */	bool field_18C1;
		/* 18C4h */	int field_18C4;  // not initialized
		/* 18C8h */	int field_18C8;
		/* 18CCh */	char field_18CC[0x38];  // 18CC is array of cSpeciesProfile* ?
		/* 1904h */	eastl::fixed_vector<ResourceKey, 14> mSpeciesKeys;
		/* 19C4h */	cOrnamentPtr mpDomesticatedAnimalsPen;
		/* 19C8h */ cOrnamentPtr mpEggPen;
		/* 19CCh */	cGameDataPtr mpDomesticatedAnimalsHerd;  //TODO
		/* 19D0h */	cTotemPolePtr mpTotemPole;
		/* 19D4h */	uint32_t mhFootprint;
		/* 19D8h */	int mPurchasedTools;
	};
	ASSERT_SIZE(cTribe, 0x19E0);

	namespace Addresses(cTribe) {
		DeclareAddress(GetToolByType);  // 0xC8ED20 0xC8F870
		DeclareAddress(SpawnMember);  // 0xC97BA0 0xC983C0
		DeclareAddress(CreateTool);  // 0xC95950 0xC96170
		DeclareAddress(RemoveTool);  // 0xC96800 0xC97020
		DeclareAddress(UpdateFoodVisuals);  // 0xC94520 0xC94CE0
	}

	cTribe* SpawnNpcTribe(const Math::Vector3& position, int tribeArchetype, int numMembers, int foodAmount, bool, cSpeciesProfile* species);
}

namespace Addresses(Simulator) {
	DeclareAddress(SpawnNpcTribe);  // 0xC92860 0xC932F0
	DeclareAddress(sTribeFishHotSpots_ptr);  // 0x157EB90 0x157ABB0
	DeclareAddress(sTribeFishTimer_ptr);  // 0x1699678 0x16953F8
	DeclareAddress(sTribeFishEndTime_ptr);  // 0x16995E8 0x1695368
}