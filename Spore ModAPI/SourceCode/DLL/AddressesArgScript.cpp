#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\ArgScript\FormatParser.h>
#include <Spore\ArgScript\IBlock.h>
#include <Spore\ArgScript\Lexer.h>
#include <Spore\ArgScript\Line.h>

namespace Addresses(ArgScript)
{
	DefineAddress(CreateStream, SelectAddress(0x841190, 0x840920, 0x8409A0));
}

namespace ArgScript
{
	namespace Addresses(FormatParser)
	{
		// DefineAddress(ReplaceVariables, SelectAddress(0x843F10, , ));

		DefineAddress(AddRef, SelectAddress(0x83D030, 0x83F620, 0x83F6A0));
		DefineAddress(Release, SelectAddress(0x841A80, 0x841210, 0x841290));
		DefineAddress(Initialize, SelectAddress(0x845FB0, 0x845710, 0x845790));
		DefineAddress(Dispose, SelectAddress(0x847680, 0x846DE0, 0x846E60));
		DefineAddress(SetData, SelectAddress(0x841AC0, 0xA6FE50, 0xA6FE70));
		DefineAddress(AddParser, SelectAddress(0x8468D0, 0x846030, 0x8460B0));
		DefineAddress(RemoveParser, SelectAddress(0x8469C0, 0x846120, 0x8461A0));
		DefineAddress(RemoveParserByObject, SelectAddress(0x846940, 0x8460A0, 0x846120));
		DefineAddress(GetParser, SelectAddress(0x8434D0, 0x842C40, 0x842CC0));
		DefineAddress(SetFlag, SelectAddress(0x841D50, 0x8414C0, 0x841540));
		DefineAddress(SetVersionRange, SelectAddress(0x841AD0, 0x841250, 0x8412D0));
		DefineAddress(GetVersion, SelectAddress(0x804E30, 0xFF3480, 0xFF3480));
		DefineAddress(func30h, SelectAddress(0x8477E0, 0x846F40, 0x846FC0));
		DefineAddress(Close, SelectAddress(0x845780, 0x844EF0, 0x844F70));
		DefineAddress(ProcessFile, SelectAddress(0x843520, 0x842C90, 0x842D10));
		DefineAddress(ProcessStream, SelectAddress(0x843810, 0x842F80, 0x843000));
		DefineAddress(ProcessLine, SelectAddress(0x844990, 0x844100, 0x844180));
		DefineAddress(CreateDefinition, SelectAddress(0x845870, 0x844FE0, 0x845060));
		DefineAddress(ProcessFileSafe, SelectAddress(0x841AF0, 0x841270, 0x8412F0));
		DefineAddress(ProcessStreamSafe, SelectAddress(0x841B60, 0x8412E0, 0x841360));
		DefineAddress(ProcessLineSafe, SelectAddress(0x841BD0, 0x841350, 0x8413D0));
		DefineAddress(CreateDefinitionSafe, SelectAddress(0x841C40, 0x8413C0, 0x841440));
		DefineAddress(func58h, SelectAddress(0xC6FF70, 0x8414F0, 0x841570));
		DefineAddress(func5Ch, SelectAddress(0x841D80, 0x841500, 0x841580));
		DefineAddress(func60h, SelectAddress(0x843B00, 0x843270, 0x8432F0));
		DefineAddress(HasParser, SelectAddress(0x843B40, 0x8432B0, 0x843330));
		DefineAddress(HasDefinition, SelectAddress(0x843B90, 0x843300, 0x843380));
		DefineAddress(SetVariable, SelectAddress(0x8473D0, 0x846B30, 0x846BB0));
		DefineAddress(GetVariable, SelectAddress(0x843BE0, 0x843350, 0x8433D0));
		DefineAddress(SetGlobalVariable, SelectAddress(0x846B50, 0x8462B0, 0x846330));
		DefineAddress(func78h, SelectAddress(0x841DB0, 0x841530, 0x8415B0));
		DefineAddress(StartScope, SelectAddress(0x845B20, 0x845290, 0x845310));
		DefineAddress(EndScope, SelectAddress(0x842550, 0x841CC0, 0x841D40));
		DefineAddress(PurgeScope, SelectAddress(0x846CF0, 0x846450, 0x8464D0));
		DefineAddress(GetCurrentScope, SelectAddress(0x841DF0, 0xD1DCD0, 0xD1DCD0));
		DefineAddress(AddBlock, SelectAddress(0x845BA0, 0x845310, 0x845390));
		DefineAddress(AddSpecialBlock, SelectAddress(0x845BE0, 0x845350, 0x8453D0));
		DefineAddress(ParseBool, SelectAddress(0x841CB0, 0x841430, 0x8414B0));
		DefineAddress(ParseFloat, SelectAddress(0x841CC0, 0x841440, 0x8414C0));
		DefineAddress(ParseInt, SelectAddress(0x841CD0, 0x841450, 0x8414D0));
		DefineAddress(ParseUInt, SelectAddress(0x841CD0, 0x841450, 0x8414D0));
		DefineAddress(ParseVector2, SelectAddress(0x841E00, 0x841570, 0x8415F0));
		DefineAddress(ParseVector3, SelectAddress(0x841E50, 0x8415C0, 0x841640));
		DefineAddress(ParseVector4, SelectAddress(0x841ED0, 0x841640, 0x8416C0));
		DefineAddress(ParseColorRGB, SelectAddress(0x841E50, 0x8415C0, 0x841640));
		DefineAddress(ParseColorRGBA, SelectAddress(0x841F70, 0x8416E0, 0x841760));
		DefineAddress(GetLexer, SelectAddress(0x94EBD0, 0xFF3A50, 0xFF3A50));
		DefineAddress(SetTraceStream, SelectAddress(0x842000, 0x841770, 0x8417F0));
		DefineAddress(funcC0h, SelectAddress(0x842040, 0x8417B0, 0x841830));
		DefineAddress(GetTraceStream, SelectAddress(0x8D88F0, 0xFF02D0, 0xFF02D0));
		DefineAddress(funcC8h, SelectAddress(0xFC8510, 0x6C0230, 0x6C0230));
	}

