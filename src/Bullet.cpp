#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif
#ifndef STEX_H
#define STEX_H
#include "sTexture.cpp"
#endif

class Bullet
{
private:
	// Varibles for the bullet
	int posy,posx;
	sTexture * bulletTex;
	// martian's collison box
	SDL_Rect collider;
	int vely,velx;
public:
    // Bullet constants
	static const int BULLET_WIDTH = 2;
	static const int BULLET_HEIGHT = 4;
	static const int BULLET_VELX = 0;// Velocity is constant
	static const int BULLET_VELY = 4;
	
	SDL_Renderer * renderer;
	bool firing, destroyed;
	
	Bullet(){}
	
	Bullet(SDL_Renderer *r, int x, int y, bool north)
	{
		posy = y,posx = x;
		// If north is specified set vel to north (-y) else south (y)
		if (north) vely = -BULLET_VELY;
		else vely = BULLET_VELY;
		velx = BULLET_VELX;
		
		collider = {x,y,BULLET_WIDTH,BULLET_HEIGHT};
		renderer = r;
		bulletTex = new sTexture();
		bulletTex->generate(renderer, BULLET_WIDTH,BULLET_HEIGHT);
		firing = false;
		destroyed = false;
	}
	

	~Bullet()
	{
		if (bulletTex != NULL)
		{
			reset();
			renderer = NULL;
			bulletTex->free();
			
		}
	}
	
	// reset the bullet 
	bool reset()
	{
		if (!destroyed)
		{
			destroyed = true;
			firing = false;
			SDL_Log("Bullet destroyed at %d,%d", posx,posy);
			moveTo(-1,-1);
		}
		
	}
	
	bool fire(int x, int y)
	{
		destroyed = false;
		firing = true;
		SDL_Log("Bullet fired at %d,%d", posx,posy);
		moveTo(x,y);
	}
	
	bool collidesWith(SDL_Rect * obj)
	{	
		// Update collison detection box to next location 
		collider.x += velx;
		collider.y += vely;
		if (SDL_HasIntersection(&collider,obj)){
			SDL_Log("Bullet collision at %d ,%d.\n",collider.x,collider.y);
			// Reset collison quad
			collider.x -= velx;
			collider.y -= vely;
			
			return true;
		}
		else{
			collider.x -= velx;
			collider.y -= vely;
			return false;
		}
	}
	
	SDL_Rect * getCollisionRect(){
		return &collider;
	}
	
	// Move the martian
	void move(){
		posy += vely;
		collider.x = posx; collider.y = posy; 
		return;
		
	}

	void update(){
		if(destroyed) reset();
		else move();
	}
	
	void moveTo(int x, int y){
		posx = x;
		posy = y;
		// update collision detection box
		collider.x = posx;
		collider.y = posy;
	}
	
	void render(){
		bulletTex->render(renderer,posx,posy);
		return;
	}
	
	int getPosy(){
		return posy;
	}
	
	int getPosx(){
		return posx;
	}
	
	void toString(){
		SDL_Log("Bullet Pos: %d, %d Dim: %d, %d\f",posx,posy,BULLET_WIDTH,BULLET_HEIGHT);
		SDL_Log("Bullet collider Pos: %d, %d Dim: %d, %d\f",collider.x,collider.y,collider.w,collider.h);
	}
};
