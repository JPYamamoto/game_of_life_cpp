#ifndef GUI_H
#define GUI_H

#include "game_of_life.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class GUI {
    public:
        GUI(int board_size, int cell_size);
        ~GUI();
        bool init(const char *title, int x_pos, int y_pos);
        void handleEvents();
        void start();
        void stop();
        void render();
        void clean();
        bool isActive() { return is_active; }

    private:
        bool is_active;
        bool is_running;
        int width;
        int height;
        int board_size;
        int cell_size;
        int top_grid;
        TTF_Font *font;
        SDL_Texture *label;
        std::string text;

        GameOfLife *game_of_life;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        SDL_TimerID timer;

        static Uint32 nextState(Uint32 interval, void * param);
        void drawButtons();
        void drawGrid();
        void drawBoard();
        void drawCell(int x, int y);
        void handleClick(SDL_MouseButtonEvent &button);
        void defineLabel();
};

#endif
