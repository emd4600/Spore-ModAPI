#pragma once

#include <Spore\Resource\IPFRecord.h>

namespace Simulator
{
	class ISerializerStream : public Object
	{
	public:
		static const uint32_t TYPE = 0x179CD60;

		/* 10h */	virtual bool func10h(int, const ResourceKey& name) = 0;
		/* 14h */	virtual bool func14h() = 0;
		/* 18h */	virtual bool func18h() = 0;
		/* 1Ch */	virtual bool func1Ch() = 0;
		/* 20h */	virtual Resource::IPFRecord* GetRecord() const = 0;
		/* 24h */	virtual int func24h() const = 0;
		/* 28h */	virtual bool func28h(uint32_t nounID, int, int) = 0;
		/* 2Ch */	virtual bool func2Ch(int, int) = 0;
		/* 30h */	virtual bool func30h(int) = 0;  // related with prop files?
		/* 34h */	virtual bool func34h(int, int) = 0;
		/* 38h */	virtual bool func38h(int, int) = 0;
		/* 3Ch */	virtual int func3Ch() = 0;
		/* 40h */	virtual void func40h(int) = 0;
	};

	//class SerializerStream
	//	: public DefaultRefCounted
	//	, public ISerializerStream
	//{
	//protected:
	//	/* 0Ch */	bool field_0C;
	//	/* 10h */	int field_10;
	//	/* 14h */	Resource::IPFRecord* mpRecord;
	//	/* 18h */	int field_18;
	//};

	struct Attribute;

	/// The type of function used to read binary attribute data. 
	/// The parameters are the data serializer and the address of memory where the data must be read.
	typedef bool(*ReadFunction_t)(ISerializerStream*, void*);
	/// The type of function used to write binary attribute data. 
	/// The parameters are the data serializer and the address of memory where the data is.
	typedef bool(*WriteFunction_t)(ISerializerStream*, void*);

	/// The type of function used to read attribute data, which is expressed in text. 
	/// The parameters are the text string and the address of memory where the data must be read.
	typedef void(*ReadTextFunction_t)(const eastl::string&, void*);
	/// The type of function used to write attribute data, which is expressed in text. 
	/// The parameters are the destination text buffer and the address of memory where the data is.
	typedef void(*WriteTextFunction_t)(char*, void*);

	typedef bool(*UnknownFunction_t)();
	typedef bool(*UnknownFunction2_t)(void*, const char*, int);
	typedef void*(*OffsetFunction_t)(Attribute*);

	struct Attribute
	{
		static bool DefaultUnknownFunction() { return true; }
		static bool DefaultUnknownFunction2(void*, const char*, int) { return true; }
		static void* DefaultOffset(Attribute*);

		Attribute() = default;
		Attribute(const char*, uint32_t, size_t,
			ReadFunction_t, WriteFunction_t, ReadTextFunction_t, WriteTextFunction_t, UnknownFunction2_t);

		/* 00h */	const char* name;
		/* 04h */	uint32_t id;
		/* 08h */	size_t offset;
		/* 0Ch */	int field_0C;  // not initialized
		/* 10h */	int field_10;  // not initialized
		/* 14h */	int field_14;  // not initialized
		/* 18h */	void* pCurrentObject;
		/* 1Ch */	int field_1C;
		/* 20h */	OffsetFunction_t offsetFunction;
		/* 24h */	ReadFunction_t readFunction;
		/* 28h */	WriteFunction_t writeFunction;
		/* 2Ch */	ReadTextFunction_t readTextFunction;
		/* 30h */	WriteTextFunction_t writeTextFunction;
		/* 34h */	UnknownFunction_t field_34;
		/* 38h */	UnknownFunction2_t field_38;
	};
	ASSERT_SIZE(Attribute, 0x3C);

	struct ClassSerializer
	{
		struct AttributePointer
		{
			/* 00h */	uint32_t id;
			/* 04h */	int field_4;
			/* 08h */	bool field_8;
			/* 0Ch */	void* field_C;   // field_18 of the attribute
			/* 10h */	Attribute* pAttribute;
		};

		static const uint32_t CLASS_ID = 0x1A80D26;

		ClassSerializer(void* pObject, Attribute* attributes, uint32_t classID = 0x1A80D26);

		// Attributes are searched with a binary search, they must be ordered
		AttributePointer attributes[128];
		/* A00h */	int count;
		/* A04h */	int field_A04;  // count of attributes written
		/* A08h */	uint32_t id;
		/* A0Ch */	void* pObject;
		/* A10h */	Attribute* pAttributes;

		bool Read(ISerializerStream* pStream);
		bool Write(ISerializerStream* pStream);
	};
	ASSERT_SIZE(ClassSerializer, 0xA14);

	namespace Addresses(ClassSerializer) 
	{
		DeclareAddress(Read);
		DeclareAddress(Write);
	}

	class XmlSerializer
	{
		// it has things, but we are not really interested
	public:
		bool AttributesToXml(Attribute* attributes, void* object, const char* name);
	};

	namespace Addresses(XmlSerializer)
	{
		DeclareAddress(AttributesToXml);
	}
}

