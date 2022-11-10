/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once

#include <Spore\Resource\IResourceFactory.h>
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\Resource\IResourceMap.h>
#include <Spore\Resource\DatabasePackedFile.h>

#include <EASTL\list.h>

/// Access the active resource manager.
#define ResourceManager (*Resource::IResourceManager::Get())

#define IResourceManagerPtr eastl::intrusive_ptr<Resource::IResourceManager>

namespace Resource
{
	///
	/// IResourceManager is a singleton class used to access resources in Spore's file system.
	///
	/// The main function of the ResourceManager is to access to the resources stored in Spore's files. The manager contains multiple 
	/// IResourceFactory instances, which are assigned to certain typeIDs. When trying to get a resource, those factories will be used
	/// to generate an instance of the correct class according to the resource type. Therefore, the ResourceManager can only be used for those
	/// types that have factories assigned to them.
	///
	/// You can assign your own factories or delete existing ones, but if that is not an option, ResourceManager provides a method to find
	/// the DatabasePackedFile that contains a certain file. This way, ResourceManager can always be used to get files, either via the GetResource
	/// method or the GetDBPF one. The DBPFs are stored in the resource manager according to their priority.
	///
	/// The manager contains a cache of IResourceMap instances that is used to avoid repeteadly creating new instances of a resource that
	/// already exists. The ReadResource method can be used instead of GetResource to forcibly create a new resource even if it's already
	/// in the cache.
	/// 
	/// This manager provides additional functionality relating files. It keeps a map of ResourceKey - string16 values, which can be used
	/// to store the original name of certain resources. For example:
	/// ~~~~~~~~~~~~~~~~~~~~~~{.cpp}
	/// ResourceManager.SetFileName(ResourceKey(0x00000000, 0x40212002, 0x0469A3F7), u"ShaderFragments!LowQuality.graphics");
	/// // Now you can access this file using the name we assigned instead of the original name, which had special IDs
	/// ResourceManager.GetFileName(dstKey, u"ShaderFragments!LowQuality.graphics");
	/// ~~~~~~~~~~~~~~~~~~~~~~
	///
	/// Additionally, the manager also keeps a map of typeID - string16 values, which allows to map extension strings to certain typeIDs.
	/// For example:
	/// ~~~~~~~~~~~~~~~~~~~~~~{.cpp}
	/// // for example, we could have the mappings on a file and load it on startup
	/// ResourceManager.AddExtensionMapping(0x2F7D0004, u"png");
	/// // now, if we try to use the .png extension, we will receive the correct typeID, instead of using the FNV hash of "png" (which is not 0x2F7D0004)
	/// ResourceManager.GetFileName(dstKey, u"MyImages!EditorUIFrame.png");
	/// ~~~~~~~~~~~~~~~~~~~~~~
	///
	class IResourceManager
	{

	public:

		typedef list<DatabasePackedFile*, CoreAllocatorAdapter<ICoreAllocator>> DBPFList;

		/* 00h */	virtual ~IResourceManager();
		/* 04h */	virtual bool Initialize() = 0;
		/* 08h */	virtual bool Dispose() = 0;

		///
		/// Gets the resource that has the given ResourceKey name. 
		/// If the resource is contained in the cache, that will be used.
		/// The name will be modified to use the correct types, according to the mappings in this manager.
		/// The resource will be seached in all the DBPF files in this manager, unless a specific one is specified.
		/// Once the file is found, the correct factory will be used to generate the appropiate resource, unless
		/// a specific IResourceFactory is specified.
		///
		/// @param[in] name The ResourceKey name to find. If the typeID is mapped in the manager to other alternative typeIDs, all them will be tested.
		/// @param[out] ppDst [Optional] A pointer to a ResourceObject*. It will be assigned with the generated resource.
		/// @param arg_8 [Optional] Usage unknown, usually 0.
		/// @param[in] pDBPF [Optional] The DatabasePackedFile where the file will be searched. Use nullptr to search in all DBPFs in this manager.
		/// @param[in] pFactory [Optional] The IResourceFactory used to generate the resource. Use nullptr to use the appropiate factory according to the typeID mapping in this manager.
		/// @param[in] pCacheName [Optional] The ResourceKey name used to search the resource in the cache.
		/// @returns True if the resource was found or generated, false otherwise.
		///
		/* 0Ch */	virtual bool GetResource(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr,
			int arg_8 = 0,
			DBPF* pDBPF = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pCacheName = nullptr) = 0;

