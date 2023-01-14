#pragma once

#include <Spore\Graphics\IModelWorld.h>

namespace Graphics
{
	class cModelWorld
		: public IModelWorld
	{
	public:
		// parameter is actually cMWLoadingModel
		void FinishBackgroundLoad(Graphics::Model**);

		void UpdateWithLODMeshes(App::PropertyList*, Graphics::cMWModelInternal*, int);
	};

	namespace Addresses(cModelWorld)
	{
		DeclareAddress(FinishBackgroundLoad);
		DeclareAddress(UpdateWithLODMeshes);
	}
}