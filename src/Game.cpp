//Game include
#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#endif
#include "Timer.cpp"
class Game
{
private:

public:
	
	SDL_Window * window;
	// Screen renderer
	SDL_Renderer * renderer;
	const int SCREEN_W = 640;
	const int SCREEN_H = 480;
	
	Game()
	{
		window = NULL;
		// Screen renderer
		renderer = NULL;
	}

	bool init()
	{
		// Init SDL
		if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)< 0 )
		{
			SDL_Log("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
			return false;
		}
		// load support for the PNG image formats
		int flags = IMG_INIT_PNG;
		int initted=IMG_Init(flags);
		if((initted&flags) != flags) {
			SDL_Log("IMG_Init: Failed to init required image support!\n");
			SDL_Log("IMG_Init: %s\n", IMG_GetError());
			return false;
		}
		// Init TTF_lib
		if(TTF_Init()==-1){
			SDL_Log("TTF_Init: %s\n", TTF_GetError());
			return false;
		}
		 //Initialize SDL_mixer
		 if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{
			SDL_Log( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			return false;
		} 
    
		// Show window
		window = SDL_CreateWindow("SDL Test",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
		if (!window) {
			SDL_Log("Window could not be created",SDL_GetError());
			return false;
		}
		// Create renderer
		renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
		if(!renderer){
			SDL_Log("renderer could not be created",SDL_GetError());
			return false;
		}
		// Renderer BG color
		SDL_SetRenderDrawColor(renderer, 0x00,0x00,0x00,0x00);
		
		/* Enable standard application logging */ 
		SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO); 
		
		return true;
	}

	void clear(){
		SDL_RenderClear(renderer);
	}
	
	void render(){
		SDL_RenderPresent(renderer);
	}
	
	bool setRenderScale(int sx, int sy){
		SDL_RenderSetScale(renderer,sx,sy);
	}
	
	SDL_Renderer * getRenderer(){
		return renderer;
	}
	
	bool * setRenderer(SDL_Renderer * r){
		renderer = r;
	}
};
