#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cGameBundleContainer.h>

#define BundleManager (*Simulator::cBundleManager::Get())

namespace Simulator
{
	class cBundleManager
		: public cStrategy
	{
	public:
		static cBundleManager* Get();

		/// Creates one or more bundles of the given type and adds them to the container.
		/// The number of bundles created depends on the 'amount' and how much value each bundle
		/// can contain, which depends on the container.
		/// @param amount
		/// @param container
		/// @param bundleType
		/// @returns The last bundle created
		cGameBundle* CreateBundles(float amount, cGameBundleContainer* container, int bundleType);

		/// Removes a certain quantity from a bundle container. This will remove as many bundles as necessary,
		/// and change the value of the last remaining bundle. If the amount is small enough, no bundle may be deleted.
		/// @param amount
		/// @param container
		/// @param bundle If not null, removes only that specific bundle
		/// @returns The actual amount that has been removed.
		float RemoveBundles(float amount, cGameBundleContainer* container, cGameBundle* bundle = nullptr);

	public:
		/* 1Ch */	void* mpGroundContainer;  //TODO cGameBundleGroundContainerPtr
	};
	ASSERT_SIZE(cBundleManager, 0x20);

	namespace Addresses(cBundleManager) {
		DeclareAddress(Get);  // 0xB3D210 0xB3D3B0
		DeclareAddress(CreateBundles);  // 0xAC7810 0xAC79F0
		DeclareAddress(RemoveBundles);  // 0xAC7A70 TODO
	}
}