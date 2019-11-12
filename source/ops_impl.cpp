#ifndef _OPS_
#define _OPS_

#include "Z80.h"

#define CARRY (1<<0)
#define ADD_SUB (1<<1)
#define PARITY_OVERFLOW (1<<2)
#define HALF_CARRY (1<<3)
#define ZERO (1<<4)
#define SIGN (1<<5)

void Z80::NOP(){
    std::cout << "NOP" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDBCnn(){
    std::cout << "LDBCnn" <<std::endl;
    this->_r.c = this->mmu.rb(this->_r.pc);
    this->_r.b = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
}

void Z80::LDmBCA(){
    std::cout << "LDmBCA" <<std::endl;
    this->mmu.wb(this->_r.b << 8 + this->_r.c, this->_r.a);
}

void Z80::INCBC(){
    std::cout << "INCBC" <<std::endl;
    this->_r.c += 1;
    this->_r.b = this->_r.c == 0x00 ? this->_r.b + 1 : this->_r.b;
    //Set OF, Z, etc.
}

void Z80::INCB(){
    std::cout << "INCB" <<std::endl;
    this->_r.b += 1;
    //Set OF, Z, etc.
}

void Z80::DECB(){
    std::cout << "DECB" <<std::endl;
    this->_r.b -= 1;
    //Set UF, Z, etc.
}

void Z80::LDBn(){
    std::cout << "LDBn" <<std::endl;
    this->_r.b = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::RLCA(){
    std::cout << "RLCA" <<std::endl;
    this->_r.f = this->_r.a & 0x80; //FIXME: Carry flag position
    this->_r.a = this->_r.a << 1 + ((this->_r.a & 0x80) >> 7);
}

void Z80::LDmnnSP(){
    std::cout << "LDmnnSP" <<std::endl;
    this->mmu.ww(this->mmu.rb(this->_r.pc) + (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.sp);
    this->_r.pc += 2;
}

void Z80::ADDHLBC(){
    std::cout << "ADDHLBC" <<std::endl;
}

void Z80::LDAmBC(){
    std::cout << "LDAmBC" <<std::endl;
    this->_r.a = this->mmu.rb(this->_r.b << 8 + this->_r.c);
}

void Z80::DECBC(){
    std::cout << "DECBC" <<std::endl;
    this->_r.c -= 1;
    this->_r.b = this->_r.c == 0xFF ? this->_r.b - 1 : this->_r.b;
    this->_r.f = (this->_r.h == 0x0 && this->_r.l == 0x0) ? this->_r.f | ZERO : this->_r.f;
    //Set UF, Z, etc.
}

void Z80::INCC(){
    std::cout << "INCC" <<std::endl;
    this->_r.c += 1;
    //Set OF, Z, etc.
}

void Z80::DECC(){
    std::cout << "DECC" <<std::endl;
    this->_r.c -= 1;
    //Set UF, Z, etc.
}

void Z80::LDCn(){
    std::cout << "LDCn" <<std::endl;
    this->_r.c = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::RRCA(){
    std::cout << "RRCA" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::STOP(){
    std::cout << "STOP" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDDEnn(){
    std::cout << "LDDEnn" <<std::endl;
    this->_r.e = this->mmu.rb(this->_r.pc);
    this->_r.d = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
}

void Z80::LDmDEA(){
    std::cout << "LDmDEA" <<std::endl;
    this->mmu.wb(this->_r.d << 8 + this->_r.e, this->_r.a);
}

void Z80::INCDE(){
    std::cout << "INCDE" <<std::endl;
    this->_r.e += 1;
    this->_r.d = this->_r.e == 0x00 ? this->_r.d + 1 : this->_r.d;
    //Set OF, Z, etc.
}

void Z80::INCD(){
    std::cout << "INCD" <<std::endl;
    this->_r.d += 1;
    //Set OF, Z, etc.
}

void Z80::DECD(){
    std::cout << "DECD" <<std::endl;
    this->_r.d -= 1;
    //Set UF, Z, etc.
}

void Z80::LDDn(){
    std::cout << "LDDn" <<std::endl;
    this->_r.d = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::RLA(){
    std::cout << "RLA" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRn(){
    std::cout << "JRn" <<std::endl;
    this->_r.pc += (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::ADDHLDE(){
    std::cout << "ADDHLDE" <<std::endl;
}

void Z80::LDAmDE(){
    std::cout << "LDAmDE" <<std::endl;
    this->_r.a = this->mmu.rb(this->_r.d << 8 + this->_r.e);
}

void Z80::DECDE(){
    std::cout << "DECDE" <<std::endl;
    this->_r.e -= 1;
    this->_r.d = this->_r.e == 0xFF ? this->_r.d - 1 : this->_r.d;
    this->_r.f = (this->_r.h == 0x0 && this->_r.l == 0x0) ? this->_r.f | ZERO : this->_r.f;
    //Set UF, Z, etc.
}

void Z80::INCE(){
    std::cout << "INCE" <<std::endl;
    this->_r.e += 1;
    //Set OF, Z, etc.
}

void Z80::DECE(){
    std::cout << "DECE" <<std::endl;
    this->_r.e -= 1;
    //Set UF, Z, etc.
}

void Z80::LDEn(){
    std::cout << "LDEn" <<std::endl;
    this->_r.e = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::RRA(){
    std::cout << "RRA" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRNZn(){
    //std::cout << "JRNZn" <<std::endl;
    this->_r.pc += this->_r.f & ZERO ? 0 : (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::LDHLnn(){
    std::cout << "LDHLnn" <<std::endl;
    this->_r.l = this->mmu.rb(this->_r.pc);
    this->_r.h = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
}

void Z80::LDImHLA(){
    std::cout << "LDImHLA" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);
    this->INCHL();
}

void Z80::INCHL(){
    std::cout << "INCHL" <<std::endl;
    this->_r.l += 1;
    this->_r.h = this->_r.l == 0x00 ? this->_r.h + 1 : this->_r.h;
    //Set OF, Z, etc.
}

void Z80::INCH(){
    std::cout << "INCH" <<std::endl;
    this->_r.h += 1;
    //Set OF, Z, etc.
}

void Z80::DECH(){
    std::cout << "DECH" <<std::endl;
    this->_r.h -= 1;
    //Set UF, Z, etc.
}

void Z80::LDHn(){
    std::cout << "LDHn" <<std::endl;
    this->_r.h = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::DAA(){
    std::cout << "DAA" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRZn(){
    std::cout << "JRZn" <<std::endl;
    this->_r.pc += this->_r.f & ZERO ? (int8_t) this->mmu.rb(this->_r.pc) : 0;
    this->_r.pc += 1;
}

void Z80::ADDHLHL(){
    std::cout << "ADDHLHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDIAmHL(){
    std::cout << "LDIAmHL" <<std::endl;
    this->_r.a = this->mmu.rb(this->_r.h << 8 + this->_r.l);
    this->INCHL();
}

void Z80::DECHL(){
    //std::cout << "DECHL" <<std::endl;
    this->_r.l -= 1;
    this->_r.h = this->_r.l == 0xFF ? this->_r.h - 1 : this->_r.h;
    this->_r.f = (this->_r.h == 0x0 && this->_r.l == 0x0) ? this->_r.f | ZERO : this->_r.f;
    //Set UF, Z, etc.
}

void Z80::INCL(){
    std::cout << "INCL" <<std::endl;
    this->_r.l += 1;
    //Set OF, Z, etc.
}

void Z80::DECL(){
    std::cout << "DECL" <<std::endl;
    this->_r.l -= 1;
    //Set UF, Z, etc.
}

void Z80::LDLn(){
    std::cout << "LDLn" <<std::endl;
    this->_r.l = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::NOT(){
    std::cout << "NOT" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRNCn(){
    std::cout << "JRNCn" <<std::endl;
    this->_r.pc += this->_r.f & CARRY ? 0 : (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::LDSPnn(){
    std::cout << "LDSPnn" <<std::endl;
    this->_r.sp = this->mmu.rw(this->_r.pc);
    this->_r.pc += 2;
}

void Z80::LDDmHLA(){
    //std::cout << "LDDmHLA" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);
    this->DECHL();
}

void Z80::INCSP(){
    std::cout << "INCSP" <<std::endl;
    this->_r.sp += 1;
    //Set OF, Z, etc.
}

void Z80::INCmHL(){
    std::cout << "INCmHL" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.h << 8 + this->_r.l) + 1);
    //Set OF, Z, etc. if needed?
}

void Z80::DECmHL(){
    std::cout << "DECmHL" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.h << 8 + this->_r.l) - 1);
    //Set UF, Z, etc. if needed?
}

void Z80::LDmHLn(){
    std::cout << "LDmHLn" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->mmu.rb(this->_r.pc));
    this->_r.pc += 1;
}

void Z80::SCF(){
    std::cout << "SCF" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JRCn(){
    std::cout << "JRCn" <<std::endl;
    this->_r.pc += this->_r.f & CARRY ? (int8_t) this->mmu.rb(this->_r.pc) : 0;
    this->_r.pc += 1;
}

void Z80::ADDHLSP(){
    std::cout << "ADDHLSP" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDDAmHL(){
    std::cout << "LDDAmHL" <<std::endl;
    this->_r.a = this->mmu.rb(this->_r.h << 8 + this->_r.l);
    this->DECHL();
}

void Z80::DECSP(){
    std::cout << "DECSP" <<std::endl;
    this->_r.sp -= 1;
    //Set UF, Z, etc.
}

void Z80::INCA(){
    std::cout << "INCA" <<std::endl;
    this->_r.a += 1;
    //Set OF, Z, etc.
}

void Z80::DECA(){
    std::cout << "DECA" <<std::endl;
    this->_r.a -= 1;
    //Set UF, Z, etc.
}

void Z80::LDAn(){
    std::cout << "LDAn" <<std::endl;
    this->_r.a = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::CCF(){
    std::cout << "CCF" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDBB(){
    std::cout << "LDBB" <<std::endl;
    this->_r.b = this->_r.b;
}

void Z80::LDBC(){
    std::cout << "LDBC" <<std::endl;
    this->_r.b = this->_r.c;
}

void Z80::LDBD(){
    std::cout << "LDBD" <<std::endl;
    this->_r.b = this->_r.d;
}

void Z80::LDBE(){
    std::cout << "LDBE" <<std::endl;
    this->_r.b = this->_r.e;
}

void Z80::LDBH(){
    std::cout << "LDBH" <<std::endl;
    this->_r.b = this->_r.h;
}

void Z80::LDBL(){
    std::cout << "LDBL" <<std::endl;
    this->_r.b = this->_r.l;
}

void Z80::LDBmHL(){
    std::cout << "LDBmHL" <<std::endl;
    this->_r.b = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDBA(){
    std::cout << "LDBA" <<std::endl;
    this->_r.b = this->_r.a;
}

void Z80::LDCB(){
    std::cout << "LDCB" <<std::endl;
    this->_r.c = this->_r.b;
}

void Z80::LDCC(){
    std::cout << "LDCC" <<std::endl;
    this->_r.c = this->_r.c;
}

void Z80::LDCD(){
    std::cout << "LDCD" <<std::endl;
    this->_r.c = this->_r.d;
}

void Z80::LDCE(){
    std::cout << "LDCE" <<std::endl;
    this->_r.c = this->_r.e;
}

void Z80::LDCH(){
    std::cout << "LDCH" <<std::endl;
    this->_r.c = this->_r.h;
}

void Z80::LDCL(){
    std::cout << "LDCL" <<std::endl;
    this->_r.c = this->_r.l;
}

void Z80::LDCmHL(){
    std::cout << "LDCmHL" <<std::endl;
    this->_r.c = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDCA(){
    std::cout << "LDCA" <<std::endl;
    this->_r.c = this->_r.a;
}

void Z80::LDDB(){
    std::cout << "LDDB" <<std::endl;
    this->_r.d = this->_r.b;
}

void Z80::LDDC(){
    std::cout << "LDDC" <<std::endl;
    this->_r.d = this->_r.c;
}

void Z80::LDDD(){
    std::cout << "LDDD" <<std::endl;
    this->_r.d = this->_r.d;
}

void Z80::LDDE(){
    std::cout << "LDDE" <<std::endl;
    this->_r.d = this->_r.e;
}

void Z80::LDDH(){
    std::cout << "LDDH" <<std::endl;
    this->_r.d = this->_r.h;
}

void Z80::LDDL(){
    std::cout << "LDDL" <<std::endl;
    this->_r.d = this->_r.l;
}

void Z80::LDDmHL(){
    std::cout << "LDDmHL" <<std::endl;
    this->_r.d = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDDA(){
    std::cout << "LDDA" <<std::endl;
    this->_r.d = this->_r.a;
}

void Z80::LDEB(){
    std::cout << "LDEB" <<std::endl;
    this->_r.e = this->_r.b;
}

void Z80::LDEC(){
    std::cout << "LDEC" <<std::endl;
    this->_r.e = this->_r.c;
}

void Z80::LDED(){
    std::cout << "LDED" <<std::endl;
    this->_r.e = this->_r.d;
}

void Z80::LDEE(){
    std::cout << "LDEE" <<std::endl;
    this->_r.e = this->_r.e;
}

void Z80::LDEH(){
    std::cout << "LDEH" <<std::endl;
    this->_r.e = this->_r.h;
}

void Z80::LDEL(){
    std::cout << "LDEL" <<std::endl;
    this->_r.e = this->_r.l;
}

void Z80::LDEmHL(){
    std::cout << "LDEmHL" <<std::endl;
    this->_r.e = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDEA(){
    std::cout << "LDEA" <<std::endl;
    this->_r.e = this->_r.a;
}

void Z80::LDHB(){
    std::cout << "LDHB" <<std::endl;
    this->_r.h = this->_r.b;
}

void Z80::LDHC(){
    std::cout << "LDHC" <<std::endl;
    this->_r.h = this->_r.c;
}

void Z80::LDHD(){
    std::cout << "LDHD" <<std::endl;
    this->_r.h = this->_r.d;
}

void Z80::LDHE(){
    std::cout << "LDHE" <<std::endl;
    this->_r.h = this->_r.e;
}

void Z80::LDHH(){
    std::cout << "LDHH" <<std::endl;
    this->_r.h = this->_r.h;
}

void Z80::LDHL(){
    std::cout << "LDHL" <<std::endl;
    this->_r.h = this->_r.l;
}

void Z80::LDHmHL(){
    std::cout << "LDHmHL" <<std::endl;
    this->_r.h = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDHA(){
    std::cout << "LDHA" <<std::endl;
    this->_r.h = this->_r.a;
}

void Z80::LDLB(){
    std::cout << "LDLB" <<std::endl;
    this->_r.l = this->_r.b;
}

void Z80::LDLC(){
    std::cout << "LDLC" <<std::endl;
    this->_r.l = this->_r.c;
}

void Z80::LDLD(){
    std::cout << "LDLD" <<std::endl;
    this->_r.l = this->_r.d;
}

void Z80::LDLE(){
    std::cout << "LDLE" <<std::endl;
    this->_r.l = this->_r.e;
}

void Z80::LDLH(){
    std::cout << "LDLH" <<std::endl;
    this->_r.l = this->_r.h;
}

void Z80::LDLL(){
    std::cout << "LDLL" <<std::endl;
    this->_r.l = this->_r.l;
}

void Z80::LDLmHL(){
    std::cout << "LDLmHL" <<std::endl;
    this->_r.l = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDLA(){
    std::cout << "LDLA" <<std::endl;
    this->_r.l = this->_r.a;
}

void Z80::LDmHLB(){
    std::cout << "LDmHLB" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.b);
}

void Z80::LDmHLC(){
    std::cout << "LDmHLC" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.c);
}

void Z80::LDmHLD(){
    std::cout << "LDmHLD" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.d);
}

void Z80::LDmHLE(){
    std::cout << "LDmHLE" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.e);
}

void Z80::LDmHLH(){
    std::cout << "LDmHLH" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.h);
}

void Z80::LDmHLL(){
    std::cout << "LDmHLL" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.l);
}

void Z80::HALT(){
    std::cout << "HALT" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDmHLA(){
    std::cout << "LDmHLA" <<std::endl;
    this->mmu.wb(this->_r.h << 8 + this->_r.l, this->_r.a);
}

void Z80::LDAB(){
    std::cout << "LDAB" <<std::endl;
    this->_r.a = this->_r.b;
}

void Z80::LDAC(){
    std::cout << "LDAC" <<std::endl;
    this->_r.a = this->_r.c;
}

void Z80::LDAD(){
    std::cout << "LDAD" <<std::endl;
    this->_r.a = this->_r.d;
}

void Z80::LDAE(){
    std::cout << "LDAE" <<std::endl;
    this->_r.a = this->_r.e;
}

void Z80::LDAH(){
    std::cout << "LDAH" <<std::endl;
    this->_r.a = this->_r.h;
}

void Z80::LDAL(){
    std::cout << "LDAL" <<std::endl;
    this->_r.a = this->_r.l;
}

void Z80::LDAmHL(){
    std::cout << "LDAmHL" <<std::endl;
    this->_r.a = this->mmu.rb(this->_r.h << 8 + this->_r.l);
}

void Z80::LDAA(){
    std::cout << "LDAA" <<std::endl;
    this->_r.a = this->_r.a;
}

void Z80::ADDAB(){
    std::cout << "ADDAB" <<std::endl;
    this->_r.f = ((this->_r.a + this->_r.b) >> 8) & 0x1;
    this->_r.a += this->_r.b;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAC(){
    std::cout << "ADDAC" <<std::endl;
    this->_r.f = ((this->_r.a + this->_r.c) >> 8) & 0x1;
    this->_r.a += this->_r.c;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAD(){
    std::cout << "ADDAD" <<std::endl;
    this->_r.f = ((this->_r.a + this->_r.d) >> 8) & 0x1;
    this->_r.a += this->_r.d;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAE(){
    std::cout << "ADDAE" <<std::endl;
    this->_r.f = ((this->_r.a + this->_r.e) >> 8) & 0x1;
    this->_r.a += this->_r.e;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAH(){
    std::cout << "ADDAH" <<std::endl;
    this->_r.f = ((this->_r.a + this->_r.h) >> 8) & 0x1;
    this->_r.a += this->_r.h;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAL(){
    std::cout << "ADDAL" <<std::endl;
    this->_r.f = ((this->_r.a + this->_r.l) >> 8) & 0x1;
    this->_r.a += this->_r.l;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAmHL(){
    std::cout << "ADDAmHL" <<std::endl;
    this->_r.f = ((this->_r.a + this->mmu.rb(this->_r.h << 8 + this->_r.l)) >> 8) & 0x1;
    this->_r.a += this->mmu.rb(this->_r.h << 8 + this->_r.l);
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADDAA(){
    std::cout << "ADDAA" <<std::endl;
    this->_r.f = ((this->_r.a + this->_r.a) >> 8) & 0x1;
    this->_r.a += this->_r.a;
    this->_r.a &= 0xFF;
    //Set 0, OF (above), etc.
}

void Z80::ADCAB(){
    std::cout << "ADCAB" <<std::endl;
    this->_r.a = this->_r.a + this->_r.b + (this->_r.f & CARRY);
}

void Z80::ADCAC(){
    std::cout << "ADCAC" <<std::endl;
    this->_r.a = this->_r.a + this->_r.c + (this->_r.f & CARRY);
}

void Z80::ADCAD(){
    std::cout << "ADCAD" <<std::endl;
    this->_r.a = this->_r.a + this->_r.d + (this->_r.f & CARRY);
}

void Z80::ADCAE(){
    std::cout << "ADCAE" <<std::endl;
    this->_r.a = this->_r.a + this->_r.e + (this->_r.f & CARRY);
}

void Z80::ADCAH(){
    std::cout << "ADCAH" <<std::endl;
    this->_r.a = this->_r.a + this->_r.h + (this->_r.f & CARRY);
}

void Z80::ADCAL(){
    std::cout << "ADCAL" <<std::endl;
    this->_r.a = this->_r.a + this->_r.l + (this->_r.f & CARRY);
}

void Z80::ADCAmHL(){
    std::cout << "ADCAmHL" <<std::endl;
    this->_r.a = this->_r.a + this->mmu.rb(this->_r.h << 8 + this->_r.l) + (this->_r.f & CARRY);
    this->_r.pc += 1;
}

void Z80::ADCAA(){
    std::cout << "ADCAA" <<std::endl;
    this->_r.a = this->_r.a + this->_r.a + (this->_r.f & CARRY);
}

void Z80::SUBAB(){
    std::cout << "SUBAB" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAC(){
    std::cout << "SUBAC" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAD(){
    std::cout << "SUBAD" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAE(){
    std::cout << "SUBAE" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAH(){
    std::cout << "SUBAH" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAL(){
    std::cout << "SUBAL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAmHL(){
    std::cout << "SUBAmHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SUBAA(){
    std::cout << "SUBAA" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAB(){
    std::cout << "SBCAB" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAC(){
    std::cout << "SBCAC" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAD(){
    std::cout << "SBCAD" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAE(){
    std::cout << "SBCAE" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAH(){
    std::cout << "SBCAH" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAL(){
    std::cout << "SBCAL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAmHL(){
    std::cout << "SBCAmHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAA(){
    std::cout << "SBCAA" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ANDB(){
    std::cout << "ANDB" <<std::endl;
    this->_r.a &= this->_r.b;
    //Set 0, carry, etc.
}

void Z80::ANDC(){
    std::cout << "ANDC" <<std::endl;
    this->_r.a &= this->_r.c;
    //Set 0, carry, etc.
}

void Z80::ANDD(){
    std::cout << "ANDD" <<std::endl;
    this->_r.a &= this->_r.d;
    //Set 0, carry, etc.
}

void Z80::ANDE(){
    std::cout << "ANDE" <<std::endl;
    this->_r.a &= this->_r.e;
    //Set 0, carry, etc.
}

void Z80::ANDH(){
    std::cout << "ANDH" <<std::endl;
    this->_r.a &= this->_r.h;
    //Set 0, carry, etc.
}

void Z80::ANDL(){
    std::cout << "ANDL" <<std::endl;
    this->_r.a &= this->_r.l;
    //Set 0, carry, etc.
}

void Z80::ANDmHL(){
    std::cout << "ANDmHL" <<std::endl;
    this->_r.a &= this->mmu.rb(this->_r.h << 8 + this->_r.l);
    //Set 0, carry, etc.
}

void Z80::ANDA(){
    std::cout << "ANDA" <<std::endl;
    this->_r.a &= this->_r.a;
    //Set 0, carry, etc.
}

void Z80::XORB(){
    std::cout << "XORB" <<std::endl;
    this->_r.a ^= this->_r.b;
    //Set 0, carry, etc.
}

void Z80::XORC(){
    std::cout << "XORC" <<std::endl;
    this->_r.a ^= this->_r.c;
    //Set 0, carry, etc.
}

void Z80::XORD(){
    std::cout << "XORD" <<std::endl;
    this->_r.a ^= this->_r.d;
    //Set 0, carry, etc.
}

void Z80::XORE(){
    std::cout << "XORE" <<std::endl;
    this->_r.a ^= this->_r.e;
    //Set 0, carry, etc.
}

void Z80::XORH(){
    std::cout << "XORH" <<std::endl;
    this->_r.a ^= this->_r.h;
    //Set 0, carry, etc.
}

void Z80::XORL(){
    std::cout << "XORL" <<std::endl;
    this->_r.a ^= this->_r.l;
    //Set 0, carry, etc.
}

void Z80::XORmHL(){
    std::cout << "XORmHL" <<std::endl;
    this->_r.a ^= this->mmu.rb(this->_r.h << 8 + this->_r.l);
    //Set 0, carry, etc.
}

void Z80::XORA(){
    std::cout << "XORA" <<std::endl;
    this->_r.a ^= this->_r.a;
    //Set 0, carry, etc.
}

void Z80::ORB(){
    std::cout << "ORB" <<std::endl;
    this->_r.a |= this->_r.b;
    //Set 0, carry, etc.
}

void Z80::ORC(){
    std::cout << "ORC" <<std::endl;
    this->_r.a |= this->_r.c;
    //Set 0, carry, etc.
}

void Z80::ORD(){
    std::cout << "ORD" <<std::endl;
    this->_r.a |= this->_r.d;
    //Set 0, carry, etc.
}

void Z80::ORE(){
    std::cout << "ORE" <<std::endl;
    this->_r.a |= this->_r.e;
    //Set 0, carry, etc.
}

void Z80::ORH(){
    std::cout << "ORH" <<std::endl;
    this->_r.a |= this->_r.h;
    //Set 0, carry, etc.
}

void Z80::ORL(){
    std::cout << "ORL" <<std::endl;
    this->_r.a |= this->_r.l;
    //Set 0, carry, etc.
}

void Z80::ORmHL(){
    std::cout << "ORmHL" <<std::endl;
    this->_r.a |= this->mmu.rb(this->_r.h << 8 + this->_r.l);
    //Set 0, carry, etc.
}

void Z80::ORA(){
    std::cout << "ORA" <<std::endl;
    this->_r.a |= this->_r.a;
    //Set 0, carry, etc.
}

void Z80::CPB(){
    std::cout << "CPB" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPC(){
    std::cout << "CPC" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPD(){
    std::cout << "CPD" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPE(){
    std::cout << "CPE" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPH(){
    std::cout << "CPH" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPL(){
    std::cout << "CPL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPmHL(){
    std::cout << "CPmHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPA(){
    std::cout << "CPA" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETNZ(){
    std::cout << "RETNZ" <<std::endl;
    if(this->_r.f & ZERO == 0){
        this->_r.pc = this->mmu.rb(this->_r.sp) & this->mmu.rb(this->_r.sp + 1);
        this->_r.sp += 2;
    }
}

void Z80::POPBC(){
    std::cout << "POPBC" <<std::endl;
    this->_r.c = this->mmu.rb(this->_r.sp);
    this->_r.b = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::JPNZnn(){
    std::cout << "JPNZnn" <<std::endl;
    this->_r.pc = (this->_r.f & ZERO) ? this->_r.pc : this->mmu.rw(this->_r.pc);
    this->_r.pc += (this->_r.f & ZERO) ? 0 : 2;
}

void Z80::JPnn(){
    std::cout << "JPnn" <<std::endl;
}

void Z80::CALLNZnn(){
    std::cout << "CALLNZnn" <<std::endl;
    if(this->_r.f & ZERO == 0){
        this->mmu.wb(this->_r.sp, (this->_r.pc + 2) & 0xFF00);
        this->mmu.wb(this->_r.sp - 1, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
}

void Z80::PUSHBC(){
    std::cout << "PUSHBC" <<std::endl;
    this->mmu.wb(this->_r.sp, this->_r.b);
    this->mmu.wb(this->_r.sp - 1, this->_r.c);
    this->_r.sp -= 2;
}

void Z80::ADDAn(){
    std::cout << "ADDAn" <<std::endl;
    this->_r.f = (this->_r.a + this->mmu.rb(this->_r.pc) >> 8) & 0x1;
    this->_r.a += this->mmu.rb(this->_r.pc);
    this->_r.a &= 0xFF;
    this->_r.pc += 1;
    //Set 0, OF (above), etc.
}

void Z80::RST0(){
    std::cout << "RST0" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETZ(){
    std::cout << "RETZ" <<std::endl;
    if(this->_r.f & ZERO == 1){
        this->_r.pc = this->mmu.rb(this->_r.sp) & this->mmu.rb(this->_r.sp + 1);
        this->_r.sp += 2;
    }
}

void Z80::RET(){
    std::cout << "RET" <<std::endl;
        this->_r.pc = this->mmu.rb(this->_r.sp) & this->mmu.rb(this->_r.sp + 1);
        this->_r.sp += 2;
}

void Z80::JPZnn(){
    std::cout << "JPZnn" <<std::endl;
    this->_r.pc = (this->_r.f & ZERO) ? this->mmu.rw(this->_r.pc) : this->_r.pc;
    this->_r.pc += (this->_r.f & ZERO) ? 2 : 0;
}

void Z80::Extops(){
    //std::cout << "Extops" <<std::endl;
    (this->*ext_ops[mmu.rb(this->_r.pc++)].op_function)();
}

void Z80::CALLZnn(){
    std::cout << "CALLZnn" <<std::endl;
    if(this->_r.f & ZERO == 1){
        this->mmu.wb(this->_r.sp, (this->_r.pc + 2) & 0xFF00);
        this->mmu.wb(this->_r.sp - 1, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
}

void Z80::CALLnn(){
    std::cout << "CALLnn" <<std::endl;
        this->mmu.wb(this->_r.sp, (this->_r.pc + 2) & 0xFF00);
        this->mmu.wb(this->_r.sp - 1, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
}

void Z80::ADCAn(){
    std::cout << "ADCAn" <<std::endl;
    this->_r.a = this->_r.a + this->mmu.rb(this->_r.pc) + (this->_r.f & CARRY);
}

void Z80::RST8(){
    std::cout << "RST8" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETNC(){
    std::cout << "RETNC" <<std::endl;
    if(this->_r.f & CARRY == 0){
        this->_r.pc = this->mmu.rb(this->_r.sp) & this->mmu.rb(this->_r.sp + 1);
        this->_r.sp += 2;
    }
}

void Z80::POPDE(){
    std::cout << "POPDE" <<std::endl;
    this->_r.e = this->mmu.rb(this->_r.sp);
    this->_r.d = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::JPNCnn(){
    std::cout << "JPNCnn" <<std::endl;
    this->_r.pc = (this->_r.f & CARRY) ? this->_r.pc : this->mmu.rw(this->_r.pc);
    this->_r.pc += (this->_r.f & CARRY) ? 0 : 2;
}

void Z80::XX1(){
    std::cout << "XX1" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLNCnn(){
    std::cout << "CALLNCnn" <<std::endl;
    if(this->_r.f & CARRY == 0){
        this->mmu.wb(this->_r.sp, (this->_r.pc + 2) & 0xFF00);
        this->mmu.wb(this->_r.sp - 1, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
}

void Z80::PUSHDE(){
    std::cout << "PUSHDE" <<std::endl;
    this->mmu.wb(this->_r.sp, this->_r.d);
    this->mmu.wb(this->_r.sp - 1, this->_r.e);
    this->_r.sp -= 2;
}

void Z80::SUBAn(){
    std::cout << "SUBAn" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RST10(){
    std::cout << "RST10" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETC(){
    std::cout << "RETC" <<std::endl;
    if(this->_r.f & CARRY == 1){
        this->_r.pc = this->mmu.rb(this->_r.sp) & this->mmu.rb(this->_r.sp + 1);
        this->_r.sp += 2;
    }
}

void Z80::RETI(){
    std::cout << "RETI" <<std::endl;
}

void Z80::JPCnn(){
    std::cout << "JPCnn" <<std::endl;
    this->_r.pc = (this->_r.f & CARRY) ? this->mmu.rw(this->_r.pc) : this->_r.pc;
    this->_r.pc += (this->_r.f & CARRY) ? 2 : 0;
}

void Z80::XX2(){
    std::cout << "XX2" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLCnn(){
    std::cout << "CALLCnn" <<std::endl;
    if(this->_r.f & CARRY == 1){
        this->mmu.wb(this->_r.sp, (this->_r.pc + 2) & 0xFF00);
        this->mmu.wb(this->_r.sp - 1, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
}

void Z80::XX3(){
    std::cout << "XX3" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::SBCAn(){
    std::cout << "SBCAn" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RST18(){
    std::cout << "RST18" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDHmnA(){
    std::cout << "LDHmnA" <<std::endl;
    this->mmu.wb(0xFF00 | this->mmu.rb(this->_r.pc), this->_r.a);
    this->_r.pc += 1;
}

void Z80::POPHL(){
    std::cout << "POPHL" <<std::endl;
    this->_r.l = this->mmu.rb(this->_r.sp);
    this->_r.h = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::LDHmCA(){
    std::cout << "LDHmCA" <<std::endl;
    this->mmu.wb(0xFF00 | this->_r.c, this->_r.a);
}

void Z80::XX4(){
    std::cout << "XX4" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX5(){
    std::cout << "XX5" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::PUSHHL(){
    std::cout << "PUSHHL" <<std::endl;
    this->mmu.wb(this->_r.sp, this->_r.h);
    this->mmu.wb(this->_r.sp - 1, this->_r.l);
    this->_r.sp -= 2;
}

void Z80::ANDn(){
    std::cout << "ANDn" <<std::endl;
    this->_r.a &= this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    //Set 0, carry, etc.
}

void Z80::RST20(){
    std::cout << "RST20" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ADDSPd(){
    std::cout << "ADDSPd" <<std::endl;
    this->_r.sp += this->mmu.rb(this->_r.pc) > 0x7F ? ((int8_t)~this->mmu.rb(this->_r.pc) + 1) & 0xFF : this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
}

void Z80::JPmHL(){
    std::cout << "JPmHL" <<std::endl;
    this->_r.pc = this->mmu.rw(this->_r.h << 8 + this->_r.l);
    this->_r.pc += 2;
}

void Z80::LDmnnA(){
    std::cout << "LDmnnA" <<std::endl;
    this->mmu.wb(this->mmu.rb(this->_r.pc) + (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.a);
    this->_r.pc += 2;
}

void Z80::XX6(){
    std::cout << "XX6" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX7(){
    std::cout << "XX7" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XX8(){
    std::cout << "XX8" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XORn(){
    std::cout << "XORn" <<std::endl;
    this->_r.a ^= this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    //Set 0, carry, etc.
}

void Z80::RST28(){
    std::cout << "RST28" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDHAmn(){
    std::cout << "LDHAmn" <<std::endl;
    this->_r.a = this->mmu.rb(0xFF00 | this->mmu.rb(this->_r.pc));
    this->_r.pc += 1;
}

void Z80::POPAF(){
    std::cout << "POPAF" <<std::endl;
    this->_r.f = this->mmu.rb(this->_r.sp);
    this->_r.a = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::XX9(){
    std::cout << "XX9" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::DI(){
    std::cout << "DI" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XXA(){
    std::cout << "XXA" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::PUSHAF(){
    std::cout << "PUSHAF" <<std::endl;
    this->mmu.wb(this->_r.sp, this->_r.a);
    this->mmu.wb(this->_r.sp - 1, this->_r.f);
    this->_r.sp -= 2;
}

void Z80::ORn(){
    std::cout << "ORn" <<std::endl;
    this->_r.a |= this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    //Set 0, carry, etc.
}

void Z80::RST30(){
    std::cout << "RST30" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDHLSPd(){
    std::cout << "LDHLSPd" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDSPHL(){
    std::cout << "LDSPHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::LDAmnn(){
    std::cout << "LDAmnn" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EI(){
    std::cout << "EI" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XXB(){
    std::cout << "XXB" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::XXC(){
    std::cout << "XXC" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CPn(){
    std::cout << "CPn" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RST38(){
    std::cout << "RST38" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}


void Z80::ERLCB(){
    std::cout << "ERLCB" <<std::endl;
    this->_r.f = ((this->_r.b & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.b = (this->_r.b << 1) | ((this->_r.b & 0x80) >> 7);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERLCC(){
    std::cout << "ERLCC" <<std::endl;
    this->_r.f = ((this->_r.c & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERLCD(){
    std::cout << "ERLCD" <<std::endl;
    this->_r.f = ((this->_r.d & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.d = (this->_r.d << 1) | ((this->_r.d & 0x80) >> 7);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERLCE(){
    std::cout << "ERLCE" <<std::endl;
    this->_r.f = ((this->_r.e & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.e = (this->_r.e << 1) | ((this->_r.e & 0x80) >> 7);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERLCH(){
    std::cout << "ERLCH" <<std::endl;
    this->_r.f = ((this->_r.h & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.h = (this->_r.h << 1) | ((this->_r.h & 0x80) >> 7);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERLCL(){
    std::cout << "ERLCL" <<std::endl;
    this->_r.f = ((this->_r.l & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.l = (this->_r.l << 1) | ((this->_r.l & 0x80) >> 7);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERLCmHL(){
    std::cout << "ERLCmHL" <<std::endl;
    this->_r.f = ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7) | this->_r.f & 0xFE;
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) << 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7));
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERLCA(){
    std::cout << "ERLCA" <<std::endl;
    this->_r.f = ((this->_r.a & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.a = (this->_r.a << 1) | ((this->_r.a & 0x80) >> 7);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERRCB(){
    std::cout << "ERRCB" <<std::endl;
    this->_r.f = (this->_r.b & 0x1) | (this->_r.f & 0xFE);
    this->_r.b = (this->_r.b >> 1) | ((this->_r.b & 0x1) << 7);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERRCC(){
    std::cout << "ERRCC" <<std::endl;
    this->_r.f = (this->_r.c & 0x1) | (this->_r.f & 0xFE);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERRCD(){
    std::cout << "ERRCD" <<std::endl;
    this->_r.f = (this->_r.d & 0x1) | (this->_r.f & 0xFE);
    this->_r.d = (this->_r.d >> 1) | ((this->_r.d & 0x1) << 7);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERRCE(){
    std::cout << "ERRCE" <<std::endl;
    this->_r.f = (this->_r.e & 0x1) | (this->_r.f & 0xFE);
    this->_r.e = (this->_r.e >> 1) | ((this->_r.e & 0x1) << 7);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERRCH(){
    std::cout << "ERRCH" <<std::endl;
    this->_r.f = (this->_r.h & 0x1) | (this->_r.f & 0xFE);
    this->_r.h = (this->_r.h >> 1) | ((this->_r.h & 0x1) << 7);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERRCL(){
    std::cout << "ERRCL" <<std::endl;
    this->_r.f = (this->_r.l & 0x1) | (this->_r.f & 0xFE);
    this->_r.l = (this->_r.l >> 1) | ((this->_r.l & 0x1) << 7);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERRCmHL(){
    std::cout << "ERRCmHL" <<std::endl;
    this->_r.f = (this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) | this->_r.f & 0xFE;
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) >> 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) << 7));
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERRCA(){
    std::cout << "ERRCA" <<std::endl;
    this->_r.f = (this->_r.a & 0x1) | (this->_r.f & 0xFE);
    this->_r.a = (this->_r.a >> 1) | ((this->_r.a & 0x1) << 7);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERLB(){
    std::cout << "ERLB" <<std::endl;
    this->_r.b = (this->_r.b << 1) | ((this->_r.b & 0x80) >> 7);
}

void Z80::ERLC(){
    std::cout << "ERLC" <<std::endl;
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
}

void Z80::ERLD(){
    std::cout << "ERLD" <<std::endl;
    this->_r.d = (this->_r.d << 1) | ((this->_r.d & 0x80) >> 7);
}

void Z80::ERLE(){
    std::cout << "ERLE" <<std::endl;
    this->_r.e = (this->_r.e << 1) | ((this->_r.e & 0x80) >> 7);
}

void Z80::ERLH(){
    std::cout << "ERLH" <<std::endl;
    this->_r.h = (this->_r.h << 1) | ((this->_r.h & 0x80) >> 7);
}

void Z80::ERLL(){
    std::cout << "ERLL" <<std::endl;
    this->_r.l = (this->_r.l << 1) | ((this->_r.l & 0x80) >> 7);
}

void Z80::ERLmHL(){
    std::cout << "ERLmHL" <<std::endl;
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) << 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7));
}

void Z80::ERLA(){
    std::cout << "ERLA" <<std::endl;
    this->_r.a = (this->_r.a << 1) | ((this->_r.a & 0x80) >> 7);
}

void Z80::ERRB(){
    std::cout << "ERRB" <<std::endl;
    this->_r.b = (this->_r.b >> 1) | ((this->_r.b & 0x1) << 7);
}

void Z80::ERRC(){
    std::cout << "ERRC" <<std::endl;
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
}

void Z80::ERRD(){
    std::cout << "ERRD" <<std::endl;
    this->_r.d = (this->_r.d >> 1) | ((this->_r.d & 0x1) << 7);
}

void Z80::ERRE(){
    std::cout << "ERRE" <<std::endl;
    this->_r.e = (this->_r.e >> 1) | ((this->_r.e & 0x1) << 7);
}

void Z80::ERRH(){
    std::cout << "ERRH" <<std::endl;
    this->_r.h = (this->_r.h >> 1) | ((this->_r.h & 0x1) << 7);
}

void Z80::ERRL(){
    std::cout << "ERRL" <<std::endl;
    this->_r.l = (this->_r.l >> 1) | ((this->_r.l & 0x1) << 7);
}

void Z80::ERRmHL(){
    std::cout << "ERRmHL" <<std::endl;
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) >> 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) << 7));
}

void Z80::ERRA(){
    std::cout << "ERRA" <<std::endl;
    this->_r.a = (this->_r.a >> 1) | ((this->_r.a & 0x1) << 7);
}

void Z80::ESLAB(){
    std::cout << "ESLAB" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.b & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.b <<= 1;
}

void Z80::ESLAC(){
    std::cout << "ESLAC" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.c & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.c <<= 1;
}

void Z80::ESLAD(){
    std::cout << "ESLAD" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.d & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.d <<= 1;
}

void Z80::ESLAE(){
    std::cout << "ESLAE" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.e & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.e <<= 1;
}

void Z80::ESLAH(){
    std::cout << "ESLAH" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.h & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.h <<= 1;
}

void Z80::ESLAL(){
    std::cout << "ESLAL" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.l & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.l <<= 1;
}

void Z80::ESLAmHL(){
    std::cout << "ESLAmHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESLAA(){
    std::cout << "ESLAA" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.a & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.a <<= 1;
}

void Z80::ESRAB(){
    std::cout << "ESRAB" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.b & 0x1) ? CARRY : 0);
    this->_r.b >>= 1;
}

void Z80::ESRAC(){
    std::cout << "ESRAC" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.c & 0x1) ? CARRY : 0);
    this->_r.c >>= 1;
}

void Z80::ESRAD(){
    std::cout << "ESRAD" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.d & 0x1) ? CARRY : 0);
    this->_r.d >>= 1;
}

void Z80::ESRAE(){
    std::cout << "ESRAE" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.e & 0x1) ? CARRY : 0);
    this->_r.e >>= 1;
}

void Z80::ESRAH(){
    std::cout << "ESRAH" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.h & 0x1) ? CARRY : 0);
    this->_r.h >>= 1;
}

void Z80::ESRAL(){
    std::cout << "ESRAL" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.l & 0x1) ? CARRY : 0);
    this->_r.l >>= 1;
}

void Z80::ESRAmHL(){
    std::cout << "ESRAmHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESRAA(){
    std::cout << "ESRAA" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.a & 0x1) ? CARRY : 0);
    this->_r.a >>= 1;
}

void Z80::ESWAPB(){
    std::cout << "ESWAPB" <<std::endl;
    this->_r.b = (((this->_r.b & 0xF0) >> 4) & 0x0F) | (((this->_r.b & 0x0F) << 4) & 0xF0);
}

void Z80::ESWAPC(){
    std::cout << "ESWAPC" <<std::endl;
    this->_r.c = (((this->_r.c & 0xF0) >> 4) & 0x0F) | (((this->_r.c & 0x0F) << 4) & 0xF0);
}

void Z80::ESWAPD(){
    std::cout << "ESWAPD" <<std::endl;
    this->_r.d = (((this->_r.d & 0xF0) >> 4) & 0x0F) | (((this->_r.d & 0x0F) << 4) & 0xF0);
}

void Z80::ESWAPE(){
    std::cout << "ESWAPE" <<std::endl;
    this->_r.e = (((this->_r.e & 0xF0) >> 4) & 0x0F) | (((this->_r.e & 0x0F) << 4) & 0xF0);
}

void Z80::ESWAPH(){
    std::cout << "ESWAPH" <<std::endl;
    this->_r.h = (((this->_r.h & 0xF0) >> 4) & 0x0F) | (((this->_r.h & 0x0F) << 4) & 0xF0);
}

void Z80::ESWAPL(){
    std::cout << "ESWAPL" <<std::endl;
    this->_r.l = (((this->_r.l & 0xF0) >> 4) & 0x0F) | (((this->_r.l & 0x0F) << 4) & 0xF0);
}

void Z80::ESWAPmHL(){
    std::cout << "ESWAPmHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESWAPA(){
    std::cout << "ESWAPA" <<std::endl;
    this->_r.a = (((this->_r.a & 0xF0) >> 4) & 0x0F) | (((this->_r.a & 0x0F) << 4) & 0xF0);
}

void Z80::ESRLB(){
    std::cout << "ESRLB" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.b & 0x1) ? CARRY : 0);
    this->_r.b = (this->_r.b >> 1) & 0x7F;
}

void Z80::ESRLC(){
    std::cout << "ESRLC" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.c & 0x1) ? CARRY : 0);
    this->_r.c = (this->_r.c >> 1) & 0x7F;
}

void Z80::ESRLD(){
    std::cout << "ESRLD" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.d & 0x1) ? CARRY : 0);
    this->_r.d = (this->_r.d >> 1) & 0x7F;
}

void Z80::ESRLE(){
    std::cout << "ESRLE" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.e & 0x1) ? CARRY : 0);
    this->_r.e = (this->_r.e >> 1) & 0x7F;
}

void Z80::ESRLH(){
    std::cout << "ESRLH" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.h & 0x1) ? CARRY : 0);
    this->_r.h = (this->_r.h >> 1) & 0x7F;
}

void Z80::ESRLL(){
    std::cout << "ESRLL" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.l & 0x1) ? CARRY : 0);
    this->_r.l = (this->_r.l >> 1) & 0x7F;
}

void Z80::ESRLmHL(){
    std::cout << "ESRLmHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESRLA(){
    std::cout << "ESRLA" <<std::endl;
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.a & 0x1) ? CARRY : 0);
    this->_r.a = (this->_r.a >> 1) & 0x7F;
}

void Z80::EBIT0B(){
    std::cout << "EBIT0B" <<std::endl;
    this->_r.f = (this->_r.b & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT0C(){
    std::cout << "EBIT0C" <<std::endl;
    this->_r.f = (this->_r.c & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT0D(){
    std::cout << "EBIT0D" <<std::endl;
    this->_r.f = (this->_r.d & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT0E(){
    std::cout << "EBIT0E" <<std::endl;
    this->_r.f = (this->_r.e & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT0H(){
    std::cout << "EBIT0H" <<std::endl;
    this->_r.f = (this->_r.h & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT0L(){
    std::cout << "EBIT0L" <<std::endl;
    this->_r.f = (this->_r.l & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT0mHL(){
    std::cout << "EBIT0mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EBIT0A(){
    std::cout << "EBIT0A" <<std::endl;
    this->_r.f = (this->_r.a & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT1B(){
    std::cout << "EBIT1B" <<std::endl;
    this->_r.f = (this->_r.b & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT1C(){
    std::cout << "EBIT1C" <<std::endl;
    this->_r.f = (this->_r.c & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT1D(){
    std::cout << "EBIT1D" <<std::endl;
    this->_r.f = (this->_r.d & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT1E(){
    std::cout << "EBIT1E" <<std::endl;
    this->_r.f = (this->_r.e & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT1H(){
    std::cout << "EBIT1H" <<std::endl;
    this->_r.f = (this->_r.h & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT1L(){
    std::cout << "EBIT1L" <<std::endl;
    this->_r.f = (this->_r.l & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT1mHL(){
    std::cout << "EBIT1mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EBIT1A(){
    std::cout << "EBIT1A" <<std::endl;
    this->_r.f = (this->_r.a & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT2B(){
    std::cout << "EBIT2B" <<std::endl;
    this->_r.f = (this->_r.b & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT2C(){
    std::cout << "EBIT2C" <<std::endl;
    this->_r.f = (this->_r.c & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT2D(){
    std::cout << "EBIT2D" <<std::endl;
    this->_r.f = (this->_r.d & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT2E(){
    std::cout << "EBIT2E" <<std::endl;
    this->_r.f = (this->_r.e & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT2H(){
    std::cout << "EBIT2H" <<std::endl;
    this->_r.f = (this->_r.h & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT2L(){
    std::cout << "EBIT2L" <<std::endl;
    this->_r.f = (this->_r.l & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT2mHL(){
    std::cout << "EBIT2mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EBIT2A(){
    std::cout << "EBIT2A" <<std::endl;
    this->_r.f = (this->_r.a & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT3B(){
    std::cout << "EBIT3B" <<std::endl;
    this->_r.f = (this->_r.b & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT3C(){
    std::cout << "EBIT3C" <<std::endl;
    this->_r.f = (this->_r.c & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT3D(){
    std::cout << "EBIT3D" <<std::endl;
    this->_r.f = (this->_r.d & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT3E(){
    std::cout << "EBIT3E" <<std::endl;
    this->_r.f = (this->_r.e & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT3H(){
    std::cout << "EBIT3H" <<std::endl;
    this->_r.f = (this->_r.h & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT3L(){
    std::cout << "EBIT3L" <<std::endl;
    this->_r.f = (this->_r.l & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT3mHL(){
    std::cout << "EBIT3mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EBIT3A(){
    std::cout << "EBIT3A" <<std::endl;
    this->_r.f = (this->_r.a & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT4B(){
    std::cout << "EBIT4B" <<std::endl;
    this->_r.f = (this->_r.b & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT4C(){
    std::cout << "EBIT4C" <<std::endl;
    this->_r.f = (this->_r.c & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT4D(){
    std::cout << "EBIT4D" <<std::endl;
    this->_r.f = (this->_r.d & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT4E(){
    std::cout << "EBIT4E" <<std::endl;
    this->_r.f = (this->_r.e & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT4H(){
    std::cout << "EBIT4H" <<std::endl;
    this->_r.f = (this->_r.h & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT4L(){
    std::cout << "EBIT4L" <<std::endl;
    this->_r.f = (this->_r.l & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT4mHL(){
    std::cout << "EBIT4mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EBIT4A(){
    std::cout << "EBIT4A" <<std::endl;
    this->_r.f = (this->_r.a & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT5B(){
    std::cout << "EBIT5B" <<std::endl;
    this->_r.f = (this->_r.b & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT5C(){
    std::cout << "EBIT5C" <<std::endl;
    this->_r.f = (this->_r.c & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT5D(){
    std::cout << "EBIT5D" <<std::endl;
    this->_r.f = (this->_r.d & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT5E(){
    std::cout << "EBIT5E" <<std::endl;
    this->_r.f = (this->_r.e & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT5H(){
    std::cout << "EBIT5H" <<std::endl;
    this->_r.f = (this->_r.h & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT5L(){
    std::cout << "EBIT5L" <<std::endl;
    this->_r.f = (this->_r.l & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT5mHL(){
    std::cout << "EBIT5mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EBIT5A(){
    std::cout << "EBIT5A" <<std::endl;
    this->_r.f = (this->_r.a & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT6B(){
    std::cout << "EBIT6B" <<std::endl;
    this->_r.f = (this->_r.b & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT6C(){
    std::cout << "EBIT6C" <<std::endl;
    this->_r.f = (this->_r.c & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT6D(){
    std::cout << "EBIT6D" <<std::endl;
    this->_r.f = (this->_r.d & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT6E(){
    std::cout << "EBIT6E" <<std::endl;
    this->_r.f = (this->_r.e & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT6H(){
    std::cout << "EBIT6H" <<std::endl;
    this->_r.f = (this->_r.h & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT6L(){
    std::cout << "EBIT6L" <<std::endl;
    this->_r.f = (this->_r.l & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT6mHL(){
    std::cout << "EBIT6mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EBIT6A(){
    std::cout << "EBIT6A" <<std::endl;
    this->_r.f = (this->_r.a & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT7B(){
    std::cout << "EBIT7B" <<std::endl;
    this->_r.f = (this->_r.b & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT7C(){
    std::cout << "EBIT7C" <<std::endl;
    this->_r.f = (this->_r.c & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT7D(){
    std::cout << "EBIT7D" <<std::endl;
    this->_r.f = (this->_r.d & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT7E(){
    std::cout << "EBIT7E" <<std::endl;
    this->_r.f = (this->_r.e & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT7H(){
    //std::cout << "EBIT7H" <<std::endl;
    this->_r.f = (this->_r.h & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT7L(){
    std::cout << "EBIT7L" <<std::endl;
    this->_r.f = (this->_r.l & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::EBIT7mHL(){
    std::cout << "EBIT7mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::EBIT7A(){
    std::cout << "EBIT7A" <<std::endl;
    this->_r.f = (this->_r.a & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
}

void Z80::ERES0B(){
    std::cout << "ERES0B" <<std::endl;
    this->_r.b &= ~(1<<0);
}

void Z80::ERES0C(){
    std::cout << "ERES0C" <<std::endl;
    this->_r.c &= ~(1<<0);
}

void Z80::ERES0D(){
    std::cout << "ERES0D" <<std::endl;
    this->_r.d &= ~(1<<0);
}

void Z80::ERES0E(){
    std::cout << "ERES0E" <<std::endl;
    this->_r.e &= ~(1<<0);
}

void Z80::ERES0H(){
    std::cout << "ERES0H" <<std::endl;
    this->_r.h &= ~(1<<0);
}

void Z80::ERES0L(){
    std::cout << "ERES0L" <<std::endl;
    this->_r.l &= ~(1<<0);
}

void Z80::ERES0mHL(){
    std::cout << "ERES0mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ERES0A(){
    std::cout << "ERES0A" <<std::endl;
    this->_r.a &= ~(1<<0);
}

void Z80::ERES1B(){
    std::cout << "ERES1B" <<std::endl;
    this->_r.b &= ~(1<<1);
}

void Z80::ERES1C(){
    std::cout << "ERES1C" <<std::endl;
    this->_r.c &= ~(1<<1);
}

void Z80::ERES1D(){
    std::cout << "ERES1D" <<std::endl;
    this->_r.d &= ~(1<<1);
}

void Z80::ERES1E(){
    std::cout << "ERES1E" <<std::endl;
    this->_r.e &= ~(1<<1);
}

void Z80::ERES1H(){
    std::cout << "ERES1H" <<std::endl;
    this->_r.h &= ~(1<<1);
}

void Z80::ERES1L(){
    std::cout << "ERES1L" <<std::endl;
    this->_r.l &= ~(1<<1);
}

void Z80::ERES1mHL(){
    std::cout << "ERES1mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ERES1A(){
    std::cout << "ERES1A" <<std::endl;
    this->_r.a &= ~(1<<1);
}

void Z80::ERES2B(){
    std::cout << "ERES2B" <<std::endl;
    this->_r.b &= ~(1<<2);
}

void Z80::ERES2C(){
    std::cout << "ERES2C" <<std::endl;
    this->_r.c &= ~(1<<2);
}

void Z80::ERES2D(){
    std::cout << "ERES2D" <<std::endl;
    this->_r.d &= ~(1<<2);
}

void Z80::ERES2E(){
    std::cout << "ERES2E" <<std::endl;
    this->_r.e &= ~(1<<2);
}

void Z80::ERES2H(){
    std::cout << "ERES2H" <<std::endl;
    this->_r.h &= ~(1<<2);
}

void Z80::ERES2L(){
    std::cout << "ERES2L" <<std::endl;
    this->_r.l &= ~(1<<2);
}

void Z80::ERES2mHL(){
    std::cout << "ERES2mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ERES2A(){
    std::cout << "ERES2A" <<std::endl;
    this->_r.a &= ~(1<<2);
}

void Z80::ERES3B(){
    std::cout << "ERES3B" <<std::endl;
    this->_r.b &= ~(1<<3);
}

void Z80::ERES3C(){
    std::cout << "ERES3C" <<std::endl;
    this->_r.c &= ~(1<<3);
}

void Z80::ERES3D(){
    std::cout << "ERES3D" <<std::endl;
    this->_r.d &= ~(1<<3);
}

void Z80::ERES3E(){
    std::cout << "ERES3E" <<std::endl;
    this->_r.e &= ~(1<<3);
}

void Z80::ERES3H(){
    std::cout << "ERES3H" <<std::endl;
    this->_r.h &= ~(1<<3);
}

void Z80::ERES3L(){
    std::cout << "ERES3L" <<std::endl;
    this->_r.l &= ~(1<<3);
}

void Z80::ERES3mHL(){
    std::cout << "ERES3mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ERES3A(){
    std::cout << "ERES3A" <<std::endl;
    this->_r.a &= ~(1<<3);
}

void Z80::ERES4B(){
    std::cout << "ERES4B" <<std::endl;
    this->_r.b &= ~(1<<4);
}

void Z80::ERES4C(){
    std::cout << "ERES4C" <<std::endl;
    this->_r.c &= ~(1<<4);
}

void Z80::ERES4D(){
    std::cout << "ERES4D" <<std::endl;
    this->_r.d &= ~(1<<4);
}

void Z80::ERES4E(){
    std::cout << "ERES4E" <<std::endl;
    this->_r.e &= ~(1<<4);
}

void Z80::ERES4H(){
    std::cout << "ERES4H" <<std::endl;
    this->_r.h &= ~(1<<4);
}

void Z80::ERES4L(){
    std::cout << "ERES4L" <<std::endl;
    this->_r.l &= ~(1<<4);
}

void Z80::ERES4mHL(){
    std::cout << "ERES4mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ERES4A(){
    std::cout << "ERES4A" <<std::endl;
    this->_r.a &= ~(1<<4);
}

void Z80::ERES5B(){
    std::cout << "ERES5B" <<std::endl;
    this->_r.b &= ~(1<<5);
}

void Z80::ERES5C(){
    std::cout << "ERES5C" <<std::endl;
    this->_r.c &= ~(1<<5);
}

void Z80::ERES5D(){
    std::cout << "ERES5D" <<std::endl;
    this->_r.d &= ~(1<<5);
}

void Z80::ERES5E(){
    std::cout << "ERES5E" <<std::endl;
    this->_r.e &= ~(1<<5);
}

void Z80::ERES5H(){
    std::cout << "ERES5H" <<std::endl;
    this->_r.h &= ~(1<<5);
}

void Z80::ERES5L(){
    std::cout << "ERES5L" <<std::endl;
    this->_r.l &= ~(1<<5);
}

void Z80::ERES5mHL(){
    std::cout << "ERES5mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ERES5A(){
    std::cout << "ERES5A" <<std::endl;
    this->_r.a &= ~(1<<5);
}

void Z80::ERES6B(){
    std::cout << "ERES6B" <<std::endl;
    this->_r.b &= ~(1<<6);
}

void Z80::ERES6C(){
    std::cout << "ERES6C" <<std::endl;
    this->_r.c &= ~(1<<6);
}

void Z80::ERES6D(){
    std::cout << "ERES6D" <<std::endl;
    this->_r.d &= ~(1<<6);
}

void Z80::ERES6E(){
    std::cout << "ERES6E" <<std::endl;
    this->_r.e &= ~(1<<6);
}

void Z80::ERES6H(){
    std::cout << "ERES6H" <<std::endl;
    this->_r.h &= ~(1<<6);
}

void Z80::ERES6L(){
    std::cout << "ERES6L" <<std::endl;
    this->_r.l &= ~(1<<6);
}

void Z80::ERES6mHL(){
    std::cout << "ERES6mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ERES6A(){
    std::cout << "ERES6A" <<std::endl;
    this->_r.a &= ~(1<<6);
}

void Z80::ERES7B(){
    std::cout << "ERES7B" <<std::endl;
    this->_r.b &= ~(1<<7);
}

void Z80::ERES7C(){
    std::cout << "ERES7C" <<std::endl;
    this->_r.c &= ~(1<<7);
}

void Z80::ERES7D(){
    std::cout << "ERES7D" <<std::endl;
    this->_r.d &= ~(1<<7);
}

void Z80::ERES7E(){
    std::cout << "ERES7E" <<std::endl;
    this->_r.e &= ~(1<<7);
}

void Z80::ERES7H(){
    std::cout << "ERES7H" <<std::endl;
    this->_r.h &= ~(1<<7);
}

void Z80::ERES7L(){
    std::cout << "ERES7L" <<std::endl;
    this->_r.l &= ~(1<<7);
}

void Z80::ERES7mHL(){
    std::cout << "ERES7mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ERES7A(){
    std::cout << "ERES7A" <<std::endl;
    this->_r.a &= ~(1<<7);
}

void Z80::ESET0B(){
    std::cout << "ESET0B" <<std::endl;
    this->_r.b |= (1<<0);
}

void Z80::ESET0C(){
    std::cout << "ESET0C" <<std::endl;
    this->_r.c |= (1<<0);
}

void Z80::ESET0D(){
    std::cout << "ESET0D" <<std::endl;
    this->_r.d |= (1<<0);
}

void Z80::ESET0E(){
    std::cout << "ESET0E" <<std::endl;
    this->_r.e |= (1<<0);
}

void Z80::ESET0H(){
    std::cout << "ESET0H" <<std::endl;
    this->_r.h |= (1<<0);
}

void Z80::ESET0L(){
    std::cout << "ESET0L" <<std::endl;
    this->_r.l |= (1<<0);
}

void Z80::ESET0mHL(){
    std::cout << "ESET0mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESET0A(){
    std::cout << "ESET0A" <<std::endl;
    this->_r.a |= (1<<0);
}

void Z80::ESET1B(){
    std::cout << "ESET1B" <<std::endl;
    this->_r.b |= (1<<1);
}

void Z80::ESET1C(){
    std::cout << "ESET1C" <<std::endl;
    this->_r.c |= (1<<1);
}

void Z80::ESET1D(){
    std::cout << "ESET1D" <<std::endl;
    this->_r.d |= (1<<1);
}

void Z80::ESET1E(){
    std::cout << "ESET1E" <<std::endl;
    this->_r.e |= (1<<1);
}

void Z80::ESET1H(){
    std::cout << "ESET1H" <<std::endl;
    this->_r.h |= (1<<1);
}

void Z80::ESET1L(){
    std::cout << "ESET1L" <<std::endl;
    this->_r.l |= (1<<1);
}

void Z80::ESET1mHL(){
    std::cout << "ESET1mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESET1A(){
    std::cout << "ESET1A" <<std::endl;
    this->_r.a |= (1<<1);
}

void Z80::ESET2B(){
    std::cout << "ESET2B" <<std::endl;
    this->_r.b |= (1<<2);
}

void Z80::ESET2C(){
    std::cout << "ESET2C" <<std::endl;
    this->_r.c |= (1<<2);
}

void Z80::ESET2D(){
    std::cout << "ESET2D" <<std::endl;
    this->_r.d |= (1<<2);
}

void Z80::ESET2E(){
    std::cout << "ESET2E" <<std::endl;
    this->_r.e |= (1<<2);
}

void Z80::ESET2H(){
    std::cout << "ESET2H" <<std::endl;
    this->_r.h |= (1<<2);
}

void Z80::ESET2L(){
    std::cout << "ESET2L" <<std::endl;
    this->_r.l |= (1<<2);
}

void Z80::ESET2mHL(){
    std::cout << "ESET2mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESET2A(){
    std::cout << "ESET2A" <<std::endl;
    this->_r.a |= (1<<2);
}

void Z80::ESET3B(){
    std::cout << "ESET3B" <<std::endl;
    this->_r.b |= (1<<3);
}

void Z80::ESET3C(){
    std::cout << "ESET3C" <<std::endl;
    this->_r.c |= (1<<3);
}

void Z80::ESET3D(){
    std::cout << "ESET3D" <<std::endl;
    this->_r.d |= (1<<3);
}

void Z80::ESET3E(){
    std::cout << "ESET3E" <<std::endl;
    this->_r.e |= (1<<3);
}

void Z80::ESET3H(){
    std::cout << "ESET3H" <<std::endl;
    this->_r.h |= (1<<3);
}

void Z80::ESET3L(){
    std::cout << "ESET3L" <<std::endl;
    this->_r.l |= (1<<3);
}

void Z80::ESET3mHL(){
    std::cout << "ESET3mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESET3A(){
    std::cout << "ESET3A" <<std::endl;
    this->_r.a |= (1<<3);
}

void Z80::ESET4B(){
    std::cout << "ESET4B" <<std::endl;
    this->_r.b |= (1<<4);
}

void Z80::ESET4C(){
    std::cout << "ESET4C" <<std::endl;
    this->_r.c |= (1<<4);
}

void Z80::ESET4D(){
    std::cout << "ESET4D" <<std::endl;
    this->_r.d |= (1<<4);
}

void Z80::ESET4E(){
    std::cout << "ESET4E" <<std::endl;
    this->_r.e |= (1<<4);
}

void Z80::ESET4H(){
    std::cout << "ESET4H" <<std::endl;
    this->_r.h |= (1<<4);
}

void Z80::ESET4L(){
    std::cout << "ESET4L" <<std::endl;
    this->_r.l |= (1<<4);
}

void Z80::ESET4mHL(){
    std::cout << "ESET4mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESET4A(){
    std::cout << "ESET4A" <<std::endl;
    this->_r.a |= (1<<4);
}

void Z80::ESET5B(){
    std::cout << "ESET5B" <<std::endl;
    this->_r.b |= (1<<5);
}

void Z80::ESET5C(){
    std::cout << "ESET5C" <<std::endl;
    this->_r.c |= (1<<5);
}

void Z80::ESET5D(){
    std::cout << "ESET5D" <<std::endl;
    this->_r.d |= (1<<5);
}

void Z80::ESET5E(){
    std::cout << "ESET5E" <<std::endl;
    this->_r.e |= (1<<5);
}

void Z80::ESET5H(){
    std::cout << "ESET5H" <<std::endl;
    this->_r.h |= (1<<5);
}

void Z80::ESET5L(){
    std::cout << "ESET5L" <<std::endl;
    this->_r.l |= (1<<5);
}

void Z80::ESET5mHL(){
    std::cout << "ESET5mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESET5A(){
    std::cout << "ESET5A" <<std::endl;
    this->_r.a |= (1<<5);
}

void Z80::ESET6B(){
    std::cout << "ESET6B" <<std::endl;
    this->_r.b |= (1<<6);
}

void Z80::ESET6C(){
    std::cout << "ESET6C" <<std::endl;
    this->_r.c |= (1<<6);
}

void Z80::ESET6D(){
    std::cout << "ESET6D" <<std::endl;
    this->_r.d |= (1<<6);
}

void Z80::ESET6E(){
    std::cout << "ESET6E" <<std::endl;
    this->_r.e |= (1<<6);
}

void Z80::ESET6H(){
    std::cout << "ESET6H" <<std::endl;
    this->_r.h |= (1<<6);
}

void Z80::ESET6L(){
    std::cout << "ESET6L" <<std::endl;
    this->_r.l |= (1<<6);
}

void Z80::ESET6mHL(){
    std::cout << "ESET6mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESET6A(){
    std::cout << "ESET6A" <<std::endl;
    this->_r.a |= (1<<6);
}

void Z80::ESET7B(){
    std::cout << "ESET7B" <<std::endl;
    this->_r.b |= (1<<7);
}

void Z80::ESET7C(){
    std::cout << "ESET7C" <<std::endl;
    this->_r.c |= (1<<7);
}

void Z80::ESET7D(){
    std::cout << "ESET7D" <<std::endl;
    this->_r.d |= (1<<7);
}

void Z80::ESET7E(){
    std::cout << "ESET7E" <<std::endl;
    this->_r.e |= (1<<7);
}

void Z80::ESET7H(){
    std::cout << "ESET7H" <<std::endl;
    this->_r.h |= (1<<7);
}

void Z80::ESET7L(){
    std::cout << "ESET7L" <<std::endl;
    this->_r.l |= (1<<7);
}

void Z80::ESET7mHL(){
    std::cout << "ESET7mHL" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::ESET7A(){
    std::cout << "ESET7A" <<std::endl;
    this->_r.a |= (1<<7);
}

#endif
