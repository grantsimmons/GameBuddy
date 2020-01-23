#include "blit.h"

Uint32 converter[WINDOW_WIDTH * WINDOW_HEIGHT];
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//DataStream gDataStream(1);
LTexture gStreamingTexture;

LTexture::LTexture(){
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPixels = NULL;
	mPitch = 0;
}

LTexture::~LTexture(){
	//Deallocate
	free();
}

bool LTexture::createBlank(int width, int height){
	//Create uninitialized texture
	mTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if(mTexture == NULL){
		printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
	}
	else{
		mWidth = width;
		mHeight = height;
	}

	return mTexture != NULL;
}

void LTexture::free(){
	//Free texture if it exists
	if(mTexture != NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		mPixels = NULL;
		mPitch = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if(clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth(){
	return mWidth;
}

int LTexture::getHeight(){
	return mHeight;
}

bool LTexture::lockTexture(){
	bool success = true;

	//Texture is already locked
	if(mPixels != NULL){
		printf("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else{
		if(SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0){
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}

bool LTexture::unlockTexture(){
	bool success = true;

	//Texture is not locked
	if(mPixels == NULL){
		printf("Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else{
		SDL_UnlockTexture(mTexture);
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

void* LTexture::getPixels(){
	return mPixels;
}

void LTexture::copyPixels(void* pixels){
	//Texture is locked
	if(mPixels != NULL){
		//Copy to locked pixels
		memcpy(mPixels, pixels, mPitch * mHeight);
	}
}

int LTexture::getPitch(){
	return mPitch;
}

Uint32 LTexture::getPixel32(unsigned int x, unsigned int y){
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32*)mPixels;

    //Get the pixel requested
    return pixels[ (y * (mPitch / 4)) + x ];
}

void DataStream::setScheme(int type){
    switch(type){
        case 0: //Black and white
            scheme = new Uint32[4] {0x000000, 0x555555, 0xABABAB, 0xFFFFFF};
            break;
        case 1: //Retro
            scheme = new Uint32[4] {0x0f380f, 0x306230, 0x0fac8b, 0x0fbc9b};
            break;
        case 2: //Random
            scheme = new Uint32[4];
            for(int i = 0; i < 4; i++){
                scheme[i] = rand() % 0xFFFFFF;
            }
            break;
        case 3: //Specified
            break;
        default:
            scheme = new Uint32[4] {0x0f380f, 0x306230, 0x0fac8b, 0x0fbc9b};
    }
    

}

Uint32* DataStream::atop(bool blackwhite = false){
    if(blackwhite){
        for(int x = 0; x < int(sizeof(converter) / sizeof(*converter)); x++){
            Uint32 conversion = Uint8(256 / 4 * gb_arr[x]);
            conversion |= conversion << 8 | conversion << 16; //Make all bytes equal
            conversion &= 0x00ffffff; //Limit to 24 bits
            converter[x] = conversion;
        }
    }
    else{
        for(int x = 0; x < int(sizeof(converter) / sizeof(*converter)); x++){
            converter[x] = scheme[gb_arr[x]]; //TODO: catch range error
        }
    }
    return converter; 
}

//Helper function to simulate memory population for gameboy display
void setConverter(Uint8* gb_input, int offset = 0){
    int i = 0;
    for(int x = 0; x < int(sizeof(converter) / sizeof(*converter)); x++){
        gb_input[x] = (++i + offset) % 4;
    }
}

SDL_Surface* SDL_ScaleSurface(SDL_Surface* surface, Uint16 x_scale, Uint16 y_scale){
    if(!surface || !x_scale || !y_scale){
        return NULL;
    }
    Uint32* orig_surface_pixels = (Uint32*) surface->pixels;
    SDL_Surface* ret = SDL_CreateRGBSurface(surface->flags, surface->w * x_scale, surface->h * y_scale, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    Uint32* dest_surface_pixels = (Uint32*) ret->pixels;
    for(Sint32 y = 0; y < surface->h; y++){
        for(Sint32 y_iter = 0; y_iter < y_scale; y_iter++){
            for(Sint32 x = 0; x < surface->w; x++){
                for(Uint16 x_iter = 0; x_iter < x_scale; x_iter++){
                    dest_surface_pixels[(x_scale * surface->w) * (y_scale * y + y_iter) + (x_scale * x + x_iter)] = orig_surface_pixels[(surface->w * y) + x]; 
                }
            }
        }
    }
    return ret;
}

DataStream::DataStream(uint8_t* gb_arr, int schemetype = 0): gb_arr(gb_arr){
    //gb_arr = gpu.getFB();
//DataStream::DataStream(int schemetype = 0){
    srand(time(NULL));
    setScheme(schemetype);
}

void DataStream::updateBuffer(){
    //update current image
    bool success = true;

    SDL_Surface* loadedSurface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, rmask, gmask, bmask, amask);

    if(loadedSurface == NULL){
        printf("ERROR");
        success = false;
    }
    else{
        //Pipeline:
        //  load blank surface
        //  copy uint array from memory
        //  convert to pixel array with memcpy
        //  scale surface (do only if needed)
        //  convert surface
        //  copy pixels to texture
        //  cleanup

        //setConverter(gb_arr);
        atop();

        SDL_memcpy(loadedSurface->pixels, converter, sizeof(Uint32) * WINDOW_WIDTH * WINDOW_HEIGHT); //Copy from newly created pixel array
        SDL_Surface* scaledSurface = SDL_ScaleSurface(loadedSurface, SCALE_WIDTH, SCALE_HEIGHT);

        SDL_FreeSurface(loadedSurface);

        loadedSurface = SDL_ConvertSurfaceFormat(scaledSurface, SDL_PIXELFORMAT_RGBA8888, 0);
        //loadedSurface = SDL_ConvertSurfaceFormat(SDL_ScaleSurface(loadedSurface, SCALE_WIDTH, SCALE_HEIGHT), SDL_PIXELFORMAT_RGBA8888, 0);
        SDL_FreeSurface(scaledSurface);
        gStreamingTexture.copyPixels(loadedSurface->pixels);
    }
    SDL_FreeSurface(loadedSurface);
    return;

}

void DataStream::genStatic(){
    for(int x = 0; x < int(sizeof(converter) / sizeof(*converter)); x++){
        gb_arr[x] = rand() % 4;
    }
    return;
}

bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Seed random
		srand(SDL_GetTicks());
        //srand(2);
        //srand(time(NULL));

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                if(!gStreamingTexture.createBlank(WINDOW_WIDTH * SCALE_WIDTH, WINDOW_HEIGHT * SCALE_HEIGHT)){
                    printf("Failed to create streaming texture!\n");
                    success = false;
                }
			}
		}
	}

	return success;
}

void close(){
	//Free loaded images
	gStreamingTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
