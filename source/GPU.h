#ifndef _GPU_
#define _GPU_

#include <stdio.h>
#include <cstdint>

class GPU{
    public:

        GPU(uint8_t mode, uint64_t modeclock, uint16_t scy, uint16_t scx,
            uint16_t line, uint16_t lyc, uint16_t wy, uint16_t wx);

        void step(uint16_t ticks);

        void renderScan();

        uint8_t rb(uint16_t addr);

        void wb(uint16_t addr, uint8_t val);

        void status();

        void getTicks();

    private:

        uint8_t _mode;

        uint64_t _modeclock;

        uint16_t _scy; //0xFF42

        uint16_t _scx; //0xFF43

        uint16_t _line; //0xFF44

        uint16_t _lyc; //0xFF45 

        uint16_t _wy; //0xFF4A

        uint16_t _wx; //0xFF4B
};

#endif
