#ifndef _OPS_
#define _OPS_

#include "Z80.h"

#define CARRY (1<<4) //C
#define HALF_CARRY (1<<5) //H
#define ADD_SUB (1<<6) //N
#define ZERO (1<<7) //Z

void Z80::NOP(){
    this->_r.f &= 0xF0;
}

void Z80::LDBCnn(){
    this->_r.c = this->mmu.rb(this->_r.pc);
    this->_r.b = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDmBCA(){
    this->mmu.wb(this->_r.b << 8 | this->_r.c, this->_r.a);
    this->_r.f &= 0xF0;
}

void Z80::INCBC(){
    this->_r.c += 1;
    this->_r.b = this->_r.c == 0x00 ? this->_r.b + 1 : this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::INCB(){
    this->_r.f = (this->_r.b & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.b += 1;
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECB(){
    this->_r.f = (this->_r.b & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.b -= 1;
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDBn(){
    this->_r.b = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RLCA(){
    this->_r.f = (this->_r.a & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = this->_r.a << 1 | ((this->_r.a & 0x80) ? 1 : 0);
    this->_r.f &= ~(ZERO | ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::LDmnnSP(){
    this->mmu.ww(this->mmu.rb(this->_r.pc) | (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.sp);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::ADDHLBC(){
    uint16_t result = (this->_r.h << 8 | this->_r.l) + (this->_r.b << 8 | this->_r.c);
    bool old_carry = (this->_r.l + this->_r.c) & 0x100 ? 1 : 0; //Needed?
    this->_r.f = (this->_r.h + this->_r.b + (int) old_carry) & 0x100 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f = ((this->_r.h & 0xF) + (this->_r.b & 0xF) + (int) old_carry) & 0x10 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.h = (result & 0xFF00) >> 8;
    this->_r.l = result & 0xFF;
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::LDAmBC(){
    this->_r.a = this->mmu.rb(this->_r.b << 8 | this->_r.c);
    this->_r.f &= 0xF0;
}

void Z80::DECBC(){
    this->_r.c -= 1;
    this->_r.b = this->_r.c == 0xFF ? this->_r.b - 1 : this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::INCC(){
    this->_r.f = (this->_r.c & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.c += 1;
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECC(){
    this->_r.f = (this->_r.c & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.c -= 1;
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDCn(){
    this->_r.c = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RRCA(){
    this->_r.f = (this->_r.a & 0x01) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = this->_r.a >> 1 | ((this->_r.a & 0x01) ? 1 << 7 : 0);
    this->_r.f &= ~(ZERO | ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::STOP(){
#ifdef VERIF
    this->running = false;
#endif
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDDEnn(){
    this->_r.e = this->mmu.rb(this->_r.pc);
    this->_r.d = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDmDEA(){
    this->mmu.wb(this->_r.d << 8 | this->_r.e, this->_r.a);
    this->_r.f &= 0xF0;
}

void Z80::INCDE(){
    this->_r.e += 1;
    this->_r.d = this->_r.e == 0x00 ? this->_r.d + 1 : this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::INCD(){
    this->_r.f = (this->_r.d & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.d += 1;
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECD(){
    this->_r.f = (this->_r.d & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.d -= 1;
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDDn(){
    this->_r.d = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RLA(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.a & 0x80) ? this->_r.f | CARRY : this->_r.f & ~CARRY;
    this->_r.a = ((this->_r.a << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= ~(ZERO | ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::JRn(){
    this->_r.pc += (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::ADDHLDE(){
    uint16_t result = (this->_r.h << 8 | this->_r.l) + (this->_r.d << 8 | this->_r.e);
    bool old_carry = (this->_r.l + this->_r.e) & 0x100 ? 1 : 0; //Needed?
    this->_r.f = (this->_r.h + this->_r.d + (int) old_carry) & 0x100 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f = ((this->_r.h & 0xF) + (this->_r.d & 0xF) + (int) old_carry) & 0x10 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.h = (result & 0xFF00) >> 8;
    this->_r.l = result & 0xFF;
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::LDAmDE(){
    this->_r.a = this->mmu.rb(this->_r.d << 8 | this->_r.e);
    this->_r.f &= 0xF0;
}

void Z80::DECDE(){
    this->_r.e -= 1;
    this->_r.d = this->_r.e == 0xFF ? this->_r.d - 1 : this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::INCE(){
    this->_r.f = (this->_r.e & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.e += 1;
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECE(){
    this->_r.f = (this->_r.e & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.e -= 1;
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDEn(){
    this->_r.e = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RRA(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.a & 0x01) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = ((this->_r.a >> 1) | (int) orig_carry << 7) & 0xFF;
    this->_r.f &= ~(ZERO | ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::JRNZn(){
    this->_r.pc += this->_r.f & ZERO ? 0 : (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::LDHLnn(){
    this->_r.l = this->mmu.rb(this->_r.pc);
    this->_r.h = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDImHLA(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.a);
    this->INCHL();
    this->_r.f &= 0xF0;
}

void Z80::INCHL(){
    this->_r.l += 1;
    this->_r.h = this->_r.l == 0x00 ? this->_r.h + 1 : this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::INCH(){
    this->_r.f = (this->_r.h & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.h += 1;
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECH(){
    this->_r.f = (this->_r.h & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.h -= 1;
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDHn(){
    this->_r.h = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::DAA(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::JRZn(){
    this->_r.pc += this->_r.f & ZERO ? (int8_t) this->mmu.rb(this->_r.pc) : 0;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::ADDHLHL(){
    uint16_t result = (this->_r.h << 8 | this->_r.l) + (this->_r.h << 8 | this->_r.l);
    bool old_carry = (this->_r.l + this->_r.l) & 0x100 ? 1 : 0; //Needed?
    this->_r.f = (this->_r.h + this->_r.h + (int) old_carry) & 0x100 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f = ((this->_r.h & 0xF) + (this->_r.h & 0xF) + (int) old_carry) & 0x10 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.h = (result & 0xFF00) >> 8;
    this->_r.l = result & 0xFF;
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::LDIAmHL(){
    this->_r.a = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->INCHL();
    this->_r.f &= 0xF0;
}

void Z80::DECHL(){
    this->_r.l -= 1;
    this->_r.h = this->_r.l == 0xFF ? this->_r.h - 1 : this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::INCL(){
    this->_r.f = (this->_r.l & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.l += 1;
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECL(){
    this->_r.f = (this->_r.l & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.l -= 1;
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDLn(){
    this->_r.l = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::NOT(){
    this->_r.a = ~this->_r.a;
    this->_r.f |= ADD_SUB | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::JRNCn(){
    this->_r.pc += this->_r.f & CARRY ? 0 : (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::LDSPnn(){
    this->_r.sp = this->mmu.rw(this->_r.pc);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDDmHLA(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.a);
    this->DECHL();
    this->_r.f &= 0xF0;
}

void Z80::INCSP(){
    this->_r.sp += 1;
    this->_r.f &= 0xF0;
}

void Z80::INCmHL(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->mmu.rb(this->_r.h << 8 | this->_r.l) + 1);
    this->_r.f = this->mmu.rb(this->_r.h << 8 | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0x1F == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECmHL(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->mmu.rb(this->_r.h << 8 | this->_r.l) - 1);
    this->_r.f = this->mmu.rb(this->_r.h << 8 | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0x1F == 0x0F ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDmHLn(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->mmu.rb(this->_r.pc));
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::SCF(){
    this->_r.f = this->_r.f & ~ADD_SUB & ~HALF_CARRY | CARRY;
    this->_r.f &= 0xF0;
}

void Z80::JRCn(){
    this->_r.pc += this->_r.f & CARRY ? (int8_t) this->mmu.rb(this->_r.pc) : 0;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::ADDHLSP(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDDAmHL(){
    this->_r.a = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->DECHL();
    this->_r.f &= 0xF0;
}

void Z80::DECSP(){
    this->_r.sp -= 1;
    this->_r.f &= 0xF0;
}

void Z80::INCA(){
    this->_r.f = (this->_r.a & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.a += 1;
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECA(){
    this->_r.f = (this->_r.a & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.a -= 1;
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDAn(){
    this->_r.a = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::CCF(){
    this->_r.f = (this->_r.f & CARRY) ? this->_r.f & ~(CARRY) : this->_r.f | CARRY;
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::LDBB(){
    this->_r.b = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDBC(){
    this->_r.b = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDBD(){
    this->_r.b = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDBE(){
    this->_r.b = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDBH(){
    this->_r.b = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDBL(){
    this->_r.b = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDBmHL(){
    this->_r.b = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDBA(){
    this->_r.b = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDCB(){
    this->_r.c = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDCC(){
    this->_r.c = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDCD(){
    this->_r.c = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDCE(){
    this->_r.c = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDCH(){
    this->_r.c = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDCL(){
    this->_r.c = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDCmHL(){
    this->_r.c = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDCA(){
    this->_r.c = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDDB(){
    this->_r.d = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDDC(){
    this->_r.d = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDDD(){
    this->_r.d = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDDE(){
    this->_r.d = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDDH(){
    this->_r.d = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDDL(){
    this->_r.d = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDDmHL(){
    this->_r.d = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDDA(){
    this->_r.d = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDEB(){
    this->_r.e = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDEC(){
    this->_r.e = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDED(){
    this->_r.e = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDEE(){
    this->_r.e = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDEH(){
    this->_r.e = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDEL(){
    this->_r.e = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDEmHL(){
    this->_r.e = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDEA(){
    this->_r.e = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDHB(){
    this->_r.h = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDHC(){
    this->_r.h = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDHD(){
    this->_r.h = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDHE(){
    this->_r.h = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDHH(){
    this->_r.h = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDHL(){
    this->_r.h = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDHmHL(){
    this->_r.h = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDHA(){
    this->_r.h = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDLB(){
    this->_r.l = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDLC(){
    this->_r.l = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDLD(){
    this->_r.l = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDLE(){
    this->_r.l = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDLH(){
    this->_r.l = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDLL(){
    this->_r.l = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDLmHL(){
    this->_r.l = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDLA(){
    this->_r.l = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDmHLB(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.b);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLC(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.c);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLD(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.d);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLE(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.e);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLH(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.h);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLL(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::HALT(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDmHLA(){
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.a);
    this->_r.f &= 0xF0;
}

void Z80::LDAB(){
    this->_r.a = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDAC(){
    this->_r.a = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDAD(){
    this->_r.a = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDAE(){
    this->_r.a = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDAH(){
    this->_r.a = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDAL(){
    this->_r.a = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDAmHL(){
    this->_r.a = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDAA(){
    this->_r.a = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::ADDAB(){
    this->_r.f = this->_r.a + this->_r.b > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.b & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.b;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAC(){
    this->_r.f = this->_r.a + this->_r.c > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.c & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.c;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAD(){
    this->_r.f = this->_r.a + this->_r.d > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.d & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.d;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAE(){
    this->_r.f = this->_r.a + this->_r.e > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.e & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.e;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAH(){
    this->_r.f = this->_r.a + this->_r.h > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.h & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.h;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAL(){
    this->_r.f = this->_r.a + this->_r.l > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.l & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.l;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAmHL(){
    this->_r.f = this->_r.a + this->mmu.rb(this->_r.h << 8 | this->_r.l) > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAA(){
    this->_r.f = this->_r.a + this->_r.a > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.a & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.a;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADCAB(){
    bool temp_carry = (this->_r.a + this->_r.b + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.b & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.b + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAC(){
    bool temp_carry = (this->_r.a + this->_r.c + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.c & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.c + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAD(){
    bool temp_carry = (this->_r.a + this->_r.d + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.d & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.d + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAE(){
    bool temp_carry = (this->_r.a + this->_r.e + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.e & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.e + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAH(){
    bool temp_carry = (this->_r.a + this->_r.h + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.h & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.h + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAL(){
    bool temp_carry = (this->_r.a + this->_r.l + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.l & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.l + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAmHL(){
    bool temp_carry = (this->_r.a + this->mmu.rb(this->_r.h << 8 | this->_r.l) + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->mmu.rb(this->_r.h << 8 | this->_r.l) + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAA(){
    bool temp_carry = (this->_r.a + this->_r.a + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.a & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.a + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::SUBAB(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.b & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.b) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.b;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAC(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.c & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.c) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.c;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAD(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.d & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.d) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.d;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAE(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.e & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.e) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.e;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAH(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.h & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.h) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.h;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAL(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.l & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.l) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.l;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAmHL(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->mmu.rb(this->_r.h << 8 | this->_r.l)) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAA(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.a & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.a) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.a;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SBCAB(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAC(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAD(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAE(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAH(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAL(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAmHL(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAA(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::ANDB(){
    this->_r.a &= this->_r.b;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDC(){
    this->_r.a &= this->_r.c;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDD(){
    this->_r.a &= this->_r.d;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDE(){
    this->_r.a &= this->_r.e;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDH(){
    this->_r.a &= this->_r.h;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDL(){
    this->_r.a &= this->_r.l;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDmHL(){
    this->_r.a &= this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDA(){
    this->_r.a &= this->_r.a;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::XORB(){
    this->_r.a ^= this->_r.b;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORC(){
    this->_r.a ^= this->_r.c;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORD(){
    this->_r.a ^= this->_r.d;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORE(){
    this->_r.a ^= this->_r.e;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORH(){
    this->_r.a ^= this->_r.h;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORL(){
    this->_r.a ^= this->_r.l;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORmHL(){
    this->_r.a ^= this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORA(){
    this->_r.a ^= this->_r.a;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORB(){
    this->_r.a |= this->_r.b;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORC(){
    this->_r.a |= this->_r.c;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORD(){
    this->_r.a |= this->_r.d;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORE(){
    this->_r.a |= this->_r.e;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORH(){
    this->_r.a |= this->_r.h;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORL(){
    this->_r.a |= this->_r.l;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORmHL(){
    this->_r.a |= this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORA(){
    this->_r.a |= this->_r.a;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::CPB(){
    uint8_t val = this->_r.a - this->_r.b;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.b & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPC(){
    uint8_t val = this->_r.a - this->_r.c;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.c & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPD(){
    uint8_t val = this->_r.a - this->_r.d;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.d & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPE(){
    uint8_t val = this->_r.a - this->_r.e;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.e & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPH(){
    uint8_t val = this->_r.a - this->_r.h;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.h & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPL(){
    uint8_t val = this->_r.a - this->_r.l;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.l & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPmHL(){
    uint8_t val = this->_r.a - this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPA(){
    uint8_t val = this->_r.a - this->_r.a;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.a & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::RETNZ(){
    if(this->_r.f & ZERO == 0){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    }
    this->_r.f &= 0xF0;
}

void Z80::POPBC(){
    this->_r.c = this->mmu.rb(this->_r.sp);
    this->_r.b = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::JPNZnn(){
    this->_r.pc = (this->_r.f & ZERO) ? this->_r.pc : this->mmu.rw(this->_r.pc);
    this->_r.pc += (this->_r.f & ZERO) ? 0 : 2;
    this->_r.f &= 0xF0;
}

void Z80::JPnn(){
    this->_r.pc = this->mmu.rw(this->_r.pc);
    this->_r.f &= 0xF0;
}

void Z80::CALLNZnn(){
    if(this->_r.f & ZERO == 0){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
    this->_r.f &= 0xF0;
}

void Z80::PUSHBC(){
    this->mmu.wb(this->_r.sp - 1, this->_r.b);
    this->mmu.wb(this->_r.sp - 2, this->_r.c);
    this->_r.sp -= 2;
    this->_r.f &= 0xF0;
}

void Z80::ADDAn(){
    this->_r.f = this->_r.a + this->mmu.rb(this->_r.pc) > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->mmu.rb(this->_r.pc) & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->mmu.rb(this->_r.pc);
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST0(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::RETZ(){
    if(this->_r.f & ZERO == 1){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    }
    this->_r.f &= 0xF0;
}

void Z80::RET(){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::JPZnn(){
    this->_r.pc = (this->_r.f & ZERO) ? this->mmu.rw(this->_r.pc) : this->_r.pc;
    this->_r.pc += (this->_r.f & ZERO) ? 2 : 0;
    this->_r.f &= 0xF0;
}

void Z80::Extops(){
    updateTiming(true);
    (this->*ext_ops[mmu.rb(this->_r.pc++)].op_function)();
    gpu.step(this->_r.t);
    this->_r.f &= 0xF0;
}

void Z80::CALLZnn(){
    if(this->_r.f & ZERO == 1){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
    this->_r.f &= 0xF0;
}

void Z80::CALLnn(){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    this->_r.f &= 0xF0;
}

void Z80::ADCAn(){
    bool temp_carry = (this->_r.a + this->mmu.rb(this->_r.pc) + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->mmu.rb(this->_r.pc) & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->mmu.rb(this->_r.pc) + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST8(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::RETNC(){
    if(this->_r.f & CARRY == 0){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    }
    this->_r.f &= 0xF0;
}

void Z80::POPDE(){
    this->_r.e = this->mmu.rb(this->_r.sp);
    this->_r.d = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::JPNCnn(){
    this->_r.pc = (this->_r.f & CARRY) ? this->_r.pc : this->mmu.rw(this->_r.pc);
    this->_r.pc += (this->_r.f & CARRY) ? 0 : 2;
    this->_r.f &= 0xF0;
}

void Z80::XX1(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::CALLNCnn(){
    if(this->_r.f & CARRY == 0){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
    this->_r.f &= 0xF0;
}

void Z80::PUSHDE(){
    this->mmu.wb(this->_r.sp - 1, this->_r.d);
    this->mmu.wb(this->_r.sp - 2, this->_r.e);
    this->_r.sp -= 2;
    this->_r.f &= 0xF0;
}

void Z80::SUBAn(){
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->mmu.rb(this->_r.pc) & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->mmu.rb(this->_r.pc)) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->mmu.rb(this->_r.pc);
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST10(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::RETC(){
    if(this->_r.f & CARRY == 1){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    }
    this->_r.f &= 0xF0;
}

void Z80::RETI(){
    this->_r.f &= 0xF0;
}

void Z80::JPCnn(){
    this->_r.pc = (this->_r.f & CARRY) ? this->mmu.rw(this->_r.pc) : this->_r.pc;
    this->_r.pc += (this->_r.f & CARRY) ? 2 : 0;
    this->_r.f &= 0xF0;
}

void Z80::XX2(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::CALLCnn(){
    if(this->_r.f & CARRY == 1){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
    this->_r.f &= 0xF0;
}

void Z80::XX3(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAn(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::RST18(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDHmnA(){
    this->mmu.wb(0xFF00 | this->mmu.rb(this->_r.pc), this->_r.a);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::POPHL(){
    this->_r.l = this->mmu.rb(this->_r.sp);
    this->_r.h = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDHmCA(){
    this->mmu.wb(0xFF00 | this->_r.c, this->_r.a);
    this->_r.f &= 0xF0;
}

void Z80::XX4(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XX5(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::PUSHHL(){
    this->mmu.wb(this->_r.sp - 1, this->_r.h);
    this->mmu.wb(this->_r.sp - 2, this->_r.l);
    this->_r.sp -= 2;
    this->_r.f &= 0xF0;
}

void Z80::ANDn(){
    this->_r.a &= this->mmu.rb(this->_r.pc);
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST20(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::ADDSPd(){
    //Depends on sign
    //this->_r.f = ((this->_r.sp & 0xF) + (this->mmu.rb(this->_r.pc) & 0xF) & 0x10 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY));
    //this->_r.f = ((this->_r.sp & 0xFF) + (this->mmu.rb(this->_r.pc) & 0xFF) & 0x100 ? this->_r.f | CARRY : this->_r.f & ~(CARRY));
    this->_r.sp += this->mmu.rb(this->_r.pc) > 0x7F ? ((int8_t)~this->mmu.rb(this->_r.pc) + 1) & 0xFF : this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= ~(ZERO | ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::JPmHL(){
    this->_r.pc = this->mmu.rw(this->_r.h << 8 | this->_r.l);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDmnnA(){
    this->mmu.wb(this->mmu.rb(this->_r.pc) | (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.a);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::XX6(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XX7(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XX8(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XORn(){
    this->_r.a ^= this->mmu.rb(this->_r.pc);
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST28(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDHAmn(){
    this->_r.a = this->mmu.rb(0xFF00 | this->mmu.rb(this->_r.pc));
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::POPAF(){
    this->_r.f = this->mmu.rb(this->_r.sp);
    this->_r.a = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::XX9(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::DI(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XXA(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::PUSHAF(){
    this->mmu.wb(this->_r.sp - 1, this->_r.a);
    this->mmu.wb(this->_r.sp - 2, this->_r.f);
    this->_r.sp -= 2;
    this->_r.f &= 0xF0;
}

void Z80::ORn(){
    this->_r.a |= this->mmu.rb(this->_r.pc);
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST30(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDHLSPd(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDSPHL(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDAmnn(){
    this->_r.a = this->mmu.rb(this->mmu.rb(this->_r.pc++) | this->mmu.rb(this->_r.pc++) << 8);
    this->_r.f &= 0xF0;
}

void Z80::EI(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XXB(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XXC(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::CPn(){
    uint8_t val = this->_r.a - this->mmu.rb(this->_r.pc);
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->mmu.rb(this->_r.pc) & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST38(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}


void Z80::ERLCB(){
    this->_r.f = ((this->_r.b & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.b = (this->_r.b << 1) | ((this->_r.b & 0x80) >> 7);
    this->_r.f &= 0xF0;
}

void Z80::ERLCC(){
    this->_r.f = ((this->_r.c & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
    this->_r.f &= 0xF0;
}

void Z80::ERLCD(){
    this->_r.f = ((this->_r.d & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.d = (this->_r.d << 1) | ((this->_r.d & 0x80) >> 7);
    this->_r.f &= 0xF0;
}

void Z80::ERLCE(){
    this->_r.f = ((this->_r.e & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.e = (this->_r.e << 1) | ((this->_r.e & 0x80) >> 7);
    this->_r.f &= 0xF0;
}

void Z80::ERLCH(){
    this->_r.f = ((this->_r.h & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.h = (this->_r.h << 1) | ((this->_r.h & 0x80) >> 7);
    this->_r.f &= 0xF0;
}

void Z80::ERLCL(){
    this->_r.f = ((this->_r.l & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.l = (this->_r.l << 1) | ((this->_r.l & 0x80) >> 7);
    this->_r.f &= 0xF0;
}

void Z80::ERLCmHL(){
    this->_r.f = ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7) | this->_r.f & 0xFE;
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) << 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7));
    this->_r.f &= 0xF0;
}

void Z80::ERLCA(){
    this->_r.f = ((this->_r.a & 0x80) >> 7) | (this->_r.f & 0xFE);
    this->_r.a = (this->_r.a << 1) | ((this->_r.a & 0x80) >> 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRCB(){
    this->_r.f = (this->_r.b & 0x1) | (this->_r.f & 0xFE);
    this->_r.b = (this->_r.b >> 1) | ((this->_r.b & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRCC(){
    this->_r.f = (this->_r.c & 0x1) | (this->_r.f & 0xFE);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRCD(){
    this->_r.f = (this->_r.d & 0x1) | (this->_r.f & 0xFE);
    this->_r.d = (this->_r.d >> 1) | ((this->_r.d & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRCE(){
    this->_r.f = (this->_r.e & 0x1) | (this->_r.f & 0xFE);
    this->_r.e = (this->_r.e >> 1) | ((this->_r.e & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRCH(){
    this->_r.f = (this->_r.h & 0x1) | (this->_r.f & 0xFE);
    this->_r.h = (this->_r.h >> 1) | ((this->_r.h & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRCL(){
    this->_r.f = (this->_r.l & 0x1) | (this->_r.f & 0xFE);
    this->_r.l = (this->_r.l >> 1) | ((this->_r.l & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRCmHL(){
    this->_r.f = (this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) | this->_r.f & 0xFE;
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) >> 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) << 7));
    this->_r.f &= 0xF0;
}

void Z80::ERRCA(){
    this->_r.f = (this->_r.a & 0x1) | (this->_r.f & 0xFE);
    this->_r.a = (this->_r.a >> 1) | ((this->_r.a & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERLB(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f &= (this->_r.b & 0x80) ? 0xFF : ~CARRY; //Clear Carry
    this->_r.f |= (this->_r.b & 0x80) ? CARRY : 0x00;
    this->_r.b = ((this->_r.b << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= 0xF0;
}

void Z80::ERLC(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f &= (this->_r.c & 0x80) ? 0xFF : ~CARRY; //Clear Carry
    this->_r.f |= (this->_r.c & 0x80) ? CARRY : 0x00;
    this->_r.c = ((this->_r.c << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= 0xF0;
}

void Z80::ERLD(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f &= (this->_r.d & 0x80) ? 0xFF : ~CARRY; //Clear Carry
    this->_r.f |= (this->_r.d & 0x80) ? CARRY : 0x00;
    this->_r.d = ((this->_r.d << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= 0xF0;
}

void Z80::ERLE(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f &= (this->_r.e & 0x80) ? 0xFF : ~CARRY; //Clear Carry
    this->_r.f |= (this->_r.e & 0x80) ? CARRY : 0x00;
    this->_r.e = ((this->_r.e << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= 0xF0;
}

void Z80::ERLH(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f &= (this->_r.h & 0x80) ? 0xFF : ~CARRY; //Clear Carry
    this->_r.f |= (this->_r.h & 0x80) ? CARRY : 0x00;
    this->_r.h = ((this->_r.h << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= 0xF0;
}

void Z80::ERLL(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f &= (this->_r.l & 0x80) ? 0xFF : ~CARRY; //Clear Carry
    this->_r.f |= (this->_r.l & 0x80) ? CARRY : 0x00;
    this->_r.l = ((this->_r.l << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= 0xF0;
}

void Z80::ERLmHL(){
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) << 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7));
    this->_r.f &= 0xF0;
}

void Z80::ERLA(){
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f &= (this->_r.a & 0x80) ? 0xFF : ~CARRY; //Clear Carry
    this->_r.f |= (this->_r.a & 0x80) ? CARRY : 0x00;
    this->_r.a = ((this->_r.a << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= 0xF0;
}

void Z80::ERRB(){
    this->_r.b = (this->_r.b >> 1) | ((this->_r.b & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRC(){
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRD(){
    this->_r.d = (this->_r.d >> 1) | ((this->_r.d & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRE(){
    this->_r.e = (this->_r.e >> 1) | ((this->_r.e & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRH(){
    this->_r.h = (this->_r.h >> 1) | ((this->_r.h & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRL(){
    this->_r.l = (this->_r.l >> 1) | ((this->_r.l & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ERRmHL(){
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) >> 1 | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) << 7));
    this->_r.f &= 0xF0;
}

void Z80::ERRA(){
    this->_r.a = (this->_r.a >> 1) | ((this->_r.a & 0x1) << 7);
    this->_r.f &= 0xF0;
}

void Z80::ESLAB(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.b & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.b <<= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESLAC(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.c & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.c <<= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESLAD(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.d & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.d <<= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESLAE(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.e & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.e <<= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESLAH(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.h & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.h <<= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESLAL(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.l & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.l <<= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESLAmHL(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::ESLAA(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.a & 0x80) >> 7 ? CARRY : 0x0);
    this->_r.a <<= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESRAB(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.b & 0x1) ? CARRY : 0);
    this->_r.b >>= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESRAC(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.c & 0x1) ? CARRY : 0);
    this->_r.c >>= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESRAD(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.d & 0x1) ? CARRY : 0);
    this->_r.d >>= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESRAE(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.e & 0x1) ? CARRY : 0);
    this->_r.e >>= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESRAH(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.h & 0x1) ? CARRY : 0);
    this->_r.h >>= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESRAL(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.l & 0x1) ? CARRY : 0);
    this->_r.l >>= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESRAmHL(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::ESRAA(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.a & 0x1) ? CARRY : 0);
    this->_r.a >>= 1;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPB(){
    this->_r.b = (((this->_r.b & 0xF0) >> 4) & 0x0F) | (((this->_r.b & 0x0F) << 4) & 0xF0);
    this->_r.f &= 0xF0;
}

void Z80::ESWAPC(){
    this->_r.c = (((this->_r.c & 0xF0) >> 4) & 0x0F) | (((this->_r.c & 0x0F) << 4) & 0xF0);
    this->_r.f &= 0xF0;
}

void Z80::ESWAPD(){
    this->_r.d = (((this->_r.d & 0xF0) >> 4) & 0x0F) | (((this->_r.d & 0x0F) << 4) & 0xF0);
    this->_r.f &= 0xF0;
}

void Z80::ESWAPE(){
    this->_r.e = (((this->_r.e & 0xF0) >> 4) & 0x0F) | (((this->_r.e & 0x0F) << 4) & 0xF0);
    this->_r.f &= 0xF0;
}

void Z80::ESWAPH(){
    this->_r.h = (((this->_r.h & 0xF0) >> 4) & 0x0F) | (((this->_r.h & 0x0F) << 4) & 0xF0);
    this->_r.f &= 0xF0;
}

void Z80::ESWAPL(){
    this->_r.l = (((this->_r.l & 0xF0) >> 4) & 0x0F) | (((this->_r.l & 0x0F) << 4) & 0xF0);
    this->_r.f &= 0xF0;
}

void Z80::ESWAPmHL(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPA(){
    this->_r.a = (((this->_r.a & 0xF0) >> 4) & 0x0F) | (((this->_r.a & 0x0F) << 4) & 0xF0);
    this->_r.f &= 0xF0;
}

void Z80::ESRLB(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.b & 0x1) ? CARRY : 0);
    this->_r.b = (this->_r.b >> 1) & 0x7F;
    this->_r.f &= 0xF0;
}

void Z80::ESRLC(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.c & 0x1) ? CARRY : 0);
    this->_r.c = (this->_r.c >> 1) & 0x7F;
    this->_r.f &= 0xF0;
}

void Z80::ESRLD(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.d & 0x1) ? CARRY : 0);
    this->_r.d = (this->_r.d >> 1) & 0x7F;
    this->_r.f &= 0xF0;
}

void Z80::ESRLE(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.e & 0x1) ? CARRY : 0);
    this->_r.e = (this->_r.e >> 1) & 0x7F;
    this->_r.f &= 0xF0;
}

void Z80::ESRLH(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.h & 0x1) ? CARRY : 0);
    this->_r.h = (this->_r.h >> 1) & 0x7F;
    this->_r.f &= 0xF0;
}

void Z80::ESRLL(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.l & 0x1) ? CARRY : 0);
    this->_r.l = (this->_r.l >> 1) & 0x7F;
    this->_r.f &= 0xF0;
}

void Z80::ESRLmHL(){
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::ESRLA(){
    this->_r.f = this->_r.f & ~(CARRY) | ((this->_r.a & 0x1) ? CARRY : 0);
    this->_r.a = (this->_r.a >> 1) & 0x7F;
    this->_r.f &= 0xF0;
}

void Z80::EBIT0B(){
    this->_r.f = (this->_r.b & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT0C(){
    this->_r.f = (this->_r.c & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT0D(){
    this->_r.f = (this->_r.d & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT0E(){
    this->_r.f = (this->_r.e & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT0H(){
    this->_r.f = (this->_r.h & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT0L(){
    this->_r.f = (this->_r.l & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT0mHL(){
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT0A(){
    this->_r.f = (this->_r.a & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT1B(){
    this->_r.f = (this->_r.b & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT1C(){
    this->_r.f = (this->_r.c & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT1D(){
    this->_r.f = (this->_r.d & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT1E(){
    this->_r.f = (this->_r.e & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT1H(){
    this->_r.f = (this->_r.h & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT1L(){
    this->_r.f = (this->_r.l & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT1mHL(){
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT1A(){
    this->_r.f = (this->_r.a & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT2B(){
    this->_r.f = (this->_r.b & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT2C(){
    this->_r.f = (this->_r.c & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT2D(){
    this->_r.f = (this->_r.d & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT2E(){
    this->_r.f = (this->_r.e & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT2H(){
    this->_r.f = (this->_r.h & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT2L(){
    this->_r.f = (this->_r.l & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT2mHL(){
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT2A(){
    this->_r.f = (this->_r.a & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT3B(){
    this->_r.f = (this->_r.b & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT3C(){
    this->_r.f = (this->_r.c & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT3D(){
    this->_r.f = (this->_r.d & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT3E(){
    this->_r.f = (this->_r.e & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT3H(){
    this->_r.f = (this->_r.h & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT3L(){
    this->_r.f = (this->_r.l & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT3mHL(){
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT3A(){
    this->_r.f = (this->_r.a & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT4B(){
    this->_r.f = (this->_r.b & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT4C(){
    this->_r.f = (this->_r.c & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT4D(){
    this->_r.f = (this->_r.d & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT4E(){
    this->_r.f = (this->_r.e & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT4H(){
    this->_r.f = (this->_r.h & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT4L(){
    this->_r.f = (this->_r.l & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT4mHL(){
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT4A(){
    this->_r.f = (this->_r.a & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT5B(){
    this->_r.f = (this->_r.b & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT5C(){
    this->_r.f = (this->_r.c & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT5D(){
    this->_r.f = (this->_r.d & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT5E(){
    this->_r.f = (this->_r.e & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT5H(){
    this->_r.f = (this->_r.h & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT5L(){
    this->_r.f = (this->_r.l & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT5mHL(){
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT5A(){
    this->_r.f = (this->_r.a & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT6B(){
    this->_r.f = (this->_r.b & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT6C(){
    this->_r.f = (this->_r.c & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT6D(){
    this->_r.f = (this->_r.d & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT6E(){
    this->_r.f = (this->_r.e & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT6H(){
    this->_r.f = (this->_r.h & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT6L(){
    this->_r.f = (this->_r.l & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT6mHL(){
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT6A(){
    this->_r.f = (this->_r.a & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT7B(){
    this->_r.f = (this->_r.b & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT7C(){
    this->_r.f = (this->_r.c & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT7D(){
    this->_r.f = (this->_r.d & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT7E(){
    this->_r.f = (this->_r.e & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT7H(){
    this->_r.f = (this->_r.h & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT7L(){
    this->_r.f = (this->_r.l & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT7mHL(){
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::EBIT7A(){
    this->_r.f = (this->_r.a & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ERES0B(){
    this->_r.b &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0C(){
    this->_r.c &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0D(){
    this->_r.d &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0E(){
    this->_r.e &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0H(){
    this->_r.h &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0L(){
    this->_r.l &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<0)));
    this->_r.f &= 0xF0;
}

void Z80::ERES0A(){
    this->_r.a &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES1B(){
    this->_r.b &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1C(){
    this->_r.c &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1D(){
    this->_r.d &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1E(){
    this->_r.e &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1H(){
    this->_r.h &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1L(){
    this->_r.l &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<1)));
    this->_r.f &= 0xF0;
}

void Z80::ERES1A(){
    this->_r.a &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES2B(){
    this->_r.b &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2C(){
    this->_r.c &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2D(){
    this->_r.d &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2E(){
    this->_r.e &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2H(){
    this->_r.h &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2L(){
    this->_r.l &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<2)));
    this->_r.f &= 0xF0;
}

void Z80::ERES2A(){
    this->_r.a &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES3B(){
    this->_r.b &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3C(){
    this->_r.c &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3D(){
    this->_r.d &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3E(){
    this->_r.e &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3H(){
    this->_r.h &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3L(){
    this->_r.l &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<3)));
    this->_r.f &= 0xF0;
}

void Z80::ERES3A(){
    this->_r.a &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES4B(){
    this->_r.b &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4C(){
    this->_r.c &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4D(){
    this->_r.d &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4E(){
    this->_r.e &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4H(){
    this->_r.h &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4L(){
    this->_r.l &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<4)));
    this->_r.f &= 0xF0;
}

void Z80::ERES4A(){
    this->_r.a &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES5B(){
    this->_r.b &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5C(){
    this->_r.c &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5D(){
    this->_r.d &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5E(){
    this->_r.e &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5H(){
    this->_r.h &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5L(){
    this->_r.l &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<5)));
    this->_r.f &= 0xF0;
}

void Z80::ERES5A(){
    this->_r.a &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES6B(){
    this->_r.b &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6C(){
    this->_r.c &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6D(){
    this->_r.d &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6E(){
    this->_r.e &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6H(){
    this->_r.h &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6L(){
    this->_r.l &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<6)));
    this->_r.f &= 0xF0;
}

void Z80::ERES6A(){
    this->_r.a &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES7B(){
    this->_r.b &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7C(){
    this->_r.c &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7D(){
    this->_r.d &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7E(){
    this->_r.e &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7H(){
    this->_r.h &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7L(){
    this->_r.l &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<7)));
    this->_r.f &= 0xF0;
}

void Z80::ERES7A(){
    this->_r.a &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET0B(){
    this->_r.b |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0C(){
    this->_r.c |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0D(){
    this->_r.d |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0E(){
    this->_r.e |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0H(){
    this->_r.h |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0L(){
    this->_r.l |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<0)));
    this->_r.f &= 0xF0;
}

void Z80::ESET0A(){
    this->_r.a |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET1B(){
    this->_r.b |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1C(){
    this->_r.c |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1D(){
    this->_r.d |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1E(){
    this->_r.e |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1H(){
    this->_r.h |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1L(){
    this->_r.l |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<1)));
    this->_r.f &= 0xF0;
}

void Z80::ESET1A(){
    this->_r.a |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET2B(){
    this->_r.b |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2C(){
    this->_r.c |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2D(){
    this->_r.d |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2E(){
    this->_r.e |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2H(){
    this->_r.h |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2L(){
    this->_r.l |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<2)));
    this->_r.f &= 0xF0;
}

void Z80::ESET2A(){
    this->_r.a |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET3B(){
    this->_r.b |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3C(){
    this->_r.c |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3D(){
    this->_r.d |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3E(){
    this->_r.e |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3H(){
    this->_r.h |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3L(){
    this->_r.l |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<3)));
    this->_r.f &= 0xF0;
}

void Z80::ESET3A(){
    this->_r.a |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET4B(){
    this->_r.b |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4C(){
    this->_r.c |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4D(){
    this->_r.d |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4E(){
    this->_r.e |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4H(){
    this->_r.h |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4L(){
    this->_r.l |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<4)));
    this->_r.f &= 0xF0;
}

void Z80::ESET4A(){
    this->_r.a |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET5B(){
    this->_r.b |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5C(){
    this->_r.c |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5D(){
    this->_r.d |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5E(){
    this->_r.e |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5H(){
    this->_r.h |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5L(){
    this->_r.l |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<5)));
    this->_r.f &= 0xF0;
}

void Z80::ESET5A(){
    this->_r.a |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET6B(){
    this->_r.b |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6C(){
    this->_r.c |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6D(){
    this->_r.d |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6E(){
    this->_r.e |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6H(){
    this->_r.h |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6L(){
    this->_r.l |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<6)));
    this->_r.f &= 0xF0;
}

void Z80::ESET6A(){
    this->_r.a |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET7B(){
    this->_r.b |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7C(){
    this->_r.c |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7D(){
    this->_r.d |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7E(){
    this->_r.e |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7H(){
    this->_r.h |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7L(){
    this->_r.l |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7mHL(){
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<7)));
    this->_r.f &= 0xF0;
}

void Z80::ESET7A(){
    this->_r.a |= (1<<7);
    this->_r.f &= 0xF0;
}

#endif
