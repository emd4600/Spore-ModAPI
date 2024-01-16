#pragma once

#include <Spore\Simulator\Serialization.h>
#include <Spore\IO.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\map.h>
#include <EASTL\set.h>
#include <EASTL\hash_map.h>
#include <EASTL\hash_set.h>

#ifndef SDK_TO_GHIDRA
namespace Simulator
{
	class ISimulatorSerializable;

	namespace SerializationTypes
	{
		//PLACEHOLDER use bool = std::is_base_of<ISimulatorSerializable, T>::value
		// but keep in mind that for that we actually save the pointer, or whatever

		template <typename T>
		struct SerializedType
		{
			static bool Read(ISerializerReadStream*, T*);
			static bool Write(ISerializerWriteStream*, T*);
			static void ReadText(const eastl::string&, T*);
			static void WriteText(char*, T*);
		};

		template <class T>
		struct SerializedType<eastl::intrusive_ptr<T>>
		{
			static bool Read(ISerializerReadStream* stream, eastl::intrusive_ptr<T>* dst) {
				*dst = nullptr;
				stream->ReadPointer(T::TYPE, dst, 0);
				return true;
			}

			static bool Write(ISerializerWriteStream* stream, eastl::intrusive_ptr<T>* src) {
				ISimulatorSerializable* pointer = nullptr;
				if (*src) {
					pointer = ((Object*)(*src))->Cast(T::TYPE);
				}
				stream->WritePointer(pointer);
				return true;
			}

			static void ReadText(const eastl::string& str, eastl::intrusive_ptr<T>* dst) {
			}

			static void WriteText(char* buf, eastl::intrusive_ptr<T>* src) {
				buf[0] = '\0';
			}
		};

		template <>
		struct SerializedType<bool>
		{
			static bool Read(ISerializerReadStream* stream, bool* dst) {
				bool b;
				IO::ReadBool8(stream->GetRecord()->GetStream(), b);
				*dst = b;
				return true;
			}

			static bool Write(ISerializerWriteStream* stream, bool* src) {
				IO::WriteBool8(stream->GetRecord()->GetStream(), src);
				return true;
			}

			static void ReadText(const eastl::string& str, bool* dst) {
				*dst = atol(str.c_str());
			}

			static void WriteText(char* buf, bool* src) {
				sprintf_s(buf, 1024, "%d", *src);
			}
		};

		template <>
		struct SerializedType<int>
		{
			static bool Read(ISerializerReadStream* stream, int* dst) {
				IO::ReadInt32(stream->GetRecord()->GetStream(), dst);
				return true;
			}

			static bool Write(ISerializerWriteStream* stream, int* src) {
				IO::WriteInt32(stream->GetRecord()->GetStream(), src);
				return true;
			}

			static void ReadText(const eastl::string& str, int* dst) {
				*dst = atol(str.c_str());
			}

			static void WriteText(char* buf, int* src) {
				sprintf_s(buf, 1024, "%d", *src);
			}
		};

		template <>
		struct SerializedType<uint32_t>
		{
			static bool Read(ISerializerReadStream* stream, uint32_t* dst) {
				IO::ReadUInt32(stream->GetRecord()->GetStream(), dst);
				return true;
			}

			static bool Write(ISerializerWriteStream* stream, uint32_t* src) {
				IO::WriteUInt32(stream->GetRecord()->GetStream(), src);
				return true;
			}

			static void ReadText(const eastl::string& str, uint32_t* dst) {
				*dst = atol(str.c_str());
			}

			static void WriteText(char* buf, uint32_t* src) {
				sprintf_s(buf, 1024, "%d", *src);
			}
		};

		template <>
		struct SerializedType<float>
		{
			static bool Read(ISerializerReadStream* stream, float* dst) {
				IO::ReadFloat(stream->GetRecord()->GetStream(), dst);
				return true;
			}
			static bool Write(ISerializerWriteStream* stream, float* src) {
				IO::WriteFloat(stream->GetRecord()->GetStream(), src);
				return true;
			}
			static void ReadText(const eastl::string& str, float* dst) {
				*dst = float(atof(str.c_str()));
			}
			static void WriteText(char* buf, float* src) {
				sprintf_s(buf, 1024, "%f", *src);
			}
		};

		template <>
		struct SerializedType<eastl::string>
		{
			static bool Read(ISerializerReadStream* stream, eastl::string* dst) {
				auto s = stream->GetRecord()->GetStream();
				size_t count;
				IO::ReadUInt32(s, &count);
				if (count > 0) {
					*dst = eastl::string(count, ' ');
					for (size_t i = 0; i < count; ++i) {
						IO::ReadUInt8(s, (uint8_t*)(*dst)[i], 1);
					}
				}
				return true;
			}
			static bool Write(ISerializerWriteStream* stream, eastl::string* src) {
				size_t count = src->size();
				IO::WriteUInt32(stream->GetRecord()->GetStream(), &count);
				IO::WriteUInt8(stream->GetRecord()->GetStream(), (const uint8_t*)src->data(), src->size());
				return true;
			}
			static void ReadText(const eastl::string& str, eastl::string* dst) {
				*dst = str;
			}
			static void WriteText(char* buf, eastl::string* src) {
				sprintf_s(buf, 1024, "%s", src->c_str());
			}
		};

