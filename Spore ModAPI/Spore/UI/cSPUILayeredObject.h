#pragma once

#include <Spore\Object.h>
#include <Spore\Transform.h>
#include <Spore\App\cViewer.h>
#include <Spore\UTFWin\IWinProc.h>

#define cSPUILayeredObjectPtr eastl::intrusive_ptr<UI::cSPUILayeredObject>

namespace UI
{
	class cSPUILayeredObject
		: public DefaultRefCounted
	{
	public:
		App::cViewer* GetViewer() const;

	protected:
		/* 08h */	App::cViewer* mpViewer;
		/* 0Ch */	int field_C;
		/* 10h */	IWinProcPtr mpObjectWindowProc;
		/* 14h */	eastl::vector<int> field_14;
		/* 28h */	int field_28;
		/* 2Ch */	Transform field_2C;
		/* 64h */	float field_64;
		/* 68h */	float field_68;
		/* 6Ch */	float field_6C;
		/* 70h */	float field_70;
		/* 74h */	bool field_74;
		/* 75h */	bool field_75;
		/* 76h */	bool field_76;
		/* 77h */	bool field_77;
		/* 78h */	bool field_78;  // true
	};
	ASSERT_SIZE(cSPUILayeredObject, 0x7C);

	inline App::cViewer* cSPUILayeredObject::GetViewer() const {
		return mpViewer;
	}
}