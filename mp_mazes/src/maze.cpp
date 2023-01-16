/* Your code here! */
#include <vector>
#include <queue>
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "maze.h"

void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    maze_ = std::vector<int>(width_ * height_, 0);
    if(maze_.empty()) {
        return;
        //Undefined behavior if further processing is done on empty.
        //This prevents this
    }
    DisjointSets path_set;
    path_set.addelements(width_ * height_);
    while(path_set.size(0) < width_ * height_) {
        int dir = rand() % 2;
        int randx = rand() % (width_ - 1 + dir);
        int randy = rand() % (height_ - dir);  //One below width_ and height_, so we may remove bottom or right
        //Direction is determined. Move right, and width_ is one less than size. Move down, and height_ is one less than size.
        if(dir == 0) {
            if(path_set.find(index(randx, randy)) == -1 || path_set.find(index(randx, randy)) != path_set.find(index(randx + 1, randy))) {
                maze_.at(index(randx, randy)) += 1;  //sets it to one if closed, or to 3 if bottom is open
                path_set.setunion(index(randx, randy), index(randx + 1, randy));
            }
        } else {
            if(path_set.find(index(randx, randy)) == -1 || path_set.find(index(randx, randy)) != path_set.find(index(randx, randy + 1))) {
                maze_.at(index(randx, randy)) += 2;  //sets it to 2 if closed, or to 3 if right is open
                path_set.setunion(index(randx, randy), index(randx, randy + 1));
            }
        }
    }
}

size_t SquareMaze::index(int x, int y) const {
    return y * width_ + x;
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) {
        return x < width_ && maze_.at(index(x, y)) % 2 == 1;
    }
    if (dir == 1) {
        return y < height_ && maze_.at(index(x, y)) / 2 == 1;
    }
    if (dir == 2) {
        return x > 0 && canTravel(x - 1, y, 0);
    }
    return y > 0 && canTravel(x, y - 1, 1);
}
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    //Does not protect overflow out of bounds
    if(dir == 0) {
        if(exists) {
            maze_.at(index(x, y)) = canTravel(x, y, 1)?2:0;
        } else {
            maze_.at(index(x, y)) = canTravel(x, y, 1)?3:1;
        }
    } else if (dir == 1) {
        if(exists) {
            maze_.at(index(x, y)) = canTravel(x, y, 0)?1:0;
        } else {
            maze_.at(index(x, y)) = canTravel(x, y, 0)?3:2;
        }
    }
}
std::vector<int> SquareMaze::solveMaze() {
    //return maze_;
    //Not implemented.
    std::vector<int> paths(width_ * height_, -1);
    paths.at(index(0, 0)) = 4;
    std::queue<std::pair<int, int>> traversal;
    std::pair<int, int> winner;
    traversal.push(std::pair<int, int>(0, 0));
    size_t path_size = 0; //tracks size of current path
    size_t largest_size = 0;
    //A BFS is performed with direction placed in next cell
    while(!traversal.empty()) {
        bool is_largest = true; //tracks steps. Is false when elements tie in size.
        for(int i = traversal.size(); i > 0; i--) {
            int currx = traversal.front().first;
            int curry = traversal.front().second;
            if(canTravel(currx, curry, 0) && paths.at(index(currx + 1, curry)) == -1) {
                paths.at(index(currx + 1, curry)) = 0;
                traversal.push(std::pair<int, int>(currx + 1, curry));
            }
            if(canTravel(currx, curry, 1) && paths.at(index(currx, curry + 1)) == -1) {
                paths.at(index(currx, curry + 1)) = 1;
                traversal.push(std::pair<int, int>(currx, curry + 1));
            }
            if(canTravel(currx, curry, 2) && paths.at(index(currx - 1, curry)) == -1) {
                paths.at(index(currx - 1, curry)) = 2;
                traversal.push(std::pair<int, int>(currx - 1, curry));
            }
            if(canTravel(currx, curry, 3) && paths.at(index(currx, curry - 1)) == -1) {
                paths.at(index(currx, curry - 1)) = 3;
                traversal.push(std::pair<int, int>(currx, curry - 1));
            }
            if(curry == height_ - 1) {
                if(is_largest || winner.first > traversal.front().first) {
                    winner = traversal.front();
                    is_largest = false;
                    largest_size = path_size;
                }
            }
            traversal.pop();
        }
        path_size++;
    }
    std::vector<int> winning_path(largest_size, 0);
    //This makes the path vector by retracing the winning path to origin
    for(int i = largest_size - 1; i >= 0; i--) {
        winning_path.at(i) = paths.at(index(winner.first, winner.second));
        if(winning_path.at(i) == 0) {
            winner.first--;
        } else if(winning_path.at(i) == 1) {
            winner.second--;
        } else if(winning_path.at(i) == 2) {
            winner.first++;
        } else if(winning_path.at(i) == 3) {
            winner.second++;
        }
    }
    return winning_path;
}

cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG* output = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);
    for(unsigned i = 0; i < output->height(); i++) {
        output->getPixel(0, i).l = 0.0;
    }
    for(unsigned i = 10; i < output->width(); i++) {
        output->getPixel(i, 0).l = 0.0;
    }
    for(int y = 0; y < height_; y++) {
        for(int x = 0; x < width_; x++) {
            if(maze_.at(index(x, y)) == 0) { //all closed
                for(unsigned i = 0; i <= 10; i++) {
                    output->getPixel((x + 1) * 10, y * 10 + i).l = 0.0;
                    output->getPixel(x * 10 + i, (y + 1) * 10).l = 0.0;
                }
            }
            if(maze_.at(index(x, y)) == 2) {  //only right closed
                for(unsigned i = 0; i <= 10; i++) {
                    output->getPixel((x + 1) * 10, y * 10 + i).l = 0.0;
                }
            }
            if(maze_.at(index(x, y)) == 1) {  //only down closed
                for(unsigned i = 0; i <= 10; i++) {
                    output->getPixel(x * 10 + i, (y + 1) * 10).l = 0.0;
                }
            }
        }
    }
    return output;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
    //return new cs225::PNG(width_, height_);
    //Not implemented
    cs225::PNG* output = drawMaze();
    std::vector<int> directions = solveMaze();
    int x_coord = 5;
    int y_coord = 5;
    output->getPixel(x_coord, y_coord).h = 0;
    output->getPixel(x_coord, y_coord).s = 1;
    output->getPixel(x_coord, y_coord).l = 0.5;
    for(size_t i = 0; i < directions.size(); i++) {
        if(directions.at(i) == 0) {
            for(int i = 0; i < 10; i++) {
                x_coord++;
                output->getPixel(x_coord, y_coord).h = 0;
                output->getPixel(x_coord, y_coord).s = 1;
                output->getPixel(x_coord, y_coord).l = 0.5;
            }
        }
        if(directions.at(i) == 1) {
            for(int i = 0; i < 10; i++) {
                y_coord++;
                output->getPixel(x_coord, y_coord).h = 0;
                output->getPixel(x_coord, y_coord).s = 1;
                output->getPixel(x_coord, y_coord).l = 0.5;
            }
        }
        if(directions.at(i) == 2) {
            for(int i = 0; i < 10; i++) {
                x_coord--;
                output->getPixel(x_coord, y_coord).h = 0;
                output->getPixel(x_coord, y_coord).s = 1;
                output->getPixel(x_coord, y_coord).l = 0.5;
            }
        }
        if(directions.at(i) == 3) {
            for(int i = 0; i < 10; i++) {
                y_coord--;
                output->getPixel(x_coord, y_coord).h = 0;
                output->getPixel(x_coord, y_coord).s = 1;
                output->getPixel(x_coord, y_coord).l = 0.5;
            }
        }
    }
    x_coord -= 4;
    for(int i = 0; i < 9; i++) {
        output->getPixel(x_coord, output->height() - 1).l = 1.0;
        x_coord++;
    }
    return output;
}

