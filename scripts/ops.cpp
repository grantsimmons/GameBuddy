#define CARRY (1<<4)
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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

void Z80::LDImHL(){
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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

