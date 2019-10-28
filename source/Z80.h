#ifndef _CPU_
#define _CPU_

#include <iostream>
#include "MMU.h"

class Z80{
	public:

		Z80(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e,  uint8_t h, 
			uint8_t l, uint8_t f, uint8_t m, uint8_t t, uint16_t pc, uint16_t sp,
			uint64_t cm, uint64_t ct); //Initial State

		void exec();

		void reset();

		//Debugging
		void status();
        void debug();

		//OPs
		void NOP();
		void LDBCnn();
		void LDmBCA();
		void INCBC();
		void INCB();
		void DECB();
		void LDBn();
		void RLCA();
		void LDmnnSP();
		void ADDHLBC();
		void LDAmBC();
		void DECBC();
		void INCC();
		void DECC();
		void LDCn();
		void RRCA();
		void STOP();
		void LDDEnn();
		void LDmDEA();
		void INCDE();
		void INCD();
		void DECD();
		void LDDn();
		void RLA();
		void JRn();
		void ADDHLDE();
		void LDAmDE();
		void DECDE();
		void INCE();
		void DECE();
		void LDEn();
		void RRA();
		void JRNZn();
		void LDHLnn();
		void LDImHLA();
		void INCHL();
		void INCH();
		void DECH();
		void LDHn();
		void DAA();
		void JRZn();
		void ADDHLHL();
		void LDIAmHL();
		void DECHL();
		void INCL();
		void DECL();
		void LDLn();
		void NOT();
		void JRNCn();
		void LDSPnn();
		void LDDmHLA();
		void INCSP();
		void INCmHL();
		void DECmHL();
		void LDmHLn();
		void SCF();
		void JRCn();
		void ADDHLSP();
		void LDDAmHL();
		void DECSP();
		void INCA();
		void DECA();
		void LDAn();
		void CCF();
		void LDBB();
		void LDBC();
		void LDBD();
		void LDBE();
		void LDBH();
		void LDBL();
		void LDBmHL();
		void LDBA();
		void LDCB();
		void LDCC();
		void LDCD();
		void LDCE();
		void LDCH();
		void LDCL();
		void LDCmHL();
		void LDCA();
		void LDDB();
		void LDDC();
		void LDDD();
		void LDDE();
		void LDDH();
		void LDDL();
		void LDDmHL();
		void LDDA();
		void LDEB();
		void LDEC();
		void LDED();
		void LDEE();
		void LDEH();
		void LDEL();
		void LDEmHL();
		void LDEA();
		void LDHB();
		void LDHC();
		void LDHD();
		void LDHE();
		void LDHH();
		void LDHL();
		void LDHmHL();
		void LDHA();
		void LDLB();
		void LDLC();
		void LDLD();
		void LDLE();
		void LDLH();
		void LDLL();
		void LDLmHL();
		void LDLA();
		void LDmHLB();
		void LDmHLC();
		void LDmHLD();
		void LDmHLE();
		void LDmHLH();
		void LDmHLL();
		void HALT();
		void LDmHLA();
		void LDAB();
		void LDAC();
		void LDAD();
		void LDAE();
		void LDAH();
		void LDAL();
		void LDAmHL();
		void LDAA();
		void ADDAB();
		void ADDAC();
		void ADDAD();
		void ADDAE();
		void ADDAH();
		void ADDAL();
		void ADDAmHL();
		void ADDAA();
		void ADCAB();
		void ADCAC();
		void ADCAD();
		void ADCAE();
		void ADCAH();
		void ADCAL();
		void ADCAmHL();
		void ADCAA();
		void SUBAB();
		void SUBAC();
		void SUBAD();
		void SUBAE();
		void SUBAH();
		void SUBAL();
		void SUBAmHL();
		void SUBAA();
		void SBCAB();
		void SBCAC();
		void SBCAD();
		void SBCAE();
		void SBCAH();
		void SBCAL();
		void SBCAmHL();
		void SBCAA();
		void ANDB();
		void ANDC();
		void ANDD();
		void ANDE();
		void ANDH();
		void ANDL();
		void ANDmHL();
		void ANDA();
		void XORB();
		void XORC();
		void XORD();
		void XORE();
		void XORH();
		void XORL();
		void XORmHL();
		void XORA();
		void ORB();
		void ORC();
		void ORD();
		void ORE();
		void ORH();
		void ORL();
		void ORmHL();
		void ORA();
		void CPB();
		void CPC();
		void CPD();
		void CPE();
		void CPH();
		void CPL();
		void CPmHL();
		void CPA();
		void RETNZ();
		void POPBC();
		void JPNZnn();
		void JPnn();
		void CALLNZnn();
		void PUSHBC();
		void ADDAn();
		void RST0();
		void RETZ();
		void RET();
		void JPZnn();
		void Extops();
		void CALLZnn();
		void CALLnn();
		void ADCAn();
		void RST8();
		void RETNC();
		void POPDE();
		void JPNCnn();
		void XX1();
		void CALLNCnn();
		void PUSHDE();
		void SUBAn();
		void RST10();
		void RETC();
		void RETI();
		void JPCnn();
		void XX2();
		void CALLCnn();
		void XX3();
		void SBCAn();
		void RST18();
		void LDHmnA();
		void POPHL();
		void LDHmCA();
		void XX4();
		void XX5();
		void PUSHHL();
		void ANDn();
		void RST20();
		void ADDSPd();
		void JPmHL();
		void LDmnnA();
		void XX6();
		void XX7();
		void XX8();
		void XORn();
		void RST28();
		void LDHAmn();
		void POPAF();
		void XX9();
		void DI();
		void XXA();
		void PUSHAF();
		void ORn();
		void RST30();
		void LDHLSPd();
		void LDSPHL();
		void LDAmnn();
		void EI();
		void XXB();
		void XXC();
		void CPn();
		void RST38();
	private:
        struct{
            uint64_t m, t;
        }_clock;

