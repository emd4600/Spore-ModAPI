#pragma once

#include "Serialization.h"
#include <Spore\IO.h>

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
			static bool Read(ISerializerStream*, T*);
			static bool Write(ISerializerStream*, T*);
			static void ReadText(const eastl::string&, T*);
			static void WriteText(char*, T*);
		};

		template <>
		struct SerializedType<bool>
		{
			static bool Read(ISerializerStream* stream, bool* dst) {
				bool b;
				IO::ReadBool8(stream->GetRecord()->GetStream(), b);
				*dst = b;
				return true;
			}

			static bool Write(ISerializerStream* stream, bool* src) {
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
			static bool Read(ISerializerStream* stream, int* dst) {
				IO::ReadInt32(stream->GetRecord()->GetStream(), dst);
				return true;
			}

			static bool Write(ISerializerStream* stream, int* src) {
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
			static bool Read(ISerializerStream* stream, uint32_t* dst) {
				IO::ReadUInt32(stream->GetRecord()->GetStream(), dst);
				return true;
			}

			static bool Write(ISerializerStream* stream, uint32_t* src) {
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
			static bool Read(ISerializerStream* stream, float* dst) {
				IO::ReadFloat(stream->GetRecord()->GetStream(), dst);
				return true;
			}
			static bool Write(ISerializerStream* stream, float* src) {
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
			static bool Read(ISerializerStream* stream, eastl::string* dst) {
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
			static bool Write(ISerializerStream* stream, eastl::string* src) {
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
			static bool Read(ISerializerStream* stream, eastl::string16* dst) {
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
			static bool Write(ISerializerStream* stream, eastl::string16* src) {
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
			static bool Read(ISerializerStream* stream, ResourceKey* dst) {
				IO::ReadUInt32(stream->GetRecord()->GetStream(), &dst->groupID);
				IO::ReadUInt32(stream->GetRecord()->GetStream(), &dst->typeID);
				IO::ReadUInt32(stream->GetRecord()->GetStream(), &dst->instanceID);
				return true;
			}

			static bool Write(ISerializerStream* stream, ResourceKey* src) {
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
			static bool Read(ISerializerStream* stream, eastl::vector<T>* dst) {
				int count;
				IO::ReadInt32(stream->GetRecord()->GetStream(), &count);
				*dst = eastl::vector<T>(count);
				for (int i = 0; i < count; ++i) {
					SerializationTypes::Read<T>(stream, &(*dst)[i]);
				}
				return true;
			}
			static bool Write(ISerializerStream* stream, eastl::vector<T>* src) {
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

		template<typename T>
		bool Read(ISerializerStream* stream, T* dst)
		{
			return SerializedType<T>::Read(stream, dst);
		}

		template<typename T>
		bool Write(ISerializerStream* stream, T* src)
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