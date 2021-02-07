#include "gui.h"
#include <SDL2/SDL_timer.h>

#define START "Start"
#define STOP "Stop"

GUI::GUI(int board_size, int cell_size) {
    this->board_size = board_size;
    this->cell_size = cell_size;

    this->is_running = false;
    this->is_active = false;
    this->width = board_size * cell_size;
    this->height = board_size * cell_size;
    this->top_grid = cell_size;
    this->text = START;

    this->game_of_life = new GameOfLife(board_size);
}

GUI::~GUI() {
    delete game_of_life;
}

bool GUI::init(const char *title, int x_pos, int y_pos) {
    is_active = false;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error initializing the GUI system: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "GUI system initialized." << std::endl;
    window = SDL_CreateWindow(title, x_pos, y_pos, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Error creating the window: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Window created." << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Error creating the renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Renderer created." << std::endl;

    if (TTF_Init() < 0) {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }

    std::cout << "Fonts renderer created." << std::endl;
    this->font = TTF_OpenFont("src/font.ttf", 12);

    if (font == NULL) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
    }

    std::cout << "Fonts loaded successfully." << std::endl;
    defineLabel();

    is_active = true;
    return true;
}

void GUI::handleEvents() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                is_active = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleClick(event.button);
                break;
        }
    }
}

void GUI::start() {
    std::cout << "Starting process." << std::endl;
    timer = SDL_AddTimer(1000, &nextState, this);
    text = STOP;
    defineLabel();
    is_running = true;
}

void GUI::stop() {
    std::cout << "Stopping process." << std::endl;
    SDL_RemoveTimer(timer);
    text = START;
    defineLabel();
    is_running = false;
}

void GUI::defineLabel() {
    SDL_Surface * surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
    this->label = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Uint32 GUI::nextState(Uint32 interval, void *param) {
    ((GUI *)param)->game_of_life->nextState();
    return interval;
}


void GUI::handleClick(SDL_MouseButtonEvent &event) {
    if (event.button == SDL_BUTTON_LEFT) {
        int mouse_x = event.x;
        int mouse_y = event.y - top_grid;

        if (mouse_y < 0) {
            if (is_running) {
                stop();
            } else {
                start();
            }
        } else {
            int cell_x = mouse_x / cell_size;
            int cell_y = mouse_y / cell_size;

            game_of_life->flipCell(cell_x, cell_y);
        }
    }
}

void GUI::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    drawButtons();
    drawGrid();
    drawBoard();

    SDL_RenderPresent(renderer);
}

void GUI::drawButtons() {
    if (is_running) {
        SDL_SetRenderDrawColor(renderer, 128, 0, 0, SDL_ALPHA_OPAQUE);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, SDL_ALPHA_OPAQUE);
    }

    SDL_Rect rect_button = {
        .x = 0,
        .y = 0,
        .w = width,
        .h = top_grid
    };

    int text_width;
    TTF_SizeText(font, text.c_str(), &text_width, NULL);
    int offset = (width - text_width) / 2;

    SDL_Rect rect_text = {
        .x = offset,
        .y = 0,
        .w = text_width,
        .h = top_grid
    };

    SDL_RenderFillRect(renderer, &rect_button);
    SDL_RenderCopy(renderer, label, NULL, &rect_text);
}

void GUI::drawGrid() {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

    for (int x = cell_size; x <= width; x += cell_size) {
        SDL_RenderDrawLine(renderer, x, top_grid, x, height);
    }

    for (int y = top_grid + cell_size; y <= height; y += cell_size) {
        SDL_RenderDrawLine(renderer, 0, y, width, y);
    }
}

void GUI::drawBoard() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            if (game_of_life->getCell(x, y)) {
                drawCell(x, y);
            }
        }
    }

}

void GUI::drawCell(int x, int y) {
    SDL_Rect rect = {
        .x = (x * cell_size),
        .y = (y * cell_size) + top_grid,
        .w = cell_size,
        .h = cell_size
    };

    SDL_RenderFillRect(renderer, &rect);
}

void GUI::clean() {
    if (window) {
        SDL_DestroyWindow(window);
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    if (font) {
        TTF_CloseFont(font);
    }

    TTF_Quit();
    SDL_Quit();

    std::cout << "Cleaned GUI. Exiting." << std::endl;
}
