#ifndef _GPU_
#define _GPU_

#include <cstdint>
#include <Z80.h>

class GPU{
    public:

        GPU();

        void step();

    private:
        _mode;
        _modeclock;
        _line;
}

#endif
