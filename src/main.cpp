#include <iostream>

#include <SDL2/SDL.h>

#include "netrom.h"

int main(int argc, char **argv) {

	netrom::Netrom* game = netrom::Netrom::init();

	game->mainLoop();
	game->del(game);

    return 0;
}