		///
		/// Similar usage to ResourceManager::GetResource . This method allows to get more info,
		/// but it is unknown what that info is.
		///
		/* 10h */	virtual bool GetAsyncResource(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr,
			AsyncResourcePtr* ppDstAsync = nullptr,
			void* arg_C = nullptr,
			void* arg_10 = nullptr,
			DBPF* pDBPF = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pAlternativeName = nullptr) = 0;

		///
		/// Gets a resource from the resource cache in this manager. If it isn't present in the cache,
		/// nothing will happen.
		/// @returns True if the file was present in the cache, false otherwise.
		///
		/* 14h */	virtual bool GetCachedResource(const ResourceKey& name, ResourceObjectPtr* pDst) = 0;

		/* 18h */	virtual bool func18h(int arg_0, int arg_4, int arg_8, int arg_C, int arg_10) = 0;

		///
		/// Similar usage to ResourceManager::GetResource . This method does not check the cache, however,
		/// therefore always generating a new resource.
		/// @returns True if the resource was successfully generated and read, false otherwise.
		///
		/* 1Ch */	virtual bool ReadResource(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr,
			int arg_8 = 0,
			DBPF* pDBPF = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pCacheName = nullptr) = 0;

		///
		/// Writes the given resource to a package file. If the DBPF is specified in this method, a new file will
		/// always be created on it even if it does not exist yet; however, if no DBPF is specified, the resource
		/// will be written in the first DBPF that contains a file with the given name.
		/// If there is a problem while writing the resource, the file on the DBPF will be deleted.
		///
		/// @param pResource[in] The ResourceObject to write. It will be written according to the IResourceFactory specified or the one that corresponds to the typeID.
		/// @param arg_4 [Optional] Usage unknown, usually 0.
		/// @param pDBPF[in] [Optional] The DatabasePackedFile where the resource will be written.
		/// @param pFactory[in] [Optional] The IResourceFactory that will be used to write the resource. Use nullptr to use the one that corresponds to the resource's typeID.
		/// @param pNameKey[in] [Optional] The ResourceKey that must be used as the name. If nullptr, the name of the resource will be used.
		/// @returns True if the resource was successfuly written, false otherwise.
		///
		/* 20h */	virtual bool WriteResource(
			const ResourceObject* pResource,
			int arg_4 = 0,
			DBPF* pDBPF = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pNameKey = nullptr) = 0;

		///
		/// Maps all the alternative typeIDs in pnTypes (which has nCount values) to nTypeID.
		///
		/* 24h */	virtual void SetTypeRemap(uint32_t nTypeID, uint32_t* pnTypes, size_t nCount) = 0;

		///
		/// Gets all the alternative typeIDs mapped to nTypeID.
		/// @returns The number of alternative typeIDs mapped.
		///
		/* 28h */	virtual size_t GetTypeRemap(vector<uint32_t>& dst, uint32_t nTypeID) const = 0;

		///
		/// Gets the typeID that nSubtypeId is assigned to.
		///
		/* 2Ch */	virtual uint32_t GetGeneralTypeID(uint32_t nSubtypeID) const = 0;

		///
		/// Used to get the real name of a file ResourceKey, using the correct type according to the mappings in this manager.
		/// @param[in] nameKey The original ResourceKey of the file.
		/// @param[out] pDst [Optional] The ResourceKey where the real key of the file will be put, with the correct typeID.
		/// @param[in] pDBPF [Optional] The DatabasePackedFile where the file will be searched. If not specified, it will be searched in all the DBPFs in this manager.
		/// @returns The DatabasePackedFile that contains this file.
		///
		/* 30h */	virtual DBPF* GetRealFileKey(const ResourceKey& nameKey, ResourceKey* pDst = nullptr, DBPF* pDBPF = nullptr) const = 0;