		template <>
		struct SerializedType<eastl::string16>
		{
			static bool Read(ISerializerReadStream* stream, eastl::string16* dst) {
				auto s = stream->GetRecord()->GetStream();
				size_t count;
				IO::ReadUInt32(s, &count);
				if (count > 0) {
					*dst = eastl::string16(count, ' ');
					for (size_t i = 0; i < count; ++i) {
						IO::ReadInt16(s, (int16_t*)(*dst)[i], 1, IO::Endian::Little);
					}
				}
				return true;
			}
			static bool Write(ISerializerWriteStream* stream, eastl::string16* src) {
				size_t count = src->size();
				IO::WriteUInt32(stream->GetRecord()->GetStream(), &count);
				IO::WriteInt16(stream->GetRecord()->GetStream(), (const int16_t*)src->data(), src->size(), IO::Endian::Little);
				return true;
			}
			static void ReadText(const eastl::string& str, eastl::string16* dst) {
				*dst = eastl::string16(eastl::string16::CtorConvert(), str);
			}
			static void WriteText(char* buf, eastl::string16* src) {
				sprintf_s(buf, 1024, "%ls", (wchar_t*)src->c_str());
			}
		};

		template <>
		struct SerializedType<ResourceKey>
		{
			static bool Read(ISerializerReadStream* stream, ResourceKey* dst) {
				IO::ReadUInt32(stream->GetRecord()->GetStream(), &dst->groupID);
				IO::ReadUInt32(stream->GetRecord()->GetStream(), &dst->typeID);
				IO::ReadUInt32(stream->GetRecord()->GetStream(), &dst->instanceID);
				return true;
			}

			static bool Write(ISerializerWriteStream* stream, ResourceKey* src) {
				IO::WriteUInt32(stream->GetRecord()->GetStream(), &src->groupID);
				IO::WriteUInt32(stream->GetRecord()->GetStream(), &src->typeID);
				IO::WriteUInt32(stream->GetRecord()->GetStream(), &src->instanceID);
				return true;
			}

			static void ReadText(const eastl::string& str, ResourceKey* dst) {
				ResourceKey::Parse(*dst, eastl::string16(eastl::string16::CtorConvert(), str).c_str());
			}

			static void WriteText(char* buf, ResourceKey* src) {
				sprintf_s(buf, 1024, "0x%x!0x%x.0x%x", src->groupID, src->instanceID, src->typeID);
			}
		};


		template <typename T>
		struct SerializedType<eastl::vector<T>>
		{
			static bool Read(ISerializerReadStream* stream, eastl::vector<T>* dst) {
				int count;
				IO::ReadInt32(stream->GetRecord()->GetStream(), &count);
				*dst = eastl::vector<T>(count);
				for (int i = 0; i < count; ++i) {
					SerializationTypes::Read<T>(stream, &(*dst)[i]);
				}
				return true;
			}
			static bool Write(ISerializerWriteStream* stream, eastl::vector<T>* src) {
				int count = src->size();
				IO::WriteInt32(stream->GetRecord()->GetStream(), &count);
				for (int i = 0; i < count; ++i) {
					SerializationTypes::Write<T>(stream, &(*src)[i]);
				}
				return true;
			}
			static void ReadText(const eastl::string& str, eastl::vector<T>* dst) {
			}
			static void WriteText(char* buf, eastl::vector<T>* src) {
				buf[0] = '\0';
			}
		};


		template <typename T>
		struct SerializedType<eastl::set<T>>
		{
			static bool Read(ISerializerReadStream* stream, eastl::set<T>* dst) {
				int count;
				IO::ReadInt32(stream->GetRecord()->GetStream(), &count);
				*dst = eastl::set<T>();
				for (int i = 0; i < count; ++i) {
					T object;
					SerializationTypes::Read<T>(stream, &object);
					dst->insert(object);
				}
				return true;
			}
			static bool Write(ISerializerWriteStream* stream, eastl::set<T>* src) {
				int count = src->size();
				IO::WriteInt32(stream->GetRecord()->GetStream(), &count);
				for (auto& object : *src) {
					SerializationTypes::Write<T>(stream, const_cast<T*>(&object));
				}
				return true;
			}
			static void ReadText(const eastl::string& str, eastl::set<T>* dst) {
			}
			static void WriteText(char* buf, eastl::set<T>* src) {
				buf[0] = '\0';
			}
		};


