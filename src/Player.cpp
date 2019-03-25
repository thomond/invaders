/*
Player class

*/ 
#ifndef ENTITY_H
#define ENTITY_H
#include "Entity.cpp"
#endif



// The player that will move around on the screen
// TODO: 
//       death and lives => Game.cpp logic to deal with this
//       
class Player : public Entity
{
	private:
	int livesLeft;
	int score;
	Mix_Chunk * pShootSnd;
    
    // Player related timer for death ani
	Timer deathTimer;
	public:
	static const int PLAYER_WIDTH = 32;
	static const int PLAYER_HEIGHT = 32;
	static const int PLAYER_POSY = SCREEN_H-64;
	static const int PLAYER_POSX = 64;
	static const int PLAYER_FRAME_ROW = 0;
	static const int PLAYER_FRAME_COL = 0;
	// axis velocity of the player
	static const int PLAYER_VEL = 10;
	static const int PLAYER_DEATH_FRAME_ROW = 0;
	static const int PLAYER_DEATH_FRAME_COL = 1;
	static const int PLAYER_LIVES = 6;
	//static const char * PLAYER_SHOOT_SND_PATH = "./res//smw_coin.wav";
	
	
	Player(): Entity()
	{
	}
	
	void init(SDL_Renderer * r){
		Entity::renderer = r;
		posx = PLAYER_POSX;posy = PLAYER_POSY;
		collider = {PLAYER_POSX,PLAYER_POSY,PLAYER_WIDTH,PLAYER_HEIGHT};
		currFrameCol = PLAYER_FRAME_COL; // Set current frame col to default defined
		currFrameRow = PLAYER_FRAME_ROW;
		tex->loadFromFile(r,"./res/tilesheet.png",PLAYER_WIDTH,PLAYER_HEIGHT);
		livesLeft = PLAYER_LIVES;
		score = 0;
		bullet = new Bullet(r, -1,-1,true); 	// Set bullet to default pos
		pShootSnd = Mix_LoadWAV( "./res//smw_coin.wav" );

	}
	
	// player event handler
	void handleEvent(SDL_Event& e){
		// handle key
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			// adjust velocity
			switch(e.key.keysym.sym)
			{
				case SDLK_a: velx -= PLAYER_VEL; break;
				case SDLK_d: velx += PLAYER_VEL; break;
				case SDLK_z: fired = true; break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			// adjust velocity
			switch(e.key.keysym.sym)
			{
				case SDLK_a: velx += PLAYER_VEL; break;
				case SDLK_d: velx -= PLAYER_VEL; break;
				case SDLK_z: fired = false; break;
			}
		}
	}
	
	// Move the player
	void move(){
		posx += velx;
		// update collision detection box
		collider.x = posx;
	}

	void update()
	{
		if (livesLeft<= 0)  return; // Bail if no lives left
		
		if(dead && deathTimer.isDone()) 
            reset(); // reset player if dead 

		// Check for bullet fire condition
		if(fired && !bullet->firing){
			bullet->fire( posx,posy);
			Mix_PlayChannel( -1, pShootSnd, 0 );
		}
		if(bullet->firing)
			bullet->update();
		
		
		// Move player
		if (doMove) move();
		
	}
	
	void render()
	{
		Entity::render();
		if(!bullet->destroyed) bullet->render();
	
	}
	
	void die(){
		dead = true;
		livesLeft--; 
		SDL_Log("Lives Left: %d", livesLeft); 
		currFrameCol = PLAYER_DEATH_FRAME_COL;
		currFrameRow = PLAYER_DEATH_FRAME_ROW;
        // Start player timer
        deathTimer.start(5000);
	}
	
	void reset(){
		dead=false;
		currFrameCol = PLAYER_FRAME_COL;
		currFrameRow = PLAYER_FRAME_ROW;
		
	}
	
	void toString(){
		SDL_Log("Pos: %d, %d Dim: %d, %d\f",posx,posy,PLAYER_WIDTH,PLAYER_HEIGHT);
		SDL_Log("Pos: %d, %d Dim: %d, %d\f",collider.x,collider.y,collider.w,collider.h);
	}
	
	int getLivesLeft(){
		return livesLeft;
	}
	
	int getScore(){
		return score;
	}
	
	int setScore(int s){
		score = s;
	}
};