		/* 34h */	virtual size_t func34h(vector<ResourceKey>& pDst, int arg_4) = 0;

		///
		/// Gets all the file keys in this manager that match the criteria specified by the given request. If request is nullptr,
		/// all the files in the manager will be added.
		/// @param[out] dst The vector where all the files ResourceKey names will be added.
		/// @param[in] request The criteria that the files must match in order to be added to the vector.
		/// @param[out] pDstDBPFs [Optional] A vector where all the DatabasePackedFile objects that contained the files will be added.
		/// @returns The number of file keys that matched the criteria.
		///
		/* 38h */	virtual size_t GetFileKeys(vector<ResourceKey>& dst, IResourceFilter* request, vector<DBPF*>* pDstDBPFs = nullptr) const = 0;

		/* 3Ch */	virtual int func3Ch(int, int, int) = 0;
		/* 40h */	virtual bool func40h(int, int, int, int, int) = 0;

		///
		/// Adds or removes the given IResourceFactory to this manager. Resource factories are used to generate resource objects depending on
		/// their type. The factory will be assigned to the types returned by IResourceFactory::GetSupportedTypes.
		/// @param add If true, pFactory will be added to the manager; if false, it will be removed from the manager.
		/// @param pFactory The IResourceFactory to add to/remove from this manager.
		/// @param arg_8 Unknown usage, usually 0.
		/// @returns True if the factory was successfully added/removed, false otherwise.
		///
		/* 44h */	virtual bool SetResourceFactory(bool add, IResourceFactory* pFactory, uint32_t arg_8) = 0;

		///
		/// Returns the IResourceFactory that belongs to the specified \c typeID. 
		/// If \c subTypeID is ResourceKey::kWildcardID, the first factory assigned to the \c typeID will be returned;
		/// Otherwise, IResourceFactory::IsValid() will be called on every factory using the types provided here,
		/// and the first one that returns true will be returned.
		///
		/* 48h */	virtual IResourceFactory* GetResourceFactory(uint32_t typeID, uint32_t subTypeID = ResourceKey::kWildcardID) const = 0;

		///
		/// Puts all the IResourceFactory instances that are assigned to the specified \c typeID into the given list.
		/// If \c typeID is ResourceKey::kWildcardID, all the factories in this manager will be added.
		/// @returns The number of factories found.
		///
		/* 4Ch */	virtual size_t GetResourceFactories(list<IResourceFactory*>& dst, uint32_t typeID = ResourceKey::kWildcardID) const = 0;

		///
		/// Adds the given DatabasePackedFile to this manager, using the priority specified.
		/// The priority of a DBPF is used when getting files from the resource manager;
		/// since a certain file name can be contained in multiple packages, the one with the
		/// most priority will be chosen.
		/// The usage of the first argument is unknown, but it is usually 'true'.
		///
		/* 50h */	virtual bool AddDBPF(bool, Database* pDBPF, int nPriority) = 0;

		///
		/// Gets the priority of the given DatabasePackedFile if it is contained in this ResourceManager.
		/// This method can also be used to check if a DBPF is added or not in this list.
		/// @param[in] pDBPF The DatabasePackedFile from which the priority will be got.
		/// @param[out] [Optional] A pointer to an integer that will contain the priority. This parameter can be nullptr.
		/// @returns True if the manager contained the DBPF, false otherwise.
		///
		/* 54h */	virtual bool GetPriority(DatabasePackedFile* pDBPF, int* pDst = nullptr) const = 0;

		///
		/// Returns the first DatabasePackedFile that contains the given 
		///
		/* 58h */	virtual DatabasePackedFile* GetDBPF(const ResourceKey& name) const = 0;

