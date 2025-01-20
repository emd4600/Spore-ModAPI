#pragma once

#include <Spore\Sporepedia\OTDBParameters.h>

#define ObjectTemplateDB (*Sporepedia::OTDB::cObjectTemplateDB::Get())

namespace Sporepedia
{
	namespace OTDB
	{
		class ISummarizer
			: public DefaultRefCounted
		{
		public:
			/* 10h */	virtual uint32_t GetID() const = 0;
			/* 14h */	virtual int GetAMTuningVersion() const = 0;
			/* 18h */	virtual int GetAssetTypesCount() const = 0;
			/* 1Ch */	virtual uint32_t GetAssetType(int index) const = 0;
			/* 20h */	virtual bool SetParameters(const ResourceKey& key, eastl::vector<Parameter>& dst) = 0;
		};

		class cObjectTemplateDB
			: public Object
		{
		public:
			/* 10h */	virtual bool Initialize();
			/* 14h */	virtual bool Dispose();
			/* 18h */	virtual bool Write(bool, bool writeSummarizers);
			/* 1Ch */	virtual bool func1Ch();
			/* 20h */	virtual void func20h();
			/* 24h */	virtual bool func24h(eastl::vector<ResourceKey>& dstKeys, int, const eastl::vector<QueryParameter>& parameters);
			/* 28h */	virtual bool func28h(int, int, int);
			/* 2Ch */	virtual void FindObjects(eastl::vector<ResourceKey>& dst, const eastl::vector<QueryParameter>& parameters);
			//TODO thse functions are placeholders
			/* 30h */	virtual int func30h();
			/* 34h */	virtual int func34h();
			/* 38h */	virtual int func38h();
			/* 3Ch */	virtual int func3Ch();
			/* 40h */	virtual int func40h();
			/* 44h */	virtual int func44h();
			/* 48h */	virtual int func48h();
			/* 4Ch */	virtual int func4Ch();
			/* 50h */	virtual int func50h();
			/* 54h */	virtual int func54h();
			/* 58h */	virtual int func58h();
			/* 5Ch */	virtual int func5Ch();
			/* 60h */	virtual int func60h();
			/* 64h */	virtual int func64h();
			/* 68h */	virtual int func68h();
			/* 6Ch */	virtual int func6Ch();
			/* 70h */	virtual int func70h();
			/* 74h */	virtual int func74h();
			/* 78h */	virtual int func78h();

			/* 7Ch */	virtual void AddSummarizer(ISummarizer* pSummarizer);

			static cObjectTemplateDB* Get();
		};

		namespace Addresses(cObjectTemplateDB)
		{
			DeclareAddress(Get);
		}
	}
}