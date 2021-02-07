#include<iostream>
#include<SDL.h>
#include"Window.h"
#include"TextureManager.h"
#include"Game.h"
int main(int, char**) {
	Game* game = Game::instance();
	game->mainloop();
	return 0;
}