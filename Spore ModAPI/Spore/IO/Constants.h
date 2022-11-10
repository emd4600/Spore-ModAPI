#pragma once

#include <Spore\Internal.h>
#include <EASTL\string.h>

namespace IO
{
	typedef size_t size_type;

	/// Used to designate an error condition for many functions that return size_type.
	const size_type kSizeTypeError = (size_type)-1;


	/// Used to designate the condition whereby a requested operation is complete
	/// and no more processing can be done. Only applicable to functions that 
	/// document the use of kSizeTypeDone.
	const size_type kSizeTypeDone = (size_type)-2;


	/// Defines a value to be used for eastl::string conversion functions which means
	/// that the eastl::string length is specified by a wherever the terminating null
	/// character is. For the copying or converting of eastl::strings, the terminating
	/// null character is also copied to the destination.
	const size_t kLengthNull = (size_t)-1;

	enum class FileError : uint32_t
	{
		Success = 0,
		InvalidHandle = 0xFFFFFFFE,
		OutOfMemory = 0xCFDE0002,  // both OutOfMemory and NotEnoughMemory
		FileNotFound = 0xCFDE0004,
		PathNotFound = 0xCFDE0005,  // also INVALID_DRIVE
		AccessDenied = 0xCFDE0006,
		CurrentDirectory = 0xCFDE0008,
		WriteProtect = 0xCFDE0007,
		NotReady = 0xCFDE000B,
		CRC = 0xCFDE000C,
		Other = 0xCFDE000D
	};

	/// Defines stream access flags, much like file access flags.
	enum class AccessFlags : int
	{
		/// No specified flags. Also used to indicate that a given IO stream is closed.
		None = 0x00,  
		/// Used for identifying read access to an entity.
		Read = 0x01,  
		/// Used for identifying write access to an entity.
		Write = 0x02,  
		/// Used for identifying both read and write access to an entity.
		ReadWrite = 0x03   
	};

	/// Creation disposition. Specifies aspects of how to create or not create a file during opening of it.
	enum class CD : int
	{
		/// Fails if file already exists.
		CreateNew = 1,      
		/// Never fails, always opens or creates and truncates to 0.
		CreateAlways = 2,      
		/// Fails if file doesn't exist, keeps contents.
		OpenExisting = 3,      
		/// Never fails, creates if doesn't exist, keeps contents.
		OpenAlways = 4,      
		/// Fails if file doesn't exist, but truncates to 0 if it does.
		TruncateExisting = 5,      
		/// Default (implementation-specific) disposition
		Default = 6       
	};

	/// Defines the positional basis for a user GetPosition or SetPosition action.
	enum class PositionType : int
	{
		/// For GetPosition refers to absolute index of next byte to read; always positive. For SetPosition, refers to absolute index of next byte to be written; always positive.
		Begin = 0,    
		/// For GetPosition always returns zero. For SetPosition, refers to position relative to current position; can be positive or negative.
		Current = 1,
		/// For GetPosition returns to position relative to end (i.e. the negative of bytes left to read); always negative. For SetPosition, refers to position relative to end; can be positive or negative.
		End = 2     
	};

	/// Defines textual line ending property types.
	enum class LineEnd : int
	{
		/// Refers to no line termination. When writing, it means to append nothing.
		None = 0,     
		/// Refers to automatic line termination. When writing, it means to append kLineTerminationNewline if there isn't one already.
		Auto = 1,     
		/// Refers to "\n" line termination. When writing, it means to append a newline always.
		Newline = 2,     
		/// Same as Newline.
		Unix = 2,     
		/// Refers to "\r\n" line termination. When writing, it means to append a newline always.
		Windows = 3      
	};

	enum Share
	{
		/// No sharing.
		kShareNone = 0x00,     
		/// Allow sharing for reading.
		kShareRead = 0x01,     
		/// Allow sharing for writing.
		kShareWrite = 0x02,     
		/// Allow sharing for deletion.
		kShareDelete = 0x04      
	};

	enum UsageHints
	{
		kUsageHintNone = 0x00,
		kUsageHintSequential = 0x01,
		kUsageHintRandom = 0x02
	};

	/// Defines state values or function return values. Zero means success and non-zero means failure in general.
	/// Note that various stream types may define their own errors in addition to these generic errors.
	enum State
	{
		kStateSuccess = 0,
		kStateError = -1,
		kStateNotOpen = -2
	};

	/// Defines endian-ness. This is appropriate for working with binary numerical data. 
	enum class Endian : int
	{
		/// Big endian.
		Big = 0,        
		/// Little endian.
		Little = 1,            
#ifdef EA_SYSTEM_BIG_ENDIAN
		/// Whatever endian is native to the machine.
		Local = Big    
#else 
		/// Whatever endian is native to the machine.
		Local = Little 
#endif
	};


	/// Ensures the given path finishes with a path separator ('/' or '\' depending on the OS),
	/// modifying it if necessary.
	/// @param path
	/// @returns
	bool EnsureTrailingPathSeparator(eastl::string16& path);

	int ConcatenatePathComponents(char16_t* dstPath, const char16_t* component1, const char16_t* component2);

	namespace Directory
	{
		/// Returns true if the given path is an existing folder in the users disk.
		/// @param path
		/// @returns
		bool Exists(const char16_t* path);

		bool Create(const char16_t* path);

		bool Remove(const char16_t* path, bool recursive);
	}

	namespace File
	{
		/// Returns true if the given path is an existing file in the users disk.
		/// @param path
		/// @returns
		bool Exists(const char16_t* path);

		bool Remove(const char16_t* path);

		unsigned int GetSize(const char16_t* path);
	}

	namespace Addresses(File)
	{
		DeclareAddress(Exists);  // 0x9324E0 0x931F70
		DeclareAddress(Remove);  // 0x932510 0x931FA0
		DeclareAddress(GetSize);  // 0x9325A0 0x932030
	}

	namespace Addresses(Directory)
	{
		DeclareAddress(Create);  // 0x932EA0 0x932930
		DeclareAddress(Exists);  // 0x9327F0 0x932280
		DeclareAddress(Remove);  // 0x932510 0x932860
	}
}

namespace Addresses(IO)
{
	DeclareAddress(EnsureTrailingPathSeparator);  // 0x931CC0 0x931740
	DeclareAddress(ConcatenatePathComponents);  // 0x930200 0x9300D0
}