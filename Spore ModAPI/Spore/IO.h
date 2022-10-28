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

/// @file IO.h
/// This file includes all the necessary headers in order to work with file input/output.

/// @namespace IO
///
/// @brief Classes to work with file input/output, that is, reading and writing data into files.
///
/// The main concept of this namespace is that of "streams", which are objects where data can be read form/written into.
/// It's abstract representation is IO::IStream, which defines all the operations you can do to a stream.
/// There are several subclasses to it, depending on the type of stream: use IO::FileStream if you want to write a
/// disk file.
/// Before you can use a stream, you have to call IO::IStream::Open() with the appropriate parameters (it depends on whether you
/// want to create a new file, read or write, etc). AFter you are finished writing, call IO::IStream::Close() so the
/// system releases the stream resources.

#include <Spore\IO\IStream.h>
#include <Spore\IO\FileStream.h>
#include <Spore\IO\StreamAdapter.h>
#include <Spore\IO\StreamBuffer.h>
#include <Spore\IO\StreamChild.h>
#include <Spore\IO\StreamFixedMemory.h>
#include <Spore\IO\StreamMemory.h>
#include <Spore\IO\StreamNull.h>
#include <Spore\IO\XmlWriter.h>

/// @namespace IO
///
/// The IO namespace contains classes used to work with file input/output. The IStream interfaces defines the methods needed
/// to read/write a file (not all IStreams support reading/writing). Then there are specific implementations, the most notable of
/// which are:
/// - FileStream: Used for reading files in the file system.
/// - MemoryStream: Used for reading files from the memory.
///
/// The IO namespace itself also contains several methods for reading/writing specific types of data, for example IO::ReadInt32(),
/// IO::WriteUInt(),...
///
/// There's also a class called XmlWriter which can be used to easily write simple files in the XML format.
///