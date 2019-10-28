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
    std::cout << "JRNZn" <<std::endl;
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
    std::cout << "DECHL" <<std::endl;
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
    std::cout << "LDDmHLA" <<std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RET(){
    std::cout << "RET" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::JPZnn(){
    std::cout << "JPZnn" <<std::endl;
    this->_r.pc = (this->_r.f & ZERO) ? this->mmu.rw(this->_r.pc) : this->_r.pc;
    this->_r.pc += (this->_r.f & ZERO) ? 2 : 0;
}

void Z80::Extops(){
    std::cout << "Extops" <<std::endl;
    this->_r.pc += 1;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLZnn(){
    std::cout << "CALLZnn" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::CALLnn(){
    std::cout << "CALLnn" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::RETI(){
    std::cout << "RETI" <<std::endl;
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
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
    std::cout << "Uncovered Function" << std::endl;
}

void Z80::POPHL(){
    std::cout << "POPHL" <<std::endl;
    this->_r.l = this->mmu.rb(this->_r.sp);
    this->_r.h = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
}

void Z80::LDHmCA(){
    std::cout << "LDHmCA" <<std::endl;
    this->_r.h = this->mmu.rb(this->_r.c << 8 + this->_r.a);
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
    std::cout << "Uncovered Function" << std::endl;
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

#endif
