#include "game_of_life.h"
#include "gui.h"

int main() {
    const int FPS = 60;
    GUI *gui = new GUI(50, 20);

    if (!gui->init("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)) {
        exit(1);
    }

    while (gui->isActive()) {
        gui->handleEvents();
        gui->render();
        SDL_Delay(1000 / FPS);
    }

    gui->clean();

    return 0;
}