	namespace Addresses(IBlock)
	{
		DefineAddress(AddParser, SelectAddress(0x83D600, 0x83CC90, 0x83CD00));
		DefineAddress(GetParser, SelectAddress(0x83D3D0, 0x83CA60, 0x83CAD0));
	}

	namespace Addresses(Lexer)
	{
		DefineAddress(AddFunction, SelectAddress(0x83E860, 0x83DFE0, 0x83E050));
		DefineAddress(ExpectChar, SelectAddress(0x83DB20, 0x83D2A0, 0x83D310));
		DefineAddress(OptionalExpectChar, SelectAddress(0x83DB70, 0x83D2F0, 0x83D360));
		DefineAddress(NextParameter, SelectAddress(0x83E4E0, 0x83DC60, 0x83DCD0));
	}

	namespace Addresses(Line)
	{
		DefineAddress(GetArgumentsRange, SelectAddress(0x838880, 0x838080, 0x838100));
		DefineAddress(GetArguments, SelectAddress(0x838B80, 0x838380, 0x838400));
		DefineAddress(GetArgumentAt, SelectAddress(0x838780, 0x837F80, 0x838000));
		DefineAddress(GetArgumentsCount, SelectAddress(0x838790, 0x837F90, 0x838010));

		DefineAddress(GetOption, SelectAddress(0x838B90, 0x838390, 0x838410));
		DefineAddress(GetOptionRange, SelectAddress(0x838990, 0x838190, 0x838210));
		DefineAddress(HasFlag, SelectAddress(0x838910, 0x838110, 0x838190));

		DefineAddress(GetEnum, SelectAddress(0x841470, 0x840C00, 0x840C80));
		DefineAddress(GetOptionalEnum, SelectAddress(0x841080, 0x840810, 0x840890));

		DefineAddress(FromString, SelectAddress(0x838C20, 0x838420, 0x8384A0));
	}
}
#endif
