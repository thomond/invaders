/*
Entity class

*/ 
#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif
#ifndef TEX_H
#define TEX_H
#include "tsTexture.cpp"
#endif


// Entity abstract class
//       
class Entity
{
	protected:
	// x and y offsets of the player; posy will always be at fixed location
	int posx,posy;
	// velocity of the player - only move left and right
	int velx,vely;
	// Tilesheet Texture for the player
	tsTexture * tex;
	
	// player's collison box
	SDL_Rect collider;
	// The current frame for the player character 
	int currFrameCol,currFrameRow;
	
	Bullet * bullet; 	// Set bullet to NULL until fired
	
	public:
	
	// set render context for player
	SDL_Renderer * renderer;
	
	//states
	bool fired; // Weather the player has fired a bullet
	bool dead;
	bool doMove;
	
	Entity()
	{ 	
		velx = 0,vely = 0; 
		fired = false;
		doMove = true;
		dead = false;
		tex = new tsTexture();
	} 
	
	Entity(SDL_Renderer * r):Entity()
	{
		renderer = r;
		Entity::Entity();
		
	}
	
	bool collidesWith(SDL_Rect * obj)
	{
		// Update collison detection box to next location 
		collider.x += velx;
		collider.y += vely;
		if (SDL_HasIntersection(&collider,obj)){
			SDL_Log("Collision.\n");
			SDL_Log("collision at %d ,%d.\n",collider.x,collider.y);
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
	
	// Absolute movment func
	void moveTo(int x, int y){
		posy = y;
		posx = x;
		// update collision detection box
		collider.x = posx;
		collider.y = posy;
	}
	
	//Show player
	void render(){
		tex->render(renderer,posx,posy,currFrameCol,currFrameRow);
		return;
	}
	
	Bullet * getBullet(){
		return bullet;
	}
	
	int getPosx()
	{
		return posx;
	}
	int getPosy()
	{
		return posy;
	}
	
	int getVelx()
	{
		return posx;
	}
	int getVely()
	{
		return posy;
	}
	
	void setVelx(int v)
	{
		velx = v;
	}
	void setVely(int v)
	{
		vely = v;
	}
};
