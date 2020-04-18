#pragma once

#include <Spore\MathUtils.h>

namespace Graphics
{
	struct ShaderDataInformation
	{
		enum DataType
		{
			DATATYPE_NA = 0x0,
			DATATYPE_FLOAT = 0x1,
			DATATYPE_INT = 0x2,
			DATATYPE_BOOL = 0x3,
			DATATYPE_CUSTOM = 0x4,
			DATATYPE_FORCEENUMSIZEINT = 0x7FFFFFFF,
		};

		typedef void(*UnfixCB)(void* data, void* sizeAndAlignment);
		typedef void(*RefixCB)(void* data, void* arenaIterator);
		typedef void(*FixupCB)(void* data, void* arenaIterator);
		typedef void(*UploadCB)(unsigned int startRegister, unsigned int count, bool isVertexShader);

		static void DefaultFix(void*, void*) {};

		int16_t id;
		DataType type;
		int8_t rows;
		int8_t columns;
		const void* externalReference;
		UnfixCB unfixCallback;
		RefixCB refixCallback;
		FixupCB fixupCallback;
		UploadCB uploadCallback;
	};


	struct ShadowMapInfo
	{
		Math::Vector4 mRangeAndStrength; 
		Math::Vector4 mShadowDir;
		Math::Vector4 mNestInfo;
	};
}