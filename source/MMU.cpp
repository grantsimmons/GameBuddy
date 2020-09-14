#include "MMU.h"

#include <iomanip>
#include <bitset>

std::ofstream mmu_outfile;

MMU::MMU(GPU& gpu, bool inbios = 0): gpu(gpu), _inbios(inbios)
{
    mmu_outfile.open("serial.txt");

}

uint8_t MMU::rb(uint16_t addr){ //Read byte from given address
    switch(addr & 0xF000){
        case 0x0000: //ROM bank #0
            if(this->_inbios){
                if(addr < 0x0100)
                    return this->_bios[addr];
                else if(addr == 0x0100){ //Z80._r.pc == 0x0100
                    printf("Exiting BIOS. Addr: %02x\n", addr);
                    this->_inbios = 0;
                    return this->_rom[addr];
                }
                else if(addr > 0x100){ //Cart ROM reads from BIOS
                    return this->_rom[addr];
                }
            }
            else //BIOS reassigned after use
                std::cout << "ROM Read " << std::hex << addr << ", " << std::bitset<8>(_rom[addr]) << "\n";
                return this->_rom[addr];
            break;

        case 0x1000:
        case 0x2000:
        case 0x3000:
            std::cout << "ROM Read " << std::hex << addr << ", " << std::bitset<8>(_rom[addr]) << "\n";
            return this->_rom[addr];

        case 0x4000: //Switchable ROM bank
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return this->_rom[addr];

        case 0x8000: //V-RAM (8k)
        case 0x9000:
            return gpu.readVram(addr);

        case 0xA000: //Switchable RAM (8k)
        case 0xB000:
            return this->_eram[addr & 0x1FFF];

        case 0xC000: //Internal RAM
        case 0xD000:
        case 0xE000: //Echo RAM
            std::cout << "WRAM Read " << std::hex << addr << " (Masked = " << std::hex << (addr & 0x1FFF) << "), " << std::bitset<8>(_wram[addr & 0x1FFF]) << "\n";
            return this->_wram[addr & 0x1FFF];

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
                    return this->_wram[addr & 0x1FFF];

                case 0xE00: //Sprite attrib Mem (OAM)
                    //return ((addr & 0xFF) < 0xA0) ? gpu._oam[addr & 0xFF] : 0;
                    return 0; //GPU unimplemented

                case 0xF00: //Zero-page and I/O
                    if(addr > 0xFF7F){
                        return this->_zram[addr & 0x7F];
                    }
                    else switch(addr & 0xF0){
                        //GPU access
                        case 0x40:
                        case 0x50:
                        case 0x60:
                        case 0x70:
                            return gpu.rb(addr);
                            return 0;
                    }
                    return 0;
            }
        default:
            return 0x00;
    }
    return 0;
}

uint16_t MMU::rw(uint16_t addr){ //Read word from given address
    return this->rb(addr) | (this->rb(addr+1) << 8);
}

void MMU::wb(uint16_t addr, uint8_t val){ //Write byte to given address
    switch(addr & 0xF000){
        case 0x0000:
            if(this->_inbios && addr < 0x0100) 
                return; //Read-Only

        case 0x1000: //ROM
        case 0x2000:
        case 0x3000:
            break;

        case 0x4000: //ROM
        case 0x5000:
        case 0x6000:
        case 0x7000:
            break;

        case 0x8000: //VRAM
        case 0x9000:
            std::cout << "VRAM write: " << std::hex << addr << ", " << std::hex << (int) val << '\n';
            gpu.writeVram(addr, val);
            break;

        case 0xA000:
        case 0xB000:
            this->_eram[addr & 0x1FFF] = val; //FIXME: Is this right?

        case 0xC000:
        case 0xD000:
        case 0xE000:
            std::cout << "WRAM write: " << std::hex << addr << ", " << std::hex << (int) val << '\n';
            this->_wram[addr & 0x1FFF] = val;
            std::cout << "Read back: " << std::hex << addr << ", " << (int) this->rb(addr) << '\n';
            break;

        case 0xF000:
            switch(addr & 0x0F00){
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
                    //std::cout << "WRAM write" << std::endl;
                    this->_wram[addr & 0x1FF] = val;
                    break;

                case 0xE00:
                    //if((addr&0xFF)<0xA0) gpu._oam[addr&0xFF] = val;
                    break;

                case 0xF00:
                    //std::cout << "ZRAM write" << std::endl;
                    if(addr > 0xFF7F){
                        this->_zram[addr & 0x7F] = val;
                    }
                    else{
                        switch(addr & 0xF0){
							case 0x00:
								if(addr & 0x1){
									std::cout << "Writing " << (int) val <<
										" to Serial" << '\n';
                                        mmu_outfile << (int) val;
								}
								if(addr & 0x2){
									std::cout << "Writing " << (int) val <<
										" to SC" << '\n';
								}
								if(addr & 0x3){
									std::cout << "That wasn't supposed to happen" << '\n';
								}
								break;
                            //GPU access
                            case 0x40:
                            case 0x50:
                            case 0x60:
                            case 0x70:
                                gpu.wb(addr, val);
                            break;
                        }
                    }
                    break;
                    
            }
        break;
    }
    return;
}

