#include "GPU.h"

GPU::GPU(uint8_t mode = 0, uint64_t modeclock = 0, uint16_t scy = 0, 
         uint16_t scx = 0, uint16_t line = 0, uint16_t lyc = 0, uint16_t wy = 0,
         uint16_t wx = 0):
        _mode(mode), _modeclock(modeclock), _scy(scy), _scx(scx), _line(line),
         _lyc(lyc), _wy(wy), _wx(wx){

}

void GPU::step(uint16_t ticks){
    //Increment modeclock
    this->_modeclock += ticks;
    switch(this->_mode){ //TODO: Enumerate for readability
        //OAM Read mode, scanline active
        case 2:
            if(this->_modeclock >= 80){
                //Enter scanline mode 3
                this->_modeclock = 0;
                this->_mode = 3;
            }
            break;

        //VRAM Read mode, scanline active
        //End of mode 3 is end of scanline
        case 3:
            if(this->_modeclock >= 172){
                this->_modeclock = 0;
                this->_mode = 0;
                this->renderScan();
            }
            break;

        //HBLANK
        //After last HBLANK, push screen data to front end
        case 0:
            if(this->_modeclock >= 204){
                this->_modeclock = 0;
                this->_line++;

                if(this->_line == 143){
                    //VBLANK
                    this->_mode = 1;
                    //TODO: Pass image data here
                }

                else{
                    this->_mode = 2;
                }
            }
            break;

        //VBLANK
        case 1:
            if(this->_modeclock >= 456){
                this->_modeclock = 0;
                this->_line++;

                if(this->_line > 153){
                    //Restart scanning mode
                    this->_mode = 2;
                    this->_line = 0;
                }
            }
            break;
    }
    return;
}

void GPU::renderScan(){
    return;
}

uint8_t GPU::rb(uint16_t addr){
    switch(addr){
        case 0xFF42:
            return this->_scy;
            break;

        case 0xFF43:
            return this->_scx;
            break;

        case 0xFF44:
            printf("Accessing line register\n");
            return this->_line;
            break;
    }
    return 0;
}

void GPU::wb(uint16_t addr, uint8_t val){
    switch(addr){
        case 0xFF42:
            this->_scy = val;
            break;
        case 0xFF43:
            this->_scx = val;
            break;
        case 0xFF44:
            this->_line = 0; //Read Only, reset when written
            break;
    }
}

void GPU::status(){
    printf("Mode: %d\n", _mode);
    printf("Mode Clock: %d\n", _modeclock);
    printf("Line: %d\n", _line);
    printf("SCY: %x\n", _scy);
    printf("SCX: %x\n", _scx);
    printf("LYC: %x\n", _lyc);
    printf("WY: %x\n", _wy);
    printf("WX: %x\n", _wx);

}

void GPU::getTicks(){
    printf("Ticks: %d\n", _modeclock);
}
