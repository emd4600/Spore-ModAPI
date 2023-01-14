#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\IO\Allocator.h>
#include <Spore\IO\EAIOZoneObject.h>
#include <Spore\IO\FileStream.h>
#include <Spore\IO\Constants.h>
#include <Spore\IO\StreamAdapter.h>
#include <Spore\IO\StreamBuffer.h>
#include <Spore\IO\StreamChild.h>
#include <Spore\IO\StreamFixedMemory.h>
#include <Spore\IO\StreamMemory.h>
#include <Spore\IO\StreamNull.h>
#include <Spore\IO\XmlWriter.h>

namespace Addresses(IO)
{
	DefineAddress(GetAllocator, SelectAddress(0x9261B0, 0x925F40));

	DefineAddress(ReadBool8, SelectAddress(0x93B1B0, 0x93ABF0));

	DefineAddress(ReadInt8, SelectAddress(0x93ABF0, 0x93A630));
	DefineAddress(ReadUInt8, SelectAddress(0x93ABF0, 0x93A630));

	DefineAddress(ReadInt16, SelectAddress(0x93AC30, 0x93A670));
	DefineAddress(ReadUInt16, SelectAddress(0x93AC30, 0x93A670));

	DefineAddress(ReadUInt32, SelectAddress(0x93ACB0, 0x93A6F0));
	DefineAddress(ReadFloat, SelectAddress(0x93ACB0, 0x93A6F0));
	// We want this to be the last one because this is the function we want in SDK-to-Ghidra
	DefineAddress(ReadInt32, SelectAddress(0x93ACB0, 0x93A6F0));

	DefineAddress(ReadResourceID, SelectAddress(0x93AD30, 0x93A770));

	DefineAddress(ReadCString, SelectAddress(0x530690, 0x530280));

	DefineAddress(ReadLine, SelectAddress(0x93ADE0, 0x93A820));


	DefineAddress(WriteInt8, SelectAddress(0x93AED0, 0x93A910));
	DefineAddress(WriteUInt8, SelectAddress(0x93AED0, 0x93A910));

	DefineAddress(WriteInt16, SelectAddress(0x93AF00, 0x93A940));
	DefineAddress(WriteUInt16, SelectAddress(0x93AF00, 0x93A940));

	DefineAddress(WriteUInt32, SelectAddress(0x93AFA0, 0x93A9E0));
	DefineAddress(WriteFloat, SelectAddress(0x93AFA0, 0x93A9E0));
	// We want this to be the last one because this is the function we want in SDK-to-Ghidra
	DefineAddress(WriteInt32, SelectAddress(0x93AFA0, 0x93A9E0));

	DefineAddress(WriteResourceID, SelectAddress(0x93B040, 0x93AA80));

	DefineAddress(WriteLine, SelectAddress(0x93B100, 0x93AB40));


	DefineAddress(EnsureTrailingPathSeparator, SelectAddress(0x931CC0, 0x931740));
	DefineAddress(ConcatenatePathComponents, SelectAddress(0x930200, 0x9300D0));
}

namespace IO
{
	namespace Addresses(EAIOZoneObject)
	{
		DefineAddress(new_, SelectAddress(0x9264E0, 0x926270));
		DefineAddress(delete_, SelectAddress(0x926560, 0x9262F0));
	}

	namespace Addresses(FileStream)
	{
		DefineAddress(AddRef, SelectAddress(0x931D00, 0x931780));
		DefineAddress(Release, SelectAddress(0x931D10, 0x931790));
		DefineAddress(GetType, SelectAddress(0x8D65B0, 0x8D62A0));
		DefineAddress(GetAccessFlags, SelectAddress(0xFA1540, 0x931A90));
		DefineAddress(GetState, SelectAddress(0x932010, 0x931AA0));
		DefineAddress(Close, SelectAddress(0x931FC0, 0x931A40));
		DefineAddress(GetSize, SelectAddress(0x9320B0, 0x931B40));
		DefineAddress(SetSize, SelectAddress(0x932100, 0x931B90));
		DefineAddress(GetPosition, SelectAddress(0x932150, 0x931BE0));
		DefineAddress(SetPosition, SelectAddress(0x9321B0, 0x931C40));
		DefineAddress(GetAvailable, SelectAddress(0x932210, 0x931CA0));
		DefineAddress(Read, SelectAddress(0x932220, 0x931CB0));
		DefineAddress(Flush, SelectAddress(0x9322B0, 0x931D40));
		DefineAddress(Write, SelectAddress(0x932270, 0x931D00));
		DefineAddress(SetPath, SelectAddress(0x931D60, 0x9317E0));
		DefineAddress(SetPathCString, SelectAddress(0x931D30, 0x9317B0));
		DefineAddress(GetPath, SelectAddress(0x931DF0, 0x931870));
		DefineAddress(GetPathCString, SelectAddress(0x931D90, 0x931810));
		DefineAddress(Open, SelectAddress(0x931E40, 0x9318C0));
	}