		///
		/// Gets all the DatabasePackedFile objects in this manager and puts it to the dst list. 
		/// Optionally, a ResourceKey can be specified; in that case, only the DBPFs that contain that file will be added.
		/// @param[out] dst A list of DBPF pointers that uses CoreAllocatorAdapter<ICoreAllocator> where the DBPFs will be added.
		/// @param[in] pFileKey [Optional] A ResourceKey that the DBPFs must contain, or nullptr if no filtering is wanted.
		/// @returns The number of DBPFs added to the list.
		///
		/* 5Ch */	virtual size_t GetAllDBPFs(DBPFList& dst, const ResourceKey* pFileKey = nullptr) = 0;

		/* 60h */	virtual int func60h(int, int) = 0;
		/* 64h */	virtual bool func64h(int, int, int) = 0;

		///
		/// Returns the IResourceMap cache that contains a resource with this name (if any).
		///
		/* 68h */	virtual IResourceMap* GetResourceCache(ResourceKey& name) const = 0;

		/* 6Ch */	virtual bool func6Ch(int, int) = 0;
		/* 70h */	virtual void func70h(IResourceMap*, CachedResourceObject*) = 0;

		///
		/// Puts all the resource caches used in this manager into the given list.
		/// @returns the number of caches added.
		///
		/* 74h */	virtual size_t GetResourceCaches(list<IResourceMap*>& dst) const = 0;

		///
		/// Adds this file name to the list, so that it can be accessed using the corresponding ResourceKey.
		/// The file name is in the format "groupID!instanceID.typeID", and it will be mapped to the
		/// key generated using the ResourceKey::Parse function.
		/// @returns True if the file name was mapped successfully, false otherwise.
		///
		/* 78h */	virtual bool AddFileName(const char16_t* pFileName) = 0;

		///
		/// Gets the file name that corresponds to the specified ResourceKey.
		/// The file name will be in the format "groupID!instanceID.typeID".
		/// The file name can be parsed to a key again using the ResourceKey::Parse method.
		/// A file name wil be generated even if it's not mapped; when that happens, the ResourceKey members are displayed in hexadecimal format.
		/// @param[in] resourceKey The ResourceKey that will be represented as a string.
		/// @param[out] dst A string16 that will contain the resulting text. 
		///
		/* 7Ch */	virtual void GetFileName(const ResourceKey& resourceKey, string16& dst) const = 0;

		///
		/// Maps the given ResourceKey to the file name specified, which is in the format "groupID!instanceID.typeID".
		/// The file name can be parsed to a key again using the ResourceKey::Parse method.
		/// @returns True if it was successfully mapped.
		///
		/* 80h */	virtual bool SetFileName(const ResourceKey& resourceKey, const char16_t* pFileName) = 0;

		///
		/// Removes the file name mapped for the given ResourceKey.
		/// The file name can be parsed to a key again using the ResourceKey::Parse method.
		/// @returns True if the file name mapping was removed, false if it did not exist.
		///
		/* 84h */	virtual bool RemoveFileName(const ResourceKey& resourceKey) = 0;

		///
		/// Returns the typeID that has the given extension mapped to it, or (uint32_t)-1 (so 0xFFFFFFFF) if no typeID has this extension mapped.
		///
		/* 88h */	virtual uint32_t GetTypeID(const char16_t* pExtension) const = 0;

		///
		/// Returns the extension that is mapped to the given type ID, or nullptr if there's no mapping.
		///
		/* 8Ch */	virtual char16_t* GetExtension(uint32_t typeID) const = 0;

		///
		/// Maps the given typeID (as a uint32_t hash) to the specified extension string. 
		/// @returns True if the extension was successfully mapped or already existed, false if the typeID was mapped to a different extension.
		///
		/* 90h */	virtual bool AddExtensionMapping(uint32_t typeID, const char16_t* pExtension) = 0;

		///
		/// Removes the given typeID (as a uint32_t hash) and the extension it is mapped to.
		/// @returns True if the extension existed and was removed, false otherwise.
		///
		/* 94h */	virtual bool RemoveExtensionMapping(uint32_t typeID) = 0;


		///
		/// Gets the active resource manager.
		///
		static IResourceManager* Get();

	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	///////////////////////////////////


	namespace Addresses(IResourceManager)
	{
		DeclareAddress(Get);
	}
}