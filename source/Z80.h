#ifndef _CPU_
#define _CPU_

#include <cstdint>
#include "MMU.h"

class Z80{
	private:
        struct clock{
            uint8_t m, t;
        }_clock;

        struct r{
            uint8_t a, b, c, d, e, h, l, f, m, t;
            uint16_t pc, sp;

        }_r;
        
        MMU mmu;
		
	public:

		Z80();

		Z80(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e,  uint8_t h, 
			uint8_t l, uint8_t f, uint8_t m, uint8_t t, uint16_t pc, uint16_t sp,
			uint8_t cm, uint8_t ct);

		void reset();


		//Debugging
		void status();


}z80;

#endif
