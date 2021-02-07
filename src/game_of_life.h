#ifndef GOL_H
#define GOL_H

#include <vector>
#include <iostream>

class GameOfLife {
    int size;
    std::vector<bool> state;

    public:
        GameOfLife(unsigned int size) : size(size), state(size * size, 0) {};
        std::vector<bool>::const_iterator begin() const {return state.begin();}
        std::vector<bool>::const_iterator end() const {return state.end();}
        void nextState();
        void setCell(int, int, bool);
        void flipCell(int, int);
        bool getCell(int, int);
        std::string toString();

    private:
        int  countNeighbours(int, int);
        int  toIndex(int, int);
};

#endif
