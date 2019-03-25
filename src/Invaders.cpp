#include "stdio.h"

#include "Game.cpp"

#include "Bullet.cpp"
#include "Player.cpp"
#include "Martian.cpp"
#include "TextTexture.cpp"



class Invaders : public Game
{
private:
    Player player;
    
    TTF_Font * hudFont = NULL;
    sTexture hudTex;
    TextTexture * scoreText;
    TextTexture * livesText;
    // quit flag
    bool quit = false;
    // Event handler
    SDL_Event e;
    // Internal bounds for the game
    SDL_Rect rBorder,lBorder, hudRect;

    Uint32 mTimer = 0;
    bool mTimerRunning = false;
    Uint32 mTiming = 3000; // Time to wait between moves in ms

    const int mWaveSzRow = 5;
    const int mWaveSzCol = 11;
    Martian * wave[5][11];
    
    Bullet * playerBullet = NULL;     // Set bullet to NULL until fired

public:
    Invaders() : Game(){
        
    }
    
    bool init(){
        Game::init();
        // Init player and bullet
        player.init(renderer);
        playerBullet = player.getBullet();
        
        lBorder = {0,0,16,SCREEN_H};
        rBorder = {SCREEN_W-16,0,16,SCREEN_H};
        
        setHUD();
        
        setEnemies();
        // Start movement timer
        mTimerRunning = true;
        mTimer = SDL_GetTicks();
    }

    void doLoop(){
        bool inLoop = true;
        while(inLoop){
            // Handle input events in queue by polling them
            while(SDL_PollEvent(&e) != 0)
            {
                // User requests quit
                if (e.type == SDL_QUIT)
                    inLoop = false;
                player.handleEvent(e);
            }
            
            
            clear();
            update();
            render();
        }
    }
    
    void update(){
        updateHUD();
        updatePlayer();
        updateBullets();
        updateEnemies();
    }
    
    void clear(){
        Game::clear();
    }
    
    void render(){

        renderHUD();
        player.render();
        renderEnemies();
        Game::render();
    }
protected:
    
    updatePlayer(){
        if(player.collidesWith(&rBorder)|| player.collidesWith(&lBorder) )
            player.doMove = false; // Stop player
        else player.doMove = true;
        player.update();    
    }
    
    updateBullets(){
        // Chk if bullet has left screen and delete otherwise move it further     
        if (playerBullet->getPosy() <=0)
            playerBullet->reset();
        
    }
    
    updateEnemies(){

        // Move martians evey 1.5 seconds
        // Todo: change this val to varible depending on top most row
        Uint32 currTime = SDL_GetTicks();
        if((currTime - mTimer) >= mTiming){
            for (int i=0;i< mWaveSzRow;i++  )
                for (int y=0;y< mWaveSzCol;y++ ){
                    /* if (wave[i][y] == NULL) continue;
                    if (wave[i][y]->dead ){ // If sprite is dead remove it
                        delete wave[i][y]; wave[i][y] = NULL; break;
                    } 
                    else */
                    wave[i][y]->move();
                }
            
            mTimer = SDL_GetTicks();// reset movment timer
        }
        
        // Go through each enemny in array and check if it collides with borders or bullets
        // If it does loop through each one again and descend each martian 
        // so that the entire group descends at once
        for (int i=0;i<mWaveSzRow ; i++)
        {
            for (int y=0;y<mWaveSzCol ; y++)
            {
                if (wave[i][y]->dead) continue; 
                // Bullet coll detection with player
                if(wave[i][y]->getBullet()->collidesWith(player.getCollisionRect())){
                    player.die();
                    wave[i][y]->getBullet()->reset();
                }
                // Game over if collides with player or floor
                if(wave[i][y]->collidesWith(player.getCollisionRect()))
                    player.die();
                
                if(wave[i][y]->getPosy()>=SCREEN_H)
                    SDL_Log("Game Over");
                // Descend logic
                if(wave[i][y]->collidesWith(&rBorder)||wave[i][y]->collidesWith(&lBorder)){
                    if (mTiming >= 20) mTiming = mTiming - 200; // Make wave move faster
                    for (int ii=0;ii<mWaveSzRow ; ii++)
                        for (int yy=0;yy<mWaveSzCol ; yy++ )
                            wave[ii][yy]->descend();
                    break;
                }
                if(!playerBullet->destroyed && playerBullet->collidesWith(wave[i][y]->getCollisionRect()))// Delete bullet and destroy enemy
                {
                    wave[i][y]->die();
                    player.setScore(player.getScore()+20);
                    playerBullet->reset();
                } 
                wave[i][y]->update();
                
            }
        } 
        
    }
    
    void setHUD(){
         // Top HUD for score and lives
        hudFont = TTF_OpenFont("./res/lazy.ttf",24);
        if(!hudFont){ 
            SDL_Log("Failed to loaf TTF: %s",TTF_GetError()); 
            return -1;
        }
        
        scoreText = new TextTexture(renderer, hudFont,TextTexture::COLOR_WHITE);
        livesText = new TextTexture(renderer, hudFont,TextTexture::COLOR_WHITE);

        hudRect = {0,0,SCREEN_W,32};
        
        hudTex.generate(renderer,hudRect.w,hudRect.h);
    }
    
    void updateHUD(){
        if(scoreText && livesText){
            scoreText->setText("Score: ");
            scoreText->appendInt(player.getScore());
            livesText->setText("Lives: ");
            livesText->appendInt(player.getLivesLeft());
        }
        
    }

    void renderHUD(){
        hudTex.render(renderer, hudRect.x, hudRect.y);
        scoreText->render(20, 5);
        livesText->render(SCREEN_W - 100, 5);
    }

    void renderEnemies(){
        // Render wave
        for (int i=0; i<mWaveSzRow;i++ )
            for (int y=0;y<mWaveSzCol ; y++)
                if (!wave[i][y]->dead) wave[i][y]->render();
    }
    
    void setEnemies(){
        
        for (int i=0; i<mWaveSzRow; i++)
        {
            int type;
            if (i==0) type = Martian::MARTIAN_TYPEC;
            else if (i==1||i==2) type = Martian::MARTIAN_TYPEB;
            else if (i==3||i==4) type = Martian::MARTIAN_TYPEA;
            for (int y=0; y<mWaveSzCol; y++ )
            {
                wave[i][y] = new Martian(renderer,type);
                // Place each enemy so that they sit next to each other
                int offset = 34;
                wave[i][y]->moveTo((y*Martian::MARTIAN_WIDTH),offset+(i*Martian::MARTIAN_HEIGHT));
            }
            
        }
    }
    
};
