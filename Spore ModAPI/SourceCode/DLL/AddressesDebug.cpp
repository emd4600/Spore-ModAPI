#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Debug\ReportWriter.h>

namespace Debug
{
	namespace Addresses(ReportWriter)
	{
		DefineAddress(GetFileNameExtension, SelectAddress(0x0091eee0, 0x0091ec20));
		DefineAddress(OpenReport, SelectAddress(0x0091ef10, 0x0091ec50));
		DefineAddress(CloseReport, SelectAddress(0x0091ef70, 0x0091ecb0));
		DefineAddress(BeginSection, SelectAddress(0x0091efa0, 0x0091ece0));
		DefineAddress(EndSection, SelectAddress(0x0091efd0, 0x0091ed10));
		DefineAddress(WriteText, SelectAddress(0x0091efe0, 0x0091ed20));
		DefineAddress(WriteFormatted, SelectAddress(0x0091f020, 0x0091ed60));
		DefineAddress(WriteKeyValue, SelectAddress(0x0091f070, 0x0091edb0));
		DefineAddress(WriteKeyValueFormatted, SelectAddress(0x0091f0f0, 0x0091ee30));
		DefineAddress(WriteBlankLine, SelectAddress(0x0091f140, 0x0091ee80));
		DefineAddress(Write, SelectAddress(0x0091f150, 0x0091ee90));
		DefineAddress(GetPosition, SelectAddress(0x0091f1b0, 0x0091eef0));
		DefineAddress(SetPosition, SelectAddress(0x0091f1d0, 0x0091ef10));
	};
}

#endif
