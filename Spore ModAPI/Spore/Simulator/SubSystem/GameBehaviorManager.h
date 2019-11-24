#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cBehaviorAgent.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Clock.h>
#include <EASTL\vector.h>
#include <EASTL\list.h>

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
		/* 20h */	virtual int func20h(int, int, int, int);
		/* 24h */	virtual int func24h(int, int, int, int);
		/* 28h */	virtual void func28h();  // sets field_A0 to true
		/* 2Ch */	virtual void func2Ch();  // sets field_A0 to false
		/* 30h */	virtual void func30h();
		/* 34h */	virtual const vector<intrusive_ptr<cBehaviorAgent>>& GetAgents();
		/* 38h */	virtual bool AddAgent(cBehaviorAgent* agent);
		/* 3Ch */	virtual bool RemoveAgent(cBehaviorAgent* agent);
		/* 40h */	virtual bool HasAgent(cBehaviorAgent* agent);
		/* 44h */	virtual void func44h();

	protected:
		/* 20h */	Clock* mpStopwatch;
		/* 24h */	vector<intrusive_ptr<cBehaviorAgent>> mAgents;
		/* 38h */	list<intrusive_ptr<Object>> field_38;
		/* 44h */	vector<pair<int, intrusive_ptr<Object>>> field_44;
		/* 58h */	int field_58;  // -1
		/* 5Ch */	int field_5C;  // -1
		/* 60h */	vector<pair<int, intrusive_ptr<Object>>> field_60;
		/* 74h */	int field_74;  // -1
		/* 78h */	int field_78;  // -1
		/* 7Ch */	vector<pair<int, intrusive_ptr<Object>>> field_7C;
		/* 90h */	int field_90;  // -1
		/* 94h */	int field_94;  // -1
		/* 98h */	int field_98;
		/* 9Ch */	int field_9C;
		/* A0h */	bool field_A0;

	public:
		static cGameBehaviorManager* Get();
	};

	inline cGameBehaviorManager* GameBehaviorManager() {
		return cGameBehaviorManager::Get();
	}

	ASSERT_SIZE(cGameBehaviorManager, 0xA4);

	namespace Addresses(cGameBehaviorManager) {
		DeclareAddress(Get);
	}
}