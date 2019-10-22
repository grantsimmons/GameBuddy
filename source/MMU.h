#ifndef _MMU_
#define _MMU_

#include <cstdint>
#include <string>

class MMU{
    public:

        bool _inbios;

        MMU(bool inbios);

    //protected:

        uint8_t rb(uint16_t addr); //Read byte from given address

        uint16_t rw(uint16_t addr); //Read word from given address

		//void load(std::string file);

		void loadBios();

        void wb(uint16_t addr, uint8_t val); //Write byte to given address

        void ww(uint16_t addr, uint8_t val); //Write word to given address

    private:

        uint8_t _bios[0x0100]; //Bootstrapping program

		uint8_t _rom[0x8000]; //ROM (32kB Cart)

		uint8_t _eram[0x2000]; //External RAM

		uint8_t _wram[0x2000]; //Working RAM

		uint8_t _zram[0x100]; //Zero-page and I/O

        uint8_t memory[0x10000]; //Rest of memory
};

#endif
