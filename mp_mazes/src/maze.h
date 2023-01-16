/* Your code here! */
#pragma once
#include <vector>
#include <queue>
#include "dsets.h"
#include "cs225/PNG.h"

class SquareMaze {
    public:
    //SquareMaze(); Constructor follows rule of zero.
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    std::vector<int> solveMaze();
    cs225::PNG* drawMaze() const;
    cs225::PNG* drawMazeWithSolution();
    private:
    //Given x and y, returns the 1D coordinate for the vector maze
    size_t index(int x, int y) const;
    //consider changing width_ and height_ to ints in case of parameter bugs,
    int width_;
    int height_;
    //This is a 1D vector of size width_ * height_. It contains the state of each grid
    //0 == closed, 1 == right wall open, 2 == down wall open, 3 == both walls open
    std::vector<int> maze_;
};