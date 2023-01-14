#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cBehaviorAgent.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Clock.h>
#include <EASTL\vector.h>
#include <EASTL\list.h>

#define GameBehaviorManager (*Simulator::cGameBehaviorManager::Get())

namespace Simulator
{
	class cGameBehaviorManager
		: public App::IMessageListener
		, public cStrategy
	{
	public:

		/* 10h */	virtual int func10h();  // get field_9C
		/* 14h */	virtual int func14h(int);
		/* 18h */	virtual void func18h(int);
		/* 1Ch */	virtual int func1Ch(int, int, int, int);
		/* 20h */	virtual int func20h(cBehaviorBase* pBehavior, cBehaviorAgent* pTargetAgent, cBehaviorList* pOwner, int);
		/* 24h */	virtual int func24h(int, int, int, int);
		/* 28h */	virtual void func28h();  // sets field_A0 to true
		/* 2Ch */	virtual void func2Ch();  // sets field_A0 to false
		/* 30h */	virtual void func30h();
		/* 34h */	virtual const eastl::vector<cBehaviorAgentPtr>& GetAgents();
		/* 38h */	virtual bool AddAgent(cBehaviorAgent* agent);
		/* 3Ch */	virtual bool RemoveAgent(cBehaviorAgent* agent);
		/* 40h */	virtual bool HasAgent(cBehaviorAgent* agent);
		/* 44h */	virtual void func44h();

	public:
		/* 20h */	Clock* mpStopwatch;
		/* 24h */	eastl::vector<cBehaviorAgentPtr> mAgents;
		/* 38h */	eastl::list<ObjectPtr> field_38;
		/* 44h */	eastl::vector<eastl::pair<int, ObjectPtr>> field_44;
		/* 58h */	int field_58;  // -1, index to vector above
		/* 5Ch */	int field_5C;  // -1
		/* 60h */	eastl::vector<eastl::pair<int, ObjectPtr>> field_60;
		/* 74h */	int field_74;  // -1
		/* 78h */	int field_78;  // -1
		/* 7Ch */	eastl::vector<eastl::pair<int, ObjectPtr>> field_7C;
		/* 90h */	int field_90;  // -1
		/* 94h */	int field_94;  // -1
		/* 98h */	int field_98;
		/* 9Ch */	int field_9C;
		/* A0h */	bool field_A0;

	public:
		static cGameBehaviorManager* Get();
	};

	ASSERT_SIZE(cGameBehaviorManager, 0xA4);

	namespace Addresses(cGameBehaviorManager) {
		DeclareAddress(Get);
	}
}