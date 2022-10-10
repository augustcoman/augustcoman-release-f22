#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance): image_(&png), tolerance_(tolerance) {  
  start_ = Point(start.x, start.y);
  traversal_ = std::queue<Point>();
  traversal_.push(start_);
  visited_ = std::vector<std::vector<bool>>(image_->width(), std::vector<bool>(image_->height(), false));
  //visited_[start.x][start.y] = true;
  /** @todo [Part 1] */
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /*
  if(point.x < image_->width() - 1 && isValid(point.x + 1, point.y)) {
    traversal_.push(Point(point.x + 1, point.y));
  }
  if(point.y < image_->height() - 1 && isValid(point.x, point.y + 1)) {
    traversal_.push(Point(point.x, point.y + 1));
  }
  if(point.x > 0 && isValid(point.x - 1, point.y)) {
    traversal_.push(Point(point.x - 1, point.y));
  }
  if(point.y > 0 && isValid(point.x, point.y - 1)) {
    traversal_.push(Point(point.x, point.y - 1));
  }
  */
  if(isValid(point.x, point.y)) {
    traversal_.push(Point(point.x, point.y));
  }
  /** @todo [Part 1] */
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if(traversal_.empty()) {
    return Point(0, 0);
  }
  Point current = traversal_.front();
  visited_[current.x][current.y] = true;
  while(!traversal_.empty() && visited_[traversal_.front().x][traversal_.front().y]) {
    traversal_.pop();
  }
  return current;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(traversal_.empty()) {
    return Point(0, 0);
  }
  return traversal_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return traversal_.empty();
}

bool BFS::isValid(unsigned x, unsigned y) {
  if(x >= image_->width() || y >= image_->height()) {
    return false;
  }
  if(visited_[x][y]) {
    return false;
  }
  const HSLAPixel& start_pixel = image_->getPixel(start_.x, start_.y);
  const HSLAPixel& curr_pixel = image_->getPixel(x, y);
  return calcDelta(start_pixel, curr_pixel) < tolerance_;
}