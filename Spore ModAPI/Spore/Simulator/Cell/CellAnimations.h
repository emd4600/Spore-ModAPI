#pragma once

#include <Spore\Internal.h>

namespace Simulator
{
	namespace Cell
	{
		enum CellAnimations
		{
			/// 0xAAAA0015
			kAnimIndexCellIdle = 0,
			/// 0xAAAA0016
			kAnimIndexCellIdleBlink1 = 1,
			/// 0xAAAA0017
			kAnimIndexCellIdleBlink2 = 2,
			/// 0xAAAA0018
			kAnimIndexCellIdleBlink3 = 3,
			/// 0xAAAA0019
			kAnimIndexCellMovFlg = 4,
			/// 0xAAAA0020
			kAnimIndexCellMovFlgBlink = 5,
			/// 0xAAAA0005
			kAnimIndexCellEatFilter = 6,
			/// 0xAAAA0000
			kAnimIndexCellDmgSolidSpike = 7,
			/// 0xAAAA0001
			kAnimIndexCellDmgSolidMand = 8,
			/// 0xAAAA0002
			kAnimIndexCellDeathAvatar = 9,
			/// 0xAAAA0003
			kAnimIndexCellDeathNpc = 10,
			/// 0xAAAA0004
			kAnimIndexCellDeathNpcIdle = 11,
			/// 0xAAAA0006
			kAnimIndexCellEatFilterNpc = 12,
			/// 0xAAAA0007
			kAnimIndexCellEatMand = 13,
			/// 0xAAAA0008
			kAnimIndexCellEatMandNpc = 14,
			/// 0xAAAA0009
			kAnimIndexCellEatProb = 15,
			/// 0xAAAA0011
			kAnimIndexCellTakeDmgElec = 16,
			/// 0xAAAA0012
			kAnimIndexCellTakeDmgPoison = 17,
			/// 0xAAAA0013
			kAnimIndexCellTakeDmgStab = 18,
			/// 0xAAAA0021
			kAnimIndexCellMoveJet = 19,
			/// 0xAAAA0022
			kAnimIndexCellMoveJetBlink = 20,
			/// 0xAAAA0019
			kAnimIndexCellMovFlg2 = 21,
			/// 0xAAAA0023
			kAnimIndexCellMoveNpcScared = 22,
			/// 0xAAAA0024
			kAnimIndexCellMoveNpcMad = 23,
			/// 0xAAAA0023
			kAnimIndexCellMoveNpcScared2 = 24,
			/// 0xAAAA0024
			kAnimIndexCellMoveNpcMad2 = 25,
			/// 0xAAAA0021
			kAnimIndexCellMoveJet2 = 26,
			/// 0xAAAA0021
			kAnimIndexCellMoveJet3 = 27,
			/// 0xAAAA0025
			kAnimIndexCellNpcScared = 28,
			/// 0xAAAA0026
			kAnimIndexCellNpcMad = 29,
			/// 0xAAAA0027
			kAnimIndexCellDeathNpcIdle2 = 30,
			/// 0xAAAA0028
			kAnimIndexCellEatFilterFail = 31,
			/// 0xAAAA0029
			kAnimIndexCellEatMandFail = 32,
			/// 0xAAAA0030
			kAnimIndexCellGlanceMad = 33,
			/// 0xAAAA0031
			kAnimIndexCellGlanceSpike = 34,
			/// 0xAAAA0032
			kAnimIndexCellPunctureSpike = 35,
			/// 0xAAAA0033
			kAnimIndexCellGrow = 36,
			/// 0xAAAA0036
			kAnimIndexCellDeathAvatarIdle = 37,
			/// 0xAAAA0037
			kAnimIndexCellElecRelease = 38,
			/// 0xAAAA0038
			kAnimIndexCellBubblePop = 39,
			/// 0xAAAA0039
			kAnimIndexCellEatProbStun = 40,
			/// 0xAAAA0040
			kAnimIndexCellNpcStartled = 41,
			/// 0xAAAA0041
			kAnimIndexCellPoked = 42,
			/// 0xAAAA0042
			kAnimIndexCellTakeDmgElecNpc = 43,
			/// 0xAAAA0043
			kAnimIndexCellTakeDmgPoisonNpc = 44,
			/// 0xAAAA0044
			kAnimIndexCellTakeDmgStabNpc = 45,
			/// 0xAAAA0045
			kAnimIndexCellGlanceSpikeOnSpike = 46,
			/// 0xAAAA0046
			kAnimIndexCellEatProbRetractTrgt = 47,
			/// 0xAAAA0047
			kAnimIndexCellEatProbRetract = 48,
			/// 0xAAAA0048
			kAnimIndexCellEatMandNpcBig = 49,
			/// 0xAAAA0049
			kAnimIndexCellIdleBig = 50,
			/// 0xAAAA0050
			kAnimIndexCellIdleBlink1Big = 51,
			/// 0xAAAA0051
			kAnimIndexCellIdleBlink2Big = 52,
			/// 0xAAAA0052
			kAnimIndexCellIdleBlink3Big = 53,
			/// 0xAAAA0053
			kAnimIndexCellMovFlgBig = 54,
			/// 0xAAAA0054
			kAnimIndexCellMovFlgBigBlink = 55,
			/// 0xAAAA0055
			kAnimIndexCellMovFlgBigMad = 56,
			/// 0xAAAA0056
			kAnimIndexCellMovCilBig = 57,
			/// 0xAAAA0057
			kAnimIndexCellMovCilBigBlink = 58,
			/// 0xAAAA0058
			kAnimIndexCellMovCilBigMad = 59,
			/// 0xAAAA0056
			kAnimIndexCellMovCilBig2 = 60,
			/// 0xAAAA0057
			kAnimIndexCellMovCilBigBlink2 = 61,
			/// 0xAAAA0058
			kAnimIndexCellMovCilBigMad2 = 62,
			/// 0xAAAA0059
			kAnimIndexCellNpcMadBig = 63,
			/// 0xAAAA0060
			kAnimIndexCellMovCil = 64,
			/// 0xAAAA0061
			kAnimIndexCellMovCilBlink = 65,
			/// 0xAAAA0062
			kAnimIndexCellMovPoisonRelease = 66,
			/// 0xAAAA0063
			kAnimIndexCellMovCilMad = 67,
			/// 0xAAAA0064
			kAnimIndexCellMovCilScared = 68,
			/// 0xAAAA0065
			kAnimIndexCellDmgSolidDeath = 69,
			/// 0xAAAA0066
			kAnimIndexCellPoisonRelease = 70,
			/// 0xAAAA0067
			kAnimIndexCellHatchLayEgg = 71,
			/// 0xAAAA0068
			kAnimIndexCellHatchEgg = 72,
			/// 0xAAAA0069
			kAnimIndexCellHatchIce = 73,
			/// 0xAAAA0070
			kAnimIndexCellGoToEditor = 74,
			/// 0xAAAA0071
			kAnimIndexCellDeathEaten = 75,
			/// 0xAAAA0072
			kAnimIndexCellDeathEatenNpc = 76,
			/// 0xAAAA0073
			kAnimIndexCellTakeDmgMand = 77,
			/// 0xAAAA0074
			kAnimIndexCellPartDiscover = 78,
			/// 0xAAAA0075
			kAnimIndexCellEatFilterChew = 79,
			/// 0xAAAA0076
			kAnimIndexCellEatMandChew = 80,
			/// 0xAAAA0077
			kAnimIndexCellEatProbChew = 81,
			/// 0xAAAA0078
			kAnimIndexCellDmgSolidMandNpc = 82,
			/// 0xAAAA0079
			kAnimIndexCellDmgSolidDeathNpc = 83,
			/// 0xAAAA0080
			kAnimIndexCellTakeDmgMandNpc = 84,
			/// 0xAAAA0081
			kAnimIndexCellMovToBeach = 85,
			/// 0xAAAA0082
			kAnimIndexCellGlanceMad2 = 86,
			/// 0xAAAA0083
			kAnimIndexCellMovFlgBigMadBlink = 87,
			/// 0xAAAA0084
			kAnimIndexCellGlanceProbOnProb = 88,
			/// 0xAAAA0085
			kAnimIndexCellMovCil180 = 89,
			/// 0xAAAA0086
			kAnimIndexCellMovCil180v2 = 90,
			/// 0xAAAA0087
			kAnimIndexCellMovCil180v3 = 91,
			/// 0xAAAA0088
			kAnimIndexCellMovCil180v4 = 92,
			/// 0xAAAA0089
			kAnimIndexCellMovCil180v5 = 93,
			/// 0xAAAA0090
			kAnimIndexCellMovFlgStart = 94,
			/// 0xAAAA0090
			kAnimIndexCellMovFlgStart2 = 95,
			/// 0xAAAA0091
			kAnimIndexCellMovCil2 = 96,
			/// 0xAAAA0092
			kAnimIndexCellMoveJet4 = 97,
			/// 0xAAAA0093
			kAnimIndexCellTakeDmgPoisonBig = 98,
			/// 0xAAAA0095
			kAnimIndexCellMovBankLt = 99,
			/// 0xAAAA0096
			kAnimIndexCellMovBankRt = 100,
			/// 0xAAAA0097
			kAnimIndexCellBackgrndGuy = 101,
			/// 0xAAAA0098
			kAnimIndexCellTakeDmgElecNpcBig = 102,
			/// 0xAAAA0099
			kAnimIndexEpicCellEyePokeReact = 103,
			/// 0xAAAA0100
			kAnimIndexEpicCellEyePokeClosedLF = 104,
			/// 0xAAAA0101
			kAnimIndexEpicCellEyePokeClosedRF = 105,
			/// 0xAAAA0102
			kAnimIndexEpicCellEyePokeClosedLC = 106,
			/// 0xAAAA0103
			kAnimIndexEpicCellEyePokeClosedRC = 107,
			/// 0xAAAA0104
			kAnimIndexEpicCellEyePokeClosedLB = 108,
			/// 0xAAAA0105
			kAnimIndexEpicCellEyePokeClosedRB = 109,
			/// 0xAAAA0106
			kAnimIndexEpicCellBiteRock = 110,
			/// 0xAAAA0107
			kAnimIndexEpicCellElectrocuted = 111,
			/// 0xAAAA0108
			kAnimIndexEpicCellChokes = 112,
			/// 0xAAAA0109
			kAnimIndexEpicCellProboscised = 113,
			/// 0xAAAA0110
			kAnimIndexEpicCellDeathTurnover = 114,
			/// 0xAAAA0111
			kAnimIndexEpicCellDeathIdle = 115,
			/// 0xAAAA0112
			kAnimIndexEpicCellEyePokeReactLt = 116,
			/// 0xAAAA0113
			kAnimIndexEpicCellEyePokeReactRt = 117,
			/// 0xAAAA0114
			kAnimIndexCellMate01 = 118,
			/// 0xAAAA0115
			kAnimIndexCellMate02 = 119,
			/// 0xAAAA0116
			kAnimIndexCellMatingCall = 120,
			/// 0xAAAA0117
			kAnimIndexCellEatProbRetractTrgtNpc = 121,
			/// 0xAAAA0118
			kAnimIndexCellEatProbRetractNpc = 122,
			/// 0xAAAA0119
			kAnimIndexCellEatProbStunNpc = 123,
			/// 0xAAAA0120
			kAnimIndexCellEatProbNpc = 124,
			/// 0xAAAA0121
			kAnimIndexCellTakeDmgStabNpcBig = 125,
			/// 0xAAAA0122
			kAnimIndexCellTakeDmgMandNpcBig = 126,
			/// 0xAAAA0123
			kAnimIndexEpicCellPoked = 127,
			/// 0xAAAA0123
			kAnimIndexEpicCellPoked2 = 128,
			/// 0xAAAA0124
			kAnimIndexCellBrainUpgrade = 129,
			/// 0xAAAA0125
			kAnimIndexCellHatchLayEggNpc = 130,
		};

		struct cCellAnimDefinition
		{
			/* 00h */	int field_0;
			/* 04h */	uint32_t animID;
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	int field_10;
			/* 14h */	int field_14;
			/* 18h */	int field_18;
			/* 1Ch */	int field_1C;
			/* 20h */	int field_20;
		};
		ASSERT_SIZE(cCellAnimDefinition, 0x24);
	}
}