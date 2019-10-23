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
		void LDImHL();
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
			{&Z80::LDImHL, "LDImHL"},
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
	std::cout << "NOP" << std::endl;
}
void Z80::LDBCnn(){
	std::cout << "LDBC" << std::endl;
	this->_r.c = this->mmu.rb(this->_r.pc);
	this->_r.b = this->mmu.rb(this->_r.pc + 1);
	this->_r.pc += 2;
}
void Z80::LDmBCA(){
	std::cout << "LDmBCA" << std::endl;
	this->_r.a = this->mmu.rb(this->_r.b << 8 + this->_r.c);
}
void Z80::INCBC(){
	std::cout << "INCBC" << std::endl;
	this->_r.c += 1;
	this->_r.b = this->_r.c == 0 ? this->_r.b + 1 : this->_r.b;
}
void Z80::INCB(){
	std::cout << "INCB" << std::endl;
	this->_r.b += 1;
}
void Z80::DECB(){
	std::cout << "DECB" << std::endl;
	this->_r.b -= 1;
}
void Z80::LDBn(){
	std::cout << "LDBn" << std::endl;
	this->_r.b = this->mmu.rb(this->_r.pc);
	this->_r.pc++;
}
void Z80::RLCA(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmnnSP(){
	std::cout << "LDmnnSP" << std::endl;
	this->mmu.ww(this->mmu.rb(this->_r.pc) + (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.sp);
	this->_r.pc += 2;
}
void Z80::ADDHLBC(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAmBC(){
	std::cout << "LDAmBC" << std::endl;
	this->_r.a = this->mmu.rb(this->_r.b << 8 + this->_r.c);
}
void Z80::DECBC(){
	std::cout << "DECBC" << std::endl;
	this->_r.c -= 1;
	this->_r.b = this->_r.c == 0xFF ? this->_r.b - 1 : this->_r.b;
}
void Z80::INCC(){
	std::cout << "INCC" << std::endl;
	this->_r.c += 1;
}
void Z80::DECC(){
	std::cout << "DECC" << std::endl;
	this->_r.c -= 1;
}
void Z80::LDCn(){
	std::cout << "LDCn" << std::endl;
	this->_r.c = this->mmu.rb(this->_r.pc);
	this->_r.pc++;
}
void Z80::RRCA(){
	std::cout << "Test" << std::endl;
}
void Z80::STOP(){
	std::cout << "Test" << std::endl;
}
void Z80::LDDEnn(){
	std::cout << "LDDEnn" << std::endl;
	this->_r.e = this->mmu.rb(this->_r.pc);
	this->_r.d = this->mmu.rb(this->_r.pc + 1);
	this->_r.pc += 2;
}
void Z80::LDmDEA(){
	std::cout << "LDmDEA" << std::endl;
	this->mmu.wb(this->_r.d << 8 + this->_r.e, this->_r.a);
}
void Z80::INCDE(){
	std::cout << "INCDE" << std::endl;
	this->_r.e += 1;
	this->_r.d = this->_r.e == 0 ? this->_r.d + 1 : this->_r.d;
}
void Z80::INCD(){
	std::cout << "INCD" << std::endl;
	this->_r.d += 1;
}
void Z80::DECD(){
	std::cout << "DECD" << std::endl;
	this->_r.d -= 1;
}
void Z80::LDDn(){
	std::cout << "LDDn" << std::endl;
	this->_r.d = this->mmu.rb(this->_r.pc);
	this->_r.pc++;
}
void Z80::RLA(){
	std::cout << "Test" << std::endl;
}
void Z80::JRn(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDHLDE(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAmDE(){
	std::cout << "LDAmDE" << std::endl;
	this->_r.a = this->mmu.rb(this->_r.d << 8 + this->_r.e);
}
void Z80::DECDE(){
	std::cout << "DECDE" << std::endl;
	this->_r.e -= 1;
	this->_r.d = this->_r.e == 0xFF ? this->_r.d - 1 : this->_r.d;
}
void Z80::INCE(){
	std::cout << "INCE" << std::endl;
	this->_r.e += 1;
}
void Z80::DECE(){
	std::cout << "DECE" << std::endl;
	this->_r.e -= 1;
}
void Z80::LDEn(){
	std::cout << "LDEn" << std::endl;
	this->_r.e = this->mmu.rb(this->_r.pc);
	this->_r.pc++;
}
void Z80::RRA(){
	std::cout << "Test" << std::endl;
}
void Z80::JRNZn(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHLnn(){
	std::cout << "LD HLnn" << std::endl;
	this->_r.l = this->mmu.rb(this->_r.pc);
	this->_r.h = this->mmu.rb(this->_r.pc + 1);
	this->_r.pc += 2; //reading word

}
void Z80::LDImHLA(){
	std::cout << "Test" << std::endl;
}
void Z80::INCHL(){
	std::cout << "INCHL" << std::endl;
	this->_r.l += 1;
	this->_r.h = this->_r.l == 0x00 ? this->_r.h + 1 : this->_r.h;
}
void Z80::INCH(){
	std::cout << "INCH" << std::endl;
	this->_r.h += 1;
}
void Z80::DECH(){
	std::cout << "DECH" << std::endl;
	this->_r.h -= 1;
}
void Z80::LDHn(){
	std::cout << "LDHn" << std::endl;
	this->_r.h = this->mmu.rb(this->_r.pc);
	this->_r.pc++;
}
void Z80::DAA(){
	std::cout << "Test" << std::endl;
}
void Z80::JRZn(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDHLHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDImHL(){
	std::cout << "Test" << std::endl;
}
void Z80::DECHL(){
	std::cout << "DECHL" << std::endl;
	this->_r.l -= 1;
	this->_r.h = this->_r.l == 0xFF ? this->_r.h - 1 : this->_r.h;
}
void Z80::INCL(){
	std::cout << "INCL" << std::endl;
	this->_r.l += 1;
}
void Z80::DECL(){
	std::cout << "DECL" << std::endl;
	this->_r.l -= 1;
}
void Z80::LDLn(){
	std::cout << "LDLn" << std::endl;
	this->_r.l = this->mmu.rb(this->_r.pc);
	this->_r.pc++;
}
void Z80::NOT(){
	std::cout << "Test" << std::endl;
}
void Z80::JRNCn(){
	std::cout << "Test" << std::endl;
}
void Z80::LDSPnn(){
	std::cout << "Test" << std::endl;
	this->_r.sp = mmu.rw(this->_r.pc); //already incremented pc
	this->_r.pc += 2;
	//this->_r.m = 3; //Timing
	//this->_r.t = 12;
}
void Z80::LDDmHLA(){
	std::cout << "LDDmHLA" << std::endl;
	this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);
	this->_r.l -= 1;
	this->_r.h = this->_r.l == 0xFF ? this->_r.h - 1 : this->_r.h;
}
void Z80::INCSP(){
	std::cout << "INCSP" << std::endl;
	this->_r.sp += 1;
}
void Z80::INCmHL(){
	std::cout << "INCmHL" << std::endl;
	this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.h << 8 + this->_r.l) + 1);
}
void Z80::DECmHL(){
	std::cout << "DECmHL" << std::endl;
	this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.h << 8 + this->_r.l) + 1);
}
void Z80::LDmHLn(){
	std::cout << "LDmHLn" << std::endl;
	this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.pc));
	this->_r.pc++;
}
void Z80::SCF(){
	std::cout << "Test" << std::endl;
}
void Z80::JRCn(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDHLSP(){
	std::cout << "Test" << std::endl;
}
void Z80::LDDAmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::DECSP(){
	std::cout << "DECSP" << std::endl;
	this->_r.sp -= 1;
}
void Z80::INCA(){
	std::cout << "INCA" << std::endl;
	this->_r.a += 1;
}
void Z80::DECA(){
	std::cout << "DECA" << std::endl;
	this->_r.a -= 1;
}
void Z80::LDAn(){
	std::cout << "LDAn" << std::endl;
	this->_r.a = this->mmu.rb(this->_r.pc);
	this->_r.pc++;
}
void Z80::CCF(){
	std::cout << "Test" << std::endl;
}
void Z80::LDBB(){
	std::cout << "LDBB" << std::endl;
	this->_r.b = this->_r.b;
}
void Z80::LDBC(){
	std::cout << "LDBC" << std::endl;
	this->_r.b = this->_r.c;
}
void Z80::LDBD(){
	std::cout << "LDBD" << std::endl;
	this->_r.b = this->_r.d;
}
void Z80::LDBE(){
	std::cout << "LDBE" << std::endl;
	this->_r.b = this->_r.e;
}
void Z80::LDBH(){
	std::cout << "LDBH" << std::endl;
	this->_r.b = this->_r.h;
}
void Z80::LDBL(){
	std::cout << "LDBL" << std::endl;
	this->_r.b = this->_r.l;
}
void Z80::LDBmHL(){
	std::cout << "LDBmHL" << std::endl;
	this->_r.b = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}
void Z80::LDBA(){
	std::cout << "LDBA" << std::endl;
	this->_r.b = this->_r.a;
}
void Z80::LDCB(){
	std::cout << "LDCB" << std::endl;
	this->_r.c = this->_r.b;
}
void Z80::LDCC(){
	std::cout << "LDCC" << std::endl;
	this->_r.c = this->_r.c;
}
void Z80::LDCD(){
	std::cout << "LDCD" << std::endl;
	this->_r.c = this->_r.d;
}
void Z80::LDCE(){
	std::cout << "LDCE" << std::endl;
	this->_r.c = this->_r.e;
}
void Z80::LDCH(){
	std::cout << "LDCH" << std::endl;
	this->_r.c = this->_r.h;
}
void Z80::LDCL(){
	std::cout << "LDCL" << std::endl;
	this->_r.c = this->_r.l;
}
void Z80::LDCmHL(){
	std::cout << "LDCmHL" << std::endl;
	this->_r.c = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}
void Z80::LDCA(){
	std::cout << "LDCA" << std::endl;
	this->_r.c = this->_r.a;
}
void Z80::LDDB(){
	std::cout << "LDDB" << std::endl;
	this->_r.d = this->_r.b;
}
void Z80::LDDC(){
	std::cout << "LDDC" << std::endl;
	this->_r.d = this->_r.c;
}
void Z80::LDDD(){
	std::cout << "LDDD" << std::endl;
	this->_r.d = this->_r.d;
}
void Z80::LDDE(){
	std::cout << "LDDE" << std::endl;
	this->_r.d = this->_r.e;
}
void Z80::LDDH(){
	std::cout << "LDDH" << std::endl;
	this->_r.d = this->_r.h;
}
void Z80::LDDL(){
	std::cout << "LDDL" << std::endl;
	this->_r.d = this->_r.l;
}
void Z80::LDDmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDDA(){
	std::cout << "Test" << std::endl;
}
void Z80::LDEB(){
	std::cout << "Test" << std::endl;
}
void Z80::LDEC(){
	std::cout << "Test" << std::endl;
}
void Z80::LDED(){
	std::cout << "Test" << std::endl;
}
void Z80::LDEE(){
	std::cout << "Test" << std::endl;
}
void Z80::LDEH(){
	std::cout << "Test" << std::endl;
}
void Z80::LDEL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDEmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDEA(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHB(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHC(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHD(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHE(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHH(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHA(){
	std::cout << "Test" << std::endl;
}
void Z80::LDLB(){
	std::cout << "Test" << std::endl;
}
void Z80::LDLC(){
	std::cout << "Test" << std::endl;
}
void Z80::LDLD(){
	std::cout << "Test" << std::endl;
}
void Z80::LDLE(){
	std::cout << "Test" << std::endl;
}
void Z80::LDLH(){
	std::cout << "Test" << std::endl;
}
void Z80::LDLL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDLmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDLA(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmHLB(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmHLC(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmHLD(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmHLE(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmHLH(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmHLL(){
	std::cout << "Test" << std::endl;
}
void Z80::HALT(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmHLA(){
	std::cout << "LDmHLA" << std::endl;
	this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);
}
void Z80::LDAB(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAC(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAD(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAE(){
	std::cout << "LDAE" << std::endl;
	this->_r.a = this->_r.e;
}
void Z80::LDAH(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAA(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAB(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAC(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAD(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAE(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAH(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAL(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAA(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAB(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAC(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAD(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAE(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAH(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAL(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAA(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAB(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAC(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAD(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAE(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAH(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAL(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAA(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAB(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAC(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAD(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAE(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAH(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAL(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAA(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDB(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDC(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDD(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDE(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDH(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDL(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDA(){
	std::cout << "Test" << std::endl;
}
void Z80::XORB(){
	std::cout << "Test" << std::endl;
}
void Z80::XORC(){
	std::cout << "Test" << std::endl;
}
void Z80::XORD(){
	std::cout << "Test" << std::endl;
}
void Z80::XORE(){
	std::cout << "Test" << std::endl;
}
void Z80::XORH(){
	std::cout << "Test" << std::endl;
}
void Z80::XORL(){
	std::cout << "Test" << std::endl;
}
void Z80::XORmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::XORA(){
	std::cout << "XORA" << std::endl;
	this->_r.a ^= this->_r.a;
	//set flags
	//timing
}
void Z80::ORB(){
	std::cout << "Test" << std::endl;
}
void Z80::ORC(){
	std::cout << "Test" << std::endl;
}
void Z80::ORD(){
	std::cout << "Test" << std::endl;
}
void Z80::ORE(){
	std::cout << "Test" << std::endl;
}
void Z80::ORH(){
	std::cout << "Test" << std::endl;
}
void Z80::ORL(){
	std::cout << "Test" << std::endl;
}
void Z80::ORmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::ORA(){
	std::cout << "Test" << std::endl;
}
void Z80::CPB(){
	std::cout << "Test" << std::endl;
}
void Z80::CPC(){
	std::cout << "Test" << std::endl;
}
void Z80::CPD(){
	std::cout << "Test" << std::endl;
}
void Z80::CPE(){
	std::cout << "Test" << std::endl;
}
void Z80::CPH(){
	std::cout << "Test" << std::endl;
}
void Z80::CPL(){
	std::cout << "Test" << std::endl;
}
void Z80::CPmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::CPA(){
	std::cout << "Test" << std::endl;
}
void Z80::RETNZ(){
	std::cout << "Test" << std::endl;
}
void Z80::POPBC(){
	std::cout << "Test" << std::endl;
}
void Z80::JPNZnn(){
	std::cout << "Test" << std::endl;
}
void Z80::JPnn(){
	std::cout << "Test" << std::endl;
}
void Z80::CALLNZnn(){
	std::cout << "Test" << std::endl;
}
void Z80::PUSHBC(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDAn(){
	std::cout << "Test" << std::endl;
}
void Z80::RST0(){
	std::cout << "Test" << std::endl;
}
void Z80::RETZ(){
	std::cout << "Test" << std::endl;
}
void Z80::RET(){
	std::cout << "Test" << std::endl;
}
void Z80::JPZnn(){
	std::cout << "Test" << std::endl;
}
void Z80::Extops(){
	std::cout << "Test" << std::endl;
}
void Z80::CALLZnn(){
	std::cout << "Test" << std::endl;
}
void Z80::CALLnn(){
	std::cout << "Test" << std::endl;
}
void Z80::ADCAn(){
	std::cout << "Test" << std::endl;
}
void Z80::RST8(){
	std::cout << "Test" << std::endl;
}
void Z80::RETNC(){
	std::cout << "Test" << std::endl;
}
void Z80::POPDE(){
	std::cout << "Test" << std::endl;
}
void Z80::JPNCnn(){
	std::cout << "Test" << std::endl;
}
void Z80::XX1(){
	std::cout << "Test" << std::endl;
}
void Z80::CALLNCnn(){
	std::cout << "Test" << std::endl;
}
void Z80::PUSHDE(){
	std::cout << "Test" << std::endl;
}
void Z80::SUBAn(){
	std::cout << "Test" << std::endl;
}
void Z80::RST10(){
	std::cout << "Test" << std::endl;
}
void Z80::RETC(){
	std::cout << "Test" << std::endl;
}
void Z80::RETI(){
	std::cout << "Test" << std::endl;
}
void Z80::JPCnn(){
	std::cout << "Test" << std::endl;
}
void Z80::XX2(){
	std::cout << "Test" << std::endl;
}
void Z80::CALLCnn(){
	std::cout << "Test" << std::endl;
}
void Z80::XX3(){
	std::cout << "Test" << std::endl;
}
void Z80::SBCAn(){
	std::cout << "Test" << std::endl;
}
void Z80::RST18(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHmnA(){
	std::cout << "LDHmnA" << std::endl;
	this->mmu.wb(this->mmu.rb(this->_r.pc) + 0xFF00, this->_r.a);
	this->_r.pc++;
}
void Z80::POPHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHmCA(){
	std::cout << "LDHmCA" << std::endl;
	this->mmu.wb(this->_r.c + 0xFF00, this->_r.a);
}
void Z80::XX4(){
	std::cout << "Test" << std::endl;
}
void Z80::XX5(){
	std::cout << "Test" << std::endl;
}
void Z80::PUSHHL(){
	std::cout << "Test" << std::endl;
}
void Z80::ANDn(){
	std::cout << "Test" << std::endl;
}
void Z80::RST20(){
	std::cout << "Test" << std::endl;
}
void Z80::ADDSPd(){
	std::cout << "Test" << std::endl;
}
void Z80::JPmHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDmnnA(){
	std::cout << "Test" << std::endl;
}
void Z80::XX6(){
	std::cout << "Test" << std::endl;
}
void Z80::XX7(){
	std::cout << "Test" << std::endl;
}
void Z80::XX8(){
	std::cout << "Test" << std::endl;
}
void Z80::XORn(){
	std::cout << "Test" << std::endl;
}
void Z80::RST28(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHAmn(){
	std::cout << "Test" << std::endl;
}
void Z80::POPAF(){
	std::cout << "Test" << std::endl;
}
void Z80::XX9(){
	std::cout << "Test" << std::endl;
}
void Z80::DI(){
	std::cout << "Test" << std::endl;
}
void Z80::XXA(){
	std::cout << "Test" << std::endl;
}
void Z80::PUSHAF(){
	std::cout << "Test" << std::endl;
}
void Z80::ORn(){
	std::cout << "Test" << std::endl;
}
void Z80::RST30(){
	std::cout << "Test" << std::endl;
}
void Z80::LDHLSPd(){
	std::cout << "Test" << std::endl;
}
void Z80::LDSPHL(){
	std::cout << "Test" << std::endl;
}
void Z80::LDAmnn(){
	std::cout << "Test" << std::endl;
}
void Z80::EI(){
	std::cout << "Test" << std::endl;
}
void Z80::XXB(){
	std::cout << "Test" << std::endl;
}
void Z80::XXC(){
	std::cout << "Test" << std::endl;
}
void Z80::CPn(){
	std::cout << "Test" << std::endl;
}
void Z80::RST38(){
	std::cout << "Test" << std::endl;
}
#endif       