        struct{
            uint8_t a, b, c, d, e, h, l, f, m, t;
            uint16_t pc, sp;

        }_r;

		struct op_pointer{ //TODO: Split ops into separate file
			void (Z80::*op_function)(void);
			std::string op; //Debugging purposes
		};

		const op_pointer ops[0x100] = {
			{&Z80::NOP, "NOP"}, //00
			{&Z80::LDBCnn, "LDBCnn"},
			{&Z80::LDmBCA, "LDmBCA"},
			{&Z80::INCBC, "INCBC"},
			{&Z80::INCB, "INCB"},
			{&Z80::DECB, "DECB"},
			{&Z80::LDBn, "LDBn"},
			{&Z80::RLCA, "RLCA"},
			{&Z80::LDmnnSP, "LDmnnSP"},
			{&Z80::ADDHLBC, "ADDHLBC"},
			{&Z80::LDAmBC, "LDAmBC"},
			{&Z80::DECBC, "DECBC"},
			{&Z80::INCC, "INCC"},
			{&Z80::DECC, "DECC"},
			{&Z80::LDCn, "LDCn"},
			{&Z80::RRCA, "RRCA"},

			{&Z80::STOP, "STOP"}, //10
			{&Z80::LDDEnn, "LDDEnn"},
			{&Z80::LDmDEA, "LDmDEA"},
			{&Z80::INCDE, "INCDE"},
			{&Z80::INCD, "INCD"},
			{&Z80::DECD, "DECD"},
			{&Z80::LDDn, "LDDn"},
			{&Z80::RLA, "RLA"},
			{&Z80::JRn, "JRn"},
			{&Z80::ADDHLDE, "ADDHLDE"},
			{&Z80::LDAmDE, "LDAmDE"},
			{&Z80::DECDE, "DECDE"},
			{&Z80::INCE, "INCE"},
			{&Z80::DECE, "DECE"},
			{&Z80::LDEn, "LDEn"},
			{&Z80::RRA, "RRA"},

			{&Z80::JRNZn, "JRNZn"}, //20
			{&Z80::LDHLnn, "LDHLnn"},
			{&Z80::LDImHLA, "LDImHLA"},
			{&Z80::INCHL, "INCHL"},
			{&Z80::INCH, "INCH"},
			{&Z80::DECH, "DECH"},
			{&Z80::LDHn, "LDHn"},
			{&Z80::DAA, "DAA"},
			{&Z80::JRZn, "JRZn"},
			{&Z80::ADDHLHL, "ADDHLHL"},
			{&Z80::LDIAmHL, "LDIAmHL"},
			{&Z80::DECHL, "DECHL"},
			{&Z80::INCL, "INCL"},
			{&Z80::DECL, "DECL"},
			{&Z80::LDLn, "LDLn"},
			{&Z80::NOT, "NOT"}, //CPL

			{&Z80::JRNCn, "JRNCn"}, //30
			{&Z80::LDSPnn, "LDSPnn"},
			{&Z80::LDDmHLA, "LDDmHLA"},
			{&Z80::INCSP, "INCSP"},
			{&Z80::INCmHL, "INCmHL"},
			{&Z80::DECmHL, "DECmHL"},
			{&Z80::LDmHLn, "LDmHLn"},
			{&Z80::SCF, "SCF"},
			{&Z80::JRCn, "JRCn"},
			{&Z80::ADDHLSP, "ADDHLSP"},
			{&Z80::LDDAmHL, "LDDAmHL"},
			{&Z80::DECSP, "DECSP"},
			{&Z80::INCA, "INCA"},
			{&Z80::DECA, "DECA"},
			{&Z80::LDAn, "LDAn"},
			{&Z80::CCF, "CCF"},

			{&Z80::LDBB, "LDBB"}, //40
			{&Z80::LDBC, "LDBC"},
			{&Z80::LDBD, "LDBD"},
			{&Z80::LDBE, "LDBE"},
			{&Z80::LDBH, "LDBH"},
			{&Z80::LDBL, "LDBL"},
			{&Z80::LDBmHL, "LDBmHL"},
			{&Z80::LDBA, "LDBA"},
			{&Z80::LDCB, "LDCB"},
			{&Z80::LDCC, "LDCC"},
			{&Z80::LDCD, "LDCD"},
			{&Z80::LDCE, "LDCE"},
			{&Z80::LDCH, "LDCH"},
			{&Z80::LDCL, "LDCL"},
			{&Z80::LDCmHL, "LDCmHL"},
			{&Z80::LDCA, "LDCA"},

			{&Z80::LDDB, "LDDB"}, //50
			{&Z80::LDDC, "LDDC"},
			{&Z80::LDDD, "LDDD"},
			{&Z80::LDDE, "LDDE"},
			{&Z80::LDDH, "LDDH"},
			{&Z80::LDDL, "LDDL"},
			{&Z80::LDDmHL, "LDDmHL"},
			{&Z80::LDDA, "LDDA"},
			{&Z80::LDEB, "LDEB"},
			{&Z80::LDEC, "LDEC"},
			{&Z80::LDED, "LDED"},
			{&Z80::LDEE, "LDEE"},
			{&Z80::LDEH, "LDEH"},
			{&Z80::LDEL, "LDEL"},
			{&Z80::LDEmHL, "LDEmHL"},
			{&Z80::LDEA, "LDEA"},

			{&Z80::LDHB, "LDHB"}, //60
			{&Z80::LDHC, "LDHC"},
			{&Z80::LDHD, "LDHD"},
			{&Z80::LDHE, "LDHE"},
			{&Z80::LDHH, "LDHH"},
			{&Z80::LDHL, "LDHL"},
			{&Z80::LDHmHL, "LDHmHL"},
			{&Z80::LDHA, "LDHA"},
			{&Z80::LDLB, "LDLB"},
			{&Z80::LDLC, "LDLC"},
			{&Z80::LDLD, "LDLD"},
			{&Z80::LDLE, "LDLE"},
			{&Z80::LDLH, "LDLH"},
			{&Z80::LDLL, "LDLL"},
			{&Z80::LDLmHL, "LDLmHL"},
			{&Z80::LDLA, "LDLA"},

			{&Z80::LDmHLB, "LDmHLB"}, //70
			{&Z80::LDmHLC, "LDmHLC"},
			{&Z80::LDmHLD, "LDmHLD"},
			{&Z80::LDmHLE, "LDmHLE"},
			{&Z80::LDmHLH, "LDmHLH"},
			{&Z80::LDmHLL, "LDmHLL"},
			{&Z80::HALT, "HALT"},
			{&Z80::LDmHLA, "LDmHLA"},
			{&Z80::LDAB, "LDAB"},
			{&Z80::LDAC, "LDAC"},
			{&Z80::LDAD, "LDAD"},
			{&Z80::LDAE, "LDAE"},
			{&Z80::LDAH, "LDAH"},
			{&Z80::LDAL, "LDAL"},
			{&Z80::LDAmHL, "LDAmHL"},
			{&Z80::LDAA, "LDAA"},

			{&Z80::ADDAB, "ADDAB"}, //80
			{&Z80::ADDAC, "ADDAC"},
			{&Z80::ADDAD, "ADDAD"},
			{&Z80::ADDAE, "ADDAE"},
			{&Z80::ADDAH, "ADDAH"},
			{&Z80::ADDAL, "ADDAL"},
			{&Z80::ADDAmHL, "ADDAmHL"},
			{&Z80::ADDAA, "ADDAA"},
			{&Z80::ADCAB, "ADCAB"},
			{&Z80::ADCAC, "ADCAC"},
			{&Z80::ADCAD, "ADCAD"},
			{&Z80::ADCAE, "ADCAE"},
			{&Z80::ADCAH, "ADCAH"},
			{&Z80::ADCAL, "ADCAL"},
			{&Z80::ADCAmHL, "ADCAmHL"},
			{&Z80::ADCAA, "ADCAA"},

			{&Z80::SUBAB, "SUBAB"}, //90
			{&Z80::SUBAC, "SUBAC"},
			{&Z80::SUBAD, "SUBAD"},
			{&Z80::SUBAE, "SUBAE"},
			{&Z80::SUBAH, "SUBAH"},
			{&Z80::SUBAL, "SUBAL"},
			{&Z80::SUBAmHL, "SUBAmHL"},
			{&Z80::SUBAA, "SUBAA"},
			{&Z80::SBCAB, "SBCAB"},
			{&Z80::SBCAC, "SBCAC"},
			{&Z80::SBCAD, "SBCAD"},
			{&Z80::SBCAE, "SBCAE"},
			{&Z80::SBCAH, "SBCAH"},
			{&Z80::SBCAL, "SBCAL"},
			{&Z80::SBCAmHL, "SBCAmHL"},
			{&Z80::SBCAA, "SBCAA"},

			{&Z80::ANDB, "ANDB"}, //A0
			{&Z80::ANDC, "ANDC"},
			{&Z80::ANDD, "ANDD"},
			{&Z80::ANDE, "ANDE"},
			{&Z80::ANDH, "ANDH"},
			{&Z80::ANDL, "ANDL"},
			{&Z80::ANDmHL, "ANDmHL"},
			{&Z80::ANDA, "ANDA"},
			{&Z80::XORB, "XORB"},
			{&Z80::XORC, "XORC"},
			{&Z80::XORD, "XORD"},
			{&Z80::XORE, "XORE"},
			{&Z80::XORH, "XORH"},
			{&Z80::XORL, "XORL"},
			{&Z80::XORmHL, "XORmHL"},
			{&Z80::XORA, "XORA"},

			{&Z80::ORB, "ORB"}, //B0
			{&Z80::ORC, "ORC"},
			{&Z80::ORD, "ORD"},
			{&Z80::ORE, "ORE"},
			{&Z80::ORH, "ORH"},
			{&Z80::ORL, "ORL"},
			{&Z80::ORmHL, "ORmHL"},
			{&Z80::ORA, "ORA"},
			{&Z80::CPB, "CPB"},
			{&Z80::CPC, "CPC"},
			{&Z80::CPD, "CPD"},
			{&Z80::CPE, "CPE"},
			{&Z80::CPH, "CPH"},
			{&Z80::CPL, "CPL"},
			{&Z80::CPmHL, "CPmHL"},
			{&Z80::CPA, "CPA"},

			{&Z80::RETNZ, "RETNZ"}, //C0
			{&Z80::POPBC, "POPBC"},
			{&Z80::JPNZnn, "JPNZnn"},
			{&Z80::JPnn, "JPnn"},
			{&Z80::CALLNZnn, "CALLNZnn"},
			{&Z80::PUSHBC, "PUSHBC"},
			{&Z80::ADDAn, "ADDAn"},
			{&Z80::RST0, "RST0"},
			{&Z80::RETZ, "RETZ"},
			{&Z80::RET, "RET"},
			{&Z80::JPZnn, "JPZnn"},
			{&Z80::Extops, "Extops"},
			{&Z80::CALLZnn, "CALLZnn"},
			{&Z80::CALLnn, "CALLnn"},
			{&Z80::ADCAn, "ADCAn"},
			{&Z80::RST8, "RST8"},

			{&Z80::RETNC, "RETNC"}, //D0
			{&Z80::POPDE, "POPDE"},
			{&Z80::JPNCnn, "JPNCnn"},
			{&Z80::XX1, "XX1"},
			{&Z80::CALLNCnn, "CALLNCnn"},
			{&Z80::PUSHDE, "PUSHDE"},
			{&Z80::SUBAn, "SUBAn"},
			{&Z80::RST10, "RST10"},
			{&Z80::RETC, "RETC"},
			{&Z80::RETI, "RETI"},
			{&Z80::JPCnn, "JPCnn"},
			{&Z80::XX2, "XX2"},
			{&Z80::CALLCnn, "CALLCnn"},
			{&Z80::XX3, "XX3"},
			{&Z80::SBCAn, "SBCAn"},
			{&Z80::RST18, "RST18"},

			{&Z80::LDHmnA, "LDHmnA"}, //E0
			{&Z80::POPHL, "POPHL"},
			{&Z80::LDHmCA, "LDHmCA"},
			{&Z80::XX4, "XX4"},
			{&Z80::XX5, "XX5"},
			{&Z80::PUSHHL, "PUSHHL"},
			{&Z80::ANDn, "ANDn"},
			{&Z80::RST20, "RST20"},
			{&Z80::ADDSPd, "ADDSPd"},
			{&Z80::JPmHL, "JPmHL"},
			{&Z80::LDmnnA, "LDmnnA"},
			{&Z80::XX6, "XX6"},
			{&Z80::XX7, "XX7"},
			{&Z80::XX8, "XX8"},
			{&Z80::XORn, "XORn"},
			{&Z80::RST28, "RST28"},

			{&Z80::LDHAmn, "LDHAmn"}, //F0
			{&Z80::POPAF, "POPAF"},
			{&Z80::XX9, "XX9"},
			{&Z80::DI, "DI"},
			{&Z80::XXA, "XXA"},
			{&Z80::PUSHAF, "PUSHAF"},
			{&Z80::ORn, "ORn"},
			{&Z80::RST30, "RST30"},
			{&Z80::LDHLSPd, "LDHLSPd"},
			{&Z80::LDSPHL, "LDSPHL"},
			{&Z80::LDAmnn, "LDAmnn"},
			{&Z80::EI, "EI"},
			{&Z80::XXB, "XXB"},
			{&Z80::XXC, "XXC"},
			{&Z80::CPn, "CPn"},
			{&Z80::RST38, "RST38"}
		};

        MMU mmu;
		
};
//}z80(29,0,0,0,0,0,0,0,0,0,0,0x0000,0,0);
#endif       
