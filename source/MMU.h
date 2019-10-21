#ifndef _MMU_
#define _MMU_

#include <cstdint>

class MMU{
    public:

        bool _inbios;

        MMU(bool inbios);

    //protected:

        uint8_t rb(uint16_t addr); //Read byte from given address

        uint16_t rw(uint16_t addr); //Read word from given address

        void wb(uint16_t addr, uint8_t val); //Write byte to given address

        void ww(uint16_t addr, uint8_t val); //Write word to given address

    private:

        uint8_t _bios[0x0100]; //Bootstrapping program

		uint8_t _rom[0x7FFF];

        uint8_t memory[0x10000]; //Rest of memory
};

#endif
