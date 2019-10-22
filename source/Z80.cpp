#include <cstdint>
#include <stdio.h>
#include "MMU.h"
#include "Z80.h"

extern MMU mmu;
        
Z80::Z80():_r{0,0,0,0,0,0,0,0,0,0,0,0xfffe}, _clock{0,0}, mmu(1){

    for(int i = 0; i < 0x10; i++){
        printf("Reading bios at 0x%04x: 0x%02x\n", i, mmu.rb(i));
    }
            //memset(memory, 0, sizeof(memory));
}

Z80::Z80(uint8_t a = 0x00, uint8_t b = 0x00, uint8_t c = 0x00, uint8_t d = 0x00,
         uint8_t e = 0x00, uint8_t h = 0x00, uint8_t l = 0x00, uint8_t f = 0x00,
         uint8_t m = 0x00, uint8_t t = 0x00, uint16_t pc = 0x0000,
         uint16_t sp = 0xfffe, uint8_t cm = 0x00, uint8_t ct = 0x00):
        _r{a,b,c,d,e,h,l,f,m,t,pc,sp}, _clock{cm,ct}, mmu(1){

    for(int i = 0; i < 0x10; i++){
        printf("Reading bios at 0x%04x: 0x%02x\n", i, mmu.rb(i));
    }
            //memset(memory, 0, sizeof(memory));
}


void Z80::reset(){
    this->_r.a = 0x00;
    this->_r.b = 0x00;
    this->_r.c = 0x00;
    this->_r.d = 0x00;
    this->_r.e = 0x00;
    this->_r.h = 0x00;
    this->_r.l = 0x00;
    this->_r.f = 0x00;
    this->_r.pc = 0x0000;
    this->_r.sp = 0xfffe;
    this->_r.m = 0x00;
    this->_r.t = 0x00;
    this->_clock.m = 0x00;
    this->_clock.t = 0x00;
    this->mmu._inbios = 1;
}

void Z80::status(){
    printf("a = %02x\n", _r.a);
    printf("b = %02x\n", _r.b);
    printf("c = %02x\n", _r.c);
    printf("d = %02x\n", _r.d);
    printf("e = %02x\n", _r.e);
    printf("h = %02x\n", _r.h);
    printf("l = %02x\n", _r.l);
    printf("f = %02x\n", _r.f);
    printf("m = %02x\n", _r.m);
    printf("t = %02x\n", _r.t);
    printf("pc = %04x\n", _r.pc);
    printf("sp = %04x\n", _r.sp);
    printf("cm = %04x\n", _clock.m);
    printf("ct = %04x\n", _clock.t);
    printf("MMU = %01x\n", mmu._inbios);
}

int main(){
    z80.status();
    return 1;
}
