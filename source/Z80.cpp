#include <stdio.h>
#include "MMU.h"
#include "Z80.h"

Z80::Z80(uint8_t a = 0x00, uint8_t b = 0x00, uint8_t c = 0x00, uint8_t d = 0x00,
         uint8_t e = 0x00, uint8_t h = 0x00, uint8_t l = 0x00, uint8_t f = 0x00,
         uint8_t m = 0x00, uint8_t t = 0x00, uint16_t pc = 0x0000,
         uint16_t sp = 0xfffe, uint64_t cm = 0x00, uint64_t ct = 0x00):
        _r{a,b,c,d,e,h,l,f,m,t,pc,sp}, _clock{cm,ct}, mmu(1){

    mmu.loadBios();
}

void Z80::exec(){
    while(this->_r.pc < 0x20){
        //std::cout << "Executing function " << this->_r.pc << std::endl;
        (this->*ops[mmu.rb(this->_r.pc++)].op_function)(); //Execute op at pc
        this->_r.pc &= 0xFFFF;
        if(mmu._inbios && this->_r.pc == 0x100){
            mmu._inbios = 0;
            std::cout << "Exiting BIOS" << std::endl;
        }
        //std::cout << this->mmu.rb(this->_r.pc) << std::endl;
        //if(this->_r.pc > 0x0a || this->_r.pc <= 0x06){
        //    this->status();
        //}
    }
    mmu.dump_mem();
    //this->debug();
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
    //printf("cm = %04x\n", _clock.m);
    //printf("ct = %04x\n", _clock.t);
    printf("MMU = %01x\n", mmu._inbios);
}

void Z80::debug(){
    //customizable debug function
    for(uint16_t i = 0; i < 0xFF7F; i++){
        if(mmu.rb(i) != 0){
            printf("\n%04x: ", i);
            printf("0x%02x ", mmu.rb(i));
        }
    }
}

//int main(){
//    z80.status();
//    z80.exec();
//    return 1;
//}
