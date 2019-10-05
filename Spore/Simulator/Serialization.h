#pragma once

#include <Spore\Resource\IPFRecord.h>

namespace Simulator
{
	class DataSerializer
	{

	};

	/// The type of function used to read binary attribute data. 
	/// The parameters are the data serializer and the address of memory where the data must be read.
	typedef bool(*ReadFunction_t)(DataSerializer*, void*);
	/// The type of function used to write binary attribute data. 
	/// The parameters are the data serializer and the address of memory where the data is.
	typedef bool(*WriteFunction_t)(DataSerializer*, void*);

	/// The type of function used to read attribute data, which is expressed in text. 
	/// The parameters are the text string and the address of memory where the data must be read.
	typedef bool(*ReadTextFunction_t)(string&, void*);
	/// The type of function used to write attribute data, which is expressed in text. 
	/// The parameters are the destination text buffer and the address of memory where the data is.
	typedef bool(*WriteTextFunction_t)(char*, void*);

	typedef bool(*UnknownFunction_t)();

	struct Attribute
	{
		/* 04h */	UnknownFunction_t field_4;
		/* 08h */	WriteTextFunction_t writeTextFunction;
		/* 0Ch */	ReadTextFunction_t readTextFunction;
		/* 10h */	WriteFunction_t writeFunction;
		/* 14h */	ReadFunction_t readFunction;

		/* 30h */	size_t size;  // in bytes
		/* 34h */	uint32_t id;
		/* 38h */	const char* name;
	};
	static_assert(sizeof(Attribute) == 60, "sizeof(Attribute) == 60");
}