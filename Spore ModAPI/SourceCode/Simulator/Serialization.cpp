#include <Spore\Simulator\Serialization.h>

namespace Simulator
{
	ClassSerializer::ClassSerializer(void* _pObject, Attribute _attributes[], uint32_t classID)
		: pObject(_pObject)
		, pAttributes(_attributes)
		, id(classID)
		, count(0)
		, field_A04(0)
	{
		Attribute* ptr = _attributes;
		while (ptr->readFunction && ptr->writeFunction && count < 128) {
			attributes[count++] = {ptr->id, 0, false, ptr->pCurrentObject, ptr};
			ptr += 1;
		}
	}

	auto_METHOD(ClassSerializer, bool, Read, Args(ISerializerStream* pStream), Args(pStream));
	auto_METHOD(ClassSerializer, bool, Write, Args(ISerializerStream* pStream), Args(pStream));

	void* Attribute::DefaultOffset(Attribute* ptr) {
		return (char*)ptr->pCurrentObject + ptr->offset;
	}

	Attribute::Attribute(const char* _name, uint32_t _id, size_t _offset,
		ReadFunction_t read, WriteFunction_t write, ReadTextFunction_t readText, WriteTextFunction_t writeText, 
		UnknownFunction2_t _field_38)
		: name(_name)
		, id(_id)
		, offset(_offset)
		, readFunction(read)
		, writeFunction(write)
		, readTextFunction(readText)
		, writeTextFunction(writeText)
		, field_38(_field_38)
		, field_34(&Attribute::DefaultUnknownFunction)
		, offsetFunction(&Attribute::DefaultOffset)
		, pCurrentObject(nullptr)
		, field_1C(0)
	{

	}

}