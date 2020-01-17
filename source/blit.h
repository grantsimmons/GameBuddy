#ifndef _BLIT_
#define _BLIT_

#include "SDL.h"
#include <time.h>
#include <stdio.h>
#include <string>
//#include "GPU.h"

//Screen dimension constants
const int WINDOW_WIDTH = 160;
const int WINDOW_HEIGHT = 144;
const int SCALE_WIDTH = 4;
const int SCALE_HEIGHT = 4;
const int SCREEN_WIDTH = WINDOW_WIDTH * 4;
const int SCREEN_HEIGHT = WINDOW_HEIGHT * 4;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Texture wrapper class
class LTexture{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();
		
		//Creates blank texture
		bool createBlank(int width, int height);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		//Pixel manipulators
		bool lockTexture();
		bool unlockTexture();
		void* getPixels();
		void copyPixels(void* pixels);
		int getPitch();
		Uint32 getPixel32(unsigned int x, unsigned int y);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		void* mPixels;
		int mPitch;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//A test animation stream
class DataStream{
	public:
		//Initializes internals
		DataStream(int schemetype);

		//Gets current frame data
        void updateBuffer();

        //Helper function to populate memory with random stimulus
        void genStatic();

        void setScheme(int type);

        Uint32* atop(bool blackwhite);

	private:
		//Internal data
        Uint8 gb_arr[WINDOW_WIDTH*WINDOW_HEIGHT];
        //uint8_t* gb_arr;
        Uint32* scheme; //indexed color cheme

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const Uint32 rmask = 0xff000000;
        const Uint32 gmask = 0x00ff0000;
        const Uint32 bamsk = 0x0000ff00;
        const Uint32 amask = 0x000000ff;
#else
        const Uint32 rmask = 0x000000ff;
        const Uint32 gmask = 0x0000ff00;
        const Uint32 bmask = 0x00ff0000;
        const Uint32 amask = 0xff000000;
#endif

};

extern Uint32 converter[WINDOW_WIDTH * WINDOW_HEIGHT];

//Scene textures
extern LTexture gStreamingTexture;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Animation stream
extern DataStream gDataStream;

#endif
