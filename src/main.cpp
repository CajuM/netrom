#include <iostream>

#include <SDL2/SDL.h>

#include "Netrom.h"

int main(int argc, char **argv) {

	netrom::Netrom* game = netrom::Netrom::init(argc, argv);

	game->mainLoop();
	game->del(game);

    return 0;
}
