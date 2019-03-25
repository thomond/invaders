#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif
#ifndef STEX_H
#define STEX_H
#include "sTexture.cpp"
#endif
/* Tilesheet class 
   inherits from sTexture
   
 */
class tsTexture : public sTexture
{
	public:	
	// init vars
	tsTexture():sTexture(){
		frameWidth = 0;
		frameHeight = 0;
		framex = 0;
		framey = 0;
	}
	
	~tsTexture(){
		sTexture::free();
	}

	
	
	bool loadFromFile(SDL_Renderer * renderer, char *  path, int fw, int fh){
		frameWidth = fw; frameHeight = fh;
		return sTexture::loadFromFile(renderer, path);
	}

	void free(){
		if (tex != NULL)
		{
			SDL_DestroyTexture(tex);
			tex = NULL;
			width = 0;
			height = 0;
		}
	}

	// Using the renderer context render to x,y using row and col of tilesheet
	void render(SDL_Renderer * renderer, int x, int y, int col, int row){
		SDL_Rect  dstQuad = {x,y,getFrameWidth(),getFrameHeight()};
		// where in the tile sheet to copy 
		// The parameters sent in are row and column which is tranlated to real x,y coords by multiplying by the frame w/h
		SDL_Rect srcQuad = {(col*getFrameWidth()),(row*getFrameHeight()),getFrameWidth(),getFrameHeight()};
		// Render texture to screen
		SDL_RenderCopy(renderer, tex,&srcQuad,&dstQuad);
	}
	
	void render(SDL_Renderer * renderer, int x, int y){
		sTexture::render(renderer,x,y);
	}
	
	// Sets the current frame to draw using x,y pair representing col and row of tilesheet
	bool setFrame(int _framex, int _framey){
		framex = _framex;
		framey = _framey;
	}
	
	int getFrameWidth(){
		return frameWidth;
	}
	
	int getFrameHeight(){
		return frameHeight;
	}

private:
		int frameWidth;
		int frameHeight;
		int framex,framey;
};

