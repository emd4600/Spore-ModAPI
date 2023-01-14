#pragma once

#include <Spore\App\cJob.h>
#include <Spore\Internal.h>

#define JobManager (*App::IJobManager::Get())

namespace App
{
#ifdef SDK_TO_GHIDRA
	class cJobThread
	{
		int todo;
	};
	class LimitStopwatch
	{
		int todo;
	};
#else
	class cJobThread;  //TODO
	class LimitStopwatch;  //TODO
#endif

	class IJobManager
	{
	public:
		/* 00h */	virtual ~IJobManager() = 0;
		/* 04h */	virtual bool Initialize() = 0;
		/* 08h */	virtual void PreShutdown() = 0;
		/* 0Ch */	virtual void Dispose() = 0;
		/* 10h */	virtual bool CreateJob(cJob*& pDst) = 0;
		/* 14h */	virtual cJobThread* CreateJobThread(int, bool, int) = 0;
		/* 18h */	virtual void DestroyJobThread(cJobThread* thread) = 0;
		/* 1Ch */	virtual bool Run(cJobThread* thread, LimitStopwatch* stopwatch = nullptr, bool = false) = 0;
		/* 20h */	virtual void Lock() = 0;
		/* 24h */	virtual void Unlock() = 0;
		/* 28h */	virtual void RaiseThreadPriorities(int priority) = 0;
		/* 2Ch */	virtual void RestoreThreadPriorities() = 0;
		/* 30h */	virtual bool CircularRef(cJob* job1, cJob* job2) = 0;
		/* 34h */	virtual bool JobsAreActive(int) = 0;
		/* 38h */	virtual void DebugDumpStatus() = 0;  // does nothing
		/* 3Ch */	virtual void DebugDumpDot(int) = 0;  // does nothing
		/* 40h */	virtual void DebugAddBackgroundScopes() = 0;  // does nothing

		static IJobManager* Get();
	};

	namespace Addresses(IJobManager)
	{
		DeclareAddress(Get);  // 0x68F980 0x68F490
	}
}