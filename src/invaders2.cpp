/*
Space invaders

TODO:
add display logic for HUD; score and lives
player reset
pause/quit/reset game
add bases
add flying saucers
*/ 
const int SCREEN_W = 640;
const int SCREEN_H = 480;
#include "Invaders.cpp"

int main(int argc, char *argv[])
{
	Invaders game;
	game.init();
	game.doLoop();
}