		template <typename Key, typename Value>
		struct SerializedType<eastl::map<Key, Value>>
		{
			static bool Read(ISerializerReadStream* stream, eastl::map<Key, Value>* dst) {
				int count;
				IO::ReadInt32(stream->GetRecord()->GetStream(), &count);
				*dst = eastl::map<Key, Value>();
				for (int i = 0; i < count; ++i) {
					Key key;
					SerializationTypes::Read<Key>(stream, &key);

					Value value;
					SerializationTypes::Read<Value>(stream, &value);

					(*dst)[key] = value;
				}
				return true;
			}
			static bool Write(ISerializerWriteStream* stream, eastl::map<Key, Value>* src) {
				int count = src->size();
				IO::WriteInt32(stream->GetRecord()->GetStream(), &count);
				for (auto& object : *src) {
					SerializationTypes::Write<Key>(stream, const_cast<Key*>(&object.first));
					SerializationTypes::Write<Value>(stream, &object.second);
				}
				return true;
			}
			static void ReadText(const eastl::string& str, eastl::map<Key, Value>* dst) {
			}
			static void WriteText(char* buf, eastl::map<Key, Value>* src) {
				buf[0] = '\0';
			}
		};


		template <typename T>
		struct SerializedType<eastl::hash_set<T>>
		{
			static bool Read(ISerializerReadStream* stream, eastl::hash_set<T>* dst) {
				int count;
				IO::ReadInt32(stream->GetRecord()->GetStream(), &count);
				*dst = eastl::hash_set<T>();
				for (int i = 0; i < count; ++i) {
					T object;
					SerializationTypes::Read<T>(stream, &object);
					dst->insert(object);
				}
				return true;
			}
			static bool Write(ISerializerWriteStream* stream, eastl::hash_set<T>* src) {
				int count = src->size();
				IO::WriteInt32(stream->GetRecord()->GetStream(), &count);
				for (auto& object : *src) {
					SerializationTypes::Write<T>(stream, const_cast<T*>(&object));
				}
				return true;
			}
			static void ReadText(const eastl::string& str, eastl::hash_set<T>* dst) {
			}
			static void WriteText(char* buf, eastl::hash_set<T>* src) {
				buf[0] = '\0';
			}
		};


		template <typename Key, typename Value>
		struct SerializedType<eastl::hash_map<Key, Value>>
		{
			static bool Read(ISerializerReadStream* stream, eastl::hash_map<Key, Value>* dst) {
				int count;
				IO::ReadInt32(stream->GetRecord()->GetStream(), &count);
				*dst = eastl::hash_map<Key, Value>();
				for (int i = 0; i < count; ++i) {
					Key key;
					SerializationTypes::Read<Key>(stream, &key);

					Value value;
					SerializationTypes::Read<Value>(stream, &value);

					(*dst)[key] = value;
				}
				return true;
			}
			static bool Write(ISerializerWriteStream* stream, eastl::hash_map<Key, Value>* src) {
				int count = src->size();
				IO::WriteInt32(stream->GetRecord()->GetStream(), &count);
				for (auto& object : *src) {
					SerializationTypes::Write<Key>(stream, const_cast<Key*>(&object.first));
					SerializationTypes::Write<Value>(stream, &object.second);
				}
				return true;
			}
			static void ReadText(const eastl::string& str, eastl::hash_map<Key, Value>* dst) {
			}
			static void WriteText(char* buf, eastl::hash_map<Key, Value>* src) {
				buf[0] = '\0';
			}
		};


		template<typename T>
		bool Read(ISerializerReadStream* stream, T* dst)
		{
			return SerializedType<T>::Read(stream, dst);
		}

		template<typename T>
		bool Write(ISerializerWriteStream* stream, T* src)
		{
			return SerializedType<T>::Write(stream, src);
		}

		template<typename T>
		void ReadText(const eastl::string& str, T* dst)
		{
			SerializedType<T>::ReadText(str, dst);
		}

		template<typename T>
		void WriteText(char* buffer, T* src)
		{
			SerializedType<T>::WriteText(buffer, src);
		}
	};
}

#define SimAttribute_(className, field, index, T) Simulator::Attribute(#field, index, offsetof(className, field), \
	(Simulator::ReadFunction_t)&Simulator::SerializationTypes::Read<T>, (Simulator::WriteFunction_t)&Simulator::SerializationTypes::Write<T>, \
	(Simulator::ReadTextFunction_t)&Simulator::SerializationTypes::ReadText<T>, (Simulator::WriteTextFunction_t)&Simulator::SerializationTypes::WriteText<T>, nullptr)

#define SimAttribute(className, field, index) SimAttribute_(className, field, index, decltype(((className*)0)->field))

#endif