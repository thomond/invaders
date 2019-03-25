#ifndef SDL_TTF_H
#define SDL_TTF_H
#include "SDL2/SDL_ttf.h"
#endif

#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#endif


class UIManager()
{
    
    UIManager * INSTANCE = NULL;
    
    // Sound states
    enum State
    {
      Undefined, // USed when uninitialised 
      Playing,
      Stopped,
      Paused
    };
    enum State mBGMState = State.Undefined;
    
    // singleton
    UIManager * getInstance()
    {
        if (INSTANCE == NULL) INSTANCE = new UIManager();
        else return INSTANCE;
    }
    
    bool init(){
        // Init TTF_lib
		if(TTF_Init()==-1){
			SDL_Log("TTF_Init: %s\n", TTF_GetError());
			return false;
		}
    }
    
    
    void drawText(char* text){}
    
    void playFX(char* filename){}
    
    
};
