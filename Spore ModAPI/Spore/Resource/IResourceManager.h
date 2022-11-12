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
#include <Spore\Resource\IKeyFilter.h>
#include <Spore\Resource\ICache.h>
#include <Spore\Resource\Database.h>

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
	/// The manager distinguishes two different kinds of type IDs: the *resource type* and the *record type*. Record types are the type IDs
	/// you find in files, such as `.rw4`, `.prop`, etc. Resource types are used to differentiate between different kinds of ResourceObject;
	/// for example, `.raster` and `.rw4` are assigned to the same resource type.
	///
	/// You can assign your own factories or delete existing ones, but if that is not an option, ResourceManager provides a method to find
	/// the DatabasePackedFile that contains a certain file. This way, ResourceManager can always be used to get files, either via the GetResource
	/// method or the GetDBPF one. The DBPFs are stored in the resource manager according to their priority.
	///
	/// The manager contains a list of ICache instances that is used to avoid repeteadly creating new instances of a resource that
	/// already exists. The IResourceManager::GetPrivateResource() method can be used instead of IResourceManager::GetResource() to forcibly create a new resource even if it's already
	/// in the cache.
	/// 
	/// This manager provides additional functionality relating files. It keeps a map of ResourceKey - eastl::string16 values, which can be used
	/// to store the original name of certain resources. For example:
	/// ~~~~~~~~~~~~~~~~~~~~~~{.cpp}
	/// ResourceManager.SetKeyName(ResourceKey(0x00000000, 0x40212002, 0x0469A3F7), u"ShaderFragments!LowQuality.graphics");
	/// // Now you can access this file using the name we assigned instead of the original name, which had special IDs
	/// ResourceKey dstKey = ResourceManager.GetKeyFromName(u"ShaderFragments!LowQuality.graphics");
	/// ~~~~~~~~~~~~~~~~~~~~~~
	///
	/// Additionally, the manager also keeps a map of typeID - eastl::string16 values, which allows to map extension eastl::strings to certain typeIDs.
	/// For example:
	/// ~~~~~~~~~~~~~~~~~~~~~~{.cpp}
	/// // for example, we could have the mappings on a file and load it on startup
	/// ResourceManager.SetTypename(0x2F7D0004, u"png");
	/// // now, if we try to use the .png extension, we will receive the correct typeID, instead of using the FNV hash of "png" (which is not 0x2F7D0004)
	/// ResourceKey dstKey = ResourceManager.GetFileName(u"MyImages!EditorUIFrame.png");
	/// ~~~~~~~~~~~~~~~~~~~~~~
	///
	class IResourceManager
	{

	public:
		typedef void(*ChangeNotificationCallback_t)(Database*, const ResourceKey&, void*);
		typedef eastl::list<Database*, ICoreAllocatorAdapter> DatabaseList;

		/* 00h */	virtual ~IResourceManager();
		/* 04h */	virtual bool Initialize() = 0;
		/* 08h */	virtual bool Dispose() = 0;

		/// Gets the resource that has the given ResourceKey name. 
		/// If the resource is contained in the cache, that will be used.
		/// The name will be modified to use the correct types, according to the mappings in this manager.
		/// The resource will be seached in all the DBPF files in this manager, unless a specific one is specified.
		/// Once the file is found, the correct factory will be used to generate the appropiate resource, unless
		/// a specific IResourceFactory is specified.
		///
		/// @param[in] name The ResourceKey name to find. If the typeID is mapped in the manager to other alternative typeIDs, all them will be tested.
		/// @param[out] ppDst [Optional] A pointer to a ResourceObject*. It will be assigned with the generated resource.
		/// @param[in] factoryData [Optional] Additional data that is passed to the resource factory, usually null.
		/// @param[in] pDatabase [Optional] The Database where the file will be searched. Use nullptr to search in all available databases.
		/// @param[in] pFactory [Optional] The IResourceFactory used to generate the resource. Use nullptr to use the appropiate factory according to the typeID mapping in this manager.
		/// @param[in] pCacheName [Optional] The ResourceKey name used to search the resource in the cache.
		/// @returns True if the resource was found or generated, false otherwise.
		/* 0Ch */	virtual bool GetResource(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr,
			void* factoryData = nullptr,
			Database* pDatabase = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pCacheName = nullptr) = 0;

		/// Similar usage to ResourceManager::GetResource(), but this method returns inmediately and loads the resource 
		/// asynchronously.
		/// @param[in] name
		/// @param[out] ppDst
		/// @param[out] ppDstAsync
		/// @param[in] arg_C
		/// @param[in] factoryData
		/// @param[in] pDatabase
		/// @param[in] pFactory
		/// @param[in] pCacheName
		/// @returns
		/* 10h */	virtual bool GetResourceAsync(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr,
			IAsyncRequestPtr* ppDstAsync = nullptr,
			void* arg_C = nullptr,
			void* factoryData = nullptr,
			Database* pDatabase = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pCacheName = nullptr) = 0;

		/// Gets a resource from the resource cache in this manager. If it isn't present in the cache,
		/// nothing will happen.
		/// @param name
		/// @param pDst
		/// @returns True if the file was present in the cache, false otherwise.
		/* 14h */	virtual bool GetLoadedResource(const ResourceKey& name, ResourceObjectPtr* pDst) = 0;

		/* 18h */	virtual bool ReloadResource(
			const ResourceKey& name, 
			ResourceObject* pResource, 
			void* pFactoryData = nullptr, 
			Database* pDatabase = nullptr,
			IResourceFactory* pFactory = nullptr) = 0;

		/// Similar usage to ResourceManager::GetResource . This method does not check the cache, however,
		/// therefore always generating a new resource.
		/// @param[in] name The ResourceKey name to find. If the typeID is mapped in the manager to other alternative typeIDs, all them will be tested.
		/// @param[out] ppDst [Optional] A pointer to a ResourceObject*. It will be assigned with the generated resource.
		/// @param[in] factoryData [Optional] Additional data that is passed to the resource factory, usually null.
		/// @param[in] pDatabase [Optional] The Database where the file will be searched. Use nullptr to search in all available databases.
		/// @param[in] pFactory [Optional] The IResourceFactory used to generate the resource. Use nullptr to use the appropiate factory according to the typeID mapping in this manager.
		/// @param[in] pCacheName [Optional] The ResourceKey name used to search the resource in the cache.
		/// @returns True if the resource was successfully generated and read, false otherwise.
		/* 1Ch */	virtual bool GetPrivateResource(
			const ResourceKey& name,
			ResourceObjectPtr* ppDst = nullptr,
			void* pFactoryData = nullptr,
			Database* pDatabase = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pCacheName = nullptr) = 0;

		/// Writes the given resource to a package file. If the DBPF is specified in this method, a new file will
		/// always be created on it even if it does not exist yet; however, if no DBPF is specified, the resource
		/// will be written in the first DBPF that contains a file with the given name.
		/// If there is a problem while writing the resource, the file on the DBPF will be deleted.
		///
		/// @param pResource[in] The ResourceObject to write. It will be written according to the IResourceFactory specified or the one that corresponds to the typeID.
		/// @param pFactoryData[in] [Optional] Additional data that is passed to the resource factory, usually null.
		/// @param pDatabase[in] [Optional] The Database where the resource will be written.
		/// @param pFactory[in] [Optional] The IResourceFactory that will be used to write the resource. Use nullptr to use the one that corresponds to the resource's typeID.
		/// @param pNameKey[in] [Optional] The ResourceKey that must be used as the name. If nullptr, the name of the resource will be used.
		/// @returns True if the resource was successfuly written, false otherwise.
		/* 20h */	virtual bool WriteResource(
			const ResourceObject* pResource,
			void* pFactoryData = nullptr,
			Database* pDatabase = nullptr,
			IResourceFactory* pFactory = nullptr,
			const ResourceKey* pNameKey = nullptr) = 0;

		/// Maps all the record types to the given resource type.
		/// @param resourceType
		/// @param recordTypes
		/// @param count Number of entries in `recordTypes`
		/* 24h */	virtual void SetTypeMapping(uint32_t resourceType, uint32_t* recordTypes, size_t count) = 0;

		/// Gets all the record type IDs mapped to the given
		/// @param[out] dst
		/// @param resourceType
		/// @returns The number of record types mapped.
		/* 28h */	virtual size_t GetRecordTypesFromResourceType(eastl::vector<uint32_t>& dst, uint32_t resourceType) = 0;

		/// Gets the general resource type ID that the given record type is assigned to.
		/// Record types are the ones found in files, whereas resource types are for ResourceObject
		/// (for example, `.raster` and `.rw4` are different record types but they all map to the same resource type).
		/// @param recordType
		/// @returns 
		/* 2Ch */	virtual uint32_t GetTypeMapping(uint32_t recordType) = 0;

		/// Finds the real record key of a given resource, as well as the database that contaiend it.
		/// @param[in] nameKey The original ResourceKey of the file.
		/// @param[out] pDst [Optional] The ResourceKey where the real key of the file will be put, with the correct typeID.
		/// @param[in] pDatabase [Optional] The database where the file will be searched. If not specified, it will be searched in all available databases.
		/// @returns The database that contains this file, or null if it is not in any database.
		///
		/* 30h */	virtual Database* FindRecord(const ResourceKey& nameKey, ResourceKey* pDst = nullptr, Database* pDatabase = nullptr) = 0;

		/// Gets a list of the keys of all the loaded resources in this manager.
		/// @param[out] pDst
		/// @param filter
		/// @returns
		/* 34h */	virtual size_t GetResourceKeyList(eastl::vector<ResourceKey>& pDst, IKeyFilter* filter) = 0;

		/// Gets all the file keys in this manager that match the criteria specified by the given request. If request is nullptr,
		/// all the files in the manager will be given.
		/// @param[out] dst The vector where all the files ResourceKey names will be added.
		/// @param[in] filter The criteria that the files must match in order to be added to the vector.
		/// @param[out] pDstDatabases [Optional] A vector where all the Database objects that contained the files will be added.
		/// @returns The number of file keys that matched the criteria.
		/* 38h */	virtual size_t GetRecordKeyList(eastl::vector<ResourceKey>& dst, IKeyFilter* filter, eastl::vector<Database*>* pDstDatabases = nullptr) = 0;

		/* 3Ch */	virtual size_t GetRecordKeyList2(eastl::vector<ResourceKey>& dst, IKeyFilter* filter, bool cached) = 0;

		/* 40h */	virtual bool RegisterChangeNotification(bool, ChangeNotificationCallback_t callback, void* data, IKeyFilter* filter, int) = 0;

		/// Adds or removes the given IResourceFactory to this manager. Resource factories are used to generate resource objects depending on
		/// their type. The factory will be assigned to the types returned by IResourceFactory::GetSupportedTypes.
		/// @param add If true, pFactory will be added to the manager; if false, it will be removed from the manager.
		/// @param pFactory The IResourceFactory to add to/remove from this manager.
		/// @param arg_8 Unknown usage, usually 0.
		/// @returns True if the factory was successfully added/removed, false otherwise.
		/* 44h */	virtual bool RegisterFactory(bool add, IResourceFactory* pFactory, uint32_t arg_8) = 0;

		/// Returns the IResourceFactory that belongs to the specified \c typeID. 
		/// If \c recordTypeID is ResourceKey::kWildcardID, the first factory assigned to the \c resourceTypeID will be returned;
		/// Otherwise, IResourceFactory::CanConvert() will be called on every factory using the types provided here,
		/// and the first one that returns true will be returned.
		/// @param resourceTypeID
		/// @param recordTypeID
		/// @return 
		/* 48h */	virtual IResourceFactory* FindFactory(uint32_t resourceTypeID, uint32_t recordTypeID = ResourceKey::kWildcardID) = 0;

		/// Puts all the IResourceFactory instances that are assigned to the specified \c resourceTypeID into the given list.
		/// If \c resourceTypeID is ResourceKey::kWildcardID, all the factories in this manager will be added.
		/// @param[out] dst
		/// @param[in] resourceTypeID
		/// @returns The number of factories found.
		/* 4Ch */	virtual size_t GetFactoryList(eastl::list<IResourceFactory*>& dst, uint32_t resourceTypeID = ResourceKey::kWildcardID) = 0;

		/// Adds/removes the given DatabasePackedFile to this manager, using the priority specified.
		/// The priority of a DBPF is used when getting files from the resource manager;
		/// since a certain file name can be contained in multiple packages, the one with the
		/// most priority will be chosen.
		/// The usage of the first argument is unknown, but it is usually 'true'.
		/// @param add If true, the database is added to the manager; if false, the database is removed from the manager
		/// @param pDatabase The database to add/remove
		/// @param priority The priority of this database, this determines in which order files are searched in databases
		/// @returns Whether the database was registered or not.
		/* 50h */	virtual bool RegisterDatabase(bool add, Database* pDatabase, int priority = 1000) = 0;

		/// Checks if a database is already registered in this manager, and optionally gets its priority.
		/// @param[in] pDatabase The database
		/// @param[out] dstPriority [Optional] A pointer to an integer that will contain the priority. This parameter can be nullptr.
		/// @returns True if the manager contained the DBPF, false otherwise.
		///
		/* 54h */	virtual bool IsDatabaseRegistered(Database* pDatabase, int* dstPriority = nullptr) = 0;

		/// Returns the first database that contains the given file. Databases are searched in descending order of priority.
		/// @param name
		/// @returns name
		/* 58h */	virtual Database* FindDatabase(const ResourceKey& name) = 0;

		///
		/// Gets all the Database objects in this manager and puts it to the dst list. 
		/// Optionally, a ResourceKey can be specified; in that case, only the databases that contain that file will be added.
		/// @param[out] dst A list of Database pointers where the databases will be added.
		/// @param[in] pFileKey [Optional] A ResourceKey that the returned databases must contain, or nullptr if no filtering is wanted.
		/// @returns The number of databases added to the list.
		///
		/* 5Ch */	virtual size_t GetDatabaseList(DatabaseList& dst, const ResourceKey* pFileKey = nullptr) = 0;

		/// Calls the registered database change listeners that were added with RegisterChangeNotification()
		/// @param pDatabase
		/// @param keys
		/// 
		/* 60h */	virtual void DoDatabaseChanged(Database* pDatabase, eastl::vector<ResourceKey>& keys) = 0;

		/* 64h */	virtual bool RegisterCache(bool add, ICache* pCache, int) = 0;

		/// Returns the cache that contains a resource with this name (if any).
		/// @param name
		/// @returns
		/* 68h */	virtual ICache* FindCache(const ResourceKey& name) = 0;

		/* 6Ch */	virtual bool CacheResource(ResourceObject* pResource, bool) = 0;

		/// Removes certain (or all) elements from a cache.
		/// @param pCache
		/// @param pFilter
		/* 70h */	virtual void FlushCache(ICache* pCache, IKeyFilter* pFilter = nullptr) = 0;

		/// Puts all the resource caches used in this manager into the given list.
		/// @returns The number of caches.
		/* 74h */	virtual size_t GetCacheList(eastl::list<ICache*>& dst) = 0;

		/// Adds this file name to the list, so that it can be accessed using the corresponding ResourceKey.
		/// The file name is in the format "groupID!instanceID.typeID", and it will be mapped to the
		/// key generated using the ResourceKey::Parse function.
		/// @param fileName
		/// @returns True if the file name was mapped successfully, false otherwise.
		
		/// Returns the resource key that maps to the given file name.
		/// @param defaultTypeID [Optional] Type ID used if the file name does not have an extension
		/// @param defaultGroupID [Optional] Group ID used if the file name does not have a folder
		/* 78h */	virtual ResourceKey GetKeyFromName(const char16_t* fileName, uint32_t defaultTypeID = 0, uint32_t defaultGroupID = 0) = 0;

		/// Gets the file name that corresponds to the specified ResourceKey.
		/// The file name will be in the format "groupID!instanceID.typeID".
		/// The file name can be parsed to a key again using the ResourceKey::Parse() method.
		/// A file name wil be generated even if it's not mapped; when that happens, the ResourceKey members are displayed in hexadecimal format.
		/// @param[in] key The ResourceKey that will be represented as a eastl::string.
		/// @param[out] dst A string16 that will contain the resulting text. 
		/* 7Ch */	virtual void GetNameFromKey(const ResourceKey& key, eastl::string16& dst) = 0;

		/// Maps the given ResourceKey to the file name specified, which is in the format "groupID!instanceID.typeID".
		/// The file name can be parsed to a key again using the ResourceKey::Parse method.
		/// @param key
		/// @param fileName
		/// @returns True if it was successfully mapped.
		/* 80h */	virtual bool SetKeyName(const ResourceKey& key, const char16_t* fileName) = 0;

		/// Removes the file name mapped for the given ResourceKey.
		/// The file name can be parsed to a key again using the ResourceKey::Parse method.
		/// @param key
		/// @returns True if the file name mapping was removed, false if it did not exist.
		/* 84h */	virtual bool ForgetKeyName(const ResourceKey& key) = 0;

		/// Returns the typeID that has the given extension mapped to it, or `0xFFFFFFFF` if no typeID has this extension mapped.
		/// @param typeName
		/// @returns
		/* 88h */	virtual uint32_t GetTypeFromTypename(const char16_t* typeName) = 0;

		/// Returns the extension that is mapped to the given type ID, or nullptr if there's no mapping.
		/// @param typeID
		/// @returns
		/* 8Ch */	virtual const char16_t* GetTypenameFromType(uint32_t typeID) = 0;

		/// Maps the given typeID to the specified extension string.
		/// @param typeID
		/// @param pExtension
		/// @returns True if the extension was successfully mapped or already existed, false if the typeID was mapped to a different extension.
		/* 90h */	virtual bool SetTypename(uint32_t typeID, const char16_t* pExtension) = 0;

		/// Removes the extension the given typeID it is mapped to.
		/// @param typeID
		/// @returns True if the extension existed and was removed, false otherwise.
		/* 94h */	virtual bool ResetTypename(uint32_t typeID) = 0;


		/// Gets the active resource manager.
		/// @return
		static IResourceManager* Get();
	};

	namespace Addresses(IResourceManager)
	{
		DeclareAddress(Get);
	}
}