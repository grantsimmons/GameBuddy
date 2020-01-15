#include "GPU.h"

GPU::GPU(){

}

GPU::step(){
    //Increment modeclock
    //this->_modeclock += z80._r.t;
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
            if(this->_mode_clock >= 456){
                this->_mode_clock = 0;
                this->_line++;

                if(this->_line > 153){
                    //Restart scanning mode
                    this->_mode = 2;
                    this->_line = 0;
                }
            }
            break;
    }
}
