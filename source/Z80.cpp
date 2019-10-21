#include <cstdint>
#include <stdio.h>
#include "MMU.h"

class Z80{

    private:
        // Internal State
        struct clock{
            uint8_t m, t;
        }_clock;

        struct r{
            uint8_t a, b, c, d, e, h, l, f, m, t;
            uint16_t pc, sp;

        }_r;
        
        MMU mmu;
        
    public:
        Z80(uint8_t a = 0x00,
            uint8_t b = 0x00,
            uint8_t c = 0x00,
            uint8_t d = 0x00,
            uint8_t e = 0x00,
            uint8_t h = 0x00,
            uint8_t l = 0x00,
            uint8_t f = 0x00,
            uint8_t m = 0x00,
            uint8_t t = 0x00,
            uint16_t pc = 0x0000,
            uint16_t sp = 0xfffe,
            uint8_t cm = 0x00,
            uint8_t ct = 0x00
            ):
        _r{a,b,c,d,e,h,l,f,m,t,pc,sp},
        _clock{cm,ct},
        mmu(1)
        {
            for(int i = 0; i < 0x10; i++){
                printf("Reading bios at 0x%04x: 0x%02x\n", i, mmu.rb(i));
            }
            //memset(memory, 0, sizeof(memory));
        }

        void reset(){
            this->_r.a = 0;
            this->_r.b = 0;
            this->_r.c = 0;
            this->_r.d = 0;
            this->_r.e = 0;
            this->_r.h = 0;
            this->_r.l = 0;
            this->_r.f = 0;
            this->_r.pc = 0;
            this->_r.sp = 0;
            this->_r.m = 0;
            this->_r.t = 0;
            this->_clock.m = 0;
            this->_clock.t = 0;
            mmu._inbios = 1;
        }

        void status(){
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

};

int main(){
    Z80 cpu;
    cpu.status();
    return 1;
}
