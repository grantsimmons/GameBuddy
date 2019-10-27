#ifndef _CPU_
#define _CPU_

#include <cstdint>
#include <string>
#include <iostream>
#include "MMU.h"

//#include "ops.h"

class Z80{
	public:

		Z80(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e,  uint8_t h, 
			uint8_t l, uint8_t f, uint8_t m, uint8_t t, uint16_t pc, uint16_t sp,
			uint64_t cm, uint64_t ct); //Initial State

		void exec();

		void reset();

		//Debugging
		void status();

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
		
}z80(0,0,0,0,0,0,0,0,0,0,0,0x0000,0,0);
             

void Z80::NOP(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDBCnn(){
    this->_r.c = this->mmu.rb(this->_r.pc);
    this->_r.b = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
}

void Z80::LDmBCA(){
    this->mmu.wb(this->_r.b << 8 + this->_r.c, this->_r.a);
}

void Z80::INCBC(){
    this->_r.b += 1;
    this->_r.c = this->_r.b == 0x00 ? this->_r.c + 1 : this->_r.c;
    //Set OF, Z, etc.
}

void Z80::INCB(){
    this->_r.b += 1;
    //Set OF, Z, etc.
}

void Z80::DECB(){
    this->_r.b -= 1;
    //Set UF, Z, etc.
}

void Z80::LDBn(){
    this->_r.b = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::RLCA(){
    this->_r.f = this->_r.a & 0x80; //FIXME: Carry flag position
    this->_r.a = this->_r.a << 1 + ((this->_r.a & 0x80) >> 7);
}

void Z80::LDmnnSP(){
    this->mmu.ww(this->mmu.rb(this->_r.pc) + (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.sp);
    this->_r.pc += 2;
}

void Z80::ADDHLBC(){
}

void Z80::LDAmBC(){
    this->_r.a = this->mmu.rb(this->_r.b << 8 + this->_r.c);
}

void Z80::DECBC(){
    this->_r.b -= 1;
    this->_r.c = this->_r.b == 0xFF ? this->_r.c - 1 : this->_r.c;
    //Set UF, Z, etc.
}

void Z80::INCC(){
    this->_r.c += 1;
    //Set OF, Z, etc.
}

void Z80::DECC(){
    this->_r.c -= 1;
    //Set UF, Z, etc.
}

void Z80::LDCn(){
    this->_r.c = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::RRCA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::STOP(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDDEnn(){
    this->_r.e = this->mmu.rb(this->_r.pc);
    this->_r.d = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
}

void Z80::LDmDEA(){
    this->mmu.wb(this->_r.d << 8 + this->_r.e, this->_r.a);
}

void Z80::INCDE(){
    this->_r.d += 1;
    this->_r.e = this->_r.d == 0x00 ? this->_r.e + 1 : this->_r.e;
    //Set OF, Z, etc.
}

void Z80::INCD(){
    this->_r.d += 1;
    //Set OF, Z, etc.
}

void Z80::DECD(){
    this->_r.d -= 1;
    //Set UF, Z, etc.
}

void Z80::LDDn(){
    this->_r.d = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::RLA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADDHLDE(){
}

void Z80::LDAmDE(){
    this->_r.a = this->mmu.rb(this->_r.d << 8 + this->_r.e);
}

void Z80::DECDE(){
    this->_r.d -= 1;
    this->_r.e = this->_r.d == 0xFF ? this->_r.e - 1 : this->_r.e;
    //Set UF, Z, etc.
}

void Z80::INCE(){
    this->_r.e += 1;
    //Set OF, Z, etc.
}

void Z80::DECE(){
    this->_r.e -= 1;
    //Set UF, Z, etc.
}

void Z80::LDEn(){
    this->_r.e = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::RRA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRNZn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDHLnn(){
    this->_r.l = this->mmu.rb(this->_r.pc);
    this->_r.h = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
}

void Z80::LDImHLA(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);
    this->INCHL();
}

void Z80::INCHL(){
    this->_r.h += 1;
    this->_r.l = this->_r.h == 0x00 ? this->_r.l + 1 : this->_r.l;
    //Set OF, Z, etc.
}

void Z80::INCH(){
    this->_r.h += 1;
    //Set OF, Z, etc.
}

void Z80::DECH(){
    this->_r.h -= 1;
    //Set UF, Z, etc.
}

void Z80::LDHn(){
    this->_r.h = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::DAA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRZn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADDHLHL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDIAmHL(){
    this->_r.a = this->mmu.rb(this->_r.h << 8 + this->_r.l);
    this->INCHL();
}

void Z80::DECHL(){
    this->_r.h -= 1;
    this->_r.l = this->_r.h == 0xFF ? this->_r.l - 1 : this->_r.l;
    //Set UF, Z, etc.
}

void Z80::INCL(){
    this->_r.l += 1;
    //Set OF, Z, etc.
}

void Z80::DECL(){
    this->_r.l -= 1;
    //Set UF, Z, etc.
}

void Z80::LDLn(){
    this->_r.l = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::NOT(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRNCn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDSPnn(){
    this->_r.sp = this->mmu.rw(this->_r.pc);
    this->_r.pc += 2;
}

void Z80::LDDmHLA(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);
    this->DECHL();
}

void Z80::INCSP(){
    this->_r.sp += 1;
    //Set OF, Z, etc.
}

void Z80::INCmHL(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.h << 8 + this->_r.l) + 1);
    //Set OF, Z, etc. if needed?
}

void Z80::DECmHL(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.h << 8 + this->_r.l) - 1);
    //Set UF, Z, etc. if needed?
}

void Z80::LDmHLn(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.pc));
    this->_r.pc += 1;
}

void Z80::SCF(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRCn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADDHLSP(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDDAmHL(){
    this->_r.a = this->mmu.rb(this->_r.h << 8 + this->_r.l);
    this->DECHL();
}

void Z80::DECSP(){
    this->_r.sp -= 1;
    //Set UF, Z, etc.
}

void Z80::INCA(){
    this->_r.a += 1;
    //Set OF, Z, etc.
}

void Z80::DECA(){
    this->_r.a -= 1;
    //Set UF, Z, etc.
}

void Z80::LDAn(){
    this->_r.a = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::CCF(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDBB(){
    this->_r.b = this->_r.b;
}

void Z80::LDBC(){
    this->_r.b = this->_r.c;
}

void Z80::LDBD(){
    this->_r.b = this->_r.d;
}

void Z80::LDBE(){
    this->_r.b = this->_r.e;
}

void Z80::LDBH(){
    this->_r.b = this->_r.h;
}

void Z80::LDBL(){
    this->_r.b = this->_r.l;
}

void Z80::LDBmHL(){
    this->_r.b = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDBA(){
    this->_r.b = this->_r.a;
}

void Z80::LDCB(){
    this->_r.c = this->_r.b;
}

void Z80::LDCC(){
    this->_r.c = this->_r.c;
}

void Z80::LDCD(){
    this->_r.c = this->_r.d;
}

void Z80::LDCE(){
    this->_r.c = this->_r.e;
}

void Z80::LDCH(){
    this->_r.c = this->_r.h;
}

void Z80::LDCL(){
    this->_r.c = this->_r.l;
}

void Z80::LDCmHL(){
    this->_r.c = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDCA(){
    this->_r.c = this->_r.a;
}

void Z80::LDDB(){
    this->_r.d = this->_r.b;
}

void Z80::LDDC(){
    this->_r.d = this->_r.c;
}

void Z80::LDDD(){
    this->_r.d = this->_r.d;
}

void Z80::LDDE(){
    this->_r.d = this->_r.e;
}

void Z80::LDDH(){
    this->_r.d = this->_r.h;
}

void Z80::LDDL(){
    this->_r.d = this->_r.l;
}

void Z80::LDDmHL(){
    this->_r.d = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDDA(){
    this->_r.d = this->_r.a;
}

void Z80::LDEB(){
    this->_r.e = this->_r.b;
}

void Z80::LDEC(){
    this->_r.e = this->_r.c;
}

void Z80::LDED(){
    this->_r.e = this->_r.d;
}

void Z80::LDEE(){
    this->_r.e = this->_r.e;
}

void Z80::LDEH(){
    this->_r.e = this->_r.h;
}

void Z80::LDEL(){
    this->_r.e = this->_r.l;
}

void Z80::LDEmHL(){
    this->_r.e = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDEA(){
    this->_r.e = this->_r.a;
}

void Z80::LDHB(){
    this->_r.h = this->_r.b;
}

void Z80::LDHC(){
    this->_r.h = this->_r.c;
}

void Z80::LDHD(){
    this->_r.h = this->_r.d;
}

void Z80::LDHE(){
    this->_r.h = this->_r.e;
}

void Z80::LDHH(){
    this->_r.h = this->_r.h;
}

void Z80::LDHL(){
    this->_r.h = this->_r.l;
}

void Z80::LDHmHL(){
    this->_r.h = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDHA(){
    this->_r.h = this->_r.a;
}

void Z80::LDLB(){
    this->_r.l = this->_r.b;
}

void Z80::LDLC(){
    this->_r.l = this->_r.c;
}

void Z80::LDLD(){
    this->_r.l = this->_r.d;
}

void Z80::LDLE(){
    this->_r.l = this->_r.e;
}

void Z80::LDLH(){
    this->_r.l = this->_r.h;
}

void Z80::LDLL(){
    this->_r.l = this->_r.l;
}

void Z80::LDLmHL(){
    this->_r.l = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDLA(){
    this->_r.l = this->_r.a;
}

void Z80::LDmHLB(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.b);
}

void Z80::LDmHLC(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.c);
}

void Z80::LDmHLD(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.d);
}

void Z80::LDmHLE(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.e);
}

void Z80::LDmHLH(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.h);
}

void Z80::LDmHLL(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.l);
}

void Z80::HALT(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDmHLA(){
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);
}

void Z80::LDAB(){
    this->_r.a = this->_r.b;
}

void Z80::LDAC(){
    this->_r.a = this->_r.c;
}

void Z80::LDAD(){
    this->_r.a = this->_r.d;
}

void Z80::LDAE(){
    this->_r.a = this->_r.e;
}

void Z80::LDAH(){
    this->_r.a = this->_r.h;
}

void Z80::LDAL(){
    this->_r.a = this->_r.l;
}

void Z80::LDAmHL(){
    this->_r.a = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDAA(){
    this->_r.a = this->_r.a;
}

void Z80::ADDAB(){
    this->_r.f = ((this->_r.a + this->_r.b) >> 8) & 0x1;
    this->_r.a += this->_r.b;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAC(){
    this->_r.f = ((this->_r.a + this->_r.c) >> 8) & 0x1;
    this->_r.a += this->_r.c;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAD(){
    this->_r.f = ((this->_r.a + this->_r.d) >> 8) & 0x1;
    this->_r.a += this->_r.d;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAE(){
    this->_r.f = ((this->_r.a + this->_r.e) >> 8) & 0x1;
    this->_r.a += this->_r.e;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAH(){
    this->_r.f = ((this->_r.a + this->_r.h) >> 8) & 0x1;
    this->_r.a += this->_r.h;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAL(){
    this->_r.f = ((this->_r.a + this->_r.l) >> 8) & 0x1;
    this->_r.a += this->_r.l;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAmHL(){
    this->_r.f = ((this->_r.a + this->mmu.rb(this->_r.h << 8 + this->_r.l)) >> 8) & 0x1;
    this->_r.a += this->mmu.rb(this->_r.h << 8 + this->_r.l);
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAA(){
    this->_r.f = ((this->_r.a + this->_r.a) >> 8) & 0x1;
    this->_r.a += this->_r.a;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADCAB(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADCAC(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADCAD(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADCAE(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADCAH(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADCAL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADCAmHL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADCAA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAB(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAC(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAD(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAE(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAH(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAmHL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAB(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAC(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAD(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAE(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAH(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAmHL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ANDB(){
    this->_r.a &= this->_r.b;
    //Set 0, carry, etc.
}

void Z80::ANDC(){
    this->_r.a &= this->_r.c;
    //Set 0, carry, etc.
}

void Z80::ANDD(){
    this->_r.a &= this->_r.d;
    //Set 0, carry, etc.
}

void Z80::ANDE(){
    this->_r.a &= this->_r.e;
    //Set 0, carry, etc.
}

void Z80::ANDH(){
    this->_r.a &= this->_r.h;
    //Set 0, carry, etc.
}

void Z80::ANDL(){
    this->_r.a &= this->_r.l;
    //Set 0, carry, etc.
}

void Z80::ANDmHL(){
    this->_r.a &= this->mmu.rb(this->_r.h << 8 + this->_r.l);
    //Set 0, carry, etc.
}

void Z80::ANDA(){
    this->_r.a &= this->_r.a;
    //Set 0, carry, etc.
}

void Z80::XORB(){
    this->_r.a ^= this->_r.b;
    //Set 0, carry, etc.
}

void Z80::XORC(){
    this->_r.a ^= this->_r.c;
    //Set 0, carry, etc.
}

void Z80::XORD(){
    this->_r.a ^= this->_r.d;
    //Set 0, carry, etc.
}

void Z80::XORE(){
    this->_r.a ^= this->_r.e;
    //Set 0, carry, etc.
}

void Z80::XORH(){
    this->_r.a ^= this->_r.h;
    //Set 0, carry, etc.
}

void Z80::XORL(){
    this->_r.a ^= this->_r.l;
    //Set 0, carry, etc.
}

void Z80::XORmHL(){
    this->_r.a ^= this->mmu.rb(this->_r.h << 8 + this->_r.l);
    //Set 0, carry, etc.
}

void Z80::XORA(){
    this->_r.a ^= this->_r.a;
    //Set 0, carry, etc.
}

void Z80::ORB(){
    this->_r.a |= this->_r.b;
    //Set 0, carry, etc.
}

void Z80::ORC(){
    this->_r.a |= this->_r.c;
    //Set 0, carry, etc.
}

void Z80::ORD(){
    this->_r.a |= this->_r.d;
    //Set 0, carry, etc.
}

void Z80::ORE(){
    this->_r.a |= this->_r.e;
    //Set 0, carry, etc.
}

void Z80::ORH(){
    this->_r.a |= this->_r.h;
    //Set 0, carry, etc.
}

void Z80::ORL(){
    this->_r.a |= this->_r.l;
    //Set 0, carry, etc.
}

void Z80::ORmHL(){
    this->_r.a |= this->mmu.rb(this->_r.h << 8 + this->_r.l);
    //Set 0, carry, etc.
}

void Z80::ORA(){
    this->_r.a |= this->_r.a;
    //Set 0, carry, etc.
}

void Z80::CPB(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPC(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPD(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPE(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPH(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPmHL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETNZ(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::POPBC(){
    this->_r.c = this->mmu.rb(this->_r.sp);
    this->_r.b = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::JPNZnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JPnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLNZnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::PUSHBC(){
    this->mmu.ww(this->_r.sp, (this->_r.b << 8) + this->_r.c);
    this->_r.sp -= 2;
}

void Z80::ADDAn(){
    this->_r.f = (this->_r.a + this->mmu.rb(this->_r.pc) >> 8) & 0x1;
    this->_r.a += this->mmu.rb(this->_r.pc);
    this->_r.a &= 0xFF;
    this->_r.pc += 1;
    //Set 0, OF (above), etc.
}

void Z80::RST0(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETZ(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RET(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JPZnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::Extops(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLZnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADCAn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RST8(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETNC(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::POPDE(){
    this->_r.e = this->mmu.rb(this->_r.sp);
    this->_r.d = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::JPNCnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX1(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLNCnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::PUSHDE(){
    this->mmu.ww(this->_r.sp, (this->_r.d << 8) + this->_r.e);
    this->_r.sp -= 2;
}

void Z80::SUBAn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RST10(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETC(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETI(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JPCnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX2(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLCnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX3(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RST18(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDHmnA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::POPHL(){
    this->_r.l = this->mmu.rb(this->_r.sp);
    this->_r.h = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::LDHmCA(){
    this->_r.h = this->mmu.rb(this->_r.c << 8 + this->_r.a);
}

void Z80::XX4(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX5(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::PUSHHL(){
    this->mmu.ww(this->_r.sp, (this->_r.h << 8) + this->_r.l);
    this->_r.sp -= 2;
}

void Z80::ANDn(){
    this->_r.a &= this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    //Set 0, carry, etc.
}

void Z80::RST20(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADDSPd(){
    this->_r.sp += this->mmu.rb(this->_r.pc) > 0x7F ? (~this->mmu.rb(this->_r.pc) + 1) & 0xFF : this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::JPmHL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDmnnA(){
    this->mmu.wb(this->mmu.rb(this->_r.pc) + (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.a);
    this->_r.pc += 2;
}

void Z80::XX6(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX7(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX8(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XORn(){
    this->_r.a ^= this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    //Set 0, carry, etc.
}

void Z80::RST28(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDHAmn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::POPAF(){
    this->_r.f = this->mmu.rb(this->_r.sp);
    this->_r.a = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::XX9(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::DI(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XXA(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::PUSHAF(){
    this->mmu.ww(this->_r.sp, (this->_r.a << 8) + this->_r.f);
    this->_r.sp -= 2;
}

void Z80::ORn(){
    this->_r.a |= this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    //Set 0, carry, etc.
}

void Z80::RST30(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDHLSPd(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDSPHL(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDAmnn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EI(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XXB(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XXC(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPn(){
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RST38(){
    std::cout << "Uncovered Function" << std::endl;
}

#endif       