	namespace Addresses(StreamBuffer)
	{
		DefineAddress(AddRef, SelectAddress(0x83D030, 0x83F6A0));
		DefineAddress(Release, SelectAddress(0x93BF70, 0x93B820));
		DefineAddress(GetType, SelectAddress(0x93B360, 0x93ADA0));
		DefineAddress(GetAccessFlags, SelectAddress(0x93B370, 0x93ADB0));
		DefineAddress(GetState, SelectAddress(0x93B390, 0x93ADD0));
		DefineAddress(Close, SelectAddress(0x93B980, 0x93B3C0));
		DefineAddress(GetSize, SelectAddress(0x93B3B0, 0x93ADF0));
		DefineAddress(SetSize, SelectAddress(0x93B580, 0x93AFC0));
		DefineAddress(GetPosition, SelectAddress(0x93B3E0, 0x93AE20));
		DefineAddress(SetPosition, SelectAddress(0x93B5D0, 0x93B010));
		DefineAddress(GetAvailable, SelectAddress(0x93B420, 0x93AE60));
		DefineAddress(Read, SelectAddress(0x93B670, 0x93B0B0));
		DefineAddress(Flush, SelectAddress(0x93B830, 0x93B270));
		DefineAddress(Write, SelectAddress(0x93B9C0, 0x93B400));

		DefineAddress(SetBufferSizes, SelectAddress(0x93B490, 0x93AED0));
		DefineAddress(SetStream, SelectAddress(0x93B8F0, 0x93B330));
		DefineAddress(FillWriteBuffer, SelectAddress(0x93B840, 0x93B280));
		DefineAddress(FlushWriteBuffer, SelectAddress(0x93B430, 0x93AE70));
	}

	namespace Addresses(StreamChild)
	{
		DefineAddress(AddRef, SelectAddress(0x93BB70, 0x93C350));
		DefineAddress(Release, SelectAddress(0x93BD60, 0x93C360));
		DefineAddress(GetType, SelectAddress(0x923C40, 0x93B780));
		DefineAddress(GetAccessFlags, SelectAddress(0x93BC20, 0x93B630));
		DefineAddress(GetState, SelectAddress(0x93BC00, 0x93B640));
		DefineAddress(Close, SelectAddress(0xFC8510, 0x93B610));
		DefineAddress(GetSize, SelectAddress(0x101B0F0, 0x6C0230));
		DefineAddress(SetSize, SelectAddress(0x93BC40, 0xDDE930));
		DefineAddress(GetPosition, SelectAddress(0x93BC50, 0x93B660));
		DefineAddress(SetPosition, SelectAddress(0x93BCB0, 0x93B670));
		DefineAddress(GetAvailable, SelectAddress(0x93BCC0, 0x93B6D0));
		DefineAddress(Read, SelectAddress(0xA37650, 0x93B6E0));
		DefineAddress(Flush, SelectAddress(0x951320, 0xB1FB30));
		DefineAddress(Write, SelectAddress(0x93BB90, 0x950E00));

		DefineAddress(Open, SelectAddress(0x93BB90, 0x93B5A0));
	}

