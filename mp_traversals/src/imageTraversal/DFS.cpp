#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance): image_(&png), tolerance_(tolerance) {  
  start_ = Point(start.x, start.y);
  traversal_ = std::stack<Point>();
  traversal_.push(start_);
  //visited_ = std::vector<bool>(false, image_->width() * image_->height());
  //visited_.at(start_.x + (image_->width() * start_.y)) = true;
  //(width, height)
  visited_ = std::vector<std::vector<bool>>(image_->width(), std::vector<bool>(image_->height(), false));
  //visited_[start.x][start.y] = true;
  // Must we account for pixels out of bounds?
  /** @todo [Part 1] */
  //visited_ = std::vector<std::vector<bool>>(std::vector<bool>(false, image_->height()), image_->width())
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}
//Current plan is to make traversals NULL, and treat them as the same as traversals with empty data.

/**
 * Adds a Point for the traversal to visit at some point in the future.
 * Note: does not check bounds
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
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
  //const HSLAPixel& start_pixel = image_->getPixel(start_.x, start_.y);
  //if(point.x < image_->width() - 1 && !visited_[point.x + 1][point.y] && calculateDelta(image_->getPixel(point.x + 1, point.y), start_pixel) < tolerance_);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if(traversal_.empty()) {
    return Point(0, 0);
  }
  Point current = traversal_.top();
  visited_[current.x][current.y] = true;
  while(!traversal_.empty() && visited_[traversal_.top().x][traversal_.top().y]) {
    traversal_.pop();
  }
  return current;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if(traversal_.empty()) {
    return Point(0, 0);
  }
  return traversal_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return traversal_.empty();
}

//Note: does not check for bounds.
bool DFS::isValid(unsigned x, unsigned y) {
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

//Note: Code will be edited for grader compliance. The ImageTraversal should handle the add function.