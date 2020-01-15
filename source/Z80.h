#ifndef _CPU_
#define _CPU_

#include "MMU.h"
//#include "GPU.h"

class Z80{
	public:

		Z80(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e,  uint8_t h,
			uint8_t l, uint8_t f, uint8_t m, uint16_t t, uint16_t pc, uint16_t sp,
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

        //Extension ops
        void ERLCB(); //0x00
        void ERLCC();
        void ERLCD();
        void ERLCE();
        void ERLCH();
        void ERLCL();
        void ERLCmHL();
        void ERLCA();
        void ERRCB();
        void ERRCC();
        void ERRCD();
        void ERRCE();
        void ERRCH();
        void ERRCL();
        void ERRCmHL();
        void ERRCA();
        void ERLB(); //0x10
        void ERLC();
        void ERLD();
        void ERLE();
        void ERLH();
        void ERLL();
        void ERLmHL();
        void ERLA();
        void ERRB();
        void ERRC();
        void ERRD();
        void ERRE();
        void ERRH();
        void ERRL();
        void ERRmHL();
        void ERRA();
        void ESLAB(); //0x20
        void ESLAC();
        void ESLAD();
        void ESLAE();
        void ESLAH();
        void ESLAL();
        void ESLAmHL();
        void ESLAA();
        void ESRAB();
        void ESRAC();
        void ESRAD();
        void ESRAE();
        void ESRAH();
        void ESRAL();
        void ESRAmHL();
        void ESRAA();
        void ESWAPB(); //0x30
        void ESWAPC();
        void ESWAPD();
        void ESWAPE();
        void ESWAPH();
        void ESWAPL();
        void ESWAPmHL();
        void ESWAPA();
        void ESRLB();
        void ESRLC();
        void ESRLD();
        void ESRLE();
        void ESRLH();
        void ESRLL();
        void ESRLmHL();
        void ESRLA();
        void EBIT0B(); //0x40
        void EBIT0C();
        void EBIT0D();
        void EBIT0E();
        void EBIT0H();
        void EBIT0L();
        void EBIT0mHL();
        void EBIT0A();
        void EBIT1B(); //0x48
        void EBIT1C();
        void EBIT1D();
        void EBIT1E();
        void EBIT1H();
        void EBIT1L();
        void EBIT1mHL();
        void EBIT1A();
        void EBIT2B(); //0x50
        void EBIT2C();
        void EBIT2D();
        void EBIT2E();
        void EBIT2H();
        void EBIT2L();
        void EBIT2mHL();
        void EBIT2A();
        void EBIT3B(); //0x58
        void EBIT3C();
        void EBIT3D();
        void EBIT3E();
        void EBIT3H();
        void EBIT3L();
        void EBIT3mHL();
        void EBIT3A();
        void EBIT4B(); //0x60
        void EBIT4C();
        void EBIT4D();
        void EBIT4E();
        void EBIT4H();
        void EBIT4L();
        void EBIT4mHL();
        void EBIT4A();
        void EBIT5B(); //0x68
        void EBIT5C();
        void EBIT5D();
        void EBIT5E();
        void EBIT5H();
        void EBIT5L();
        void EBIT5mHL();
        void EBIT5A();
        void EBIT6B(); //0x70
        void EBIT6C();
        void EBIT6D();
        void EBIT6E();
        void EBIT6H();
        void EBIT6L();
        void EBIT6mHL();
        void EBIT6A();
        void EBIT7B(); //0x78
        void EBIT7C();
        void EBIT7D();
        void EBIT7E();
        void EBIT7H();
        void EBIT7L();
        void EBIT7mHL();
        void EBIT7A(); //
        void ERES0B(); //0x80
        void ERES0C();
        void ERES0D();
        void ERES0E();
        void ERES0H();
        void ERES0L();
        void ERES0mHL();
        void ERES0A();
        void ERES1B(); //0x88
        void ERES1C();
        void ERES1D();
        void ERES1E();
        void ERES1H();
        void ERES1L();
        void ERES1mHL();
        void ERES1A();
        void ERES2B(); //0x90
        void ERES2C();
        void ERES2D();
        void ERES2E();
        void ERES2H();
        void ERES2L();
        void ERES2mHL();
        void ERES2A();
        void ERES3B(); //0x98
        void ERES3C();
        void ERES3D();
        void ERES3E();
        void ERES3H();
        void ERES3L();
        void ERES3mHL();
        void ERES3A();
        void ERES4B(); //0xA0
        void ERES4C();
        void ERES4D();
        void ERES4E();
        void ERES4H();
        void ERES4L();
        void ERES4mHL();
        void ERES4A();
        void ERES5B(); //0xA8
        void ERES5C();
        void ERES5D();
        void ERES5E();
        void ERES5H();
        void ERES5L();
        void ERES5mHL();
        void ERES5A();
        void ERES6B(); //0xB0
        void ERES6C();
        void ERES6D();
        void ERES6E();
        void ERES6H();
        void ERES6L();
        void ERES6mHL();
        void ERES6A();
        void ERES7B(); //0xB8
        void ERES7C();
        void ERES7D();
        void ERES7E();
        void ERES7H();
        void ERES7L();
        void ERES7mHL();
        void ERES7A();
        void ESET0B(); //0xC0
        void ESET0C();
        void ESET0D();
        void ESET0E();
        void ESET0H();
        void ESET0L();
        void ESET0mHL();
        void ESET0A();
        void ESET1B(); //0xC8
        void ESET1C();
        void ESET1D();
        void ESET1E();
        void ESET1H();
        void ESET1L();
        void ESET1mHL();
        void ESET1A();
        void ESET2B(); //0xD0
        void ESET2C();
        void ESET2D();
        void ESET2E();
        void ESET2H();
        void ESET2L();
        void ESET2mHL();
        void ESET2A();
        void ESET3B(); //0xD8
        void ESET3C();
        void ESET3D();
        void ESET3E();
        void ESET3H();
        void ESET3L();
        void ESET3mHL();
        void ESET3A();
        void ESET4B(); //0xE0
        void ESET4C();
        void ESET4D();
        void ESET4E();
        void ESET4H();
        void ESET4L();
        void ESET4mHL();
        void ESET4A();
        void ESET5B(); //0xE8
        void ESET5C();
        void ESET5D();
        void ESET5E();
        void ESET5H();
        void ESET5L();
        void ESET5mHL();
        void ESET5A();
        void ESET6B(); //0xF0
        void ESET6C();
        void ESET6D();
        void ESET6E();
        void ESET6H();
        void ESET6L();
        void ESET6mHL();
        void ESET6A();
        void ESET7B(); //0xF8
        void ESET7C();
        void ESET7D();
        void ESET7E();
        void ESET7H();
        void ESET7L();
        void ESET7mHL();
        void ESET7A();


	private:
        struct{
            uint64_t m, t;
            //uint32_t m, t;
        }_clock;

        struct{
            uint8_t a, b, c, d, e, h, l, f, m;
            uint16_t pc, sp, t;

        }_r;

		struct op_pointer{ //TODO: Split ops into separate file
			void (Z80::*op_function)(void);
			std::string op; //Debugging purposes
            //Other op information here
		};

        const op_pointer ext_ops[0x100] = {
            {&Z80::ERLCB, "RLCB"},
            {&Z80::ERLCC, "RLCC"},
            {&Z80::ERLCD, "RLCD"},
            {&Z80::ERLCE, "RLCE"},
            {&Z80::ERLCH, "RLCH"},
            {&Z80::ERLCL, "RLCL"},
            {&Z80::ERLCmHL, "RLCmHL"},
            {&Z80::ERLCA, "RLCA"},
            {&Z80::ERRCB, "RRCB"},
            {&Z80::ERRCC, "RRCC"},
            {&Z80::ERRCD, "RRCD"},
            {&Z80::ERRCE, "RRCE"},
            {&Z80::ERRCH, "RRCH"},
            {&Z80::ERRCL, "RRCL"},
            {&Z80::ERRCmHL, "RRCmHL"},
            {&Z80::ERRCA, "RRCA"},
            {&Z80::ERLB, "RLB"},
            {&Z80::ERLC, "RLC"},
            {&Z80::ERLD, "RLD"},
            {&Z80::ERLE, "RLE"},
            {&Z80::ERLH, "RLH"},
            {&Z80::ERLL, "RLL"},
            {&Z80::ERLmHL, "RLmHL"},
            {&Z80::ERLA, "RLA"},
            {&Z80::ERRB, "RRB"},
            {&Z80::ERRC, "RRC"},
            {&Z80::ERRD, "RRD"},
            {&Z80::ERRE, "RRE"},
            {&Z80::ERRH, "RRH"},
            {&Z80::ERRL, "RRL"},
            {&Z80::ERRmHL, "RRmHL"},
            {&Z80::ERRA, "RRA"},
            {&Z80::ESLAB, "SLAB"},
            {&Z80::ESLAC, "SLAC"},
            {&Z80::ESLAD, "SLAD"},
            {&Z80::ESLAE, "SLAE"},
            {&Z80::ESLAH, "SLAH"},
            {&Z80::ESLAL, "SLAL"},
            {&Z80::ESLAmHL, "SLAmHL"},
            {&Z80::ESLAA, "SLAA"},
            {&Z80::ESRAB, "SRAB"},
            {&Z80::ESRAC, "SRAC"},
            {&Z80::ESRAD, "SRAD"},
            {&Z80::ESRAE, "SRAE"},
            {&Z80::ESRAH, "SRAH"},
            {&Z80::ESRAL, "SRAL"},
            {&Z80::ESRAmHL, "SRAmHL"},
            {&Z80::ESRAA, "SRAA"},
            {&Z80::ESWAPB, "SWAPB"},
            {&Z80::ESWAPC, "SWAPC"},
            {&Z80::ESWAPD, "SWAPD"},
            {&Z80::ESWAPE, "SWAPE"},
            {&Z80::ESWAPH, "SWAPH"},
            {&Z80::ESWAPL, "SWAPL"},
            {&Z80::ESWAPmHL, "SWAPmHL"},
            {&Z80::ESWAPA, "SWAPA"},
            {&Z80::ESRLB, "SRLB"},
            {&Z80::ESRLC, "SRLC"},
            {&Z80::ESRLD, "SRLD"},
            {&Z80::ESRLE, "SRLE"},
            {&Z80::ESRLH, "SRLH"},
            {&Z80::ESRLL, "SRLL"},
            {&Z80::ESRLmHL, "SRLmHL"},
            {&Z80::ESRLA, "SRLA"},
            {&Z80::EBIT0B, "BIT0B"},
            {&Z80::EBIT0C, "BIT0C"},
            {&Z80::EBIT0D, "BIT0D"},
            {&Z80::EBIT0E, "BIT0E"},
            {&Z80::EBIT0H, "BIT0H"},
            {&Z80::EBIT0L, "BIT0L"},
            {&Z80::EBIT0mHL, "BIT0mHL"},
            {&Z80::EBIT0A, "BIT0A"},
            {&Z80::EBIT1B, "BIT1B"},
            {&Z80::EBIT1C, "BIT1C"},
            {&Z80::EBIT1D, "BIT1D"},
            {&Z80::EBIT1E, "BIT1E"},
            {&Z80::EBIT1H, "BIT1H"},
            {&Z80::EBIT1L, "BIT1L"},
            {&Z80::EBIT1mHL, "BIT1mHL"},
            {&Z80::EBIT1A, "BIT1A"},
            {&Z80::EBIT2B, "BIT2B"},
            {&Z80::EBIT2C, "BIT2C"},
            {&Z80::EBIT2D, "BIT2D"},
            {&Z80::EBIT2E, "BIT2E"},
            {&Z80::EBIT2H, "BIT2H"},
            {&Z80::EBIT2L, "BIT2L"},
            {&Z80::EBIT2mHL, "BIT2mHL"},
            {&Z80::EBIT2A, "BIT2A"},
            {&Z80::EBIT3B, "BIT3B"},
            {&Z80::EBIT3C, "BIT3C"},
            {&Z80::EBIT3D, "BIT3D"},
            {&Z80::EBIT3E, "BIT3E"},
            {&Z80::EBIT3H, "BIT3H"},
            {&Z80::EBIT3L, "BIT3L"},
            {&Z80::EBIT3mHL, "BIT3mHL"},
            {&Z80::EBIT3A, "BIT3A"},
            {&Z80::EBIT4B, "BIT4B"},
            {&Z80::EBIT4C, "BIT4C"},
            {&Z80::EBIT4D, "BIT4D"},
            {&Z80::EBIT4E, "BIT4E"},
            {&Z80::EBIT4H, "BIT4H"},
            {&Z80::EBIT4L, "BIT4L"},
            {&Z80::EBIT4mHL, "BIT4mHL"},
            {&Z80::EBIT4A, "BIT4A"},
            {&Z80::EBIT5B, "BIT5B"},
            {&Z80::EBIT5C, "BIT5C"},
            {&Z80::EBIT5D, "BIT5D"},
            {&Z80::EBIT5E, "BIT5E"},
            {&Z80::EBIT5H, "BIT5H"},
            {&Z80::EBIT5L, "BIT5L"},
            {&Z80::EBIT5mHL, "BIT5mHL"},
            {&Z80::EBIT5A, "BIT5A"},
            {&Z80::EBIT6B, "BIT6B"},
            {&Z80::EBIT6C, "BIT6C"},
            {&Z80::EBIT6D, "BIT6D"},
            {&Z80::EBIT6E, "BIT6E"},
            {&Z80::EBIT6H, "BIT6H"},
            {&Z80::EBIT6L, "BIT6L"},
            {&Z80::EBIT6mHL, "BIT6mHL"},
            {&Z80::EBIT6A, "BIT6A"},
            {&Z80::EBIT7B, "BIT7B"},
            {&Z80::EBIT7C, "BIT7C"},
            {&Z80::EBIT7D, "BIT7D"},
            {&Z80::EBIT7E, "BIT7E"},
            {&Z80::EBIT7H, "BIT7H"},
            {&Z80::EBIT7L, "BIT7L"},
            {&Z80::EBIT7mHL, "BIT7mHL"},
            {&Z80::EBIT7A, "BIT7A"},
            {&Z80::ERES0B, "RES0B"},
            {&Z80::ERES0C, "RES0C"},
            {&Z80::ERES0D, "RES0D"},
            {&Z80::ERES0E, "RES0E"},
            {&Z80::ERES0H, "RES0H"},
            {&Z80::ERES0L, "RES0L"},
            {&Z80::ERES0mHL, "RES0mHL"},
            {&Z80::ERES0A, "RES0A"},
            {&Z80::ERES1B, "RES1B"},
            {&Z80::ERES1C, "RES1C"},
            {&Z80::ERES1D, "RES1D"},
            {&Z80::ERES1E, "RES1E"},
            {&Z80::ERES1H, "RES1H"},
            {&Z80::ERES1L, "RES1L"},
            {&Z80::ERES1mHL, "RES1mHL"},
            {&Z80::ERES1A, "RES1A"},
            {&Z80::ERES2B, "RES2B"},
            {&Z80::ERES2C, "RES2C"},
            {&Z80::ERES2D, "RES2D"},
            {&Z80::ERES2E, "RES2E"},
            {&Z80::ERES2H, "RES2H"},
            {&Z80::ERES2L, "RES2L"},
            {&Z80::ERES2mHL, "RES2mHL"},
            {&Z80::ERES2A, "RES2A"},
            {&Z80::ERES3B, "RES3B"},
            {&Z80::ERES3C, "RES3C"},
            {&Z80::ERES3D, "RES3D"},
            {&Z80::ERES3E, "RES3E"},
            {&Z80::ERES3H, "RES3H"},
            {&Z80::ERES3L, "RES3L"},
            {&Z80::ERES3mHL, "RES3mHL"},
            {&Z80::ERES3A, "RES3A"},
            {&Z80::ERES4B, "RES4B"},
            {&Z80::ERES4C, "RES4C"},
            {&Z80::ERES4D, "RES4D"},
            {&Z80::ERES4E, "RES4E"},
            {&Z80::ERES4H, "RES4H"},
            {&Z80::ERES4L, "RES4L"},
            {&Z80::ERES4mHL, "RES4mHL"},
            {&Z80::ERES4A, "RES4A"},
            {&Z80::ERES5B, "RES5B"},
            {&Z80::ERES5C, "RES5C"},
            {&Z80::ERES5D, "RES5D"},
            {&Z80::ERES5E, "RES5E"},
            {&Z80::ERES5H, "RES5H"},
            {&Z80::ERES5L, "RES5L"},
            {&Z80::ERES5mHL, "RES5mHL"},
            {&Z80::ERES5A, "RES5A"},
            {&Z80::ERES6B, "RES6B"},
            {&Z80::ERES6C, "RES6C"},
            {&Z80::ERES6D, "RES6D"},
            {&Z80::ERES6E, "RES6E"},
            {&Z80::ERES6H, "RES6H"},
            {&Z80::ERES6L, "RES6L"},
            {&Z80::ERES6mHL, "RES6mHL"},
            {&Z80::ERES6A, "RES6A"},
            {&Z80::ERES7B, "RES7B"},
            {&Z80::ERES7C, "RES7C"},
            {&Z80::ERES7D, "RES7D"},
            {&Z80::ERES7E, "RES7E"},
            {&Z80::ERES7H, "RES7H"},
            {&Z80::ERES7L, "RES7L"},
            {&Z80::ERES7mHL, "RES7mHL"},
            {&Z80::ERES7A, "RES7A"},
            {&Z80::ESET0B, "SET0B"},
            {&Z80::ESET0C, "SET0C"},
            {&Z80::ESET0D, "SET0D"},
            {&Z80::ESET0E, "SET0E"},
            {&Z80::ESET0H, "SET0H"},
            {&Z80::ESET0L, "SET0L"},
            {&Z80::ESET0mHL, "SET0mHL"},
            {&Z80::ESET0A, "SET0A"},
            {&Z80::ESET1B, "SET1B"},
            {&Z80::ESET1C, "SET1C"},
            {&Z80::ESET1D, "SET1D"},
            {&Z80::ESET1E, "SET1E"},
            {&Z80::ESET1H, "SET1H"},
            {&Z80::ESET1L, "SET1L"},
            {&Z80::ESET1mHL, "SET1mHL"},
            {&Z80::ESET1A, "SET1A"},
            {&Z80::ESET2B, "SET2B"},
            {&Z80::ESET2C, "SET2C"},
            {&Z80::ESET2D, "SET2D"},
            {&Z80::ESET2E, "SET2E"},
            {&Z80::ESET2H, "SET2H"},
            {&Z80::ESET2L, "SET2L"},
            {&Z80::ESET2mHL, "SET2mHL"},
            {&Z80::ESET2A, "SET2A"},
            {&Z80::ESET3B, "SET3B"},
            {&Z80::ESET3C, "SET3C"},
            {&Z80::ESET3D, "SET3D"},
            {&Z80::ESET3E, "SET3E"},
            {&Z80::ESET3H, "SET3H"},
            {&Z80::ESET3L, "SET3L"},
            {&Z80::ESET3mHL, "SET3mHL"},
            {&Z80::ESET3A, "SET3A"},
            {&Z80::ESET4B, "SET4B"},
            {&Z80::ESET4C, "SET4C"},
            {&Z80::ESET4D, "SET4D"},
            {&Z80::ESET4E, "SET4E"},
            {&Z80::ESET4H, "SET4H"},
            {&Z80::ESET4L, "SET4L"},
            {&Z80::ESET4mHL, "SET4mHL"},
            {&Z80::ESET4A, "SET4A"},
            {&Z80::ESET5B, "SET5B"},
            {&Z80::ESET5C, "SET5C"},
            {&Z80::ESET5D, "SET5D"},
            {&Z80::ESET5E, "SET5E"},
            {&Z80::ESET5H, "SET5H"},
            {&Z80::ESET5L, "SET5L"},
            {&Z80::ESET5mHL, "SET5mHL"},
            {&Z80::ESET5A, "SET5A"},
            {&Z80::ESET6B, "SET6B"},
            {&Z80::ESET6C, "SET6C"},
            {&Z80::ESET6D, "SET6D"},
            {&Z80::ESET6E, "SET6E"},
            {&Z80::ESET6H, "SET6H"},
            {&Z80::ESET6L, "SET6L"},
            {&Z80::ESET6mHL, "SET6mHL"},
            {&Z80::ESET6A, "SET6A"},
            {&Z80::ESET7B, "SET7B"},
            {&Z80::ESET7C, "SET7C"},
            {&Z80::ESET7D, "SET7D"},
            {&Z80::ESET7E, "SET7E"},
            {&Z80::ESET7H, "SET7H"},
            {&Z80::ESET7L, "SET7L"},
            {&Z80::ESET7mHL, "SET7mHL"},
            {&Z80::ESET7A, "SET7A"}
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

        const struct{
            uint8_t m_op_cycles[256] = 
            {
            1,3,2,2,1,1,2,1,5,2,2,2,1,1,2,1,
            1,3,2,2,1,1,2,1,3,2,2,2,1,1,2,1,
            2,3,2,2,1,1,2,1,2,2,2,2,1,1,2,1,
            2,3,2,2,3,3,3,1,2,2,2,2,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            2,2,2,2,2,2,1,2,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            2,3,3,4,3,4,2,4,2,4,3,1,3,6,2,4,
            2,3,3,0,3,4,2,4,2,4,3,0,3,0,2,4,
            3,3,2,0,0,4,2,4,4,1,4,0,0,0,2,4,
            3,3,2,1,0,4,2,4,3,2,4,1,0,0,2,4
            };

            uint8_t m_op_cycles_branched[256] =
            {
            1,3,2,2,1,1,2,1,5,2,2,2,1,1,2,1,
            1,3,2,2,1,1,2,1,3,2,2,2,1,1,2,1,
            3,3,2,2,1,1,2,1,3,2,2,2,1,1,2,1,
            3,3,2,2,3,3,3,1,3,2,2,2,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            2,2,2,2,2,2,1,2,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
            5,3,4,4,6,4,2,4,5,4,4,1,6,6,2,4,
            5,3,4,0,6,4,2,4,5,4,4,0,6,0,2,4,
            3,3,2,0,0,4,2,4,4,1,4,0,0,0,2,4,
            3,3,2,1,0,4,2,4,3,2,4,1,0,0,2,4
            };

            uint8_t m_ext_cycles[256] =
            {
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
            2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2
            };

            uint16_t t_op_cycles[256] = 
            {
            4,12,8,8,4,4,8,4,20,8,8,8,4,4,8,4,
            4,12,8,8,4,4,8,4,12,8,8,8,4,4,8,4,
            8,12,8,8,4,4,8,4,8,8,8,8,4,4,8,4,
            8,12,8,8,12,12,12,4,8,8,8,8,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            8,8,8,8,8,8,4,8,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            8,12,12,16,12,16,8,16,8,16,12,4,12,24,8,16,
            8,12,12,0,12,16,8,16,8,16,12,0,12,0,8,16,
            12,12,8,0,0,16,8,16,16,4,16,0,0,0,8,16,
            12,12,8,4,0,16,8,16,12,8,16,4,0,0,8,16
            };

            uint16_t t_op_cycles_branched[256] =
            {
            4,12,8,8,4,4,8,4,20,8,8,8,4,4,8,4,
            4,12,8,8,4,4,8,4,12,8,8,8,4,4,8,4,
            12,12,8,8,4,4,8,4,12,8,8,8,4,4,8,4,
            12,12,8,8,12,12,12,4,12,8,8,8,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            8,8,8,8,8,8,4,8,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
            20,12,16,16,24,16,8,16,20,16,16,4,24,24,8,16,
            20,12,16,0,24,16,8,16,20,16,16,0,24,0,8,16,
            12,12,8,0,0,16,8,16,16,4,16,0,0,0,8,16,
            12,12,8,4,0,16,8,16,12,8,16,4,0,0,8,16
            };

            uint16_t t_ext_cycles[256] =
            {
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8,
            8,8,8,8,8,8,16,8,8,8,8,8,8,8,16,8
            };

            
        }_timings;

        MMU mmu;
        //GPU gpu;

};
//}z80(29,0,0,0,0,0,0,0,0,0,0,0x0000,0,0);
#endif
