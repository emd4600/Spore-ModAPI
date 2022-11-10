#pragma once

#include <Spore\Internal.h>

#define cJobPtr eastl::intrusive_ptr<App::cJob>

namespace App
{
	class cJob;

	typedef bool(*cJobCallback)(cJob*, void*);

	class cJob
	{
		// We only care about the methods, not the fields

		int AddRef();
		int Release();

		/// Sets the method that is called to execute this job.
		/// @param callback
		/// @param object Additional parameter that is passed to the callback method.
		void SetMethodCallback(cJobCallback callback, void* object);

		void AddDependency(cJob* other);
		void AddWeakDependency(cJob* other);

		/// Blocks the current thread until this job finishes executing.
		void Wait();

		/// Cancels the execution of the job.
		/// @param wait
		void Cancel(bool wait);

		void Resume();

		/// Sets a function that must be executed when the job finishes.
		/// @param callback Function that will be executed
		/// @param data Additional data that is passed to the function.
		void Continuation(void(*callback)(cJob*, void*), void* data);

		int GetStatus();

		void SetThreadAffinity(uint32_t affinity = 0x80000000);

	public:
		/* 00h */	cJobCallback mCallback;
		/* 04h */	void* mpCallbackObject;
		/* 08h */	char padding[0x18 - 0x8];
		/* 18h */	uint32_t mThreadAffinity;
	};

	namespace Addresses(cJob)
	{
		DeclareAddress(AddRef);  // 0x68FE20 0x68F910
		DeclareAddress(Release);  // 0x690540 0x6900E0
		DeclareAddress(AddDependency);  // 0x6915D0 0x691340
		DeclareAddress(AddWeakDependency);  // 0x691610 0x691380
		DeclareAddress(Wait);  // 0x692900 0x692670
		DeclareAddress(Cancel);  // 0x692650 0x6923C0
		DeclareAddress(Resume);  // 0x690DD0 0x690970
		DeclareAddress(Continuation);  // 0x68FE80 0x68F9B0
		DeclareAddress(GetStatus);  // 0x68FE40 0x68F930
	}
}