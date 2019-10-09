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

/// 
/// @page io Input/Output Streams
///
/// This page contains information about file input/output, that is, all the classes and methods contained in the IO
/// namespace. To use the more important ones, you need to include the header IO.h
///
/// @tableofcontents
///
/// @section io_tutorial1 Tutorial: Open a file stream form the disk
///
/// Opening a stream from a file in the disk is really simple, you just have to use the IO::FileStream class:
/// ~~~~~~~~~~~~~~~~~~~{.cpp}
/// IO::IStream* pStream = new IO::FileStream("C:\\Users\\Modder\\Desktop\\VeryImportantFile.bin");
/// // now use the stream as you would with any IStream
/// ~~~~~~~~~~~~~~~~~~~
///
/// @section more_info More information:
/// - IO::IStream
/// - IO::FileStream
/// - IO::MemoryStream
/// - IO
///