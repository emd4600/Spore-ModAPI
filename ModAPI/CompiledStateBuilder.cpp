#include "CompiledStateBuilder.h"

using namespace ModAPI;

CompiledStateBuilder::CompiledStateBuilder()
	: offset(0), size(0), bufferSize(BUFFER_SIZE)
{
	buffer = new char[BUFFER_SIZE];
}

CompiledStateBuilder::~CompiledStateBuilder()
{
	delete buffer;
}

int CompiledStateBuilder::GetSize()
{
	return size;
}

void CompiledStateBuilder::CopyBuffer(char* dst)
{
	memcpy(dst, buffer, size);
}

void CompiledStateBuilder::CheckBufferSize(int extraSize)
{
	if (offset + extraSize > bufferSize)
	{
		bufferSize += BUFFER_SIZE;
		char* newBuffer = new char[bufferSize];

		CopyBuffer(newBuffer);
		delete buffer;

		buffer = newBuffer;
	}
}

//void CompiledStateBuilder::WriteBool(bool value)
//{
//	CheckBufferSize(sizeof(value));
//	IncrementSize(sizeof(value));
//
//	*(bool*)(buffer + offset) = value;
//	offset += sizeof(value);
//}
//
//void CompiledStateBuilder::WriteChar(char value)
//{
//	CheckBufferSize(sizeof(value));
//	IncrementSize(sizeof(value));
//
//	*(char*)(buffer + offset) = value;
//	offset += sizeof(value);
//}
//
//void CompiledStateBuilder::WriteShort(short value)
//{
//	CheckBufferSize(sizeof(value));
//	IncrementSize(sizeof(value));
//
//	*(short*)(buffer + offset) = value;
//	offset += sizeof(value);
//}
//
//void CompiledStateBuilder::WriteInt(int value)
//{
//	CheckBufferSize(sizeof(value));
//	IncrementSize(sizeof(value));
//
//	*(int*)(buffer + offset) = value;
//	offset += sizeof(value);
//}
//
//void CompiledStateBuilder::WriteFloat(float value)
//{
//	CheckBufferSize(sizeof(value));
//	IncrementSize(sizeof(value));
//
//	*(float*)(buffer + offset) = value;
//	offset += sizeof(value);
//}


int CompiledStateBuilder::GetOffset()
{
	return offset;
}

void CompiledStateBuilder::SetOffset(int offset)
{
	this->offset = offset;
}