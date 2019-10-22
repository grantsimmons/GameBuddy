#ifndef _CPU_
#define _CPU_

#include <cstdint>
#include <string>
#include "MMU.h"

class Z80{
	private:
        struct clock{
            uint64_t m, t;
        }_clock;

        struct r{
            uint8_t a, b, c, d, e, h, l, f, m, t;
            uint16_t pc, sp;

        }_r;

		//enum op_map : uint8_t{
		std::string arr[0x100] = {
			"NOP", //00
			"LDBCnn",
			"LDmBCA",
			"INCBC",
			"INCB",
			"DECB",
			"LDBn",
			"RLCA",
			"LDmnnSP",
			"ADDHLBC",
			"LDAmBC",
			"DECBC",
			"INCC",
			"DECC",
			"LDCn",
			"RRCA",

			"STOP", //10
			"LDDEnn",
			"LDmDEA",
			"INCDE",
			"INCD",
			"DECD",
			"LDDn",
			"RLA",
			"JRn",
			"ADDHLDE",
			"LDAmDE",
			"DECDE",
			"INCE",
			"DECE",
			"LDEn",
			"RRA",

			"JRNZn", //20
			"LDHLnn",
			"LDImHLA",
			"INCHL",
			"INCH",
			"DECH",
			"LDHn",
			"DAA",
			"JRZn",
			"ADDHLHL",
			"LDImHL",
			"DECHL",
			"INCL",
			"DECL",
			"LDLn",
			"NOT", //CPL

			"JRNCn", //30
			"LDSPnn",
			"LDDmHLA",
			"INCSP",
			"INCmHL",
			"DECmHL",
			"LDmHLn",
			"SCF",
			"JRCn",
			"ADDHLSP",
			"LDDAmHL",
			"DECSP",
			"INCA",
			"DECA",
			"LDAn",
			"CCF",

			"LDBB", //40
			"LDBC",
			"LDBD",
			"LDBE",
			"LDBH",
			"LDBL",
			"LDBmHL",
			"LDBA",
			"LDCB",
			"LDCC",
			"LDCD",
			"LDCE",
			"LDCH",
			"LDCL",
			"LDCmHL",
			"LDCA",

			"LDDB", //50
			"LDDC",
			"LDDD",
			"LDDE",
			"LDDH",
			"LDDL",
			"LDDmHL",
			"LDDA",
			"LDEB",
			"LDEC",
			"LDED",
			"LDEE",
			"LDEH",
			"LDEL",
			"LDEmHL",
			"LDEA",

			"LDHB", //60
			"LDHC",
			"LDHD",
			"LDHE",
			"LDHH",
			"LDHL",
			"LDHmHL",
			"LDHA",
			"LDLB",
			"LDLC",
			"LDLD",
			"LDLE",
			"LDLH",
			"LDLL",
			"LDLmHL",
			"LDLA",

			"LDmHLB", //70
			"LDmHLC",
			"LDmHLD",
			"LDmHLE",
			"LDmHLH",
			"LDmHLL",
			"HALT",
			"LDmHLA",
			"LDAB",
			"LDAC",
			"LDAD",
			"LDAE",
			"LDAH",
			"LDAL",
			"LDAmHL",
			"LDAA",

			"ADDAB", //80
			"ADDAC",
			"ADDAD",
			"ADDAE",
			"ADDAH",
			"ADDAL",
			"ADDAmHL",
			"ADDAA",
			"ADCAB",
			"ADCAC",
			"ADCAD",
			"ADCAE",
			"ADCAH",
			"ADCAL",
			"ADCAmHL",
			"ADCAA",

			"SUBAB", //90
			"SUBAC",
			"SUBAD",
			"SUBAE",
			"SUBAH",
			"SUBAL",
			"SUBAmHL",
			"SUBAA",
			"SBCAB",
			"SBCAC",
			"SBCAD",
			"SBCAE",
			"SBCAH",
			"SBCAL",
			"SBCAmHL",
			"SBCAA",

			"ANDB", //A0
			"ANDC",
			"ANDD",
			"ANDE",
			"ANDH",
			"ANDL",
			"ANDmHL",
			"ANDA",
			"XORB",
			"XORC",
			"XORD",
			"XORE",
			"XORH",
			"XORL",
			"XORmHL",
			"XORA",

			"ORB", //B0
			"ORC",
			"ORD",
			"ORE",
			"ORH",
			"ORL",
			"ORmHL",
			"ORA",
			"CPB",
			"CPC",
			"CPD",
			"CPE",
			"CPH",
			"CPL",
			"CPmHL",
			"CPA",

			"RETNZ", //C0
			"POPBC",
			"JPNZnn",
			"JPnn",
			"CALLNZnn",
			"PUSHBC",
			"ADDAn",
			"RST0",
			"RETZ",
			"RET",
			"JPZnn",
			"Extops",
			"CALLZnn",
			"CALLnn",
			"ADCAn",
			"RST8",

			"RETNC", //D0
			"POPDE",
			"JPNCnn",
			"XX1",
			"CALLNCnn",
			"PUSHDE",
			"SUBAn",
			"RST10",
			"RETC",
			"RETI",
			"JPCnn",
			"XX2",
			"CALLCnn",
			"XX3",
			"SBCAn",
			"RST18",

			"LDHmnA", //E0
			"POPHL",
			"LDHmCA",
			"XX4",
			"XX5",
			"PUSHHL",
			"ANDn",
			"RST20",
			"ADDSPd",
			"JPmHL",
			"LDmnnA",
			"XX6",
			"XX7",
			"XX8",
			"XORn",
			"RST28",

			"LDHAmn", //F0
			"POPAF",
			"XX9",
			"DI",
			"XXA",
			"PUSHAF",
			"ORn",
			"RST30",
			"LDHLSPd",
			"LDSPHL",
			"LDAmnn",
			"EI",
			"XXB",
			"XXC",
			"CPn",
			"RST38"
		};
		//}_op_map;
        
        MMU mmu;
		
	public:

		Z80(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e,  uint8_t h, 
			uint8_t l, uint8_t f, uint8_t m, uint8_t t, uint16_t pc, uint16_t sp,
			uint64_t cm, uint64_t ct); //Initial State

		

		void reset();

		//Debugging
		void status();


}z80(0,0,0,0,0,0,0,0,0,0,0,0xfffe,0,0);

#endif
