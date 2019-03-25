/*
Martian class

*/ 
#ifndef ENTITY_H
#define ENTITY_H
#include "Entity.cpp"
#endif
#include <ctime>
#include "stdlib.h"
#include <random>
// The martian that will move around on the screen
// 
//       
//       
class Martian : public Entity
{
	public:
	// static Constantsg++
	static const int MARTIAN_WIDTH = 32;
	static const int MARTIAN_HEIGHT = 32;
	static const int MARTIAN_POSY = 32;
	static const int MARTIAN_POSX = 32;
	static const int MARTIAN_TYPEA = 0;
	static const int MARTIAN_TYPEB = 1;
	static const int MARTIAN_TYPEC = 2;
	// Tilesheet related constants for each enemy type
	static const int MARTIAN_TYPEA_FRAME_ROW = 1;
	static const int MARTIAN_TYPEA_FRAME_COL = 0;
	static const int MARTIAN_TYPEB_FRAME_ROW = 2;
	static const int MARTIAN_TYPEB_FRAME_COL = 0;
	static const int MARTIAN_TYPEC_FRAME_ROW = 3;
	static const int MARTIAN_TYPEC_FRAME_COL = 0;
	static const int MARTIAN_DEATH_FRAME_ROW = 4;
	// axis velocity of the martian
	static const int MARTIAN_VEL = MARTIAN_WIDTH;
	

	
	Martian(): Entity(){}
	
	Martian(SDL_Renderer * r, const int type) : Entity(r)
	{
		posx = MARTIAN_POSX;posy = MARTIAN_POSY;
		velx = MARTIAN_VEL,vely = MARTIAN_VEL;
		dead = false;
		collider = {MARTIAN_POSX,MARTIAN_POSY,MARTIAN_WIDTH,MARTIAN_HEIGHT};
		tex->loadFromFile(r,"./res/tilesheet.png",MARTIAN_WIDTH,MARTIAN_HEIGHT);
		// Set frame info
		switch(type)
		{
			case MARTIAN_TYPEA:
				currFrameRow = MARTIAN_TYPEA_FRAME_ROW;
				currFrameCol = MARTIAN_TYPEA_FRAME_COL;
			break;
			case MARTIAN_TYPEB:
				currFrameRow = MARTIAN_TYPEB_FRAME_ROW;
				currFrameCol = MARTIAN_TYPEB_FRAME_COL;
			break;
			case MARTIAN_TYPEC:
				currFrameRow = MARTIAN_TYPEC_FRAME_ROW;
				currFrameCol = MARTIAN_TYPEC_FRAME_COL;
			break;
		}	
		//martianTexture->generate(r,MARTIAN_WIDTH,MARTIAN_HEIGHT);
		
		// Init timer vals for firing logic and then start timer
		srand(time(NULL));
		bullet = new Bullet(r, -1,-1,false); 
	}
	
	
	

	
	// Move the martian
	void move(){
		posx += velx; //posy = vely;
		// Update animation 
		// if it using starting frame (0) imcrement, if not then decrement
		if(currFrameCol == MARTIAN_TYPEC_FRAME_COL) currFrameCol++;
		else currFrameCol--;
		collider.x = posx; collider.y = posy; 
		return;
		
	}
	
	void update()
	{
		// Cjecks whather to fire; 
		// Gets a num between 1 and 5000 and if num is 1 it fires 
		// E.G. there is 1 in 5000 of it occuring
		int num = rand()%5000;
		if (num==1)
			//SDL_Log("%d",num);
			bullet->fire( posx,posy);
				
		if (bullet->firing)
			bullet->update();
		return;
	}
	
	void render(){
		Entity::render();
		if (bullet->firing)
			bullet->render();
		return;
	}
	
	void descend(){
		posy += vely;
		collider.x = posx; collider.y = posy;
		// Reverse direction of martian
		velx = -velx;
		return;
	}
	
	void die(){
		dead = true;
		currFrameCol = 0;
		currFrameRow = MARTIAN_DEATH_FRAME_ROW;
	}
	
	void toString(){
		SDL_Log("Pos: %d, %d Dim: %d, %d\f",posx,posy,MARTIAN_WIDTH,MARTIAN_HEIGHT);
		SDL_Log("Pos: %d, %d Dim: %d, %d\f",collider.x,collider.y,collider.w,collider.h);
	}
	
};
