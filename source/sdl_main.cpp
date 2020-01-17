#include "blit.h"
#include "Z80.h"
#include "GPU.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern LTexture gStreamingTexture;
extern DataStream gDataStream;

int main(int argc, char* args[]){
	//Start up SDL and create window
	if(!init()){
		printf("Failed to initialize!\n");
	}
	else{
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

            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            //Copy frame from buffer
            gStreamingTexture.lockTexture();
            gDataStream.genStatic(); //TODO: Move texture commands out of stream
            gDataStream.updateBuffer();
            gStreamingTexture.unlockTexture();

            //Render frame
            gStreamingTexture.render((SCREEN_WIDTH - gStreamingTexture.getWidth()) / 2, (SCREEN_HEIGHT - gStreamingTexture.getHeight()) / 2);

            //Update screen
            SDL_RenderPresent(gRenderer);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