	namespace Addresses(FixedMemoryStream)
	{
		DefineAddress(AddRef, SelectAddress(0x83D030, 0x83F6A0));
		DefineAddress(Release, SelectAddress(0x93BF70, 0x93B820));
		DefineAddress(GetType, SelectAddress(0x93BE00, 0x93B840));
		DefineAddress(GetAccessFlags, SelectAddress(0x5D6800, 0x10E87E0));
		DefineAddress(GetState, SelectAddress(0x1065680, 0xE310C0));
		DefineAddress(Close, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(GetSize, SelectAddress(0x80E390, 0xFC7E10));
		DefineAddress(SetSize, SelectAddress(0x93BE30, 0x93B870));
		DefineAddress(GetPosition, SelectAddress(0x93C110, 0x93B890));
		DefineAddress(SetPosition, SelectAddress(0x93BE50, 0x93B8C0));
		DefineAddress(GetAvailable, SelectAddress(0x93BFC0, 0x93BA10));
		DefineAddress(Read, SelectAddress(0x93BEA0, 0x93B910));
		DefineAddress(Flush, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(Write, SelectAddress(0x93BEE0, 0x93B950));

		DefineAddress(SetData, SelectAddress(0x93BE10, 0x93B850));
	}

	namespace Addresses(MemoryStream)
	{
		DefineAddress(AddRef, SelectAddress(0x83D030, 0x83F6A0));
		DefineAddress(Release, SelectAddress(0x93BF70, 0x93B820));
		DefineAddress(GetType, SelectAddress(0x93BFA0, 0x93B9F0));
		DefineAddress(GetAccessFlags, SelectAddress(0x93BFB0, 0x93BA00));
		DefineAddress(GetState, SelectAddress(0x1065680, 0xE310C0));
		DefineAddress(Close, SelectAddress(0x93C870, 0x93C290));
		DefineAddress(GetSize, SelectAddress(0x80E390, 0xFC7E10));
		DefineAddress(SetSize, SelectAddress(0x93C8C0, 0x93C2E0));
		DefineAddress(GetPosition, SelectAddress(0x93C110, 0x93B890));
		DefineAddress(SetPosition, SelectAddress(0x93C610, 0x93C030));
		DefineAddress(GetAvailable, SelectAddress(0x93BFC0, 0x93BA10));
		DefineAddress(Read, SelectAddress(0x93C140, 0x93BB60));
		DefineAddress(Flush, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(Write, SelectAddress(0x93C6A0, 0x93C0C0));

		DefineAddress(SetData, SelectAddress(0x93C4C0, 0x93BEE0));
		DefineAddress(SetDataRaw, SelectAddress(0x93C380, 0x93BDA0));
		DefineAddress(GetOption, SelectAddress(0x93BFD0, 0x93BA20));
		DefineAddress(SetOption, SelectAddress(0x93C060, 0x93BAB0));
	}

	namespace Addresses(StreamNull)
	{
		DefineAddress(AddRef, SelectAddress(0x93BB60, 0x93C350));
		DefineAddress(Release, SelectAddress(0x93BB70, 0x93C360));
		DefineAddress(GetType, SelectAddress(0x93C920, 0x93C340));
		DefineAddress(GetAccessFlags, SelectAddress(0x5D6800, 0x10E87E0));
		DefineAddress(GetState, SelectAddress(0x1065680, 0xE310C0));
		DefineAddress(Close, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(GetSize, SelectAddress(0x1065680, 0xE310C0));
		DefineAddress(SetSize, SelectAddress(0xB5E030, 0xB7D550));
		DefineAddress(GetPosition, SelectAddress(0x108DD90, 0x111CD70));
		DefineAddress(SetPosition, SelectAddress(0xDDFB10, 0x88A610));
		DefineAddress(GetAvailable, SelectAddress(0x93C930, 0x93C380));
		DefineAddress(Read, SelectAddress(0x93C940, 0x93C390));
		DefineAddress(Flush, SelectAddress(0xA37650, 0xB1FB30));
		DefineAddress(Write, SelectAddress(0xDDFB10, 0x88A610));
	}

	namespace Addresses(XmlWriter)
	{
		DefineAddress(WriteXmlHeader, SelectAddress(0x902040, 0x901C00));
		DefineAddress(BeginElement, SelectAddress(0x902210, 0x901DD0));
		DefineAddress(EndElement, SelectAddress(0x902270, 0x901E30));
		DefineAddress(BeginProcessingInstruction, SelectAddress(0x901D70, 0x901930));
		DefineAddress(EndProcessingInstruction, SelectAddress(0x901DE0, 0x9019A0));
		DefineAddress(AppendAttribute, SelectAddress(0x901E20, 0x9019E0));
		DefineAddress(AppendAttributeF, SelectAddress(0x901EB0, 0x901A70));
		DefineAddress(WriteCharData, SelectAddress(0x901F80, 0x901B40));
		DefineAddress(WriteCDATA, SelectAddress(0x901FB0, 0x901B70));
		DefineAddress(WriteComment, SelectAddress(0x902340, 0x901F00));
		DefineAddress(WriteName, SelectAddress(0x902010, 0x901BD0));
		DefineAddress(WriteText, SelectAddress(0x902470, 0x902030));
	}

	namespace Addresses(File)
	{
		DefineAddress(Exists, SelectAddress(0x9324E0, 0x931F70));
		DefineAddress(Remove, SelectAddress(0x932510, 0x931FA0));
		DefineAddress(GetSize, SelectAddress(0x9325A0, 0x932030));
	}

	namespace Addresses(Directory)
	{
		DefineAddress(Create, SelectAddress(0x932EA0, 0x932930));
		DefineAddress(Exists, SelectAddress(0x9327F0, 0x932280));
		DefineAddress(Remove, SelectAddress(0x932510, 0x932860));
	}
}
#endif
