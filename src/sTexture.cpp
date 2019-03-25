#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif

// Texture wrapper class
class sTexture
{
	private:
	
	public:	
	// init vars
	sTexture(){
		tex = NULL;
		width = 0;
		height = 0;
	}
	
	~sTexture(){
		free();
	}


	
	
	bool loadFromFile(SDL_Renderer * renderer, char *  path){
		// Remove any previous image
		free();
		//The final texture to be returned
		SDL_Texture * newTexture = NULL;
		
		// Load img
		SDL_Surface * loadedSurface = IMG_Load(path);
		if (!loadedSurface){
			SDL_Log("Unable to load image: %s\n",IMG_GetError());
			return NULL;
		}
		// Set colour key
		SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0xff,0x00,0xff));
		newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return NULL;
		}
		width = loadedSurface->w;
		height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		tex =  newTexture;
		
		return tex != NULL;
	}

	// Generates a flood filled prim for display of width and height
	// Uses SDL_FillRect (https://wiki.libsdl.org/SDL_FillRect)
	bool generate(SDL_Renderer * renderer, int w, int h){
		// Remove any previous image
		free();
		//The final texture to be returned
		SDL_Texture * newTexture = NULL;
		
		// Load img
		SDL_Surface * loadedSurface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
		SDL_FillRect( loadedSurface,NULL,SDL_MapRGB(loadedSurface->format,0xff,0x00,0x00));
		if (!loadedSurface){
			SDL_Log("Unable to render primative: %s\n",IMG_GetError());
			return NULL;
		}
		// Set colour key
		SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0xff,0x00,0xff));
		newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return NULL;
		}
		width = loadedSurface->w;
		height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		tex =  newTexture;
		
		return tex != NULL;
	}
	
	
	// Renders text to texture
	bool loadFromRenderedText(SDL_Renderer * renderer,TTF_Font * textFont,char * text, SDL_Color textColor)
	{
		// Remove any previous image
		free();
		//The final texture to be returned
		SDL_Texture * newTexture = NULL;
		
		// Load img
		SDL_Surface * loadedSurface = TTF_RenderText_Solid(textFont,text,textColor);
		if (!loadedSurface){
			SDL_Log("Unable to render: %s\n",TTF_GetError());
			return false;
		}
		// Set colour key
		//SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0xff,0x00,0xff));
		
		newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return false;
		}
		width = loadedSurface->w;
		height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		tex =  newTexture;
		
		return tex != NULL;
	}
	
	// Set color modulation
	void setColor(Uint8 r, Uint8 g, Uint8 b)
	{
		return;
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

	void render(SDL_Renderer * renderer, int x, int y){
		SDL_Rect  renderQuad = {x,y,width,height};
		// Render texture to screen
		SDL_RenderCopy(renderer, tex,NULL,&renderQuad);
	}

	int getWidth(){
		return width;
	}
	int getHeight(){
		return height;
	}

protected:
		SDL_Texture * tex;
		int width;
		int height;		
};

