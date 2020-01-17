#include "blit.h"
#include "Z80.h"
//#include "GPU.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern LTexture gStreamingTexture;
DataStream* gDataStream;

int main(int argc, char* args[]){
	//Start up SDL and create window
	if(!init()){
		printf("Failed to initialize!\n");
	}
	else{
        Z80 z80 = Z80(0,0,0,0,0,0,0,0,0,0,0,0,0,0);
        gDataStream = new DataStream(z80.getGPUFB(), 0);
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //While application is running
        int i = 0;
        while(!quit){
            //Handle events on queue
            while(SDL_PollEvent(&e) != 0){
                //User requests quit
                if(e.type == SDL_QUIT){
                    quit = true;
                }
            }
            z80.exec();
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
