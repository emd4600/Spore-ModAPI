//#ifndef MODAPI_DLL_EXPORT
/****************************************************************************
* Copyright (C) 2026 Rosalie Wanders
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

#include <Spore\Debug\ReportWriter.h>

namespace Debug
{
	auto_METHOD(ReportWriter, void, GetFileNameExtension, Args(char* buffer, size_t size), Args(buffer, size));
	auto_METHOD(ReportWriter, bool, OpenReport, Args(char* param_1), Args(param_1));
	auto_METHOD_(ReportWriter, bool, CloseReport);
	auto_METHOD(ReportWriter, bool, BeginSection, Args(const char* name), Args(name));
	auto_METHOD_(ReportWriter, void, EndSection);
	auto_METHOD(ReportWriter, bool, WriteText, Args(const char* text), Args(text));
	auto_METHOD(ReportWriter, bool, WriteFormatted, Args(const char* text), Args(text));
	auto_METHOD(ReportWriter, bool, WriteKeyValue, Args(const char* key, const char* value), Args(key, value));
	auto_METHOD(ReportWriter, bool, WriteKeyValueFormatted, Args(const char* key, const char* value), Args(key, value));
	auto_METHOD_(ReportWriter, void, WriteBlankLine);
	auto_METHOD(ReportWriter, bool, Write, Args(const char* text, size_t size), Args(text, size));
	auto_METHOD_(ReportWriter, long, GetPosition);
	auto_METHOD(ReportWriter, void, SetPosition, Args(long position), Args(position));
};

//#endif