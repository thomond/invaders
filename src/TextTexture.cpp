#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#endif
#ifndef STEX_H
#define STEX_H
#include "sTexture.cpp"
#endif
#include "string.h"
// Texture wrapper class
class TextTexture : public sTexture
{
	private:
	SDL_Renderer * renderer;
	TTF_Font * textFont;
	SDL_Color textColor;
	char mText[50];
	public:	
	// Color consts
	static const SDL_Color COLOR_GREEN = {0,255,0};
	static const SDL_Color COLOR_RED = {255,0,0};
	static const SDL_Color COLOR_BLUE = {0,0,255};
	static const SDL_Color COLOR_WHITE = {255,255,255};
	
	// init vars
	TextTexture(SDL_Renderer * r, TTF_Font * f, SDL_Color c):sTexture(){
		if(!r)
            {SDL_Log("Renderer is NULL!\n");}
		else renderer = r;
		if(!f)
            {SDL_Log("Font is NULL!\n");}
		else textFont = f;
		textColor = c;
		strcpy(mText, "");
	}
	
	TextTexture(SDL_Renderer * r, TTF_Font * f, SDL_Color c,const char * initialText):TextTexture(r,f,c){
		strcpy(mText,initialText);
		
	}
	
	~TextTexture(){
		sTexture::free();
	}

	void setText(const char * t){
		strcpy(mText,t);
	}
	
	// Append to mText to render
	bool append(const char * t){
		strcat(mText,t);
	}
	
	// append an int to the string to print
	bool appendInt(int num){
		char lifeStr[10];
		sprintf(lifeStr,"%d",num);
		append(lifeStr);
	}
	
	// Renders mText to texture using the defined font, color and renderer
	bool setRenderedText()
	{
        setRenderedText(mText);
    }
	
	// Renders mText to texture using the defined font, color and renderer
	bool setRenderedText(char* text)
	{
		// Remove any previous image
		sTexture::free();
		//The final texture to be returned
		SDL_Texture * newTexture = NULL;
		
		// Load img
		SDL_Surface * loadedSurface = TTF_RenderText_Solid(textFont,text,textColor);
		if (!loadedSurface){
			SDL_Log("Unable to render: %s\n",TTF_GetError());
			return false;
		}
		
		newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return false;
		}
		sTexture::width = loadedSurface->w;
		sTexture::height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		sTexture::tex =  newTexture;
		if (!sTexture::tex) {SDL_Log("Setting rendered text failed!%s\n",SDL_GetError()); return false;}
		
		return true;
	}
	
	// Set color modulation
	void setColor(Uint8 r, Uint8 g, Uint8 b)
	{
		textColor = {r,g,b};
	}
	
	// Update mText texture with contents of ;mText'
	void update()
	{
		
		sTexture::free();
		// Load img
		SDL_Surface * loadedSurface = TTF_RenderText_Solid(textFont,mText,textColor);
		if (!loadedSurface){
			SDL_Log("Unable to render: %s\n",TTF_GetError());
			return false;
		}
		
		SDL_Texture * newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return false;
		}
		sTexture::width = loadedSurface->w;
		sTexture::height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		sTexture::tex =  newTexture;
	}
	
	void render(int x, int y){
		// Update mText before rendering
		//update();
		setRenderedText();
		sTexture::render(renderer, x,y);
	}
	
	void render(int x, int y, char* text){
		// Update mText before rendering
		//update();
		setRenderedText(text);
		sTexture::render(renderer, x,y);
	}
};

