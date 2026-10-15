#pragma once

#include <Spore\Internal.h>

namespace Debug
{
	class ReportWriter
	{
	public:
		/* 00h */ // TODO ~ReportWriter();
		/* 04h */ void GetFileNameExtension(char* buffer, size_t size);
		/* 08h */ bool OpenReport(char* param_1); // TODO
		/* 0Ch */ bool CloseReport(void);
		/* 10h */ // TODO
		/* 14h */ // TODO
		/* 18h */ bool BeginSection(const char* name);
		/* 1Ch */ void EndSection(void);
		/* 20h */ bool WriteText(const char* text);
		/* 24h */ bool WriteFormatted(const char* text);
		/* 28h */ bool WriteKeyValue(const char* key, const char* value);
		/* 2Ch */ bool WriteKeyValueFormatted(const char* key, const char* value);
		/* 30h */ void WriteBlankLine(void);
		/* 34h */ bool Write(const char* text, size_t size);
		/* 38h */ long GetPosition(void);
		/* 3Ch */ void SetPosition(long position);
	};

	namespace Addresses(ReportWriter)
	{
		DeclareAddress(GetFileNameExtension);
		DeclareAddress(OpenReport);
		DeclareAddress(CloseReport);
		DeclareAddress(BeginSection);
		DeclareAddress(EndSection);
		DeclareAddress(WriteText);
		DeclareAddress(WriteFormatted);
		DeclareAddress(WriteKeyValue);
		DeclareAddress(WriteKeyValueFormatted);
		DeclareAddress(WriteBlankLine);
		DeclareAddress(Write);
		DeclareAddress(GetPosition);
		DeclareAddress(SetPosition);
	}
}
