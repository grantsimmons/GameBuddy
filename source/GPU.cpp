#include "GPU.h"
#include "blit.h"

#define BG_MEM_SELECT (1<<3)
#define TILE_SET_SELECT (1<<4)
#define LCD_EN (1<<5)


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

                //TODO: Move SDL functiosn to VBLANK
                
                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                gStreamingTexture.lockTexture();
                this->renderScan(); //Update Frame Buffer
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
                    gDataStream->updateBuffer(); //Push Frame to SDL Surface
                    gStreamingTexture.unlockTexture();

                    //Render frame
                    gStreamingTexture.render((SCREEN_WIDTH - gStreamingTexture.getWidth()) / 2, (SCREEN_HEIGHT - gStreamingTexture.getHeight()) / 2);

                    //Update screen
                    SDL_RenderPresent(gRenderer);
                
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
    bool window_en = false;
    bool sig = false;
    uint16_t base_addr = 0x8000;
    uint16_t bg_mem = 0x9800;

    if(_lcdc & LCD_EN){
        if(_wy <= _line){
            window_en = true;
        }
    }

    if(_lcdc & TILE_SET_SELECT){
        base_addr = 0x8000; //Unsigned 0x8000-0x8FFF
        sig = false;
    }
    else{
        base_addr = 0x8800; //Signed 0x8800-0x97FF, 0x9000 at center
        sig = true;
    }

    if(!window_en){
        if(_lcdc & BG_MEM_SELECT){
            bg_mem = 0x9c00;
        }
        else{
            bg_mem = 0x9800;
        }
    }
    else{
        if(_lcdc & (1<<6)){
            bg_mem = 0x9C00;
        }
        else{
            bg_mem = 0x9800;
        }
    }

    uint16_t ypos = 0;
    if(!window_en){
        ypos = _scy + _line;
    }
    else{
        ypos = _line - _wy;
    }

    //get vertical pixels of scanline
    uint16_t tile_row = (ypos << 2); // * 32 / 8
    uint16_t xpos;

    for(uint16_t pixel = 0; pixel < 160; pixel++){
        xpos = pixel + _scx;
        //translate to window space if needed
        if(window_en){
            if(pixel >= _wx - 7){
                xpos = pixel - (_wx - 7);
            }
        }

        //which of 32 horizontal tiles
        uint16_t tile_col = (uint16_t) (xpos >> 3); // / 8
        int16_t tile_num;
        uint16_t tile_addr = bg_mem + tile_row + tile_col; //multiply row by line length?

        if(!sig){
            tile_num = (uint8_t) this->readVram(tile_addr);
        }
        else{
            tile_num = (int8_t) this->readVram(tile_addr);
        }

        uint16_t tile_loc = base_addr;

        if(!sig){
            tile_loc += (tile_num * 16);
        }
        else{
            tile_loc += ((tile_num + 128) * 16);
        }

        //find vertical line of tile we're on
        uint8_t line = ypos % 8;
        line <<= 1;
        uint8_t data1 = this->readVram(tile_loc + line);
        uint8_t data2 = this->readVram(tile_loc + line + 1);
        int color_bit = xpos % 8;
        color_bit -= 7;
        color_bit *= -1;
        int color_num = data2 & (1 << color_bit) ? 1 : 0;
        color_num |= data1 & (1 << color_bit) ? 1 : 0;
        //color_num &= 0xF;
        //printf("Color num: %x\n", color_num);

        //printf("Color: %x\n", getColor(color_num));
        this->_framebuffer[160 * _line + pixel] = (uint8_t) getColor(color_num); //from 0xFF47
    }
    return;
}

uint8_t GPU::getColor(uint8_t color_num){
	switch(color_num){
		case 0:
			return _pal & 0x3;
		case 1:
			return (_pal & 0xC) >> 2;
		case 2:
			return (_pal & 0x30) >> 4;
		case 3:
			return (_pal & 0xC0) >> 6;
		default:
			printf("ERROR: invalid color");
			return 0;
	}
}

uint8_t GPU::rb(uint16_t addr){
    switch(addr){
        case 0xFF40:
            return this->_lcdc;

        case 0xFF42:
            return this->_scy;

        case 0xFF43:
            return this->_scx;

        case 0xFF44:
            //printf("Accessing line register\n");
            return this->_line;

        case 0xFF45:
            return this->_lyc;

        case 0xFF47:
            return this->_pal;

        case 0xFF4A:
            return this->_wy;

        case 0xFF4B:
            return this->_wx;
    }
    return 0;
}

void GPU::wb(uint16_t addr, uint8_t val){
    switch(addr){
        case 0xFF40:
            this->_lcdc = val;
            break;

        case 0xFF42:
            this->_scy = val;
            break;
            
        case 0xFF43:
            this->_scx = val;
            break;
            
        case 0xFF44:
            this->_line = 0; //Read Only, reset when written
            break;

        case 0xFF45:
            this->_lyc = val;
            break;

        case 0xFF47:
            this->_pal = val;
            break;

        case 0xFF4A:
            this->_wy = val;
            break;

        case 0xFF4B:
            this->_wx = val;
            break;

        default:
            break;
    }
}

uint8_t GPU::readVram(uint16_t addr){
    return _vram[addr & 0x1FFF];
}

void GPU::writeVram(uint16_t addr, uint8_t val){
    _vram[addr & 0x1FFF] = val;
}

void GPU::status(){
    printf("Mode: %d\n", _mode);
    printf("Mode Clock: %d\n", _modeclock);
    printf("LCDC: %02x\n", _lcdc);
    printf("Line: %d\n", _line);
    printf("SCY: %x\n", _scy);
    printf("SCX: %x\n", _scx);
    printf("LYC: %x\n", _lyc);
    printf("PAL: %02x\n", _pal);
    printf("WY: %x\n", _wy);
    printf("WX: %x\n", _wx);

}

void GPU::getTicks(){
    printf("Ticks: %d\n", _modeclock);
}

uint8_t* GPU::getFB(){
    return this->_framebuffer;

}

void GPU::printFB(){
    printf("FRAME BUFFER\n");
    for(uint32_t i = 0; i < 160 * 144; i++){
            printf("%02x ", this->_framebuffer[i]);
            if (i % 160 == 159)
                printf("\n");
    }
    
}
