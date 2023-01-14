#pragma once

#include <Spore\Anim\IAnimWorld.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Editors\EditorCreatureController.h>
#include <Spore\Editors\EditorAnimations.h>
#include <Spore\Editors\cEditorAnimEvent.h>
#include <Spore\Object.h>
#include <EASTL\map.h>
#include <EASTL\vector.h>

#define cEditorAnimWorldPtr eastl::intrusive_ptr<Editors::cEditorAnimWorld>

namespace Editors
{
	class cEditorAnimWorld
		: public RefCountTemplate
	{
	public:
		EditorCreatureController* GetCreatureController(int creatureID);

		Anim::AnimatedCreature* GetAnimatedCreature(int creatureID);

		void DestroyCreature(int creatureID);

		void SetTargetPosition(int creatureID, struct Math::Vector3 position, bool applyNow = false, bool ignoreZ = false);

		void SetTargetAngle(int creatureID, float angle, bool applyNow = false);

	public:
		/// `.prop` files from `editorAnims~` group (0x40606300)
		/* 08h */	eastl::map<int, EditorCreatureControllerPtr> mCreatures;  //TODO not really EditorCreatureController? check sub_59C440
		/* 24h */	eastl::vector<cEditorAnimEventPtr> field_24;
		/* 38h */	IAnimWorldPtr mpAnimWorld;
		/* 3Ch */	EditorAnimationsPtr mpAnimations;
		/* 40h */	IModelWorldPtr mpModelWorld;
		/* 44h */	int mNextCreatureIndex;  // 1
	};
	ASSERT_SIZE(cEditorAnimWorld, 0x48);

	namespace Addresses(cEditorAnimWorld)
	{
		DeclareAddress(GetCreatureController);  // 0x59C820 0x59CAC0
		DeclareAddress(GetAnimatedCreature);  // 0x59C7D0 0x59CA70
		DeclareAddress(DestroyCreature);  // 0x59C440 0x59C6E0
		DeclareAddress(SetTargetPosition);  // 0x59CC60 0x59CF00
		DeclareAddress(SetTargetAngle);  // 0x59CC00 0x59CEA0
	}
}