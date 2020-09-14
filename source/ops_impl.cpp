#ifndef _OPS_
#define _OPS_

#include "Z80.h"

#define CARRY (1<<4) //C
#define HALF_CARRY (1<<5) //H
#define ADD_SUB (1<<6) //N
#define ZERO (1<<7) //Z

void Z80::NOP(){
    std::cout << "NOP\n";
    this->_r.f &= 0xF0;
}

void Z80::LDBCnn(){
    std::cout << "LDBCnn\n";
    this->_r.c = this->mmu.rb(this->_r.pc);
    this->_r.b = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDmBCA(){
    std::cout << "LDmBCA\n";
    this->mmu.wb(this->_r.b << 8 | this->_r.c, this->_r.a);
    this->_r.f &= 0xF0;
}

void Z80::INCBC(){
    std::cout << "INCBC\n";
    this->_r.c += 1;
    this->_r.b = this->_r.c == 0x00 ? this->_r.b + 1 : this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::INCB(){
    std::cout << "INCB\n";
    this->_r.f = (this->_r.b & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.b += 1;
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECB(){
    std::cout << "DECB\n";
    this->_r.f = (this->_r.b & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.b -= 1;
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDBn(){
    std::cout << "LDBn\n";
    this->_r.b = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RLCA(){
    std::cout << "RLCA\n";
    this->_r.f = (this->_r.a & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = this->_r.a << 1 | ((this->_r.a & 0x80) ? 1 : 0);
    this->_r.f &= ~(ZERO | ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::LDmnnSP(){
    std::cout << "LDmnnSP\n";
    this->mmu.ww(this->mmu.rb(this->_r.pc) | (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.sp);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::ADDHLBC(){
    std::cout << "ADDHLBC\n";
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
    std::cout << "LDAmBC\n";
    this->_r.a = this->mmu.rb(this->_r.b << 8 | this->_r.c);
    this->_r.f &= 0xF0;
}

void Z80::DECBC(){
    std::cout << "DECBC\n";
    this->_r.c -= 1;
    this->_r.b = this->_r.c == 0xFF ? this->_r.b - 1 : this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::INCC(){
    std::cout << "INCC\n";
    this->_r.f = (this->_r.c & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.c += 1;
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECC(){
    std::cout << "DECC\n";
    this->_r.f = (this->_r.c & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.c -= 1;
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDCn(){
    std::cout << "LDCn\n";
    this->_r.c = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RRCA(){
    std::cout << "RRCA\n";
    this->_r.f = (this->_r.a & 0x01) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = this->_r.a >> 1 | ((this->_r.a & 0x01) ? 1 << 7 : 0);
    this->_r.f &= ~(ZERO | ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::STOP(){
    std::cout << "STOP\n";
#ifdef VERIF
    this->running = false;
#endif
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDDEnn(){
    std::cout << "LDDEnn\n";
    this->_r.e = this->mmu.rb(this->_r.pc);
    this->_r.d = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDmDEA(){
    std::cout << "LDmDEA\n";
    this->mmu.wb(this->_r.d << 8 | this->_r.e, this->_r.a);
    this->_r.f &= 0xF0;
}

void Z80::INCDE(){
    std::cout << "INCDE\n";
    this->_r.e += 1;
    this->_r.d = this->_r.e == 0x00 ? this->_r.d + 1 : this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::INCD(){
    std::cout << "INCD\n";
    this->_r.f = (this->_r.d & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.d += 1;
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECD(){
    std::cout << "DECD\n";
    this->_r.f = (this->_r.d & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.d -= 1;
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDDn(){
    std::cout << "LDDn\n";
    this->_r.d = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RLA(){
    std::cout << "RLA\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.a & 0x80) ? this->_r.f | CARRY : this->_r.f & ~CARRY;
    this->_r.a = ((this->_r.a << 1) | (int) orig_carry) & 0xFF;
    this->_r.f &= ~(ZERO | ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::JRn(){
    std::cout << "JRn\n";
    this->_r.pc += (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::ADDHLDE(){
    std::cout << "ADDHLDE\n";
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
    std::cout << "LDAmDE\n";
    this->_r.a = this->mmu.rb(this->_r.d << 8 | this->_r.e);
    this->_r.f &= 0xF0;
}

void Z80::DECDE(){
    std::cout << "DECDE\n";
    this->_r.e -= 1;
    this->_r.d = this->_r.e == 0xFF ? this->_r.d - 1 : this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::INCE(){
    std::cout << "INCE\n";
    this->_r.f = (this->_r.e & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.e += 1;
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECE(){
    std::cout << "DECE\n";
    this->_r.f = (this->_r.e & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.e -= 1;
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDEn(){
    std::cout << "LDEn\n";
    this->_r.e = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RRA(){
    std::cout << "RRA\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.a & 0x01) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = ((this->_r.a >> 1) | (int) orig_carry << 7) & 0xFF;
    this->_r.f &= ~(ZERO | ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::JRNZn(){
    std::cout << "JRNZn\n";
    this->_r.pc += this->_r.f & ZERO ? 0 : (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::LDHLnn(){
    std::cout << "LDHLnn\n";
    this->_r.l = this->mmu.rb(this->_r.pc);
    this->_r.h = this->mmu.rb(this->_r.pc + 1);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDImHLA(){
    std::cout << "LDImHLA\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.a);
    this->INCHL();
    this->_r.f &= 0xF0;
}

void Z80::INCHL(){
    std::cout << "INCHL\n";
    this->_r.l += 1;
    this->_r.h = this->_r.l == 0x00 ? this->_r.h + 1 : this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::INCH(){
    std::cout << "INCH\n";
    this->_r.f = (this->_r.h & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.h += 1;
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECH(){
    std::cout << "DECH\n";
    this->_r.f = (this->_r.h & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.h -= 1;
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDHn(){
    std::cout << "LDHn\n";
    this->_r.h = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::DAA(){
    std::cout << "DAA\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::JRZn(){
    std::cout << "JRZn\n";
    this->_r.pc += this->_r.f & ZERO ? (int8_t) this->mmu.rb(this->_r.pc) : 0;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::ADDHLHL(){
    std::cout << "ADDHLHL\n";
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
    std::cout << "LDIAmHL\n";
    this->_r.a = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->INCHL();
    this->_r.f &= 0xF0;
}

void Z80::DECHL(){
    std::cout << "DECHL\n";
    this->_r.l -= 1;
    this->_r.h = this->_r.l == 0xFF ? this->_r.h - 1 : this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::INCL(){
    std::cout << "INCL\n";
    this->_r.f = (this->_r.l & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.l += 1;
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECL(){
    std::cout << "DECL\n";
    this->_r.f = (this->_r.l & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.l -= 1;
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDLn(){
    std::cout << "LDLn\n";
    this->_r.l = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::NOT(){
    std::cout << "NOT\n";
    this->_r.a = ~this->_r.a;
    this->_r.f |= ADD_SUB | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::JRNCn(){
    std::cout << "JRNCn\n";
    this->_r.pc += this->_r.f & CARRY ? 0 : (int8_t) this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::LDSPnn(){
    std::cout << "LDSPnn\n";
    this->_r.sp = this->mmu.rw(this->_r.pc);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDDmHLA(){
    std::cout << "LDDmHLA\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.a);
    this->DECHL();
    this->_r.f &= 0xF0;
}

void Z80::INCSP(){
    std::cout << "INCSP\n";
    this->_r.sp += 1;
    this->_r.f &= 0xF0;
}

void Z80::INCmHL(){
    std::cout << "INCmHL\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->mmu.rb(this->_r.h << 8 | this->_r.l) + 1);
    this->_r.f = this->mmu.rb(this->_r.h << 8 | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0x1F == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECmHL(){
    std::cout << "DECmHL\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->mmu.rb(this->_r.h << 8 | this->_r.l) - 1);
    this->_r.f = this->mmu.rb(this->_r.h << 8 | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0x1F == 0x0F ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDmHLn(){
    std::cout << "LDmHLn\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->mmu.rb(this->_r.pc));
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::SCF(){
    std::cout << "SCF\n";
    this->_r.f = this->_r.f & ~ADD_SUB & ~HALF_CARRY | CARRY;
    this->_r.f &= 0xF0;
}

void Z80::JRCn(){
    std::cout << "JRCn\n";
    this->_r.pc += this->_r.f & CARRY ? (int8_t) this->mmu.rb(this->_r.pc) : 0;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::ADDHLSP(){
    std::cout << "ADDHLSP\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDDAmHL(){
    std::cout << "LDDAmHL\n";
    this->_r.a = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->DECHL();
    this->_r.f &= 0xF0;
}

void Z80::DECSP(){
    std::cout << "DECSP\n";
    this->_r.sp -= 1;
    this->_r.f &= 0xF0;
}

void Z80::INCA(){
    std::cout << "INCA\n";
    this->_r.f = (this->_r.a & 0xF) + 1 == 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.a += 1;
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::DECA(){
    std::cout << "DECA\n";
    this->_r.f = (this->_r.a & 0xF) == 0x0 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY);
    this->_r.a -= 1;
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f |= ADD_SUB;
    this->_r.f &= 0xF0;
}

void Z80::LDAn(){
    std::cout << "LDAn\n";
    this->_r.a = this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::CCF(){
    std::cout << "CCF\n";
    this->_r.f = (this->_r.f & CARRY) ? (this->_r.f & ~(CARRY)) : (this->_r.f | CARRY);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::LDBB(){
    std::cout << "LDBB\n";
    this->_r.b = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDBC(){
    std::cout << "LDBC\n";
    this->_r.b = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDBD(){
    std::cout << "LDBD\n";
    this->_r.b = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDBE(){
    std::cout << "LDBE\n";
    this->_r.b = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDBH(){
    std::cout << "LDBH\n";
    this->_r.b = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDBL(){
    std::cout << "LDBL\n";
    this->_r.b = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDBmHL(){
    std::cout << "LDBmHL\n";
    this->_r.b = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDBA(){
    std::cout << "LDBA\n";
    this->_r.b = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDCB(){
    std::cout << "LDCB\n";
    this->_r.c = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDCC(){
    std::cout << "LDCC\n";
    this->_r.c = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDCD(){
    std::cout << "LDCD\n";
    this->_r.c = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDCE(){
    std::cout << "LDCE\n";
    this->_r.c = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDCH(){
    std::cout << "LDCH\n";
    this->_r.c = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDCL(){
    std::cout << "LDCL\n";
    this->_r.c = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDCmHL(){
    std::cout << "LDCmHL\n";
    this->_r.c = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDCA(){
    std::cout << "LDCA\n";
    this->_r.c = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDDB(){
    std::cout << "LDDB\n";
    this->_r.d = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDDC(){
    std::cout << "LDDC\n";
    this->_r.d = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDDD(){
    std::cout << "LDDD\n";
    this->_r.d = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDDE(){
    std::cout << "LDDE\n";
    this->_r.d = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDDH(){
    std::cout << "LDDH\n";
    this->_r.d = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDDL(){
    std::cout << "LDDL\n";
    this->_r.d = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDDmHL(){
    std::cout << "LDDmHL\n";
    this->_r.d = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDDA(){
    std::cout << "LDDA\n";
    this->_r.d = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDEB(){
    std::cout << "LDEB\n";
    this->_r.e = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDEC(){
    std::cout << "LDEC\n";
    this->_r.e = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDED(){
    std::cout << "LDED\n";
    this->_r.e = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDEE(){
    std::cout << "LDEE\n";
    this->_r.e = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDEH(){
    std::cout << "LDEH\n";
    this->_r.e = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDEL(){
    std::cout << "LDEL\n";
    this->_r.e = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDEmHL(){
    std::cout << "LDEmHL\n";
    this->_r.e = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDEA(){
    std::cout << "LDEA\n";
    this->_r.e = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDHB(){
    std::cout << "LDHB\n";
    this->_r.h = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDHC(){
    std::cout << "LDHC\n";
    this->_r.h = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDHD(){
    std::cout << "LDHD\n";
    this->_r.h = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDHE(){
    std::cout << "LDHE\n";
    this->_r.h = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDHH(){
    std::cout << "LDHH\n";
    this->_r.h = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDHL(){
    std::cout << "LDHL\n";
    this->_r.h = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDHmHL(){
    std::cout << "LDHmHL\n";
    this->_r.h = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDHA(){
    std::cout << "LDHA\n";
    this->_r.h = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDLB(){
    std::cout << "LDLB\n";
    this->_r.l = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDLC(){
    std::cout << "LDLC\n";
    this->_r.l = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDLD(){
    std::cout << "LDLD\n";
    this->_r.l = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDLE(){
    std::cout << "LDLE\n";
    this->_r.l = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDLH(){
    std::cout << "LDLH\n";
    this->_r.l = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDLL(){
    std::cout << "LDLL\n";
    this->_r.l = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDLmHL(){
    std::cout << "LDLmHL\n";
    this->_r.l = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDLA(){
    std::cout << "LDLA\n";
    this->_r.l = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::LDmHLB(){
    std::cout << "LDmHLB\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.b);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLC(){
    std::cout << "LDmHLC\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.c);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLD(){
    std::cout << "LDmHLD\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.d);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLE(){
    std::cout << "LDmHLE\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.e);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLH(){
    std::cout << "LDmHLH\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.h);
    this->_r.f &= 0xF0;
}

void Z80::LDmHLL(){
    std::cout << "LDmHLL\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::HALT(){
    std::cout << "HALT\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDmHLA(){
    std::cout << "LDmHLA\n";
    this->mmu.wb(this->_r.h << 8 | this->_r.l, this->_r.a);
    this->_r.f &= 0xF0;
}

void Z80::LDAB(){
    std::cout << "LDAB\n";
    this->_r.a = this->_r.b;
    this->_r.f &= 0xF0;
}

void Z80::LDAC(){
    std::cout << "LDAC\n";
    this->_r.a = this->_r.c;
    this->_r.f &= 0xF0;
}

void Z80::LDAD(){
    std::cout << "LDAD\n";
    this->_r.a = this->_r.d;
    this->_r.f &= 0xF0;
}

void Z80::LDAE(){
    std::cout << "LDAE\n";
    this->_r.a = this->_r.e;
    this->_r.f &= 0xF0;
}

void Z80::LDAH(){
    std::cout << "LDAH\n";
    this->_r.a = this->_r.h;
    this->_r.f &= 0xF0;
}

void Z80::LDAL(){
    std::cout << "LDAL\n";
    this->_r.a = this->_r.l;
    this->_r.f &= 0xF0;
}

void Z80::LDAmHL(){
    std::cout << "LDAmHL\n";
    this->_r.a = this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f &= 0xF0;
}

void Z80::LDAA(){
    std::cout << "LDAA\n";
    this->_r.a = this->_r.a;
    this->_r.f &= 0xF0;
}

void Z80::ADDAB(){
    std::cout << "ADDAB\n";
    this->_r.f = this->_r.a + this->_r.b > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.b & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.b;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAC(){
    std::cout << "ADDAC\n";
    this->_r.f = this->_r.a + this->_r.c > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.c & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.c;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAD(){
    std::cout << "ADDAD\n";
    this->_r.f = this->_r.a + this->_r.d > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.d & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.d;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAE(){
    std::cout << "ADDAE\n";
    this->_r.f = this->_r.a + this->_r.e > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.e & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.e;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAH(){
    std::cout << "ADDAH\n";
    this->_r.f = this->_r.a + this->_r.h > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.h & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.h;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAL(){
    std::cout << "ADDAL\n";
    this->_r.f = this->_r.a + this->_r.l > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.l & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.l;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAmHL(){
    std::cout << "ADDAmHL\n";
    this->_r.f = this->_r.a + this->mmu.rb(this->_r.h << 8 | this->_r.l) > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADDAA(){
    std::cout << "ADDAA\n";
    this->_r.f = this->_r.a + this->_r.a > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.a & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->_r.a;
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::ADCAB(){
    std::cout << "ADCAB\n";
    bool temp_carry = (this->_r.a + this->_r.b + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.b & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.b + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAC(){
    std::cout << "ADCAC\n";
    bool temp_carry = (this->_r.a + this->_r.c + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.c & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.c + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAD(){
    std::cout << "ADCAD\n";
    bool temp_carry = (this->_r.a + this->_r.d + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.d & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.d + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAE(){
    std::cout << "ADCAE\n";
    bool temp_carry = (this->_r.a + this->_r.e + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.e & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.e + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAH(){
    std::cout << "ADCAH\n";
    bool temp_carry = (this->_r.a + this->_r.h + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.h & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.h + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAL(){
    std::cout << "ADCAL\n";
    bool temp_carry = (this->_r.a + this->_r.l + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.l & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.l + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAmHL(){
    std::cout << "ADCAmHL\n";
    bool temp_carry = (this->_r.a + this->mmu.rb(this->_r.h << 8 | this->_r.l) + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->mmu.rb(this->_r.h << 8 | this->_r.l) + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ADCAA(){
    std::cout << "ADCAA\n";
    bool temp_carry = (this->_r.a + this->_r.a + (this->_r.f & CARRY ? 1 : 0)) > 0xFF ? true : false; //Carry flag
    this->_r.f = ((this->_r.a & 0xF) + (this->_r.a & 0xF) + (this->_r.f & CARRY ? 1 : 0)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY)); //Half-Carry flag
    this->_r.a += this->_r.a + (this->_r.f & CARRY ? 1 : 0);
    this->_r.f &= ~(ADD_SUB); //Clear Add_Sub flag;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f = temp_carry ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f &= 0xF0;
}

void Z80::SUBAB(){
    std::cout << "SUBAB\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.b & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.b) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.b;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAC(){
    std::cout << "SUBAC\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.c & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.c) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.c;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAD(){
    std::cout << "SUBAD\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.d & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.d) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.d;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAE(){
    std::cout << "SUBAE\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.e & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.e) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.e;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAH(){
    std::cout << "SUBAH\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.h & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.h) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.h;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAL(){
    std::cout << "SUBAL\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.l & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.l) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.l;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAmHL(){
    std::cout << "SUBAmHL\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->mmu.rb(this->_r.h << 8 | this->_r.l)) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SUBAA(){
    std::cout << "SUBAA\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->_r.a & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->_r.a) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->_r.a;
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= 0xF0;
}

void Z80::SBCAB(){
    std::cout << "SBCAB\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAC(){
    std::cout << "SBCAC\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAD(){
    std::cout << "SBCAD\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAE(){
    std::cout << "SBCAE\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAH(){
    std::cout << "SBCAH\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAL(){
    std::cout << "SBCAL\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAmHL(){
    std::cout << "SBCAmHL\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAA(){
    std::cout << "SBCAA\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::ANDB(){
    std::cout << "ANDB\n";
    this->_r.a &= this->_r.b;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDC(){
    std::cout << "ANDC\n";
    this->_r.a &= this->_r.c;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDD(){
    std::cout << "ANDD\n";
    this->_r.a &= this->_r.d;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDE(){
    std::cout << "ANDE\n";
    this->_r.a &= this->_r.e;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDH(){
    std::cout << "ANDH\n";
    this->_r.a &= this->_r.h;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDL(){
    std::cout << "ANDL\n";
    this->_r.a &= this->_r.l;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDmHL(){
    std::cout << "ANDmHL\n";
    this->_r.a &= this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::ANDA(){
    std::cout << "ANDA\n";
    this->_r.a &= this->_r.a;
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.f &= 0xF0;
}

void Z80::XORB(){
    std::cout << "XORB\n";
    this->_r.a ^= this->_r.b;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORC(){
    std::cout << "XORC\n";
    this->_r.a ^= this->_r.c;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORD(){
    std::cout << "XORD\n";
    this->_r.a ^= this->_r.d;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORE(){
    std::cout << "XORE\n";
    this->_r.a ^= this->_r.e;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORH(){
    std::cout << "XORH\n";
    this->_r.a ^= this->_r.h;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORL(){
    std::cout << "XORL\n";
    this->_r.a ^= this->_r.l;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORmHL(){
    std::cout << "XORmHL\n";
    this->_r.a ^= this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::XORA(){
    std::cout << "XORA\n";
    this->_r.a ^= this->_r.a;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORB(){
    std::cout << "ORB\n";
    this->_r.a |= this->_r.b;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORC(){
    std::cout << "ORC\n";
    this->_r.a |= this->_r.c;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORD(){
    std::cout << "ORD\n";
    this->_r.a |= this->_r.d;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORE(){
    std::cout << "ORE\n";
    this->_r.a |= this->_r.e;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORH(){
    std::cout << "ORH\n";
    this->_r.a |= this->_r.h;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORL(){
    std::cout << "ORL\n";
    this->_r.a |= this->_r.l;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORmHL(){
    std::cout << "ORmHL\n";
    this->_r.a |= this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ORA(){
    std::cout << "ORA\n";
    this->_r.a |= this->_r.a;
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::CPB(){
    std::cout << "CPB\n";
    uint8_t val = this->_r.a - this->_r.b;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.b & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPC(){
    std::cout << "CPC\n";
    uint8_t val = this->_r.a - this->_r.c;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.c & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPD(){
    std::cout << "CPD\n";
    uint8_t val = this->_r.a - this->_r.d;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.d & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPE(){
    std::cout << "CPE\n";
    uint8_t val = this->_r.a - this->_r.e;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.e & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPH(){
    std::cout << "CPH\n";
    uint8_t val = this->_r.a - this->_r.h;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.h & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPL(){
    std::cout << "CPL\n";
    uint8_t val = this->_r.a - this->_r.l;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.l & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPmHL(){
    std::cout << "CPmHL\n";
    uint8_t val = this->_r.a - this->mmu.rb(this->_r.h << 8 | this->_r.l);
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->mmu.rb(this->_r.h << 8 | this->_r.l) & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::CPA(){
    std::cout << "CPA\n";
    uint8_t val = this->_r.a - this->_r.a;
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->_r.a & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.f &= 0xF0;
}

void Z80::RETNZ(){
    std::cout << "RETNZ\n";
    if(this->_r.f & ZERO == 0){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    }
    this->_r.f &= 0xF0;
}

void Z80::POPBC(){
    std::cout << "POPBC\n";
    this->_r.c = this->mmu.rb(this->_r.sp);
    this->_r.b = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::JPNZnn(){
    std::cout << "JPNZnn\n";
    this->_r.pc = (this->_r.f & ZERO) ? this->_r.pc : this->mmu.rw(this->_r.pc);
    this->_r.pc += (this->_r.f & ZERO) ? 0 : 2;
    this->_r.f &= 0xF0;
}

void Z80::JPnn(){
    std::cout << "JPnn\n";
    this->_r.pc = this->mmu.rw(this->_r.pc);
    this->_r.f &= 0xF0;
}

void Z80::CALLNZnn(){
    std::cout << "CALLNZnn\n";
    if(this->_r.f & ZERO == 0){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
    this->_r.f &= 0xF0;
}

void Z80::PUSHBC(){
    std::cout << "PUSHBC\n";
    this->mmu.wb(this->_r.sp - 1, this->_r.b);
    this->mmu.wb(this->_r.sp - 2, this->_r.c);
    this->_r.sp -= 2;
    this->_r.f &= 0xF0;
}

void Z80::ADDAn(){
    std::cout << "ADDAn\n";
    this->_r.f = this->_r.a + this->mmu.rb(this->_r.pc) > 0xFF ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.f = ((this->_r.a & 0xF) + (this->mmu.rb(this->_r.pc) & 0xF)) & 0x10 ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f &= ~(ADD_SUB);
    this->_r.a += this->mmu.rb(this->_r.pc);
    this->_r.f = (this->_r.a == 0) ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST0(){
    std::cout << "RST0\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::RETZ(){
    std::cout << "RETZ\n";
    if(this->_r.f & ZERO == 1){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    }
    this->_r.f &= 0xF0;
}

void Z80::RET(){
    std::cout << "RET\n";
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::JPZnn(){
    std::cout << "JPZnn\n";
    this->_r.pc = (this->_r.f & ZERO) ? this->mmu.rw(this->_r.pc) : this->_r.pc;
    this->_r.pc += (this->_r.f & ZERO) ? 2 : 0;
    this->_r.f &= 0xF0;
}

void Z80::Extops(){
    std::cout << "Extops\n";
    updateTiming(true);
    (this->*ext_ops[mmu.rb(this->_r.pc++)].op_function)();
    gpu.step(this->_r.t);
    this->_r.f &= 0xF0;
}

void Z80::CALLZnn(){
    std::cout << "CALLZnn\n";
    if(this->_r.f & ZERO == 1){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
    this->_r.f &= 0xF0;
}

void Z80::CALLnn(){
    std::cout << "CALLnn\n";
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    this->_r.f &= 0xF0;
}

void Z80::ADCAn(){
    std::cout << "ADCAn\n";
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
    std::cout << "RST8\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::RETNC(){
    std::cout << "RETNC\n";
    if(this->_r.f & CARRY == 0){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    }
    this->_r.f &= 0xF0;
}

void Z80::POPDE(){
    std::cout << "POPDE\n";
    this->_r.e = this->mmu.rb(this->_r.sp);
    this->_r.d = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::JPNCnn(){
    std::cout << "JPNCnn\n";
    this->_r.pc = (this->_r.f & CARRY) ? this->_r.pc : this->mmu.rw(this->_r.pc);
    this->_r.pc += (this->_r.f & CARRY) ? 0 : 2;
    this->_r.f &= 0xF0;
}

void Z80::XX1(){
    std::cout << "XX1\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::CALLNCnn(){
    std::cout << "CALLNCnn\n";
    if(this->_r.f & CARRY == 0){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
    this->_r.f &= 0xF0;
}

void Z80::PUSHDE(){
    std::cout << "PUSHDE\n";
    this->mmu.wb(this->_r.sp - 1, this->_r.d);
    this->mmu.wb(this->_r.sp - 2, this->_r.e);
    this->_r.sp -= 2;
    this->_r.f &= 0xF0;
}

void Z80::SUBAn(){
    std::cout << "SUBAn\n";
    this->_r.f |= ADD_SUB; //Set Add_Sub flag;
    this->_r.f = ((this->_r.a & 0x0F) < (this->mmu.rb(this->_r.pc) & 0x0F)) ? (this->_r.f | HALF_CARRY) : (this->_r.f & ~(HALF_CARRY));
    this->_r.f = (this->_r.a < this->mmu.rb(this->_r.pc)) ? (this->_r.f | CARRY) : (this->_r.f & ~(CARRY));
    this->_r.a -= this->mmu.rb(this->_r.pc);
    this->_r.f = this->_r.a == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST10(){
    std::cout << "RST10\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::RETC(){
    std::cout << "RETC\n";
    if(this->_r.f & CARRY == 1){
        this->_r.pc = this->mmu.rw(this->_r.sp);
        this->_r.sp += 2;
    }
    this->_r.f &= 0xF0;
}

void Z80::RETI(){
    std::cout << "RETI\n";
    this->_r.f &= 0xF0;
}

void Z80::JPCnn(){
    std::cout << "JPCnn\n";
    this->_r.pc = (this->_r.f & CARRY) ? this->mmu.rw(this->_r.pc) : this->_r.pc;
    this->_r.pc += (this->_r.f & CARRY) ? 2 : 0;
    this->_r.f &= 0xF0;
}

void Z80::XX2(){
    std::cout << "XX2\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::CALLCnn(){
    std::cout << "CALLCnn\n";
    if(this->_r.f & CARRY == 1){
        this->mmu.wb(this->_r.sp - 1, ((this->_r.pc + 2) & 0xFF00) >> 8);
        this->mmu.wb(this->_r.sp - 2, (this->_r.pc + 2) & 0x00FF);
        this->_r.sp -= 2;
        this->_r.pc = this->mmu.rw(this->_r.pc);
    }
    this->_r.f &= 0xF0;
}

void Z80::XX3(){
    std::cout << "XX3\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::SBCAn(){
    std::cout << "SBCAn\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::RST18(){
    std::cout << "RST18\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDHmnA(){
    std::cout << "LDHmnA\n";
    this->mmu.wb(0xFF00 | this->mmu.rb(this->_r.pc), this->_r.a);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::POPHL(){
    std::cout << "POPHL\n";
    this->_r.l = this->mmu.rb(this->_r.sp);
    this->_r.h = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDHmCA(){
    std::cout << "LDHmCA\n";
    this->mmu.wb(0xFF00 | this->_r.c, this->_r.a);
    this->_r.f &= 0xF0;
}

void Z80::XX4(){
    std::cout << "XX4\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XX5(){
    std::cout << "XX5\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::PUSHHL(){
    std::cout << "PUSHHL\n";
    this->mmu.wb(this->_r.sp - 1, this->_r.h);
    this->mmu.wb(this->_r.sp - 2, this->_r.l);
    this->_r.sp -= 2;
    this->_r.f &= 0xF0;
}

void Z80::ANDn(){
    std::cout << "ANDn\n";
    this->_r.a &= this->mmu.rb(this->_r.pc);
    this->_r.f = HALF_CARRY | (this->_r.a == 0 ? ZERO : 0);
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST20(){
    std::cout << "RST20\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::ADDSPd(){
    std::cout << "ADDSPd\n";
    //Depends on sign
    //this->_r.f = ((this->_r.sp & 0xF) + (this->mmu.rb(this->_r.pc) & 0xF) & 0x10 ? this->_r.f | HALF_CARRY : this->_r.f & ~(HALF_CARRY));
    //this->_r.f = ((this->_r.sp & 0xFF) + (this->mmu.rb(this->_r.pc) & 0xFF) & 0x100 ? this->_r.f | CARRY : this->_r.f & ~(CARRY));
    this->_r.sp += this->mmu.rb(this->_r.pc) > 0x7F ? ((int8_t)~this->mmu.rb(this->_r.pc) + 1) & 0xFF : this->mmu.rb(this->_r.pc);
    this->_r.pc += 1;
    this->_r.f &= ~(ZERO | ADD_SUB);
    this->_r.f &= 0xF0;
}

void Z80::JPmHL(){
    std::cout << "JPmHL\n";
    this->_r.pc = this->mmu.rw(this->_r.h << 8 | this->_r.l);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::LDmnnA(){
    std::cout << "LDmnnA\n";
    this->mmu.wb(this->mmu.rb(this->_r.pc) | (this->mmu.rb(this->_r.pc + 1) << 8), this->_r.a);
    this->_r.pc += 2;
    this->_r.f &= 0xF0;
}

void Z80::XX6(){
    std::cout << "XX6\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XX7(){
    std::cout << "XX7\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XX8(){
    std::cout << "XX8\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XORn(){
    std::cout << "XORn\n";
    this->_r.a ^= this->mmu.rb(this->_r.pc);
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST28(){
    std::cout << "RST28\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDHAmn(){
    std::cout << "LDHAmn\n";
    this->_r.a = this->mmu.rb(0xFF00 | this->mmu.rb(this->_r.pc));
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::POPAF(){
    std::cout << "POPAF\n";
    this->_r.f = this->mmu.rb(this->_r.sp);
    this->_r.a = this->mmu.rb(this->_r.sp + 1);
    this->_r.sp += 2;
    this->_r.f &= 0xF0;
}

void Z80::XX9(){
    std::cout << "XX9\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::DI(){
    std::cout << "DI\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XXA(){
    std::cout << "XXA\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::PUSHAF(){
    std::cout << "PUSHAF\n";
    this->mmu.wb(this->_r.sp - 1, this->_r.a);
    this->mmu.wb(this->_r.sp - 2, this->_r.f);
    this->_r.sp -= 2;
    this->_r.f &= 0xF0;
}

void Z80::ORn(){
    std::cout << "ORn\n";
    this->_r.a |= this->mmu.rb(this->_r.pc);
    this->_r.f = this->_r.a == 0 ? ZERO : 0;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST30(){
    std::cout << "RST30\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDHLSPd(){
    std::cout << "LDHLSPd\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDSPHL(){
    std::cout << "LDSPHL\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::LDAmnn(){
    std::cout << "LDAmnn\n";
    this->_r.a = this->mmu.rb(this->mmu.rb(this->_r.pc++) | this->mmu.rb(this->_r.pc++) << 8);
    this->_r.f &= 0xF0;
}

void Z80::EI(){
    std::cout << "EI\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XXB(){
    std::cout << "XXB\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::XXC(){
    std::cout << "XXC\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}

void Z80::CPn(){
    std::cout << "CPn\n";
    uint8_t val = this->_r.a - this->mmu.rb(this->_r.pc);
    this->_r.f = (ADD_SUB) | ((this->_r.a & 0xF) - (this->mmu.rb(this->_r.pc) & 0xF) < 0 ? HALF_CARRY : 0) | (val == 0 ? ZERO : 0) | (this->_r.a < val ? CARRY : 0);
    this->_r.f &= val == 0 ? 0xFF : ~ZERO;
    this->_r.pc += 1;
    this->_r.f &= 0xF0;
}

void Z80::RST38(){
    std::cout << "RST38\n";
    std::cout << "Uncovered Function" << std::endl;
    this->_r.f &= 0xF0;
}


void Z80::ERLCB(){
    std::cout << "ERLCB\n";
    this->_r.f = this->_r.b & 0x80 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.b = (this->_r.b << 1) | ((this->_r.b & 0x80) >> 7);
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLCC(){
    std::cout << "ERLCC\n";
    this->_r.f = this->_r.c & 0x80 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.c = (this->_r.c << 1) | ((this->_r.c & 0x80) >> 7);
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLCD(){
    std::cout << "ERLCD\n";
    this->_r.f = this->_r.d & 0x80 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.d = (this->_r.d << 1) | ((this->_r.d & 0x80) >> 7);
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLCE(){
    std::cout << "ERLCE\n";
    this->_r.f = this->_r.e & 0x80 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.e = (this->_r.e << 1) | ((this->_r.e & 0x80) >> 7);
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLCH(){
    std::cout << "ERLCH\n";
    this->_r.f = this->_r.h & 0x80 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.h = (this->_r.h << 1) | ((this->_r.h & 0x80) >> 7);
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLCL(){
    std::cout << "ERLCL\n";
    this->_r.f = this->_r.l & 0x80 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.l = (this->_r.l << 1) | ((this->_r.l & 0x80) >> 7);
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLCmHL(){
    std::cout << "ERLCmHL\n";
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l) << 1) | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) >> 7));
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLCA(){
    std::cout << "ERLCA\n";
    this->_r.f = this->_r.a & 0x80 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = (this->_r.a << 1) | ((this->_r.a & 0x80) >> 7);
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRCB(){
    std::cout << "ERRCB\n";
    this->_r.f = this->_r.b & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.b = (this->_r.b >> 1) | ((this->_r.b & 0x1) << 7);
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRCC(){
    std::cout << "ERRCC\n";
    this->_r.f = this->_r.c & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.c = (this->_r.c >> 1) | ((this->_r.c & 0x1) << 7);
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRCD(){
    std::cout << "ERRCD\n";
    this->_r.f = this->_r.d & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.d = (this->_r.d >> 1) | ((this->_r.d & 0x1) << 7);
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRCE(){
    std::cout << "ERRCE\n";
    this->_r.f = this->_r.e & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.e = (this->_r.e >> 1) | ((this->_r.e & 0x1) << 7);
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRCH(){
    std::cout << "ERRCH\n";
    this->_r.f = this->_r.h & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.h = (this->_r.h >> 1) | ((this->_r.h & 0x1) << 7);
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRCL(){
    std::cout << "ERRCL\n";
    this->_r.f = this->_r.l & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.l = (this->_r.l >> 1) | ((this->_r.l & 0x1) << 7);
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRCmHL(){
    std::cout << "ERRCmHL\n";
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l) >> 1) | ((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1) << 7));
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRCA(){
    std::cout << "ERRCA\n";
    this->_r.f = this->_r.a & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = (this->_r.a >> 1) | ((this->_r.a & 0x1) << 7);
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLB(){
    std::cout << "ERLB\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.b & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.b = ((this->_r.b << 1) | (int) orig_carry) & 0xFF;
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLC(){
    std::cout << "ERLC\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.c & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.c = ((this->_r.c << 1) | (int) orig_carry) & 0xFF;
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLD(){
    std::cout << "ERLD\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.d & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.d = ((this->_r.d << 1) | (int) orig_carry) & 0xFF;
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLE(){
    std::cout << "ERLE\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.e & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.e = ((this->_r.e << 1) | (int) orig_carry) & 0xFF;
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLH(){
    std::cout << "ERLH\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.h & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.h = ((this->_r.h << 1) | (int) orig_carry) & 0xFF;
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLL(){
    std::cout << "ERLL\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.l & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.l = ((this->_r.l << 1) | (int) orig_carry) & 0xFF;
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLmHL(){
    std::cout << "ERLmHL\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) << 1 | int(orig_carry));
    this->_r.f = (this->mmu.rb((this->_r.h << 8) | this->_r.l) == 0) ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERLA(){
    std::cout << "ERLA\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = (this->_r.a & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = ((this->_r.a << 1) | (int) orig_carry) & 0xFF;
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRB(){
    std::cout << "ERRB\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = this->_r.b & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.b = (this->_r.b >> 1) | (int(orig_carry) << 7);
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRC(){
    std::cout << "ERRC\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = this->_r.c & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.c = (this->_r.c >> 1) | (int(orig_carry) << 7);
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRD(){
    std::cout << "ERRD\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = this->_r.d & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.d = (this->_r.d >> 1) | (int(orig_carry) << 7);
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRE(){
    std::cout << "ERRE\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = this->_r.e & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.e = (this->_r.e >> 1) | (int(orig_carry) << 7);
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRH(){
    std::cout << "ERRH\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = this->_r.h & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.h = (this->_r.h >> 1) | (int(orig_carry) << 7);
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRL(){
    std::cout << "ERRL\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = this->_r.l & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.l = (this->_r.l >> 1) | (int(orig_carry) << 7);
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRmHL(){
    std::cout << "ERRmHL\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (this->mmu.rb((this->_r.h << 8) | this->_r.l)) >> 1 | (int(orig_carry) << 7));
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ERRA(){
    std::cout << "ERRA\n";
    bool orig_carry = this->_r.f & CARRY ? 1 : 0;
    this->_r.f = this->_r.a & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = (this->_r.a >> 1) | (int(orig_carry) << 7);
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESLAB(){
    std::cout << "ESLAB\n";
    this->_r.f = (this->_r.b & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.b <<= 1;
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESLAC(){
    std::cout << "ESLAC\n";
    this->_r.f = (this->_r.c & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.c <<= 1;
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESLAD(){
    std::cout << "ESLAD\n";
    this->_r.f = (this->_r.d & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.d <<= 1;
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESLAE(){
    std::cout << "ESLAE\n";
    this->_r.f = (this->_r.e & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.e <<= 1;
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESLAH(){
    std::cout << "ESLAH\n";
    this->_r.f = (this->_r.h & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.h <<= 1;
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESLAL(){
    std::cout << "ESLAL\n";
    this->_r.f = (this->_r.l & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.l <<= 1;
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESLAmHL(){
    std::cout << "ESLAmHL\n";
    this->_r.f = (this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->mmu.wb(this->mmu.rb((this->_r.h << 8) | this->_r.l), this->mmu.rb((this->_r.h << 8) | this->_r.l) << 1);
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESLAA(){
    std::cout << "ESLAA\n";
    this->_r.f = (this->_r.a & 0x80) ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a <<= 1;
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESRAB(){
    std::cout << "ESRAB\n";
    this->_r.f = this->_r.b & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.b = (this->_r.b >> 1) | (this->_r.b & 0x80);
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESRAC(){
    std::cout << "ESRAC\n";
    this->_r.f = this->_r.c & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.c = (this->_r.c >> 1) | (this->_r.c & 0x80);
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESRAD(){
    std::cout << "ESRAD\n";
    this->_r.f = this->_r.d & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.d = (this->_r.d >> 1) | (this->_r.d & 0x80);
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESRAE(){
    std::cout << "ESRAE\n";
    this->_r.f = this->_r.e & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.e = (this->_r.e >> 1) | (this->_r.e & 0x80);
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESRAH(){
    std::cout << "ESRAH\n";
    this->_r.f = this->_r.h & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.h = (this->_r.h >> 1) | (this->_r.h & 0x80);
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESRAL(){
    std::cout << "ESRAL\n";
    this->_r.f = this->_r.l & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.l = (this->_r.l >> 1) | (this->_r.l & 0x80);
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESRAmHL(){
    std::cout << "ESRAmHL\n";
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.f = (this->mmu.rb((this->_r.h << 8) | this->_r.l) >> 1 | this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->mmu.wb((this->_r.h << 8) | this->_r.l, this->mmu.rb((this->_r.h << 8) | this->_r.l) >> 1 | this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x80);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESRAA(){
    std::cout << "ESRAA\n";
    this->_r.f = this->_r.a & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = (this->_r.a >> 1) | (this->_r.a & 0x80);
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f &= 0xF0;
}

void Z80::ESWAPB(){
    std::cout << "ESWAPB\n";
    this->_r.b = (((this->_r.b & 0xF0) >> 4) & 0x0F) | (((this->_r.b & 0x0F) << 4) & 0xF0);
    this->_r.f = 0;
    this->_r.f |= this->_r.b == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPC(){
    std::cout << "ESWAPC\n";
    this->_r.c = (((this->_r.c & 0xF0) >> 4) & 0x0F) | (((this->_r.c & 0x0F) << 4) & 0xF0);
    this->_r.f = 0;
    this->_r.f |= this->_r.c == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPD(){
    std::cout << "ESWAPD\n";
    this->_r.d = (((this->_r.d & 0xF0) >> 4) & 0x0F) | (((this->_r.d & 0x0F) << 4) & 0xF0);
    this->_r.f = 0;
    this->_r.f |= this->_r.d == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPE(){
    std::cout << "ESWAPE\n";
    this->_r.e = (((this->_r.e & 0xF0) >> 4) & 0x0F) | (((this->_r.e & 0x0F) << 4) & 0xF0);
    this->_r.f = 0;
    this->_r.f |= this->_r.e == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPH(){
    std::cout << "ESWAPH\n";
    this->_r.h = (((this->_r.h & 0xF0) >> 4) & 0x0F) | (((this->_r.h & 0x0F) << 4) & 0xF0);
    this->_r.f = 0;
    this->_r.f |= this->_r.h == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPL(){
    std::cout << "ESWAPL\n";
    this->_r.l = (((this->_r.l & 0xF0) >> 4) & 0x0F) | (((this->_r.l & 0x0F) << 4) & 0xF0);
    this->_r.f = 0;
    this->_r.f |= this->_r.l == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPmHL(){
    std::cout << "ESWAPmHL\n";
    this->mmu.wb((this->_r.h << 8) | this->_r.l, (((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0xF0) >> 4) & 0x0F) | (((this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x0F) << 4) & 0xF0));
    this->_r.f = 0;
    this->_r.f |= this->mmu.rb((this->_r.h << 8) | this->_r.l) == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ESWAPA(){
    std::cout << "ESWAPA\n";
    this->_r.a = (((this->_r.a & 0xF0) >> 4) & 0x0F) | (((this->_r.a & 0x0F) << 4) & 0xF0);
    this->_r.f = 0;
    this->_r.f |= this->_r.a == 0 ? ZERO : 0;
    this->_r.f &= 0xF0;
}

void Z80::ESRLB(){
    std::cout << "ESRLB\n";
    this->_r.f = this->_r.b & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.b = (this->_r.b >> 1);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f = this->_r.b == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= 0xF0;
}

void Z80::ESRLC(){
    std::cout << "ESRLC\n";
    this->_r.f = this->_r.c & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.c = (this->_r.c >> 1);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f = this->_r.c == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= 0xF0;
}

void Z80::ESRLD(){
    std::cout << "ESRLD\n";
    this->_r.f = this->_r.d & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.d = (this->_r.d >> 1);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f = this->_r.d == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= 0xF0;
}

void Z80::ESRLE(){
    std::cout << "ESRLE\n";
    this->_r.f = this->_r.e & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.e = (this->_r.e >> 1);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f = this->_r.e == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= 0xF0;
}

void Z80::ESRLH(){
    std::cout << "ESRLH\n";
    this->_r.f = this->_r.h & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.h = (this->_r.h >> 1);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f = this->_r.h == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= 0xF0;
}

void Z80::ESRLL(){
    std::cout << "ESRLL\n";
    this->_r.f = this->_r.l & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.l = (this->_r.l >> 1);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f = this->_r.l == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= 0xF0;
}

void Z80::ESRLmHL(){
    std::cout << "ESRLmHL\n";
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->mmu.wb((this->_r.h << 8) | this->_r.l, this->mmu.rb((this->_r.h << 8) | this->_r.l) >> 1);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f = this->mmu.rb((this->_r.h << 8) | this->_r.l) == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= 0xF0;
}

void Z80::ESRLA(){
    std::cout << "ESRLA\n";
    this->_r.f = this->_r.a & 0x1 ? this->_r.f | CARRY : this->_r.f & ~(CARRY);
    this->_r.a = (this->_r.a >> 1);
    this->_r.f = this->_r.f & ~(ADD_SUB | HALF_CARRY);
    this->_r.f = this->_r.a == 0 ? this->_r.f | ZERO : this->_r.f & ~(ZERO);
    this->_r.f &= 0xF0;
}

void Z80::EBIT0B(){
    std::cout << "EBIT0B\n";
    this->_r.f = (this->_r.b & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT0C(){
    std::cout << "EBIT0C\n";
    this->_r.f = (this->_r.c & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT0D(){
    std::cout << "EBIT0D\n";
    this->_r.f = (this->_r.d & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT0E(){
    std::cout << "EBIT0E\n";
    this->_r.f = (this->_r.e & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT0H(){
    std::cout << "EBIT0H\n";
    this->_r.f = (this->_r.h & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT0L(){
    std::cout << "EBIT0L\n";
    this->_r.f = (this->_r.l & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT0mHL(){
    std::cout << "EBIT0mHL\n";
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT0A(){
    std::cout << "EBIT0A\n";
    this->_r.f = (this->_r.a & (1<<0)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT1B(){
    std::cout << "EBIT1B\n";
    this->_r.f = (this->_r.b & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT1C(){
    std::cout << "EBIT1C\n";
    this->_r.f = (this->_r.c & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT1D(){
    std::cout << "EBIT1D\n";
    this->_r.f = (this->_r.d & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT1E(){
    std::cout << "EBIT1E\n";
    this->_r.f = (this->_r.e & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT1H(){
    std::cout << "EBIT1H\n";
    this->_r.f = (this->_r.h & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT1L(){
    std::cout << "EBIT1L\n";
    this->_r.f = (this->_r.l & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT1mHL(){
    std::cout << "EBIT1mHL\n";
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT1A(){
    std::cout << "EBIT1A\n";
    this->_r.f = (this->_r.a & (1<<1)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT2B(){
    std::cout << "EBIT2B\n";
    this->_r.f = (this->_r.b & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT2C(){
    std::cout << "EBIT2C\n";
    this->_r.f = (this->_r.c & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT2D(){
    std::cout << "EBIT2D\n";
    this->_r.f = (this->_r.d & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT2E(){
    std::cout << "EBIT2E\n";
    this->_r.f = (this->_r.e & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT2H(){
    std::cout << "EBIT2H\n";
    this->_r.f = (this->_r.h & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT2L(){
    std::cout << "EBIT2L\n";
    this->_r.f = (this->_r.l & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT2mHL(){
    std::cout << "EBIT2mHL\n";
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT2A(){
    std::cout << "EBIT2A\n";
    this->_r.f = (this->_r.a & (1<<2)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT3B(){
    std::cout << "EBIT3B\n";
    this->_r.f = (this->_r.b & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT3C(){
    std::cout << "EBIT3C\n";
    this->_r.f = (this->_r.c & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT3D(){
    std::cout << "EBIT3D\n";
    this->_r.f = (this->_r.d & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT3E(){
    std::cout << "EBIT3E\n";
    this->_r.f = (this->_r.e & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT3H(){
    std::cout << "EBIT3H\n";
    this->_r.f = (this->_r.h & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT3L(){
    std::cout << "EBIT3L\n";
    this->_r.f = (this->_r.l & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT3mHL(){
    std::cout << "EBIT3mHL\n";
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT3A(){
    std::cout << "EBIT3A\n";
    this->_r.f = (this->_r.a & (1<<3)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT4B(){
    std::cout << "EBIT4B\n";
    this->_r.f = (this->_r.b & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT4C(){
    std::cout << "EBIT4C\n";
    this->_r.f = (this->_r.c & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT4D(){
    std::cout << "EBIT4D\n";
    this->_r.f = (this->_r.d & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT4E(){
    std::cout << "EBIT4E\n";
    this->_r.f = (this->_r.e & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT4H(){
    std::cout << "EBIT4H\n";
    this->_r.f = (this->_r.h & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT4L(){
    std::cout << "EBIT4L\n";
    this->_r.f = (this->_r.l & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT4mHL(){
    std::cout << "EBIT4mHL\n";
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT4A(){
    std::cout << "EBIT4A\n";
    this->_r.f = (this->_r.a & (1<<4)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT5B(){
    std::cout << "EBIT5B\n";
    this->_r.f = (this->_r.b & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT5C(){
    std::cout << "EBIT5C\n";
    this->_r.f = (this->_r.c & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT5D(){
    std::cout << "EBIT5D\n";
    this->_r.f = (this->_r.d & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT5E(){
    std::cout << "EBIT5E\n";
    this->_r.f = (this->_r.e & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT5H(){
    std::cout << "EBIT5H\n";
    this->_r.f = (this->_r.h & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT5L(){
    std::cout << "EBIT5L\n";
    this->_r.f = (this->_r.l & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT5mHL(){
    std::cout << "EBIT5mHL\n";
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT5A(){
    std::cout << "EBIT5A\n";
    this->_r.f = (this->_r.a & (1<<5)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT6B(){
    std::cout << "EBIT6B\n";
    this->_r.f = (this->_r.b & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT6C(){
    std::cout << "EBIT6C\n";
    this->_r.f = (this->_r.c & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT6D(){
    std::cout << "EBIT6D\n";
    this->_r.f = (this->_r.d & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT6E(){
    std::cout << "EBIT6E\n";
    this->_r.f = (this->_r.e & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT6H(){
    std::cout << "EBIT6H\n";
    this->_r.f = (this->_r.h & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT6L(){
    std::cout << "EBIT6L\n";
    this->_r.f = (this->_r.l & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT6mHL(){
    std::cout << "EBIT6mHL\n";
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT6A(){
    std::cout << "EBIT6A\n";
    this->_r.f = (this->_r.a & (1<<6)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT7B(){
    std::cout << "EBIT7B\n";
    this->_r.f = (this->_r.b & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT7C(){
    std::cout << "EBIT7C\n";
    this->_r.f = (this->_r.c & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT7D(){
    std::cout << "EBIT7D\n";
    this->_r.f = (this->_r.d & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT7E(){
    std::cout << "EBIT7E\n";
    this->_r.f = (this->_r.e & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT7H(){
    std::cout << "EBIT7H\n";
    this->_r.f = (this->_r.h & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT7L(){
    std::cout << "EBIT7L\n";
    this->_r.f = (this->_r.l & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT7mHL(){
    std::cout << "EBIT7mHL\n";
    this->_r.f = (this->mmu.rb(this->_r.h << 8 | this->_r.l) & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::EBIT7A(){
    std::cout << "EBIT7A\n";
    this->_r.f = (this->_r.a & (1<<7)) == 0 ? (this->_r.f | ZERO) : (this->_r.f & ~(ZERO));
    this->_r.f &= ~(ADD_SUB);
    this->_r.f = this->_r.f | HALF_CARRY;
    this->_r.f &= 0xF0;
}

void Z80::ERES0B(){
    std::cout << "ERES0B\n";
    this->_r.b &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0C(){
    std::cout << "ERES0C\n";
    this->_r.c &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0D(){
    std::cout << "ERES0D\n";
    this->_r.d &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0E(){
    std::cout << "ERES0E\n";
    this->_r.e &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0H(){
    std::cout << "ERES0H\n";
    this->_r.h &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0L(){
    std::cout << "ERES0L\n";
    this->_r.l &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES0mHL(){
    std::cout << "ERES0mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<0)));
    this->_r.f &= 0xF0;
}

void Z80::ERES0A(){
    std::cout << "ERES0A\n";
    this->_r.a &= ~(1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ERES1B(){
    std::cout << "ERES1B\n";
    this->_r.b &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1C(){
    std::cout << "ERES1C\n";
    this->_r.c &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1D(){
    std::cout << "ERES1D\n";
    this->_r.d &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1E(){
    std::cout << "ERES1E\n";
    this->_r.e &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1H(){
    std::cout << "ERES1H\n";
    this->_r.h &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1L(){
    std::cout << "ERES1L\n";
    this->_r.l &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES1mHL(){
    std::cout << "ERES1mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<1)));
    this->_r.f &= 0xF0;
}

void Z80::ERES1A(){
    std::cout << "ERES1A\n";
    this->_r.a &= ~(1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ERES2B(){
    std::cout << "ERES2B\n";
    this->_r.b &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2C(){
    std::cout << "ERES2C\n";
    this->_r.c &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2D(){
    std::cout << "ERES2D\n";
    this->_r.d &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2E(){
    std::cout << "ERES2E\n";
    this->_r.e &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2H(){
    std::cout << "ERES2H\n";
    this->_r.h &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2L(){
    std::cout << "ERES2L\n";
    this->_r.l &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES2mHL(){
    std::cout << "ERES2mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<2)));
    this->_r.f &= 0xF0;
}

void Z80::ERES2A(){
    std::cout << "ERES2A\n";
    this->_r.a &= ~(1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ERES3B(){
    std::cout << "ERES3B\n";
    this->_r.b &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3C(){
    std::cout << "ERES3C\n";
    this->_r.c &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3D(){
    std::cout << "ERES3D\n";
    this->_r.d &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3E(){
    std::cout << "ERES3E\n";
    this->_r.e &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3H(){
    std::cout << "ERES3H\n";
    this->_r.h &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3L(){
    std::cout << "ERES3L\n";
    this->_r.l &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES3mHL(){
    std::cout << "ERES3mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<3)));
    this->_r.f &= 0xF0;
}

void Z80::ERES3A(){
    std::cout << "ERES3A\n";
    this->_r.a &= ~(1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ERES4B(){
    std::cout << "ERES4B\n";
    this->_r.b &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4C(){
    std::cout << "ERES4C\n";
    this->_r.c &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4D(){
    std::cout << "ERES4D\n";
    this->_r.d &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4E(){
    std::cout << "ERES4E\n";
    this->_r.e &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4H(){
    std::cout << "ERES4H\n";
    this->_r.h &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4L(){
    std::cout << "ERES4L\n";
    this->_r.l &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES4mHL(){
    std::cout << "ERES4mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<4)));
    this->_r.f &= 0xF0;
}

void Z80::ERES4A(){
    std::cout << "ERES4A\n";
    this->_r.a &= ~(1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ERES5B(){
    std::cout << "ERES5B\n";
    this->_r.b &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5C(){
    std::cout << "ERES5C\n";
    this->_r.c &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5D(){
    std::cout << "ERES5D\n";
    this->_r.d &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5E(){
    std::cout << "ERES5E\n";
    this->_r.e &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5H(){
    std::cout << "ERES5H\n";
    this->_r.h &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5L(){
    std::cout << "ERES5L\n";
    this->_r.l &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES5mHL(){
    std::cout << "ERES5mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<5)));
    this->_r.f &= 0xF0;
}

void Z80::ERES5A(){
    std::cout << "ERES5A\n";
    this->_r.a &= ~(1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ERES6B(){
    std::cout << "ERES6B\n";
    this->_r.b &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6C(){
    std::cout << "ERES6C\n";
    this->_r.c &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6D(){
    std::cout << "ERES6D\n";
    this->_r.d &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6E(){
    std::cout << "ERES6E\n";
    this->_r.e &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6H(){
    std::cout << "ERES6H\n";
    this->_r.h &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6L(){
    std::cout << "ERES6L\n";
    this->_r.l &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES6mHL(){
    std::cout << "ERES6mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<6)));
    this->_r.f &= 0xF0;
}

void Z80::ERES6A(){
    std::cout << "ERES6A\n";
    this->_r.a &= ~(1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ERES7B(){
    std::cout << "ERES7B\n";
    this->_r.b &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7C(){
    std::cout << "ERES7C\n";
    this->_r.c &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7D(){
    std::cout << "ERES7D\n";
    this->_r.d &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7E(){
    std::cout << "ERES7E\n";
    this->_r.e &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7H(){
    std::cout << "ERES7H\n";
    this->_r.h &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7L(){
    std::cout << "ERES7L\n";
    this->_r.l &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ERES7mHL(){
    std::cout << "ERES7mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) & ~(1<<7)));
    this->_r.f &= 0xF0;
}

void Z80::ERES7A(){
    std::cout << "ERES7A\n";
    this->_r.a &= ~(1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET0B(){
    std::cout << "ESET0B\n";
    this->_r.b |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0C(){
    std::cout << "ESET0C\n";
    this->_r.c |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0D(){
    std::cout << "ESET0D\n";
    this->_r.d |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0E(){
    std::cout << "ESET0E\n";
    this->_r.e |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0H(){
    std::cout << "ESET0H\n";
    this->_r.h |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0L(){
    std::cout << "ESET0L\n";
    this->_r.l |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET0mHL(){
    std::cout << "ESET0mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<0)));
    this->_r.f &= 0xF0;
}

void Z80::ESET0A(){
    std::cout << "ESET0A\n";
    this->_r.a |= (1<<0);
    this->_r.f &= 0xF0;
}

void Z80::ESET1B(){
    std::cout << "ESET1B\n";
    this->_r.b |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1C(){
    std::cout << "ESET1C\n";
    this->_r.c |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1D(){
    std::cout << "ESET1D\n";
    this->_r.d |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1E(){
    std::cout << "ESET1E\n";
    this->_r.e |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1H(){
    std::cout << "ESET1H\n";
    this->_r.h |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1L(){
    std::cout << "ESET1L\n";
    this->_r.l |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET1mHL(){
    std::cout << "ESET1mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<1)));
    this->_r.f &= 0xF0;
}

void Z80::ESET1A(){
    std::cout << "ESET1A\n";
    this->_r.a |= (1<<1);
    this->_r.f &= 0xF0;
}

void Z80::ESET2B(){
    std::cout << "ESET2B\n";
    this->_r.b |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2C(){
    std::cout << "ESET2C\n";
    this->_r.c |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2D(){
    std::cout << "ESET2D\n";
    this->_r.d |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2E(){
    std::cout << "ESET2E\n";
    this->_r.e |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2H(){
    std::cout << "ESET2H\n";
    this->_r.h |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2L(){
    std::cout << "ESET2L\n";
    this->_r.l |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET2mHL(){
    std::cout << "ESET2mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<2)));
    this->_r.f &= 0xF0;
}

void Z80::ESET2A(){
    std::cout << "ESET2A\n";
    this->_r.a |= (1<<2);
    this->_r.f &= 0xF0;
}

void Z80::ESET3B(){
    std::cout << "ESET3B\n";
    this->_r.b |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3C(){
    std::cout << "ESET3C\n";
    this->_r.c |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3D(){
    std::cout << "ESET3D\n";
    this->_r.d |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3E(){
    std::cout << "ESET3E\n";
    this->_r.e |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3H(){
    std::cout << "ESET3H\n";
    this->_r.h |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3L(){
    std::cout << "ESET3L\n";
    this->_r.l |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET3mHL(){
    std::cout << "ESET3mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<3)));
    this->_r.f &= 0xF0;
}

void Z80::ESET3A(){
    std::cout << "ESET3A\n";
    this->_r.a |= (1<<3);
    this->_r.f &= 0xF0;
}

void Z80::ESET4B(){
    std::cout << "ESET4B\n";
    this->_r.b |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4C(){
    std::cout << "ESET4C\n";
    this->_r.c |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4D(){
    std::cout << "ESET4D\n";
    this->_r.d |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4E(){
    std::cout << "ESET4E\n";
    this->_r.e |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4H(){
    std::cout << "ESET4H\n";
    this->_r.h |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4L(){
    std::cout << "ESET4L\n";
    this->_r.l |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET4mHL(){
    std::cout << "ESET4mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<4)));
    this->_r.f &= 0xF0;
}

void Z80::ESET4A(){
    std::cout << "ESET4A\n";
    this->_r.a |= (1<<4);
    this->_r.f &= 0xF0;
}

void Z80::ESET5B(){
    std::cout << "ESET5B\n";
    this->_r.b |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5C(){
    std::cout << "ESET5C\n";
    this->_r.c |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5D(){
    std::cout << "ESET5D\n";
    this->_r.d |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5E(){
    std::cout << "ESET5E\n";
    this->_r.e |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5H(){
    std::cout << "ESET5H\n";
    this->_r.h |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5L(){
    std::cout << "ESET5L\n";
    this->_r.l |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET5mHL(){
    std::cout << "ESET5mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<5)));
    this->_r.f &= 0xF0;
}

void Z80::ESET5A(){
    std::cout << "ESET5A\n";
    this->_r.a |= (1<<5);
    this->_r.f &= 0xF0;
}

void Z80::ESET6B(){
    std::cout << "ESET6B\n";
    this->_r.b |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6C(){
    std::cout << "ESET6C\n";
    this->_r.c |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6D(){
    std::cout << "ESET6D\n";
    this->_r.d |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6E(){
    std::cout << "ESET6E\n";
    this->_r.e |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6H(){
    std::cout << "ESET6H\n";
    this->_r.h |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6L(){
    std::cout << "ESET6L\n";
    this->_r.l |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET6mHL(){
    std::cout << "ESET6mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<6)));
    this->_r.f &= 0xF0;
}

void Z80::ESET6A(){
    std::cout << "ESET6A\n";
    this->_r.a |= (1<<6);
    this->_r.f &= 0xF0;
}

void Z80::ESET7B(){
    std::cout << "ESET7B\n";
    this->_r.b |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7C(){
    std::cout << "ESET7C\n";
    this->_r.c |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7D(){
    std::cout << "ESET7D\n";
    this->_r.d |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7E(){
    std::cout << "ESET7E\n";
    this->_r.e |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7H(){
    std::cout << "ESET7H\n";
    this->_r.h |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7L(){
    std::cout << "ESET7L\n";
    this->_r.l |= (1<<7);
    this->_r.f &= 0xF0;
}

void Z80::ESET7mHL(){
    std::cout << "ESET7mHL\n";
    this->mmu.wb((this->_r.h << 8 | this->_r.l), (this->mmu.rb(this->_r.h << 8 | this->_r.l) | (1<<7)));
    this->_r.f &= 0xF0;
}

void Z80::ESET7A(){
    std::cout << "ESET7A\n";
    this->_r.a |= (1<<7);
    this->_r.f &= 0xF0;
}

#endif
