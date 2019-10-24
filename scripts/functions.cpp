#define CARRY (1<<4)
void Z80::NOP();
void Z80::LDBCnn();
void Z80::LDmBCA();
void Z80::INCBC();
void Z80::INCB();
void Z80::DECB();
void Z80::LDBn();
void Z80::RLCA();
void Z80::LDmnnSP();
void Z80::ADDHLBC();
void Z80::LDAmBC();
void Z80::DECBC();
void Z80::INCC();
void Z80::DECC();
void Z80::LDCn();
void Z80::RRCA();
void Z80::STOP();
void Z80::LDDEnn();
void Z80::LDmDEA();
void Z80::INCDE();
void Z80::INCD();
void Z80::DECD();
void Z80::LDDn();
void Z80::RLA();
void Z80::JRn();
void Z80::ADDHLDE();
void Z80::LDAmDE();
void Z80::DECDE();
void Z80::INCE();
void Z80::DECE();
void Z80::LDEn();
void Z80::RRA();
void Z80::JRNZn();
void Z80::LDHLnn();
void Z80::LDImHLA();
void Z80::INCHL();
void Z80::INCH();
void Z80::DECH();
void Z80::LDHn();
void Z80::DAA();
void Z80::JRZn();
void Z80::ADDHLHL();
void Z80::LDImHL();
void Z80::DECHL();
void Z80::INCL();
void Z80::DECL();
void Z80::LDLn();
void Z80::NOT();
void Z80::JRNCn();
void Z80::LDSPnn();
void Z80::LDDmHLA();
void Z80::INCSP();
void Z80::INCmHL();
void Z80::DECmHL();
void Z80::LDmHLn();
void Z80::SCF();
void Z80::JRCn();
void Z80::ADDHLSP();
void Z80::LDDAmHL();
void Z80::DECSP();
void Z80::INCA();
void Z80::DECA();
void Z80::LDAn();
void Z80::CCF();
void Z80::LDBB();
void Z80::LDBC();
void Z80::LDBD();
void Z80::LDBE();
void Z80::LDBH();
void Z80::LDBL();
void Z80::LDBmHL();
void Z80::LDBA();
void Z80::LDCB();
void Z80::LDCC();
void Z80::LDCD();
void Z80::LDCE();
void Z80::LDCH();
void Z80::LDCL();
void Z80::LDCmHL();
void Z80::LDCA();
void Z80::LDDB();
void Z80::LDDC();
void Z80::LDDD();
void Z80::LDDE();
void Z80::LDDH();
void Z80::LDDL();
void Z80::LDDmHL();
void Z80::LDDA();
void Z80::LDEB();
void Z80::LDEC();
void Z80::LDED();
void Z80::LDEE();
void Z80::LDEH();
void Z80::LDEL();
void Z80::LDEmHL();
void Z80::LDEA();
void Z80::LDHB();
void Z80::LDHC();
void Z80::LDHD();
void Z80::LDHE();
void Z80::LDHH();
void Z80::LDHL();
void Z80::LDHmHL();
void Z80::LDHA();
void Z80::LDLB();
void Z80::LDLC();
void Z80::LDLD();
void Z80::LDLE();
void Z80::LDLH();
void Z80::LDLL();
void Z80::LDLmHL();
void Z80::LDLA();
void Z80::LDmHLB();
void Z80::LDmHLC();
void Z80::LDmHLD();
void Z80::LDmHLE();
void Z80::LDmHLH();
void Z80::LDmHLL();
void Z80::HALT();
void Z80::LDmHLA();
void Z80::LDAB();
void Z80::LDAC();
void Z80::LDAD();
void Z80::LDAE();
void Z80::LDAH();
void Z80::LDAL();
void Z80::LDAmHL();
void Z80::LDAA();
void Z80::ADDAB();
void Z80::ADDAC();
void Z80::ADDAD();
void Z80::ADDAE();
void Z80::ADDAH();
void Z80::ADDAL();
void Z80::ADDAmHL();
void Z80::ADDAA();
void Z80::ADCAB();
void Z80::ADCAC();
void Z80::ADCAD();
void Z80::ADCAE();
void Z80::ADCAH();
void Z80::ADCAL();
void Z80::ADCAmHL();
void Z80::ADCAA();
void Z80::SUBAB();
void Z80::SUBAC();
void Z80::SUBAD();
void Z80::SUBAE();
void Z80::SUBAH();
void Z80::SUBAL();
void Z80::SUBAmHL();
void Z80::SUBAA();
void Z80::SBCAB();
void Z80::SBCAC();
void Z80::SBCAD();
void Z80::SBCAE();
void Z80::SBCAH();
void Z80::SBCAL();
void Z80::SBCAmHL();
void Z80::SBCAA();
void Z80::ANDB();
void Z80::ANDC();
void Z80::ANDD();
void Z80::ANDE();
void Z80::ANDH();
void Z80::ANDL();
void Z80::ANDmHL();
void Z80::ANDA();
void Z80::XORB();
void Z80::XORC();
void Z80::XORD();
void Z80::XORE();
void Z80::XORH();
void Z80::XORL();
void Z80::XORmHL();
void Z80::XORA();
void Z80::ORB();
void Z80::ORC();
void Z80::ORD();
void Z80::ORE();
void Z80::ORH();
void Z80::ORL();
void Z80::ORmHL();
void Z80::ORA();
void Z80::CPB();
void Z80::CPC();
void Z80::CPD();
void Z80::CPE();
void Z80::CPH();
void Z80::CPL();
void Z80::CPmHL();
void Z80::CPA();
void Z80::RETNZ();
void Z80::POPBC();
void Z80::JPNZnn();
void Z80::JPnn();
void Z80::CALLNZnn();
void Z80::PUSHBC();
void Z80::ADDAn();
void Z80::RST0();
void Z80::RETZ();
void Z80::RET();
void Z80::JPZnn();
void Z80::Extops();
void Z80::CALLZnn();
void Z80::CALLnn();
void Z80::ADCAn();
void Z80::RST8();
void Z80::RETNC();
void Z80::POPDE();
void Z80::JPNCnn();
void Z80::XX1();
void Z80::CALLNCnn();
void Z80::PUSHDE();
void Z80::SUBAn();
void Z80::RST10();
void Z80::RETC();
void Z80::RETI();
void Z80::JPCnn();
void Z80::XX2();
void Z80::CALLCnn();
void Z80::XX3();
void Z80::SBCAn();
void Z80::RST18();
void Z80::LDHmnA();
void Z80::POPHL();
void Z80::LDHmCA();
void Z80::XX4();
void Z80::XX5();
void Z80::PUSHHL();
void Z80::ANDn();
void Z80::RST20();
void Z80::ADDSPd();
void Z80::JPmHL();
void Z80::LDmnnA();
void Z80::XX6();
void Z80::XX7();
void Z80::XX8();
void Z80::XORn();
void Z80::RST28();
void Z80::LDHAmn();
void Z80::POPAF();
void Z80::XX9();
void Z80::DI();
void Z80::XXA();
void Z80::PUSHAF();
void Z80::ORn();
void Z80::RST30();
void Z80::LDHLSPd();
void Z80::LDSPHL();
void Z80::LDAmnn();
void Z80::EI();
void Z80::XXB();
void Z80::XXC();
void Z80::CPn();
void Z80::RST38();
