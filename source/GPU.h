#ifndef _GPU_
#define _GPU_

#include <stdio.h>
#include <cstdint>

#include "blit.h"
//#include "SDL.h"

class GPU{
    public:

        GPU(uint8_t mode, uint64_t modeclock, uint16_t scy, uint16_t scx,
            uint16_t line, uint16_t lyc, uint16_t wy, uint16_t wx);

        void step(uint16_t ticks);

        void renderScan();
        
        void renderScan2();

        uint8_t rb(uint16_t addr);

        uint8_t readVram(uint16_t addr);

        void writeVram(uint16_t addr, uint8_t val);

        void wb(uint16_t addr, uint8_t val);

        void status();

        void getTicks();

        uint8_t getColor(uint8_t color_num);

        uint8_t* getFB();

        void printFB();

    private:

        uint8_t _vram[0x2000];

        uint8_t _mode;

        uint64_t _modeclock;

        uint8_t _lcdc; //0xFF40, R/W

        uint16_t _scy; //0xFF42

        uint16_t _scx; //0xFF43

        uint16_t _line; //0xFF44

        uint16_t _lyc; //0xFF45 

        uint8_t _pal; //0xFF47

        uint16_t _wy; //0xFF4A

        uint16_t _wx; //0xFF4B

        //uint8_t* _framebuffer = new uint8_t[160*140];
        uint8_t _framebuffer[160 * 144];
};

#endif
