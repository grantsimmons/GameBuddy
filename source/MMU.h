#ifndef _MMU_
#define _MMU_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

#include "GPU.h"

class MMU{
    public:

        MMU(GPU& gpu, bool inbios);

        bool _inbios;
        
    //protected:

        uint8_t rb(uint16_t addr); //Read byte from given address

        uint16_t rw(uint16_t addr); //Read word from given address

		void loadRom(std::string file);

		void loadBios();

        void wb(uint16_t addr, uint8_t val); //Write byte to given address

        void ww(uint16_t addr, uint16_t val); //Write word to given address

		void dump_mem();

    private:

        GPU& gpu;

        uint8_t _bios[0x0100]; //Bootstrapping program

		uint8_t _rom[0x8000]; //ROM (32kB Cart)

		uint8_t _eram[0x2000]; //External RAM

		uint8_t _wram[0x2000]; //Working RAM

		uint8_t _zram[0x100]; //Zero-page and I/O

        uint8_t memory[0x10000]; //Rest of memory
};

#endif
