#include "game_of_life.h"

void GameOfLife::nextState() {
    std::vector<bool> next_state(size * size, false);

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int neighbours = countNeighbours(x, y);

            if ((getCell(x, y) && neighbours == 2) || neighbours == 3)
                next_state[toIndex(x, y)] = true;
            else
                next_state[toIndex(x, y)] = false;
        }
    }

    state = next_state;
}

int GameOfLife::toIndex(int x, int y) {
    if (x < 0 || x >= size || y < 0 || y >= size)
        return -1;

    return (y * size) + x;
}

bool GameOfLife::getCell(int x, int y) {
    return state[toIndex(x, y)];
}

void GameOfLife::setCell(int x, int y, bool value) {
    state[toIndex(x, y)] = value;
}

void GameOfLife::flipCell(int x, int y) {
    int position = toIndex(x, y);
    state[position] = !state[position];
}

int GameOfLife::countNeighbours(int x, int y) {
    int total = 0;
    int position = toIndex(x, y);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int neighbour_pos = toIndex(x + i, y + j);

            if (neighbour_pos != -1)
                total += state[neighbour_pos] ? 1 : 0;
        }
    }

    return total - (state[position] ? 1 : 0);
}

std::string GameOfLife::toString() {
    std::string result("");

    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            result.append(getCell(x, y) ? "■" : "□");

            if (x == size - 1)
                result.append("\n");
        }

    return result;
}