void MMU::ww(uint16_t addr, uint16_t val){ //Write word to given address
    this->wb(addr + 1, val >> 8);
    this->wb(addr, val & 0xFF);
    return;
}

void MMU::loadRom(std::string file){
    printf("Loading Game ROM...\n");
    std::ifstream in_file(file, std::ifstream::binary);
    uint8_t c = in_file.get();
    uint16_t index = 0;
    while(in_file.good()){
        //printf("0x%02x, ",c);
        this->_rom[index] = c;
        c = in_file.get();
        index++;
    }
    printf("Exit Index: %x\n", index);
    printf("\n");
    in_file.close();
    std::cout << "Loaded Game ROM" << std::endl;

}

void MMU::loadBios(){ //Hard-code at some point
    printf("Loading ROM...\n");
//#ifndef VERIF
    std::ifstream in_file("dmg_boot.bin", std::ifstream::binary);
//#else
//    std::ifstream in_file("..\\..\\GameBuddy-Verilog\\scripts\\stim.bin", std::ifstream::binary);
//#endif
    uint8_t c = in_file.get();
    uint16_t index = 0;
    while(in_file.good()){
        this->_bios[index] = c;
        printf("0x%02x, ",c);
        c = in_file.get();
        index++;
    }
    printf("Exit Index: %x\n", index);
    printf("\n");
    in_file.close();
    std::cout << "Loaded file" << std::endl;

}

void MMU::dump_mem(){
    std::cout << "Dumping mem" << std::endl;
    //for(uint16_t i = 0; i < 0x0100; i++){
    int counter = 0;
    /*
    std::cout << "BIOS" << std::endl;
    for(uint8_t i : _bios){
        printf("%02x ", i);
        counter++;
        if (counter % 16 == 0)
            std::cout << '\n';
    }
    printf("\n");
    counter = 0;
    std::cout << "WRAM\n";
    for(uint8_t i : _wram){
        //if (i != 0){
            printf("%02x ", i);
            counter++;
            if (counter % 16 == 0)
                std::cout << '\n';
        //}
    }
    printf("\n");
    counter = 0;
    std::cout << "ZRAM\n";
    for(uint8_t i : _zram){
        printf("%02x ", i);
        counter++;
        if (counter % 16 == 0)
            std::cout << '\n';
    }
    printf("\n");
    counter = 0;
    std::cout << "ROM\n";
    for(uint8_t i : this->_rom){
        //if (i != 0){
            printf("%02x ", i);
            counter++;
            if (counter % 16 == 0)
                std::cout << '\n';
        //}
    }
    printf("\n");
    counter = 0;
    std::cout << "ERAM\n";
    for(uint8_t i : this->_eram){
        //if (i != 0){
            printf("%02x ", i);
            counter++;
            if (counter % 16 == 0)
                std::cout << '\n';
        //}
    }
    */
    printf("\n");
    std::cout << "VRAM\n";
    for(uint16_t i = 0; i < 0x2000; i++){
            if (i % 16 == 0)
                std::cout << "\n0x" << std::setfill('0') << std::setw(4) << std::right << std::hex << counter++ * 16 << ": ";
            printf("%02x ", gpu.readVram(i));
    }
    printf("\n");
    //counter = 0;
    //std::cout << "Memory" << std::endl;
    //for(uint8_t i : this->memory){
    //    if (i != 0){
    //        printf("%02x ", i);
    //        counter++;
    //        if (counter % 16 == 0)
    //            std::cout << std::endl;
    //    }
    //}

}

