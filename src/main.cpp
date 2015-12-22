#include <iostream>

#include <SDL2/SDL.h>

#include "Netrom.h"

int main(int argc, char **argv) {

	netrom::Netrom* netrom = netrom::Netrom::init();

	netrom->mainLoop();
	delete netrom;

    return 0;
}
