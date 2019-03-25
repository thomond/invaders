class DisplayManager
{
    DisplayManager * INSTANCE = NULL;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    // singleton
    DisplayManager * getInstance()
    {
        if (INSTANCE == NULL) INSTANCE = new DisplayManager();
        else return INSTANCE;
    }
    
    // Returns  blank SDL_Texture that can be set as render target
    static SDL_Texture*  createNewTargetTexture(int w, int h){
        return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);// SDL_TEXTUREACCESS_TARGET must be set 
    }
    
    bool init(char* title, int scr_w, int scr_h){
        // create main mWindow and renderer
        // Show window
		window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scr_w, scr_h, SDL_WINDOW_SHOWN);
		if (!window) {
			SDL_Log("Window could not be created",SDL_GetError());
			return false;
		}
		// Create renderer 
		mRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
		if(!mRenderer){
			SDL_Log("renderer could not be created",SDL_GetError());
			return false;
		}
        
    }
    
    // Render a src texture to a destination texture, e.g. layer. Texture nust have the right flags
    bool renderTo(sTexture *texSrc, sTexture *texDest){
        SDL_SetRenderTarget(mRenderer, texDest);
        
        SDL_SetRenderTarget(mRenderer, texDest);
    }
    
    bool render(){
        //SDL_RenderPresent(mRenderer);
        texSrc->render(mRenderer);
    }
};

/*
 * SDL_Texture* auxtexture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 500);

//change the rendering target

SDL_SetTextureBlendMode(auxtexture, SDL_BLENDMODE_BLEND);
SDL_SetRenderTarget(ren, auxtexture);

//render what we want
triangle->render(ren); //render my class triangle e.g


//change the target back to the default and then render the aux

SDL_SetRenderTarget(ren, NULL); //NULL SETS TO DEFAULT
SDL_RenderCopy(ren, auxtexture, NULL, canvas->drect);
SDL_DestroyTexture(auxtexture);
Cheers.

shareimprove this answer
edited Sep 12 '13 at 6:33
answered Sep 6 '13 at 20:36

chelo_c
89811327
3
Some tips for future readers. Always make sure you initialize your SDL_Renderer with the SDL_RENDERER_TARGETTEXTURE flag to support render targets. Also, never try to use a SDL_Texture that was created from a SDL_Surface using the SDL_CreateTextureFromSurface function. It just won't work.  Justin Skiles Feb 26 '14 at 3:51
@JustinSkiles I'm glad someone noticed the lack of SDL_RENDERER_TARGETTEXTURE, for a brief moment I thought either I'd gone crazy or the api had suddenly changed to allow all renderers to render straight to render target textures
 */
