#pragma once

#include <Spore\ResourceKey.h>
#include <Spore\LocalizedString.h>
#include <EASTL\vector.h>

#define IEditorLimitsPtr eastl::intrusive_ptr<Editors::IEditorLimits>
#define StdEditorLimitsPtr eastl::intrusive_ptr<Editors::StdEditorLimits>

namespace Editors
{
	class IEditorLimits
	{
	public:
		virtual ~IEditorLimits();

		int AddRef();
		int Release();

		/* 04h */	virtual int GetValue(int index);
		/* 08h */	virtual int func08h(const ResourceKey& key);
		/* 0Ch */	virtual bool HasEnough(int index, int value);
		/* 10h */	virtual int func08h(const ResourceKey& key, LocalizedString* pText);
		/* 14h */	virtual bool func14h(int);
		/* 18h */	virtual void SetLimit(int index, int value);

	private:
		int mnRefCount;
	};

	class StdEditorLimits : public IEditorLimits
	{
	public:
		enum EditorLimitType {
			kBudget = 0,
			kComplexity = 1
		};

		/// Limits the value at the given index so that it's not greater than the limit.
		/* 1Ch */	virtual void EnsureLimit(int index);
		/// Adds a certain amount to the value of the given index. The total value will be capped at its limit.
		/// A message of type `0x3150C27` will be sent
		/* 20h */	virtual void AddValue(int index, int value);
		/// Sets a certain value of the given index. The total value will be capped at its limit.
		/// A message of type `0x3150C27` will be sent
		/* 24h */	virtual void SetValue(int index, int value);
		/* 28h */	virtual bool func28h(int);
		/* 2Ch */	virtual void func2Ch(int);
		/* 30h */	virtual void func30h(int);
		/* 34h */	virtual bool func34h(int);
		/* 38h */	virtual void func38h(int, int);

		/* 08h */	eastl::vector<int> mValues;
		/* 1Ch */	eastl::vector<int> mLimits;
	};
	ASSERT_SIZE(StdEditorLimits, 0x30);
}