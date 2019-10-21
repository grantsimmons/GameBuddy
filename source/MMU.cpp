#include <cstdint>
#include "MMU.h"

MMU::MMU(bool inbios = 0): _inbios(inbios), _bios{0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E}
{

}

uint8_t MMU::rb(uint16_t addr){ //Read byte from given address
    switch(addr & 0xF000){
        case 0x0000:
            if(this->_inbios){
                if(addr < 0x0100)
                    return this->_bios[addr];
                else if(addr == 0x0100) //Z80._r.pc == 0x0100
                    this->_inbios = 0;
            }
            else //BIOS reassigned after use
                return this->_rom[addr];
            break;
        case 0x1000:
        case 0x2000:
        case 0x3000:
            return this->_rom[addr];
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return this->_rom[addr];
        case 0x8000:
        case 0xA000:
        case 0xC000:
        case 0xF000:
        default:
            return 0;
    }
    return 1;
}

uint16_t MMU::rw(uint16_t addr){ //Read word from given address
    return 1;
}

void MMU::wb(uint16_t addr, uint8_t val){ //Write byte to given address
    return;
}

void MMU::ww(uint16_t addr, uint8_t val){ //Write word to given address
    return;
}
