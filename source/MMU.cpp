#include <cstdint>
#include <fstream>
#include "MMU.h"
#include <string>
#include <iostream>
#include <stdio.h>

MMU::MMU(bool inbios = 0): _inbios(inbios), _bios{0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E}
{

}

uint8_t MMU::rb(uint16_t addr){ //Read byte from given address
    switch(addr & 0xF000){
        case 0x0000: //ROM bank #0
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
        case 0x4000: //Switchable ROM bank
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return this->_rom[addr];
        case 0x8000: //V-RAM
            //return gpu._vram[addr&0x1FFF];
        case 0xA000: //Switchable RAM
        case 0xB000:
            return this->_eram[addr&0x1FFF];
        case 0xC000: //Internal RAM
        case 0xD000:
        case 0xE000: //Echo RAM
            return this->_wram[addr&0x1FFF];
        case 0xF000:
            switch (addr & 0x0F00){
                case 0x000: //Continuation of Echo RAM
                case 0x100:
                case 0x200:
                case 0x300:
                case 0x400:
                case 0x500:
                case 0x600:
                case 0x700:
                case 0x800:
                case 0x900:
                case 0xA00:
                case 0xB00:
                case 0xC00:
                case 0xD00:
                    return this->_wram[addr&0x1FFF];
                case 0xE00: //Sprite attrib Mem (OAM)
                    //return ((addr&0xFF)<0xA0) ? gpu._oam[addr&0xFF] : 0;
                    return 0; //GPU unimplemented
                case 0xF00: //Zero-page and I/O
                    if(addr > 0xFF7F){
                        return this->_zram[addr&0x7F];
                    }
                    else switch(addr&0xF0){
                        //Unimplemented
                    }
            }
        default:
            return 0x00;
    }
    return 1;
}

uint16_t MMU::rw(uint16_t addr){ //Read word from given address
    return this->rb(addr) + (this->rb(addr+1) << 8);
}

void MMU::wb(uint16_t addr, uint8_t val){ //Write byte to given address
    switch(addr&0xF000){
        case 0x0000:
            if(this->_inbios && addr<0x0100) 
                return;
        case 0x1000:
        case 0x2000:
        case 0x3000:
            break;

        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            break;
        case 0x8000:
        case 0x9000:
            //unimplemented
            break;

        case 0xA000:
        case 0xB000:

        case 0xC000:
        case 0xD000:
        case 0xE000:
            this->_wram[addr&0x1FFF] = val;
            break;

        case 0xF000:
            switch(addr&0x0F000){
                case 0x000:
                case 0x100:
                case 0x200:
                case 0x300:
                case 0x400:
                case 0x500:
                case 0x600:
                case 0x700:
                case 0x800:
                case 0x900:
                case 0xA00:
                case 0xB00:
                case 0xC00:
                case 0xD00:
                    this->_wram[addr&0x1FF] = val;
                    break;

                case 0xE00:
                    //if((addr&0xFF)<0xA0) gpu._oam[addr&0xFF] = val;

                case 0xF00:
                    if(addr > 0xFF7F) this->_zram[addr&0x7F] = val;
                    else switch(addr&0xF0){
                    }
                    
                }
        break;
    }
    //this->dump_mem(); //Currently broken
    return;
}

void MMU::ww(uint16_t addr, uint16_t val){ //Write word to given address
    this->wb(addr + 1, val >> 8);
    this->wb(addr, val & 0xFF);
    return;
}

void MMU::loadBios(){ //Hard-code at some point
    printf("Loading ROM...\n");
    std::ifstream in_file("dmg_boot.bin");
    //printf("Loaded file\n");
    uint8_t c = in_file.get();
    uint16_t index = 0;
    while(in_file.good()){
        printf("0x%02x, ",c);
        this->_bios[index] = c;
        c = in_file.get();
        index++;
    }
    printf("\n");
    in_file.close();
    std::cout << "Loaded file" << std::endl;

}

void MMU::dump_mem(){
    std::cout << "Dumping mem" << std::endl;
    //for(uint16_t i = 0; i < 0x0100; i++){
    for(uint8_t i : _bios){
        printf("%02x ", i);
        std::cout << i << std::endl;
        //if(i % 0x20 == 0){
        //    printf("\n0x%04x: ", i);
        //}
        //printf("%02x ", _bios[i]);
    }
    printf("\n");
    //for(uint8_t i : this->_rom){
    //    std::cout << i << std::endl;
    //}
    //for(uint8_t i : this->_eram){
    //    std::cout << i << std::endl;
    //}
    //for(uint8_t i : this->_wram){
    //    std::cout << i << std::endl;
    //}
    //for(uint8_t i : this->_zram){
    //    std::cout << i << std::endl;
    //}
    //for(uint8_t i : this->memory){
    //    std::cout << i << std::endl;
    //}

}
